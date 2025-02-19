/* -*- c-basic-offset: 8 -*-
   rdesktop: A Remote Desktop Protocol client.
   User interface services - X keyboard mapping

   Copyright (C) Matthew Chapman <matthewc.unsw.edu.au> 1999-2008
   Copyright 2003-2008 Peter Astrand <astrand@cendio.se> for Cendio AB

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifdef RDP2VNC
#include "vnc/x11stubs.h"
#else
#include <X11/Xlib.h>
#include <X11/keysym.h>
#endif

#include <ctype.h>
#include <limits.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include "rdesktop.h"
#include "scancodes.h"
#include "l2wscancodes.h"

#define KEYMAP_SIZE 0xffff+1
#define KEYMAP_MASK 0xffff
#define KEYMAP_MAX_LINE_LENGTH 80

extern Display *g_display;
extern Window g_wnd;
extern char g_keymapname[16];
extern unsigned int g_keylayout;
extern int g_keyboard_type;
extern int g_keyboard_subtype;
extern int g_keyboard_functionkeys;
extern int g_win_button_size;
extern RD_BOOL g_enable_compose;
extern RD_BOOL g_use_rdp5;
extern RD_BOOL g_numlock_sync;
extern RD_BOOL g_ind_raw_converter;
extern int scancodes_table[];

static RD_BOOL keymap_loaded;
static key_translation *keymap[KEYMAP_SIZE];
static KeySym keypress_keysyms[256];
static int min_keycode;
static uint16 remote_modifier_state = 0;
static uint16 saved_remote_modifier_state = 0;
static uint32 vkmenu, vkcontrol, vklshift, vkrshift, vknumlock;

static void update_modifier_state(uint8 scancode, RD_BOOL pressed);

/* Free key_translation structure, including linked list */
static void
free_key_translation(key_translation * ptr)
{
	key_translation *next;

	while (ptr)
	{
		next = ptr->next;
		xfree(ptr);
		ptr = next;
	}
}

static void
add_to_keymap(char *keyname, uint8 scancode, uint16 modifiers, char *mapname)
{
	KeySym keysym;
	key_translation *tr;

	keysym = XStringToKeysym(keyname);
	if (keysym == NoSymbol)
	{
		DEBUG_KBD(("Bad keysym \"%s\" in keymap %s (ignoring)\n", keyname, mapname));
		return;
	}

	DEBUG_KBD(("Adding translation, keysym=0x%x, scancode=0x%x, "
		   "modifiers=0x%x\n", (unsigned int) keysym, scancode, modifiers));

	tr = (key_translation *) xmalloc(sizeof(key_translation));
	memset(tr, 0, sizeof(key_translation));
	tr->scancode = scancode;
	tr->modifiers = modifiers;
	free_key_translation(keymap[keysym & KEYMAP_MASK]);
	keymap[keysym & KEYMAP_MASK] = tr;

	return;
}

static void
add_sequence(char *rest, char *mapname)
{
	KeySym keysym;
	key_translation *tr, **prev_next;
	size_t chars;
	char keyname[KEYMAP_MAX_LINE_LENGTH];

	/* Skip over whitespace after the sequence keyword */
	chars = strspn(rest, " \t");
	rest += chars;

	/* Fetch the keysym name */
	chars = strcspn(rest, " \t\0");
	STRNCPY(keyname, rest, chars + 1);
	rest += chars;

	keysym = XStringToKeysym(keyname);
	if (keysym == NoSymbol)
	{
		DEBUG_KBD(("Bad keysym \"%s\" in keymap %s (ignoring line)\n", keyname, mapname));
		return;
	}


	DEBUG_KBD(("Adding sequence for keysym (0x%lx, %s) -> ", keysym, keyname));

	free_key_translation(keymap[keysym & KEYMAP_MASK]);
	prev_next = &keymap[keysym & KEYMAP_MASK];

	while (*rest)
	{
		/* Skip whitespace */
		chars = strspn(rest, " \t");
		rest += chars;

		/* Fetch the keysym name */
		chars = strcspn(rest, " \t\0");
		STRNCPY(keyname, rest, chars + 1);
		rest += chars;

		keysym = XStringToKeysym(keyname);
		if (keysym == NoSymbol)
		{
			DEBUG_KBD(("Bad keysym \"%s\" in keymap %s (ignoring line)\n", keyname,
				   mapname));
			return;
		}

		/* Allocate space for key_translation structure */
		tr = (key_translation *) xmalloc(sizeof(key_translation));
		memset(tr, 0, sizeof(key_translation));
		*prev_next = tr;
		prev_next = &tr->next;
		tr->seq_keysym = keysym;

		DEBUG_KBD(("0x%x, ", (unsigned int) keysym));
	}
	DEBUG_KBD(("\n"));
}

RD_BOOL
xkeymap_from_locale(const char *locale)
{
	char *str, *ptr;
	FILE *fp;

	/* Create a working copy */
	str = xstrdup(locale);

	/* Truncate at dot and at */
	ptr = strrchr(str, '.');
	if (ptr)
		*ptr = '\0';
	ptr = strrchr(str, '@');
	if (ptr)
		*ptr = '\0';

	/* Replace _ with - */
	ptr = strrchr(str, '_');
	if (ptr)
		*ptr = '-';

	/* Convert to lowercase */
	ptr = str;
	while (*ptr)
	{
		*ptr = tolower((int) *ptr);
		ptr++;
	}

	/* Try to open this keymap (da-dk) */
	fp = xkeymap_open(str);
	if (fp == NULL)
	{
		/* Truncate at dash */
		ptr = strrchr(str, '-');
		if (ptr)
			*ptr = '\0';

		/* Try the short name (da) */
		fp = xkeymap_open(str);
	}

	if (fp)
	{
		fclose(fp);
		STRNCPY(g_keymapname, str, sizeof(g_keymapname));
		xfree(str);
		return True;
	}

	xfree(str);
	return False;
}


/* Joins two path components. The result should be freed with
   xfree(). */
static char *
pathjoin(const char *a, const char *b)
{
	char *result;
	result = xmalloc(PATH_MAX * 2 + 1);

	if (b[0] == '/')
	{
		strncpy(result, b, PATH_MAX);
	}
	else
	{
		strncpy(result, a, PATH_MAX);
		strcat(result, "/");
		strncat(result, b, PATH_MAX);
	}
	return result;
}

/* Try to open a keymap with fopen() */
FILE *
xkeymap_open(const char *filename)
{
	char *path1, *path2;
	char *home;
	FILE *fp;

	/* Try ~/.rdesktop/keymaps */
	home = getenv("HOME");
	if (home)
	{
		path1 = pathjoin(home, ".rdesktop/keymaps");
		path2 = pathjoin(path1, filename);
		xfree(path1);
		fp = fopen(path2, "r");
		xfree(path2);
		if (fp)
			return fp;
	}

	/* Try KEYMAP_PATH */
	path1 = pathjoin(KEYMAP_PATH, filename);
	fp = fopen(path1, "r");
	xfree(path1);
	if (fp)
		return fp;

	/* Try current directory, in case we are running from the source
	   tree */
	path1 = pathjoin("keymaps", filename);
	fp = fopen(path1, "r");
	xfree(path1);
	if (fp)
		return fp;

	return NULL;
}

static RD_BOOL
xkeymap_read(char *mapname)
{
	FILE *fp;
	char line[KEYMAP_MAX_LINE_LENGTH];
	unsigned int line_num = 0;
	unsigned int line_length = 0;
	char *keyname, *p;
	char *line_rest;
	uint8 scancode;
	uint16 modifiers;

	fp = xkeymap_open(mapname);
	if (fp == NULL)
	{
		error("Failed to open keymap %s\n", mapname);
		return False;
	}

	/* FIXME: More tolerant on white space */
	while (fgets(line, sizeof(line), fp) != NULL)
	{
		line_num++;

		/* Replace the \n with \0 */
		p = strchr(line, '\n');
		if (p != NULL)
			*p = 0;

		line_length = strlen(line);

		/* Completely empty line */
		if (strspn(line, " \t\n\r\f\v") == line_length)
		{
			continue;
		}

		/* Include */
		if (str_startswith(line, "include "))
		{
			if (!xkeymap_read(line + sizeof("include ") - 1))
				return False;
			continue;
		}

		/* map */
		if (str_startswith(line, "map "))
		{
			g_keylayout = strtoul(line + sizeof("map ") - 1, NULL, 16);
			DEBUG_KBD(("Keylayout 0x%x\n", g_keylayout));
			continue;
		}

		/* compose */
		if (str_startswith(line, "enable_compose"))
		{
			DEBUG_KBD(("Enabling compose handling\n"));
			g_enable_compose = True;
			continue;
		}

		/* sequence */
		if (str_startswith(line, "sequence"))
		{
			add_sequence(line + sizeof("sequence") - 1, mapname);
			continue;
		}

		/* keyboard_type */
		if (str_startswith(line, "keyboard_type "))
		{
			g_keyboard_type = strtol(line + sizeof("keyboard_type ") - 1, NULL, 16);
			DEBUG_KBD(("keyboard_type 0x%x\n", g_keyboard_type));
			continue;
		}

		/* keyboard_subtype */
		if (str_startswith(line, "keyboard_subtype "))
		{
			g_keyboard_subtype =
				strtol(line + sizeof("keyboard_subtype ") - 1, NULL, 16);
			DEBUG_KBD(("keyboard_subtype 0x%x\n", g_keyboard_subtype));
			continue;
		}

		/* keyboard_functionkeys */
		if (str_startswith(line, "keyboard_functionkeys "))
		{
			g_keyboard_functionkeys =
				strtol(line + sizeof("keyboard_functionkeys ") - 1, NULL, 16);
			DEBUG_KBD(("keyboard_functionkeys 0x%x\n", g_keyboard_functionkeys));
			continue;
		}

		/* Comment */
		if (line[0] == '#')
		{
			continue;
		}

		/* Normal line */
		keyname = line;
		p = strchr(line, ' ');
		if (p == NULL)
		{
			error("Bad line %d in keymap %s\n", line_num, mapname);
			continue;
		}
		else
		{
			*p = 0;
		}

		/* scancode */
		p++;
		scancode = strtol(p, &line_rest, 16);

		/* flags */
		/* FIXME: Should allow case-insensitive flag names. 
		   Fix by using lex+yacc... */
		modifiers = 0;
		if (strstr(line_rest, "altgr"))
		{
			MASK_ADD_BITS(modifiers, MapAltGrMask);
		}

		if (strstr(line_rest, "shift"))
		{
			MASK_ADD_BITS(modifiers, MapLeftShiftMask);
		}

		if (strstr(line_rest, "numlock"))
		{
			MASK_ADD_BITS(modifiers, MapNumLockMask);
		}

		if (strstr(line_rest, "localstate"))
		{
			MASK_ADD_BITS(modifiers, MapLocalStateMask);
		}

		if (strstr(line_rest, "inhibit"))
		{
			MASK_ADD_BITS(modifiers, MapInhibitMask);
		}

		add_to_keymap(keyname, scancode, modifiers, mapname);

		if (strstr(line_rest, "addupper"))
		{
			/* Automatically add uppercase key, with same modifiers 
			   plus shift */
			for (p = keyname; *p; p++)
				*p = toupper((int) *p);
			MASK_ADD_BITS(modifiers, MapLeftShiftMask);
			add_to_keymap(keyname, scancode, modifiers, mapname);
		}
	}

	fclose(fp);
	return True;
}


/* Before connecting and creating UI */
void
xkeymap_init(void)
{
	unsigned int max_keycode;

	if (strcmp(g_keymapname, "none"))
	{
		if (xkeymap_read(g_keymapname))
			keymap_loaded = True;
	}

	XDisplayKeycodes(g_display, &min_keycode, (int *) &max_keycode);
}

static void
send_winkey(uint32 ev_time, RD_BOOL pressed, RD_BOOL leftkey)
{
	uint8 winkey;

	if (leftkey)
		winkey = SCANCODE_CHAR_LWIN;
	else
		winkey = SCANCODE_CHAR_RWIN;

	if (pressed)
	{
		if (g_use_rdp5)
		{
			rdp_send_scancode(ev_time, RDP_KEYPRESS, winkey);
		}
		else
		{
			/* RDP4 doesn't support winkey. Fake with Ctrl-Esc */
			rdp_send_scancode(ev_time, RDP_KEYPRESS, SCANCODE_CHAR_LCTRL);
			rdp_send_scancode(ev_time, RDP_KEYPRESS, SCANCODE_CHAR_ESC);
		}
	}
	else
	{
		/* key released */
		if (g_use_rdp5)
		{
			rdp_send_scancode(ev_time, RDP_KEYRELEASE, winkey);
		}
		else
		{
			rdp_send_scancode(ev_time, RDP_KEYRELEASE, SCANCODE_CHAR_ESC);
			rdp_send_scancode(ev_time, RDP_KEYRELEASE, SCANCODE_CHAR_LCTRL);
		}
	}
}

static void
reset_winkey(uint32 ev_time)
{
	if (g_use_rdp5)
	{
		/* For some reason, it seems to suffice to release
		 *either* the left or right winkey. */
		rdp_send_scancode(ev_time, RDP_KEYRELEASE, SCANCODE_CHAR_LWIN);
	}
}


void
set_keypress_keysym(unsigned int keycode, KeySym keysym)
{
	if (keycode < 8 || keycode > 255)
		return;
	keypress_keysyms[keycode] = keysym;
}


KeySym
reset_keypress_keysym(unsigned int keycode, KeySym keysym)
{
	KeySym ks;
	if (keycode < 8 || keycode > 255)
		return keysym;
	ks = keypress_keysyms[keycode];
	if (ks != 0)
	{
		keypress_keysyms[keycode] = 0;
	}
	else
	{
		ks = keysym;
	}

	return ks;
}


/* Handle special key combinations */
RD_BOOL
handle_special_keys(uint32 keysym, unsigned int state, uint32 ev_time, RD_BOOL pressed)
{
	switch (keysym)
	{
		case XK_Return:
			if ((get_key_state(state, XK_Alt_L) || get_key_state(state, XK_Alt_R))
			    && (get_key_state(state, XK_Control_L)
				|| get_key_state(state, XK_Control_R)))
			{
				/* Ctrl-Alt-Enter: toggle full screen */


                                /* harry */
                                
/*				if (pressed)
					xwin_toggle_fullscreen(); */

                                /* harry */
                                
				return True;
			}
			break;

		case XK_Break:
			/* Send Break sequence E0 46 E0 C6 */
			if (pressed)
			{
				rdp_send_scancode(ev_time, RDP_KEYPRESS,
						  (SCANCODE_EXTENDED | 0x46));
				rdp_send_scancode(ev_time, RDP_KEYPRESS,
						  (SCANCODE_EXTENDED | 0xc6));
			}
			/* No release sequence */
			return True;
			break;

		case XK_Pause:
			/* According to MS Keyboard Scan Code
			   Specification, pressing Pause should result
			   in E1 1D 45 E1 9D C5. I'm not exactly sure
			   of how this is supposed to be sent via
			   RDP. The code below seems to work, but with
			   the side effect that Left Ctrl stays
			   down. Therefore, we release it when Pause
			   is released. */
			if (pressed)
			{
				rdp_send_input(ev_time, RDP_INPUT_SCANCODE, RDP_KEYPRESS, 0xe1, 0);
				rdp_send_input(ev_time, RDP_INPUT_SCANCODE, RDP_KEYPRESS, 0x1d, 0);
				rdp_send_input(ev_time, RDP_INPUT_SCANCODE, RDP_KEYPRESS, 0x45, 0);
				rdp_send_input(ev_time, RDP_INPUT_SCANCODE, RDP_KEYPRESS, 0xe1, 0);
				rdp_send_input(ev_time, RDP_INPUT_SCANCODE, RDP_KEYPRESS, 0x9d, 0);
				rdp_send_input(ev_time, RDP_INPUT_SCANCODE, RDP_KEYPRESS, 0xc5, 0);
			}
			else
			{
				/* Release Left Ctrl */
				rdp_send_input(ev_time, RDP_INPUT_SCANCODE, RDP_KEYRELEASE,
					       0x1d, 0);
			}
			return True;
			break;

		case XK_Meta_L:	/* Windows keys */
		case XK_Super_L:
		case XK_Hyper_L:
			send_winkey(ev_time, pressed, True);
			return True;
			break;

		case XK_Meta_R:
		case XK_Super_R:
		case XK_Hyper_R:
			send_winkey(ev_time, pressed, False);
			return True;
			break;

		case XK_space:
			/* Prevent access to the Windows system menu in single app mode */
			if (g_win_button_size
			    && (get_key_state(state, XK_Alt_L) || get_key_state(state, XK_Alt_R)))
				return True;
			break;

		case XK_Num_Lock:
			/* Synchronize on key release */
			if (g_numlock_sync && !pressed)
				rdp_send_input(0, RDP_INPUT_SYNCHRONIZE, 0,
					       ui_get_numlock_state(read_keyboard_state()), 0);

			/* Inhibit */
			return True;
			break;
		case XK_Overlay1_Enable:
			/* Toggle SeamlessRDP */
			if (pressed)
				ui_seamless_toggle();
			break;

	}
	return False;
}


key_translation
xkeymap_translate_key(uint32 keysym, unsigned int keycode, unsigned int state)
{
	key_translation tr = { 0, 0, 0, 0 };
	key_translation *ptr;

	ptr = keymap[keysym & KEYMAP_MASK];
	if (ptr)
	{
		tr = *ptr;
		if (tr.seq_keysym == 0)	/* Normal scancode translation */
		{
			if (MASK_HAS_BITS(tr.modifiers, MapInhibitMask))
			{
				DEBUG_KBD(("Inhibiting key\n"));
				tr.scancode = 0;
				return tr;
			}

			if (MASK_HAS_BITS(tr.modifiers, MapLocalStateMask))
			{
				/* The modifiers to send for this key should be obtained
				   from the local state. Currently, only shift is implemented. */
				if (MASK_HAS_BITS(state, ShiftMask))
				{
					tr.modifiers = MapLeftShiftMask;
				}
			}

			/* Windows interprets CapsLock+Ctrl+key
			   differently from Shift+Ctrl+key. Since we
			   are simulating CapsLock with Shifts, things
			   like Ctrl+f with CapsLock on breaks. To
			   solve this, we are releasing Shift if Ctrl
			   is on, but only if Shift isn't physically pressed. */
			if (MASK_HAS_BITS(tr.modifiers, MapShiftMask)
			    && MASK_HAS_BITS(remote_modifier_state, MapCtrlMask)
			    && !MASK_HAS_BITS(state, ShiftMask))
			{
				DEBUG_KBD(("Non-physical Shift + Ctrl pressed, releasing Shift\n"));
				MASK_REMOVE_BITS(tr.modifiers, MapShiftMask);
			}

			DEBUG_KBD(("Found scancode translation, scancode=0x%x, modifiers=0x%x\n",
				   tr.scancode, tr.modifiers));
		}
	}
	else
	{
		if (keymap_loaded)
			warning("No translation for (keysym 0x%lx, %s)\n", keysym,
				get_ksname(keysym));

		/* not in keymap, try to interpret the raw scancode */
		if (((int) keycode >= min_keycode) && (keycode <= 0x60))
		{
			tr.scancode = keycode - min_keycode;

			/* The modifiers to send for this key should be
			   obtained from the local state. Currently, only
			   shift is implemented. */
			if (MASK_HAS_BITS(state, ShiftMask))
			{
				tr.modifiers = MapLeftShiftMask;
			}

			DEBUG_KBD(("Sending guessed scancode 0x%x\n", tr.scancode));
		}
		else
		{
			DEBUG_KBD(("No good guess for keycode 0x%x found\n", keycode));
		}
	}

	return tr;
}

static RD_BOOL
is_modifier(uint8 scancode)
{
	switch (scancode)
	{
		case SCANCODE_CHAR_LSHIFT:
		case SCANCODE_CHAR_RSHIFT:
		case SCANCODE_CHAR_LCTRL:
		case SCANCODE_CHAR_RCTRL:
		case SCANCODE_CHAR_LALT:
		case SCANCODE_CHAR_RALT:
		case SCANCODE_CHAR_LWIN:
		case SCANCODE_CHAR_RWIN:
		case SCANCODE_CHAR_NUMLOCK:
			return True;
		default:
			break;
	}
	return False;
}


void
xkeymap_send_keys(uint32 keysym, unsigned int keycode, unsigned int state, uint32 ev_time,
		  RD_BOOL pressed, uint8 nesting)
{
	key_translation tr, *ptr;
	tr = xkeymap_translate_key(keysym, keycode, state);

	if (tr.seq_keysym == 0)
	{
		/* Scancode translation */
		if (tr.scancode == 0)
			return;

		save_remote_modifiers(tr.scancode);
		ensure_remote_modifiers(ev_time, tr);
		rdp_send_scancode(ev_time, pressed ? RDP_KEYPRESS : RDP_KEYRELEASE, tr.scancode);
		restore_remote_modifiers(ev_time, tr.scancode);
		return;
	}

	/* Sequence, only on key down */
	if (pressed)
	{
		ptr = &tr;
		do
		{
			DEBUG_KBD(("Handling sequence element, keysym=0x%x\n",
				   (unsigned int) ptr->seq_keysym));

			if (nesting++ > 32)
			{
				error("Sequence nesting too deep\n");
				return;
			}

			xkeymap_send_keys(ptr->seq_keysym, keycode, state, ev_time, True, nesting);
			xkeymap_send_keys(ptr->seq_keysym, keycode, state, ev_time, False, nesting);
			ptr = ptr->next;
		}
		while (ptr);
	}
}

uint16
xkeymap_translate_button(unsigned int button)
{
	switch (button)
	{
		case Button1:	/* left */
			return MOUSE_FLAG_BUTTON1;
		case Button2:	/* middle */
			return MOUSE_FLAG_BUTTON3;
		case Button3:	/* right */
			return MOUSE_FLAG_BUTTON2;
		case Button4:	/* wheel up */
			return MOUSE_FLAG_BUTTON4;
		case Button5:	/* wheel down */
			return MOUSE_FLAG_BUTTON5;
	}

	return 0;
}

char *
get_ksname(uint32 keysym)
{
	char *ksname = NULL;

	if (keysym == NoSymbol)
		ksname = "NoSymbol";
	else if (!(ksname = XKeysymToString(keysym)))
		ksname = "(no name)";

	return ksname;
}

void
save_remote_modifiers(uint8 scancode)
{
	if (is_modifier(scancode))
		return;

	saved_remote_modifier_state = remote_modifier_state;
}

void
restore_remote_modifiers(uint32 ev_time, uint8 scancode)
{
	key_translation dummy = { };

	if (is_modifier(scancode))
		return;

	dummy.scancode = 0;
	dummy.modifiers = saved_remote_modifier_state;
	ensure_remote_modifiers(ev_time, dummy);
}

void
ensure_remote_modifiers(uint32 ev_time, key_translation tr)
{
	/* If this key is a modifier, do nothing */
	if (is_modifier(tr.scancode))
		return;

	if (!g_numlock_sync)
	{
		/* NumLock */
		if (MASK_HAS_BITS(tr.modifiers, MapNumLockMask)
		    != MASK_HAS_BITS(remote_modifier_state, MapNumLockMask))
		{
			/* The remote modifier state is not correct */
			uint16 new_remote_state;

			if (MASK_HAS_BITS(tr.modifiers, MapNumLockMask))
			{
				DEBUG_KBD(("Remote NumLock state is incorrect, activating NumLock.\n"));
				new_remote_state = KBD_FLAG_NUMLOCK;
				remote_modifier_state = MapNumLockMask;
			}
			else
			{
				DEBUG_KBD(("Remote NumLock state is incorrect, deactivating NumLock.\n"));
				new_remote_state = 0;
				remote_modifier_state = 0;
			}

			rdp_send_input(0, RDP_INPUT_SYNCHRONIZE, 0, new_remote_state, 0);
		}
	}


	/* Shift. Left shift and right shift are treated as equal; either is fine. */
	if (MASK_HAS_BITS(tr.modifiers, MapShiftMask)
	    != MASK_HAS_BITS(remote_modifier_state, MapShiftMask))
	{
		/* The remote modifier state is not correct */
		if (MASK_HAS_BITS(tr.modifiers, MapLeftShiftMask))
		{
			/* Needs left shift. Send down. */
			rdp_send_scancode(ev_time, RDP_KEYPRESS, SCANCODE_CHAR_LSHIFT);
		}
		else if (MASK_HAS_BITS(tr.modifiers, MapRightShiftMask))
		{
			/* Needs right shift. Send down. */
			rdp_send_scancode(ev_time, RDP_KEYPRESS, SCANCODE_CHAR_RSHIFT);
		}
		else
		{
			/* Should not use this modifier. Send up for shift currently pressed. */
			if (MASK_HAS_BITS(remote_modifier_state, MapLeftShiftMask))
				/* Left shift is down */
				rdp_send_scancode(ev_time, RDP_KEYRELEASE, SCANCODE_CHAR_LSHIFT);
			else
				/* Right shift is down */
				rdp_send_scancode(ev_time, RDP_KEYRELEASE, SCANCODE_CHAR_RSHIFT);
		}
	}

	/* AltGr */
	if (MASK_HAS_BITS(tr.modifiers, MapAltGrMask)
	    != MASK_HAS_BITS(remote_modifier_state, MapAltGrMask))
	{
		/* The remote modifier state is not correct */
		if (MASK_HAS_BITS(tr.modifiers, MapAltGrMask))
		{
			/* Needs this modifier. Send down. */
			rdp_send_scancode(ev_time, RDP_KEYPRESS, SCANCODE_CHAR_RALT);
		}
		else
		{
			/* Should not use this modifier. Send up. */
			rdp_send_scancode(ev_time, RDP_KEYRELEASE, SCANCODE_CHAR_RALT);
		}
	}


}


unsigned int
read_keyboard_state()
{
#ifdef RDP2VNC
	return 0;
#else
	unsigned int state;
	Window wdummy;
	int dummy;

	XQueryPointer(g_display, g_wnd, &wdummy, &wdummy, &dummy, &dummy, &dummy, &dummy, &state);
	return state;
#endif
}


uint16
ui_get_numlock_state(unsigned int state)
{
	uint16 numlock_state = 0;

	if (get_key_state(state, XK_Num_Lock))
		numlock_state = KBD_FLAG_NUMLOCK;

	return numlock_state;
}


void
reset_modifier_keys()
{
	unsigned int state = read_keyboard_state();

	/* reset keys */
	uint32 ev_time;
	ev_time = time(NULL);

	if (MASK_HAS_BITS(remote_modifier_state, MapLeftShiftMask)
	    && !get_key_state(state, XK_Shift_L))
		rdp_send_scancode(ev_time, RDP_KEYRELEASE, SCANCODE_CHAR_LSHIFT);

	if (MASK_HAS_BITS(remote_modifier_state, MapRightShiftMask)
	    && !get_key_state(state, XK_Shift_R))
		rdp_send_scancode(ev_time, RDP_KEYRELEASE, SCANCODE_CHAR_RSHIFT);

	if (MASK_HAS_BITS(remote_modifier_state, MapLeftCtrlMask)
	    && !get_key_state(state, XK_Control_L))
		rdp_send_scancode(ev_time, RDP_KEYRELEASE, SCANCODE_CHAR_LCTRL);

	if (MASK_HAS_BITS(remote_modifier_state, MapRightCtrlMask)
	    && !get_key_state(state, XK_Control_R))
		rdp_send_scancode(ev_time, RDP_KEYRELEASE, SCANCODE_CHAR_RCTRL);

	if (MASK_HAS_BITS(remote_modifier_state, MapLeftAltMask) && !get_key_state(state, XK_Alt_L))
		rdp_send_scancode(ev_time, RDP_KEYRELEASE, SCANCODE_CHAR_LALT);

	if (MASK_HAS_BITS(remote_modifier_state, MapRightAltMask) &&
	    !get_key_state(state, XK_Alt_R) && !get_key_state(state, XK_Mode_switch)
	    && !get_key_state(state, XK_ISO_Level3_Shift))
		rdp_send_scancode(ev_time, RDP_KEYRELEASE, SCANCODE_CHAR_RALT);

	reset_winkey(ev_time);
        vknumlock = get_key_state(state, XK_Num_Lock);

	if (g_numlock_sync)
		rdp_send_input(ev_time, RDP_INPUT_SYNCHRONIZE, 0, ui_get_numlock_state(state), 0);
}


static void
update_modifier_state(uint8 scancode, RD_BOOL pressed)
{
#ifdef WITH_DEBUG_KBD
	uint16 old_modifier_state;

	old_modifier_state = remote_modifier_state;
#endif

	switch (scancode)
	{
		case SCANCODE_CHAR_LSHIFT:
			MASK_CHANGE_BIT(remote_modifier_state, MapLeftShiftMask, pressed);
			break;
		case SCANCODE_CHAR_RSHIFT:
			MASK_CHANGE_BIT(remote_modifier_state, MapRightShiftMask, pressed);
			break;
		case SCANCODE_CHAR_LCTRL:
			MASK_CHANGE_BIT(remote_modifier_state, MapLeftCtrlMask, pressed);
			break;
		case SCANCODE_CHAR_RCTRL:
			MASK_CHANGE_BIT(remote_modifier_state, MapRightCtrlMask, pressed);
			break;
		case SCANCODE_CHAR_LALT:
			MASK_CHANGE_BIT(remote_modifier_state, MapLeftAltMask, pressed);
			break;
		case SCANCODE_CHAR_RALT:
			MASK_CHANGE_BIT(remote_modifier_state, MapRightAltMask, pressed);
			break;
		case SCANCODE_CHAR_LWIN:
			MASK_CHANGE_BIT(remote_modifier_state, MapLeftWinMask, pressed);
			break;
		case SCANCODE_CHAR_RWIN:
			MASK_CHANGE_BIT(remote_modifier_state, MapRightWinMask, pressed);
			break;
		case SCANCODE_CHAR_NUMLOCK:
			/* KeyReleases for NumLocks are sent immediately. Toggle the
			   modifier state only on Keypress */
			if (pressed && !g_numlock_sync)
			{
				RD_BOOL newNumLockState;
				newNumLockState =
					(MASK_HAS_BITS
					 (remote_modifier_state, MapNumLockMask) == False);
				MASK_CHANGE_BIT(remote_modifier_state,
						MapNumLockMask, newNumLockState);
			}
	}

#ifdef WITH_DEBUG_KBD
	if (old_modifier_state != remote_modifier_state)
	{
		DEBUG_KBD(("Before updating modifier_state:0x%x, pressed=0x%x\n",
			   old_modifier_state, pressed));
		DEBUG_KBD(("After updating modifier_state:0x%x\n", remote_modifier_state));
	}
#endif

}

/* Send keyboard input */
void
rdp_send_scancode(uint32 time, uint16 flags, uint8 scancode)
{
	update_modifier_state(scancode, !(flags & RDP_KEYRELEASE));

	if (scancode & SCANCODE_EXTENDED)
	{
		DEBUG_KBD(("Sending extended scancode=0x%x, flags=0x%x\n",
			   scancode & ~SCANCODE_EXTENDED, flags));
		rdp_send_input(time, RDP_INPUT_SCANCODE, flags | KBD_FLAG_EXT,
			       scancode & ~SCANCODE_EXTENDED, 0);
	}
	else
	{
		DEBUG_KBD(("Sending scancode=0x%x, flags=0x%x\n", scancode, flags));
		rdp_send_input(time, RDP_INPUT_SCANCODE, flags, scancode, 0);
	}
}

typedef unsigned char byte;
typedef unsigned int  dword;

static byte vkscancode[256] = {
            /* 00 - 07 */ 0, 0, 0, 0, 0, 0, 0, 0,
            /* 08 - 0f */ 0, SCANCODE_CHAR_ESC, SCANCODE_CHAR_1, SCANCODE_CHAR_2, SCANCODE_CHAR_3, SCANCODE_CHAR_4, SCANCODE_CHAR_5, SCANCODE_CHAR_6,
            /* 10 - 17 */ SCANCODE_CHAR_7, SCANCODE_CHAR_8, SCANCODE_CHAR_9, SCANCODE_CHAR_0, SCANCODE_CHAR_MINUS, SCANCODE_CHAR_EQUAL, SCANCODE_CHAR_BACKSPACE, SCANCODE_CHAR_TAB,
            /* 18 - 1f */ SCANCODE_CHAR_Q, SCANCODE_CHAR_W, SCANCODE_CHAR_E, SCANCODE_CHAR_R, SCANCODE_CHAR_T, SCANCODE_CHAR_Y, SCANCODE_CHAR_U, SCANCODE_CHAR_I,
            /* 20 - 27 */ SCANCODE_CHAR_O, SCANCODE_CHAR_P, SCANCODE_CHAR_BRACKETLEFT, SCANCODE_CHAR_BRACKETRIGHT, SCANCODE_CHAR_ENTER, SCANCODE_CHAR_LCTRL, SCANCODE_CHAR_A, SCANCODE_CHAR_S,
            /* 28 - 2f */ SCANCODE_CHAR_D, SCANCODE_CHAR_F, SCANCODE_CHAR_G, SCANCODE_CHAR_H, SCANCODE_CHAR_J, SCANCODE_CHAR_K, SCANCODE_CHAR_L, SCANCODE_CHAR_SEMICOLON,
            /* 30 - 37 */ SCANCODE_CHAR_APOSTROPHE, SCANCODE_CHAR_GRAVE, SCANCODE_CHAR_LSHIFT, SCANCODE_KEY_42, SCANCODE_CHAR_Z, SCANCODE_CHAR_X, SCANCODE_CHAR_C, SCANCODE_CHAR_V,
            /* 38 - 3f */ SCANCODE_CHAR_B, SCANCODE_CHAR_N, SCANCODE_CHAR_M, SCANCODE_CHAR_COMMA, SCANCODE_CHAR_DOT, SCANCODE_CHAR_SLASH, SCANCODE_CHAR_RSHIFT, SCANCODE_CHAR_NUMERICSTAR,
            /* 40 - 47 */ SCANCODE_CHAR_LALT, SCANCODE_CHAR_SPACE, SCANCODE_CHAR_CAPSLOCK, SCANCODE_CHAR_F1, SCANCODE_CHAR_F2, SCANCODE_CHAR_F3, SCANCODE_CHAR_F4, SCANCODE_CHAR_F5,
            /* 48 - 4f */ SCANCODE_CHAR_F6, SCANCODE_CHAR_F7, SCANCODE_CHAR_F8, SCANCODE_CHAR_F9, SCANCODE_CHAR_F10, SCANCODE_CHAR_NUMLOCK, SCANCODE_CHAR_SCROLLLOCK, SCANCODE_CHAR_NUMERIC7,
            /* 50 - 57 */ SCANCODE_CHAR_NUMERIC8, SCANCODE_CHAR_NUMERIC9, SCANCODE_CHAR_NUMERICMINUS, SCANCODE_CHAR_NUMERIC4, SCANCODE_CHAR_NUMERIC5, SCANCODE_CHAR_NUMERIC6, SCANCODE_CHAR_NUMERICPLUS, SCANCODE_CHAR_NUMERIC1,
            /* 58 - 5f */ SCANCODE_CHAR_NUMERIC2, SCANCODE_CHAR_NUMERIC3, SCANCODE_CHAR_NUMERIC0, SCANCODE_CHAR_NUMERICDOT, 0, 0, 0, SCANCODE_CHAR_F11,
            /* 60 - 67 */ SCANCODE_CHAR_F12, SCANCODE_CHAR_HOME, SCANCODE_CHAR_UPARROW, SCANCODE_CHAR_PAGEUP, SCANCODE_CHAR_LARROW, 0, SCANCODE_CHAR_RARROW, SCANCODE_CHAR_END,
            /* 68 - 6f */ SCANCODE_CHAR_NUMERICENTER, SCANCODE_CHAR_RCTRL, SCANCODE_CHAR_NUMERICSLASH, SCANCODE_CHAR_DELETE, SCANCODE_CHAR_RALT, SCANCODE_CHAR_RCTRL, SCANCODE_CHAR_HOME, SCANCODE_CHAR_UPARROW,
            /* 70 - 77 */ SCANCODE_CHAR_PAGEUP, SCANCODE_CHAR_LARROW, SCANCODE_CHAR_RARROW, SCANCODE_CHAR_END, SCANCODE_CHAR_DNARROW, SCANCODE_CHAR_PAGEDOWN, SCANCODE_CHAR_INSERT, SCANCODE_CHAR_DELETE,
            /* 78 - 7f */ 0, 0, 0, 0, 0, 0, 0, 0,

            /* 80 - 87 */ 0, 0, 0, 0, 0, SCANCODE_CHAR_LWIN, 0, SCANCODE_CHAR_APPLICATION,
            /* 88 - 8f */ 0, 0, 0, 0, 0, 0, 0, 0,
            /* 90 - 97 */ 0, 0, 0, 0, 0, 0, 0, 0,
            /* 98 - 9f */ 0, 0, 0, 0, 0, 0, 0, 0,
            /* a0 - a7 */ 0, 0, 0, 0, 0, 0, 0, 0,
            /* a8 - af */ 0, 0, 0, 0, 0, 0, 0, 0,
            /* b0 - b7 */ 0, 0, 0, 0, 0, 0, 0, 0,
            /* b8 - bf */ 0, 0, 0, 0, 0, 0, 0, 0,
            /* c0 - c7 */ 0, 0, 0, 0, 0, 0, 0, 0,
            /* c8 - cf */ 0, 0, 0, 0, 0, 0, 0, 0,
            /* d0 - d7 */ 0, 0, 0, 0, 0, 0, 0, 0,
            /* d8 - df */ 0, 0, 0, 0, 0, 0, 0, 0,
            /* e0 - e7 */ 0, 0, 0, 0, 0, 0, 0, 0,
            /* e8 - ef */ 0, 0, 0, 0, 0, 0, 0, 0,
            /* f0 - f7 */ 0, 0, 0, 0, 0, 0, 0, 0,
            /* f8 - ff */ 0, 0, 0, 0, 0, 0, 0, 0
};

static inline int vk_handle_special_keys( uint32 keysym, uint32 ev_time, RD_BOOL pressed) {

        RD_BOOL leftkey = 0;

        switch( keysym)        {
        case SCANCODE_CHAR_NUMLOCK:
                if( !pressed)
                        vknumlock = !vknumlock;
                return 0;

        case SCANCODE_CHAR_ENTER:
        case SCANCODE_CHAR_NUMERICENTER:
                if( pressed && vkmenu && vkcontrol) {
                        /* Ctrl-Alt-Enter: toggle full screen */
                       xwin_toggle_fullscreen();
                       return 1;
                }
               return 0;

        case SCANCODE_CHAR_PAUSE:
                if( pressed) {
                        if( vkcontrol) {
                                rdp_send_scancode( ev_time, RDP_KEYPRESS, (SCANCODE_EXTENDED | 0x46));
                                rdp_send_scancode( ev_time, RDP_KEYPRESS, (SCANCODE_EXTENDED | 0xc6));
                        }
                        else {
                                rdp_send_input( ev_time, RDP_INPUT_SCANCODE, RDP_KEYPRESS, 0xe1, 0);
                                rdp_send_input( ev_time, RDP_INPUT_SCANCODE, RDP_KEYPRESS, 0x1d, 0);
                                rdp_send_input( ev_time, RDP_INPUT_SCANCODE, RDP_KEYPRESS, 0x45, 0);
                                rdp_send_input( ev_time, RDP_INPUT_SCANCODE, RDP_KEYPRESS, 0xe1, 0);
                                rdp_send_input( ev_time, RDP_INPUT_SCANCODE, RDP_KEYPRESS, 0x9d, 0);
                                rdp_send_input( ev_time, RDP_INPUT_SCANCODE, RDP_KEYPRESS, 0xc5, 0);
                        }
               }
                else {
                       /* Release Left Ctrl */
                        if( vkcontrol)
                                rdp_send_input( ev_time, RDP_INPUT_SCANCODE, RDP_KEYRELEASE, 0x1d, 0);
                }
                return 1;

        case SCANCODE_CHAR_PRINT:
                if( vkmenu)
                        rdp_send_input( ev_time, RDP_INPUT_SCANCODE, pressed ? RDP_KEYPRESS : RDP_KEYRELEASE, 0x54, 0);
                else if( vkcontrol && (vklshift || vklshift))
                        rdp_send_input( ev_time, RDP_INPUT_SCANCODE, pressed ? RDP_KEYPRESS : RDP_KEYRELEASE, SCANCODE_EXTENDED|0x37, 0);
                else {
#if 0
                        if( pressed) {
                                rdp_send_input( ev_time, RDP_INPUT_SCANCODE, RDP_KEYPRESS, SCANCODE_CHAR_LSHIFT, 0);
                                rdp_send_input( ev_time, RDP_INPUT_SCANCODE, RDP_KEYPRESS, SCANCODE_EXTENDED|0x37, 0);
                        }
                        else {
                                rdp_send_input( ev_time, RDP_INPUT_SCANCODE, RDP_KEYRELEASE, SCANCODE_EXTENDED|0x37, 0);
                                rdp_send_input( ev_time, RDP_INPUT_SCANCODE, RDP_KEYRELEASE, SCANCODE_CHAR_LSHIFT, 0);
                        }
#endif
                }
                return 1;

        case SCANCODE_CHAR_LWIN:
                leftkey = True;
        case SCANCODE_CHAR_RWIN:
                if( pressed) {
                        if( g_use_rdp5) {
                                rdp_send_scancode(ev_time, RDP_KEYPRESS, keysym);
                        }
                        else {
                                /* RDP4 doesn't support winkey. Fake with Ctrl-Esc */
                                rdp_send_scancode( ev_time, RDP_KEYPRESS, SCANCODE_CHAR_LCTRL);
                                rdp_send_scancode( ev_time, RDP_KEYPRESS, SCANCODE_CHAR_ESC);
                        }
                }
                else {
                        if( g_use_rdp5) {
                                rdp_send_scancode(ev_time, RDP_KEYRELEASE, keysym);
                        }
                        else {
                                rdp_send_scancode(ev_time, RDP_KEYRELEASE, SCANCODE_CHAR_ESC);
                                rdp_send_scancode(ev_time, RDP_KEYRELEASE, SCANCODE_CHAR_LCTRL);
                        }
                }
                return 1;

        case SCANCODE_CHAR_INSERT:
        case SCANCODE_CHAR_DELETE:
        case SCANCODE_CHAR_LARROW:
        case SCANCODE_CHAR_HOME:
        case SCANCODE_CHAR_END:
        case SCANCODE_CHAR_UPARROW:
        case SCANCODE_CHAR_DNARROW:
        case SCANCODE_CHAR_PAGEUP:
        case SCANCODE_CHAR_PAGEDOWN:
        case SCANCODE_CHAR_RARROW:
        case SCANCODE_CHAR_NUMERICSLASH:
        case SCANCODE_CHAR_APPLICATION:
               rdp_send_scancode( ev_time, pressed ? RDP_KEYPRESS : RDP_KEYRELEASE, SCANCODE_CHAR_LSHIFT);
               rdp_send_scancode( ev_time, pressed ? RDP_KEYPRESS : RDP_KEYRELEASE, keysym);
               return 1;
        }
       return 0;
}


void vk_handle_key( XKeyEvent *xkey) {

        uint32 vk, ev_time, pressed = (xkey->type == KeyPress);
       
        if (g_ind_raw_converter)
            vk = scancodes_table[ xkey->keycode];
        else
            vk = vkscancode[ xkey->keycode];
      
        DEBUG_KBD(( "vk_handle_key( scancode=0x%x) vk = 0x%x\n", xkey->keycode, vk));

        if( !vk)
                return;

        ev_time = time( 0);

        if( (vk == SCANCODE_CHAR_LCTRL) || (vk == SCANCODE_CHAR_RCTRL))
                vkcontrol = pressed;
        else if( (vk == SCANCODE_CHAR_LALT) || (vk == SCANCODE_CHAR_RALT))
                vkmenu = pressed;
        else if( vk == SCANCODE_CHAR_LSHIFT)
                vklshift = pressed;
        else if( vk == SCANCODE_CHAR_RSHIFT)
                vkrshift = pressed;
        else if( vk_handle_special_keys( vk, ev_time, pressed))
                return;

        rdp_send_input( ev_time, RDP_INPUT_SCANCODE, pressed ? RDP_KEYPRESS : RDP_KEYRELEASE, vk, 0);
}
