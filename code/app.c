
#include "app.h"

const unsigned int WIDTH = 600;
const unsigned int HEIGHT = 600;
unsigned int BUFFER[WIDTH * HEIGHT];
unsigned int douf[1024 * 1024 * 20];

unsigned int *GetBuffer()
{
    return BUFFER;;
}

app_files Files;
app_console Console;

int PrintInteger(char *Buffer, int Value)
{
    u32 CurrentIndex = 0;
    while(Value > 0)
    {
        Buffer[CurrentIndex++] = (Value & 1) + '0';
        Value /= 10;
    }
    
    Buffer[CurrentIndex] = '\0';
    return CurrentIndex;
}


#if 0
internal void ConsoleErrorMessage(char *Message)
{
    u32 MessageSize = StringLength(Message);
    Console.Messages[Console.Count] = 
        AllocateStringSize(Message, MessageSize);
    Console.Size[Console.Count++] = MessageSize;
}

int ConsoleGetMessageCount()
{
    return Console.Count;
}

int ConsoleGetMessageSize(int Index)
{
    return Console.Size[Index];
}

char *ConsoleGetMessage(int Index)
{
    return Console.Messages[Index];
}
#endif

#if 0
int GetFileIndex(char *FileName)
{
    int FileIndex;
    for(FileIndex = 0;
        FileIndex < Files.Count;
        FileIndex++)
    {
        char *ThisName = Files.Names[FileIndex];
        if (CompareString(FileName, ThisName))
        {
            ConsoleLog((float)FileIndex);
            char Buffer[256];
            //PrintInteger(Buffer, FileIndex);
            ConsoleErrorMessage("1");
            
            return FileIndex;
        }
    }
    
    return -1;
}

char *GetFileContent(int Index)
{
    Assert(Index < Files.Count);
    return Files.Contents[Index];
}

int GetFileSize(int Index)
{
    Assert(Index < Files.Count);
    return Files.Size[Index];
}

void AddFile(char *Name, char *Content, int ContentSize) 
{
    void *FileData = Allocate(ContentSize);
    CopyStringSize(Content, FileData, ContentSize);
    Files.Contents[Files.Count] = FileData;
    char *NameData = AllocateString(Name);
    Files.Names[Files.Count] = NameData;
    Files.Size[Files.Count] = ContentSize;
    Files.Count++;
}
#endif

platform_read_entire_file *ReadEntireFile;

internal void 
AppInit(open_gl *OpenGL, app_state *AppState, 
        app_platform *AppPlatform)
{
    OpenGL->glEnable(GL_BLEND);
    OpenGL->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    OpenGL->glGenTextures(1, &AppState->Texture);
    
    ReadEntireFile = AppPlatform->ReadEntireFile;
    
    
    for(int i = 0; i < 1; i++)
    {
        platform_read_entire_file_result Result =
            ReadEntireFile("test.html");
        //ConsoleLogString(Result.Contents, Result.Size);
    }
    for(int i = 0; i < 1; i++)
    {
        platform_read_entire_file_result Result =
            ReadEntireFile("README.txt");
        //ConsoleLogString(Result.Contents, Result.Size);
    }
#if 0
    ConsoleLogString("Here", StringLength("Here"));
    ConsoleLog((float)Result.Size);
    ConsoleLogString(Result.Contents, StringLength(Result.Contents));
#endif
}

internal void 
AppMainLoop(open_gl *OpenGL, app_state *AppState,
            float TimeStamp)
{
    static float a = 0;
    a += TimeStamp / 10000.f * 2.f;
    if (a >= 1.f)
    {
        a = 0;
    }
    ConsoleLog(a);
    OpenGL->glClearColor(a, a, 1.f - a, 1.f);
    OpenGL->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    ConsoleLog((float)AppState->Texture);
    ConsoleLogString("ab", 2);
    
}
#if 0
int go(char *Text, int TextSize) {
    glClearColor(1.f, 0.f, 1.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT() | GL_DEPTH_BUFFER_BIT());
    
    int x;
    for (x = 0; x < WIDTH; x++) {
        int y;
        for (y = 0; y < HEIGHT; y++) {
            unsigned int color;
            if (y < HEIGHT/2) {
                color = 0xff00ffff; // RGBA little endian
            } else {
                color = 0xffff0000; // RGBA little endian
            }
            
            BUFFER[WIDTH * x + y] = color;;
        }
    }
    return Text[2];
}
#endif
