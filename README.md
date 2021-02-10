This is a widget to display a calendar as a popup - sort of.  It has a
GtkEntry in which the date can be entered, but also a button to display
a calendar that can be use in a point-and-click fashion.  It pops up in
a GtkDialog, and when closed, the date is put into the GtkEntry.

This widget is Gobject-Introspection compatible, which means that this
object can be implemented in numerous programming languages.  Languages
tested are Perl and Python.

=======================================================================

PREREQUISITES

In order to build this project you must have pkg-config, Gtk-3 development
files, GObject Introspection development files, and, to build the
documentation, gtk-doc, and autotools

INSTALLATION NOTES

Please read the file "INSTALL" for general instructions on setting up.
Below are additional instructions for initial setup.

Prior to running autoconf (or autoreconf), the command "gtkdocize" should
be run to install gtk-doc.make.  then run autoconf or autoreconf.  Finally,
run ./configure.  The option "--with-gtk-doc" must be supplied with this
command to build the gtk-doc documentation, as it is disabled by default

