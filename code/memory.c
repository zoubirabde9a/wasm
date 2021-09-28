

typedef struct memory_arena
{
    u8 *Base;
    memory_index Size;
    memory_index Used;
    u32 TempCount;
}memory_arena;

typedef struct temporary_memory
{
    memory_arena *Arena;
    memory_index Used;
}temporary_memory;

inline void
InitializeArena(memory_arena *Arena,
                memory_index *Base, memory_index Size)
{
    Arena->Base = (u8 *)Base;
    Arena->Size = Size;
    Arena->Used = 0;
    Arena->TempCount = 0;
}

inline memory_index
GetAlignmentOffset(memory_arena *Arena, memory_index Alignment)
{
    memory_index Offset = 0;
    memory_index Ptr = (memory_index)Arena->Base + Arena->Used;
    memory_index Mask = Alignment - 1;
    if (Ptr & Mask)
    {
        Offset = Alignment - (Ptr & Mask);
    }
    
    return Offset;
}

inline memory_index
GetArenaSizeRemaining(memory_arena *Arena, memory_index Alignment)
{
    memory_index SizeRemaining;
    SizeRemaining = Arena->Size - (Arena->Used + GetAlignmentOffset(Arena, Alignment));
    return SizeRemaining;
}

inline void *
ArenaAllocateSize(memory_arena *Arena, memory_index PrefSize, memory_index Alignment)
{
    memory_index Size = PrefSize;
    
    memory_index AlignmentOffset = GetAlignmentOffset(Arena, Alignment);
    Size += AlignmentOffset;
    
    Assert(Arena->Size >=(Arena->Used + Size));
    void *Result = Arena->Base + Arena->Used + AlignmentOffset;
    Arena->Used += Size;
    
    return Result;
}

#define AllocateStruct(Arena, Type, ...) (Type *)ArenaAllocateSize(Arena, sizeof(Type), ##__VA_ARGS__)
#define AllocateArray(Arena, Count, Type, ...) (Type *)ArenaAllocateSize(Arena, (Count) * sizeof(Type), ##__VA_ARGS__)

#define AllocateStruct4(Arena, Type) AllocateStruct(Arena, Type, 4)
#define AllocateArray4(Arena, Count, Type) AllocateArray(Arena, Count, Type, 4)


internal void
CopyMemory(void *Source, void *Dest, memory_index Size)
{
    u8 *SourceU8 = (u8 *)Source;
    u8 *DestU8 = (u8 *)Dest;
    memory_index Index;
    for(Index = 0; Index < Size; Index++)
    {
        DestU8[Index] = SourceU8[Index];
    }
};

internal u32 
StringLength(char *String)
{
    u32 Result = 0;
    int Index;
    for(Index = 0; String[Index]; Index++)
    {
        Result ++;
    }
    return Result;
}


inline char *
ArenaAllocateString(memory_arena *Arena, char *Source)
{
    memory_index StringSize = StringLength(Source) + 1;
    char *Dest = AllocateArray4(Arena, StringSize, char);
    CopyMemory(Source, Dest, StringSize);
    return Dest;
}


inline temporary_memory
BeginTemporaryMemory(memory_arena *Arena)
{
    temporary_memory Result;
    
    Result.Arena = Arena;
    Result.Used = Arena->Used;
    Arena->TempCount++;
    
    return Result;
}

inline void
ZeroSize(void *Ptr, memory_index Size)
{
    u8 *BytePtr = (u8 *)Ptr;
    while(Size--)
    {
        *BytePtr++ = 0;
    }
}

#define ZeroArray(Array, Count, Type) ZeroSize(Array, (Count) * sizeof(Type))

inline void
CopyString(char *Dest, memory_index DestSize, char *Src)
{
    while(*Src)
    {        
        *Dest = *Src++;
        DestSize--;
        if (DestSize == 0)
        {
            break;
        }
    }
}

inline void
EndTemporaryMemory(temporary_memory TempMemory)
{
    memory_arena *Arena = TempMemory.Arena;
    Assert(Arena->Used >= TempMemory.Used);
    Assert(Arena->TempCount > 0);
    
    memory_index MemoryFreed = Arena->Used - TempMemory.Used;
    Arena->Used = TempMemory.Used;    
    Arena->TempCount--;
    ZeroSize(Arena->Base + Arena->Used, MemoryFreed);
}

inline void
SubArena(memory_arena *Dest, memory_arena *Src,
         memory_index Size, memory_index Alignment)
{
    Dest->Size = Size;
    Dest->Base = (u8 *)ArenaAllocateSize(Src, Size, Alignment);
    Dest->Used = 0;
    Dest->TempCount = 0;
}

inline void
SubArena16(memory_arena *Dest, memory_arena *Src,
           memory_index Size)
{
    SubArena(Dest, Src, Size, 16);
}
#if 0
inline void *
Allocate(memory_index Size)
{
    void *Result = GlobalMemory + GlobalMemoryPosition;
    GlobalMemoryPosition += Size;
    return Result;
}
#endif

#if 0
internal char *AllocateString(char *String)
{
    u32 Size = StringLength(String);
    char *StringBuffer = Allocate(Size + 1);
    CopyMemory(String, StringBuffer, Size + 1);
    
    return StringBuffer;
}
#endif

#if 0
char *AllocateStringSize(char *String, u32 Size)
{
    char *StringBuffer = Allocate(Size + 1);
    CopyMemory(String, StringBuffer, (memory_index)(Size + 1));
    
    return StringBuffer;
}
#endif

internal bool32 CompareString(char *A, char *B)
{
    bool32 Result = 1;
    
    int CurrentIndex;
    for(CurrentIndex = 0;
        A[CurrentIndex] && B[CurrentIndex];
        CurrentIndex++)
    {
        if (A[CurrentIndex] != B[CurrentIndex])
        {
            Result = 0;
            break;
        }
    }
    
    if (A[CurrentIndex] || B[CurrentIndex])
    {
        Result = 0;
    }
    
    return Result;
}

internal void CopyStringSize(char *Source, char *Dest, int Size)
{
    for(int CurrentIndex = 0; CurrentIndex < Size; CurrentIndex++)
    {
        Dest[CurrentIndex] = Source[CurrentIndex];
    }
}

#if 0
void CopyString(char *Source, char *Dest)
{
    int CurrentIndex;
    for(CurrentIndex = 0; Source[CurrentIndex]; CurrentIndex++)
    {
        Dest[CurrentIndex] = Source[CurrentIndex];
    }
    Dest[CurrentIndex] = '\0';
}
#endif