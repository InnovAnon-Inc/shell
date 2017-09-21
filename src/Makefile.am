lib_LTLIBRARIES = libshell.la
libshell_la_SOURCES = shell.c
include_HEADERS = shell.h
#libshell_la_CFLAGS =
libshell_la_LIBADD = -lezfork -lrestart

bin_PROGRAMS = shell-test
shell_test_SOURCES = main.c
shell_test_LDADD = libshell.la -lezfork -lrestart
#shell_test_CFLAGS =

AM_CPPFLAGS = -D__STDC_INT64__
