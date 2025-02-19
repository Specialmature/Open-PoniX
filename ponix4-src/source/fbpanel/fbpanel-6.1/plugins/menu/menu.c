#include <stdlib.h>
#include <string.h>

#include <gdk-pixbuf/gdk-pixbuf.h>
#include <glib.h>
#include <glib/gstdio.h>

#include "panel.h"
#include "misc.h"
#include "plugin.h"
#include "bg.h"
#include "gtkbgbox.h"
#include "run.h"

//#define DEBUGPRN
#include "dbg.h"

#define MENU_DEFAULT_ICON_SIZE 22

typedef struct {
    plugin_instance plugin;
    GtkWidget *menu, *bg;
    int iconsize, paneliconsize;
    xconf *xc;
    guint tout, rtout;
    gboolean has_system_menu;
    time_t btime;
    gint icon_size;
} menu_priv;

xconf *xconf_new_from_systemmenu();
gboolean systemmenu_changed(time_t btime);
static void menu_create(plugin_instance *p); 
static void menu_destroy(menu_priv *m);
static gboolean check_system_menu(plugin_instance *p);

/* Copies original config while replacing specific entries
 * with autogenerated configs */
xconf *
menu_expand_xc(xconf *xc, menu_priv *m)
{
    xconf *nxc, *cxc, *smenu_xc;
    GSList *w;

    ENTER;
    if (!xc)
        RET(NULL);
    nxc = xconf_new(xc->name, xc->value);
    DBG("new node:%s\n", nxc->name);
    for (w = xc->sons; w; w = g_slist_next(w))
    {
        cxc = w->data;
        if (!strcmp(cxc->name, "systemmenu"))
        {
            smenu_xc = xconf_new_from_systemmenu();
            xconf_append_sons(nxc, smenu_xc);
            xconf_del(smenu_xc, FALSE);
            m->has_system_menu = TRUE;
            continue;
        }
        /* XXX: write handlers for these types */
        if (!strcmp(cxc->name, "include"))
            continue;
        xconf_append(nxc, menu_expand_xc(cxc, m));
    }
    return nxc;
}

#if 0
/* XXX: should be global service with following API
 * register_command, unregister_command, run_command
 */
static void
run_command(GtkWidget *widget, void (*cmd)(void))
{
    ENTER;
    cmd();
    RET();
}
#endif

static GtkWidget *
menu_create_separator()
{
    return gtk_separator_menu_item_new();
}

/* Creates menu item. Text and image are read from xconf. Action
 * depends on @menu. If @menu is NULL, action is to execute external
 * command. Otherwise it is to pop up @menu menu */
static GtkWidget *
menu_create_item(xconf *xc, GtkWidget *menu, menu_priv *m)
{
    gchar *name, *fname, *iname, *action, *cmd;
    GtkWidget *mi;
    
    cmd = name = fname = action = iname = NULL;
    XCG(xc, "name", &name, str);
    mi = gtk_image_menu_item_new_with_label(name ? name : "");
    gtk_container_set_border_width(GTK_CONTAINER(mi), 0);
    XCG(xc, "image", &fname, str);
    fname = expand_tilda(fname);
    XCG(xc, "icon", &iname, str);
    if (fname || iname)
    {
        GdkPixbuf *pb;
        
        if ((pb = fb_pixbuf_new(iname, fname, m->icon_size, m->icon_size,
                    FALSE)))
        {
            gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(mi),
                    gtk_image_new_from_pixbuf(pb));
            g_object_unref(G_OBJECT(pb));
        }
    }
    g_free(fname);

    if (menu)
    {
        gtk_menu_item_set_submenu(GTK_MENU_ITEM(mi), menu);
        goto done;
    }
    XCG(xc, "action", &action, str);
    if (action)
    {
        action = expand_tilda(action);

        g_signal_connect_swapped(G_OBJECT(mi), "activate",
                (GCallback)run_app, action);
        g_object_set_data_full(G_OBJECT(mi), "activate",
            action, g_free);
        goto done;
    }
    XCG(xc, "command", &cmd, str);
    if (cmd)
    {
        /* XXX: implement command API */
#if 0
        command *tmp;
        
        for (tmp = commands; tmp->name; tmp++)
            if (!g_ascii_strcasecmp(cmd, tmp->name))
            {
                g_signal_connect(G_OBJECT(mi), "activate",
                        (GCallback)run_command, tmp->cmd);
                goto done;
            }
#endif        
    }
   
done:
    return mi;
}

/* Creates menu and optionally button to pop it up.
 * If @ret_menu is TRUE, then a menu is returned. Otherwise,
 * button is created, linked to a menu and returned instead. */
static GtkWidget *
menu_create_menu(xconf *xc, gboolean ret_menu, menu_priv *m)
{
    GtkWidget *mi, *menu;
    GSList *w;
    xconf *nxc;
    
    if (!xc)
        return NULL;
    menu = gtk_menu_new ();
    gtk_container_set_border_width(GTK_CONTAINER(menu), 0);
    for (w = xc->sons; w ; w = g_slist_next(w))
    {
        nxc = w->data;
        if (!strcmp(nxc->name, "separator"))
            mi = menu_create_separator();
        else if (!strcmp(nxc->name, "item"))
            mi = menu_create_item(nxc, NULL, m);
        else if (!strcmp(nxc->name, "menu"))
            mi = menu_create_menu(nxc, FALSE, m);
        else
            continue;
        gtk_menu_shell_append(GTK_MENU_SHELL(menu), mi);
    }
    gtk_widget_show_all(menu);
    return (ret_menu) ? menu : menu_create_item(xc, menu, m);
}

static gboolean
menu_unmap(GtkWidget *menu, plugin_instance *p)
{
    ENTER;
    if (p->panel->autohide)
        ah_start(p->panel);
    RET(FALSE);
}

static void
menu_create(plugin_instance *p)
{
    menu_priv *m = (menu_priv *) p;
    
    ENTER;
    if (m->menu)
        menu_destroy(m);
    m->xc = menu_expand_xc(p->xc, m);
    m->menu = menu_create_menu(m->xc, TRUE, m);
    g_signal_connect(G_OBJECT(m->menu), "unmap", 
        G_CALLBACK(menu_unmap), p);
    m->btime = time(NULL);
    if (m->has_system_menu) 
        m->tout = g_timeout_add(30000, (GSourceFunc) check_system_menu, p);
    RET();
}

static void
menu_destroy(menu_priv *m)
{
    ENTER;
    if (m->menu) {
        gtk_widget_destroy(m->menu);
        m->menu = NULL;
        m->has_system_menu = FALSE;
    }
    if (m->tout) {
        g_source_remove(m->tout);
        m->tout = 0;
    }
    if (m->rtout) {
        g_source_remove(m->rtout);
        m->rtout = 0;
    }
    if (m->xc) {
        xconf_del(m->xc, FALSE);
        m->xc = NULL;
    }
    RET();
}

static gboolean
my_button_pressed(GtkWidget *widget, GdkEventButton *event, plugin_instance *p)
{
    menu_priv *m = (menu_priv *) p;

    ENTER;
    /* propagate Control-Button3 to the panel */
    if (event->type == GDK_BUTTON_PRESS && event->button == 3
        && event->state & GDK_CONTROL_MASK)
    {
        RET(FALSE);
    }

    if ((event->type == GDK_BUTTON_PRESS)
        && (event->x >=0 && event->x < widget->allocation.width)
        && (event->y >=0 && event->y < widget->allocation.height))
    {
        if (!m->menu)
            menu_create(p);
        if (p->panel->autohide)
            ah_stop(p->panel);
        gtk_menu_popup(GTK_MENU(m->menu),
            NULL, NULL, (GtkMenuPositionFunc)menu_pos, widget,
            event->button, event->time);
       
    }
    RET(TRUE);
}


static void
make_button(plugin_instance *p, xconf *xc)
{
    int w, h;
    menu_priv *m;
    gchar *fname, *iname;
    
    ENTER;
    m = (menu_priv *) p;
    /* XXX: this code is duplicated in every plugin.
     * Lets run it once in a panel */
    if (p->panel->orientation == GTK_ORIENTATION_HORIZONTAL)
    {
        w = -1;
        h = p->panel->max_elem_height;
    }
    else
    {
        w = p->panel->max_elem_height;
        h = -1;
    }
    fname = iname = NULL;
    XCG(xc, "image", &fname, str);
    fname = expand_tilda(fname);
    XCG(xc, "icon", &iname, str);
    if (fname || iname)
    {
        m->bg = fb_button_new(iname, fname, w, h, 0x702020, NULL);
        gtk_container_add(GTK_CONTAINER(p->pwid), m->bg);
        if (p->panel->transparent)
            gtk_bgbox_set_background(m->bg, BG_INHERIT, 0, 0);
        g_signal_connect (G_OBJECT (m->bg), "button-press-event",
            G_CALLBACK (my_button_pressed), p);
    }
    g_free(fname);
}

static gboolean
rebuild_menu(plugin_instance *p)
{
    menu_priv *m = (menu_priv *) p;
    
    ENTER;
    if (m->menu && GTK_WIDGET_MAPPED(m->menu))
        RET(TRUE);
    menu_create(p);
    m->rtout = 0;
    RET(FALSE);
}

static void
schedule_rebuild_menu(plugin_instance *p)
{
    menu_priv *m = (menu_priv *) p;
    
    ENTER;
    if (!m->rtout) {
        DBG("scheduling menu rebuild p=%p\n", p);
        m->rtout = g_timeout_add(2000, (GSourceFunc) rebuild_menu, p);
    }
    RET();

}

static gboolean
check_system_menu(plugin_instance *p)
{
    menu_priv *m = (menu_priv *) p;
    
    ENTER;
    if (systemmenu_changed(m->btime)) 
        schedule_rebuild_menu(p);
    
    RET(TRUE);
}

static int
menu_constructor(plugin_instance *p)
{
    menu_priv *m;

    ENTER;
    m = (menu_priv *) p;
    m->icon_size = MENU_DEFAULT_ICON_SIZE;
    XCG(p->xc, "iconsize", &m->icon_size, int);
    DBG("icon_size=%d\n", m->icon_size);
    make_button(p, p->xc);
    g_signal_connect_swapped(G_OBJECT(icon_theme),
        "changed", (GCallback) schedule_rebuild_menu, p);
    schedule_rebuild_menu(p);
    RET(1);
}


static void
menu_destructor(plugin_instance *p)
{
    menu_priv *m = (menu_priv *) p;

    ENTER;
    g_signal_handlers_disconnect_by_func(G_OBJECT(icon_theme),
        schedule_rebuild_menu, p);
    menu_destroy(m);
    RET();
}


static plugin_class class = {
    .count       = 0,
    .type        = "menu",
    .name        = "Menu",
    .version     = "1.0",
    .description = "Menu",
    .priv_size   = sizeof(menu_priv),

    .constructor = menu_constructor,
    .destructor  = menu_destructor,
};

static plugin_class *class_ptr = (plugin_class *) &class;
