/* ************************************************************************ *
 * gtkcalendarentry.c - Source to generate GtkCalendarEntry widget          $
 * $Id::                                                                    $
 * ************************************************************************ */

#include <stdlib.h>
#include <string.h>
#include <glib/gprintf.h>
#include "gtkcalendarentry.h"
#include <time.h>

static void gtk_calendar_entry_init (GtkCalendarEntry *vbx);
static void set_calendar_from_entries (GtkCalendarEntry *self);
static GtkWidget *build_entry (GtkBox *box, guint size, /*gchar *name,*/ gchar *lbl, GtkCalendarEntry *);

/*enum {
    LAST_SIGNAL
};

static guint gtk_calendar_entry_signals[LAST_SIGNAL] = { 0 };*/

static void
gtk_calendar_entry_class_init (GtkCalendarEntryClass *klass)
{
}

GType
gtk_calendar_entry_get_type (void)
{
    static GType gce_type = 0;

    if ( ! gce_type)
    {
        static const GTypeInfo gce_info =
        {
            sizeof (GtkCalendarEntryClass),
            NULL,   /* base_init */
            NULL,   /* base_finalize */
            (GClassInitFunc) gtk_calendar_entry_class_init,
            NULL,   /* class_finalize */
            NULL,   /* class_data */
            sizeof (GtkCalendarEntry),
            0,
            (GInstanceInitFunc) gtk_calendar_entry_init,
        };

        gce_type = g_type_register_static (GTK_TYPE_BOX, "GtkCalendarEntry",
                &gce_info, 0);
    }

    return gce_type;
}

static void
chk_ent_max (GtkWidget *fld, GtkCalendarEntry *self)
{
    if (strlen (gtk_entry_get_text (GTK_ENTRY(fld))) >=
                gtk_entry_get_max_length (GTK_ENTRY(fld)))
    {
        g_signal_emit_by_name (G_OBJECT(gtk_widget_get_toplevel (fld)),
                               "move-focus", GTK_DIR_TAB_FORWARD, NULL);
    }
}

static GtkWidget *
build_entry (GtkBox *box, guint size, /*gchar *name,*/ gchar *lbl, GtkCalendarEntry *self)
{
    GtkWidget *entry;
    GtkBox    *fld_vbx;

    fld_vbx = GTK_BOX(gtk_box_new (GTK_ORIENTATION_VERTICAL, 3));
    entry = gtk_entry_new ();
    gtk_entry_set_max_length (GTK_ENTRY(entry), size);
    gtk_entry_set_has_frame (GTK_ENTRY(entry), FALSE);
    gtk_entry_set_width_chars (GTK_ENTRY(entry), size);
    /*gtk_widget_set_name (entry, name);*/
    gtk_box_pack_start (fld_vbx, entry, FALSE, FALSE, 5);
    gtk_box_pack_start (fld_vbx, gtk_label_new (lbl), FALSE, FALSE, 5);
    gtk_box_pack_start (box, GTK_WIDGET(fld_vbx), FALSE, FALSE, 5);

    return entry;
}

/* ******************************************************************** *
 * dlg_delete_event () - Cleanup routine for delete-event on Calendar   *
 *      dialog.  Hides the dialog and emits a "Cancel" response.        *
 * ******************************************************************** */

static void
dlg_delete_event (GtkWidget *dialog, gpointer user_data)
{
    gtk_widget_hide (dialog);
    gtk_dialog_response (GTK_DIALOG(dialog), GTK_RESPONSE_CANCEL);
}

static gboolean
dlg_response ( GtkWidget *dialog, gpointer user_data)
{
    gtk_widget_hide (dialog);
    return FALSE;
}

/* ************************************************************************ *
 * gtk_calendar_entry_get_text () - Returns a formatted string representing *
 *      the date in the three entry widgets, separated by the "divider"     *
 * The returned string is created by this function, and should be freed     *
 * when no longer needed.                                                   *
 * ************************************************************************ */

gchar *
gtk_calendar_entry_get_text (GtkCalendarEntry *self)
{
    const guint orders[][3] = { {0, 1, 2}, {1, 2, 0} };
    const guint *retorder;

    switch (self->date_order)
    {
        case GTK_CALENDAR_ENTRY_MDY:
            retorder = orders[1];
            break;
        default: /* GTK_CALENDAR_ENTRY_YMD */
            retorder = orders[0];
            break;
    }

    return g_strdup_printf ("%s%c%s%c%s",
            gtk_entry_get_text (GTK_ENTRY(self->date_entry[retorder[0]])),
            self->divider,
            gtk_entry_get_text (GTK_ENTRY(self->date_entry[retorder[1]])),
            self->divider,
            gtk_entry_get_text (GTK_ENTRY(self->date_entry[retorder[2]])) );
}

void
on_date_entry_changed (GtkWidget *widg, gpointer user_data)
{
}

void
cal_fast (GtkWidget *widg, GtkCalendarEntry * self)
{
    guint mydate[3];
    const gchar *btn_name = gtk_widget_get_name (widg);

    gtk_calendar_get_date (self->calendar, &(mydate[0]),
                                           &(mydate[1]),
                                           &(mydate[2]));

    if ( ! strcmp (btn_name, "fwd5yr"))
    {
        mydate[0] += 5;
    }
    else if ( ! strcmp (btn_name, "back5yr"))
    {
        mydate[0] -= 5;
    }
    else if ( ! strcmp (btn_name, "fwd6mo"))
    {
        if ( mydate[1] < 6)
        {
            mydate[1] += 6;
        }
        else        /* We have to wrap year */
        {
            mydate[1] -= 6;
            ++mydate[0];
        }
    }   /* Finally, only "back6mo" is left */
    else if ( mydate[1] >= 6)
    {
        mydate[1] -= 6;
    }
    else    /* We need to wrap year */
    {
        mydate[1] += 6;
        --mydate[0];
    }

    gtk_calendar_select_month (self->calendar, mydate[1], mydate[0]);
}

void
run_cal (GtkWidget *btn, GtkCalendarEntry *self)
{
    gint i,
         response;

    /* Build dialog with calendar if not already done */

    if ( ! self->dlg)
    {
        GtkWidget * fast_hbx,
                  * tmpwidget;
        GtkBox    * tmp_hbx;

        self->dlg = gtk_dialog_new_with_buttons ("Ex-Calendar",
                                        NULL,   /* parent, don't do for now */
                                        GTK_DIALOG_MODAL |
                                            GTK_DIALOG_DESTROY_WITH_PARENT,
                                        "Cancel", GTK_RESPONSE_CANCEL,
                                        "Ok", GTK_RESPONSE_OK,
                                        NULL);
        g_signal_connect (self->dlg, "delete-event",
                          G_CALLBACK(dlg_delete_event),
                          NULL);
        g_signal_connect (self->dlg, "response",
                          G_CALLBACK(dlg_response), NULL);

        //gtk_box_set_spacing (gtk_dialog_get_content_area (self->dlg, 5));

        /* Now the calendar */

        self->calendar = GTK_CALENDAR(gtk_calendar_new ());
        gtk_box_pack_start (GTK_BOX(gtk_dialog_get_content_area(
                        GTK_DIALOG(self->dlg))),
                GTK_WIDGET(self->calendar), FALSE, FALSE, 5);
        gtk_widget_show GTK_WIDGET(self->calendar);

        /* Set date in calendar here */

        /* Fast-move buttons */

        fast_hbx = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 5);

        tmpwidget = gtk_button_new_with_label ("- 5 Yr");
        gtk_button_set_image (GTK_BUTTON(tmpwidget),
                            gtk_image_new_from_icon_name ("media-rewind",
                                                      GTK_ICON_SIZE_BUTTON));
        gtk_widget_set_name (tmpwidget, "back5yr");
        g_signal_connect (tmpwidget, "clicked", G_CALLBACK(cal_fast), self);
        gtk_box_pack_start (GTK_BOX(fast_hbx), tmpwidget, FALSE, FALSE, 5);

        tmpwidget = gtk_button_new_with_label ("- 6 Mo");
        gtk_button_set_image (GTK_BUTTON(tmpwidget),
                gtk_image_new_from_icon_name("go-back", GTK_ICON_SIZE_BUTTON));
        gtk_widget_set_name (tmpwidget, "back6mo");
        g_signal_connect (tmpwidget, "clicked", G_CALLBACK(cal_fast), self);
        gtk_box_pack_start (GTK_BOX(fast_hbx), tmpwidget, FALSE, FALSE, 5);

        /* We manually add the decorations to the next two buttons in order
         * to get the image to come after the label.  We tried creating the
         * buttons and then calling reorder_child on the hbox, but it didn't
         * work */

        tmpwidget = gtk_button_new ();
        gtk_widget_set_name (tmpwidget, "fwd5yr");
        tmp_hbx = GTK_BOX(gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 10));
        gtk_box_pack_start (GTK_BOX(tmp_hbx), gtk_label_new ("* 5 Yr"),
                            FALSE, FALSE, 5);
        gtk_box_pack_end (GTK_BOX(tmp_hbx),
                            gtk_image_new_from_icon_name ("go-forward",
                                GTK_ICON_SIZE_BUTTON), FALSE, FALSE, 5);
        gtk_container_add (GTK_CONTAINER(tmpwidget), GTK_WIDGET(tmp_hbx));
        g_signal_connect (tmpwidget, "clicked", G_CALLBACK(cal_fast), self);
        gtk_box_pack_end (GTK_BOX(fast_hbx), tmpwidget, FALSE, FALSE, 5);

        tmpwidget = gtk_button_new ();
        gtk_widget_set_name (tmpwidget, "fwd6mo");
        tmp_hbx = GTK_BOX(gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 5));
        gtk_box_pack_start (GTK_BOX(tmp_hbx), gtk_label_new ("* 6 Mo"),
                FALSE, FALSE, 5);
        gtk_box_pack_end (GTK_BOX(tmp_hbx),
                    gtk_image_new_from_icon_name("go-forward",
                        GTK_ICON_SIZE_BUTTON), FALSE, FALSE, 5);
        g_signal_connect (tmpwidget, "clicked", G_CALLBACK(cal_fast), self);
        gtk_container_add (GTK_CONTAINER(tmpwidget), GTK_WIDGET(tmp_hbx));
        gtk_box_pack_end (GTK_BOX(fast_hbx), tmpwidget, FALSE, FALSE, 5);
        gtk_box_pack_start (GTK_BOX(gtk_dialog_get_content_area(
                        GTK_DIALOG(self->dlg))), fast_hbx, FALSE, FALSE, 5);

        gtk_widget_show_all (fast_hbx);

        /* We do the following last to be sure that all is established */

        for (i = 0; i < 3; i++)
        {
            g_signal_connect (self->date_entry[i], "changed",
                            G_CALLBACK(on_date_entry_changed), NULL);
        }
    }           /* end <create dialog>    */

    /* set_calendar_from_entries needs to be done on each call,
     * since the entries may have been changed
     */

    set_calendar_from_entries (self);

    response = gtk_dialog_run (GTK_DIALOG(self->dlg));

    if ( response == GTK_RESPONSE_OK)
    {
        guint mydate[3];

        gtk_calendar_get_date (self->calendar, &(mydate[0]),
                                                    &(mydate[1]),
                                                    &(mydate[2]));

        ++mydate[1];  /* Adjust for calendar's 0-based months */
        gtk_calendar_entry_set_text_from_array (self, mydate);
    }
    /*else
    {
        return NULL;
    }*/
}

/* Instance initialization */

static void
gtk_calendar_entry_init (GtkCalendarEntry *self)
{
    guint i;
    GtkBox    * date_entry_hbx;
    GtkWidget * tmpwidget;
    gchar *lbl[] = {"Year", "Mo", "Da"};

    gtk_container_set_border_width (GTK_CONTAINER(self), 5);
    gtk_box_set_spacing (GTK_BOX(self), 5);

    date_entry_hbx = GTK_BOX(gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 5));

    /* Build 3 date entry boxes at top */

    for (i = 0; i < 3; i++)
    {
        self->date_entry[i] = build_entry (GTK_BOX(date_entry_hbx),
                                           i ? 2 : 4,
                                           lbl[i],
                                           self);
        gtk_entry_set_has_frame (GTK_ENTRY(self->date_entry[i]), TRUE);
    }

    gtk_box_pack_start (GTK_BOX(self), GTK_WIDGET(date_entry_hbx),
            FALSE, FALSE, 5);

    tmpwidget = gtk_button_new_with_label ("Use Calendar");
    g_signal_connect (tmpwidget, "clicked", G_CALLBACK(run_cal), self);
    gtk_box_pack_start (GTK_BOX(self), tmpwidget, FALSE, FALSE, 5);
    gtk_widget_show_all (GTK_WIDGET(self));

    gtk_calendar_entry_set_divider (self, '-');     /* Default field divider */
    gtk_calendar_entry_set_date_order(self, GTK_CALENDAR_ENTRY_YMD);
}

void
gtk_calendar_entry_set_date_order (GtkCalendarEntry *self, guint d_order)
{
    if ((d_order > GTK_CALENDAR_ENTRY_DATEORDER_MIN)
            && (d_order < GTK_CALENDAR_ENTRY_DATEORDER_MAX))
    {
        self->date_order = d_order;
    }
}

void
gtk_calendar_entry_set_divider (GtkCalendarEntry *self, gchar div)
{
    if (div)
    {
        self->divider = div;
    }
}

static void
set_calendar_from_entries (GtkCalendarEntry *self)
{
    gtk_calendar_select_month (self->calendar,
                atoi(gtk_entry_get_text (GTK_ENTRY(self->date_entry[1]))) - 1,
                atoi(gtk_entry_get_text (GTK_ENTRY(self->date_entry[0]))));
    gtk_calendar_select_day (self->calendar,
                atoi(gtk_entry_get_text (GTK_ENTRY(self->date_entry[2]))));
}

void
gtk_calendar_entry_set_text_from_string (GtkCalendarEntry *self,
                                            gchar *date)
{
    gchar **date_ent = g_strsplit (date, "-", 3);
    gchar **src_val;
    GtkEntry **date_pos;
    guint count;

    date_pos = (GtkEntry **)&(self->date_entry[0]);

    for ( count = 0; count < 3; count++)
    {
        if ( ! date_ent[count])
        {
            return;
        }
    }

    src_val = date_ent;

    while (*src_val)
    {
        gtk_entry_set_text (*(date_pos++), *(src_val++));
//        g_free (*(date_ent++));
    }

    g_strfreev (date_ent);
}

void
gtk_calendar_entry_set_text_from_array (GtkCalendarEntry *self, guint *ary)
{
    gchar datestr[20];
    guint i;

    for (i = 0; i < 3; i++)
    {
        if ( i == 0)
        {
            g_sprintf (datestr, "%04d", ary[i]);
        }
        else
        {
            g_sprintf (datestr, "%02d", ary[i]);
        }

        gtk_entry_set_text (GTK_ENTRY(self->date_entry[i]), datestr);
    }
}

GtkWidget *
gtk_calendar_entry_new (gchar *date)
{
    GtkWidget * self =  g_object_new (gtk_calendar_entry_get_type (), NULL);
    char now[20];
    gchar *set_date;
    guint i;

    if (date)
    {
        set_date = date;
    }
    else
    {
        time_t t;
        time (&t);
        struct tm  *ct = localtime (&t);

        g_sprintf (now, "%04d-%02d-%02d", ct->tm_year + 1900,
                                          ct->tm_mon + 1, ct->tm_mday);
        set_date = now;
    }


    gtk_calendar_entry_set_text_from_string (GTK_CALENDAR_ENTRY(self),
                                             set_date);

    /* We wait until now to do signal_connect on the entries so that
     * initializing these entries won't trigger them */

    for (i = 0; i < 2; i++)
    {
        g_signal_connect (GTK_CALENDAR_ENTRY(self)->date_entry[i], "changed",
                                               G_CALLBACK(chk_ent_max),
                                               self);
    }

    return self;
}

