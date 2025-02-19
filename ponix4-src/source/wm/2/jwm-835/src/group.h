/**
 * @file group.h
 * @author Joe Wingbermuehle
 * @date 2004-2006
 *
 * @brief Functions for handling window groups.
 *
 */

#ifndef GROUP_H
#define GROUP_H

struct ClientNode;
struct GroupType;

/** Enumeration of group options. */
typedef unsigned char OptionType;
#define OPTION_INVALID     0
#define OPTION_STICKY      1     /**< Start in the sticky state. */
#define OPTION_LAYER       2     /**< Start on a specific layer. */
#define OPTION_DESKTOP     3     /**< Start on a specific desktop. */
#define OPTION_ICON        4     /**< Set the icon to use. */
#define OPTION_NOLIST      5     /**< Don't display in the task list. */
#define OPTION_BORDER      6     /**< Force a window border. */
#define OPTION_NOBORDER    7     /**< Don't draw a window border. */
#define OPTION_TITLE       8     /**< Force a window title bar. */
#define OPTION_NOTITLE     9     /**< Don't draw a window title bar. */
#define OPTION_PIGNORE     10    /**< Ignore program-specified location. */
#define OPTION_MAXIMIZED   11    /**< Start maximized. */
#define OPTION_MINIMIZED   12    /**< Start minimized. */
#define OPTION_SHADED      13    /**< Start shaded. */
#define OPTION_OPACITY     14    /**< Set the opacity. */
#define OPTION_MAX_H       15    /**< Use horizontal maximization. */
#define OPTION_MAX_V       16    /**< Use vertical maximization. */
#define OPTION_NOFOCUS     17    /**< Don't focus on map. */
#define OPTION_NOSHADE     18    /**< Don't allow shading. */
#define OPTION_CENTERED    19    /**< Centered placement. */
#define OPTION_TILED       20    /**< Tiled placement. */
#define OPTION_IIGNORE     21    /**< Ignore increment when maximized. */
#define OPTION_NOPAGER     22    /**< Do not show in pager. */
#define OPTION_NOTURGENT   23    /**< Ignore the urgency hint. */

/*@{*/
#define InitializeGroups() (void)(0)
#define StartupGroups()    (void)(0)
#define ShutdownGroups()   (void)(0)
void DestroyGroups();
/*@}*/

/** Create an empty group.
 * @return An empty group.
 */
struct GroupType *CreateGroup();

/** Add a window class to a group.
 * @param gp The group.
 * @param pattern A pattern to match with the window class.
 */
void AddGroupClass(struct GroupType *gp, const char *pattern);

/** Add a window name to a group.
 * @param gp The group.
 * @param pattern A pattern to match with the window name.
 */
void AddGroupName(struct GroupType *gp, const char *pattern);

/** Add a group option that doesn't take a value.
 * @param gp The group.
 * @param option The option.
 */
void AddGroupOption(struct GroupType *gp, OptionType option);

/** Add a group option that takes a string.
 * @param gp The group.
 * @param option The option.
 * @param value The option value.
 */
void AddGroupOptionString(struct GroupType *gp, OptionType option,
                          const char *value);

/** Add a group option that takes an unsigned integer.
 * @param gp The group.
 * @param option The option.
 * @param value The option value.
 */
void AddGroupOptionUnsigned(struct GroupType *gp, OptionType option,
                            unsigned int value);

/** Apply any matching groups to a client.
 * @param np The client.
 */
void ApplyGroups(struct ClientNode *np);

#endif /* GROUP_H */

