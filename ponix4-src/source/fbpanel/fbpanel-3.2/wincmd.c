#include <stdlib.h>

#include <gdk-pixbuf/gdk-pixbuf.h>

#include "panel.h"
#include "misc.h"
#include "plugin.h"

//#define DEBUG
#include "dbg.h"


typedef struct {
    GdkPixmap *pix;
    GdkBitmap *mask;
    GtkTooltips *tips;
    int button1, button2;
    int action1, action2;
} wincmd;

enum { WC_NONE, WC_ICONIFY, WC_SHADE };
static pair wincmd_pair [] = {
    { WC_NONE,    "none" },
    { WC_ICONIFY, "iconify" },
    { WC_SHADE,   "shade" },
    { 0, NULL },
};



static void
toggle_shaded(wincmd *wc, unsigned long action)
{
    Window *win = NULL;
    int num, i;
    unsigned long *tmp, tmp2, dno;
    net_wm_window_type nwwt;
    
    ENTER;
    win = get_xaproperty (GDK_ROOT_WINDOW(), a_NET_CLIENT_LIST, XA_WINDOW, &num);
    if (!win)
	RET();
    if (!num)
        goto end;
    tmp = get_xaproperty (GDK_ROOT_WINDOW(), a_NET_CURRENT_DESKTOP, XA_CARDINAL, 0);
    dno = *tmp;
    DBG("wincmd: #desk=%d\n", dno);
    XFree(tmp);
    for (i = 0; i < num; i++) {
        int skip;

        tmp2 = get_net_wm_desktop(win[i]);
        DBG("wincmd: win=0x%x dno=%d...", win[i], tmp2);
        if ((tmp2 != -1) && (tmp2 != dno)) {
            DBG("skip - not cur desk\n");
            continue;
        }
        get_net_wm_window_type(win[i], &nwwt);
        skip = (nwwt.dock || nwwt.desktop || nwwt.splash);
        if (skip) {
            DBG("skip - omnipresent window type\n");
            continue;
        }
        Xclimsg(win[i], a_NET_WM_STATE,
              action ? a_NET_WM_STATE_ADD : a_NET_WM_STATE_REMOVE,
              a_NET_WM_STATE_SHADED, 0, 0, 0);
        DBG("ok\n");
    }
    
 end:
    XFree(win);
    RET();
}



static void
toggle_iconify(wincmd *wc, unsigned long action)
{
    Window *win = NULL;
    int num, i;
    unsigned long *tmp, tmp2, dno;
    net_wm_window_type nwwt;
    
    ENTER;
    win = get_xaproperty (GDK_ROOT_WINDOW(), a_NET_CLIENT_LIST, XA_WINDOW, &num);
    if (!win)
	RET();
    if (!num)
        goto end;
    tmp = get_xaproperty (GDK_ROOT_WINDOW(), a_NET_CURRENT_DESKTOP, XA_CARDINAL, 0);
    dno = *tmp;
    DBG("wincmd: #desk=%d\n", dno);
    XFree(tmp);
    for (i = 0; i < num; i++) {
        int skip;

        tmp2 = get_net_wm_desktop(win[i]);
        DBG("wincmd: win=0x%x dno=%d...", win[i], tmp2);
        if ((tmp2 != -1) && (tmp2 != dno)) {
            DBG("skip - not cur desk\n");
            continue;
        }
        get_net_wm_window_type(win[i], &nwwt);
        skip = (nwwt.dock || nwwt.desktop || nwwt.splash);
        if (skip) {
            DBG("skip - omnipresent window type\n");
            continue;
        }
        if (action)
            XIconifyWindow(GDK_DISPLAY(), win[i], DefaultScreen(GDK_DISPLAY()));
        else
            XMapWindow (GDK_DISPLAY(), win[i]);
        DBG("ok\n");
    }
    
 end:
    XFree(win);
    RET();
}

static gint
clicked (GtkWidget *widget, GdkEventButton *event, gpointer data)
{
    wincmd *wc = (wincmd *) data;

    ENTER;
    if (event->type != GDK_BUTTON_PRESS)
        RET(FALSE);

    if (event->button == 1) {
        wc->action1 = 1 - wc->action1;
        toggle_iconify(wc, wc->action1);
        DBG("wincmd: iconify all\n");
    } else if (event->button == 2) {
        wc->action2 = 1 - wc->action2;
        toggle_shaded(wc, wc->action2);
        DBG("wincmd: shade all\n");
    } else {
        DBG("wincmd: unsupported command\n");
    }
   
    RET(FALSE);
}

static void
wincmd_destructor(plugin *p)
{
    wincmd *wc = (wincmd *)p->priv;

    ENTER;
    if (wc->mask)
        g_object_unref(wc->mask);
    if (wc->pix)
        g_object_unref(wc->pix);
    //gtk_widget_destroy(wc->tips);
    g_free(wc);
    RET();
}



static int
wincmd_constructor(plugin *p)
{
    line s;
    gchar *tooltip, *fname;
    wincmd *wc;
    GdkPixbuf *gp, *gps;
    GtkWidget *button;
    GError *err = NULL;

    s.len = 256;
    ENTER;
    wc = g_new0(wincmd, 1);
    g_return_val_if_fail(wc != NULL, 0);
    wc->tips = gtk_tooltips_new();
    p->priv = wc;
    tooltip = fname = 0;
    while (get_line(p->fp, &s) != LINE_BLOCK_END) {
        if (s.type == LINE_NONE) {
            ERR( "wincmd: illegal token %s\n", s.str);
            goto error;
        }
        if (s.type == LINE_VAR) {
            if (!g_ascii_strcasecmp(s.t[0], "Button1")) 
                wc->button1 = str2num(wincmd_pair, s.t[1], WC_ICONIFY);
            else if (!g_ascii_strcasecmp(s.t[0], "Button2")) 
                wc->button2 = str2num(wincmd_pair, s.t[1], WC_SHADE);
            else if (!g_ascii_strcasecmp(s.t[0], "tooltip"))
                tooltip = g_strdup(s.t[1]);
            else if (!g_ascii_strcasecmp(s.t[0], "image"))
                fname = expand_tilda(s.t[1]); 
            else {
                ERR( "wincmd: unknown var %s\n", s.t[0]);
                goto error;
            }
        } else {
            ERR( "wincmd: illegal in this context %s\n", s.str);
            goto error;
        }
    }
    gp = gdk_pixbuf_new_from_file(fname, &err);
    if (!gp) {
        g_warning("wincmd: can't read image %s\n", fname);
        button = gtk_button_new_with_label("wc");
    } else {
        float ratio;
        GtkWidget *pixmap;
        
        ratio = (p->panel->orientation == ORIENT_HORIZ) ?
            (float) (p->panel->ah - 2) / (float) gdk_pixbuf_get_height(gp)
            : (float) (p->panel->aw - 2) / (float) gdk_pixbuf_get_width(gp);
        gps =  gdk_pixbuf_scale_simple (gp,
              ratio * ((float) gdk_pixbuf_get_width(gp)),
              ratio * ((float) gdk_pixbuf_get_height(gp)),
              GDK_INTERP_HYPER);
        button = gtk_button_new();
        pixmap = gtk_image_new_from_pixbuf(gps);
        gtk_widget_show(pixmap);
        gtk_container_add(GTK_CONTAINER(button), pixmap);
       
        gdk_pixbuf_unref(gp);
        gdk_pixbuf_unref(gps);

    }
    gtk_button_set_relief(GTK_BUTTON(button), GTK_RELIEF_NONE);
    gtk_container_set_border_width(GTK_CONTAINER(button), 1);
    g_signal_connect(G_OBJECT(button), "button_press_event",
                     G_CALLBACK(clicked), (gpointer)wc);
    gtk_widget_show(button);
    gtk_container_add(GTK_CONTAINER(p->pwid), button);
    g_free(fname);
    if (tooltip) {
        gtk_tooltips_set_tip(GTK_TOOLTIPS (wc->tips), button, tooltip, NULL);
        g_free(tooltip);
    }
    RET(1);

 error:
    g_free(fname);
    g_free(tooltip);
    wincmd_destructor(p);
    ERR( "%s - exit\n", __FUNCTION__);
    RET(0);
}


plugin_class wincmd_plugin_class = {
    fname: NULL,
    count: 0,

    type : "wincmd",
    name : "Window Commander ;-)",
    version: "1.0",
    description : "Sends commands to all desktop windows.\nSupported commnds are 1)toggle iconify and 2) toggle shade",
    

    constructor : wincmd_constructor,
    destructor  : wincmd_destructor,
};
