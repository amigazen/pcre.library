
#include "lib.h"

/***********************************************************************/

APTR
allocVecPooled(APTR pool,ULONG size)
{
    register ULONG *mem;

    if (mem = AllocPooled(pool,size = size+sizeof(ULONG)))
        *mem++ = size;

    return mem;
}

/****************************************************************************/

void
freeVecPooled(APTR pool,APTR mem)
{
    FreePooled(pool,(LONG *)mem-1,*((LONG *)mem-1));
}

/****************************************************************************/

void *
allocArbitratePooled(size_t size)
{
    register void *mem;

    ObtainSemaphore(&lib_memSem);
    mem = AllocPooled(lib_pool,size);
    ReleaseSemaphore(&lib_memSem);

    return mem;
}

/****************************************************************************/

void
freeArbitratePooled(void *mem,size_t size)
{
    ObtainSemaphore(&lib_memSem);
    FreePooled(lib_pool,mem,size);
    ReleaseSemaphore(&lib_memSem);
}

/****************************************************************************/

void *
allocArbitrateVecPooled(size_t size)
{
    register void *mem;

    ObtainSemaphore(&lib_memSem);
    mem = allocVecPooled(lib_pool,size);
    ReleaseSemaphore(&lib_memSem);

    return mem;
}

/****************************************************************************/

void
freeArbitrateVecPooled(void *mem)
{
    ObtainSemaphore(&lib_memSem);
    freeVecPooled(lib_pool,mem);
    ReleaseSemaphore(&lib_memSem);
}

/****************************************************************************/
