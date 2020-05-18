# Install the pkg-config file.
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = src/libshell.pc src/shell-test.pc

DISTCLEANFILES = $(pkgconfig_DATA)
EXTRA_DIST = src/libshell.pc.in src/shell-test.pc.in

SUBDIRS = src
dist_doc_DATA = README.md
ACLOCAL_AMFLAGS = -I m4

