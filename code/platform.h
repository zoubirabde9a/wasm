/* date = September 3rd 2021 6:00 pm */

#ifndef PLATFORM_H
#define PLATFORM_H


typedef struct platform_read_entire_file_result
{
    void *Contents;
    memory_index Size;
}platform_read_entire_file_result;


#define PlatformReadEntireFile(Name) platform_read_entire_file_result Name(char *FileName)

typedef PlatformReadEntireFile(platform_read_entire_file);

typedef struct app_platform
{
    platform_read_entire_file *ReadEntireFile;
}app_platform;

#endif //PLATFORM_H
