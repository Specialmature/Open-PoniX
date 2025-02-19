/* ATK -  Accessibility Toolkit
 * Copyright 2001 Sun Microsystems Inc.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */


#include "atkcomponent.h"

static gboolean   atk_component_real_contains                (AtkComponent *component,
                                                              gint         x,
                                                              gint         y,
                                                              AtkCoordType coord_type);

static AtkObject* atk_component_real_ref_accessible_at_point (AtkComponent *component,
                                                              gint         x,
                                                              gint         y,
                                                              AtkCoordType coord_type);

static void      atk_component_real_get_position             (AtkComponent *component,
                                                              gint         *x,
                                                              gint         *y,
                                                              AtkCoordType coord_type);

static void      atk_component_real_get_size                 (AtkComponent *component,
                                                              gint         *width,
                                                              gint         *height);

GType
atk_component_get_type (void)
{
  static GType type = 0;

  if (!type) {
    static const GTypeInfo tinfo =
    {
      sizeof (AtkComponentIface),
      (GBaseInitFunc) NULL,
      (GBaseFinalizeFunc) NULL,

    };

    type = g_type_register_static (G_TYPE_INTERFACE, "AtkComponent", &tinfo, 0);
  }

  return type;
}

/**
 * atk_component_add_focus_handler:
 * @component: The #AtkComponent to attach the @handler to
 * @handler: The #AtkFocusHandler to be attached to @component
 *
 * Add the specified handler to the set of functions to be called 
 * when this object receives focus events (in or out). If the handler is
 * already added it is not added again
 *
 * Returns: a handler id which can be used in atk_component_remove_focus_handler
 * or zero if the handler was already added.
 **/
guint
atk_component_add_focus_handler (AtkComponent    *component,
                                 AtkFocusHandler handler)
{
  AtkComponentIface *iface = NULL;
  g_return_val_if_fail (ATK_IS_COMPONENT (component), 0);

  iface = ATK_COMPONENT_GET_IFACE (component);

  if (iface->add_focus_handler)
    return (iface->add_focus_handler) (component, handler);
  else
    return 0;
}

/**
 * atk_component_remove_focus_handler:
 * @component: the #AtkComponent to remove the focus handler from
 * @handler_id: the handler id of the focus handler to be removed
 * from @component
 *
 * Remove the handler specified by @handler_id from the list of
 * functions to be executed when this object receives focus events 
 * (in or out).
 **/
void
atk_component_remove_focus_handler (AtkComponent    *component,
                                    guint           handler_id)
{
  AtkComponentIface *iface = NULL;
  g_return_if_fail (ATK_IS_COMPONENT (component));

  iface = ATK_COMPONENT_GET_IFACE (component);

  if (iface->remove_focus_handler)
    (iface->remove_focus_handler) (component, handler_id);
}

/**
 * atk_component_contains:
 * @component: the #AtkComponent
 * @x: x coordinate
 * @y: y coordinate
 * @coord_type: specifies whether the coordinates are relative to the screen
 * or to the components top level window
 *
 * Checks whether the specified point is within the extent of the @component.
 *
 * Returns: %TRUE or %FALSE indicating whether the specified point is within
 * the extent of the @component or not
 **/
gboolean
atk_component_contains (AtkComponent    *component,
                        gint            x,
                        gint            y,
                        AtkCoordType    coord_type)
{
  AtkComponentIface *iface = NULL;
  g_return_val_if_fail (ATK_IS_COMPONENT (component), FALSE);

  iface = ATK_COMPONENT_GET_IFACE (component);

  if (iface->contains)
    return (iface->contains) (component, x, y, coord_type);
  else
  {
    /*
     * if this method is not overridden use the default implementation.
     */
    return atk_component_real_contains (component, x, y, coord_type);
  }
}

/**
 * atk_component_ref_accessible_at_point:
 * @component: the #AtkComponent
 * @x: x coordinate
 * @y: y coordinate
 * @coord_type: specifies whether the coordinates are relative to the screen
 * or to the components top level window
 *
 * Gets a reference to the accessible child, if one exists, at the
 * coordinate point specified by @x and @y.
 *
 * Returns: a reference to the accessible child, if one exists
 **/
AtkObject*
atk_component_ref_accessible_at_point (AtkComponent    *component,
                                       gint            x,
                                       gint            y,
                                       AtkCoordType    coord_type)
{
  AtkComponentIface *iface = NULL;
  g_return_val_if_fail (ATK_IS_COMPONENT (component), NULL);

  iface = ATK_COMPONENT_GET_IFACE (component);

  if (iface->ref_accessible_at_point)
    return (iface->ref_accessible_at_point) (component, x, y, coord_type);
  else
  {
    /*
     * if this method is not overridden use the default implementation.
     */
    return atk_component_real_ref_accessible_at_point (component, x, y, coord_type);
  }
}

/**
 * atk_component_get_extents:
 * @component: an #AtkComponent
 * @x: address of #gint to put x coordinate
 * @y: address of #gint to put y coordinate
 * @width: address of #gint to put width
 * @height: address of #gint to put height
 * @coord_type: specifies whether the coordinates are relative to the screen
 * or to the components top level window
 *
 * Gets the rectangle which gives the extent of the @component.
 *
 **/
void
atk_component_get_extents    (AtkComponent    *component,
                              gint            *x,
                              gint            *y,
                              gint            *width,
                              gint            *height,
                              AtkCoordType    coord_type)
{
  AtkComponentIface *iface = NULL;
  gint local_x, local_y, local_width, local_height;
  gint *real_x, *real_y, *real_width, *real_height;

  g_return_if_fail (ATK_IS_COMPONENT (component));

  if (x)
    real_x = x;
  else
    real_x = &local_x;
  if (y)
    real_y = y;
  else
    real_y = &local_y;
  if (width)
    real_width = width;
  else
    real_width = &local_width;
  if (height)
    real_height = height;
  else
    real_height = &local_height;

  iface = ATK_COMPONENT_GET_IFACE (component);

  if (iface->get_extents)
    (iface->get_extents) (component, real_x, real_y, real_width, real_height, coord_type);
}

/**
 * atk_component_get_position:
 * @component: an #AtkComponent
 * @x: address of #gint to put x coordinate position
 * @y: address of #gint to put y coordinate position
 * @coord_type: specifies whether the coordinates are relative to the screen
 * or to the components top level window
 *
 * Gets the position of @component in the form of 
 * a point specifying @component's top-left corner.
 **/
void
atk_component_get_position   (AtkComponent    *component,
                              gint            *x,
                              gint            *y,
                              AtkCoordType    coord_type)
{
  AtkComponentIface *iface = NULL;
  gint local_x, local_y;
  gint *real_x, *real_y;

  g_return_if_fail (ATK_IS_COMPONENT (component));

  if (x)
    real_x = x;
  else
    real_x = &local_x;
  if (y)
    real_y = y;
  else
    real_y = &local_y;

  iface = ATK_COMPONENT_GET_IFACE (component);

  if (iface->get_position)
    (iface->get_position) (component, real_x, real_y, coord_type);
  else
  {
    /*
     * if this method is not overridden use the default implementation.
     */
    atk_component_real_get_position (component, real_x, real_y, coord_type);
  }
}

/**
 * atk_component_get_size:
 * @component: an #AtkComponent
 * @width: address of #gint to put width of @component
 * @height: address of #gint to put height of @component
 *
 * Gets the size of the @component in terms of width and height.
 **/
void
atk_component_get_size       (AtkComponent    *component,
                              gint            *width,
                              gint            *height)
{
  AtkComponentIface *iface = NULL;
  gint local_width, local_height;
  gint *real_width, *real_height;

  g_return_if_fail (ATK_IS_COMPONENT (component));

  if (width)
    real_width = width;
  else
    real_width = &local_width;
  if (height)
    real_height = height;
  else
    real_height = &local_height;

  g_return_if_fail (ATK_IS_COMPONENT (component));

  iface = ATK_COMPONENT_GET_IFACE (component);

  if (iface->get_size)
    (iface->get_size) (component, real_width, real_height);
  else
  {
    /*
     * if this method is not overridden use the default implementation.
     */
    atk_component_real_get_size (component, real_width, real_height);
  }
}

/**
 * atk_component_get_layer:
 * @component: an #AtkComponent
 *
 * Gets the layer of the component.
 *
 * Returns: an #AtkLayer which is the layer of the component
 **/
AtkLayer
atk_component_get_layer (AtkComponent *component) 
{
  AtkComponentIface *iface;

  g_return_val_if_fail (ATK_IS_COMPONENT (component), ATK_LAYER_INVALID);

  iface = ATK_COMPONENT_GET_IFACE (component);
  if (iface->get_layer)
    return (iface->get_layer) (component);
  else
    return ATK_LAYER_WIDGET;
}

/**
 * atk_component_get_mdi_zorder:
 * @component: an #AtkComponent
 *
 * Gets the zorder of the component. The value G_MININT will be returned 
 * if the layer of the component is not ATK_LAYER_MDI.
 *
 * Returns: a gint which is the zorder of the component, i.e. the depth at 
 * which the component is shown in relation to other components in the same 
 * container.
 **/
gint
atk_component_get_mdi_zorder (AtkComponent *component) 
{
  AtkComponentIface *iface;

  g_return_val_if_fail (ATK_IS_COMPONENT (component), G_MININT);

  iface = ATK_COMPONENT_GET_IFACE (component);
  if (iface->get_mdi_zorder)
    return (iface->get_mdi_zorder) (component);
  else
    return G_MININT;
}

/**
 * atk_component_grab_focus:
 * @component: an #AtkComponent
 *
 * Grabs focus for this @component.
 *
 * Returns: %TRUE if successful, %FALSE otherwise.
 **/
gboolean
atk_component_grab_focus (AtkComponent    *component)
{
  AtkComponentIface *iface = NULL;
  g_return_val_if_fail (ATK_IS_COMPONENT (component), FALSE);

  iface = ATK_COMPONENT_GET_IFACE (component);

  if (iface->grab_focus)
    return (iface->grab_focus) (component);
  else
    return FALSE;
}

/**
 * atk_component_set_extents:
 * @component: an #AtkComponent
 * @x: x coordinate
 * @y: y coordinate
 * @width: width to set for @component
 * @height: height to set for @component
 * @coord_type: specifies whether the coordinates are relative to the screen
 * or to the components top level window
 *
 * Sets the extents of @component.
 *
 * Returns: %TRUE or %FALSE whether the extents were set or not
 **/
gboolean
atk_component_set_extents   (AtkComponent    *component,
                             gint            x,
                             gint            y,
                             gint            width,
                             gint            height,
                             AtkCoordType    coord_type)
{
  AtkComponentIface *iface = NULL;
  g_return_val_if_fail (ATK_IS_COMPONENT (component), FALSE);

  iface = ATK_COMPONENT_GET_IFACE (component);

  if (iface->set_extents)
    return (iface->set_extents) (component, x, y, width, height, coord_type);
  else
    return FALSE;
}

/**
 * atk_component_set_position:
 * @component: an #AtkComponent
 * @x: x coordinate
 * @y: y coordinate
 * @coord_type: specifies whether the coordinates are relative to the screen
 * or to the components top level window
 *
 * Sets the postition of @component.
 * 
 * Returns: %TRUE or %FALSE whether or not the position was set or not
 **/
gboolean
atk_component_set_position   (AtkComponent    *component,
                              gint            x,
                              gint            y,
                              AtkCoordType    coord_type)
{
  AtkComponentIface *iface = NULL;
  g_return_val_if_fail (ATK_IS_COMPONENT (component), FALSE);

  iface = ATK_COMPONENT_GET_IFACE (component);

  if (iface->set_position)
    return (iface->set_position) (component, x, y, coord_type);
  else
    return FALSE;
}

/**
 * atk_component_set_size:
 * @component: an #AtkComponent
 * @width: width to set for @component
 * @height: height to set for @component
 *
 * Set the size of the @component in terms of width and height.
 *
 * Returns: %TRUE or %FALSE whether the size was set or not
 **/
gboolean
atk_component_set_size       (AtkComponent    *component,
                              gint            x,
                              gint            y)
{
  AtkComponentIface *iface = NULL;
  g_return_val_if_fail (ATK_IS_COMPONENT (component), FALSE);

  iface = ATK_COMPONENT_GET_IFACE (component);

  if (iface->set_size)
    return (iface->set_size) (component, x, y);
  else
    return FALSE;
}

static gboolean
atk_component_real_contains (AtkComponent *component,
                             gint         x,
                             gint         y,
                             AtkCoordType coord_type)
{
  gint real_x, real_y, width, height;

  real_x = real_y = width = height = 0;

  atk_component_get_extents (component, &real_x, &real_y, &width, &height, coord_type);

  if ((x >= real_x) &&
      (x < real_x + width) &&
      (y >= real_y) &&
      (y < real_y + height))
    return TRUE;
  else
    return FALSE;
}

static AtkObject* 
atk_component_real_ref_accessible_at_point (AtkComponent *component,
                                            gint         x,
                                            gint         y,
                                            AtkCoordType coord_type)
{
  gint count, i;

  count = atk_object_get_n_accessible_children (ATK_OBJECT (component));

  for (i = 0; i < count; i++)
  {
    AtkObject *obj;

    obj = atk_object_ref_accessible_child (ATK_OBJECT (component), i);

    if (obj != NULL)
    {
      if (atk_component_contains (ATK_COMPONENT (obj), x, y, coord_type))
      {
        return obj;
      }
      else
      {
        g_object_unref (obj);
      }
    }
  }
  return NULL;
}

static void
atk_component_real_get_position (AtkComponent *component,
                                 gint         *x,
                                 gint         *y,
                                 AtkCoordType coord_type)
{
  gint width, height;

  atk_component_get_extents (component, x, y, &width, &height, coord_type);
}

static void
atk_component_real_get_size (AtkComponent *component,
                             gint         *width,
                             gint         *height)
{
  gint x, y;
  AtkCoordType coord_type;

  /*
   * Pick one coordinate type; it does not matter for size
   */
  coord_type = ATK_XY_WINDOW;

  atk_component_get_extents (component, &x, &y, width, height, coord_type);
}



