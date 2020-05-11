AM_CPPFLAGS = -D__STDC_INT64__

#if USE_SUBMODULES
#SUBDIRS = ../glitter
#AM_CPPFLAGS += -I $(top_srcdir)/glitter/src
#
#SUBDIRS += ../restart
#AM_CPPFLAGS += -I $(top_srcdir)/restart/src
#
#SUBDIRS += ../ezfork
#AM_CPPFLAGS += -I $(top_srcdir)/ezfork/src
#
#SUBDIRS += ../MultiMalloc
#AM_CPPFLAGS += -I $(top_srcdir)/MultiMalloc/src
#endif

#include Makefile-LIBADD.inc
dist_bin_SCRIPTS = libshell_config shell_test_config

lib_LTLIBRARIES = libshell.la
include_HEADERS = shell.h
libshell_la_LIBADD = $(LIBSHELL_LIBADD)

bin_PROGRAMS = shell-test
#shell_test_LDADD = libshell.la $(LIBSHELL_LIBADD)
shell_test_LDADD = $(SHELL_TEST_LIBADD)
