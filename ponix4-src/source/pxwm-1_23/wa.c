#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>

// Info: xwininfo
// I am compiling using 
// gcc -o activate activate.c -L/usr/X11R6/lib -lX11

// ERROR HANDLER, GENERIC
static int ErrorHandler (Display *display, XErrorEvent *error)
{
   printf ("\r\n error! \r\n");// gcc -o xwinspy lol.c -L/usr/X11R6/lib -lX11
   return 0;
}
// END ERROR HANDLER


// Recursively search through all windows on display
Window SearchWindow(char* szWindowToFind, int level, Display *display, Window rootWindow, int iMatchMode, int showErrors)
{
    Window parent;
    Window *children;
    unsigned int noOfChildren;
    int status;
    int i;
    Window wSearchedWindow = 0;

    char* win_name;
    if (XFetchName(display, rootWindow, &win_name))
    {
            //printf("WinName (Level %d): %s\n", level, win_name);
            if(iMatchMode == 0)
            {
                if( strstr(win_name, szWindowToFind) )
                {
                    return rootWindow;
                }
            }
            else if(iMatchMode == 1)
            {
                if( !strcmp(win_name, szWindowToFind) )
                {
                    return rootWindow;
                }
            }
            else if(iMatchMode == 2)
            {
                if( strcasestr(win_name, szWindowToFind) )
                {
                    return rootWindow;
                }
            }
            else if(iMatchMode == 3)
            {
                if( !strcasecmp(win_name, szWindowToFind) )
                {
                    return rootWindow;
                }
            }
            else 
            {
                if( strstr(win_name, szWindowToFind) )
                {
                    return rootWindow;
                }
            }

    } // End if XFetchName



    status = XQueryTree (display, rootWindow, &rootWindow, &parent, &children, &noOfChildren);

    if (status == 0)
    {
        if (showErrors)
            printf ("ERROR - Could not query the window tree. Aborting.\r\n");
        return;
    }

    if (noOfChildren > 0)
    {
        for (i=0; i < noOfChildren; i++)
        {
            wSearchedWindow = SearchWindow(szWindowToFind, level+1, display, children[i], iMatchMode, showErrors);
            if(wSearchedWindow)
            {
                break;
            }
        }
    } 

    XFree ((char*) children);

    return wSearchedWindow;
} // End Sub EnumerateWindows


Window FindWindow(char* szWindowToFind)
{
    Display *display = XOpenDisplay (NULL);
    int screen = DefaultScreen (display);

    XSetErrorHandler(ErrorHandler);

    Window rootWindow = RootWindow (display, screen);   

    Window wSearchedWindow = SearchWindow(szWindowToFind, 0, display, rootWindow, 0, 0);

    char* win_name;
    if (XFetchName(display, wSearchedWindow, &win_name))
    {
        printf("Found: %s\n", win_name);
    }

    XCloseDisplay (display);
    return wSearchedWindow;
}

void ActivateWindow(char* szWindow)
{
    Window wdThisWindow = FindWindow(szWindow);

    Display *display = XOpenDisplay (NULL);

    char* win_name;
    if (XFetchName(display, wdThisWindow, &win_name))
    {
        printf("Activating: %s\n", win_name);
    }

    XSetErrorHandler(ErrorHandler);

    XSetWindowAttributes xswa;
    xswa.override_redirect = True;
    XChangeWindowAttributes(display, wdThisWindow, CWOverrideRedirect, &xswa);
    XRaiseWindow(display, wdThisWindow);
    xswa.override_redirect = False;
    XChangeWindowAttributes(display, wdThisWindow, CWOverrideRedirect, &xswa);
    XSetInputFocus(display, wdThisWindow, RevertToNone, CurrentTime);

    XCloseDisplay (display);
}



// ENUMARATE THROUGH WINDOWS AND DISPLAY THEIR TITLES
void EnumerateWindows(int level, Display *display, Window rootWindow, int showErrors)
{
    Window parent;
    Window *children;
    unsigned int noOfChildren;
    int status;
    int i;

    char* win_name;
    if (XFetchName(display, rootWindow, &win_name))
    {
            printf("Window-Name (Level %d): %s\n", level, win_name);
    }

    status = XQueryTree (display, rootWindow, &rootWindow, &parent, &children, &noOfChildren);

    if (status == 0)
    {
        if (showErrors)
            printf ("ERROR - Could not query the window tree. Aborting.\r\n");
        return;
    }

    if (noOfChildren > 0)
    {
        for (i=0; i < noOfChildren; i++)
        {
            EnumerateWindows(level+1, display, children[i], showErrors);
        }
    } 

    XFree ((char*) children);
} // End Sub EnumerateWindows


void ListAllWindowsOnScreen()
{
    Display *display = XOpenDisplay (NULL);
    int screen = DefaultScreen (display);

    XSetErrorHandler(ErrorHandler);

    Window rootWindow = RootWindow (display, screen);   

    EnumerateWindows(0, display, rootWindow, 0);
    XCloseDisplay (display);
}


int main(int argc, char *argv[])
{
    ListAllWindowsOnScreen();

    if ( (argc > 0) && (strcmp(argv[1],"")) ) {
        printf ("Activating window '%s'\n", argv[1]);    
        ActivateWindow(argv[1]);
    }

    return EXIT_SUCCESS;
}
