/**
 * @file parse.c
 * @author Joe Wingbermuehle
 * @date 2004-2006
 *
 * @brief JWM configuration parser.
 *
 */

#include "jwm.h"
#include "parse.h"
#include "lex.h"
#include "settings.h"
#include "menu.h"
#include "root.h"
#include "tray.h"
#include "group.h"
#include "misc.h"
#include "swallow.h"
#include "pager.h"
#include "error.h"
#include "key.h"
#include "main.h"
#include "font.h"
#include "color.h"
#include "icon.h"
#include "command.h"
#include "taskbar.h"
#include "traybutton.h"
#include "clock.h"
#include "dock.h"
#include "background.h"
#include "spacer.h"
#include "desktop.h"

/* Save some space by reusing parts of strings. */
static const char NOBORDER_STRING[] = "noborder";
#define BORDER_STRING (&NOBORDER_STRING[2])
static const char NOTITLE_STRING[]  = "notitle";
#define TITLE_STRING (&NOTITLE_STRING[2])
static const char MAX_WIDTH_STRING[] = "maxwidth";
#define WIDTH_STRING (&MAX_WIDTH_STRING[3])
static const char NOSHADE_STRING[] = "noshade";
#define SHADE_STRING (&NOSHADE_STRING[2])
static const char FULLSCREEN_STRING[] = "fullscreen";
#define SCREEN_STRING (&FULLSCREEN_STRING[4])

/** Structure to map key names to key types. */
typedef struct KeyMapType {
   const char *name;
   KeyType key;
} KeyMapType;

/** Mapping of key names to key types. */
static const KeyMapType KEY_MAP[] = {
   { "up",                    KEY_UP           },
   { "down",                  KEY_DOWN         },
   { "right",                 KEY_RIGHT        },
   { "left",                  KEY_LEFT         },
   { "escape",                KEY_ESC          },
   { "select",                KEY_ENTER        },
   { "next",                  KEY_NEXT         },
   { "nextstacked",           KEY_NEXTSTACK    },
   { "prev",                  KEY_PREV         },
   { "prevstacked",           KEY_PREVSTACK    },
   { "close",                 KEY_CLOSE        },
   { "minimize",              KEY_MIN          },
   { "maximize",              KEY_MAX          },
   { &SHADE_STRING[0],        KEY_SHADE        },
   { "stick",                 KEY_STICK        },
   { "move",                  KEY_MOVE         },
   { "resize",                KEY_RESIZE       },
   { "window",                KEY_WIN          },
   { "restart",               KEY_RESTART      },
   { "exit",                  KEY_EXIT         },
   { "desktop#",              KEY_DESKTOP      },
   { "rdesktop",              KEY_RDESKTOP     },
   { "ldesktop",              KEY_LDESKTOP     },
   { "udesktop",              KEY_UDESKTOP     },
   { "ddesktop",              KEY_DDESKTOP     },
   { "showdesktop",           KEY_SHOWDESK     },
   { "showtray",              KEY_SHOWTRAY     },
   { &FULLSCREEN_STRING[0],   KEY_FULLSCREEN   },
   { NULL,                    KEY_NONE         }
};

/** Structure to map names to group options. */
typedef struct OptionMapType {
   const char *name;
   OptionType option;
} OptionMapType;

/** Mapping of names to group options. */
static const OptionMapType OPTION_MAP[] = {
   { "sticky",             OPTION_STICKY        },
   { "nolist",             OPTION_NOLIST        },
   { "nopager",            OPTION_NOPAGER       },
   { &BORDER_STRING[0],    OPTION_BORDER        },
   { &NOBORDER_STRING[0],  OPTION_NOBORDER      },
   { &TITLE_STRING[0],     OPTION_TITLE         },
   { &NOTITLE_STRING[0],   OPTION_NOTITLE       },
   { "pignore",            OPTION_PIGNORE       },
   { "iignore",            OPTION_IIGNORE       },
   { "maximized",          OPTION_MAXIMIZED     },
   { "minimized",          OPTION_MINIMIZED     },
   { "hmax",               OPTION_MAX_H         },
   { "vmax",               OPTION_MAX_V         },
   { "nofocus",            OPTION_NOFOCUS       },
   { &NOSHADE_STRING[0],   OPTION_NOSHADE       },
   { "noturgent",          OPTION_NOTURGENT     },
   { "centered",           OPTION_CENTERED      },
   { "tiled",              OPTION_TILED         },
   { NULL,                 OPTION_INVALID       }
};

static const char *DEFAULT_TITLE = "JWM";
static const char *LABEL_ATTRIBUTE = "label";
static const char *ICON_ATTRIBUTE = "icon";
static const char *CONFIRM_ATTRIBUTE = "confirm";
static const char *LABELED_ATTRIBUTE = "labeled";
static const char *ONROOT_ATTRIBUTE = "onroot";
static const char *LAYER_ATTRIBUTE = "layer";
static const char *LAYOUT_ATTRIBUTE = "layout";
static const char *AUTOHIDE_ATTRIBUTE = "autohide";
static const char *X_ATTRIBUTE = "x";
static const char *Y_ATTRIBUTE = "y";
static const char *WIDTH_ATTRIBUTE = &WIDTH_STRING[0];
static const char *HEIGHT_ATTRIBUTE = "height";
static const char *NAME_ATTRIBUTE = "name";
static const char *BORDER_ATTRIBUTE = BORDER_STRING;
static const char *DISTANCE_ATTRIBUTE = "distance";
static const char *INSERT_ATTRIBUTE = "insert";
static const char *MAX_WIDTH_ATTRIBUTE = &MAX_WIDTH_STRING[0];
static const char *FORMAT_ATTRIBUTE = "format";
static const char *ZONE_ATTRIBUTE = "zone";
static const char *VALIGN_ATTRIBUTE = "valign";
static const char *HALIGN_ATTRIBUTE = "halign";
static const char *POPUP_ATTRIBUTE = "popup";
static const char *DELAY_ATTRIBUTE = "delay";
static const char *ENABLED_ATTRIBUTE = "enabled";
static const char *COORDINATES_ATTRIBUTE = "coordinates";
static const char *TYPE_ATTRIBUTE = "type";

static const char *FALSE_VALUE = "false";
static const char *TRUE_VALUE = "true";
static const char *OUTLINE_VALUE = "outline";
static const char *OPAQUE_VALUE = "opaque";

static char ParseFile(const char *fileName, int depth);
static char *ReadFile(FILE *fd);

/* Misc. */
static void Parse(const TokenNode *start, int depth);
static void ParseInclude(const TokenNode *tp, int depth);
static void ParseDesktops(const TokenNode *tp);
static void ParseDesktop(int desktop, const TokenNode *tp);
static void ParseDesktopBackground(int desktop, const TokenNode *tp);

/* Menus. */
static void ParseRootMenu(const TokenNode *start);
static MenuItem *ParseMenuItem(const TokenNode *start, Menu *menu,
                               MenuItem *last);
static MenuItem *ParseMenuInclude(const TokenNode *tp, Menu *menu,
                                  MenuItem *last);
static MenuItem *InsertMenuItem(MenuItem *last);

/* Tray. */
static void ParseTray(const TokenNode *tp);
static void ParsePager(const TokenNode *tp, TrayType *tray);
static void ParseTaskList(const TokenNode *tp, TrayType *tray);
static void ParseSwallow(const TokenNode *tp, TrayType *tray);
static void ParseTrayButton(const TokenNode *tp, TrayType *tray);
static void ParseClock(const TokenNode *tp, TrayType *tray);
static void ParseDock(const TokenNode *tp, TrayType *tray);
static void ParseSpacer(const TokenNode *tp, TrayType *tray);

/* Groups. */
static void ParseGroup(const TokenNode *tp);
static void ParseGroupOption(const TokenNode *tp,
                             struct GroupType *group,
                             const char *option);

/* Style. */
static void ParseWindowStyle(const TokenNode *start);
static void ParseActiveWindowStyle(const TokenNode *tp);
static void ParseInactiveWindowStyle(const TokenNode *tp);
static void ParseTaskListStyle(const TokenNode *start);
static void ParseTrayStyle(const TokenNode *start);
static void ParsePagerStyle(const TokenNode *start);
static void ParseMenuStyle(const TokenNode *start);
static void ParsePopupStyle(const TokenNode *start);
static void ParseClockStyle(const TokenNode *start);
static void ParseTrayButtonStyle(const TokenNode *start);

/* Feel. */
static void ParseKey(const TokenNode *tp);
static void ParseSnapMode(const TokenNode *tp);
static void ParseMoveMode(const TokenNode *tp);
static void ParseResizeMode(const TokenNode *tp);
static void ParseFocusModel(const TokenNode *tp);

static void ParseGradient(const char *value, ColorType a, ColorType b);
static char *FindAttribute(AttributeNode *ap, const char *name);
static void ReleaseTokens(TokenNode *np);
static unsigned int ParseUnsigned(const TokenNode *tp, const char *str);
static unsigned int ParseOpacity(const TokenNode *tp, const char *str);
static WinLayerType ParseLayer(const TokenNode *tp, const char *str);
static StatusWindowType ParseStatusWindowType(const TokenNode *tp,
                                              const char *str);
static void InvalidTag(const TokenNode *tp, TokenType parent);
static void ParseError(const TokenNode *tp, const char *str, ...);

/** Parse the JWM configuration. */
void ParseConfig(const char *fileName)
{
   if(!ParseFile(fileName, 0)) {
      if(JUNLIKELY(!ParseFile(SYSTEM_CONFIG, 0))) {
         ParseError(NULL, "could not open %s or %s", fileName, SYSTEM_CONFIG);
      }
   }
   ValidateTrayButtons();
   ValidateKeys();
}

/**
 * Parse a specific file.
 * @return 1 on success and 0 on failure.
 */
char ParseFile(const char *fileName, int depth)
{

   TokenNode *tokens;
   FILE *fd;
   char *buffer;

   depth += 1;
   if(JUNLIKELY(depth > MAX_INCLUDE_DEPTH)) {
      ParseError(NULL, "include depth (%d) exceeded", MAX_INCLUDE_DEPTH);
      return 0;
   }

   fd = fopen(fileName, "r");
   if(!fd) {
      return 0;
   }

   buffer = ReadFile(fd);
   fclose(fd);

   tokens = Tokenize(buffer, fileName);
   Release(buffer);
   Parse(tokens, depth);
   ReleaseTokens(tokens);

   return 1;

}

/** Release a token list. */
void ReleaseTokens(TokenNode *np)
{

   AttributeNode *ap;
   TokenNode *tp;

   while(np) {
      tp = np->next;

      while(np->attributes) {
         ap = np->attributes->next;
         if(np->attributes->name) {
            Release(np->attributes->name);
         }
         if(np->attributes->value) {
            Release(np->attributes->value);
         }
         Release(np->attributes);
         np->attributes = ap;
      }

      if(np->subnodeHead) {
         ReleaseTokens(np->subnodeHead);
      }

      if(np->value) {
         Release(np->value);
      }

      if(np->invalidName) {
         Release(np->invalidName);
      }

      if(np->fileName) {
         Release(np->fileName);
      }

      Release(np);
      np = tp;
   }

}

/** Parse a token list. */
void Parse(const TokenNode *start, int depth)
{

   TokenNode *tp;

   if(!start) {
      return;
   }

   if(JLIKELY(start->type == TOK_JWM)) {
      for(tp = start->subnodeHead; tp; tp = tp->next) {
         if(shouldReload) {
            switch(tp->type) {
            case TOK_ROOTMENU:
               ParseRootMenu(tp);
               break;
            case TOK_INCLUDE:
               ParseInclude(tp, depth);
               break;
            default:
               break;
            }
         } else {
            switch(tp->type) {
            case TOK_DESKTOPS:
               ParseDesktops(tp);
               break;
            case TOK_DOUBLECLICKSPEED:
               settings.doubleClickSpeed = ParseUnsigned(tp, tp->value);
               break;
            case TOK_DOUBLECLICKDELTA:
               settings.doubleClickDelta = ParseUnsigned(tp, tp->value);
               break;
            case TOK_FOCUSMODEL:
               ParseFocusModel(tp);
               break;
            case TOK_GROUP:
               ParseGroup(tp);
               break;
            case TOK_ICONPATH:
               AddIconPath(tp->value);
               break;
            case TOK_INCLUDE:
               ParseInclude(tp, depth);
               break;
            case TOK_KEY:
               ParseKey(tp);
               break;
            case TOK_MENUSTYLE:
               ParseMenuStyle(tp);
               break;
            case TOK_MOVEMODE:
               ParseMoveMode(tp);
               break;
            case TOK_PAGERSTYLE:
               ParsePagerStyle(tp);
               break;
            case TOK_POPUPSTYLE:
               ParsePopupStyle(tp);
               break;
            case TOK_RESIZEMODE:
               ParseResizeMode(tp);
               break;
            case TOK_RESTARTCOMMAND:
               AddRestartCommand(tp->value);
               break;
            case TOK_ROOTMENU:
               ParseRootMenu(tp);
               break;
            case TOK_SHUTDOWNCOMMAND:
               AddShutdownCommand(tp->value);
               break;
            case TOK_SNAPMODE:
               ParseSnapMode(tp);
               break;
            case TOK_STARTUPCOMMAND:
               AddStartupCommand(tp->value);
               break;
            case TOK_TASKLISTSTYLE:
               ParseTaskListStyle(tp);
               break;
            case TOK_TRAY:
               ParseTray(tp);
               break;
            case TOK_TRAYSTYLE:
               ParseTrayStyle(tp);
               break;
            case TOK_TRAYBUTTONSTYLE:
               ParseTrayButtonStyle(tp);
               break;
            case TOK_CLOCKSTYLE:
               ParseClockStyle(tp);
               break;
            case TOK_WINDOWSTYLE:
               ParseWindowStyle(tp);
               break;
            default:
               InvalidTag(tp, TOK_JWM);
               break;
            }
         }
      }
   } else {
      ParseError(start, "invalid start tag: %s", GetTokenName(start));
   }

}

/** Parse focus model. */
void ParseFocusModel(const TokenNode *tp) {
   if(JLIKELY(tp->value)) {
      if(!strcmp(tp->value, "sloppy")) {
         settings.focusModel = FOCUS_SLOPPY;
      } else if(!strcmp(tp->value, "click")) {
         settings.focusModel = FOCUS_CLICK;
      } else {
         ParseError(tp, "invalid focus model: \"%s\"", tp->value);
      }
   } else {
      ParseError(tp, "focus model not specified");
   }
}

/** Parse snap mode for moving windows. */
void ParseSnapMode(const TokenNode *tp) {

   const char *distance;

   distance = FindAttribute(tp->attributes, DISTANCE_ATTRIBUTE);
   if(distance) {
      settings.snapDistance = ParseUnsigned(tp, distance);
   }

   if(JLIKELY(tp->value)) {
      if(!strcmp(tp->value, "none")) {
         settings.snapMode = SNAP_NONE;
      } else if(!strcmp(tp->value, SCREEN_STRING)) {
         settings.snapMode = SNAP_SCREEN;
      } else if(!strcmp(tp->value, BORDER_STRING)) {
         settings.snapMode = SNAP_BORDER;
      } else {
         ParseError(tp, "invalid snap mode: %s", tp->value);
      }
   } else {
      ParseError(tp, "snap mode not specified");
   }
}

/** Parse move mode. */
void ParseMoveMode(const TokenNode *tp) {

   const char *str;

   str = FindAttribute(tp->attributes, COORDINATES_ATTRIBUTE);
   if(str) {
      settings.moveStatusType = ParseStatusWindowType(tp, str);
   }

   str = FindAttribute(tp->attributes, DELAY_ATTRIBUTE);
   if(str) {
      settings.desktopDelay = ParseUnsigned(tp, str);
   }

   if(JLIKELY(tp->value)) {
      if(!strcmp(tp->value, OUTLINE_VALUE)) {
         settings.moveMode = MOVE_OUTLINE;
      } else if(!strcmp(tp->value, OPAQUE_VALUE)) {
         settings.moveMode = MOVE_OPAQUE;
      } else {
         ParseError(tp, "invalid move mode: %s", tp->value);
      }
   } else {
      ParseError(tp, "move mode not specified");
   }

}

/** Parse resize mode. */
void ParseResizeMode(const TokenNode *tp) {

   const char *str;

   str = FindAttribute(tp->attributes, COORDINATES_ATTRIBUTE);
   if(str) {
      settings.resizeStatusType = ParseStatusWindowType(tp, str);
   }

   if(JLIKELY(tp->value)) {
      if(!strcmp(tp->value, OUTLINE_VALUE)) {
         settings.resizeMode = RESIZE_OUTLINE;
      } else if(!strcmp(tp->value, OPAQUE_VALUE)) {
         settings.resizeMode = RESIZE_OPAQUE;
      } else {
         ParseError(tp, "invalid resize mode: %s", tp->value);
      }
   } else {
      ParseError(tp, "resize mode not specified");
   }

}

/** Parse a root menu. */
void ParseRootMenu(const TokenNode *start) {

   const char *value;
   Menu *menu;

   menu = Allocate(sizeof(Menu));

   value = FindAttribute(start->attributes, HEIGHT_ATTRIBUTE);
   if(value) {
      menu->itemHeight = ParseUnsigned(start, value);
   } else {
      menu->itemHeight = 0;
   }

   value = FindAttribute(start->attributes, LABELED_ATTRIBUTE);
   if(value && !strcmp(value, TRUE_VALUE)) {
      value = FindAttribute(start->attributes, LABEL_ATTRIBUTE);
      if(!value) {
         value = DEFAULT_TITLE;
      }
      menu->label = CopyString(value);
   } else {
      menu->label = NULL;
   }

   menu->items = NULL;
   ParseMenuItem(start->subnodeHead, menu, NULL);

   value = FindAttribute(start->attributes, ONROOT_ATTRIBUTE);
   if(!value) {
      value = "123";
   }

   SetRootMenu(value, menu);

}

/** Insert a new menu item into a menu. */
MenuItem *InsertMenuItem(MenuItem *last) {

   MenuItem *item;

   item = Allocate(sizeof(MenuItem));
   item->name = NULL;
   item->type = MENU_ITEM_NORMAL;
   item->iconName = NULL;
   item->action.type = MA_NONE;
   item->action.data.str = NULL;
   item->submenu = NULL;

   item->next = NULL;
   if(last) {
      last->next = item;
   }

   return item;

}

/** Parse a menu item. */
MenuItem *ParseMenuItem(const TokenNode *start, Menu *menu,
   MenuItem *last) {

   Menu *child;
   const char *value;

   Assert(menu);

   menu->offsets = NULL;
   while(start) {
      switch(start->type) {
      case TOK_INCLUDE:

         last = ParseMenuInclude(start, menu, last);

         break;
      case TOK_MENU:

         last = InsertMenuItem(last);
         last->type = MENU_ITEM_SUBMENU;
         if(!menu->items) {
            menu->items = last;
         }

         value = FindAttribute(start->attributes, LABEL_ATTRIBUTE);
         last->name = CopyString(value);

         value = FindAttribute(start->attributes, ICON_ATTRIBUTE);
         last->iconName = CopyString(value);

         last->submenu = Allocate(sizeof(Menu));
         child = last->submenu;

         value = FindAttribute(start->attributes, HEIGHT_ATTRIBUTE);
         if(value) {
            child->itemHeight = ParseUnsigned(start, value);
         } else {
            child->itemHeight = menu->itemHeight;
         }

         value = FindAttribute(start->attributes, LABELED_ATTRIBUTE);
         if(value && !strcmp(value, TRUE_VALUE)) {
            if(last->name) {
               child->label = CopyString(last->name);
            } else {
               child->label = CopyString(DEFAULT_TITLE);
            }
         } else {
            child->label = NULL;
         }

         last->submenu->items = NULL;
         ParseMenuItem(start->subnodeHead, last->submenu, NULL);

         break;
      case TOK_PROGRAM:

         last = InsertMenuItem(last);
         if(!menu->items) {
            menu->items = last;
         }

         value = FindAttribute(start->attributes, LABEL_ATTRIBUTE);
         if(value) {
            last->name = CopyString(value);
         } else if(start->value) {
            last->name = CopyString(start->value);
         }

         value = FindAttribute(start->attributes, ICON_ATTRIBUTE);
         last->iconName = CopyString(value);

         last->action.type = MA_EXECUTE;
         last->action.data.str = CopyString(start->value);

         break;
      case TOK_SEPARATOR:

         last = InsertMenuItem(last);
         last->type = MENU_ITEM_SEPARATOR;
         if(!menu->items) {
            menu->items = last;
         }

         break;
      case TOK_DESKTOPS:
      case TOK_STICK:
      case TOK_MAXIMIZE:
      case TOK_MINIMIZE:
      case TOK_SHADE:
      case TOK_MOVE:
      case TOK_RESIZE:
      case TOK_KILL:
      case TOK_CLOSE:

         last = InsertMenuItem(last);
         if(!menu->items) {
            menu->items = last;
         }

         value = FindAttribute(start->attributes, LABEL_ATTRIBUTE);
         if(!value) {
            value = GetTokenName(start);
         }
         last->name = CopyString(value);

         value = FindAttribute(start->attributes, ICON_ATTRIBUTE);
         last->iconName = CopyString(value);

         switch(start->type) {
         case TOK_DESKTOPS:
            last->action.type = MA_DESKTOP;
            break;
         case TOK_STICK:
            last->action.type = MA_STICK;
            break;
         case TOK_MAXIMIZE:
            last->action.type = MA_MAXIMIZE;
            break;
         case TOK_MINIMIZE:
            last->action.type = MA_MINIMIZE;
            break;
         case TOK_SHADE:
            last->action.type = MA_SHADE;
            break;
         case TOK_MOVE:
            last->action.type = MA_MOVE;
            break;
         case TOK_RESIZE:
            last->action.type = MA_RESIZE;
            break;
         case TOK_KILL:
            last->action.type = MA_KILL;
            break;
         case TOK_CLOSE:
            last->action.type = MA_CLOSE;
            break;
         default:
            break;
         }

         break;
      case TOK_EXIT:

         last = InsertMenuItem(last);
         if(!menu->items) {
            menu->items = last;
         }

         value = FindAttribute(start->attributes, CONFIRM_ATTRIBUTE);
         if(value && !strcmp(value, FALSE_VALUE)) {
            settings.exitConfirmation = 0;
         } else {
            settings.exitConfirmation = 1;
         }

         value = FindAttribute(start->attributes, LABEL_ATTRIBUTE);
         if(!value) {
            value = GetTokenName(start);
         }
         last->name = CopyString(value);

         value = FindAttribute(start->attributes, ICON_ATTRIBUTE);
         last->iconName = CopyString(value);

         last->action.type = MA_EXIT;
         last->action.data.str = CopyString(start->value);

         break;
      case TOK_RESTART:

         last = InsertMenuItem(last);
         if(!menu->items) {
            menu->items = last;
         }

         value = FindAttribute(start->attributes, LABEL_ATTRIBUTE);
         if(!value) {
            value = GetTokenName(start);
         }
         last->name = CopyString(value);

         value = FindAttribute(start->attributes, ICON_ATTRIBUTE);
         last->iconName = CopyString(value);

         last->action.type = MA_RESTART;

         break;
      default:
         InvalidTag(start, TOK_MENU);
         break;
      }
      start = start->next;
   }

   return last;

}

/** Parse a menu include. */
MenuItem *ParseMenuInclude(const TokenNode *tp, Menu *menu,
   MenuItem *last) {

   FILE *fd;
   char *path;
   char *buffer = NULL;
   TokenNode *start;

   Assert(tp);

   if(!strncmp(tp->value, "exec:", 5)) {

      path = Allocate(strlen(tp->value) - 5 + 1);
      strcpy(path, tp->value + 5);
      ExpandPath(&path);

      fd = popen(path, "r");
      if(JLIKELY(fd)) {
         buffer = ReadFile(fd);
         pclose(fd);
      } else {
         ParseError(tp, "could not execute included program: %s", path);
      }

   } else {

      path = CopyString(tp->value);
      ExpandPath(&path);

      fd = fopen(path, "r");
      if(JLIKELY(fd)) {
         buffer = ReadFile(fd);
         fclose(fd);
      } else {
         ParseError(tp, "could not open include: %s", path);
      }

   }

   if(!buffer) {
      Release(path);
      return last;
   }

   start = Tokenize(buffer, path);
   Release(buffer);
   Release(path);

   if(JUNLIKELY(!start || start->type != TOK_JWM)) {
      ParseError(tp, "invalid included menu: %s", tp->value);
   } else {
      last = ParseMenuItem(start->subnodeHead, menu, last);
   }

   if(start) {
      ReleaseTokens(start);
   }

   return last;

}

/** Parse a key binding. */
void ParseKey(const TokenNode *tp) {

   const char *key;
   const char *code;
   const char *mask;
   const char *action;
   const char *command;
   KeyType k;
   int x;

   Assert(tp);

   mask = FindAttribute(tp->attributes, "mask");
   key = FindAttribute(tp->attributes, "key");
   code = FindAttribute(tp->attributes, "keycode");

   action = tp->value;
   if(JUNLIKELY(action == NULL)) {
      ParseError(tp, "no action specified for Key");
      return;
   }

   command = NULL;
   k = KEY_NONE;
   if(!strncmp(action, "exec:", 5)) {
      k = KEY_EXEC;
      command = action + 5;
   } else if(!strncmp(action, "root:", 5)) {
      k = KEY_ROOT;
      command = action + 5;
   } else {
      for(x = 0; KEY_MAP[x].name; x++) {
         if(!strcmp(action, KEY_MAP[x].name)) {
            k = KEY_MAP[x].key;
            break;
         }
      }
   }

   /* Insert the binding if it's valid. */
   if(JUNLIKELY(k == KEY_NONE)) {

      ParseError(tp, "invalid Key action: \"%s\"", action);

   } else {

      InsertBinding(k, mask, key, code, command);

   }

}

/** Parse window style. */
void ParseWindowStyle(const TokenNode *tp) {

   const TokenNode *np;

   Assert(tp);

   for(np = tp->subnodeHead; np; np = np->next) {
      switch(np->type) {
      case TOK_FONT:
         SetFont(FONT_BORDER, np->value);
         break;
      case TOK_WIDTH:
         settings.borderWidth = ParseUnsigned(np, np->value);
         break;
      case TOK_HEIGHT:
         settings.titleHeight = ParseUnsigned(np, np->value);
         break;
      case TOK_ACTIVE:
         ParseActiveWindowStyle(np);
         break;
      case TOK_INACTIVE:
         ParseInactiveWindowStyle(np);
         break;
      default:
         InvalidTag(np, TOK_WINDOWSTYLE);
         break;
      }
   }

}

/** Parse active window style information. */
void ParseActiveWindowStyle(const TokenNode *tp) {

   const TokenNode *np;

   Assert(tp);

   for(np = tp->subnodeHead; np; np = np->next) {
      switch(np->type) {
      case TOK_TEXT:
         SetColor(COLOR_TITLE_ACTIVE_FG, np->value);
         break;
      case TOK_TITLE:
         ParseGradient(np->value,
            COLOR_TITLE_ACTIVE_BG1, COLOR_TITLE_ACTIVE_BG2);
         break;
      case TOK_OUTLINE:
         SetColor(COLOR_BORDER_ACTIVE_LINE, np->value);
         break;
      case TOK_OPACITY:
         settings.activeClientOpacity = ParseOpacity(np, np->value);
         break;
      default:
         InvalidTag(np, TOK_ACTIVE);
         break;
      }
   }

}

/** Parse inactive window style information. */
void ParseInactiveWindowStyle(const TokenNode *tp) {

   const TokenNode *np;

   Assert(tp);

   for(np = tp->subnodeHead; np; np = np->next) {
      switch(np->type) {
      case TOK_TEXT:
         SetColor(COLOR_TITLE_FG, np->value);
         break;
      case TOK_TITLE:
         ParseGradient(np->value, COLOR_TITLE_BG1, COLOR_TITLE_BG2);
         break;
      case TOK_OUTLINE:
         SetColor(COLOR_BORDER_LINE, np->value);
         break;
      case TOK_OPACITY:
         settings.inactiveClientOpacity = ParseOpacity(tp, np->value);
         break;
      default:
         InvalidTag(np, TOK_INACTIVE);
         break;
      }
   }

}

/** Parse an include. */
void ParseInclude(const TokenNode *tp, int depth) {

   char *temp;

   Assert(tp);

   if(JUNLIKELY(!tp->value)) {

      ParseError(tp, "no include file specified");

   } else {

      temp = CopyString(tp->value);

      ExpandPath(&temp);

      if(JUNLIKELY(!ParseFile(temp, depth))) {
         ParseError(tp, "could not open included file %s", temp);
      }

      Release(temp);

   }

}

/** Parse desktop configuration. */
void ParseDesktops(const TokenNode *tp) {

   TokenNode *np;
   const char *width;
   const char *height;
   int desktop;

   Assert(tp);

   width = FindAttribute(tp->attributes, WIDTH_ATTRIBUTE);
   if(width != NULL) {
      settings.desktopWidth = ParseUnsigned(tp, width);
   }
   height = FindAttribute(tp->attributes, HEIGHT_ATTRIBUTE);
   if(height != NULL) {
      settings.desktopHeight = ParseUnsigned(tp, height);
   }
   settings.desktopCount = settings.desktopWidth * settings.desktopHeight;

   desktop = 0;
   for(np = tp->subnodeHead; np; np = np->next) {
      if(desktop >= settings.desktopCount) {
         break;
      }
      switch(np->type) {
      case TOK_BACKGROUND:
         ParseDesktopBackground(-1, np);
         break;
      case TOK_DESKTOP:
         ParseDesktop(desktop, np);
         desktop += 1;
         break;
      default:
         InvalidTag(np, TOK_DESKTOPS);
         break;
      }
   }

}

/** Parse a configuration for a specific desktop. */
void ParseDesktop(int desktop, const TokenNode *tp) {

   TokenNode *np;
   const char *attr;

   attr = FindAttribute(tp->attributes, NAME_ATTRIBUTE);
   if(attr) {
      SetDesktopName(desktop, attr);
   }

   for(np = tp->subnodeHead; np; np = np->next) {
      switch(np->type) {
      case TOK_BACKGROUND:
         ParseDesktopBackground(desktop, np);
         break;
      default:
         InvalidTag(np, TOK_DESKTOP);
         break;
      }
   }

}

/** Parse a background for a desktop. */
void ParseDesktopBackground(int desktop, const TokenNode *tp) {

   const char *type;

   type = FindAttribute(tp->attributes, TYPE_ATTRIBUTE);
   SetBackground(desktop, type, tp->value);

}

/** Parse task list style. */
void ParseTaskListStyle(const TokenNode *tp) {

   const char *temp;
   TokenNode *np;

   temp = FindAttribute(tp->attributes, INSERT_ATTRIBUTE);
   if(temp) {
      if(!strcmp(temp, "right")) {
         settings.taskInsertMode = INSERT_RIGHT;
      } else if(!strcmp(temp, "left")) {
         settings.taskInsertMode = INSERT_LEFT;
      } else {
         ParseError(tp, _("invalid insert mode: \"%s\""), temp);
         settings.taskInsertMode = INSERT_RIGHT;
      }
   }

   for(np = tp->subnodeHead; np; np = np->next) {
      switch(np->type) {
      case TOK_FONT:
         SetFont(FONT_TASK, np->value);
         break;
      case TOK_FOREGROUND:
         SetColor(COLOR_TASK_FG, np->value);
         break;
      case TOK_BACKGROUND:
         ParseGradient(np->value, COLOR_TASK_BG1, COLOR_TASK_BG2);
         break;
      case TOK_ACTIVEFOREGROUND:
         SetColor(COLOR_TASK_ACTIVE_FG, np->value);
         break;
      case TOK_ACTIVEBACKGROUND:
         ParseGradient(np->value, COLOR_TASK_ACTIVE_BG1, COLOR_TASK_ACTIVE_BG2);
         break;
      default:
         InvalidTag(np, TOK_TASKLISTSTYLE);
         break;
      }
   }

}

/** Parse tray style. */
void ParseTrayStyle(const TokenNode *tp) {

   const TokenNode *np;

   for(np = tp->subnodeHead; np; np = np->next) {
      switch(np->type) {
      case TOK_FONT:
         SetFont(FONT_TRAY, np->value);
         break;
      case TOK_BACKGROUND:
         ParseGradient(np->value, COLOR_TRAY_BG1, COLOR_TRAY_BG2);
         break;
      case TOK_FOREGROUND:
         SetColor(COLOR_TRAY_FG, np->value);
         break;
      case TOK_ACTIVEBACKGROUND:
         ParseGradient(np->value, COLOR_TRAY_ACTIVE_BG1, COLOR_TRAY_ACTIVE_BG2);
         break;
      case TOK_ACTIVEFOREGROUND:
         SetColor(COLOR_TRAY_ACTIVE_FG, np->value);
         break;
      case TOK_OPACITY:
         settings.trayOpacity = ParseOpacity(np, np->value);
         break;
      default:
         InvalidTag(np, TOK_TRAYSTYLE);
         break;
      }
   }

}

/** Parse tray. */
void ParseTray(const TokenNode *tp) {

   const TokenNode *np;
   const char *attr;
   TrayType *tray;

   Assert(tp);

   tray = CreateTray();

   attr = FindAttribute(tp->attributes, AUTOHIDE_ATTRIBUTE);
   if(attr && !strcmp(attr, TRUE_VALUE)) {
      SetAutoHideTray(tray, 1);
   } else {
      SetAutoHideTray(tray, 0);
   }

   attr = FindAttribute(tp->attributes, X_ATTRIBUTE);
   if(attr) {
      SetTrayX(tray, attr);
   }

   attr = FindAttribute(tp->attributes, Y_ATTRIBUTE);
   if(attr) {
      SetTrayY(tray, attr);
   }

   attr = FindAttribute(tp->attributes, WIDTH_ATTRIBUTE);
   if(attr) {
      SetTrayWidth(tray, attr);
   }

   attr = FindAttribute(tp->attributes, HEIGHT_ATTRIBUTE);
   if(attr) {
      SetTrayHeight(tray, attr);
   }

   attr = FindAttribute(tp->attributes, VALIGN_ATTRIBUTE);
   SetTrayVerticalAlignment(tray, attr);

   attr = FindAttribute(tp->attributes, HALIGN_ATTRIBUTE);
   SetTrayHorizontalAlignment(tray, attr);

   attr = FindAttribute(tp->attributes, LAYOUT_ATTRIBUTE);
   SetTrayLayout(tray, attr);

   attr = FindAttribute(tp->attributes, LAYER_ATTRIBUTE);
   if(attr) {
      const WinLayerType layer = ParseLayer(tp, attr);
      SetTrayLayer(tray, layer);
   }

   attr = FindAttribute(tp->attributes, BORDER_ATTRIBUTE);
   if(attr) {
      tray->border = ParseUnsigned(tp, attr);
   }

   for(np = tp->subnodeHead; np; np = np->next) {
      switch(np->type) {
      case TOK_PAGER:
         ParsePager(np, tray);
         break;
      case TOK_TASKLIST:
         ParseTaskList(np, tray);
         break;
      case TOK_SWALLOW:
         ParseSwallow(np, tray);
         break;
      case TOK_TRAYBUTTON:
         ParseTrayButton(np, tray);
         break;
      case TOK_CLOCK:
         ParseClock(np, tray);
         break;
      case TOK_DOCK:
         ParseDock(np, tray);
         break;
      case TOK_SPACER:
         ParseSpacer(np, tray);
         break;
      default:
         InvalidTag(np, TOK_TRAY);
         break;
      }
   }

}

/** Parse a pager tray component. */
void ParsePager(const TokenNode *tp, TrayType *tray) {

   TrayComponentType *cp;
   const char *temp;
   int labeled;

   Assert(tp);
   Assert(tray);

   labeled = 0;
   temp = FindAttribute(tp->attributes, LABELED_ATTRIBUTE);
   if(temp && !strcmp(temp, TRUE_VALUE)) {
      labeled = 1;
   }
   cp = CreatePager(labeled);
   AddTrayComponent(tray, cp);

}

/** Parse a task list tray component. */
void ParseTaskList(const TokenNode *tp, TrayType *tray) {

   TrayComponentType *cp;
   const char *temp;
   char border;

   Assert(tp);
   Assert(tray);

   temp = FindAttribute(tp->attributes, BORDER_ATTRIBUTE);
   if(temp && !strcmp(temp, FALSE_VALUE)) {
      border = 0;
   } else {
      border = 1;
   }

   cp = CreateTaskBar(border);
   AddTrayComponent(tray, cp);

   temp = FindAttribute(tp->attributes, MAX_WIDTH_ATTRIBUTE);
   if(temp) {
      SetMaxTaskBarItemWidth(cp, temp);
   }

}

/** Parse a swallow tray component. */
void ParseSwallow(const TokenNode *tp, TrayType *tray) {

   TrayComponentType *cp;
   const char *name;
   const char *temp;
   int width, height;

   Assert(tp);
   Assert(tray);

   name = FindAttribute(tp->attributes, NAME_ATTRIBUTE);
   if(name == NULL) {
      name = tp->value;
   }

   temp = FindAttribute(tp->attributes, WIDTH_ATTRIBUTE);
   if(temp) {
      width = ParseUnsigned(tp, temp);
   } else {
      width = 0;
   }

   temp = FindAttribute(tp->attributes, HEIGHT_ATTRIBUTE);
   if(temp) {
      height = ParseUnsigned(tp, temp);
   } else {
      height = 0;
   }

   cp = CreateSwallow(name, tp->value, width, height);
   if(cp) {
      AddTrayComponent(tray, cp);
   }

}

/** Parse a button tray component. */
void ParseTrayButton(const TokenNode *tp, TrayType *tray) {

   TrayComponentType *cp;
   const char *icon;
   const char *label;
   const char *popup;
   const char *temp;
   unsigned int width, height;
   char border;

   Assert(tp);
   Assert(tray);

   icon = FindAttribute(tp->attributes, ICON_ATTRIBUTE);
   label = FindAttribute(tp->attributes, LABEL_ATTRIBUTE);
   popup = FindAttribute(tp->attributes, POPUP_ATTRIBUTE);

   temp = FindAttribute(tp->attributes, BORDER_ATTRIBUTE);
   if(temp && !strcmp(temp, FALSE_VALUE)) {
      border = 0;
   } else {
      border = 1;
   }

   temp = FindAttribute(tp->attributes, WIDTH_ATTRIBUTE);
   if(temp) {
      width = ParseUnsigned(tp, temp);
   } else {
      width = 0;
   }

   temp = FindAttribute(tp->attributes, HEIGHT_ATTRIBUTE);
   if(temp) {
      height = ParseUnsigned(tp, temp);
   } else {
      height = 0;
   }

   cp = CreateTrayButton(icon, label, tp->value, popup, width, height, border);
   if(JLIKELY(cp)) {
      AddTrayComponent(tray, cp);
   }

}

/** Parse a clock tray component. */
void ParseClock(const TokenNode *tp, TrayType *tray) {

   TrayComponentType *cp;
   const char *format;
   const char *zone;
   const char *command;
   const char *temp;
   int width, height;

   Assert(tp);
   Assert(tray);

   format = FindAttribute(tp->attributes, FORMAT_ATTRIBUTE);

   zone = FindAttribute(tp->attributes, ZONE_ATTRIBUTE);

   if(tp->value && strlen(tp->value) > 0) {
      command = tp->value;
   } else {
      command = NULL;
   }

   temp = FindAttribute(tp->attributes, WIDTH_ATTRIBUTE);
   if(temp) {
      width = ParseUnsigned(tp, temp);
   } else {
      width = 0;
   }

   temp = FindAttribute(tp->attributes, HEIGHT_ATTRIBUTE);
   if(temp) {
      height = ParseUnsigned(tp, temp);
   } else {
      height = 0;
   }

   cp = CreateClock(format, zone, command, width, height);
   if(JLIKELY(cp)) {
      AddTrayComponent(tray, cp);
   }

}

/** Parse a dock tray component. */
void ParseDock(const TokenNode *tp, TrayType *tray) {

   TrayComponentType *cp;
   int width;
   char *str;

   Assert(tp);
   Assert(tray);

   str = FindAttribute(tp->attributes, WIDTH_ATTRIBUTE);
   if(str) {
      width = ParseUnsigned(tp, str);
   } else {
      width = 0;
   }

   cp = CreateDock(width);
   if(JLIKELY(cp)) {
      AddTrayComponent(tray, cp);
   }

}

/** Parse a spacer tray component. */
void ParseSpacer(const TokenNode *tp, TrayType *tray) {

   TrayComponentType *cp;
   int width;
   int height;
   char *str;

   Assert(tp);
   Assert(tray);

   /* Get the width. */
   str = FindAttribute(tp->attributes, WIDTH_ATTRIBUTE);
   if(str) {
      width = ParseUnsigned(tp, str);
   } else {
      width = 0;
   }

   /* Get the height. */
   str = FindAttribute(tp->attributes, HEIGHT_ATTRIBUTE);
   if(str) {
      height = ParseUnsigned(tp, str);
   } else {
      height = 0;
   }

   /* Create the spacer. */
   cp = CreateSpacer(width, height);
   if(JLIKELY(cp)) {
      AddTrayComponent(tray, cp);
   }

}

/** Parse pager style. */
void ParsePagerStyle(const TokenNode *tp) {

   const TokenNode *np;

   Assert(tp);

   for(np = tp->subnodeHead; np; np = np->next) {
      switch(np->type) {
      case TOK_OUTLINE:
         SetColor(COLOR_PAGER_OUTLINE, np->value);
         break;
      case TOK_FOREGROUND:
         SetColor(COLOR_PAGER_FG, np->value);
         break;
      case TOK_BACKGROUND:
         SetColor(COLOR_PAGER_BG, np->value);
         break;
      case TOK_ACTIVEFOREGROUND:
         SetColor(COLOR_PAGER_ACTIVE_FG, np->value);
         break;
      case TOK_ACTIVEBACKGROUND:
         SetColor(COLOR_PAGER_ACTIVE_BG, np->value);
         break;
      case TOK_FONT:
         SetFont(FONT_PAGER, np->value);
         break;
      case TOK_TEXT:
         SetColor(COLOR_PAGER_TEXT, np->value);
         break;
      default:
         InvalidTag(np, TOK_PAGERSTYLE);
         break;
      }
   }

}

/** Parse popup style. */
void ParsePopupStyle(const TokenNode *tp) {

   const TokenNode *np;
   const char *str;

   Assert(tp);

   str = FindAttribute(tp->attributes, ENABLED_ATTRIBUTE);
   if(str && !strcmp(str, FALSE_VALUE)) {
      settings.popupEnabled = 0;
   } else {
      settings.popupEnabled = 1;
   }

   str = FindAttribute(tp->attributes, DELAY_ATTRIBUTE);
   if(str) {
      settings.popupDelay = ParseUnsigned(tp, str);
   }

   for(np = tp->subnodeHead; np; np = np->next) {
      switch(np->type) {
      case TOK_FONT:
         SetFont(FONT_POPUP, np->value);
         break;
      case TOK_OUTLINE:
         SetColor(COLOR_POPUP_OUTLINE, np->value);
         break;
      case TOK_FOREGROUND:
         SetColor(COLOR_POPUP_FG, np->value);
         break;
      case TOK_BACKGROUND:
         SetColor(COLOR_POPUP_BG, np->value);
         break;
      default:
         InvalidTag(np, TOK_POPUPSTYLE);
         break;
      }
   }

}

/** Parse menu style. */
void ParseMenuStyle(const TokenNode *tp) {

   const TokenNode *np;

   Assert(tp);

   for(np = tp->subnodeHead; np; np = np->next) {
      switch(np->type) {
      case TOK_FONT:
         SetFont(FONT_MENU, np->value);
         break;
      case TOK_FOREGROUND:
         SetColor(COLOR_MENU_FG, np->value);
         break;
      case TOK_BACKGROUND:
         SetColor(COLOR_MENU_BG, np->value);
         break;
      case TOK_ACTIVEFOREGROUND:
         SetColor(COLOR_MENU_ACTIVE_FG, np->value);
         break;
      case TOK_ACTIVEBACKGROUND:
         ParseGradient(np->value, COLOR_MENU_ACTIVE_BG1, COLOR_MENU_ACTIVE_BG2);
         break;
      case TOK_OUTLINE:
         SetColor(COLOR_MENU_ACTIVE_OL, np->value);
         break;
      case TOK_OPACITY:
         settings.menuOpacity = ParseOpacity(np, np->value);
         break;
      default:
         InvalidTag(np, TOK_MENUSTYLE);
         break;
      }
   }

}

/** Parse clock style. */
void ParseClockStyle(const TokenNode *tp) {

   const TokenNode *np;

   Assert(tp);

   for(np = tp->subnodeHead; np; np = np->next) {
      switch(np->type) {
      case TOK_FONT:
         SetFont(FONT_CLOCK, np->value);
         break;
      case TOK_FOREGROUND:
         SetColor(COLOR_CLOCK_FG, np->value);
         break;
      case TOK_BACKGROUND:
         SetColor(COLOR_CLOCK_BG, np->value);
         break;
      default:
         InvalidTag(np, TOK_CLOCKSTYLE);
         break;
      }
   }

}

/** Parse tray button style. */
void ParseTrayButtonStyle(const TokenNode *tp)
{

   const TokenNode *np;

   Assert(tp);

   for(np = tp->subnodeHead; np; np = np->next) {
      switch(np->type) {
      case TOK_FONT:
         SetFont(FONT_TRAYBUTTON, np->value);
         break;
      case TOK_FOREGROUND:
         SetColor(COLOR_TRAYBUTTON_FG, np->value);
         break;
      case TOK_BACKGROUND:
         ParseGradient(np->value, COLOR_TRAYBUTTON_BG1, COLOR_TRAYBUTTON_BG2);
         break;
      case TOK_ACTIVEFOREGROUND:
         SetColor(COLOR_TRAYBUTTON_ACTIVE_FG, np->value);
         break;
      case TOK_ACTIVEBACKGROUND:
         ParseGradient(np->value, COLOR_TRAYBUTTON_ACTIVE_BG1,
                       COLOR_TRAYBUTTON_ACTIVE_BG2);
         break;
      default:
         InvalidTag(np, TOK_TRAYBUTTONSTYLE);
         break;
      }
   }

}

/** Parse an option group. */
void ParseGroup(const TokenNode *tp)
{

   const TokenNode *np;
   struct GroupType *group;

   Assert(tp);

   group = CreateGroup();

   for(np = tp->subnodeHead; np; np = np->next) {
      switch(np->type) {
      case TOK_CLASS:
         AddGroupClass(group, np->value);
         break;
      case TOK_NAME:
         AddGroupName(group, np->value);
         break;
      case TOK_OPTION:
         ParseGroupOption(np, group, np->value);
         break;
      default:
         InvalidTag(np, TOK_GROUP);
         break;
      }
   }

}

/** Parse a option group option. */
void ParseGroupOption(const TokenNode *tp, struct GroupType *group,
                      const char *option)
{

   int x;

   if(!option) {
      return;
   }

   for(x = 0; OPTION_MAP[x].name; x++) {
      if(!strcmp(option, OPTION_MAP[x].name)) {
         AddGroupOption(group, OPTION_MAP[x].option);
         return;
      }
   }

   /* These options have arguments and so we handled them separately. */
   if(!strncmp(option, "layer:", 6)) {
      const WinLayerType layer = ParseLayer(tp, option + 6);
      AddGroupOptionUnsigned(group, OPTION_LAYER, layer);
   } else if(!strncmp(option, "desktop:", 8)) {
      const unsigned int desktop = (unsigned int)atoi(option + 8);
      AddGroupOptionUnsigned(group, OPTION_DESKTOP, desktop);
   } else if(!strncmp(option, "icon:", 5)) {
      AddGroupOptionString(group, OPTION_ICON, option + 5);
   } else if(!strncmp(option, "opacity:", 8)) {
      const unsigned int opacity = ParseOpacity(tp, option + 8);
      AddGroupOptionUnsigned(group, OPTION_OPACITY, opacity);
   } else {
      ParseError(tp, "invalid Group Option: %s", option);
   }

}

/** Parse a color which may be a gradient. */
void ParseGradient(const char *value, ColorType a, ColorType b)
{

   const char *sep;
   char *temp;
   int len;

   /* Find the separator. */
   sep = strchr(value, ':');

   if(!sep) {

      /* Only one color given - use the same color for both. */
      SetColor(a, value);
      SetColor(b, value);

   } else {

      /* Two colors. */

      /* Get the first color. */
      len = (int)(sep - value);
      temp = AllocateStack(len + 1);
      memcpy(temp, value, len);
      temp[len] = 0;
      SetColor(a, temp);
      ReleaseStack(temp);

      /* Get the second color. */
      len = strlen(sep + 1);
      temp = AllocateStack(len + 1);
      memcpy(temp, sep + 1, len);
      temp[len] = 0;
      SetColor(b, temp);
      ReleaseStack(temp);

   }

}

/** Find an attribute in a list of attributes. */
char *FindAttribute(AttributeNode *ap, const char *name)
{

   while(ap) {
      if(!strcmp(name, ap->name)) {
         return ap->value;
      }
      ap = ap->next;
   }

   return NULL;
}

/** Read a file. */
char *ReadFile(FILE *fd)
{

   const int BLOCK_SIZE = 1 << 14;  // Start at 16k.

   char *buffer;
   int len, max;
   int ch;

   len = 0;
   max = BLOCK_SIZE;
   buffer = Allocate(max + 1);

   for(;;) {
      ch = fgetc(fd);
      if(JUNLIKELY(ch == EOF || ch == 0)) {
         break;
      }
      buffer[len++] = ch;
      if(JUNLIKELY(len >= max)) {
         max *= 2;
         if(JUNLIKELY(max < 0)) {
            /* File is too big. */
            break;
         }
         buffer = Reallocate(buffer, max + 1);
      }
   }
   buffer[len] = 0;

   return buffer;

}

/** Parse an unsigned integer. */
unsigned int ParseUnsigned(const TokenNode *tp, const char *str)
{
   const long value = strtol(str, NULL, 0);
   if(JUNLIKELY(value < 0 || value > UINT_MAX)) {
      ParseError(tp, _("invalid setting: %s"), str);
      return 0;
   } else {
      return (unsigned int)value;
   }
}

/** Parse opacity (a float between 0.0 and 1.0). */
unsigned int ParseOpacity(const TokenNode *tp, const char *str)
{
   const float value = ParseFloat(str);
   if(JUNLIKELY(value <= 0.0 || value > 1.0)) {
      ParseError(tp, _("invalid opacity: %s"), str);
      return UINT_MAX;
   } else if(value == 1.0) {
      return UINT_MAX;
   } else {
      return (unsigned int)(value * UINT_MAX);
   }
}

/** Parse layer. */
WinLayerType ParseLayer(const TokenNode *tp, const char *str)
{
   if(!strcmp(str, "below")) {
      return LAYER_BELOW;
   } else if(!strcmp(str, "normal")) {
      return LAYER_NORMAL;
   } else if(!strcmp(str, "above")) {
      return LAYER_ABOVE;
   } else {
      ParseError(tp, _("invalid layer: %s"), str);
      return LAYER_NORMAL;
   }
}

/** Parse status window type. */
StatusWindowType ParseStatusWindowType(const TokenNode *tp, const char *str)
{
   if(!strcmp(str, "off")) {
      return SW_OFF;
   } else if(!strcmp(str, SCREEN_STRING)) {
      return SW_SCREEN;
   } else if(!strcmp(str, "window")) {
      return SW_WINDOW;
   } else if(!strcmp(str, "corner")) {
      return SW_CORNER;
   } else {
      ParseError(tp, _("invalid status window type: %s"), str);
      return SW_SCREEN;
   }
}

/** Display an invalid tag error message. */
void InvalidTag(const TokenNode *tp, TokenType parent)
{

   ParseError(tp, _("invalid tag in %s: %s"),
              GetTokenTypeName(parent), GetTokenName(tp));

}

/** Display a parser error. */
void ParseError(const TokenNode *tp, const char *str, ...)
{

   va_list ap;

   static const char *FILE_MESSAGE = "%s[%u]";

   char *msg;

   va_start(ap, str);

   if(tp) {
      msg = Allocate(strlen(FILE_MESSAGE) + strlen(tp->fileName) + 1);
      sprintf(msg, FILE_MESSAGE, tp->fileName, tp->line);
   } else {
      msg = CopyString(_("configuration error"));
   }

   WarningVA(msg, str, ap);

   Release(msg);

   va_end(ap);

}

