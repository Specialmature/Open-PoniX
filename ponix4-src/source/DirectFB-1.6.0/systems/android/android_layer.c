/*
   (c) Copyright 2001-2010  The world wide DirectFB Open Source Community (directfb.org)
   (c) Copyright 2000-2004  Convergence (integrated media) GmbH

   All rights reserved.

   Written by Denis Oliver Kropp <dok@directfb.org>,
              Andreas Hundt <andi@fischlustig.de>,
              Sven Neumann <neo@directfb.org>,
              Ville Syrjälä <syrjala@sci.fi> and
              Claudio Ciccani <klan@users.sf.net>.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the
   Free Software Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.
*/

#include <config.h>

#include <core/layers.h>
#include <core/screens.h>

#include <misc/conf.h>


#include "android_system.h"

/**********************************************************************************************************************/

static DFBResult
androidInitLayer( CoreLayer                  *layer,
               void                       *driver_data,
               void                       *layer_data,
               DFBDisplayLayerDescription *description,
               DFBDisplayLayerConfig      *config,
               DFBColorAdjustment         *adjustment )
{
     AndroidData *android = driver_data;

     description->type             = DLTF_GRAPHICS;
     description->caps             = DLCAPS_SURFACE;
     description->surface_caps     = DSCAPS_NONE;
     description->surface_accessor = CSAID_LAYER0;

     direct_snputs( description->name, "Android Layer", DFB_DISPLAY_LAYER_DESC_NAME_LENGTH );


     config->flags       = DLCONF_WIDTH | DLCONF_HEIGHT | DLCONF_PIXELFORMAT | DLCONF_BUFFERMODE;
     config->width       = dfb_config->mode.width  ?: 1024;
     config->height      = dfb_config->mode.height ?: 600;
     config->pixelformat = dfb_config->mode.format ?: DSPF_ARGB;
     config->buffermode  = DLBM_FRONTONLY;

     return DFB_OK;
}

static DFBResult
androidTestRegion( CoreLayer                  *layer,
                void                       *driver_data,
                void                       *layer_data,
                CoreLayerRegionConfig      *config,
                CoreLayerRegionConfigFlags *ret_failed )
{
     if (ret_failed)
          *ret_failed = DLCONF_NONE;

     return DFB_OK;
}

static DFBResult
androidSetRegion( CoreLayer                  *layer,
               void                       *driver_data,
               void                       *layer_data,
               void                       *region_data,
               CoreLayerRegionConfig      *config,
               CoreLayerRegionConfigFlags  updated,
               CoreSurface                *surface,
               CorePalette                *palette,
               CoreSurfaceBufferLock      *left_lock,
               CoreSurfaceBufferLock      *right_lock )
{
     AndroidData *android = driver_data;

     return DFB_OK;
}

static DFBResult
androidFlipRegion( CoreLayer                  *layer,
                void                       *driver_data,
                void                       *layer_data,
                void                       *region_data,
                CoreSurface                *surface,
                DFBSurfaceFlipFlags         flags,
                CoreSurfaceBufferLock      *left_lock,
                CoreSurfaceBufferLock      *right_lock )
{
     AndroidData *android = driver_data;

     eglSwapBuffers(android->dpy, android->surface);

     dfb_surface_flip( surface, false );

     return DFB_OK;
}

static const DisplayLayerFuncs _androidLayerFuncs = {
     .InitLayer     = androidInitLayer,
     .TestRegion    = androidTestRegion,
     .SetRegion     = androidSetRegion,
     .FlipRegion    = androidFlipRegion
};

const DisplayLayerFuncs *androidLayerFuncs = &_androidLayerFuncs;

