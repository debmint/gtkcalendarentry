# ###################################################################### $
# Makefile for gtkcalendarentry.                                         $
# $Id::                                                                  $
# ###################################################################### $

AM_CFLAGS = -g -Wall `pkg-config --cflags gtk+-2.0 glib-2.0`

#AM_LDFLAGS = -g -Wall -Wl,--rpath -Wl,/us/local/lib `pkg-config --libs gtk+-2.0 glib-2.0`
AM_LDFLAGS = -g -Wall `pkg-config --libs gtk+-2.0 glib-2.0`

lib_LTLIBRARIES	= libgtkcalendarentry.la
libgtkcalendarentry_la_SOURCES = gtkcalendarentry.c
include_HEADERS = gtkcalendarentry.h
