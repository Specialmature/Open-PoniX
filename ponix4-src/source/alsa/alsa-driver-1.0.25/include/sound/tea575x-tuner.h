#ifndef __SOUND_TEA575X_TUNER_H
#define __SOUND_TEA575X_TUNER_H

/*
 *   ALSA driver for TEA5757/5759 Philips AM/FM tuner chips
 *
 *	Copyright (c) 2004 Jaroslav Kysela <perex@perex.cz>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 *
 */

#include <linux/videodev2.h>
#include <media/v4l2-ctrls.h>
#ifndef CONFIG_HAVE_V4L2_CTRLS
#include <media/v4l2-ioctl.h>
#endif
#include <media/v4l2-dev.h>

#define TEA575X_FMIF	10700

#define TEA575X_DATA	(1 << 0)
#define TEA575X_CLK	(1 << 1)
#define TEA575X_WREN	(1 << 2)
#define TEA575X_MOST	(1 << 3)

struct snd_tea575x;

struct snd_tea575x_ops {
	void (*set_pins)(struct snd_tea575x *tea, u8 pins);
	u8 (*get_pins)(struct snd_tea575x *tea);
	void (*set_direction)(struct snd_tea575x *tea, bool output);
};

struct snd_tea575x {
	struct video_device vd;		/* video device */
	bool tea5759;			/* 5759 chip is present */
	bool mute;			/* Device is muted? */
	bool stereo;			/* receiving stereo */
	bool tuned;			/* tuned to a station */
	unsigned int val;		/* hw value */
	unsigned long freq;		/* frequency */
	struct mutex mutex;
	struct snd_tea575x_ops *ops;
	void *private_data;
	u8 card[32];
	u8 bus_info[32];
#ifdef CONFIG_HAVE_V4L2_CTRLS
	struct v4l2_ctrl_handler ctrl_handler;
#else
	unsigned long in_use;		/* set if the device is in use */
#endif
	int (*ext_init)(struct snd_tea575x *tea);
};

int snd_tea575x_init(struct snd_tea575x *tea);
void snd_tea575x_exit(struct snd_tea575x *tea);

#endif /* __SOUND_TEA575X_TUNER_H */
