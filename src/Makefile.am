AM_CPPFLAGS = -D__STDC_INT64__

lib_LTLIBRARIES =
bin_PROGRAMS    =

lib_LTLIBRARIES += libshell.la
include_HEADERS = shell.h
libshell_la_CPPFLAGS = $(GLITTER_CFLAGS) $(MMALLOC_CFLAGS) $(RESTART_CFLAGS) $(EZFORK_CFLAGS)
libshell_la_LIBADD   = $(GLITTER_LIBS)   $(MMALLOC_LIBS)   $(RESTART_LIBS)   $(EZFORK_LIBS)

bin_PROGRAMS += shell-test
shell_test_CPPFLAGS =         $(GLITTER_CFLAGS) $(MMALLOC_CFLAGS) $(RESTART_CFLAGS) $(EZFORK_CFLAGS)
shell_test_LDADD    = -lshell $(GLITTER_LIBS)   $(MMALLOC_LIBS)   $(RESTART_LIBS)   $(EZFORK_LIBS)
EXTRA_shell_test_DEPENDENCIES = libshell.la

