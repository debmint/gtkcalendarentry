# ###################################################################### $
# Makefile for gtkcalendarentry.                                         $
# $Id::                                                                  $
# ###################################################################### $

AM_CFLAGS = -g -Wall `pkg-config --cflags gtk+-3.0`

#AM_LDFLAGS = -g -Wall -Wl,--rpath -Wl,/us/local/lib `pkg-config --libs gtk+-2.0 glib-2.0`
AM_LDFLAGS = -g -Wall `pkg-config --libs gtk+-3.0`

CLEANFILES = 
lib_LTLIBRARIES	= libgtkcalendarentry.la
libgtkcalendarentry_la_SOURCES = gtkcalendarentry.c
source_h = gtkcalendarentry.h
include_HEADERS = gtkcalendarentry.h

if HAVE_INTROSPECTION
-include $(INTROSPECTION_MAKEFILE)
INTROSPECTION_GIRS = GtkCalendar-1.0.gir
INTROSPECTION_SCANNER_ARGS = --add-include-path=$(srcdir) --warn-all

introspection_sources = $(libgtkcalendarentry_la_SOURCES)

GtkCalendar-1.0.gir: $(lib_LTLIBRARIES)
GtkCalendar_1_0_gir_INCLUDES = Gtk-3.0
GtkCalendar_1_0_gir_CFLAGS = $(IR_SCANFLAGS)
GtkCalendar_1_0_gir_LIBS = $(lib_LTLIBRARIES)
GtkCalendar_1_0_gir_FILES = $(introspection_sources) $(include_HEADERS)
GtkCalendar_1_0_gir_NAMESPACE = GtkCalendar

girdir = $(datadir)/gir-1.0
gir_DATA = $(INTROSPECTION_GIRS)

typelibdir = $(libdir)/girepository-1.0
typelib_DATA = $(INTROSPECTION_GIRS:.gir=.typelib)

CLEANFILES += $(gir_DATA) $(typelib_DATA)
endif
