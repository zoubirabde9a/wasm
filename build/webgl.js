
export function InitWebGL(gl, env)
{
	var GlobalGLTextures = [];

    function createTexture()
    {
        GlobalGLTextures.push(gl.createTexture());
    	return GlobalGLTextures.length - 1;
    }

    function deleteTexture(Index)
    {
    	if (Index < GlobalGLTextures.length)
    	{
    		gl.deleteTexture(GlobalGLTextures[Index]);
    		GlobalGLTextures.splice(Index, 1);
    	}
    }

    function glEnable(Flags)
    {
    	gl.enable(Flags);
    }

    function glBlendFunc(SFactor, DFactor)
    {
    	gl.blendFunc(SFactor, DFactor);
    }

    function glClearColor(Red, Green, Blue, Alpha)
    {
    	gl.clearColor(Red, Green, Blue, Alpha);
    }

	function glClear(Flags)
	{
		gl.clear(Flags);
	}

    env["ConsoleLog"] = console.log;
    env["glCreateTexture"] = createTexture;
    env["glDeleteTexture"] = deleteTexture;
    env["glEnable"] = glEnable;
    env["glBlendFunc"] = glBlendFunc;
    env["glClearColor"] = glClearColor;
    env["glClear"] = glClear;

}