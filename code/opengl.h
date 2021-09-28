/* date = September 3rd 2021 0:50 pm */

#ifndef OPENGL_H
#define OPENGL_H

typedef u32 GLbitfield;
typedef float GLclampf;
typedef unsigned char GLubyte;
typedef u32 GLuint;
typedef unsigned int GLenum;
typedef i32 GLint;
typedef i32 GLsizei;
typedef unsigned char GLboolean;
typedef float GLfloat;
typedef void GLvoid;
typedef char GLchar;
typedef ptrdiff_t GLsizeiptr;
typedef ptrdiff_t GLintptr;

#ifndef GL_VERSION
#define GL_VERSION                        7938
#define GL_SRC_ALPHA                      770
#define GL_ONE_MINUS_SRC_ALPHA            771
#define GL_COLOR_BUFFER_BIT               16384
#define GL_DEPTH_BUFFER_BIT               256
#define GL_TEXTURE_2D                     3553
#define GL_FLOAT                          5126
#define GL_UNSIGNED_BYTE                  5121
#define GL_TEXTURE_WRAP_S                 10242
#define GL_TEXTURE_WRAP_T                 10243
#define GL_TEXTURE_MAG_FILTER             10240
#define GL_TEXTURE_MIN_FILTER             10241
#define GL_LINEAR_MIPMAP_LINEAR           9987
#define GL_NEAREST                        9728
#define GL_CLAMP_TO_EDGE                  33071
#define GL_ALPHA                          6406
#define GL_BLEND                          0x0BE2
#define GL_FALSE                          0
#define GL_TRUE                           1
#define GL_TRIANGLES                      4
#define GL_LINE_LOOP                      2
#define GL_LINEAR                         9729
#define GL_REPEAT                         10497
#define GL_RGBA                           6408
#define GL_RGB                            6407
#define GL_INFO_LOG_LENGTH                0x8B84
#define GL_ARRAY_BUFFER                   0x8892
#define GL_STATIC_DRAW                    0x88E4
#define GL_DYNAMIC_DRAW                   0x88E8
#define GL_DYNAMIC_READ                   0x88E9
#define GL_DYNAMIC_COPY                   0x88EA
#define GL_COMPILE_STATUS                 0x8B81
#define GL_VERTEX_SHADER                  0x8B31
#define GL_FRAGMENT_SHADER                0x8B30
#define GL_LINK_STATUS                    0x8B82
#endif


typedef void type_glGenTextures(GLsizei N,
                                GLuint* Texutres);
typedef void type_glDeleteTextures(GLsizei N,
                                   GLuint* Texutres);
typedef void type_glEnable(GLenum Cap);
typedef void type_glBlendFunc(GLenum SFactor,
                              GLenum DFactor);
typedef void type_glClear(GLbitfield Mask);
typedef void type_glClearColor(GLclampf Red,
                               GLclampf Green,
                               GLclampf Blue,
                               GLclampf Alpha);

#define OpenGLFunction(Name) type_##Name *Name


typedef struct open_gl
{
    OpenGLFunction(glGenTextures);
    OpenGLFunction(glDeleteTextures);
    OpenGLFunction(glEnable);
    OpenGLFunction(glBlendFunc);
    OpenGLFunction(glClear);
    OpenGLFunction(glClearColor);
    
}open_gl;

#endif //OPENGL_H
