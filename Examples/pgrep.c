
// gcc -O4 -noixemul -nostartfiles -opgrep pgrep.c -Iinclude

#define __NOLIBBASE__

#include <proto/exec.h>
#include <proto/dos.h>
#include <proto/asyncio.h>
#include <proto/pcre.h>
#include <string.h>

/***********************************************************************/

struct grep
{
    struct Process    *this;

    BPTR              stdout;
    BPTR              stderr;

    pcre              *re;
    int               *ovec;
    int               onum;

    STRPTR            dosPattern;
    int               rec;

    int               matches;

    ULONG             flags;
};

enum
{
    FLG_CloseErr   = 1<<0,

    FLG_Case 	   = 1<<10,
    FLG_FullPath   = 1<<11,
    FLG_WholeLine  = 1<<12,
    FLG_Recursive  = 1<<13,
    FLG_FirstMatch = 1<<14,
    FLG_PrintLines = 1<<15,
    FLG_Invert     = 1<<16,
};

/***********************************************************************/

char __ver[]   = "\0$VER: pcre.library 2.0 (5.3.2005) MorphOS version - Written by alfie";
ULONG __abox__ = 1;

struct ExecBase    *SysBase     = NULL;
struct DosLibrary  *DOSBase     = NULL;
struct Library     *PCREBase    = NULL;
struct Library 	   *AsyncIOBase = NULL;

/***********************************************************************/

#define STACKSIZE    32000
#define RECSTACKSIZE 64000

#define PRG       "pgrep"
#define TEMPLATE  "PATTERN/A,FILES/M,CS=CASESENSITIVE/S,FP=FULLPATH/S,WL=WHOLELINE/S,REC=RECURSIVE/S,FM=FIRSTMATCH/S,PL=PRINTLINES/S,INV=INVERT/S"

struct args
{
    STRPTR pattern;
    STRPTR *files;

    ULONG  caseSensitive;
    ULONG  fullPath;
    ULONG  wholeLine;
    ULONG  recursive;
    ULONG  firstMatch;
    ULONG  printLines;
    ULONG  invert;
};

/***********************************************************************/

static int match(struct grep *g,struct args *args);
static ULONG checkStdin ( struct grep *g );
static ULONG check ( struct grep *g , STRPTR dirName , STRPTR fileName );
static ULONG scan ( struct grep *g , STRPTR dirName );

/***********************************************************************/

int
pgrep(void)
{
    struct grep  	    g;
    register int 	    res = 20;

    SysBase = *((struct ExecBase **)(4));
    memset(&g,0,sizeof(g));
    g.this = (struct Process *)FindTask(NULL);

    if (DOSBase = (struct DosLibrary *)OpenLibrary("dos.library",37))
    {
        struct args            args;
        register struct RDArgs *ra;

        AsyncIOBase = OpenLibrary("asyncio.lirbary",0);

        if (!(g.stdout = Output())) return 20;

        g.stderr = Open("CONSOLE:",MODE_NEWFILE);
        if (!g.stderr) g.stderr = g.stdout;
        else g.flags |= FLG_CloseErr;

        memset(&args,0,sizeof(args));

        if (ra = ReadArgs(TEMPLATE,(LONG *)&args,NULL))
        {
            ULONG 	   size;
            register ULONG wantedStack;

            if (args.caseSensitive) g.flags |= FLG_Case;
            if (args.fullPath)      g.flags |= FLG_FullPath;
            if (args.wholeLine)     g.flags |= FLG_WholeLine;
            if (args.recursive)     g.flags |= FLG_Recursive;
            if (args.firstMatch)    g.flags |= FLG_FirstMatch;
            if (args.printLines)    g.flags |= FLG_PrintLines;
            if (args.invert)        g.flags |= FLG_Invert;

	    NewGetTaskAttrsA((struct Task *)g.this,&size,sizeof(size),TASKINFOTYPE_STACKSIZE,NULL);
	    wantedStack = (g.flags & FLG_Recursive) ? RECSTACKSIZE : STACKSIZE;

	    if (size<wantedStack)
            {
                register STRPTR stack;

		if (stack = AllocMem(wantedStack,MEMF_ANY))
                {
		    struct StackSwapStruct  swap;
		    struct PPCStackSwapArgs sargs;

	            swap.stk_Lower   = (APTR)stack;
	            swap.stk_Upper   = (ULONG)(stack+wantedStack);
	            swap.stk_Pointer = (APTR)(stack+wantedStack);

            	    sargs.Args[0] = (ULONG)&g;
            	    sargs.Args[1] = (ULONG)&args;

	    	    res = NewPPCStackSwap(&swap,&match,&sargs);

            	    FreeMem(stack,wantedStack);
                }
    		else
	        {
        	    PrintFault(IoErr(),PRG);
	        }
            }
            else
            {
       		res = match(&g,&args);
	    }

            FreeArgs(ra);
        }
        else
        {
            PrintFault(IoErr(),PRG);
            res = 10;
        }

        if (g.flags & FLG_CloseErr) Close(g.stderr);

        if (AsyncIOBase) CloseLibrary(AsyncIOBase);

        CloseLibrary((struct Library *)DOSBase);
    }
    else
    {
        g.this->pr_Result2 = ERROR_INVALID_RESIDENT_LIBRARY;
    }

    return res;
}


/***********************************************************************/

static int
match(struct grep *g,struct args *args)
{
    register int res = 20;

    if (PCREBase = OpenLibrary("pcre.library",0))
    {
        int error, erroffset;

        if (g->re = PCRECompile((STRPTR)args->pattern,&error,&erroffset,PCREA_Options,(g->flags & FLG_Case) ? 0 : PCRE_CASELESS,TAG_DONE))
        {
            if (PCREFullInfo(g->re,NULL,PCRE_INFO_CAPTURECOUNT,&g->onum)==0)
            {
                if (g->ovec = AllocVec((g->onum+1)*3*sizeof(int),MEMF_ANY*MEMF_CLEAR))
                {
                    res = 0;

                    if (args->files)
                    {
                        register STRPTR *filePtr;

                        for (filePtr = args->files; *filePtr; filePtr++)
                        {
                            char dir[256], pat[256], *file, *f;

                            if (SetSignal(0,SIGBREAKF_CTRL_C) & SIGBREAKF_CTRL_C)
                            {
                                res = 5;
                                break;
                            }

                            *dir = 0;

                            file = *filePtr;

                            if (f = PathPart(file))
                            {
                                register int m;

                                m = f-file;
                                if (m>0)
                                {
                                    if (sizeof(dir)-1<m) m = sizeof(dir)-1;
                                    strncpy(dir,file,m);
                                    dir[m] = 0;
                                }
                            }

                            f = FilePart(file);

                            if (ParsePatternNoCase(f,pat,sizeof(pat))>=0)
                            {
                                g->dosPattern = pat;
                                res = scan(g,dir);
                            }
                            else
                            {
                                FPrintf(g->stderr,"%s: can't parse \"%s\"\n",PRG,file);
                            }

                            if (res) break;
                        }
		    }
		    else
                    {
                        res = checkStdin(g);
                    }

                    if (g->matches)
                    	if (g->matches>1) FPrintf(g->stdout,"Total matches found: %ld\n",g->matches);
                    	else FPrintf(g->stdout,"One match found\n");
                    else FPrintf(g->stdout,"No match found\n");

                    FreeVec(g->ovec);
                }
                else
                {
                    FPrintf(g->stderr,"%s: not enogh memory\n",PRG);
                }
            }
            else
            {
                FPrintf(g->stderr,"%s: can't obtain re info\n",PRG);
            }

            PCREFree(g->re);
        }
        else
        {
            FPrintf(g->stderr,"%s: can't compile \"%s\": %s\n",PRG,args->pattern,PCREGetString(error));
        }

        CloseLibrary(PCREBase);
    }
    else
    {
        FPrintf(g->stderr,"%s: can't open pcre.library 0+\n",PRG);
    }

    return res;
}


static ULONG
checkStdin(struct grep *g)
{
    register BPTR  file;
    register ULONG res = 0;

    if (file = Input())
    {
        char  	       buf[256];
        register ULONG found = FALSE;
        register int   m = 0, i = 0;

        while (FGets(file,buf,sizeof(buf)-1))
        {
            register int rc, l;

            if (SetSignal(0,SIGBREAKF_CTRL_C) & SIGBREAKF_CTRL_C)
            {
                res = 5;
                break;
            }

            i++;

            rc = PCREExec(g->re,NULL,buf,l = strlen(buf),0,0,g->ovec,(g->onum+1)*3);
            if (rc>=0)
            {
                register char *b;

                if (g->flags & FLG_WholeLine)
                {
                    if (g->ovec[1]!=l) continue;
                }

                found = TRUE;
                m++;


                if ((b = strchr(buf,'\n')) || (b = strchr(buf,'\r')))
                    *b = 0;

                FPrintf(g->stdout,"%5ld:%s\n",i,buf);

                if (g->flags & FLG_FirstMatch) break;
            }
        }

        if (found)
        {
            g->matches += m;
        }
    }

    return res;
}

/***********************************************************************/

#define GETBPTR(file) (AsyncIOBase ? (((AsyncFile *)(file))->af_File) : (file))

static ULONG
check(struct grep *g,STRPTR dirName,STRPTR fileName)
{
    register BPTR  file;
    register ULONG res = 0;

    if (file = AsyncIOBase ? (BPTR)OpenAsync(fileName,MODE_READ,8192) : Open(fileName,MODE_OLDFILE))
    {
        char  	       buf[256];
        register ULONG found = FALSE;
        register int   m = 0, i = 0;

        for (;;)
        {
            register int rc, l;

            if (!(AsyncIOBase ? FGetsAsync((APTR)file,buf,sizeof(buf)-1) : FGets(file,buf,sizeof(buf)-1)))
            	break;

            if (SetSignal(0,SIGBREAKF_CTRL_C) & SIGBREAKF_CTRL_C)
            {
                res = 5;
                break;
            }

            i++;

            rc = PCREExec(g->re,NULL,buf,l = strlen(buf),0,0,g->ovec,(g->onum+1)*3);
            if (rc>=0)
            {
                if (g->flags & FLG_WholeLine)
                {
                    if (g->ovec[1]!=l) continue;
                }

                found = TRUE;
                m++;

                if (g->flags & FLG_PrintLines)
                {
                    register char *b;

                    if (m==1)
                    {
                        char fbuf[256];

                        if (g->flags & FLG_FullPath)
                        {
                            if (NameFromFH(GETBPTR(file),fbuf,sizeof(fbuf)))
                            {
                                FPrintf(g->stdout,"%s\n:",fbuf);
                            }
                        }
                        else
                        {
                            strcpy(fbuf,dirName);

                            if (AddPart(fbuf,fileName,sizeof(fbuf)))
                            {
                                FPrintf(g->stdout,"%s:\n",fbuf);
                            }
                        }
                    }

                    if ((b = strchr(buf,'\n')) || (b = strchr(buf,'\r')))
                        *b = 0;

                    FPrintf(g->stdout,"%4ld:%s\n",i,buf);
                }

                if (g->flags & FLG_FirstMatch) break;
            }
        }

        if (found)
        {
            if (!(g->flags & FLG_PrintLines))
            {
                char buf[256];

                if (g->flags & FLG_FullPath)
                {
                    if (NameFromFH(GETBPTR(file),buf,sizeof(buf)))
                    {
                        if (g->flags & FLG_FirstMatch) FPrintf(g->stdout,"%s\n",buf);
                        else FPrintf(g->stdout,"%s (%ld)\n",buf,m);
                    }
                }
                else
                {
                    strcpy(buf,dirName);

                    if (AddPart(buf,fileName,sizeof(buf)))
                    {
                        if (g->flags & FLG_FirstMatch) FPrintf(g->stdout,"%s\n",buf);
                        else FPrintf(g->stdout,"%s (%ld)\n",buf,m);
                    }
                }
            }

            g->matches += m;
        }

	if (AsyncIOBase) CloseAsync((APTR)file);
        else Close(file);
    }

    return res;
}

/***********************************************************************/

static ULONG
scan(struct grep *g,STRPTR dirName)
{
    register struct FileInfoBlock *fib;
    ULONG res = 0;

    if (fib = AllocDosObject(DOS_FIB,NULL))
    {
        register BPTR dir;

        if (dir = Lock(dirName,SHARED_LOCK))
        {
            if (Examine(dir,fib) && (fib->fib_DirEntryType>0))
            {
                register BPTR oldDir = CurrentDir(dir);

                while (ExNext(dir,fib))
                {
                    if (SetSignal(0,SIGBREAKF_CTRL_C) & SIGBREAKF_CTRL_C)
                    {
                        res = 5;
                        break;
                    }

                    if (fib->fib_DirEntryType<0)
                    {
                        if (MatchPatternNoCase(g->dosPattern,fib->fib_FileName))
                        {
                            res = check(g,dirName,fib->fib_FileName);
                            if (res) break;
                         }
                    }
                    else
                    {
                        if (g->flags & FLG_Recursive)
                        {
		            ULONG used, size;

		            NewGetTaskAttrs((struct Task *)g->this,&size,sizeof(size),TASKINFOTYPE_STACKSIZE,TAG_DONE);
		            NewGetTaskAttrs((struct Task *)g->this,&used,sizeof(used),TASKINFOTYPE_USEDSTACKSIZE,TAG_DONE);
			    if (size-used<4096) break;

                            if (res = scan(g,fib->fib_FileName)) break;
                        }
                    }
                }

                CurrentDir(oldDir);
            }
            else res = 0;

            UnLock(dir);
        }
        else res = 0;

        FreeDosObject(DOS_FIB,fib);
    }
    else res = 20;

    return res;
}

/***********************************************************************/

