/* ************************************************************************ *
 * gtkcalendarentry.h - header file for use with GtkCalendarEntry widget    $
 * $Id::                                                                    $
 * ************************************************************************ */

#ifndef _CALENDAR_ENTRY_H_
#define _CALENDAR_ENTRY_H_

#include <glib.h>
#include <glib-object.h>
#include <glib/gstrfuncs.h>
#include <gtk/gtkcalendar.h>
#include <gtk/gtkbutton.h>
#include <gtk/gtkbox.h>
#include <gtk/gtkhbox.h>
#include <gtk/gtkvbox.h>
#include <gtk/gtklabel.h>
#include <gtk/gtkwidget.h>
#include <gtk/gtkentry.h>
#include <gtk/gtkdialog.h>

G_BEGIN_DECLS

#define GTK_TYPE_CALENDAR_ENTRY             (gtk_calendar_entry_get_type ())
#define GTK_CALENDAR_ENTRY(obj)         \
    (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_CALENDAR_ENTRY, GtkCalendarEntry))
#define GTK_CALENDAR_ENTRY_CLASS(klass)  \
    (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_CALENDAR_ENTRY, GtkCalendarEntryClass))
#define GTK_IS_CALENDAR_ENTRY(obj)       \
    (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_CALENDAR_ENTRY))
#define GTK_IS_CALENDAR_ENTRY_CLASS(klass) \
    (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_CALENDAR_ENTRY))
#define GTK_CALENDAR_ENTRY_GET_CLASS (obj)  \
    (G_TYPEINSTANCE_GET_CLASS ((obj), GTK_TYPE_CALENDAR_ENTRY, Gtk__CalendarEntryClass))

typedef struct _GtkCalendarEntry       GtkCalendarEntry;
typedef struct _GtkCalendarEntryClass  GtkCalendarEntryClass;

typedef enum
{
    GTK_CALENDAR_ENTRY_DATEORDER_MIN = 0,
    GTK_CALENDAR_ENTRY_YMD,
    GTK_CALENDAR_ENTRY_MDY,
    GTK_CALENDAR_ENTRY_DATEORDER_MAX
} GtkCalendarEntryDisplayOrder;

struct _GtkCalendarEntry
{
    GtkVBox     calendarbox;
    GtkWidget   * date_entry[3];
    GtkLabel    * dash[2];
    GtkButton   * use_cal_btn;
    GtkHBox     * fast_hbox;
    GtkButton   * back5yr;
    GtkButton   * back6mo;
    GtkButton   * fwd5yr;
    GtkButton   * fwd6mo;
    GtkWidget   * dlg;
    GtkCalendar * calendar;

    /* data variables */
    gint date_array[3];
    gchar divider;
    guint date_order;
};

struct _GtkCalendarEntryClass
{
    GtkVBoxClass parent_class;
/*    void (* gtk_calendar_entry) (GtkCalendarEntry *gce);*/
};

GType   gtk_calendar_entry_get_type  (void);
void    cal_fast (GtkWidget *, GtkCalendarEntry *);
GtkBox * mainbox (void);
void     setentries_from_date (gchar **);
void    gtk_calendar_entry_set_date_order (GtkCalendarEntry *, guint);
void    gtk_calendar_entry_set_divider (GtkCalendarEntry *, gchar);
gchar * gtk_calendar_entry_get_text (GtkCalendarEntry *);
/*void     on_date_entry_changed (GtkWidget *, gpointer);*/
GtkWidget *gtk_calendar_entry_new (gchar *date);
void       run (void);
void    gtk_calendar_entry_set_text_from_string (GtkCalendarEntry *self, gchar *date);
void    gtk_calendar_entry_set_text_from_array (GtkCalendarEntry *, guint *);
gchar     *get_date (void);

G_END_DECLS

#endif      /* _CALENDAR_ENTRY_H_ */
