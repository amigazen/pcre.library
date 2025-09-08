
#include "lib.h"

/***********************************************************************/

static LONG
setRexxVarU(struct RexxMsg *msg,STRPTR name,STRPTR val,ULONG len)
{
    REGARRAY UBYTE  buf[64];
    register STRPTR t, f;

    for (f = name, t = buf; *t = toupper(*f); t++, f++);

    return SetRexxVar(msg,buf,val,len);
}

static LONG
setRexxVarU_d(struct RexxMsg *msg,STRPTR name,LONG val)
{
    REGARRAY UBYTE  buf[64], num[32];
    register STRPTR t, f;

    for (f = name, t = buf; *t = toupper(*f); t++, f++);

    sprintf(num,"%ld",val);

    return SetRexxVar(msg,buf,num,strlen(num));
}

RXLFUN(pcrematch)
{
    pcre *re;
    int  error, erroffset, *ovec, num, i, rc, max = 0; //gcc
    LONG res;

    re = pcre_compileA(argv[0],&error,&erroffset,NULL);
    if (!re) return RXFALSE;

    if (pcre_fullinfo(re,NULL,PCRE_INFO_CAPTURECOUNT,&num)!=0)
        return RXFALSE;

    ovec = allocArbitrateVecPooled((num+1)*3*sizeof(int));
    if (!ovec) return RXFALSE;

    rc = pcre_exec(re,NULL,argv[1],strlen(argv[1]),0,0,ovec,(num+1)*3);
    if (rc>=0)
    {
        int j;

        res = RXTRUE;

        if (rc==0) max = 1;
        else max = rc;

        for (i = j = 0; i<max; i++)
        {
            char   buf[64];
            STRPTR s;
            int    l;

            sprintf(buf,"%s.%ld.FROM",(ULONG)argv[2],(ULONG)i);
            res = setRexxVarU_d(msg,buf,ovec[j++]+1);
            if (res)
            {
                res = RXFALSE;
                break;
            }

            sprintf(buf,"%s.%ld.TO",(ULONG)argv[2],(ULONG)i);
            res = setRexxVarU_d(msg,buf,ovec[j++]+1);
            if (res)
            {
                res = RXFALSE;
                break;
            }

            if ((l = pcre_get_substring(argv[1],ovec,rc,i,(const char **)&s))>0)
            {
                sprintf(buf,"%s.%ld",(ULONG)argv[2],(ULONG)i);

                res = setRexxVarU(msg,buf,s,l);
                pcre_free_substring(s);

                if (res)
                {
                    res = RXFALSE;
                    break;
                }
            }
            else
            {
                res = RXFALSE;
                break;
            }
        }
    }
    else res = RXFALSE;

    freeArbitrateVecPooled(ovec);
    pcre_free(re);

    if (res) return res;

    result->value.intVal = max;
    return TYPE_Int;
}

/***********************************************************************/
