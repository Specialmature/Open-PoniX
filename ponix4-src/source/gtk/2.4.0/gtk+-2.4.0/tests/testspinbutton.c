#include <config.h>
#include <gtk/gtk.h>

int
main (int argc, char **argv)
{
        GtkWidget *window, *mainbox;
	int max;

        gtk_init (&argc, &argv);

        window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
        g_signal_connect (window, "delete_event", gtk_main_quit, NULL);

        mainbox = gtk_vbox_new (FALSE, 2);
        gtk_container_add (GTK_CONTAINER (window), mainbox);

	for (max = 9; max <= 999999999; max = max * 10 + 9) {
		GtkAdjustment *adj =
			GTK_ADJUSTMENT (gtk_adjustment_new (max,
							    1, max,
							    1,
							    (max + 1) / 10,
							    0.0));
     
		GtkWidget *spin = gtk_spin_button_new (adj, 1.0, 0);
		GtkWidget *hbox = gtk_hbox_new (FALSE, 2);
		
		gtk_box_pack_start (GTK_BOX (hbox),
				    spin,
				    FALSE,
				    FALSE,
				    2);

		gtk_container_add (GTK_CONTAINER (mainbox), hbox);

	}

        gtk_widget_show_all (window);

        gtk_main ();

        return 0;
}
