const fs = require('fs')

      async function init() {

      	var files = [];
		var fileNames = [];
		function readTextFile(file)
		{
			var rawFile = new XMLHttpRequest();
			rawFile.open("GET", file, false);
			rawFile.onreadystatechange = function ()
				{
				    if(rawFile.readyState === 4)
				    {
				        if(rawFile.status === 200 || rawFile.status == 0)
				        {
				            var allText = rawFile.responseText;
				            files.push(allText);
				            fileNames.push(file);
				        }
				    }
				}
			rawFile.send(null);
		}	
		readTextFile("README.txt");
		readTextFile("LICENSE");

		const buf = fs.readFileSync('./bare_metal_wasm.wasm')

        const { instance } = await WebAssembly.instantiate(
          buf, {}
        ); // here

        const width = 600;
        const height = 600;

        const canvas = document.getElementById("demo-canvas");
        canvas.width = width;
        canvas.height = height;

        const buffer_address = instance.exports.BUFFER.value; // here
        const image = new ImageData(
            new Uint8ClampedArray(
                instance.exports.memory.buffer, //here
                buffer_address,
                4 * width * height,
            ),
            width,
        );

		const { go, AddFile, GetFileContent, memory } = instance.exports

        const ctx = canvas.getContext("2d");
        var timestamp = 0;
        const ar = new Int8Array(memory.buffer, 0, 5)
        ar.set([72, 70, 60, 50, 0]);
        var result = go(ar.byteOffset, ar.length); 
	    console.log(`bb ${result}`); // here
	    console.log(result);


        for(let FileIndex = 0; FileIndex < files.length; FileIndex++)
        {
        	var ThisFile = files[FileIndex];
        	var ThisFileName = fileNames[FileIndex];

        	var FileData = new Int8Array(memory.buffer, 0, ThisFile.length);
        	for(let CharacterIndex = 0; CharacterIndex < ThisFile.length; CharacterIndex++)
        	{
        		FileData[CharacterIndex] = ThisFile[CharacterIndex];
        	}
		    AddFile(ThisFileName, FileData.byteOffset, FileData.length);
        }

	    ctx.putImageData(image, 0, 0);
      }

      init();