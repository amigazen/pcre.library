#ifndef _PPCINLINE_PCRE_H
#define _PPCINLINE_PCRE_H

#ifndef CLIB_PCRE_PROTOS_H
#define CLIB_PCRE_PROTOS_H
#endif

#ifndef __PPCINLINE_MACROS_H
#include <ppcinline/macros.h>
#endif

#ifndef  LIBRARIES_PCRE_H
#include <libraries/pcre.h>
#endif

#ifndef PCRE_BASE_NAME
#define PCRE_BASE_NAME PCREBase
#endif

#define PCREVersion() \
	LP0(0x24, const char *, PCREVersion, \
	, PCRE_BASE_NAME, 0, 0, 0, 0, 0, 0)

#define PCRECompileA(patt, err, errofs, attrs) \
	LP4(0x2a, pcre *, PCRECompileA, const char *, patt, a0, int *, err, a1, int *, errofs, a2, struct TagItem *, attrs, a3, \
	, PCRE_BASE_NAME, 0, 0, 0, 0, 0, 0)

#ifndef NO_PPCINLINE_STDARG
#define PCRECompile(patt, err, errofs, tags...) \
	({ULONG _tags[] = {tags}; PCRECompileA((patt), (err), (errofs), (struct TagItem *) _tags);})
#endif

#define PCREExec(re, extra, subject, len, start, opts, ofs, ofsc) \
	LP8(0x30, int, PCREExec, const pcre *, re, a0, const pcre_extra *, extra, a1, const char *, subject, a2, int, len, d0, int, start, d1, int, opts, d2, int *, ofs, a3, int, ofsc, d3, \
	, PCRE_BASE_NAME, 0, 0, 0, 0, 0, 0)

#define PCREStudy(re, opts, err) \
	LP3(0x36, pcre_extra *, PCREStudy, const pcre *, re, a0, int, opts, d0, int *, err, a1, \
	, PCRE_BASE_NAME, 0, 0, 0, 0, 0, 0)

#define PCREInfo(re, optptr, first) \
	LP3(0x3c, int, PCREInfo, const pcre *, re, a0, int *, optptr, a1, int *, first, a2, \
	, PCRE_BASE_NAME, 0, 0, 0, 0, 0, 0)

#define PCREFullInfo(__p0, __p1, __p2, __p3) \
	LP4(0x42, int, PCREFullInfo, const pcre *, __p0, a0, const pcre_extra *, __p1, a1, int, __p2, d0, void *, __p3, a2, \
	, PCRE_BASE_NAME, 0, 0, 0, 0, 0, 0)

#define PCREConfig(what, where) \
	LP2(0x48, int, PCREConfig, int, what, d0, void *, where, a0, \
	, PCRE_BASE_NAME, 0, 0, 0, 0, 0, 0)

#define PCREGetStringNumber(code, string) \
	LP2(0x4e, int, PCREGetStringNumber, const pcre *, code, a0, const char *, string, a1, \
	, PCRE_BASE_NAME, 0, 0, 0, 0, 0, 0)

#define PCRECopySubString(subject, ovec, scount, snum, buf, size) \
	LP6(0x54, int, PCRECopySubString, const char *, subject, a0, int *, ovec, a1, int, scount, d0, int, snum, d1, char *, buf, a2, int, size, d2, \
	, PCRE_BASE_NAME, 0, 0, 0, 0, 0, 0)

#define PCREFreeSubStringList(ptr) \
	LP1NR(0x66, PCREFreeSubStringList, const char **, ptr, a0, \
	, PCRE_BASE_NAME, 0, 0, 0, 0, 0, 0)

#define PCREGetSubString(subject, ovec, scount, snum, strptr) \
	LP5(0x6c, int, PCREGetSubString, const char *, subject, a0, int *, ovec, a1, int, scount, d0, int, snum, d1, const char **, strptr, a2, \
	, PCRE_BASE_NAME, 0, 0, 0, 0, 0, 0)

#define PCREGetNamedSubString(code, subject, ovec, scount, sname, sptr) \
	LP6(0x72, int, PCREGetNamedSubString, const pcre *, code, a0, const char *, subject, a1, int *, ovec, a2, int, scount, d0, const char *, sname, a3, const char **, sptr, d1, \
	, PCRE_BASE_NAME, 0, 0, 0, 0, 0, 0)

#define PCREFreeSubString(ptr) \
	LP1NR(0x78, PCREFreeSubString, const char *, ptr, a0, \
	, PCRE_BASE_NAME, 0, 0, 0, 0, 0, 0)

#define PCREFree(re) \
	LP1NR(0x7e, PCREFree, const pcre *, re, a0, \
	, PCRE_BASE_NAME, 0, 0, 0, 0, 0, 0)

#define PCREGetString(id) \
	LP1(0x84, STRPTR, PCREGetString, ULONG, id, d0, \
	, PCRE_BASE_NAME, 0, 0, 0, 0, 0, 0)

#endif /*  _PPCINLINE_PCRE_H  */
