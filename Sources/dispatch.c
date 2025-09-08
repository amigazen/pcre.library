
#include "lib.h"
#include "funlist.h"

/****************************************************************************/

#ifdef __MORPHOS__
static functionElement * searchBin(STRPTR name)
#else
static functionElement * ASM INLINE searchBin(REG(a0) STRPTR name)
#endif
{
    register int             cond, mid, low, high;
    register functionElement *r;

    if (!strncmp(name,"RMH",3))
    {
        name++, name++, name++;
        if (*name=='_') name++;
    }

    low  = 0;
    high = sizeof(functionList)/sizeof(functionElement)-1;

    while (low<=high)
    {
        mid = (low+high)>>1;
        if (!(cond = strcmp(name,(r = functionList+mid)->name))) return r;
        else
            if (cond<0) high = mid-1;
            else low = mid+1;
    }

    return NULL;
}

/****************************************************************************/

RXLFUN(help)
{
    register functionElement *fun;

    if (fun = searchBin(*argv))
    {
        REGARRAY char h[256];

        sprintf(h,"%s/%s(%s)",(ULONG)lib_name,(ULONG)fun->name,(ULONG)fun->funHelp);

        return (result->value.argString = CreateArgstring(h,strlen(h))) ?
            TYPE_ArgString : 3;
    }

    return RXERR_NTFOUND;
}

/****************************************************************************/

static struct ARexxHelp ah = {functionList,FUNLIST_Ordered,sizeof(functionList)/sizeof(functionElement)};

RXLFUN(xwz309)
{
    result->value.addr = &ah;
    return TYPE_Addr;
}

/****************************************************************************/

#ifdef __MORPHOS__
static LONG controllArgs(STRPTR *argv,struct RexxMsg *msg,STRPTR argList)
#else
static LONG ASM INLINE controllArgs(REG(a0) STRPTR *argv,REG(a1) struct RexxMsg *msg,REG(a2) STRPTR argList)
#endif
{
    register STRPTR value;
    register BYTE   i, type, t, res, na = NUMARG(msg);

    if ((na>strlen(argList)) ||
        ((type = *(argList+na)) && (type<'Z')))
        return RXERR_WRONG_ARGS_NUM;

    for (i = 0; i<na; i++)
    {
        value = *(msg->rm_Args+i+1);

        if ((type = *(argList+i))<='Z')
        {
            if (!value) return RXERR_WRONG_ARGS_NUM;
            else type += ' ';
        }

        if (value)
        {
            switch (t = type)
            {
                case 'd':
                    break;

                case 'h':
                {
                    LONG val;

#ifdef __MORPHOS__
                    if (res = (BYTE)CVs2i(STR2RA(value),&val))
#else
                    if (res = (BYTE)CVs2i(STR2RA(value),&val,RexxSysBase))
#endif
                    {
                        register int l;

                        if ((l = GETLENGTH(value))>4) return res;
                        val = 0;
                        memcpy((UBYTE *)&val+4-l,value,l);
                    }
                    value = (STRPTR)val;

                    break;
                }

                case 'm': case 'l':
                {
                    LONG val;

#ifdef __MORPHOS__
                    if (!(res = (BYTE)CVs2i(STR2RA(value),&val)))
#else
                    if (!(res = (BYTE)CVs2i(STR2RA(value),&val,RexxSysBase)))
#endif
                        value = (STRPTR)val;
                    else if (type=='l') return (LONG)res;

                    break;
                }

                case 'o':
                    if (!*value)
                    {
                        value = NULL;
                        break;
                    }

                case 's': case 'v':
                {
                    LONG sl;

#ifdef __MORPHOS__
                    res = (UBYTE)IsSymbol(value,&sl);
#else
                    res = (UBYTE)IsSymbol(value,&sl,RexxSysBase);
#endif
                    if (res<29 || res>31 || *(value+sl)) return RXERR_SYMBOL_REQUIRED;
                    if (type=='v' && GETLENGTH(value)>32) return RXERR_STRING_TOO_LONG;

                    break;
                }
            }
        }

        *(argv+i) = value;
    }

    return RXOK;
}

/****************************************************************************/

#ifdef __MORPHOS__
LONG dispatch(void)
#else
LONG ASM dispatch(REG(a0) struct RexxMsg *msg,REG(a1) STRPTR *resPtr)
#endif
{
#ifdef __MORPHOS__
    register struct RexxMsg   *msg = (struct RexxMsg *)REG_A0;
    register STRPTR 	      resPtr;
#endif
    struct resultBox          result;
    register functionElement  *fun;
    REGARRAY STRPTR           argv[MAXRMARG];
    register LONG             retCode;

    if (!RexxSysBase || !(fun = searchBin(msg->rm_Args[0])))
        return RXERR_NTFOUND;

    memset(argv,NULL,sizeof(argv));

    if (retCode = controllArgs(argv,msg,fun->argList)) return retCode;

    SetSignal(0,GETRTSIG(msg));

    retCode = (*(fun->rexxFun))(NULL,argv,msg,&result);

    switch (GETTYPE(retCode))
    {
        case TYPE_False:
#ifdef __MORPHOS__
            resPtr = CVi2arg(0);
#else
            *resPtr = CVi2arg(0,RexxSysBase);
#endif
            break;

        case TYPE_True:
#ifdef __MORPHOS__
            resPtr = CVi2arg(1);
#else
            *resPtr = CVi2arg(1,RexxSysBase);
#endif
            break;

        case TYPE_MsgErr:
            if ((retCode>0) && (retCode<49)) return retCode;
#ifdef __MORPHOS__
            resPtr = CVi2arg(retCode);
#else
            *resPtr = CVi2arg(retCode,RexxSysBase);
#endif
            break;

        case TYPE_EmptyString:
            result.value.string = EMPTY_STRING;

        case TYPE_StaticString:
#ifdef __MORPHOS__
            resPtr = CreateArgstring(result.value.string,strlen(result.value.string));
#else
            *resPtr = CreateArgstring(result.value.string,strlen(result.value.string));
#endif
            break;

        case TYPE_ArgString:
#ifdef __MORPHOS__
            resPtr = result.value.argString;
#else
            *resPtr = result.value.argString;
#endif
            break;

        case TYPE_String:
#ifdef __MORPHOS__
            resPtr = CreateArgstring(result.value.string,strlen(result.value.string));
#else
            *resPtr = CreateArgstring(result.value.string,strlen(result.value.string));
#endif
            FreeVec(result.value.string);
            break;

        case TYPE_Piccolo:
#ifdef __MORPHOS__
            resPtr = CVi2arg(GETPICCOLO(retCode));
#else
            *resPtr = CVi2arg(GETPICCOLO(retCode),RexxSysBase);
#endif
            break;

        case TYPE_Int:
#ifdef __MORPHOS__
            resPtr = CVi2arg(result.value.intVal);
#else
            *resPtr = CVi2arg(result.value.intVal,RexxSysBase);
#endif
            break;

        case TYPE_Block:
#ifdef __MORPHOS__
            resPtr = CreateArgstring(result.value.addr,result.len);
#else
            *resPtr = CreateArgstring(result.value.addr,result.len);
#endif
            FreeVec(result.value.addr);
            break;

        case TYPE_Addr:
#ifdef __MORPHOS__
            resPtr = CreateArgstring((STRPTR)&result.value.addr,4L);
#else
            *resPtr = CreateArgstring((STRPTR)&result.value.addr,4L);
#endif
            break;

#ifndef __MORPHOS__
        case TYPE_Binary:
        {
            register char buf[9];

            *resPtr = CreateArgstring(buf,stcl_h(buf,result.value.intVal));
            break;
        }
#endif

        default:
            return retCode;
    }

#ifdef __MORPHOS__
    return (REG_A0 = (ULONG)resPtr) ? RXOK : RXERR_NOMEM;
#else
    return *resPtr ? RXOK : RXERR_NOMEM;
#endif
}

/****************************************************************************/
