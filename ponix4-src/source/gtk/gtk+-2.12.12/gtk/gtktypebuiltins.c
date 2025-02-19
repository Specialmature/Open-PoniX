
/* Generated data (by glib-mkenums) */

#undef GTK_DISABLE_DEPRECATED
#define GTK_ENABLE_BROKEN
#include "gtk.h"
#include "gtkprivate.h"
#include "gtkalias.h"

/* enumerations from "gtkaccelgroup.h" */
GType
gtk_accel_flags_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GFlagsValue values[] = {
      { GTK_ACCEL_VISIBLE, "GTK_ACCEL_VISIBLE", "visible" },
      { GTK_ACCEL_LOCKED, "GTK_ACCEL_LOCKED", "locked" },
      { GTK_ACCEL_MASK, "GTK_ACCEL_MASK", "mask" },
      { 0, NULL, NULL }
    };
    etype = g_flags_register_static (g_intern_static_string ("GtkAccelFlags"), values);
  }
  return etype;
}

/* enumerations from "gtkassistant.h" */
GType
gtk_assistant_page_type_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_ASSISTANT_PAGE_CONTENT, "GTK_ASSISTANT_PAGE_CONTENT", "content" },
      { GTK_ASSISTANT_PAGE_INTRO, "GTK_ASSISTANT_PAGE_INTRO", "intro" },
      { GTK_ASSISTANT_PAGE_CONFIRM, "GTK_ASSISTANT_PAGE_CONFIRM", "confirm" },
      { GTK_ASSISTANT_PAGE_SUMMARY, "GTK_ASSISTANT_PAGE_SUMMARY", "summary" },
      { GTK_ASSISTANT_PAGE_PROGRESS, "GTK_ASSISTANT_PAGE_PROGRESS", "progress" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkAssistantPageType"), values);
  }
  return etype;
}

/* enumerations from "gtkbuilder.h" */
GType
gtk_builder_error_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_BUILDER_ERROR_INVALID_TYPE_FUNCTION, "GTK_BUILDER_ERROR_INVALID_TYPE_FUNCTION", "invalid-type-function" },
      { GTK_BUILDER_ERROR_UNHANDLED_TAG, "GTK_BUILDER_ERROR_UNHANDLED_TAG", "unhandled-tag" },
      { GTK_BUILDER_ERROR_MISSING_ATTRIBUTE, "GTK_BUILDER_ERROR_MISSING_ATTRIBUTE", "missing-attribute" },
      { GTK_BUILDER_ERROR_INVALID_ATTRIBUTE, "GTK_BUILDER_ERROR_INVALID_ATTRIBUTE", "invalid-attribute" },
      { GTK_BUILDER_ERROR_INVALID_TAG, "GTK_BUILDER_ERROR_INVALID_TAG", "invalid-tag" },
      { GTK_BUILDER_ERROR_MISSING_PROPERTY_VALUE, "GTK_BUILDER_ERROR_MISSING_PROPERTY_VALUE", "missing-property-value" },
      { GTK_BUILDER_ERROR_INVALID_VALUE, "GTK_BUILDER_ERROR_INVALID_VALUE", "invalid-value" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkBuilderError"), values);
  }
  return etype;
}

/* enumerations from "gtkcalendar.h" */
GType
gtk_calendar_display_options_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GFlagsValue values[] = {
      { GTK_CALENDAR_SHOW_HEADING, "GTK_CALENDAR_SHOW_HEADING", "show-heading" },
      { GTK_CALENDAR_SHOW_DAY_NAMES, "GTK_CALENDAR_SHOW_DAY_NAMES", "show-day-names" },
      { GTK_CALENDAR_NO_MONTH_CHANGE, "GTK_CALENDAR_NO_MONTH_CHANGE", "no-month-change" },
      { GTK_CALENDAR_SHOW_WEEK_NUMBERS, "GTK_CALENDAR_SHOW_WEEK_NUMBERS", "show-week-numbers" },
      { GTK_CALENDAR_WEEK_START_MONDAY, "GTK_CALENDAR_WEEK_START_MONDAY", "week-start-monday" },
      { 0, NULL, NULL }
    };
    etype = g_flags_register_static (g_intern_static_string ("GtkCalendarDisplayOptions"), values);
  }
  return etype;
}

/* enumerations from "gtkcellrenderer.h" */
GType
gtk_cell_renderer_state_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GFlagsValue values[] = {
      { GTK_CELL_RENDERER_SELECTED, "GTK_CELL_RENDERER_SELECTED", "selected" },
      { GTK_CELL_RENDERER_PRELIT, "GTK_CELL_RENDERER_PRELIT", "prelit" },
      { GTK_CELL_RENDERER_INSENSITIVE, "GTK_CELL_RENDERER_INSENSITIVE", "insensitive" },
      { GTK_CELL_RENDERER_SORTED, "GTK_CELL_RENDERER_SORTED", "sorted" },
      { GTK_CELL_RENDERER_FOCUSED, "GTK_CELL_RENDERER_FOCUSED", "focused" },
      { 0, NULL, NULL }
    };
    etype = g_flags_register_static (g_intern_static_string ("GtkCellRendererState"), values);
  }
  return etype;
}
GType
gtk_cell_renderer_mode_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_CELL_RENDERER_MODE_INERT, "GTK_CELL_RENDERER_MODE_INERT", "inert" },
      { GTK_CELL_RENDERER_MODE_ACTIVATABLE, "GTK_CELL_RENDERER_MODE_ACTIVATABLE", "activatable" },
      { GTK_CELL_RENDERER_MODE_EDITABLE, "GTK_CELL_RENDERER_MODE_EDITABLE", "editable" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkCellRendererMode"), values);
  }
  return etype;
}

/* enumerations from "gtkcellrendereraccel.h" */
GType
gtk_cell_renderer_accel_mode_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_CELL_RENDERER_ACCEL_MODE_GTK, "GTK_CELL_RENDERER_ACCEL_MODE_GTK", "gtk" },
      { GTK_CELL_RENDERER_ACCEL_MODE_OTHER, "GTK_CELL_RENDERER_ACCEL_MODE_OTHER", "other" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkCellRendererAccelMode"), values);
  }
  return etype;
}

/* enumerations from "gtkclist.h" */
GType
gtk_cell_type_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_CELL_EMPTY, "GTK_CELL_EMPTY", "empty" },
      { GTK_CELL_TEXT, "GTK_CELL_TEXT", "text" },
      { GTK_CELL_PIXMAP, "GTK_CELL_PIXMAP", "pixmap" },
      { GTK_CELL_PIXTEXT, "GTK_CELL_PIXTEXT", "pixtext" },
      { GTK_CELL_WIDGET, "GTK_CELL_WIDGET", "widget" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkCellType"), values);
  }
  return etype;
}
GType
gtk_clist_drag_pos_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_CLIST_DRAG_NONE, "GTK_CLIST_DRAG_NONE", "none" },
      { GTK_CLIST_DRAG_BEFORE, "GTK_CLIST_DRAG_BEFORE", "before" },
      { GTK_CLIST_DRAG_INTO, "GTK_CLIST_DRAG_INTO", "into" },
      { GTK_CLIST_DRAG_AFTER, "GTK_CLIST_DRAG_AFTER", "after" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkCListDragPos"), values);
  }
  return etype;
}
GType
gtk_button_action_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GFlagsValue values[] = {
      { GTK_BUTTON_IGNORED, "GTK_BUTTON_IGNORED", "ignored" },
      { GTK_BUTTON_SELECTS, "GTK_BUTTON_SELECTS", "selects" },
      { GTK_BUTTON_DRAGS, "GTK_BUTTON_DRAGS", "drags" },
      { GTK_BUTTON_EXPANDS, "GTK_BUTTON_EXPANDS", "expands" },
      { 0, NULL, NULL }
    };
    etype = g_flags_register_static (g_intern_static_string ("GtkButtonAction"), values);
  }
  return etype;
}

/* enumerations from "gtkctree.h" */
GType
gtk_ctree_pos_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_CTREE_POS_BEFORE, "GTK_CTREE_POS_BEFORE", "before" },
      { GTK_CTREE_POS_AS_CHILD, "GTK_CTREE_POS_AS_CHILD", "as-child" },
      { GTK_CTREE_POS_AFTER, "GTK_CTREE_POS_AFTER", "after" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkCTreePos"), values);
  }
  return etype;
}
GType
gtk_ctree_line_style_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_CTREE_LINES_NONE, "GTK_CTREE_LINES_NONE", "none" },
      { GTK_CTREE_LINES_SOLID, "GTK_CTREE_LINES_SOLID", "solid" },
      { GTK_CTREE_LINES_DOTTED, "GTK_CTREE_LINES_DOTTED", "dotted" },
      { GTK_CTREE_LINES_TABBED, "GTK_CTREE_LINES_TABBED", "tabbed" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkCTreeLineStyle"), values);
  }
  return etype;
}
GType
gtk_ctree_expander_style_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_CTREE_EXPANDER_NONE, "GTK_CTREE_EXPANDER_NONE", "none" },
      { GTK_CTREE_EXPANDER_SQUARE, "GTK_CTREE_EXPANDER_SQUARE", "square" },
      { GTK_CTREE_EXPANDER_TRIANGLE, "GTK_CTREE_EXPANDER_TRIANGLE", "triangle" },
      { GTK_CTREE_EXPANDER_CIRCULAR, "GTK_CTREE_EXPANDER_CIRCULAR", "circular" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkCTreeExpanderStyle"), values);
  }
  return etype;
}
GType
gtk_ctree_expansion_type_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_CTREE_EXPANSION_EXPAND, "GTK_CTREE_EXPANSION_EXPAND", "expand" },
      { GTK_CTREE_EXPANSION_EXPAND_RECURSIVE, "GTK_CTREE_EXPANSION_EXPAND_RECURSIVE", "expand-recursive" },
      { GTK_CTREE_EXPANSION_COLLAPSE, "GTK_CTREE_EXPANSION_COLLAPSE", "collapse" },
      { GTK_CTREE_EXPANSION_COLLAPSE_RECURSIVE, "GTK_CTREE_EXPANSION_COLLAPSE_RECURSIVE", "collapse-recursive" },
      { GTK_CTREE_EXPANSION_TOGGLE, "GTK_CTREE_EXPANSION_TOGGLE", "toggle" },
      { GTK_CTREE_EXPANSION_TOGGLE_RECURSIVE, "GTK_CTREE_EXPANSION_TOGGLE_RECURSIVE", "toggle-recursive" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkCTreeExpansionType"), values);
  }
  return etype;
}

/* enumerations from "gtkdebug.h" */
GType
gtk_debug_flag_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GFlagsValue values[] = {
      { GTK_DEBUG_MISC, "GTK_DEBUG_MISC", "misc" },
      { GTK_DEBUG_PLUGSOCKET, "GTK_DEBUG_PLUGSOCKET", "plugsocket" },
      { GTK_DEBUG_TEXT, "GTK_DEBUG_TEXT", "text" },
      { GTK_DEBUG_TREE, "GTK_DEBUG_TREE", "tree" },
      { GTK_DEBUG_UPDATES, "GTK_DEBUG_UPDATES", "updates" },
      { GTK_DEBUG_KEYBINDINGS, "GTK_DEBUG_KEYBINDINGS", "keybindings" },
      { GTK_DEBUG_MULTIHEAD, "GTK_DEBUG_MULTIHEAD", "multihead" },
      { GTK_DEBUG_MODULES, "GTK_DEBUG_MODULES", "modules" },
      { GTK_DEBUG_GEOMETRY, "GTK_DEBUG_GEOMETRY", "geometry" },
      { GTK_DEBUG_ICONTHEME, "GTK_DEBUG_ICONTHEME", "icontheme" },
      { GTK_DEBUG_PRINTING, "GTK_DEBUG_PRINTING", "printing" },
      { GTK_DEBUG_BUILDER, "GTK_DEBUG_BUILDER", "builder" },
      { 0, NULL, NULL }
    };
    etype = g_flags_register_static (g_intern_static_string ("GtkDebugFlag"), values);
  }
  return etype;
}

/* enumerations from "gtkdialog.h" */
GType
gtk_dialog_flags_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GFlagsValue values[] = {
      { GTK_DIALOG_MODAL, "GTK_DIALOG_MODAL", "modal" },
      { GTK_DIALOG_DESTROY_WITH_PARENT, "GTK_DIALOG_DESTROY_WITH_PARENT", "destroy-with-parent" },
      { GTK_DIALOG_NO_SEPARATOR, "GTK_DIALOG_NO_SEPARATOR", "no-separator" },
      { 0, NULL, NULL }
    };
    etype = g_flags_register_static (g_intern_static_string ("GtkDialogFlags"), values);
  }
  return etype;
}
GType
gtk_response_type_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_RESPONSE_NONE, "GTK_RESPONSE_NONE", "none" },
      { GTK_RESPONSE_REJECT, "GTK_RESPONSE_REJECT", "reject" },
      { GTK_RESPONSE_ACCEPT, "GTK_RESPONSE_ACCEPT", "accept" },
      { GTK_RESPONSE_DELETE_EVENT, "GTK_RESPONSE_DELETE_EVENT", "delete-event" },
      { GTK_RESPONSE_OK, "GTK_RESPONSE_OK", "ok" },
      { GTK_RESPONSE_CANCEL, "GTK_RESPONSE_CANCEL", "cancel" },
      { GTK_RESPONSE_CLOSE, "GTK_RESPONSE_CLOSE", "close" },
      { GTK_RESPONSE_YES, "GTK_RESPONSE_YES", "yes" },
      { GTK_RESPONSE_NO, "GTK_RESPONSE_NO", "no" },
      { GTK_RESPONSE_APPLY, "GTK_RESPONSE_APPLY", "apply" },
      { GTK_RESPONSE_HELP, "GTK_RESPONSE_HELP", "help" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkResponseType"), values);
  }
  return etype;
}

/* enumerations from "gtkdnd.h" */
GType
gtk_dest_defaults_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GFlagsValue values[] = {
      { GTK_DEST_DEFAULT_MOTION, "GTK_DEST_DEFAULT_MOTION", "motion" },
      { GTK_DEST_DEFAULT_HIGHLIGHT, "GTK_DEST_DEFAULT_HIGHLIGHT", "highlight" },
      { GTK_DEST_DEFAULT_DROP, "GTK_DEST_DEFAULT_DROP", "drop" },
      { GTK_DEST_DEFAULT_ALL, "GTK_DEST_DEFAULT_ALL", "all" },
      { 0, NULL, NULL }
    };
    etype = g_flags_register_static (g_intern_static_string ("GtkDestDefaults"), values);
  }
  return etype;
}
GType
gtk_target_flags_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GFlagsValue values[] = {
      { GTK_TARGET_SAME_APP, "GTK_TARGET_SAME_APP", "same-app" },
      { GTK_TARGET_SAME_WIDGET, "GTK_TARGET_SAME_WIDGET", "same-widget" },
      { GTK_TARGET_OTHER_APP, "GTK_TARGET_OTHER_APP", "other-app" },
      { GTK_TARGET_OTHER_WIDGET, "GTK_TARGET_OTHER_WIDGET", "other-widget" },
      { 0, NULL, NULL }
    };
    etype = g_flags_register_static (g_intern_static_string ("GtkTargetFlags"), values);
  }
  return etype;
}

/* enumerations from "gtkenums.h" */
GType
gtk_anchor_type_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_ANCHOR_CENTER, "GTK_ANCHOR_CENTER", "center" },
      { GTK_ANCHOR_NORTH, "GTK_ANCHOR_NORTH", "north" },
      { GTK_ANCHOR_NORTH_WEST, "GTK_ANCHOR_NORTH_WEST", "north-west" },
      { GTK_ANCHOR_NORTH_EAST, "GTK_ANCHOR_NORTH_EAST", "north-east" },
      { GTK_ANCHOR_SOUTH, "GTK_ANCHOR_SOUTH", "south" },
      { GTK_ANCHOR_SOUTH_WEST, "GTK_ANCHOR_SOUTH_WEST", "south-west" },
      { GTK_ANCHOR_SOUTH_EAST, "GTK_ANCHOR_SOUTH_EAST", "south-east" },
      { GTK_ANCHOR_WEST, "GTK_ANCHOR_WEST", "west" },
      { GTK_ANCHOR_EAST, "GTK_ANCHOR_EAST", "east" },
      { GTK_ANCHOR_N, "GTK_ANCHOR_N", "n" },
      { GTK_ANCHOR_NW, "GTK_ANCHOR_NW", "nw" },
      { GTK_ANCHOR_NE, "GTK_ANCHOR_NE", "ne" },
      { GTK_ANCHOR_S, "GTK_ANCHOR_S", "s" },
      { GTK_ANCHOR_SW, "GTK_ANCHOR_SW", "sw" },
      { GTK_ANCHOR_SE, "GTK_ANCHOR_SE", "se" },
      { GTK_ANCHOR_W, "GTK_ANCHOR_W", "w" },
      { GTK_ANCHOR_E, "GTK_ANCHOR_E", "e" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkAnchorType"), values);
  }
  return etype;
}
GType
gtk_arrow_type_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_ARROW_UP, "GTK_ARROW_UP", "up" },
      { GTK_ARROW_DOWN, "GTK_ARROW_DOWN", "down" },
      { GTK_ARROW_LEFT, "GTK_ARROW_LEFT", "left" },
      { GTK_ARROW_RIGHT, "GTK_ARROW_RIGHT", "right" },
      { GTK_ARROW_NONE, "GTK_ARROW_NONE", "none" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkArrowType"), values);
  }
  return etype;
}
GType
gtk_attach_options_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GFlagsValue values[] = {
      { GTK_EXPAND, "GTK_EXPAND", "expand" },
      { GTK_SHRINK, "GTK_SHRINK", "shrink" },
      { GTK_FILL, "GTK_FILL", "fill" },
      { 0, NULL, NULL }
    };
    etype = g_flags_register_static (g_intern_static_string ("GtkAttachOptions"), values);
  }
  return etype;
}
GType
gtk_button_box_style_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_BUTTONBOX_DEFAULT_STYLE, "GTK_BUTTONBOX_DEFAULT_STYLE", "default-style" },
      { GTK_BUTTONBOX_SPREAD, "GTK_BUTTONBOX_SPREAD", "spread" },
      { GTK_BUTTONBOX_EDGE, "GTK_BUTTONBOX_EDGE", "edge" },
      { GTK_BUTTONBOX_START, "GTK_BUTTONBOX_START", "start" },
      { GTK_BUTTONBOX_END, "GTK_BUTTONBOX_END", "end" },
      { GTK_BUTTONBOX_CENTER, "GTK_BUTTONBOX_CENTER", "center" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkButtonBoxStyle"), values);
  }
  return etype;
}
GType
gtk_curve_type_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_CURVE_TYPE_LINEAR, "GTK_CURVE_TYPE_LINEAR", "linear" },
      { GTK_CURVE_TYPE_SPLINE, "GTK_CURVE_TYPE_SPLINE", "spline" },
      { GTK_CURVE_TYPE_FREE, "GTK_CURVE_TYPE_FREE", "free" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkCurveType"), values);
  }
  return etype;
}
GType
gtk_delete_type_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_DELETE_CHARS, "GTK_DELETE_CHARS", "chars" },
      { GTK_DELETE_WORD_ENDS, "GTK_DELETE_WORD_ENDS", "word-ends" },
      { GTK_DELETE_WORDS, "GTK_DELETE_WORDS", "words" },
      { GTK_DELETE_DISPLAY_LINES, "GTK_DELETE_DISPLAY_LINES", "display-lines" },
      { GTK_DELETE_DISPLAY_LINE_ENDS, "GTK_DELETE_DISPLAY_LINE_ENDS", "display-line-ends" },
      { GTK_DELETE_PARAGRAPH_ENDS, "GTK_DELETE_PARAGRAPH_ENDS", "paragraph-ends" },
      { GTK_DELETE_PARAGRAPHS, "GTK_DELETE_PARAGRAPHS", "paragraphs" },
      { GTK_DELETE_WHITESPACE, "GTK_DELETE_WHITESPACE", "whitespace" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkDeleteType"), values);
  }
  return etype;
}
GType
gtk_direction_type_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_DIR_TAB_FORWARD, "GTK_DIR_TAB_FORWARD", "tab-forward" },
      { GTK_DIR_TAB_BACKWARD, "GTK_DIR_TAB_BACKWARD", "tab-backward" },
      { GTK_DIR_UP, "GTK_DIR_UP", "up" },
      { GTK_DIR_DOWN, "GTK_DIR_DOWN", "down" },
      { GTK_DIR_LEFT, "GTK_DIR_LEFT", "left" },
      { GTK_DIR_RIGHT, "GTK_DIR_RIGHT", "right" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkDirectionType"), values);
  }
  return etype;
}
GType
gtk_expander_style_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_EXPANDER_COLLAPSED, "GTK_EXPANDER_COLLAPSED", "collapsed" },
      { GTK_EXPANDER_SEMI_COLLAPSED, "GTK_EXPANDER_SEMI_COLLAPSED", "semi-collapsed" },
      { GTK_EXPANDER_SEMI_EXPANDED, "GTK_EXPANDER_SEMI_EXPANDED", "semi-expanded" },
      { GTK_EXPANDER_EXPANDED, "GTK_EXPANDER_EXPANDED", "expanded" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkExpanderStyle"), values);
  }
  return etype;
}
GType
gtk_icon_size_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_ICON_SIZE_INVALID, "GTK_ICON_SIZE_INVALID", "invalid" },
      { GTK_ICON_SIZE_MENU, "GTK_ICON_SIZE_MENU", "menu" },
      { GTK_ICON_SIZE_SMALL_TOOLBAR, "GTK_ICON_SIZE_SMALL_TOOLBAR", "small-toolbar" },
      { GTK_ICON_SIZE_LARGE_TOOLBAR, "GTK_ICON_SIZE_LARGE_TOOLBAR", "large-toolbar" },
      { GTK_ICON_SIZE_BUTTON, "GTK_ICON_SIZE_BUTTON", "button" },
      { GTK_ICON_SIZE_DND, "GTK_ICON_SIZE_DND", "dnd" },
      { GTK_ICON_SIZE_DIALOG, "GTK_ICON_SIZE_DIALOG", "dialog" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkIconSize"), values);
  }
  return etype;
}
GType
gtk_sensitivity_type_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_SENSITIVITY_AUTO, "GTK_SENSITIVITY_AUTO", "auto" },
      { GTK_SENSITIVITY_ON, "GTK_SENSITIVITY_ON", "on" },
      { GTK_SENSITIVITY_OFF, "GTK_SENSITIVITY_OFF", "off" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkSensitivityType"), values);
  }
  return etype;
}
GType
gtk_side_type_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_SIDE_TOP, "GTK_SIDE_TOP", "top" },
      { GTK_SIDE_BOTTOM, "GTK_SIDE_BOTTOM", "bottom" },
      { GTK_SIDE_LEFT, "GTK_SIDE_LEFT", "left" },
      { GTK_SIDE_RIGHT, "GTK_SIDE_RIGHT", "right" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkSideType"), values);
  }
  return etype;
}
GType
gtk_text_direction_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_TEXT_DIR_NONE, "GTK_TEXT_DIR_NONE", "none" },
      { GTK_TEXT_DIR_LTR, "GTK_TEXT_DIR_LTR", "ltr" },
      { GTK_TEXT_DIR_RTL, "GTK_TEXT_DIR_RTL", "rtl" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkTextDirection"), values);
  }
  return etype;
}
GType
gtk_justification_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_JUSTIFY_LEFT, "GTK_JUSTIFY_LEFT", "left" },
      { GTK_JUSTIFY_RIGHT, "GTK_JUSTIFY_RIGHT", "right" },
      { GTK_JUSTIFY_CENTER, "GTK_JUSTIFY_CENTER", "center" },
      { GTK_JUSTIFY_FILL, "GTK_JUSTIFY_FILL", "fill" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkJustification"), values);
  }
  return etype;
}
GType
gtk_match_type_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_MATCH_ALL, "GTK_MATCH_ALL", "all" },
      { GTK_MATCH_ALL_TAIL, "GTK_MATCH_ALL_TAIL", "all-tail" },
      { GTK_MATCH_HEAD, "GTK_MATCH_HEAD", "head" },
      { GTK_MATCH_TAIL, "GTK_MATCH_TAIL", "tail" },
      { GTK_MATCH_EXACT, "GTK_MATCH_EXACT", "exact" },
      { GTK_MATCH_LAST, "GTK_MATCH_LAST", "last" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkMatchType"), values);
  }
  return etype;
}
GType
gtk_menu_direction_type_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_MENU_DIR_PARENT, "GTK_MENU_DIR_PARENT", "parent" },
      { GTK_MENU_DIR_CHILD, "GTK_MENU_DIR_CHILD", "child" },
      { GTK_MENU_DIR_NEXT, "GTK_MENU_DIR_NEXT", "next" },
      { GTK_MENU_DIR_PREV, "GTK_MENU_DIR_PREV", "prev" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkMenuDirectionType"), values);
  }
  return etype;
}
GType
gtk_metric_type_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_PIXELS, "GTK_PIXELS", "pixels" },
      { GTK_INCHES, "GTK_INCHES", "inches" },
      { GTK_CENTIMETERS, "GTK_CENTIMETERS", "centimeters" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkMetricType"), values);
  }
  return etype;
}
GType
gtk_movement_step_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_MOVEMENT_LOGICAL_POSITIONS, "GTK_MOVEMENT_LOGICAL_POSITIONS", "logical-positions" },
      { GTK_MOVEMENT_VISUAL_POSITIONS, "GTK_MOVEMENT_VISUAL_POSITIONS", "visual-positions" },
      { GTK_MOVEMENT_WORDS, "GTK_MOVEMENT_WORDS", "words" },
      { GTK_MOVEMENT_DISPLAY_LINES, "GTK_MOVEMENT_DISPLAY_LINES", "display-lines" },
      { GTK_MOVEMENT_DISPLAY_LINE_ENDS, "GTK_MOVEMENT_DISPLAY_LINE_ENDS", "display-line-ends" },
      { GTK_MOVEMENT_PARAGRAPHS, "GTK_MOVEMENT_PARAGRAPHS", "paragraphs" },
      { GTK_MOVEMENT_PARAGRAPH_ENDS, "GTK_MOVEMENT_PARAGRAPH_ENDS", "paragraph-ends" },
      { GTK_MOVEMENT_PAGES, "GTK_MOVEMENT_PAGES", "pages" },
      { GTK_MOVEMENT_BUFFER_ENDS, "GTK_MOVEMENT_BUFFER_ENDS", "buffer-ends" },
      { GTK_MOVEMENT_HORIZONTAL_PAGES, "GTK_MOVEMENT_HORIZONTAL_PAGES", "horizontal-pages" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkMovementStep"), values);
  }
  return etype;
}
GType
gtk_scroll_step_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_SCROLL_STEPS, "GTK_SCROLL_STEPS", "steps" },
      { GTK_SCROLL_PAGES, "GTK_SCROLL_PAGES", "pages" },
      { GTK_SCROLL_ENDS, "GTK_SCROLL_ENDS", "ends" },
      { GTK_SCROLL_HORIZONTAL_STEPS, "GTK_SCROLL_HORIZONTAL_STEPS", "horizontal-steps" },
      { GTK_SCROLL_HORIZONTAL_PAGES, "GTK_SCROLL_HORIZONTAL_PAGES", "horizontal-pages" },
      { GTK_SCROLL_HORIZONTAL_ENDS, "GTK_SCROLL_HORIZONTAL_ENDS", "horizontal-ends" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkScrollStep"), values);
  }
  return etype;
}
GType
gtk_orientation_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_ORIENTATION_HORIZONTAL, "GTK_ORIENTATION_HORIZONTAL", "horizontal" },
      { GTK_ORIENTATION_VERTICAL, "GTK_ORIENTATION_VERTICAL", "vertical" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkOrientation"), values);
  }
  return etype;
}
GType
gtk_corner_type_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_CORNER_TOP_LEFT, "GTK_CORNER_TOP_LEFT", "top-left" },
      { GTK_CORNER_BOTTOM_LEFT, "GTK_CORNER_BOTTOM_LEFT", "bottom-left" },
      { GTK_CORNER_TOP_RIGHT, "GTK_CORNER_TOP_RIGHT", "top-right" },
      { GTK_CORNER_BOTTOM_RIGHT, "GTK_CORNER_BOTTOM_RIGHT", "bottom-right" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkCornerType"), values);
  }
  return etype;
}
GType
gtk_pack_type_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_PACK_START, "GTK_PACK_START", "start" },
      { GTK_PACK_END, "GTK_PACK_END", "end" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkPackType"), values);
  }
  return etype;
}
GType
gtk_path_priority_type_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_PATH_PRIO_LOWEST, "GTK_PATH_PRIO_LOWEST", "lowest" },
      { GTK_PATH_PRIO_GTK, "GTK_PATH_PRIO_GTK", "gtk" },
      { GTK_PATH_PRIO_APPLICATION, "GTK_PATH_PRIO_APPLICATION", "application" },
      { GTK_PATH_PRIO_THEME, "GTK_PATH_PRIO_THEME", "theme" },
      { GTK_PATH_PRIO_RC, "GTK_PATH_PRIO_RC", "rc" },
      { GTK_PATH_PRIO_HIGHEST, "GTK_PATH_PRIO_HIGHEST", "highest" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkPathPriorityType"), values);
  }
  return etype;
}
GType
gtk_path_type_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_PATH_WIDGET, "GTK_PATH_WIDGET", "widget" },
      { GTK_PATH_WIDGET_CLASS, "GTK_PATH_WIDGET_CLASS", "widget-class" },
      { GTK_PATH_CLASS, "GTK_PATH_CLASS", "class" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkPathType"), values);
  }
  return etype;
}
GType
gtk_policy_type_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_POLICY_ALWAYS, "GTK_POLICY_ALWAYS", "always" },
      { GTK_POLICY_AUTOMATIC, "GTK_POLICY_AUTOMATIC", "automatic" },
      { GTK_POLICY_NEVER, "GTK_POLICY_NEVER", "never" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkPolicyType"), values);
  }
  return etype;
}
GType
gtk_position_type_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_POS_LEFT, "GTK_POS_LEFT", "left" },
      { GTK_POS_RIGHT, "GTK_POS_RIGHT", "right" },
      { GTK_POS_TOP, "GTK_POS_TOP", "top" },
      { GTK_POS_BOTTOM, "GTK_POS_BOTTOM", "bottom" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkPositionType"), values);
  }
  return etype;
}
GType
gtk_preview_type_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_PREVIEW_COLOR, "GTK_PREVIEW_COLOR", "color" },
      { GTK_PREVIEW_GRAYSCALE, "GTK_PREVIEW_GRAYSCALE", "grayscale" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkPreviewType"), values);
  }
  return etype;
}
GType
gtk_relief_style_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_RELIEF_NORMAL, "GTK_RELIEF_NORMAL", "normal" },
      { GTK_RELIEF_HALF, "GTK_RELIEF_HALF", "half" },
      { GTK_RELIEF_NONE, "GTK_RELIEF_NONE", "none" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkReliefStyle"), values);
  }
  return etype;
}
GType
gtk_resize_mode_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_RESIZE_PARENT, "GTK_RESIZE_PARENT", "parent" },
      { GTK_RESIZE_QUEUE, "GTK_RESIZE_QUEUE", "queue" },
      { GTK_RESIZE_IMMEDIATE, "GTK_RESIZE_IMMEDIATE", "immediate" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkResizeMode"), values);
  }
  return etype;
}
GType
gtk_signal_run_type_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GFlagsValue values[] = {
      { GTK_RUN_FIRST, "GTK_RUN_FIRST", "first" },
      { GTK_RUN_LAST, "GTK_RUN_LAST", "last" },
      { GTK_RUN_BOTH, "GTK_RUN_BOTH", "both" },
      { GTK_RUN_NO_RECURSE, "GTK_RUN_NO_RECURSE", "no-recurse" },
      { GTK_RUN_ACTION, "GTK_RUN_ACTION", "action" },
      { GTK_RUN_NO_HOOKS, "GTK_RUN_NO_HOOKS", "no-hooks" },
      { 0, NULL, NULL }
    };
    etype = g_flags_register_static (g_intern_static_string ("GtkSignalRunType"), values);
  }
  return etype;
}
GType
gtk_scroll_type_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_SCROLL_NONE, "GTK_SCROLL_NONE", "none" },
      { GTK_SCROLL_JUMP, "GTK_SCROLL_JUMP", "jump" },
      { GTK_SCROLL_STEP_BACKWARD, "GTK_SCROLL_STEP_BACKWARD", "step-backward" },
      { GTK_SCROLL_STEP_FORWARD, "GTK_SCROLL_STEP_FORWARD", "step-forward" },
      { GTK_SCROLL_PAGE_BACKWARD, "GTK_SCROLL_PAGE_BACKWARD", "page-backward" },
      { GTK_SCROLL_PAGE_FORWARD, "GTK_SCROLL_PAGE_FORWARD", "page-forward" },
      { GTK_SCROLL_STEP_UP, "GTK_SCROLL_STEP_UP", "step-up" },
      { GTK_SCROLL_STEP_DOWN, "GTK_SCROLL_STEP_DOWN", "step-down" },
      { GTK_SCROLL_PAGE_UP, "GTK_SCROLL_PAGE_UP", "page-up" },
      { GTK_SCROLL_PAGE_DOWN, "GTK_SCROLL_PAGE_DOWN", "page-down" },
      { GTK_SCROLL_STEP_LEFT, "GTK_SCROLL_STEP_LEFT", "step-left" },
      { GTK_SCROLL_STEP_RIGHT, "GTK_SCROLL_STEP_RIGHT", "step-right" },
      { GTK_SCROLL_PAGE_LEFT, "GTK_SCROLL_PAGE_LEFT", "page-left" },
      { GTK_SCROLL_PAGE_RIGHT, "GTK_SCROLL_PAGE_RIGHT", "page-right" },
      { GTK_SCROLL_START, "GTK_SCROLL_START", "start" },
      { GTK_SCROLL_END, "GTK_SCROLL_END", "end" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkScrollType"), values);
  }
  return etype;
}
GType
gtk_selection_mode_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_SELECTION_NONE, "GTK_SELECTION_NONE", "none" },
      { GTK_SELECTION_SINGLE, "GTK_SELECTION_SINGLE", "single" },
      { GTK_SELECTION_BROWSE, "GTK_SELECTION_BROWSE", "browse" },
      { GTK_SELECTION_MULTIPLE, "GTK_SELECTION_MULTIPLE", "multiple" },
      { GTK_SELECTION_EXTENDED, "GTK_SELECTION_EXTENDED", "extended" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkSelectionMode"), values);
  }
  return etype;
}
GType
gtk_shadow_type_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_SHADOW_NONE, "GTK_SHADOW_NONE", "none" },
      { GTK_SHADOW_IN, "GTK_SHADOW_IN", "in" },
      { GTK_SHADOW_OUT, "GTK_SHADOW_OUT", "out" },
      { GTK_SHADOW_ETCHED_IN, "GTK_SHADOW_ETCHED_IN", "etched-in" },
      { GTK_SHADOW_ETCHED_OUT, "GTK_SHADOW_ETCHED_OUT", "etched-out" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkShadowType"), values);
  }
  return etype;
}
GType
gtk_state_type_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_STATE_NORMAL, "GTK_STATE_NORMAL", "normal" },
      { GTK_STATE_ACTIVE, "GTK_STATE_ACTIVE", "active" },
      { GTK_STATE_PRELIGHT, "GTK_STATE_PRELIGHT", "prelight" },
      { GTK_STATE_SELECTED, "GTK_STATE_SELECTED", "selected" },
      { GTK_STATE_INSENSITIVE, "GTK_STATE_INSENSITIVE", "insensitive" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkStateType"), values);
  }
  return etype;
}
GType
gtk_submenu_direction_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_DIRECTION_LEFT, "GTK_DIRECTION_LEFT", "left" },
      { GTK_DIRECTION_RIGHT, "GTK_DIRECTION_RIGHT", "right" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkSubmenuDirection"), values);
  }
  return etype;
}
GType
gtk_submenu_placement_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_TOP_BOTTOM, "GTK_TOP_BOTTOM", "top-bottom" },
      { GTK_LEFT_RIGHT, "GTK_LEFT_RIGHT", "left-right" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkSubmenuPlacement"), values);
  }
  return etype;
}
GType
gtk_toolbar_style_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_TOOLBAR_ICONS, "GTK_TOOLBAR_ICONS", "icons" },
      { GTK_TOOLBAR_TEXT, "GTK_TOOLBAR_TEXT", "text" },
      { GTK_TOOLBAR_BOTH, "GTK_TOOLBAR_BOTH", "both" },
      { GTK_TOOLBAR_BOTH_HORIZ, "GTK_TOOLBAR_BOTH_HORIZ", "both-horiz" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkToolbarStyle"), values);
  }
  return etype;
}
GType
gtk_update_type_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_UPDATE_CONTINUOUS, "GTK_UPDATE_CONTINUOUS", "continuous" },
      { GTK_UPDATE_DISCONTINUOUS, "GTK_UPDATE_DISCONTINUOUS", "discontinuous" },
      { GTK_UPDATE_DELAYED, "GTK_UPDATE_DELAYED", "delayed" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkUpdateType"), values);
  }
  return etype;
}
GType
gtk_visibility_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_VISIBILITY_NONE, "GTK_VISIBILITY_NONE", "none" },
      { GTK_VISIBILITY_PARTIAL, "GTK_VISIBILITY_PARTIAL", "partial" },
      { GTK_VISIBILITY_FULL, "GTK_VISIBILITY_FULL", "full" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkVisibility"), values);
  }
  return etype;
}
GType
gtk_window_position_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_WIN_POS_NONE, "GTK_WIN_POS_NONE", "none" },
      { GTK_WIN_POS_CENTER, "GTK_WIN_POS_CENTER", "center" },
      { GTK_WIN_POS_MOUSE, "GTK_WIN_POS_MOUSE", "mouse" },
      { GTK_WIN_POS_CENTER_ALWAYS, "GTK_WIN_POS_CENTER_ALWAYS", "center-always" },
      { GTK_WIN_POS_CENTER_ON_PARENT, "GTK_WIN_POS_CENTER_ON_PARENT", "center-on-parent" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkWindowPosition"), values);
  }
  return etype;
}
GType
gtk_window_type_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_WINDOW_TOPLEVEL, "GTK_WINDOW_TOPLEVEL", "toplevel" },
      { GTK_WINDOW_POPUP, "GTK_WINDOW_POPUP", "popup" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkWindowType"), values);
  }
  return etype;
}
GType
gtk_wrap_mode_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_WRAP_NONE, "GTK_WRAP_NONE", "none" },
      { GTK_WRAP_CHAR, "GTK_WRAP_CHAR", "char" },
      { GTK_WRAP_WORD, "GTK_WRAP_WORD", "word" },
      { GTK_WRAP_WORD_CHAR, "GTK_WRAP_WORD_CHAR", "word-char" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkWrapMode"), values);
  }
  return etype;
}
GType
gtk_sort_type_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_SORT_ASCENDING, "GTK_SORT_ASCENDING", "ascending" },
      { GTK_SORT_DESCENDING, "GTK_SORT_DESCENDING", "descending" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkSortType"), values);
  }
  return etype;
}
GType
gtk_im_preedit_style_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_IM_PREEDIT_NOTHING, "GTK_IM_PREEDIT_NOTHING", "nothing" },
      { GTK_IM_PREEDIT_CALLBACK, "GTK_IM_PREEDIT_CALLBACK", "callback" },
      { GTK_IM_PREEDIT_NONE, "GTK_IM_PREEDIT_NONE", "none" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkIMPreeditStyle"), values);
  }
  return etype;
}
GType
gtk_im_status_style_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_IM_STATUS_NOTHING, "GTK_IM_STATUS_NOTHING", "nothing" },
      { GTK_IM_STATUS_CALLBACK, "GTK_IM_STATUS_CALLBACK", "callback" },
      { GTK_IM_STATUS_NONE, "GTK_IM_STATUS_NONE", "none" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkIMStatusStyle"), values);
  }
  return etype;
}
GType
gtk_pack_direction_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_PACK_DIRECTION_LTR, "GTK_PACK_DIRECTION_LTR", "ltr" },
      { GTK_PACK_DIRECTION_RTL, "GTK_PACK_DIRECTION_RTL", "rtl" },
      { GTK_PACK_DIRECTION_TTB, "GTK_PACK_DIRECTION_TTB", "ttb" },
      { GTK_PACK_DIRECTION_BTT, "GTK_PACK_DIRECTION_BTT", "btt" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkPackDirection"), values);
  }
  return etype;
}
GType
gtk_print_pages_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_PRINT_PAGES_ALL, "GTK_PRINT_PAGES_ALL", "all" },
      { GTK_PRINT_PAGES_CURRENT, "GTK_PRINT_PAGES_CURRENT", "current" },
      { GTK_PRINT_PAGES_RANGES, "GTK_PRINT_PAGES_RANGES", "ranges" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkPrintPages"), values);
  }
  return etype;
}
GType
gtk_page_set_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_PAGE_SET_ALL, "GTK_PAGE_SET_ALL", "all" },
      { GTK_PAGE_SET_EVEN, "GTK_PAGE_SET_EVEN", "even" },
      { GTK_PAGE_SET_ODD, "GTK_PAGE_SET_ODD", "odd" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkPageSet"), values);
  }
  return etype;
}
GType
gtk_page_orientation_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_PAGE_ORIENTATION_PORTRAIT, "GTK_PAGE_ORIENTATION_PORTRAIT", "portrait" },
      { GTK_PAGE_ORIENTATION_LANDSCAPE, "GTK_PAGE_ORIENTATION_LANDSCAPE", "landscape" },
      { GTK_PAGE_ORIENTATION_REVERSE_PORTRAIT, "GTK_PAGE_ORIENTATION_REVERSE_PORTRAIT", "reverse-portrait" },
      { GTK_PAGE_ORIENTATION_REVERSE_LANDSCAPE, "GTK_PAGE_ORIENTATION_REVERSE_LANDSCAPE", "reverse-landscape" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkPageOrientation"), values);
  }
  return etype;
}
GType
gtk_print_quality_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_PRINT_QUALITY_LOW, "GTK_PRINT_QUALITY_LOW", "low" },
      { GTK_PRINT_QUALITY_NORMAL, "GTK_PRINT_QUALITY_NORMAL", "normal" },
      { GTK_PRINT_QUALITY_HIGH, "GTK_PRINT_QUALITY_HIGH", "high" },
      { GTK_PRINT_QUALITY_DRAFT, "GTK_PRINT_QUALITY_DRAFT", "draft" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkPrintQuality"), values);
  }
  return etype;
}
GType
gtk_print_duplex_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_PRINT_DUPLEX_SIMPLEX, "GTK_PRINT_DUPLEX_SIMPLEX", "simplex" },
      { GTK_PRINT_DUPLEX_HORIZONTAL, "GTK_PRINT_DUPLEX_HORIZONTAL", "horizontal" },
      { GTK_PRINT_DUPLEX_VERTICAL, "GTK_PRINT_DUPLEX_VERTICAL", "vertical" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkPrintDuplex"), values);
  }
  return etype;
}
GType
gtk_unit_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_UNIT_PIXEL, "GTK_UNIT_PIXEL", "pixel" },
      { GTK_UNIT_POINTS, "GTK_UNIT_POINTS", "points" },
      { GTK_UNIT_INCH, "GTK_UNIT_INCH", "inch" },
      { GTK_UNIT_MM, "GTK_UNIT_MM", "mm" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkUnit"), values);
  }
  return etype;
}
GType
gtk_tree_view_grid_lines_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_TREE_VIEW_GRID_LINES_NONE, "GTK_TREE_VIEW_GRID_LINES_NONE", "none" },
      { GTK_TREE_VIEW_GRID_LINES_HORIZONTAL, "GTK_TREE_VIEW_GRID_LINES_HORIZONTAL", "horizontal" },
      { GTK_TREE_VIEW_GRID_LINES_VERTICAL, "GTK_TREE_VIEW_GRID_LINES_VERTICAL", "vertical" },
      { GTK_TREE_VIEW_GRID_LINES_BOTH, "GTK_TREE_VIEW_GRID_LINES_BOTH", "both" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkTreeViewGridLines"), values);
  }
  return etype;
}
GType
gtk_drag_result_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_DRAG_RESULT_SUCCESS, "GTK_DRAG_RESULT_SUCCESS", "success" },
      { GTK_DRAG_RESULT_NO_TARGET, "GTK_DRAG_RESULT_NO_TARGET", "no-target" },
      { GTK_DRAG_RESULT_USER_CANCELLED, "GTK_DRAG_RESULT_USER_CANCELLED", "user-cancelled" },
      { GTK_DRAG_RESULT_TIMEOUT_EXPIRED, "GTK_DRAG_RESULT_TIMEOUT_EXPIRED", "timeout-expired" },
      { GTK_DRAG_RESULT_GRAB_BROKEN, "GTK_DRAG_RESULT_GRAB_BROKEN", "grab-broken" },
      { GTK_DRAG_RESULT_ERROR, "GTK_DRAG_RESULT_ERROR", "error" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkDragResult"), values);
  }
  return etype;
}

/* enumerations from "gtkfilechooser.h" */
GType
gtk_file_chooser_action_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_FILE_CHOOSER_ACTION_OPEN, "GTK_FILE_CHOOSER_ACTION_OPEN", "open" },
      { GTK_FILE_CHOOSER_ACTION_SAVE, "GTK_FILE_CHOOSER_ACTION_SAVE", "save" },
      { GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER, "GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER", "select-folder" },
      { GTK_FILE_CHOOSER_ACTION_CREATE_FOLDER, "GTK_FILE_CHOOSER_ACTION_CREATE_FOLDER", "create-folder" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkFileChooserAction"), values);
  }
  return etype;
}
GType
gtk_file_chooser_confirmation_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_FILE_CHOOSER_CONFIRMATION_CONFIRM, "GTK_FILE_CHOOSER_CONFIRMATION_CONFIRM", "confirm" },
      { GTK_FILE_CHOOSER_CONFIRMATION_ACCEPT_FILENAME, "GTK_FILE_CHOOSER_CONFIRMATION_ACCEPT_FILENAME", "accept-filename" },
      { GTK_FILE_CHOOSER_CONFIRMATION_SELECT_AGAIN, "GTK_FILE_CHOOSER_CONFIRMATION_SELECT_AGAIN", "select-again" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkFileChooserConfirmation"), values);
  }
  return etype;
}
GType
gtk_file_chooser_error_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_FILE_CHOOSER_ERROR_NONEXISTENT, "GTK_FILE_CHOOSER_ERROR_NONEXISTENT", "nonexistent" },
      { GTK_FILE_CHOOSER_ERROR_BAD_FILENAME, "GTK_FILE_CHOOSER_ERROR_BAD_FILENAME", "bad-filename" },
      { GTK_FILE_CHOOSER_ERROR_ALREADY_EXISTS, "GTK_FILE_CHOOSER_ERROR_ALREADY_EXISTS", "already-exists" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkFileChooserError"), values);
  }
  return etype;
}

/* enumerations from "gtkfilefilter.h" */
GType
gtk_file_filter_flags_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GFlagsValue values[] = {
      { GTK_FILE_FILTER_FILENAME, "GTK_FILE_FILTER_FILENAME", "filename" },
      { GTK_FILE_FILTER_URI, "GTK_FILE_FILTER_URI", "uri" },
      { GTK_FILE_FILTER_DISPLAY_NAME, "GTK_FILE_FILTER_DISPLAY_NAME", "display-name" },
      { GTK_FILE_FILTER_MIME_TYPE, "GTK_FILE_FILTER_MIME_TYPE", "mime-type" },
      { 0, NULL, NULL }
    };
    etype = g_flags_register_static (g_intern_static_string ("GtkFileFilterFlags"), values);
  }
  return etype;
}

/* enumerations from "gtkicontheme.h" */
GType
gtk_icon_lookup_flags_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GFlagsValue values[] = {
      { GTK_ICON_LOOKUP_NO_SVG, "GTK_ICON_LOOKUP_NO_SVG", "no-svg" },
      { GTK_ICON_LOOKUP_FORCE_SVG, "GTK_ICON_LOOKUP_FORCE_SVG", "force-svg" },
      { GTK_ICON_LOOKUP_USE_BUILTIN, "GTK_ICON_LOOKUP_USE_BUILTIN", "use-builtin" },
      { GTK_ICON_LOOKUP_GENERIC_FALLBACK, "GTK_ICON_LOOKUP_GENERIC_FALLBACK", "generic-fallback" },
      { 0, NULL, NULL }
    };
    etype = g_flags_register_static (g_intern_static_string ("GtkIconLookupFlags"), values);
  }
  return etype;
}
GType
gtk_icon_theme_error_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_ICON_THEME_NOT_FOUND, "GTK_ICON_THEME_NOT_FOUND", "not-found" },
      { GTK_ICON_THEME_FAILED, "GTK_ICON_THEME_FAILED", "failed" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkIconThemeError"), values);
  }
  return etype;
}

/* enumerations from "gtkiconview.h" */
GType
gtk_icon_view_drop_position_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_ICON_VIEW_NO_DROP, "GTK_ICON_VIEW_NO_DROP", "no-drop" },
      { GTK_ICON_VIEW_DROP_INTO, "GTK_ICON_VIEW_DROP_INTO", "drop-into" },
      { GTK_ICON_VIEW_DROP_LEFT, "GTK_ICON_VIEW_DROP_LEFT", "drop-left" },
      { GTK_ICON_VIEW_DROP_RIGHT, "GTK_ICON_VIEW_DROP_RIGHT", "drop-right" },
      { GTK_ICON_VIEW_DROP_ABOVE, "GTK_ICON_VIEW_DROP_ABOVE", "drop-above" },
      { GTK_ICON_VIEW_DROP_BELOW, "GTK_ICON_VIEW_DROP_BELOW", "drop-below" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkIconViewDropPosition"), values);
  }
  return etype;
}

/* enumerations from "gtkimage.h" */
GType
gtk_image_type_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_IMAGE_EMPTY, "GTK_IMAGE_EMPTY", "empty" },
      { GTK_IMAGE_PIXMAP, "GTK_IMAGE_PIXMAP", "pixmap" },
      { GTK_IMAGE_IMAGE, "GTK_IMAGE_IMAGE", "image" },
      { GTK_IMAGE_PIXBUF, "GTK_IMAGE_PIXBUF", "pixbuf" },
      { GTK_IMAGE_STOCK, "GTK_IMAGE_STOCK", "stock" },
      { GTK_IMAGE_ICON_SET, "GTK_IMAGE_ICON_SET", "icon-set" },
      { GTK_IMAGE_ANIMATION, "GTK_IMAGE_ANIMATION", "animation" },
      { GTK_IMAGE_ICON_NAME, "GTK_IMAGE_ICON_NAME", "icon-name" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkImageType"), values);
  }
  return etype;
}

/* enumerations from "gtkmessagedialog.h" */
GType
gtk_message_type_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_MESSAGE_INFO, "GTK_MESSAGE_INFO", "info" },
      { GTK_MESSAGE_WARNING, "GTK_MESSAGE_WARNING", "warning" },
      { GTK_MESSAGE_QUESTION, "GTK_MESSAGE_QUESTION", "question" },
      { GTK_MESSAGE_ERROR, "GTK_MESSAGE_ERROR", "error" },
      { GTK_MESSAGE_OTHER, "GTK_MESSAGE_OTHER", "other" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkMessageType"), values);
  }
  return etype;
}
GType
gtk_buttons_type_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_BUTTONS_NONE, "GTK_BUTTONS_NONE", "none" },
      { GTK_BUTTONS_OK, "GTK_BUTTONS_OK", "ok" },
      { GTK_BUTTONS_CLOSE, "GTK_BUTTONS_CLOSE", "close" },
      { GTK_BUTTONS_CANCEL, "GTK_BUTTONS_CANCEL", "cancel" },
      { GTK_BUTTONS_YES_NO, "GTK_BUTTONS_YES_NO", "yes-no" },
      { GTK_BUTTONS_OK_CANCEL, "GTK_BUTTONS_OK_CANCEL", "ok-cancel" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkButtonsType"), values);
  }
  return etype;
}

/* enumerations from "gtknotebook.h" */
GType
gtk_notebook_tab_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_NOTEBOOK_TAB_FIRST, "GTK_NOTEBOOK_TAB_FIRST", "first" },
      { GTK_NOTEBOOK_TAB_LAST, "GTK_NOTEBOOK_TAB_LAST", "last" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkNotebookTab"), values);
  }
  return etype;
}

/* enumerations from "gtkobject.h" */
GType
gtk_object_flags_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GFlagsValue values[] = {
      { GTK_IN_DESTRUCTION, "GTK_IN_DESTRUCTION", "in-destruction" },
      { GTK_FLOATING, "GTK_FLOATING", "floating" },
      { GTK_RESERVED_1, "GTK_RESERVED_1", "reserved-1" },
      { GTK_RESERVED_2, "GTK_RESERVED_2", "reserved-2" },
      { 0, NULL, NULL }
    };
    etype = g_flags_register_static (g_intern_static_string ("GtkObjectFlags"), values);
  }
  return etype;
}
GType
gtk_arg_flags_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GFlagsValue values[] = {
      { GTK_ARG_READABLE, "GTK_ARG_READABLE", "readable" },
      { GTK_ARG_WRITABLE, "GTK_ARG_WRITABLE", "writable" },
      { GTK_ARG_CONSTRUCT, "GTK_ARG_CONSTRUCT", "construct" },
      { GTK_ARG_CONSTRUCT_ONLY, "GTK_ARG_CONSTRUCT_ONLY", "construct-only" },
      { GTK_ARG_CHILD_ARG, "GTK_ARG_CHILD_ARG", "child-arg" },
      { 0, NULL, NULL }
    };
    etype = g_flags_register_static (g_intern_static_string ("GtkArgFlags"), values);
  }
  return etype;
}

/* enumerations from "gtkprintoperation.h" */
GType
gtk_print_status_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_PRINT_STATUS_INITIAL, "GTK_PRINT_STATUS_INITIAL", "initial" },
      { GTK_PRINT_STATUS_PREPARING, "GTK_PRINT_STATUS_PREPARING", "preparing" },
      { GTK_PRINT_STATUS_GENERATING_DATA, "GTK_PRINT_STATUS_GENERATING_DATA", "generating-data" },
      { GTK_PRINT_STATUS_SENDING_DATA, "GTK_PRINT_STATUS_SENDING_DATA", "sending-data" },
      { GTK_PRINT_STATUS_PENDING, "GTK_PRINT_STATUS_PENDING", "pending" },
      { GTK_PRINT_STATUS_PENDING_ISSUE, "GTK_PRINT_STATUS_PENDING_ISSUE", "pending-issue" },
      { GTK_PRINT_STATUS_PRINTING, "GTK_PRINT_STATUS_PRINTING", "printing" },
      { GTK_PRINT_STATUS_FINISHED, "GTK_PRINT_STATUS_FINISHED", "finished" },
      { GTK_PRINT_STATUS_FINISHED_ABORTED, "GTK_PRINT_STATUS_FINISHED_ABORTED", "finished-aborted" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkPrintStatus"), values);
  }
  return etype;
}
GType
gtk_print_operation_result_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_PRINT_OPERATION_RESULT_ERROR, "GTK_PRINT_OPERATION_RESULT_ERROR", "error" },
      { GTK_PRINT_OPERATION_RESULT_APPLY, "GTK_PRINT_OPERATION_RESULT_APPLY", "apply" },
      { GTK_PRINT_OPERATION_RESULT_CANCEL, "GTK_PRINT_OPERATION_RESULT_CANCEL", "cancel" },
      { GTK_PRINT_OPERATION_RESULT_IN_PROGRESS, "GTK_PRINT_OPERATION_RESULT_IN_PROGRESS", "in-progress" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkPrintOperationResult"), values);
  }
  return etype;
}
GType
gtk_print_operation_action_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_PRINT_OPERATION_ACTION_PRINT_DIALOG, "GTK_PRINT_OPERATION_ACTION_PRINT_DIALOG", "print-dialog" },
      { GTK_PRINT_OPERATION_ACTION_PRINT, "GTK_PRINT_OPERATION_ACTION_PRINT", "print" },
      { GTK_PRINT_OPERATION_ACTION_PREVIEW, "GTK_PRINT_OPERATION_ACTION_PREVIEW", "preview" },
      { GTK_PRINT_OPERATION_ACTION_EXPORT, "GTK_PRINT_OPERATION_ACTION_EXPORT", "export" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkPrintOperationAction"), values);
  }
  return etype;
}
GType
gtk_print_error_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_PRINT_ERROR_GENERAL, "GTK_PRINT_ERROR_GENERAL", "general" },
      { GTK_PRINT_ERROR_INTERNAL_ERROR, "GTK_PRINT_ERROR_INTERNAL_ERROR", "internal-error" },
      { GTK_PRINT_ERROR_NOMEM, "GTK_PRINT_ERROR_NOMEM", "nomem" },
      { GTK_PRINT_ERROR_INVALID_FILE, "GTK_PRINT_ERROR_INVALID_FILE", "invalid-file" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkPrintError"), values);
  }
  return etype;
}

/* enumerations from "gtkprivate.h" */
GType
gtk_private_flags_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GFlagsValue values[] = {
      { PRIVATE_GTK_USER_STYLE, "PRIVATE_GTK_USER_STYLE", "user-style" },
      { PRIVATE_GTK_RESIZE_PENDING, "PRIVATE_GTK_RESIZE_PENDING", "resize-pending" },
      { PRIVATE_GTK_LEAVE_PENDING, "PRIVATE_GTK_LEAVE_PENDING", "leave-pending" },
      { PRIVATE_GTK_HAS_SHAPE_MASK, "PRIVATE_GTK_HAS_SHAPE_MASK", "has-shape-mask" },
      { PRIVATE_GTK_IN_REPARENT, "PRIVATE_GTK_IN_REPARENT", "in-reparent" },
      { PRIVATE_GTK_DIRECTION_SET, "PRIVATE_GTK_DIRECTION_SET", "direction-set" },
      { PRIVATE_GTK_DIRECTION_LTR, "PRIVATE_GTK_DIRECTION_LTR", "direction-ltr" },
      { PRIVATE_GTK_ANCHORED, "PRIVATE_GTK_ANCHORED", "anchored" },
      { PRIVATE_GTK_CHILD_VISIBLE, "PRIVATE_GTK_CHILD_VISIBLE", "child-visible" },
      { PRIVATE_GTK_REDRAW_ON_ALLOC, "PRIVATE_GTK_REDRAW_ON_ALLOC", "redraw-on-alloc" },
      { PRIVATE_GTK_ALLOC_NEEDED, "PRIVATE_GTK_ALLOC_NEEDED", "alloc-needed" },
      { PRIVATE_GTK_REQUEST_NEEDED, "PRIVATE_GTK_REQUEST_NEEDED", "request-needed" },
      { 0, NULL, NULL }
    };
    etype = g_flags_register_static (g_intern_static_string ("GtkPrivateFlags"), values);
  }
  return etype;
}

/* enumerations from "gtkprogressbar.h" */
GType
gtk_progress_bar_style_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_PROGRESS_CONTINUOUS, "GTK_PROGRESS_CONTINUOUS", "continuous" },
      { GTK_PROGRESS_DISCRETE, "GTK_PROGRESS_DISCRETE", "discrete" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkProgressBarStyle"), values);
  }
  return etype;
}
GType
gtk_progress_bar_orientation_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_PROGRESS_LEFT_TO_RIGHT, "GTK_PROGRESS_LEFT_TO_RIGHT", "left-to-right" },
      { GTK_PROGRESS_RIGHT_TO_LEFT, "GTK_PROGRESS_RIGHT_TO_LEFT", "right-to-left" },
      { GTK_PROGRESS_BOTTOM_TO_TOP, "GTK_PROGRESS_BOTTOM_TO_TOP", "bottom-to-top" },
      { GTK_PROGRESS_TOP_TO_BOTTOM, "GTK_PROGRESS_TOP_TO_BOTTOM", "top-to-bottom" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkProgressBarOrientation"), values);
  }
  return etype;
}

/* enumerations from "gtkrc.h" */
GType
gtk_rc_flags_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GFlagsValue values[] = {
      { GTK_RC_FG, "GTK_RC_FG", "fg" },
      { GTK_RC_BG, "GTK_RC_BG", "bg" },
      { GTK_RC_TEXT, "GTK_RC_TEXT", "text" },
      { GTK_RC_BASE, "GTK_RC_BASE", "base" },
      { 0, NULL, NULL }
    };
    etype = g_flags_register_static (g_intern_static_string ("GtkRcFlags"), values);
  }
  return etype;
}
GType
gtk_rc_token_type_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_RC_TOKEN_INVALID, "GTK_RC_TOKEN_INVALID", "invalid" },
      { GTK_RC_TOKEN_INCLUDE, "GTK_RC_TOKEN_INCLUDE", "include" },
      { GTK_RC_TOKEN_NORMAL, "GTK_RC_TOKEN_NORMAL", "normal" },
      { GTK_RC_TOKEN_ACTIVE, "GTK_RC_TOKEN_ACTIVE", "active" },
      { GTK_RC_TOKEN_PRELIGHT, "GTK_RC_TOKEN_PRELIGHT", "prelight" },
      { GTK_RC_TOKEN_SELECTED, "GTK_RC_TOKEN_SELECTED", "selected" },
      { GTK_RC_TOKEN_INSENSITIVE, "GTK_RC_TOKEN_INSENSITIVE", "insensitive" },
      { GTK_RC_TOKEN_FG, "GTK_RC_TOKEN_FG", "fg" },
      { GTK_RC_TOKEN_BG, "GTK_RC_TOKEN_BG", "bg" },
      { GTK_RC_TOKEN_TEXT, "GTK_RC_TOKEN_TEXT", "text" },
      { GTK_RC_TOKEN_BASE, "GTK_RC_TOKEN_BASE", "base" },
      { GTK_RC_TOKEN_XTHICKNESS, "GTK_RC_TOKEN_XTHICKNESS", "xthickness" },
      { GTK_RC_TOKEN_YTHICKNESS, "GTK_RC_TOKEN_YTHICKNESS", "ythickness" },
      { GTK_RC_TOKEN_FONT, "GTK_RC_TOKEN_FONT", "font" },
      { GTK_RC_TOKEN_FONTSET, "GTK_RC_TOKEN_FONTSET", "fontset" },
      { GTK_RC_TOKEN_FONT_NAME, "GTK_RC_TOKEN_FONT_NAME", "font-name" },
      { GTK_RC_TOKEN_BG_PIXMAP, "GTK_RC_TOKEN_BG_PIXMAP", "bg-pixmap" },
      { GTK_RC_TOKEN_PIXMAP_PATH, "GTK_RC_TOKEN_PIXMAP_PATH", "pixmap-path" },
      { GTK_RC_TOKEN_STYLE, "GTK_RC_TOKEN_STYLE", "style" },
      { GTK_RC_TOKEN_BINDING, "GTK_RC_TOKEN_BINDING", "binding" },
      { GTK_RC_TOKEN_BIND, "GTK_RC_TOKEN_BIND", "bind" },
      { GTK_RC_TOKEN_WIDGET, "GTK_RC_TOKEN_WIDGET", "widget" },
      { GTK_RC_TOKEN_WIDGET_CLASS, "GTK_RC_TOKEN_WIDGET_CLASS", "widget-class" },
      { GTK_RC_TOKEN_CLASS, "GTK_RC_TOKEN_CLASS", "class" },
      { GTK_RC_TOKEN_LOWEST, "GTK_RC_TOKEN_LOWEST", "lowest" },
      { GTK_RC_TOKEN_GTK, "GTK_RC_TOKEN_GTK", "gtk" },
      { GTK_RC_TOKEN_APPLICATION, "GTK_RC_TOKEN_APPLICATION", "application" },
      { GTK_RC_TOKEN_THEME, "GTK_RC_TOKEN_THEME", "theme" },
      { GTK_RC_TOKEN_RC, "GTK_RC_TOKEN_RC", "rc" },
      { GTK_RC_TOKEN_HIGHEST, "GTK_RC_TOKEN_HIGHEST", "highest" },
      { GTK_RC_TOKEN_ENGINE, "GTK_RC_TOKEN_ENGINE", "engine" },
      { GTK_RC_TOKEN_MODULE_PATH, "GTK_RC_TOKEN_MODULE_PATH", "module-path" },
      { GTK_RC_TOKEN_IM_MODULE_PATH, "GTK_RC_TOKEN_IM_MODULE_PATH", "im-module-path" },
      { GTK_RC_TOKEN_IM_MODULE_FILE, "GTK_RC_TOKEN_IM_MODULE_FILE", "im-module-file" },
      { GTK_RC_TOKEN_STOCK, "GTK_RC_TOKEN_STOCK", "stock" },
      { GTK_RC_TOKEN_LTR, "GTK_RC_TOKEN_LTR", "ltr" },
      { GTK_RC_TOKEN_RTL, "GTK_RC_TOKEN_RTL", "rtl" },
      { GTK_RC_TOKEN_COLOR, "GTK_RC_TOKEN_COLOR", "color" },
      { GTK_RC_TOKEN_UNBIND, "GTK_RC_TOKEN_UNBIND", "unbind" },
      { GTK_RC_TOKEN_LAST, "GTK_RC_TOKEN_LAST", "last" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkRcTokenType"), values);
  }
  return etype;
}

/* enumerations from "gtkrecentchooser.h" */
GType
gtk_recent_sort_type_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_RECENT_SORT_NONE, "GTK_RECENT_SORT_NONE", "none" },
      { GTK_RECENT_SORT_MRU, "GTK_RECENT_SORT_MRU", "mru" },
      { GTK_RECENT_SORT_LRU, "GTK_RECENT_SORT_LRU", "lru" },
      { GTK_RECENT_SORT_CUSTOM, "GTK_RECENT_SORT_CUSTOM", "custom" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkRecentSortType"), values);
  }
  return etype;
}
GType
gtk_recent_chooser_error_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_RECENT_CHOOSER_ERROR_NOT_FOUND, "GTK_RECENT_CHOOSER_ERROR_NOT_FOUND", "not-found" },
      { GTK_RECENT_CHOOSER_ERROR_INVALID_URI, "GTK_RECENT_CHOOSER_ERROR_INVALID_URI", "invalid-uri" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkRecentChooserError"), values);
  }
  return etype;
}

/* enumerations from "gtkrecentfilter.h" */
GType
gtk_recent_filter_flags_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GFlagsValue values[] = {
      { GTK_RECENT_FILTER_URI, "GTK_RECENT_FILTER_URI", "uri" },
      { GTK_RECENT_FILTER_DISPLAY_NAME, "GTK_RECENT_FILTER_DISPLAY_NAME", "display-name" },
      { GTK_RECENT_FILTER_MIME_TYPE, "GTK_RECENT_FILTER_MIME_TYPE", "mime-type" },
      { GTK_RECENT_FILTER_APPLICATION, "GTK_RECENT_FILTER_APPLICATION", "application" },
      { GTK_RECENT_FILTER_GROUP, "GTK_RECENT_FILTER_GROUP", "group" },
      { GTK_RECENT_FILTER_AGE, "GTK_RECENT_FILTER_AGE", "age" },
      { 0, NULL, NULL }
    };
    etype = g_flags_register_static (g_intern_static_string ("GtkRecentFilterFlags"), values);
  }
  return etype;
}

/* enumerations from "gtkrecentmanager.h" */
GType
gtk_recent_manager_error_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_RECENT_MANAGER_ERROR_NOT_FOUND, "GTK_RECENT_MANAGER_ERROR_NOT_FOUND", "not-found" },
      { GTK_RECENT_MANAGER_ERROR_INVALID_URI, "GTK_RECENT_MANAGER_ERROR_INVALID_URI", "invalid-uri" },
      { GTK_RECENT_MANAGER_ERROR_INVALID_ENCODING, "GTK_RECENT_MANAGER_ERROR_INVALID_ENCODING", "invalid-encoding" },
      { GTK_RECENT_MANAGER_ERROR_NOT_REGISTERED, "GTK_RECENT_MANAGER_ERROR_NOT_REGISTERED", "not-registered" },
      { GTK_RECENT_MANAGER_ERROR_READ, "GTK_RECENT_MANAGER_ERROR_READ", "read" },
      { GTK_RECENT_MANAGER_ERROR_WRITE, "GTK_RECENT_MANAGER_ERROR_WRITE", "write" },
      { GTK_RECENT_MANAGER_ERROR_UNKNOWN, "GTK_RECENT_MANAGER_ERROR_UNKNOWN", "unknown" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkRecentManagerError"), values);
  }
  return etype;
}

/* enumerations from "gtksizegroup.h" */
GType
gtk_size_group_mode_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_SIZE_GROUP_NONE, "GTK_SIZE_GROUP_NONE", "none" },
      { GTK_SIZE_GROUP_HORIZONTAL, "GTK_SIZE_GROUP_HORIZONTAL", "horizontal" },
      { GTK_SIZE_GROUP_VERTICAL, "GTK_SIZE_GROUP_VERTICAL", "vertical" },
      { GTK_SIZE_GROUP_BOTH, "GTK_SIZE_GROUP_BOTH", "both" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkSizeGroupMode"), values);
  }
  return etype;
}

/* enumerations from "gtkspinbutton.h" */
GType
gtk_spin_button_update_policy_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_UPDATE_ALWAYS, "GTK_UPDATE_ALWAYS", "always" },
      { GTK_UPDATE_IF_VALID, "GTK_UPDATE_IF_VALID", "if-valid" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkSpinButtonUpdatePolicy"), values);
  }
  return etype;
}
GType
gtk_spin_type_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_SPIN_STEP_FORWARD, "GTK_SPIN_STEP_FORWARD", "step-forward" },
      { GTK_SPIN_STEP_BACKWARD, "GTK_SPIN_STEP_BACKWARD", "step-backward" },
      { GTK_SPIN_PAGE_FORWARD, "GTK_SPIN_PAGE_FORWARD", "page-forward" },
      { GTK_SPIN_PAGE_BACKWARD, "GTK_SPIN_PAGE_BACKWARD", "page-backward" },
      { GTK_SPIN_HOME, "GTK_SPIN_HOME", "home" },
      { GTK_SPIN_END, "GTK_SPIN_END", "end" },
      { GTK_SPIN_USER_DEFINED, "GTK_SPIN_USER_DEFINED", "user-defined" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkSpinType"), values);
  }
  return etype;
}

/* enumerations from "gtktextbuffer.h" */
GType
gtk_text_buffer_target_info_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_TEXT_BUFFER_TARGET_INFO_BUFFER_CONTENTS, "GTK_TEXT_BUFFER_TARGET_INFO_BUFFER_CONTENTS", "buffer-contents" },
      { GTK_TEXT_BUFFER_TARGET_INFO_RICH_TEXT, "GTK_TEXT_BUFFER_TARGET_INFO_RICH_TEXT", "rich-text" },
      { GTK_TEXT_BUFFER_TARGET_INFO_TEXT, "GTK_TEXT_BUFFER_TARGET_INFO_TEXT", "text" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkTextBufferTargetInfo"), values);
  }
  return etype;
}

/* enumerations from "gtktextiter.h" */
GType
gtk_text_search_flags_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GFlagsValue values[] = {
      { GTK_TEXT_SEARCH_VISIBLE_ONLY, "GTK_TEXT_SEARCH_VISIBLE_ONLY", "visible-only" },
      { GTK_TEXT_SEARCH_TEXT_ONLY, "GTK_TEXT_SEARCH_TEXT_ONLY", "text-only" },
      { 0, NULL, NULL }
    };
    etype = g_flags_register_static (g_intern_static_string ("GtkTextSearchFlags"), values);
  }
  return etype;
}

/* enumerations from "gtktextview.h" */
GType
gtk_text_window_type_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_TEXT_WINDOW_PRIVATE, "GTK_TEXT_WINDOW_PRIVATE", "private" },
      { GTK_TEXT_WINDOW_WIDGET, "GTK_TEXT_WINDOW_WIDGET", "widget" },
      { GTK_TEXT_WINDOW_TEXT, "GTK_TEXT_WINDOW_TEXT", "text" },
      { GTK_TEXT_WINDOW_LEFT, "GTK_TEXT_WINDOW_LEFT", "left" },
      { GTK_TEXT_WINDOW_RIGHT, "GTK_TEXT_WINDOW_RIGHT", "right" },
      { GTK_TEXT_WINDOW_TOP, "GTK_TEXT_WINDOW_TOP", "top" },
      { GTK_TEXT_WINDOW_BOTTOM, "GTK_TEXT_WINDOW_BOTTOM", "bottom" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkTextWindowType"), values);
  }
  return etype;
}

/* enumerations from "gtktoolbar.h" */
GType
gtk_toolbar_child_type_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_TOOLBAR_CHILD_SPACE, "GTK_TOOLBAR_CHILD_SPACE", "space" },
      { GTK_TOOLBAR_CHILD_BUTTON, "GTK_TOOLBAR_CHILD_BUTTON", "button" },
      { GTK_TOOLBAR_CHILD_TOGGLEBUTTON, "GTK_TOOLBAR_CHILD_TOGGLEBUTTON", "togglebutton" },
      { GTK_TOOLBAR_CHILD_RADIOBUTTON, "GTK_TOOLBAR_CHILD_RADIOBUTTON", "radiobutton" },
      { GTK_TOOLBAR_CHILD_WIDGET, "GTK_TOOLBAR_CHILD_WIDGET", "widget" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkToolbarChildType"), values);
  }
  return etype;
}
GType
gtk_toolbar_space_style_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_TOOLBAR_SPACE_EMPTY, "GTK_TOOLBAR_SPACE_EMPTY", "empty" },
      { GTK_TOOLBAR_SPACE_LINE, "GTK_TOOLBAR_SPACE_LINE", "line" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkToolbarSpaceStyle"), values);
  }
  return etype;
}

/* enumerations from "gtktree.h" */
GType
gtk_tree_view_mode_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_TREE_VIEW_LINE, "GTK_TREE_VIEW_LINE", "line" },
      { GTK_TREE_VIEW_ITEM, "GTK_TREE_VIEW_ITEM", "item" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkTreeViewMode"), values);
  }
  return etype;
}

/* enumerations from "gtktreemodel.h" */
GType
gtk_tree_model_flags_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GFlagsValue values[] = {
      { GTK_TREE_MODEL_ITERS_PERSIST, "GTK_TREE_MODEL_ITERS_PERSIST", "iters-persist" },
      { GTK_TREE_MODEL_LIST_ONLY, "GTK_TREE_MODEL_LIST_ONLY", "list-only" },
      { 0, NULL, NULL }
    };
    etype = g_flags_register_static (g_intern_static_string ("GtkTreeModelFlags"), values);
  }
  return etype;
}

/* enumerations from "gtktreeview.h" */
GType
gtk_tree_view_drop_position_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_TREE_VIEW_DROP_BEFORE, "GTK_TREE_VIEW_DROP_BEFORE", "before" },
      { GTK_TREE_VIEW_DROP_AFTER, "GTK_TREE_VIEW_DROP_AFTER", "after" },
      { GTK_TREE_VIEW_DROP_INTO_OR_BEFORE, "GTK_TREE_VIEW_DROP_INTO_OR_BEFORE", "into-or-before" },
      { GTK_TREE_VIEW_DROP_INTO_OR_AFTER, "GTK_TREE_VIEW_DROP_INTO_OR_AFTER", "into-or-after" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkTreeViewDropPosition"), values);
  }
  return etype;
}

/* enumerations from "gtktreeviewcolumn.h" */
GType
gtk_tree_view_column_sizing_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_TREE_VIEW_COLUMN_GROW_ONLY, "GTK_TREE_VIEW_COLUMN_GROW_ONLY", "grow-only" },
      { GTK_TREE_VIEW_COLUMN_AUTOSIZE, "GTK_TREE_VIEW_COLUMN_AUTOSIZE", "autosize" },
      { GTK_TREE_VIEW_COLUMN_FIXED, "GTK_TREE_VIEW_COLUMN_FIXED", "fixed" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkTreeViewColumnSizing"), values);
  }
  return etype;
}

/* enumerations from "gtkuimanager.h" */
GType
gtk_ui_manager_item_type_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GFlagsValue values[] = {
      { GTK_UI_MANAGER_AUTO, "GTK_UI_MANAGER_AUTO", "auto" },
      { GTK_UI_MANAGER_MENUBAR, "GTK_UI_MANAGER_MENUBAR", "menubar" },
      { GTK_UI_MANAGER_MENU, "GTK_UI_MANAGER_MENU", "menu" },
      { GTK_UI_MANAGER_TOOLBAR, "GTK_UI_MANAGER_TOOLBAR", "toolbar" },
      { GTK_UI_MANAGER_PLACEHOLDER, "GTK_UI_MANAGER_PLACEHOLDER", "placeholder" },
      { GTK_UI_MANAGER_POPUP, "GTK_UI_MANAGER_POPUP", "popup" },
      { GTK_UI_MANAGER_MENUITEM, "GTK_UI_MANAGER_MENUITEM", "menuitem" },
      { GTK_UI_MANAGER_TOOLITEM, "GTK_UI_MANAGER_TOOLITEM", "toolitem" },
      { GTK_UI_MANAGER_SEPARATOR, "GTK_UI_MANAGER_SEPARATOR", "separator" },
      { GTK_UI_MANAGER_ACCELERATOR, "GTK_UI_MANAGER_ACCELERATOR", "accelerator" },
      { 0, NULL, NULL }
    };
    etype = g_flags_register_static (g_intern_static_string ("GtkUIManagerItemType"), values);
  }
  return etype;
}

/* enumerations from "gtkwidget.h" */
GType
gtk_widget_flags_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GFlagsValue values[] = {
      { GTK_TOPLEVEL, "GTK_TOPLEVEL", "toplevel" },
      { GTK_NO_WINDOW, "GTK_NO_WINDOW", "no-window" },
      { GTK_REALIZED, "GTK_REALIZED", "realized" },
      { GTK_MAPPED, "GTK_MAPPED", "mapped" },
      { GTK_VISIBLE, "GTK_VISIBLE", "visible" },
      { GTK_SENSITIVE, "GTK_SENSITIVE", "sensitive" },
      { GTK_PARENT_SENSITIVE, "GTK_PARENT_SENSITIVE", "parent-sensitive" },
      { GTK_CAN_FOCUS, "GTK_CAN_FOCUS", "can-focus" },
      { GTK_HAS_FOCUS, "GTK_HAS_FOCUS", "has-focus" },
      { GTK_CAN_DEFAULT, "GTK_CAN_DEFAULT", "can-default" },
      { GTK_HAS_DEFAULT, "GTK_HAS_DEFAULT", "has-default" },
      { GTK_HAS_GRAB, "GTK_HAS_GRAB", "has-grab" },
      { GTK_RC_STYLE, "GTK_RC_STYLE", "rc-style" },
      { GTK_COMPOSITE_CHILD, "GTK_COMPOSITE_CHILD", "composite-child" },
      { GTK_NO_REPARENT, "GTK_NO_REPARENT", "no-reparent" },
      { GTK_APP_PAINTABLE, "GTK_APP_PAINTABLE", "app-paintable" },
      { GTK_RECEIVES_DEFAULT, "GTK_RECEIVES_DEFAULT", "receives-default" },
      { GTK_DOUBLE_BUFFERED, "GTK_DOUBLE_BUFFERED", "double-buffered" },
      { GTK_NO_SHOW_ALL, "GTK_NO_SHOW_ALL", "no-show-all" },
      { 0, NULL, NULL }
    };
    etype = g_flags_register_static (g_intern_static_string ("GtkWidgetFlags"), values);
  }
  return etype;
}
GType
gtk_widget_help_type_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GTK_WIDGET_HELP_TOOLTIP, "GTK_WIDGET_HELP_TOOLTIP", "tooltip" },
      { GTK_WIDGET_HELP_WHATS_THIS, "GTK_WIDGET_HELP_WHATS_THIS", "whats-this" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static (g_intern_static_string ("GtkWidgetHelpType"), values);
  }
  return etype;
}
#define __GTK_TYPE_BUILTINS_C__
#include "gtkaliasdef.c"

/* Generated data ends here */

