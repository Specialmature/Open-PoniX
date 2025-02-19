

#include <X11/Xatom.h>
#include <X11/cursorfont.h>

#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <gdk/gdkx.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "misc.h"
#include "panel.h"

//#define DEBUG
#include "dbg.h"


/* X11 data types */
Atom a_UTF8_STRING;

/* old WM spec */
Atom a_WM_STATE;
Atom a_WM_CLASS;

/* new NET spec */
Atom a_NET_WORKAREA;
Atom a_NET_CLIENT_LIST;
Atom a_NET_CLIENT_LIST_STACKING;
Atom a_NET_NUMBER_OF_DESKTOPS;
Atom a_NET_CURRENT_DESKTOP;
Atom a_NET_DESKTOP_NAMES;
Atom a_NET_ACTIVE_WINDOW;
Atom a_NET_WM_DESKTOP;
Atom a_NET_WM_STATE;
Atom a_NET_WM_STATE_SKIP_TASKBAR;
Atom a_NET_WM_STATE_SKIP_PAGER;
Atom a_NET_WM_STATE_STICKY;
Atom a_NET_WM_STATE_HIDDEN;
Atom a_NET_WM_STATE_SHADED;
Atom a_NET_WM_WINDOW_TYPE;
Atom a_NET_WM_WINDOW_TYPE_DESKTOP;
Atom a_NET_WM_WINDOW_TYPE_DOCK;
Atom a_NET_WM_WINDOW_TYPE_TOOLBAR;
Atom a_NET_WM_WINDOW_TYPE_MENU;
Atom a_NET_WM_WINDOW_TYPE_UTILITY;
Atom a_NET_WM_WINDOW_TYPE_SPLASH;
Atom a_NET_WM_WINDOW_TYPE_DIALOG;
Atom a_NET_WM_WINDOW_TYPE_NORMAL;
Atom a_NET_WM_DESKTOP;
Atom a_NET_WM_NAME;
Atom a_NET_WM_STRUT;
Atom a_NET_WM_STRUT_PARTIAL;
Atom a_KDE_NET_WM_SYSTEM_TRAY_WINDOW_FOR;

pair allign_pair[] = {
    { ALLIGN_NONE, "none" },
    { ALLIGN_LEFT, "left" },
    { ALLIGN_RIGHT, "right" },
    { ALLIGN_CENTER, "center"},
    { 0, NULL },
};

pair edge_pair[] = {
    { EDGE_NONE, "none" },
    { EDGE_LEFT, "left" },
    { EDGE_RIGHT, "right" },
    { EDGE_TOP, "top" },
    { EDGE_BOTTOM, "bottom" },
    { 0, NULL },
};

pair width_pair[] = {
    { WIDTH_NONE, "none" },
    { WIDTH_REQUEST, "request" },
    { WIDTH_PIXEL, "pixel" },
    { WIDTH_PERCENT, "percent" },
    { 0, NULL },
};

pair height_pair[] = {
    { HEIGHT_NONE, "none" },
    { HEIGHT_PIXEL, "pixel" },
    { 0, NULL },
};

pair bool_pair[] = {
    { 0, "false" },
    { 1, "true" },
    { 0, NULL },
};


int
str2num(pair *p, gchar *str, int defval)
{
    ENTER;
    for (;p && p->str; p++) {
        if (!g_ascii_strcasecmp(str, p->str))
            RET(p->num);
    }
    RET(defval);
}

gchar *
num2str(pair *p, int num, gchar *defval)
{
    ENTER;
    for (;p && p->str; p++) {
        if (num == p->num)
            RET(p->str);
    }
    RET(defval);
}

int
get_line(FILE *fp, line *s)
{
    gchar *tmp, *tmp2;

    ENTER;
    if (!fp) {
        s->type = LINE_NONE;
        RET(s->type);
    }
    s->type = LINE_NONE;
    while (fgets(s->str, s->len, fp)) {
        g_strstrip(s->str);
     
        if (s->str[0] == '#' || s->str[0] == 0) {
	    continue;
        }
        DBG( ">> %s\n", s->str);
        if (!g_ascii_strcasecmp(s->str, "}")) {
            s->type = LINE_BLOCK_END;
            break;
        }

        s->t[0] = s->str;
        for (tmp = s->str; isalnum(*tmp); tmp++);
        for (tmp2 = tmp; isspace(*tmp2); tmp2++);
        if (*tmp2 == '=') {
            for (++tmp2; isspace(*tmp2); tmp2++);
            s->t[1] = tmp2;
            *tmp = 0;
            s->type = LINE_VAR;
        } else if  (*tmp2 == '{') {
            *tmp = 0;
            s->type = LINE_BLOCK_START;
        } else {
            ERR( "parser: unknown token: '%c'\n", *tmp2);
        }
        break;
    }
    RET(s->type);

}

int
get_line_as_is(FILE *fp, line *s)
{
    gchar *tmp, *tmp2;

    ENTER;
    if (!fp) {
        s->type = LINE_NONE;
        RET(s->type);
    }
    s->type = LINE_NONE;
    while (fgets(s->str, s->len, fp)) {
        g_strstrip(s->str);
        if (s->str[0] == '#' || s->str[0] == 0) 
	    continue;
        DBG( ">> %s\n", s->str);
        if (!g_ascii_strcasecmp(s->str, "}")) {
            s->type = LINE_BLOCK_END;
            DBG( "        : line_block_end\n");
            break;
        }
        for (tmp = s->str; isalnum(*tmp); tmp++);
        for (tmp2 = tmp; isspace(*tmp2); tmp2++);
        if (*tmp2 == '=') {
            s->type = LINE_VAR;
        } else if  (*tmp2 == '{') {
            s->type = LINE_BLOCK_START;
        } else {
            DBG( "        : ? <%c>\n", *tmp2);
        }
        break;
    }
    RET(s->type);

}

void resolve_atoms()
{
    ENTER;
    
    a_UTF8_STRING                = XInternAtom(GDK_DISPLAY(), "UTF8_STRING", False);
    a_WM_STATE                   = XInternAtom(GDK_DISPLAY(), "WM_STATE", False);
    a_WM_CLASS                   = XInternAtom(GDK_DISPLAY(), "WM_CLASS", False);
    a_NET_WORKAREA               = XInternAtom(GDK_DISPLAY(), "_NET_WORKAREA", False);    
    a_NET_CLIENT_LIST            = XInternAtom(GDK_DISPLAY(), "_NET_CLIENT_LIST", False);
    a_NET_CLIENT_LIST_STACKING   = XInternAtom(GDK_DISPLAY(), "_NET_CLIENT_LIST_STACKING", False);
    a_NET_NUMBER_OF_DESKTOPS     = XInternAtom(GDK_DISPLAY(), "_NET_NUMBER_OF_DESKTOPS", False);
    a_NET_CURRENT_DESKTOP        = XInternAtom(GDK_DISPLAY(), "_NET_CURRENT_DESKTOP", False);
    a_NET_DESKTOP_NAMES          = XInternAtom(GDK_DISPLAY(), "_NET_DESKTOP_NAMES", False);
    a_NET_ACTIVE_WINDOW          = XInternAtom(GDK_DISPLAY(), "_NET_ACTIVE_WINDOW", False);
    a_NET_WM_DESKTOP             = XInternAtom(GDK_DISPLAY(), "_NET_WM_DESKTOP", False);
    a_NET_WM_STATE               = XInternAtom(GDK_DISPLAY(), "_NET_WM_STATE", False);
    a_NET_WM_STATE_SKIP_TASKBAR  = XInternAtom(GDK_DISPLAY(), "_NET_WM_STATE_SKIP_TASKBAR", False);
    a_NET_WM_STATE_SKIP_PAGER    = XInternAtom(GDK_DISPLAY(), "_NET_WM_STATE_SKIP_PAGER", False);
    a_NET_WM_STATE_STICKY        = XInternAtom(GDK_DISPLAY(), "_NET_WM_STATE_STICKY", False);
    a_NET_WM_STATE_HIDDEN        = XInternAtom(GDK_DISPLAY(), "_NET_WM_STATE_HIDDEN", False);
    a_NET_WM_STATE_SHADED        = XInternAtom(GDK_DISPLAY(), "_NET_WM_STATE_SHADED", False);
    a_NET_WM_WINDOW_TYPE         = XInternAtom(GDK_DISPLAY(), "_NET_WM_WINDOW_TYPE", False);

    a_NET_WM_WINDOW_TYPE_DESKTOP = XInternAtom(GDK_DISPLAY(), "_NET_WM_WINDOW_TYPE_DESKTOP", False);
    a_NET_WM_WINDOW_TYPE_DOCK    = XInternAtom(GDK_DISPLAY(), "_NET_WM_WINDOW_TYPE_DOCK", False);
    a_NET_WM_WINDOW_TYPE_TOOLBAR = XInternAtom(GDK_DISPLAY(), "_NET_WM_WINDOW_TYPE_TOOLBAR", False);
    a_NET_WM_WINDOW_TYPE_MENU    = XInternAtom(GDK_DISPLAY(), "_NET_WM_WINDOW_TYPE_MENU", False);
    a_NET_WM_WINDOW_TYPE_UTILITY = XInternAtom(GDK_DISPLAY(), "_NET_WM_WINDOW_TYPE_UTILITY", False);
    a_NET_WM_WINDOW_TYPE_SPLASH  = XInternAtom(GDK_DISPLAY(), "_NET_WM_WINDOW_TYPE_SPLASH", False);
    a_NET_WM_WINDOW_TYPE_DIALOG  = XInternAtom(GDK_DISPLAY(), "_NET_WM_WINDOW_TYPE_DIALOG", False);
    a_NET_WM_WINDOW_TYPE_NORMAL  = XInternAtom(GDK_DISPLAY(), "_NET_WM_WINDOW_TYPE_NORMAL", False);
    a_NET_WM_DESKTOP             = XInternAtom(GDK_DISPLAY(), "_NET_WM_DESKTOP", False);
    a_NET_WM_NAME                = XInternAtom(GDK_DISPLAY(), "_NET_WM_NAME", False);
    a_NET_WM_STRUT               = XInternAtom(GDK_DISPLAY(), "_NET_WM_STRUT", False);
    a_NET_WM_STRUT_PARTIAL       = XInternAtom(GDK_DISPLAY(), "_NET_WM_STRUT_PARTIAL", False);
    a_KDE_NET_WM_SYSTEM_TRAY_WINDOW_FOR
                                 = XInternAtom(GDK_DISPLAY(), "_KDE_NET_WM_SYSTEM_TRAY_WINDOW_FOR", False);
                                
    RET();
}


void
Xclimsg(Window win, long type, long l0, long l1, long l2, long l3, long l4)
{
    XClientMessageEvent xev;

    xev.type = ClientMessage;
    xev.window = win;
    xev.message_type = type;
    xev.format = 32;
    xev.data.l[0] = l0;
    xev.data.l[1] = l1;
    xev.data.l[2] = l2;
    xev.data.l[3] = l3;
    xev.data.l[4] = l4;
    XSendEvent(GDK_DISPLAY(), GDK_ROOT_WINDOW(), False,
          (SubstructureNotifyMask | SubstructureRedirectMask),
          (XEvent *) & xev);
}

void *
get_xaproperty (Window win, Atom prop, Atom type, int *nitems)
{
    Atom type_ret;
    int format_ret;
    unsigned long items_ret;
    unsigned long after_ret;
    unsigned char *prop_data;

    ENTER;
    prop_data = NULL;
    XGetWindowProperty (GDK_DISPLAY(), win, prop, 0, 0x7fffffff, False,
          type, &type_ret, &format_ret, &items_ret,
          &after_ret, &prop_data);    
    if (nitems)
        *nitems = items_ret;
    RET(prop_data);
}

static char*
text_property_to_utf8 (const XTextProperty *prop)
{
  char **list;
  int count;
  char *retval;
  
  ENTER;
  list = NULL;
  count = gdk_text_property_to_utf8_list (gdk_x11_xatom_to_atom (prop->encoding),
                                          prop->format,
                                          prop->value,
                                          prop->nitems,
                                          &list);

  DBG("count=%d\n", count);
  if (count == 0)
    return NULL;

  retval = list[0];
  list[0] = g_strdup (""); /* something to free */
  
  g_strfreev (list);

  RET(retval);
}

char *
get_textproperty(Window win, Atom atom)
{
    XTextProperty text_prop;
    char *retval;
    
    ENTER;
    if (XGetTextProperty(GDK_DISPLAY(), win, &text_prop, atom)) {
        DBG("format=%d enc=%d nitems=%d value=%s   \n",
              text_prop.format,
              text_prop.encoding,
              text_prop.nitems,
              text_prop.value);
        retval = text_property_to_utf8 (&text_prop);
        if (text_prop.nitems > 0)
            XFree (text_prop.value);
        RET(retval);

    }
    RET(NULL);
}


int
get_net_number_of_desktops()
{
    int desknum;
    unsigned long *data;

    ENTER;
    data = get_xaproperty (GDK_ROOT_WINDOW(), a_NET_NUMBER_OF_DESKTOPS,
          XA_CARDINAL, 0);
    if (!data)
        RET(0);

    desknum = *data;
    XFree (data);
    RET(desknum);
}

    
int
get_net_current_desktop ()
{
    int desk;
    unsigned long *data;

    ENTER;
    data = get_xaproperty (GDK_ROOT_WINDOW(), a_NET_CURRENT_DESKTOP, XA_CARDINAL, 0);
    if (!data)
        RET(0);

    desk = *data;
    XFree (data);
    RET(desk);
}

int
get_net_wm_desktop(Window win)
{
    int desk = 0;
    unsigned long *data;

    ENTER;
    data = get_xaproperty (win, a_NET_WM_DESKTOP, XA_CARDINAL, 0);
    if (data) {
        desk = *data;
        XFree (data);
    }
    RET(desk);
}

void
get_net_wm_state(Window win, net_wm_state *nws)
{
    Atom *state;
    int num3;
    
    
    ENTER;
    bzero(nws, sizeof(nws));
    if (!(state = get_xaproperty(win, a_NET_WM_STATE, XA_ATOM, &num3)))
        RET();
    
    DBG( "%x: netwm state = { ", (unsigned int)win);
    while (--num3 >= 0) {
        if (state[num3] == a_NET_WM_STATE_SKIP_PAGER) {
            DBG("NET_WM_STATE_SKIP_PAGER ");
            nws->skip_pager = 1;
        } else if (state[num3] == a_NET_WM_STATE_SKIP_TASKBAR) {
            DBG( "NET_WM_STATE_SKIP_TASKBAR ");	    
	    nws->skip_taskbar = 1;
	} else if (state[num3] == a_NET_WM_STATE_STICKY) {
            DBG( "NET_WM_STATE_STICKY ");
	    nws->sticky = 1;
        } else if (state[num3] == a_NET_WM_STATE_HIDDEN) {
            DBG( "NET_WM_STATE_HIDDEN ");
            nws->hidden = 1;
	} else if (state[num3] == a_NET_WM_STATE_SHADED) {
            DBG( "NET_WM_STATE_SHADED ");
            nws->shaded = 1;
	} else {
	    DBG( "... ");
	}
    }
    XFree(state);
    DBG( "}\n");
    RET();
}




void
get_net_wm_window_type(Window win, net_wm_window_type *nwwt)
{
    Atom *state;
    int num3;
    
    
    ENTER;
    bzero(nwwt, sizeof(nwwt));
    if (!(state = get_xaproperty(win, a_NET_WM_WINDOW_TYPE, XA_ATOM, &num3)))
        RET();
    
    DBG( "%x: netwm state = { ", (unsigned int)win);
    while (--num3 >= 0) {
        if (state[num3] == a_NET_WM_WINDOW_TYPE_DESKTOP) {
            DBG("NET_WM_WINDOW_TYPE_DESKTOP ");
            nwwt->desktop = 1;
        } else if (state[num3] == a_NET_WM_WINDOW_TYPE_DOCK) {
            DBG( "NET_WM_WINDOW_TYPE_DOCK ");	    
	    nwwt->dock = 1;
	} else if (state[num3] == a_NET_WM_WINDOW_TYPE_TOOLBAR) {
            DBG( "NET_WM_WINDOW_TYPE_TOOLBAR ");
	    nwwt->toolbar = 1;
        } else if (state[num3] == a_NET_WM_WINDOW_TYPE_MENU) {
            DBG( "NET_WM_WINDOW_TYPE_MENU ");
            nwwt->menu = 1;
	} else if (state[num3] == a_NET_WM_WINDOW_TYPE_UTILITY) {
            DBG( "NET_WM_WINDOW_TYPE_UTILITY ");
            nwwt->utility = 1;
	} else if (state[num3] == a_NET_WM_WINDOW_TYPE_SPLASH) {
            DBG( "NET_WM_WINDOW_TYPE_SPLASH ");
            nwwt->splash = 1;
	} else if (state[num3] == a_NET_WM_WINDOW_TYPE_DIALOG) {
            DBG( "NET_WM_WINDOW_TYPE_DIALOG ");
            nwwt->dialog = 1;
	} else if (state[num3] == a_NET_WM_WINDOW_TYPE_NORMAL) {
            DBG( "NET_WM_WINDOW_TYPE_NORMAL ");
            nwwt->normal = 1;
	} else {
	    DBG( "... ");
	}
    }
    XFree(state);
    DBG( "}\n");
    RET();
}



    

int
get_wm_state (Window win)
{
    unsigned long *data;
    int ret = 0;

    ENTER;
    data = get_xaproperty (win, a_WM_STATE, a_WM_STATE, 0);
    if (data) {
        ret = data[0];
        XFree (data);
    }
    RET(ret);
}

static void
calculate_width(int scrw, int wtype, int allign, int margin,
      int *panw, int *x)
{
    ENTER;
    DBG("scrw=%d\n", scrw);
    DBG("IN panw=%d\n", *panw);
    //scrw -= 2;
    if (wtype == WIDTH_PERCENT) {
        /* sanity check */
        if (*panw > 100)
            *panw = 100;
        else if (*panw < 0)
            *panw = 1;
        *panw = ((gfloat) scrw * (gfloat) *panw) / 100.0;
    }
    if (allign != ALLIGN_CENTER) {
        if (margin > scrw) {
            ERR( "margin is bigger then edge size %d > %d. Ignoring margin\n",
                  margin, scrw);
            margin = 0;
        }
        if (wtype == WIDTH_PERCENT)
            //*panw = MAX(scrw - margin, *panw);
            ;
        else
            *panw = MIN(scrw - margin, *panw);
    }
    DBG("OUT panw=%d\n", *panw);
    if (allign == ALLIGN_LEFT)
        *x += margin;
    else if (allign == ALLIGN_RIGHT) {
        *x += scrw - *panw - margin;
        if (*x < 0)
            *x = 0;
    } else if (allign == ALLIGN_CENTER)
        *x += (scrw - *panw) / 2;
    RET();
}


void
calculate_position(panel *np)
{
    int sswidth, ssheight, minx, miny;

    ENTER;
    if (0)  {
        //if (np->curdesk < np->wa_len/4) {
        minx = np->workarea[np->curdesk*4 + 0];
        miny = np->workarea[np->curdesk*4 + 1];
        sswidth  = np->workarea[np->curdesk*4 + 2];
        ssheight = np->workarea[np->curdesk*4 + 3];
    } else {
        minx = miny = 0;
        sswidth  = gdk_screen_width();
        ssheight = gdk_screen_height();

    }
    
    if (np->edge == EDGE_TOP || np->edge == EDGE_BOTTOM) {
        np->aw = np->width;
        np->ax = minx;
        calculate_width(sswidth, np->widthtype, np->allign, np->margin,
              &np->aw, &np->ax);
        np->ah = np->height;
        np->ah = MIN(PANEL_HEIGHT_MAX, np->ah);
        np->ah = MAX(PANEL_HEIGHT_MIN, np->ah);
        np->ay = miny + ((np->edge == EDGE_TOP) ? 0 : (ssheight - np->ah));

    } else {
        np->ah = np->width;
        np->ay = miny;
        calculate_width(ssheight, np->widthtype, np->allign, np->margin,
              &np->ah, &np->ay);
        np->aw = np->height;
        np->aw = MIN(PANEL_HEIGHT_MAX, np->aw);
        np->aw = MAX(PANEL_HEIGHT_MIN, np->aw);
        np->ax = minx + ((np->edge == EDGE_LEFT) ? 0 : (sswidth - np->aw));
    }
    DBG("%s - x=%d y=%d w=%d h=%d\n", __FUNCTION__, np->ax, np->ay, np->aw, np->ah);
    RET();
}



gchar *
expand_tilda(gchar *file)
{
    ENTER;
    RET((file[0] == '~') ?
        g_strdup_printf("%s%s", getenv("HOME"), file+1)
        : g_strdup(file));

}





Window
Select_Window(Display *dpy)
{
    int status;
    Cursor cursor;
    XEvent event;
    Window target_win = None, root = RootWindow(dpy,DefaultScreen(dpy));
    int buttons = 0;

    /* Make the target cursor */
    cursor = XCreateFontCursor(dpy, XC_crosshair);

    /* Grab the pointer using target cursor, letting it room all over */
    status = XGrabPointer(dpy, root, False,
          ButtonPressMask|ButtonReleaseMask, GrabModeSync,
          GrabModeAsync, root, cursor, CurrentTime);
    if (status != GrabSuccess) {
        ERR("Can't grab the mouse.");
        RET(None);
    }
    /* Let the user select a window... */
    while ((target_win == None) || (buttons != 0)) {
        /* allow one more event */
        XAllowEvents(dpy, SyncPointer, CurrentTime);
        XWindowEvent(dpy, root, ButtonPressMask|ButtonReleaseMask, &event);
        switch (event.type) {
        case ButtonPress:
            if (target_win == None) {
                target_win = event.xbutton.subwindow; /* window selected */
                DBG("target win = 0x%x\n", target_win);
                if (target_win == None) target_win = root;
            }
            buttons++;
            break;
        case ButtonRelease:
            if (buttons > 0) /* there may have been some down before we started */
                buttons--;
            break;
        }
    } 

    XUngrabPointer(dpy, CurrentTime);      /* Done with pointer */
    return(target_win);
}
