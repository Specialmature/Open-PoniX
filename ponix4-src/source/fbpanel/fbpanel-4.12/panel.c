

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <locale.h>
#include <string.h>
#include <signal.h>
#include <time.h>

#include "plugin.h"
#include "panel.h"
#include "misc.h"
#include "bg.h"
#include "version.h"
#include "gtkbgbox.h"

static gchar *cfgfile = NULL;
static gchar version[] = VERSION;
gchar *cprofile = "default";

int config = 0;
FbEv *fbev;
gint force_quit = 0;

//#define DEBUG
#include "dbg.h"

int log_level;

FILE *pconf; // plugin part of profile file

panel *p;
panel *the_panel;

/****************************************************
 *         panel's handlers for WM events           *
 ****************************************************/
/*
static void
panel_del_wm_strut(panel *p)
{
    XDeleteProperty(GDK_DISPLAY(), p->topxwin, a_NET_WM_STRUT);
    XDeleteProperty(GDK_DISPLAY(), p->topxwin, a_NET_WM_STRUT_PARTIAL);
}
*/


static void
panel_set_wm_strut(panel *p)
{
    gulong data[12] = { 0 };
    int i = 4;

    ENTER;
    if (!GTK_WIDGET_MAPPED (p->topgwin))
        return;
    switch (p->edge) {
    case EDGE_LEFT:
        i = 0;
        data[i] = p->aw;
        data[4 + i*2] = p->ay;
        data[5 + i*2] = p->ay + p->ah;
        if (p->autohide) data[i] = p->height_when_hidden;
        break;
    case EDGE_RIGHT:
        i = 1;
        data[i] = p->aw;
        data[4 + i*2] = p->ay;
        data[5 + i*2] = p->ay + p->ah;
        if (p->autohide) data[i] = p->height_when_hidden;
        break;
    case EDGE_TOP:
        i = 2;
        data[i] = p->ah;
        data[4 + i*2] = p->ax;
        data[5 + i*2] = p->ax + p->aw;
        if (p->autohide) data[i] = p->height_when_hidden;
        break;
    case EDGE_BOTTOM:
        i = 3;
        data[i] = p->ah;
        data[4 + i*2] = p->ax;
        data[5 + i*2] = p->ax + p->aw;
        if (p->autohide) data[i] = p->height_when_hidden;
        break;
    default:
        ERR("wrong edge %d. strut won't be set\n", p->edge);
        RET();
    }
    DBG("type %d. width %d. from %d to %d\n", i, data[i], data[4 + i*2], data[5 + i*2]);

    /* if wm supports STRUT_PARTIAL it will ignore STRUT */
    XChangeProperty(GDK_DISPLAY(), p->topxwin, a_NET_WM_STRUT_PARTIAL,
          XA_CARDINAL, 32, PropModeReplace,  (unsigned char *) data, 12);
    /* old spec, for wms that do not support STRUT_PARTIAL */
    XChangeProperty(GDK_DISPLAY(), p->topxwin, a_NET_WM_STRUT,
          XA_CARDINAL, 32, PropModeReplace,  (unsigned char *) data, 4);

    RET();
}

static void
print_wmdata(panel *p)
{
    int i;

    ENTER;
    RET();
    DBG("desktop %d/%d\n", p->curdesk, p->desknum);
    DBG("workarea\n");
    for (i = 0; i < p->wa_len/4; i++)
        DBG("(%d, %d) x (%d, %d)\n",
              p->workarea[4*i + 0],
              p->workarea[4*i + 1],
              p->workarea[4*i + 2],
              p->workarea[4*i + 3]);
    RET();
}


static GdkFilterReturn
panel_event_filter(GdkXEvent *xevent, GdkEvent *event, panel *p)
{
    Atom at;
    Window win;
    XEvent *ev = (XEvent *) xevent;

    ENTER;
    DBG("win = 0x%x\n", ev->xproperty.window);
    if (ev->type != PropertyNotify )
        RET(GDK_FILTER_CONTINUE);

    at = ev->xproperty.atom;
    win = ev->xproperty.window;
    DBG("win=%x at=%d\n", win, at);
    if (win == GDK_ROOT_WINDOW()) {
    if (at == a_NET_CLIENT_LIST) {
            DBG("A_NET_CLIENT_LIST\n");
            fb_ev_trigger(fbev, EV_CLIENT_LIST);
    } else if (at == a_NET_CURRENT_DESKTOP) {
            DBG("A_NET_CURRENT_DESKTOP\n");
            p->curdesk = get_net_current_desktop();
            fb_ev_trigger(fbev, EV_CURRENT_DESKTOP);
    } else if (at == a_NET_NUMBER_OF_DESKTOPS) {
            DBG("A_NET_NUMBER_OF_DESKTOPS\n");
            p->desknum = get_net_number_of_desktops();
            fb_ev_trigger(fbev, EV_NUMBER_OF_DESKTOPS);
    } else if (at == a_NET_DESKTOP_NAMES) {
            DBG("A_NET_DESKTOP_NAMES\n");
            fb_ev_trigger(fbev, EV_DESKTOP_NAMES);
        } else if (at == a_NET_ACTIVE_WINDOW) {
            DBG("A_NET_ACTIVE_WINDOW\n");
            fb_ev_trigger(fbev, EV_ACTIVE_WINDOW);
        }else if (at == a_NET_CLIENT_LIST_STACKING) {
            DBG("A_NET_CLIENT_LIST_STACKING\n");
            fb_ev_trigger(fbev, EV_CLIENT_LIST_STACKING);
    } else if (at == a_NET_WORKAREA) {
            DBG("A_NET_WORKAREA\n");
            p->workarea = get_xaproperty (GDK_ROOT_WINDOW(), a_NET_WORKAREA, XA_CARDINAL, &p->wa_len);
            print_wmdata(p);
        } else
            RET(GDK_FILTER_CONTINUE);
        RET(GDK_FILTER_REMOVE);
    }
    DBG("non root %x\n", win);
    RET(GDK_FILTER_CONTINUE);
}

/****************************************************
 *         panel's handlers for GTK events          *
 ****************************************************/


static gint
panel_delete_event(GtkWidget * widget, GdkEvent * event, gpointer data)
{
    ENTER;
    RET(FALSE);
}

static gint
panel_destroy_event(GtkWidget * widget, GdkEvent * event, gpointer data)
{
    //panel *p = (panel *) data;

    ENTER;
    //if (!p->self_destroy)
    gtk_main_quit();
    RET(FALSE);
}


static void
panel_realize(GtkWidget *widget, panel *p)
{
    ENTER;
    RET();

}
static gint
panel_size_req(GtkWidget *widget, GtkRequisition *req, panel *p)
{
    ENTER;
    DBG("IN req=(%d, %d)\n", req->width, req->height);
    if (p->widthtype == WIDTH_REQUEST)
        p->width = (p->orientation == ORIENT_HORIZ) ? req->width : req->height;
    if (p->heighttype == HEIGHT_REQUEST)
        p->height = (p->orientation == ORIENT_HORIZ) ? req->height : req->width;
    calculate_position(p);
    req->width  = p->aw;
    req->height = p->ah;
    DBG("OUT req=(%d, %d)\n", req->width, req->height);
    RET( TRUE );
}

static gint
panel_size_alloc(GtkWidget *widget, GtkAllocation *a, panel *p)
{
    static gint x, y;

    ENTER;
    DBG("gtk: size (%d, %d). pos (%d, %d)\n", a->width, a->height, a->x, a->y);
    DBG("our: size (%d, %d). pos (%d, %d)\n", p->aw, p->ah, p->ax, p->ay);
    if (p->widthtype == WIDTH_REQUEST)
        p->width = (p->orientation == ORIENT_HORIZ) ? a->width : a->height;
    if (p->heighttype == HEIGHT_REQUEST)
        p->height = (p->orientation == ORIENT_HORIZ) ? a->height : a->width;
    calculate_position(p);
    DBG("our: size (%d, %d). pos (%d, %d)\n", p->aw, p->ah, p->ax, p->ay);
    if (a->width == p->aw && a->height == p->ah && x == p->ax && y == p ->ay) {
        DBG("actual coords eq to preffered. just returning\n");
        RET(TRUE);
    }
    x = p->ax;
    y = p->ay;
    gtk_window_move(GTK_WINDOW(p->topgwin), p->ax, p->ay);
    DBG("moving to %d %d\n", p->ax, p->ay);
    if (p->setstrut)
        panel_set_wm_strut(p);
    RET(TRUE);
}

static  gboolean
panel_configure_event (GtkWidget *widget, GdkEventConfigure *e, panel *p)
{
    ENTER;
    if (e->width == p->cw && e->height == p->ch && e->x == p->cx && e->y == p->cy)
        RET(TRUE);
    p->cw = e->width;
    p->ch = e->height;
    p->cx = e->x;
    p->cy = e->y;
    DBG("here\n");
    if (p->transparent)
        fb_bg_notify_changed_bg(p->bg);
    DBG("here\n");
    DBG("geom: size (%d, %d). pos (%d, %d)\n", e->width, e->height, e->x, e->y);
    RET(FALSE);

}


/****************************************************
 *         panel creation                           *
 ****************************************************/
static void
make_round_corners(panel *p)
{
    GtkWidget *b1, *b2, *img;
    GtkWidget *(*box_new) (gboolean, gint);
    void (*box_pack)(GtkBox *, GtkWidget *, gboolean, gboolean, guint);
    gchar *s1, *s2;
#define IMGPREFIX  PREFIX "/share/fbpanel/images/"

    ENTER;
    if (p->edge == EDGE_TOP) {
        s1 = IMGPREFIX "top-left.xpm";
        s2 = IMGPREFIX "top-right.xpm";
    } else if (p->edge == EDGE_BOTTOM) {
        s1 = IMGPREFIX "bottom-left.xpm";
        s2 = IMGPREFIX "bottom-right.xpm";
    } else if (p->edge == EDGE_LEFT) {
        s1 = IMGPREFIX "top-left.xpm";
        s2 = IMGPREFIX "bottom-left.xpm";
    } else if (p->edge == EDGE_RIGHT) {
        s1 = IMGPREFIX "top-right.xpm";
        s2 = IMGPREFIX "bottom-right.xpm";
    } else
        RET();

    box_new = (p->orientation == ORIENT_HORIZ) ? gtk_vbox_new : gtk_hbox_new;
    b1 = box_new(0, FALSE);
    gtk_widget_show(b1);
    b2 = box_new(0, FALSE);
    gtk_widget_show(b2);

    box_pack = (p->edge == EDGE_TOP || p->edge == EDGE_LEFT) ?
        gtk_box_pack_start : gtk_box_pack_end;

    img = gtk_image_new_from_file(s1);
    gtk_widget_show(img);
    box_pack(GTK_BOX(b1), img, FALSE, FALSE, 0);
    img = gtk_image_new_from_file(s2);
    gtk_widget_show(img);
    box_pack(GTK_BOX(b2), img, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(p->lbox), b1, FALSE, FALSE, 0);
    gtk_box_pack_end(GTK_BOX(p->lbox), b2, FALSE, FALSE, 0);
    RET();
}


static gboolean
panel_leave_real(panel *p)
{
    static GdkDisplay *display;
    static int count;
    gint x, y;
    
    ENTER;
    if (!display)
        display = gdk_display_get_default();
    
    if (gdk_display_pointer_is_grabbed(display)) {
        count = 0;
        RET(TRUE);
    }
    gdk_display_get_pointer(display, NULL, &x, &y, NULL);
    if ((p->cx <= x && x <= (p->cx + p->cw))
          && (p->cy <= y && y <= (p->cy + p->ch))) {
        count = 0;
        RET(TRUE);
    }
    DBG("count=%d\n", count);
    if (count++ == 0)
        RET(TRUE);
    gtk_widget_hide(p->lbox);
    p->visible = HIDDEN;    
    p->hide_tout = 0;
    DBG("hide panel\n");
    count = 0;
    RET(FALSE);
}




static gboolean
panel_enter (GtkImage *widget, GdkEventCrossing *event, panel *p)
{
    ENTER;
    if (p->hide_tout)
        RET(FALSE);

    p->hide_tout = g_timeout_add(500, (GSourceFunc) panel_leave_real, p);
    gtk_widget_show(p->lbox);
    p->visible = VISIBLE;
    DBG("show panel\n");
    RET(TRUE);
}

static gboolean
panel_drag_motion (GtkWidget *widget, GdkDragContext *drag_context, gint x, gint y, guint time,
      panel *p)
{
    ENTER;
    panel_enter (NULL, NULL, p);
    RET(TRUE);
}


void
panel_start_gui(panel *p)
{
    Atom state[3];
    XWMHints wmhints;
    guint32 val;


    ENTER;

    // main toplevel window
    p->topgwin =  gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_container_set_border_width(GTK_CONTAINER(p->topgwin), 0);
    gtk_window_set_resizable(GTK_WINDOW(p->topgwin), FALSE);
    gtk_window_set_wmclass(GTK_WINDOW(p->topgwin), "panel", "fbpanel");
    gtk_window_set_title(GTK_WINDOW(p->topgwin), "panel");
    gtk_window_set_position(GTK_WINDOW(p->topgwin), GTK_WIN_POS_NONE);
    gtk_window_set_decorated(GTK_WINDOW(p->topgwin), FALSE);
    //GTK_WIDGET_UNSET_FLAGS (p->topgwin, GTK_CAN_FOCUS);
    gtk_window_set_accept_focus(GTK_WINDOW(p->topgwin), FALSE);    
   
    g_signal_connect(G_OBJECT(p->topgwin), "delete-event",
          G_CALLBACK(panel_delete_event), p);
    g_signal_connect(G_OBJECT(p->topgwin), "destroy-event",
          G_CALLBACK(panel_destroy_event), p);
    g_signal_connect (G_OBJECT (p->topgwin), "size-request",
          (GCallback) panel_size_req, p);
    g_signal_connect (G_OBJECT (p->topgwin), "size-allocate",
          (GCallback) panel_size_alloc, p);
    g_signal_connect (G_OBJECT (p->topgwin), "configure-event",
          (GCallback) panel_configure_event, p);
    g_signal_connect (G_OBJECT (p->topgwin), "realize",
          (GCallback) panel_realize, p);
  
    gtk_widget_realize(p->topgwin);
    //gdk_window_set_decorations(p->topgwin->window, 0);
    gtk_widget_set_app_paintable(p->topgwin, TRUE);

    // background box all over toplevel
    p->bbox = gtk_bgbox_new();
    gtk_container_add(GTK_CONTAINER(p->topgwin), p->bbox);
    gtk_widget_show(p->bbox);
    gtk_container_set_border_width(GTK_CONTAINER(p->bbox), 0);
    if (p->transparent) {
        p->bg = fb_bg_get_for_display();
        gtk_bgbox_set_background(p->bbox, BG_ROOT, p->tintcolor, p->alpha);
    }

    // main layout manager as a single child of background widget box
    p->lbox = p->my_box_new(FALSE, 0);
    gtk_container_set_border_width(GTK_CONTAINER(p->lbox), 0);
    gtk_container_add(GTK_CONTAINER(p->bbox), p->lbox);
    gtk_widget_show(p->lbox);
    if (p->round_corners)
        make_round_corners(p);

    p->box = p->my_box_new(FALSE, p->spacing);
    gtk_container_set_border_width(GTK_CONTAINER(p->box), 0);
    gtk_box_pack_start(GTK_BOX(p->lbox), p->box, TRUE, TRUE, 0);
    gtk_widget_show(p->box);

    p->topxwin = GDK_WINDOW_XWINDOW(GTK_WIDGET(p->topgwin)->window);
    DBG("topxwin = %x\n", p->topxwin);

    /* the settings that should be done before window is mapped */
    wmhints.flags = InputHint;
    wmhints.input = 0;
    XSetWMHints (GDK_DISPLAY(), p->topxwin, &wmhints);
#define WIN_HINTS_SKIP_FOCUS      (1<<0)    /* "alt-tab" skips this win */
    val = WIN_HINTS_SKIP_FOCUS;
    XChangeProperty(GDK_DISPLAY(), p->topxwin,
          XInternAtom(GDK_DISPLAY(), "_WIN_HINTS", False), XA_CARDINAL, 32,
          PropModeReplace, (unsigned char *) &val, 1);

    if (p->setdocktype) {
        state[0] = a_NET_WM_WINDOW_TYPE_DOCK;
        XChangeProperty(GDK_DISPLAY(), p->topxwin, a_NET_WM_WINDOW_TYPE, XA_ATOM,
              32, PropModeReplace, (unsigned char *) state, 1);
    }

    /* window mapping point */
    gtk_widget_show_all(p->topgwin);

    /* the settings that should be done after window is mapped */

    /* send it to running wm */
    Xclimsg(p->topxwin, a_NET_WM_DESKTOP, 0xFFFFFFFF, 0, 0, 0, 0);
    /* and assign it ourself just for case when wm is not running */
    val = 0xFFFFFFFF;
    XChangeProperty(GDK_DISPLAY(), p->topxwin, a_NET_WM_DESKTOP, XA_CARDINAL, 32,
          PropModeReplace, (unsigned char *) &val, 1);

    state[0] = a_NET_WM_STATE_SKIP_PAGER;
    state[1] = a_NET_WM_STATE_SKIP_TASKBAR;
    state[2] = a_NET_WM_STATE_STICKY;
    XChangeProperty(GDK_DISPLAY(), p->topxwin, a_NET_WM_STATE, XA_ATOM,
          32, PropModeReplace, (unsigned char *) state, 3);

    XSelectInput (GDK_DISPLAY(), GDK_ROOT_WINDOW(), PropertyChangeMask);
    gdk_window_add_filter(gdk_get_default_root_window (), (GdkFilterFunc)panel_event_filter, p);



    if (p->autohide) {
        gtk_widget_add_events(p->topgwin, GDK_ENTER_NOTIFY_MASK | GDK_LEAVE_NOTIFY_MASK);
        g_signal_connect(G_OBJECT (p->topgwin), "enter-notify-event",
              G_CALLBACK (panel_enter), p);    
        g_signal_connect (G_OBJECT (p->topgwin), "drag-motion",
          (GCallback) panel_drag_motion, p);
        gtk_drag_dest_set (p->topgwin, GTK_DEST_DEFAULT_MOTION, 
              NULL, 0, 0);
        gtk_drag_dest_set_track_motion(p->topgwin, TRUE);

        if (p->edge == EDGE_BOTTOM) {
            p->ah_dx = 0;
            p->ah_dy = p->ah - p->height_when_hidden;
        } else if (p->edge == EDGE_TOP) {
            p->ah_dx = 0;
            p->ah_dy = - (p->ah - p->height_when_hidden);
        } else if (p->edge == EDGE_LEFT) {
            p->ah_dx = p->aw - p->height_when_hidden;
            p->ah_dy = 0;
        } else if (p->edge == EDGE_RIGHT) {
            p->ah_dx = - (p->aw - p->height_when_hidden);
            p->ah_dy = 0;
        }
        
        panel_enter(NULL, NULL, p);
    }
    calculate_position(p);
    gdk_window_move_resize(p->topgwin->window, p->ax, p->ay, p->aw, p->ah);
    if (p->setstrut)
        panel_set_wm_strut(p);
    RET();
}

static int
panel_parse_global(panel *p, FILE *fp)
{
    line s;
    s.len = 256;

    ENTER;
    while (get_line(fp, &s) != LINE_NONE) {
        if (s.type == LINE_VAR) {
            if (!g_ascii_strcasecmp(s.t[0], "edge")) {
                p->edge = str2num(edge_pair, s.t[1], EDGE_NONE);
            } else if (!g_ascii_strcasecmp(s.t[0], "allign")) {
                p->allign = str2num(allign_pair, s.t[1], ALLIGN_NONE);
            } else if (!g_ascii_strcasecmp(s.t[0], "margin")) {
                p->margin = atoi(s.t[1]);
            } else if (!g_ascii_strcasecmp(s.t[0], "widthtype")) {
                p->widthtype = str2num(width_pair, s.t[1], WIDTH_NONE);
            } else if (!g_ascii_strcasecmp(s.t[0], "width")) {
                p->width = atoi(s.t[1]);
            } else if (!g_ascii_strcasecmp(s.t[0], "heighttype")) {
                p->heighttype = str2num(height_pair, s.t[1], HEIGHT_NONE);
            } else if (!g_ascii_strcasecmp(s.t[0], "height")) {
                p->height = atoi(s.t[1]);
            } else if (!g_ascii_strcasecmp(s.t[0], "spacing")) {
                p->spacing = atoi(s.t[1]);
            } else if (!g_ascii_strcasecmp(s.t[0], "SetDockType")) {
                p->setdocktype = str2num(bool_pair, s.t[1], 0);
            } else if (!g_ascii_strcasecmp(s.t[0], "SetPartialStrut")) {
                p->setstrut = str2num(bool_pair, s.t[1], 0);
            } else if (!g_ascii_strcasecmp(s.t[0], "RoundCorners")) {
                p->round_corners = str2num(bool_pair, s.t[1], 0);
            } else if (!g_ascii_strcasecmp(s.t[0], "autohide")) {
                p->autohide = str2num(bool_pair, s.t[1], 0);
            } else if (!g_ascii_strcasecmp(s.t[0], "heightWhenHidden")) {
                p->height_when_hidden = atoi(s.t[1]);                
            } else if (!g_ascii_strcasecmp(s.t[0], "Transparent")) {
                p->transparent = str2num(bool_pair, s.t[1], 0);
            } else if (!g_ascii_strcasecmp(s.t[0], "Alpha")) {
                p->alpha = atoi(s.t[1]);
                if (p->alpha > 255)
                    p->alpha = 255;
            } else if (!g_ascii_strcasecmp(s.t[0], "TintColor")) {
                if (!gdk_color_parse (s.t[1], &p->gtintcolor))
                    gdk_color_parse ("white", &p->gtintcolor);
                p->tintcolor = gcolor2rgb24(&p->gtintcolor);
                DBG("tintcolor=%x\n", p->tintcolor);
            } else {
                ERR( "fbpanel: %s - unknown var in Global section\n", s.t[0]);
                RET(0);
            }
        } else if (s.type == LINE_BLOCK_END) {
            break;
        } else {
            ERR( "fbpanel: illegal in this context %s\n", s.str);
            RET(0);
        }
    }
    p->orientation = (p->edge == EDGE_TOP || p->edge == EDGE_BOTTOM)
        ? ORIENT_HORIZ : ORIENT_VERT;
    if (p->orientation == ORIENT_HORIZ) {
        p->my_box_new = gtk_hbox_new;
        p->my_separator_new = gtk_vseparator_new;
    } else {
        p->my_box_new = gtk_vbox_new;
        p->my_separator_new = gtk_hseparator_new;
    }
    if (p->width < 0)
        p->width = 100;
    if (p->widthtype == WIDTH_PERCENT && p->width > 100)
        p->width = 100;
    p->heighttype = HEIGHT_PIXEL;
    if (p->heighttype == HEIGHT_PIXEL) {
        if (p->height < PANEL_HEIGHT_MIN)
            p->height = PANEL_HEIGHT_MIN;
        else if (p->height > PANEL_HEIGHT_MAX)
            p->height = PANEL_HEIGHT_MAX;
    }
    p->curdesk = get_net_current_desktop();
    p->desknum = get_net_number_of_desktops();
    p->workarea = get_xaproperty (GDK_ROOT_WINDOW(), a_NET_WORKAREA, XA_CARDINAL, &p->wa_len);
    print_wmdata(p);
    panel_start_gui(p);
    RET(1);
}

static int
panel_parse_plugin(panel *p, FILE *fp)
{
    line s;
    plugin *plug = NULL;
    gchar *type = NULL;
    FILE *tmpfp;
    int expand , padding, border;

    ENTER;
    s.len = 256;
    if (!(tmpfp = tmpfile())) {
        ERR( "can't open temporary file with tmpfile()\n");
        RET(0);
    }
    border = expand = padding = 0;
    while (get_line(fp, &s) != LINE_BLOCK_END) {
        if (s.type == LINE_NONE) {
            ERR( "fbpanel: bad line %s\n", s.str);
            goto error;
        }
        if (s.type == LINE_VAR) {
            if (!g_ascii_strcasecmp(s.t[0], "type")) {
                type = g_strdup(s.t[1]);
                DBG("plug %s\n", type);
            } else if (!g_ascii_strcasecmp(s.t[0], "expand"))
                expand = str2num(bool_pair,  s.t[1], 0);
            else if (!g_ascii_strcasecmp(s.t[0], "padding"))
                padding = atoi(s.t[1]);
            else if (!g_ascii_strcasecmp(s.t[0], "border"))
                border = atoi(s.t[1]);
            else {
                ERR( "fbpanel: unknown var %s\n", s.t[0]);
                goto error;
            }
        } else if (s.type == LINE_BLOCK_START) {
            if (!g_ascii_strcasecmp(s.t[0], "Config")) {
                int pno = 1;
                while (pno) {
                    get_line_as_is(fp, &s);
                    if (s.type == LINE_NONE) {
                        ERR( "fbpanel: unexpected eof\n");
                        goto error;
                    } else if (s.type == LINE_BLOCK_START) {
                        pno++;
                    } else if (s.type == LINE_BLOCK_END) {
                        pno--;
                    }
                    fprintf(tmpfp, "%s\n", s.str);
                }
            } else {
                ERR( "fbpanel: unknown block %s\n", s.t[0]);
                goto error;
            }
        } else {
            ERR( "fbpanel: illegal in this context %s\n", s.str);
            goto error;
        }
    }

    if (!type || !(plug = plugin_load(type))) {
        ERR( "fbpanel: can't load %s plugin\n", type);
        goto error;
    }
    plug->panel = p;
    plug->fp = tmpfp;
    plug->expand = expand;
    plug->padding = padding;
    plug->border = border;
    fprintf(tmpfp, "}\n");
    fseek(tmpfp, 0, SEEK_SET);
    DBG("starting\n");
    if (!plugin_start(plug)) {
        ERR( "fbpanel: can't start plugin %s\n", type);
        goto error;
    }
    DBG("plug %s\n", type);
    p->plugins = g_list_append(p->plugins, plug);
    g_free(type);
    RET(1);

 error:
    fclose(tmpfp);
    g_free(type);
    if (plug)
          plugin_put(plug);
    RET(0);

}


int
panel_start(panel *p, FILE *fp)
{
    line s;
    long pos;

    /* parse global section */
    ENTER;
    s.len = 256;
    memset(p, 0, sizeof(panel));
    p->allign = ALLIGN_CENTER;
    p->edge = EDGE_BOTTOM;
    p->widthtype = WIDTH_PERCENT;
    p->width = 100;
    p->heighttype = HEIGHT_PIXEL;
    p->height = PANEL_HEIGHT_DEFAULT;
    p->setdocktype = 1;
    p->setstrut = 1;
    p->round_corners = 0;
    p->autohide = 0;
    p->visible = VISIBLE;
    p->height_when_hidden = 2;
    p->transparent = 0;
    p->alpha = 127;
    p->tintcolor = 0xFFFFFFFF;
    p->spacing = 0;
    fbev = fb_ev_new();
    if ((get_line(fp, &s) != LINE_BLOCK_START) || g_ascii_strcasecmp(s.t[0], "Global")) {
        ERR( "fbpanel: config file must start from Global section\n");
        RET(0);
    }
    if (!panel_parse_global(p, fp))
        RET(0);

    if (!(pconf = tmpfile())) {
        ERR("can't open temporary file\n");
        RET(0);
    }
    pos = ftell(fp);
    while (get_line_as_is(fp, &s) != LINE_NONE)
        fprintf(pconf, "%s\n", s.str);
    fseek(fp, pos, SEEK_SET);

    while (get_line(fp, &s) != LINE_NONE) {
        if ((s.type  != LINE_BLOCK_START) || g_ascii_strcasecmp(s.t[0], "Plugin")) {
            ERR( "fbpanel: expecting Plugin section\n");
            RET(0);
        }
        if (!panel_parse_plugin(p, fp))
            RET(0);
    }
    gtk_widget_show_all(p->topgwin);
    print_wmdata(p);
    RET(1);
}

static void
delete_plugin(gpointer data, gpointer udata)
{
    ENTER;
    plugin_stop((plugin *)data);
    plugin_put((plugin *)data);
    RET();

}

void panel_stop(panel *p)
{
    ENTER;

    g_list_foreach(p->plugins, delete_plugin, NULL);
    g_list_free(p->plugins);
    p->plugins = NULL;

    XSelectInput (GDK_DISPLAY(), GDK_ROOT_WINDOW(), NoEventMask);
    gdk_window_remove_filter(gdk_get_default_root_window (), (GdkFilterFunc)panel_event_filter, p);
    gtk_widget_destroy(p->topgwin);
    g_object_unref(fbev);
    g_free(p->workarea);
    fclose(pconf);
    gdk_flush();
    XFlush(GDK_DISPLAY());
    XSync(GDK_DISPLAY(), True);
    RET();
}


void
usage()
{
    ENTER;
    printf("fbpanel %s - lightweight GTK2+ panel for UNIX desktops\n", version);
    printf("Command line options:\n");
    printf(" --help      -- print this help and exit\n");
    printf(" --version   -- print version and exit\n");
    printf(" --log <number> -- set log level 0-5. 0 - none 5 - chatty\n");
    printf(" --configure -- launch configuration utility\n");
    printf(" --profile name -- use specified profile\n");
    printf("\n");
    printf(" -h  -- same as --help\n");
    printf(" -p  -- same as --profile\n");
    printf(" -v  -- same as --version\n");
    printf(" -C  -- same as --configure\n");
    printf("\nVisit http://fbpanel.sourceforge.net/ for detailed documentation,\n\n");
}

FILE *
open_profile(gchar *profile)
{
    gchar *fname;
    FILE *fp;

    ENTER;
    LOG(LOG_INFO, "loading %s profile\n", profile);
    if (cfgfile) {
        g_free(cfgfile);
        cfgfile = NULL;
    }
    fname = g_strdup_printf("%s/.fbpanel/%s", getenv("HOME"), profile);
    fp = fopen(fname, "r");
    LOG(LOG_INFO, "   %s %s\n", fname, fp ? "ok" : "no");
    if (fp) {
        cfgfile = fname;
        RET(fp);
    }
    //ERR("Can't load %s\n", fname);
    g_free(fname);

    /* check private configuration directory */
    fname = g_strdup_printf("%s/share/fbpanel/%s", PREFIX, profile);
    fp = fopen(fname, "r");
    LOG(LOG_INFO, "   %s %s\n", fname, fp ? "ok" : "no");
    if (fp) {
        cfgfile = fname;
        RET(fp);
    }
    //ERR("Can't load %s\n", fname);
    g_free(fname);
    LOG(LOG_ERR, "Can't open '%s' profile\n", profile);
    RET(NULL);
}

void
handle_error(Display * d, XErrorEvent * ev)
{
    char buf[256];

    ENTER;
    if (log_level >= LOG_WARN) {
        XGetErrorText(GDK_DISPLAY(), ev->error_code, buf, 256);
        LOG(LOG_WARN, "fbpanel : X error: %s\n", buf);
    }
    RET();
}

static void
sig_usr(int signum)
{
    if (signum != SIGUSR1)
        return;
    gtk_main_quit();
}

int
main(int argc, char *argv[], char *env[])
{
    int i;
    void configure();
    FILE *pfp; /* current profile FP */
    GdkPixbuf* icon;
    ENTER;
#if 0
    printf("sizeof(gulong)=%d\n", sizeof(gulong));
    printf("sizeof(Atom)=%d\n", sizeof(Atom));
    printf("sizeof(Window)=%d\n", sizeof(Window));
    printf("sizeof(gboolean)=%d\n", sizeof(gboolean));
    RET(1);
#endif
    setlocale(LC_CTYPE, "");
    gtk_set_locale();
    gtk_init(&argc, &argv);
    XSetLocaleModifiers("");
    XSetErrorHandler((XErrorHandler) handle_error);
    icon = gdk_pixbuf_new_from_file(IMGPREFIX "star.png", NULL);
    if (icon) {
        gtk_window_set_default_icon(icon);
        g_object_unref(icon);
    }
    resolve_atoms();
    for (i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help")) {
            usage();
            exit(0);
        } else if (!strcmp(argv[i], "-v") || !strcmp(argv[i], "--version")) {
            printf("fbpanel %s\n", version);
            exit(0);
        } else if (!strcmp(argv[i], "--log")) {
            i++;
            if (i == argc) {
                ERR( "fbpanel: missing log level\n");
                usage();
                exit(1);
            } else {
                log_level = atoi(argv[i]);
            }
        } else if (!strcmp(argv[i], "--configure") || !strcmp(argv[i], "-C")) {
            config = 1;
        } else if (!strcmp(argv[i], "--profile") || !strcmp(argv[i], "-p")) {
            i++;
            if (i == argc) {
                ERR( "fbpanel: missing profile name\n");
                usage();
                exit(1);
            } else {
                cprofile = g_strdup(argv[i]);
            }
        } else {
            printf("fbpanel: unknown option - %s\n", argv[i]);
            usage();
            exit(1);
        }
    }

    gtk_icon_theme_append_search_path(gtk_icon_theme_get_default(),
    IMGPREFIX);
    signal(SIGUSR1, sig_usr);
    do {
        if (!(pfp = open_profile(cprofile)))
            exit(1);
        the_panel = p = g_new0(panel, 1);
        g_return_val_if_fail (p != NULL, 1);
        if (!panel_start(p, pfp)) {
            ERR( "fbpanel: can't start panel\n");
            exit(1);
        }
        fclose(pfp);
        if (config)
            configure();
        gtk_main();
        panel_stop(p);
        g_free(p);
    } while (force_quit == 0);

    exit(0);
}

