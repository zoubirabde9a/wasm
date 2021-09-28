/* date = September 1st 2021 10:52 pm */

#ifndef DEFINES_H
#define DEFINES_H
#include "stdint.h"
#include <stddef.h>


typedef uint8_t u8;
typedef int8_t i8;
typedef uint32_t u32;
typedef int32_t i32;
typedef i32 bool32;

#define internal static
#define memory_index u32

typedef struct app_files
{
    char *Contents[256];
    char *Names[256];
    memory_index Size[256];
    u32 Count;
}app_files;

typedef struct app_console
{
    char *Messages[256];
    u32 Size[256];
    u32 Count;
}app_console;

#define DEBUG
inline void Assert(bool32 Condition)
{
#ifdef DEBUG
    if (!Condition)
    {
        int *Ptr = 0;
        *(Ptr) = 0;
    }
#endif
}

#endif //DEFINES_H
