AM_CPPFLAGS = -D__STDC_INT64__

#if USE_SUBMODULES
#SUBDIRS = ../glitter
#AM_CPPFLAGS += -I $(top_srcdir)/glitter/src
#endif

include Makefile-LIBADD.inc

lib_LTLIBRARIES = libezfork.la
include_HEADERS = ezfork.h
libezfork_la_LIBADD = $(LIBEZFORK_LIBADD)
