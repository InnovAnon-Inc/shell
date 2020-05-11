#include $(top_srcdir)/ezfork/src/Makefile-LIBADD.inc
#include $(top_srcdir)/restart/src/Makefile-LIBADD.inc
#include $(top_srcdir)/MultiMalloc/src/Makefile-LIBADD.inc
include ../ezfork/src/Makefile-LIBADD.inc
include ../restart/src/Makefile-LIBADD.inc
include ../MultiMalloc/src/Makefile-LIBADD.inc

#if USE_SUBMODULES
#LIBSHELL_LIBADD  = ../ezfork/src/.libs/libezfork.la $(LIBEZFORK_LIBADD)
#LIBSHELL_LIBADD += ../restart/src/.libs/librestart.la $(LIBRESTART_LIBADD)
#LIBSHELL_LIBADD += ../MultiMalloc/src/.libs/libmmalloc.la $(LIBMMALLOC_LIBADD)
#else
LIBSHELL_LIBADD  = -lezfork $(LIBEZFORK_LIBADD)
LIBSHELL_LIBADD += -lrestart $(LIBRESTART_LIBADD)
LIBSHELL_LIBADD += -lmmalloc $(LIBMMALLOC_LIBADD)
#endif
