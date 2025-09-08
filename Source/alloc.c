
#include "lib.h"
#include "internal.h"

APTR
allocMem(const pcre *re,ULONG size)
{
    register APTR mem = NULL;

    if (re && size)
    {
        if (re->hmalloc)
        {
            mem = (APTR)CallHookPkt(re->hmalloc,(APTR)size,re->pool);
        }
        else
        {
            if (re->pool)
            {
                if (re->poolSem) ObtainSemaphore(re->poolSem);
                mem = (APTR)allocVecPooled(re->pool,size);
                if (re->poolSem) ReleaseSemaphore(re->poolSem);
            }
        }
    }

    return mem;
}

void
freeMem(const pcre *re,APTR mem)
{
    if (re && mem)
    {
        if (re->hfree)
        {
            CallHookPkt(re->hfree,mem,re->pool);
        }
        else
        {
            if (re->pool)
            {
                if (re->poolSem) ObtainSemaphore(re->poolSem);
                freeVecPooled(re->pool,mem);
                if (re->poolSem) ReleaseSemaphore(re->poolSem);
            }
        }
    }
}

pcre *
allocRe(struct Hook *hmalloc,APTR pool,struct SignalSemaphore *poolSem,ULONG size)
{
    register pcre *re = NULL;

    if (size)
    {
        if (hmalloc)
        {
            re = (pcre *)CallHookPkt(hmalloc,(APTR)size,pool);
        }
        else
        {
            if (pool)
            {
                if (poolSem) ObtainSemaphore(poolSem);
                re = (pcre *)allocVecPooled(pool,size);
                if (poolSem) ReleaseSemaphore(poolSem);
            }
        }
    }

    return re;
}

void
freeRe(const pcre *re)
{
    if (re)
    {
        register APTR                   pool = re->pool;
        register struct SignalSemaphore *poolSem = re->poolSem;
        register ULONG                  freePool = re->flags & FLG_FreePool;

        if (re->hfree)
        {
            CallHookPkt(re->hfree,(APTR)re,pool);
        }
        else
        {
            if (pool)
            {
                if (poolSem) ObtainSemaphore(poolSem);
                freeVecPooled(pool,(APTR)re);
                if (poolSem) ReleaseSemaphore(poolSem);
            }
        }

        if (freePool) DeletePool(pool);
    }
}
