LIBSHELL_LIBADD  = ../ezfork/src/.libs/libezfork.la $(LIBEZFORK_LIBADD)
LIBSHELL_LIBADD += ../restart/src/.libs/librestart.la $(LIBRESTART_LIBADD)
LIBSHELL_LIBADD += ../MultiMalloc/src/.libs/libmmalloc.la $(LIBMMALLOC_LIBADD)

lib_LTLIBRARIES = libshell.la
include_HEADERS = shell.h
libshell_la_LIBADD = $(LIBSHELL_LIBADD)

bin_PROGRAMS = shell-test
shell_test_LDADD = libshell.la $(LIBSHELL_LIBADD)

AM_CPPFLAGS = -D__STDC_INT64__

SUBDIRS = ../glitter
AM_CPPFLAGS += -I ../glitter/src

SUBDIRS += ../restart
AM_CPPFLAGS += -I ../restart/src

SUBDIRS += ../ezfork
AM_CPPFLAGS += -I ../ezfork/src

SUBDIRS += ../MultiMalloc
AM_CPPFLAGS += -I ../MultiMalloc/src
