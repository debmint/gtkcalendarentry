#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(gtkcalendarentry,0.1)
AC_CONFIG_SRCDIR([src/gtkcalendarentry.c])
AC_CONFIG_HEADER([config.h])
AM_INIT_AUTOMAKE([-Wno-portability])

# Checks for programs.
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_LIBTOOL

#
# Gobject Introspection
#
AC_CONFIG_MACRO_DIR([m4])

GTK_DOC_CHECK([1.0], [--flavour no-tmpl])
GOBJECT_INTROSPECTION_CHECK([1.40.0])

# Checks for libraries.

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_STRUCT_TM

# Checks for library functions.

AC_CONFIG_FILES([Makefile src/Makefile docs/Makefile docs/reference/Makefile])
AC_OUTPUT
