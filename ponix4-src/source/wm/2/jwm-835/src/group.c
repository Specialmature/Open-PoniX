/**
 * @file group.c
 * @author Joe Wingbermuehle
 * @date 2004-2006
 *
 * @brief Functions for handling window groups.
 *
 */

#include "jwm.h"
#include "group.h"
#include "client.h"
#include "icon.h"
#include "error.h"
#include "match.h"
#include "desktop.h"
#include "main.h"
#include "misc.h"
#include "settings.h"

/** What part of the window to match. */
typedef unsigned int MatchType;
#define MATCH_NAME   0  /**< Match the window name. */
#define MATCH_CLASS  1  /**< Match the window class. */

/** List of match patterns for a group. */
typedef struct PatternListType {
   char *pattern;
   MatchType match;
   struct PatternListType *next;
} PatternListType;

/** List of options for a group. */
typedef struct OptionListType {
   OptionType option;
   char *svalue;
   unsigned int uvalue;
   struct OptionListType *next;
} OptionListType;

/** List of groups. */
typedef struct GroupType {
   PatternListType *patterns;
   OptionListType *options;
   struct GroupType *next;
} GroupType;

static GroupType *groups = NULL;

static void ReleasePatternList(PatternListType *lp);
static void ReleaseOptionList(OptionListType *lp);
static void AddPattern(PatternListType **lp, const char *pattern,
                       MatchType match);
static void ApplyGroup(const GroupType *gp, ClientNode *np);

/** Destroy group data. */
void DestroyGroups()
{
   GroupType *gp;
   while(groups) {
      gp = groups->next;
      ReleasePatternList(groups->patterns);
      ReleaseOptionList(groups->options);
      Release(groups);
      groups = gp;
   }
}

/** Release a group pattern list. */
void ReleasePatternList(PatternListType *lp)
{
   PatternListType *tp;
   while(lp) {
      tp = lp->next;
      Release(lp->pattern);
      Release(lp);
      lp = tp;
   }
}

/** Release a group option list. */
void ReleaseOptionList(OptionListType *lp)
{
   OptionListType *tp;
   while(lp) {
      tp = lp->next;
      if(lp->svalue) {
         Release(lp->svalue);
      }
      Release(lp);
      lp = tp;
   }
}

/** Create an empty group. */
GroupType *CreateGroup()
{
   GroupType *tp;
   tp = Allocate(sizeof(GroupType));
   tp->patterns = NULL;
   tp->options = NULL;
   tp->next = groups;
   groups = tp;
   return tp;
}

/** Add a window class to a group. */
void AddGroupClass(GroupType *gp, const char *pattern)
{
   Assert(gp);
   if(JLIKELY(pattern)) {
      AddPattern(&gp->patterns, pattern, MATCH_CLASS);
   } else {
      Warning(_("invalid group class"));
   }
}

/** Add a window name to a group. */
void AddGroupName(GroupType *gp, const char *pattern)
{
   Assert(gp);
   if(JLIKELY(pattern)) {
      AddPattern(&gp->patterns, pattern, MATCH_NAME);
   } else {
      Warning(_("invalid group name"));
   }
}

/** Add a pattern to a pattern list. */
void AddPattern(PatternListType **lp, const char *pattern, MatchType match)
{
   PatternListType *tp;
   Assert(lp);
   Assert(pattern);
   tp = Allocate(sizeof(PatternListType));
   tp->next = *lp;
   *lp = tp;
   tp->pattern = CopyString(pattern);
   tp->match = match;
}

/** Add an option to a group. */
void AddGroupOption(GroupType *gp, OptionType option)
{
   OptionListType *lp;
   lp = Allocate(sizeof(OptionListType));
   lp->option = option;
   lp->svalue = NULL;
   lp->next = gp->options;
   gp->options = lp;
}

/** Add an option (with a string) to a group. */
void AddGroupOptionString(GroupType *gp, OptionType option,
                          const char *value)
{
   OptionListType *lp;
   Assert(value);
   lp = Allocate(sizeof(OptionListType));
   lp->option = option;
   lp->svalue = CopyString(value);
   lp->next = gp->options;
   gp->options = lp;
}

/** Add an option (with an unsigned integer) to a group. */
void AddGroupOptionUnsigned(GroupType *gp, OptionType option,
                            unsigned int value)
{
   OptionListType *lp;
   Assert(value);
   lp = Allocate(sizeof(OptionListType));
   lp->option = option;
   lp->svalue = NULL;
   lp->uvalue = value;
   lp->next = gp->options;
   gp->options = lp;
}
/** Apply groups to a client. */
void ApplyGroups(ClientNode *np)
{
   PatternListType *lp;
   GroupType *gp;
   char hasClass;
   char hasName;
   char matchesClass;
   char matchesName;

   Assert(np);
   for(gp = groups; gp; gp = gp->next) {
      hasClass = 0;
      hasName = 0;
      matchesClass = 0;
      matchesName = 0;
      for(lp = gp->patterns; lp; lp = lp->next) {
         if(lp->match == MATCH_CLASS) {
            if(Match(lp->pattern, np->className)) {
               matchesClass = 1;
            }
            hasClass = 1;
         } else if(lp->match == MATCH_NAME) {
            if(Match(lp->pattern, np->instanceName)) {
               matchesName = 1;
            }
            hasName = 1;
         } else {
            Debug("invalid match in ApplyGroups: %d", lp->match);
         }
      }
      if(hasName == matchesName && hasClass == matchesClass) {
         ApplyGroup(gp, np);
      }
   }

}

/** Apply a group to a client. */
void ApplyGroup(const GroupType *gp, ClientNode *np)
{

   OptionListType *lp;

   Assert(gp);
   Assert(np);
   for(lp = gp->options; lp; lp = lp->next) {
      switch(lp->option) {
      case OPTION_STICKY:
         np->state.status |= STAT_STICKY;
         break;
      case OPTION_NOLIST:
         np->state.status |= STAT_NOLIST;
         break;
      case OPTION_NOPAGER:
         np->state.status |= STAT_NOPAGER;
         break;
      case OPTION_BORDER:
         np->state.border |= BORDER_OUTLINE;
         break;
      case OPTION_NOBORDER:
         np->state.border &= ~BORDER_OUTLINE;
         break;
      case OPTION_TITLE:
         np->state.border |= BORDER_TITLE;
         break;
      case OPTION_NOTITLE:
         np->state.border &= ~BORDER_TITLE;
         np->state.border &= ~BORDER_SHADE;
         break;
      case OPTION_LAYER:
         np->state.layer = lp->uvalue;
         break;
      case OPTION_DESKTOP:
         if(JLIKELY(lp->uvalue >= 1 && lp->uvalue <= settings.desktopCount)) {
            np->state.desktop = lp->uvalue - 1;
         } else {
            Warning(_("invalid group desktop: %d"), lp->uvalue);
         }
         break;
      case OPTION_ICON:
         DestroyIcon(np->icon);
         np->icon = LoadNamedIcon(lp->svalue, 1);
         break;
      case OPTION_PIGNORE:
         np->state.status |= STAT_PIGNORE;
         break;
      case OPTION_IIGNORE:
         np->state.status |= STAT_IIGNORE;
         break;
      case OPTION_MAXIMIZED:
         np->state.status |= STAT_HMAX | STAT_VMAX;
         break;
      case OPTION_MINIMIZED:
         np->state.status |= STAT_MINIMIZED;
         break;
      case OPTION_SHADED:
         np->state.status |= STAT_SHADED;
         break;
      case OPTION_OPACITY:
         np->state.opacity = lp->uvalue;
         np->state.status |= STAT_OPACITY;
         break;
      case OPTION_MAX_V:
         np->state.border &= ~BORDER_MAX_H;
         break;
      case OPTION_MAX_H:
         np->state.border &= ~BORDER_MAX_V;
         break;
      case OPTION_NOFOCUS:
         np->state.status |= STAT_NOFOCUS;
         break;
      case OPTION_NOSHADE:
         np->state.border &= ~BORDER_SHADE;
         break;
      case OPTION_CENTERED:
         np->state.status |= STAT_CENTERED;
         break;
      case OPTION_TILED:
         np->state.status |= STAT_TILED;
         break;
      case OPTION_NOTURGENT:
         np->state.status |= STAT_NOTURGENT;
         break;
      default:
         Debug("invalid option: %d", lp->option);
         break;
      }
   }

}

