include $(top_srcdir)/ezfork/src/Makefile-LIBADD.inc
LIBSHELL_LIBADD  = ../ezfork/src/.libs/libezfork.la $(LIBEZFORK_LIBADD)

include $(top_srcdir)/restart/src/Makefile-LIBADD.inc
LIBSHELL_LIBADD += ../restart/src/.libs/librestart.la $(LIBRESTART_LIBADD)

include $(top_srcdir)/MultiMalloc/src/Makefile-LIBADD.inc
LIBSHELL_LIBADD += ../MultiMalloc/src/.libs/libmmalloc.la $(LIBMMALLOC_LIBADD)
