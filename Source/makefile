
TARGET  = pcre.library
DEST    = LIBS:

CC 	= ppc-morphos-gcc
CDEFS   = -DUSE_INLINE_STDARG
CFLAGS  = $(CDEFS) $(CWARN) -O2 -fomit-frame-pointer -mcpu=750 -mstring -mmultiple -noixemul -fstrict-aliasing -I../include/
LDFLAGS = -noixemul
CWARN   = -Wall\
  	  -Wno-missing-braces\
  	  -Wno-parentheses\
          -Wno-switch\
          -Wstrict-prototypes\
  	  -Werror-implicit-function-declaration\
          -Wpointer-arith

OBJS    = libinit.o init.o utils.o alloc.o loc.o maketables.o study.o get.o pcrerx.o pcre.o dispatch.o

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -nostartfiles -o $@ $(OBJS)
        ppc-morphos-strip --strip-unneeded --remove-section=.comment $@

install:
	@copy $(TARGET) $(DEST)
	@delete $(TARGET)
	@avail flush

libinit.o:      libinit.c lib.h pcre.library_rev.h loc.h base.h internal.h lib_protos.h macros.h config.h pcre.h
init.o:         init.c lib.h loc.h base.h internal.h lib_protos.h macros.h config.h pcre.h
utils.o:        utils.c lib.h loc.h base.h internal.h lib_protos.h macros.h config.h pcre.h
alloc.o:        alloc.c lib.h loc.h base.h internal.h lib_protos.h macros.h config.h pcre.h
pcre.o:         pcre.c lib.h internal.h loc.h base.h internal.h lib_protos.h config.h pcre.h
study.o:        study.c lib.h internal.h loc.h base.h internal.h lib_protos.h config.h pcre.h macros.h config.h pcre.h
maketables.o:   maketables.c lib.h internal.h loc.h base.h internal.h lib_protos.h config.h pcre.h macros.h config.h pcre.h
ucp.o:          ucp.c
get.o:          get.c lib.h internal.h loc.h base.h internal.h lib_protos.h config.h pcre.h macros.h config.h pcre.h
dispatch.o:     dispatch.c lib.h funlist.h loc.h base.h internal.h lib_protos.h macros.h config.h pcre.h
pcrerx.o:       pcrerx.c lib.h loc.h base.h internal.h lib_protos.h macros.h config.h pcre.h
loc.o:          loc.c lib.h loc.h base.h internal.h lib_protos.h macros.h config.h pcre.h

