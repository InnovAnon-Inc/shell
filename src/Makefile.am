lib_LTLIBRARIES = libshell.la
libshell_la_SOURCES = shell.c
include_HEADERS = shell.h
#libshell_la_CFLAGS =
libshell_la_LIBADD = -lezfork -lrestart -lmmalloc

bin_PROGRAMS = shell-test
shell_test_SOURCES = main.c
shell_test_LDADD = libshell.la -lezfork -lrestart -lmmalloc
#shell_test_CFLAGS =

AM_CPPFLAGS = -D__STDC_INT64__
AM_CPPFLAGS += -I $(srcdir)/../glitter/src
AM_CPPFLAGS += -I $(srcdir)/../restart/src
AM_CPPFLAGS += -I $(srcdir)/../ezfork/src
AM_CPPFLAGS += -I $(srcdir)/../MultiMalloc/src
