#include "defines.h"
#include "platform.h"
#include "opengl.c"
#include "asset.h"

extern void ConsoleLog(float Value);
extern void ConsoleLogString(char *Value, int Size);

extern GLuint glCreateTexture();
extern void glDeleteTexture(GLuint Texture);

extern void glEnable(GLenum Cap);
extern void glBlendFunc(GLenum SFactor,
                        GLenum DFactor);
extern void glClear(GLbitfield Mask);
extern void glClearColor(GLclampf Red,
                         GLclampf Green,
                         GLclampf Blue,
                         GLclampf Alpha);

extern int JSGetFileSize(int Asset);
//extern char *JSReadEntireFile(int Asset);
extern char *JSReadEntireFile(char *FileName, int Size);

internal void 
glGenTextures(GLsizei N, GLuint* Textures)
{
    int CurrentIndex;
    for(CurrentIndex = 0;
        CurrentIndex < N; CurrentIndex++)
    {
        GLuint Texture = glCreateTexture();
        Textures[CurrentIndex] = Texture;
    }
}

internal void 
glDeleteTextures(GLsizei N, GLuint* Textures)
{
    int CurrentIndex;
    for(CurrentIndex = 0;
        CurrentIndex < N; CurrentIndex++)
    {
        glDeleteTexture(Textures[CurrentIndex]);
    }
}


internal void
WebLoadOpenglFunctions(open_gl *OpenGL)
{
    OpenGL->glClear = glClear;
    OpenGL->glEnable = glEnable;
    OpenGL->glBlendFunc = glBlendFunc;
    OpenGL->glGenTextures = glGenTextures;
    OpenGL->glDeleteTextures = glDeleteTextures;
    OpenGL->glClearColor = glClearColor;
}

#define GLOBAL_MEMORY_SIZE 1024 * 1024 * 50
#define GLOBAL_TEMPORARY_MEMORY_SIZE 1024 * 1024 * 50

u8 GlobalMemory[GLOBAL_MEMORY_SIZE];
u8 GlobalTemporaryMemory[GLOBAL_TEMPORARY_MEMORY_SIZE];

#include "memory.c"

PlatformReadEntireFile(WebReadEntireFile)
{
    platform_read_entire_file_result Result = {};
    
    u32 *Data = 
    (u32 *)JSReadEntireFile(FileName, 
                            StringLength(FileName));
    Result.Size = *Data;
    Data++;
    Result.Contents = Data;
    
    return Result;
}


#include "app.c"

open_gl OpenGL;
app_state AppState;
app_platform AppPlatform;

void WebInit()
{
    InitializeArena(&AppState.Memory, (void *)GlobalMemory, GLOBAL_MEMORY_SIZE);
    InitializeArena(&AppState.TemporaryMemory, (void *)GlobalTemporaryMemory, GLOBAL_TEMPORARY_MEMORY_SIZE);
    WebLoadOpenglFunctions(&OpenGL);
    
    AppPlatform.ReadEntireFile = WebReadEntireFile;
    
    AppInit(&OpenGL, &AppState, &AppPlatform);
}
void
WebRun(float TimeStamp)
{
    AppMainLoop(&OpenGL, &AppState, TimeStamp);
}
