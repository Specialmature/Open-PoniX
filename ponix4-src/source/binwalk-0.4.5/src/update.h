/* 
 * Copyright (c) 2010 Craig Heffner
 *
 * This software is provided under the MIT license. For the full text of this license, please see
 * the COPYING file included with this code, or visit http://www.opensource.org/licenses/MIT.
 */

#ifndef UPDATE_H
#define UPDATE_H

#define BINWALK_UPDATE_URL	"http://binwalk.googlecode.com/svn/trunk/src/magic.binwalk"
#define BINCAST_UPDATE_URL	"http://binwalk.googlecode.com/svn/trunk/src/magic.bincast"
#define BINARCH_UPDATE_URL	"http://binwalk.googlecode.com/svn/trunk/src/magic.binarch"

int update_magic_file(char *url, char *outfile);
size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *fp);

#endif
