/* ************************************************************************ *
 * gtkcalendarentry.h - header file for use with GtkCalendarEntry widget    $
 * $Id::                                                                    $
 * ************************************************************************ */

#ifndef _CALENDAR_ENTRY_H_
#define _CALENDAR_ENTRY_H_

#include <gtk/gtk.h>
#include <glib-object.h>

G_BEGIN_DECLS

#define GTK_TYPE_CALENDAR_ENTRY             gtk_calendar_entry_get_type ()
G_DECLARE_FINAL_TYPE(GtkCalendarEntry, gtk_calendar_entry, GTK_CALENDAR, ENTRY, GtkBox)

typedef enum
{
    GTK_CALENDAR_ENTRY_DATEORDER_MIN = 0,
    GTK_CALENDAR_ENTRY_YMD,
    GTK_CALENDAR_ENTRY_MDY,
    GTK_CALENDAR_ENTRY_DATEORDER_MAX
} GtkCalendarEntryDisplayOrder;

struct _GtkCalendarEntryClass
{
    GtkBoxClass parent_class;
};

//void       cal_fast (GtkWidget *, GtkCalendarEntry *);
//GtkBox   * mainbox (void);
//void       setentries_from_date (gchar **);
void       gtk_calendar_entry_set_date_order (GtkCalendarEntry *self,
                             guint d_order);
void       gtk_calendar_entry_set_divider (GtkCalendarEntry *self, gchar div);
gchar    * gtk_calendar_entry_get_text (GtkCalendarEntry *self);
/*void     on_date_entry_changed (GtkWidget *, gpointer);*/
GtkWidget *gtk_calendar_entry_new (gchar *date);
//void       run (void);
void       gtk_calendar_entry_set_text_from_string (GtkCalendarEntry *self, gchar *date);
void       gtk_calendar_entry_set_text_from_array (GtkCalendarEntry *self,
                                                             guint *ary);
//gchar     *get_date (void);

G_END_DECLS

#endif      /* _CALENDAR_ENTRY_H_ */
