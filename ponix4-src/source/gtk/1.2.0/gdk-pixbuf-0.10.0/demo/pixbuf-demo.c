/* GdkPixbuf library - Scaling and compositing demo
 *
 * Copyright (C) 1999 The Free Software Foundation
 *
 * Authors: Federico Mena-Quintero <federico@gimp.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include <config.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <math.h>



#define FRAME_DELAY 50

#define BACKGROUND_NAME "background.jpg"

static const char *image_names[] = {
	"apple-red.png",
	"gnome-applets.png",
	"gnome-calendar.png",
	"gnome-foot.png",
	"gnome-gmush.png",
	"gnome-gimp.png",
	"gnome-gsame.png",
	"gnu-keys.png"
};

#define N_IMAGES (sizeof (image_names) / sizeof (image_names[0]))

/* Current frame */
static GdkPixbuf *frame;

/* Background image */
static GdkPixbuf *background;
int back_width, back_height;

/* Images */
static GdkPixbuf *images[N_IMAGES];

/* Widgets */
GtkWidget *da;



/* Loads the images for the demo and returns whether the operation succeeded */
static gboolean
load_pixbufs (void)
{
	int i;

	background = gdk_pixbuf_new_from_file (BACKGROUND_NAME);
	if (!background)
		return FALSE;

	back_width = gdk_pixbuf_get_width (background);
	back_height = gdk_pixbuf_get_height (background);

	for (i = 0; i < N_IMAGES; i++) {
		images[i] = gdk_pixbuf_new_from_file (image_names[i]);
		if (!images[i])
			return FALSE;
	}

	return TRUE;
}

/* Expose callback for the drawing area */
static gint
expose_cb (GtkWidget *widget, GdkEventExpose *event, gpointer data)
{
	guchar *pixels;
	int rowstride;

	rowstride = gdk_pixbuf_get_rowstride (frame);

	pixels = gdk_pixbuf_get_pixels (frame) + rowstride * event->area.y + event->area.x * 3;
		  
	gdk_draw_rgb_image_dithalign (widget->window,
				      widget->style->black_gc,
				      event->area.x, event->area.y,
				      event->area.width, event->area.height,
				      GDK_RGB_DITHER_NORMAL,
				      pixels, rowstride,
				      event->area.x, event->area.y);

	return TRUE;
}

#define CYCLE_LEN 60

static int frame_num;

/* Timeout handler to regenerate the frame */
static gint
timeout (gpointer data)
{
	double f;
	int i;
	double xmid, ymid;
	double radius;

	gdk_pixbuf_copy_area (background, 0, 0, back_width, back_height,
			      frame, 0, 0);

	f = (double) (frame_num % CYCLE_LEN) / CYCLE_LEN;

	xmid = back_width / 2.0;
	ymid = back_height / 2.0;

	radius = MIN (xmid, ymid) / 2.0;

	for (i = 0; i < N_IMAGES; i++) {
		double ang;
		int xpos, ypos;
		int iw, ih;
		double r;
		GdkRectangle r1, r2, dest;
		double k;

		ang = 2.0 * M_PI * (double) i / N_IMAGES - f * 2.0 * M_PI;

		iw = gdk_pixbuf_get_width (images[i]);
		ih = gdk_pixbuf_get_height (images[i]);

		r = radius + (radius / 3.0) * sin (f * 2.0 * M_PI);

		xpos = floor (xmid + r * cos (ang) - iw / 2.0 + 0.5);
		ypos = floor (ymid + r * sin (ang) - ih / 2.0 + 0.5);

		k = (i & 1) ? sin (f * 2.0 * M_PI) : cos (f * 2.0 * M_PI);
		k = 2.0 * k * k;
		k = MAX (0.25, k);

		r1.x = xpos;
		r1.y = ypos;
		r1.width = iw * k;
		r1.height = ih * k;

		r2.x = 0;
		r2.y = 0;
		r2.width = back_width;
		r2.height = back_height;

		if (gdk_rectangle_intersect (&r1, &r2, &dest))
			gdk_pixbuf_composite (images[i],
					      frame,
					      dest.x, dest.y,
					      dest.width, dest.height,
					      xpos, ypos,
					      k, k,
					      GDK_INTERP_BILINEAR,
					      ((i & 1)
					       ? MAX (127, fabs (255 * sin (f * 2.0 * M_PI)))
					       : MAX (127, fabs (255 * cos (f * 2.0 * M_PI)))));
	}

	gtk_widget_draw (da, NULL);

	frame_num++;
	return TRUE;
}

static guint timeout_id;

/* Destroy handler for the window */
static void
destroy_cb (GtkObject *object, gpointer data)
{
	gtk_timeout_remove (timeout_id);
	timeout_id = 0;

	gtk_main_quit ();
}

int
main (int argc, char **argv)
{
	GtkWidget *window;

	gtk_init (&argc, &argv);
	gdk_rgb_init ();

	if (!load_pixbufs ()) {
		g_message ("main(): Could not load all the pixbufs!");
		exit (EXIT_FAILURE);
	}

	frame = gdk_pixbuf_new (GDK_COLORSPACE_RGB, FALSE, 8, back_width, back_height);

	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_usize (window, back_width, back_height);
	gtk_window_set_policy (GTK_WINDOW (window), FALSE, FALSE, FALSE);

	gtk_signal_connect (GTK_OBJECT (window), "destroy",
			    GTK_SIGNAL_FUNC (destroy_cb), NULL);

	da = gtk_drawing_area_new ();

	gtk_signal_connect (GTK_OBJECT (da), "expose_event",
			    GTK_SIGNAL_FUNC (expose_cb), NULL);

	gtk_container_add (GTK_CONTAINER (window), da);

	timeout_id = gtk_timeout_add (FRAME_DELAY, timeout, NULL);

	gtk_widget_show_all (window);
	gtk_main ();

	return 0;
}
