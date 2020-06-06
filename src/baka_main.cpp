#include "Baka.h"
#include "baka_graphics.h"
#include "baka_input.h"
#include <SDL.h>
//#include <SDL2/SDL.h>
#include "baka_logger.h"

#include <baka_stack_allocator.h>

BakaApplication *prog = NULL;
void CloseApplication();

struct something_else
{
    int a;
    char c[4];
    float f;
};

void print_stuff(baka::StackAllocatorMarker stackaint, baka::StackAllocatorMarker stackchar, baka::StackAllocatorMarker stackelse)
{
    int *aint = (int*)stackaint.pData;
    for(int i = 0; i < stackaint.allocatedSize / sizeof(int); i++)
    {
        bakalog("aint[%d] == %d", i, aint[i]);
    }

    char *achar = (char*)stackchar.pData;
    for(int i = 0; i < stackchar.allocatedSize / sizeof(char); i++)
    {
        bakalog("achar[%d] == %c", i, achar[i]);
    }

    struct something_else *aelse = (struct something_else *)stackelse.pData;
    for(int i = 0; i < stackelse.allocatedSize / sizeof(something_else); i++)
    {
        bakalog("aelse[%d]: {a: %d, f: %f, c: %s}", i, aelse[i].a, aelse[i].f, aelse[i].c);
    }
}

int main(int argc, char *argv[])
{
    prog = new BakaApplication();
    if (!prog) return 0;
    bool running = false;
    bakalog("--==== Start of application ====--");
    
    prog->Main(argc, argv);
    atexit(CloseApplication);
    
    running = baka::Graphics::IsInit();

    baka::StackAllocator sa = baka::StackAllocator(4096);

    baka::StackAllocatorMarker stackaint = sa.Allocate(sizeof(int) * 16);
    bakalog("stack allocator marker data - size: %lu\tpData: %lu", stackaint.allocatedSize, stackaint.pData);
    int *aint = (int*)stackaint.pData;
    for(int i = 0; i < stackaint.allocatedSize / sizeof(int); i++)
    {
        aint[i] = i*5;
    }
    
    baka::StackAllocatorMarker stackchar = sa.Allocate(sizeof(char) * 16);
    bakalog("stack allocator marker data - size: %lu\tpData: %lu", stackchar.allocatedSize, stackchar.pData);
    char *achar = (char*)stackchar.pData;
    for(int i = 0; i < stackchar.allocatedSize / sizeof(char); i++)
    {
        achar[i] = 'a' + i;
    }

    baka::StackAllocatorMarker stackelse = sa.Allocate(sizeof(something_else) * 32);
    bakalog("stack allocator marker data - size: %lu\tpData: %lu", stackelse.allocatedSize, stackelse.pData);
    struct something_else *aelse = (struct something_else *)stackelse.pData;
    union intToChar
    {
        int i;
        char c[4];
    };
    
    for(int i = 0; i < stackelse.allocatedSize / sizeof(something_else); i++)
    {
        aelse[i].a = i * 4;
        aelse[i].f = (float) i * 2.5f;
        
        intToChar buff;
        buff.i = i + (int)'a';
        strcpy(aelse[i].c, buff.c);
    }

    print_stuff(stackaint, stackchar, stackelse);

    sa.FreeStackUntil(stackchar);

    print_stuff(stackaint, stackchar, stackelse);

    bakalog("--==== Update of application ====--");
    while(running)
    {
        baka::Input::Update();

        if( baka::Input::QuitRequested() || baka::Input::KeyPressed(SDL_SCANCODE_ESCAPE) )
        {
            running = false;
        }

        // prog->Update(0.0f);
        baka::Graphics::Render();
    }

    bakalog("--==== End of application ====--");
    return 0;
}

void CloseApplication()
{
    if(prog) delete prog;
}