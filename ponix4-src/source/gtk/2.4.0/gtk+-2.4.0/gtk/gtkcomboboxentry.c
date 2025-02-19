/* gtkcomboboxentry.c
 * Copyright (C) 2002, 2003  Kristian Rietveld <kris@gtk.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include <config.h>
#include "gtkcomboboxentry.h"
#include "gtkcelllayout.h"

#include "gtkentry.h"
#include "gtkcellrenderertext.h"

#include "gtkintl.h"

#define GTK_COMBO_BOX_ENTRY_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), GTK_TYPE_COMBO_BOX_ENTRY, GtkComboBoxEntryPrivate))

struct _GtkComboBoxEntryPrivate
{
  GtkWidget *entry;

  GtkCellRenderer *text_renderer;
  gint text_column;
};

static void gtk_combo_box_entry_class_init       (GtkComboBoxEntryClass *klass);
static void gtk_combo_box_entry_init             (GtkComboBoxEntry      *entry_box);

static void gtk_combo_box_entry_set_property     (GObject               *object,
                                                  guint                  prop_id,
                                                  const GValue          *value,
                                                  GParamSpec            *pspec);
static void gtk_combo_box_entry_get_property     (GObject               *object,
                                                  guint                  prop_id,
                                                  GValue                *value,
                                                  GParamSpec            *pspec);

static void gtk_combo_box_entry_active_changed   (GtkComboBox           *combo_box,
                                                  gpointer               user_data);
static void gtk_combo_box_entry_contents_changed (GtkEntry              *entry,
                                                  gpointer               user_data);
static gboolean gtk_combo_box_entry_mnemonic_activate (GtkWidget        *entry,
						       gboolean          group_cycling);

enum
{
  PROP_0,
  PROP_TEXT_COLUMN
};


GType
gtk_combo_box_entry_get_type (void)
{
  static GType combo_box_entry_type = 0;

  if (!combo_box_entry_type)
    {
      static const GTypeInfo combo_box_entry_info =
        {
          sizeof (GtkComboBoxEntryClass),
          NULL, /* base_init */
          NULL, /* base_finalize */
          (GClassInitFunc) gtk_combo_box_entry_class_init,
          NULL, /* class_finalize */
          NULL, /* class_data */
          sizeof (GtkComboBoxEntry),
          0,
          (GInstanceInitFunc) gtk_combo_box_entry_init
        };

      combo_box_entry_type = g_type_register_static (GTK_TYPE_COMBO_BOX,
                                                     "GtkComboBoxEntry",
                                                     &combo_box_entry_info,
                                                     0);
    }

  return combo_box_entry_type;
}

static void
gtk_combo_box_entry_class_init (GtkComboBoxEntryClass *klass)
{
  GObjectClass *object_class;
  GtkWidgetClass *widget_class;

  object_class = (GObjectClass *)klass;
  object_class->set_property = gtk_combo_box_entry_set_property;
  object_class->get_property = gtk_combo_box_entry_get_property;

  widget_class = (GtkWidgetClass *)klass;
  widget_class->mnemonic_activate = gtk_combo_box_entry_mnemonic_activate;

  g_object_class_install_property (object_class,
                                   PROP_TEXT_COLUMN,
                                   g_param_spec_int ("text_column",
                                                     P_("Text Column"),
                                                     P_("A column in the data source model to get the strings from"),
                                                     -1,
                                                     G_MAXINT,
                                                     -1,
                                                     G_PARAM_READWRITE));

  g_type_class_add_private ((GObjectClass *) klass,
                            sizeof (GtkComboBoxEntryPrivate));
}

static void
gtk_combo_box_entry_init (GtkComboBoxEntry *entry_box)
{
  entry_box->priv = GTK_COMBO_BOX_ENTRY_GET_PRIVATE (entry_box);
  entry_box->priv->text_column = -1;

  entry_box->priv->entry = gtk_entry_new ();
  gtk_container_add (GTK_CONTAINER (entry_box), entry_box->priv->entry);
  gtk_widget_show (entry_box->priv->entry);

  entry_box->priv->text_renderer = gtk_cell_renderer_text_new ();
  gtk_cell_layout_pack_start (GTK_CELL_LAYOUT (entry_box),
                              entry_box->priv->text_renderer, TRUE);

  gtk_combo_box_set_active (GTK_COMBO_BOX (entry_box), -1);

  g_signal_connect (entry_box->priv->entry, "changed",
                    G_CALLBACK (gtk_combo_box_entry_contents_changed),
                    entry_box);
  g_signal_connect (entry_box, "changed",
                    G_CALLBACK (gtk_combo_box_entry_active_changed), NULL);
}

static void
gtk_combo_box_entry_set_property (GObject      *object,
                                  guint         prop_id,
                                  const GValue *value,
                                  GParamSpec   *pspec)
{
  GtkComboBoxEntry *entry_box = GTK_COMBO_BOX_ENTRY (object);

  switch (prop_id)
    {
      case PROP_TEXT_COLUMN:
        gtk_combo_box_entry_set_text_column (entry_box,
                                             g_value_get_int (value));
        break;

      default:
        break;
    }
}

static void
gtk_combo_box_entry_get_property (GObject    *object,
                                  guint       prop_id,
                                  GValue     *value,
                                  GParamSpec *pspec)
{
  GtkComboBoxEntry *entry_box = GTK_COMBO_BOX_ENTRY (object);

  switch (prop_id)
    {
      case PROP_TEXT_COLUMN:
        g_value_set_int (value, entry_box->priv->text_column);
        break;

      default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
        break;
    }
}

static void
gtk_combo_box_entry_active_changed (GtkComboBox *combo_box,
                                    gpointer     user_data)
{
  gint index;
  GtkComboBoxEntry *entry_box = GTK_COMBO_BOX_ENTRY (combo_box);

  index = gtk_combo_box_get_active (combo_box);

  g_signal_handlers_block_by_func (entry_box->priv->entry,
                                   gtk_combo_box_entry_contents_changed,
                                   combo_box);

  if (index >= 0)
    {
      gchar *str = NULL;
      GtkTreeIter iter;
      GtkTreeModel *model;

      model = gtk_combo_box_get_model (combo_box);

      gtk_tree_model_iter_nth_child (model, &iter, NULL, index);
      gtk_tree_model_get (model, &iter,
                          entry_box->priv->text_column, &str,
                          -1);

      gtk_entry_set_text (GTK_ENTRY (entry_box->priv->entry), str);

      g_free (str);
    }

  g_signal_handlers_unblock_by_func (entry_box->priv->entry,
                                     gtk_combo_box_entry_contents_changed,
                                     combo_box);
}

static void
gtk_combo_box_entry_contents_changed (GtkEntry *entry,
                                      gpointer  user_data)
{
  GtkComboBox *combo_box = GTK_COMBO_BOX (user_data);

  g_signal_handlers_block_by_func (combo_box,
                                   gtk_combo_box_entry_active_changed,
                                   NULL);
  gtk_combo_box_set_active (combo_box, -1);
  g_signal_handlers_unblock_by_func (combo_box,
                                     gtk_combo_box_entry_active_changed,
                                     NULL);
}

/* public API */

/**
 * gtk_combo_box_entry_new:
 *
 * Creates a new #GtkComboBoxEntry which has a #GtkEntry as child. After
 * construction, you should set a model using gtk_combo_box_set_model() and a
 * text_column * using gtk_combo_box_entry_set_text_column().
 *
 * Return value: A new #GtkComboBoxEntry.
 *
 * Since: 2.4
 */
GtkWidget *
gtk_combo_box_entry_new (void)
{
  return GTK_WIDGET (g_object_new (gtk_combo_box_entry_get_type (), NULL));
}

/**
 * gtk_combo_box_entry_new_with_model:
 * @model: A #GtkTreeModel.
 * @text_column: A column in @model to get the strings from.
 *
 * Creates a new #GtkComboBoxEntry which has a #GtkEntry as child and a list
 * of strings as popup. You can get the #GtkEntry from a #GtkComboBoxEntry
 * using GTK_ENTRY (GTK_BIN (combo_box_entry)->child). To add and remove
 * strings from the list, just modify @model using its data manipulation
 * API.
 *
 * Return value: A new #GtkComboBoxEntry.
 *
 * Since: 2.4
 */
GtkWidget *
gtk_combo_box_entry_new_with_model (GtkTreeModel *model,
                                    gint          text_column)
{
  GtkWidget *ret;

  g_return_val_if_fail (GTK_IS_TREE_MODEL (model), NULL);
  g_return_val_if_fail (text_column >= 0, NULL);
  g_return_val_if_fail (text_column < gtk_tree_model_get_n_columns (model), NULL);

  ret = g_object_new (gtk_combo_box_entry_get_type (),
                      "model", model,
                      "text_column", text_column,
                      NULL);

  return ret;
}

/**
 * gtk_combo_box_entry_set_text_column:
 * @entry_box: A #GtkComboBoxEntry.
 * @text_column: A column in @model to get the strings from.
 *
 * Sets the model column which @entry_box should use to get strings from
 * to be @text_column.
 *
 * Since: 2.4.
 */
void
gtk_combo_box_entry_set_text_column (GtkComboBoxEntry *entry_box,
                                     gint              text_column)
{
  g_return_if_fail (text_column >= 0);
  g_return_if_fail (text_column < gtk_tree_model_get_n_columns (gtk_combo_box_get_model (GTK_COMBO_BOX (entry_box))));
  g_return_if_fail (entry_box->priv->text_column == -1);

  entry_box->priv->text_column = text_column;

  gtk_cell_layout_set_attributes (GTK_CELL_LAYOUT (entry_box),
                                  entry_box->priv->text_renderer,
                                  "text", text_column,
                                  NULL);
}

/**
 * gtk_combo_box_entry_get_text_column:
 * @entry_box: A #GtkComboBoxEntry.
 *
 * Returns the column which @entry_box is using to get the strings from.
 *
 * Return value: A column in the data source model of @entry_box.
 *
 * Since: 2.4
 */
gint
gtk_combo_box_entry_get_text_column (GtkComboBoxEntry *entry_box)
{
  g_return_val_if_fail (GTK_IS_COMBO_BOX_ENTRY (entry_box), 0);

  return entry_box->priv->text_column;
}

static gboolean
gtk_combo_box_entry_mnemonic_activate (GtkWidget *widget,
				       gboolean   group_cycling)
{
  GtkComboBoxEntry *entry_box = GTK_COMBO_BOX_ENTRY (widget);

  gtk_widget_grab_focus (entry_box->priv->entry);

  return TRUE;
}


/* convenience API for simple text combos */

/**
 * gtk_combo_box_entry_new_text:
 *
 * Convenience function which constructs a new editable text combo box, which 
 * is a #GtkComboBoxEntry just displaying strings. If you use this function to
 * create a text combo box, you should only manipulate its data source with
 * the following convenience functions: gtk_combo_box_append_text(),
 * gtk_combo_box_insert_text(), gtk_combo_box_prepend_text() and
 * gtk_combo_box_remove_text().
 *
 * Return value: A new text #GtkComboBoxEntry.
 *
 * Since: 2.4
 */
GtkWidget *
gtk_combo_box_entry_new_text (void)
{
  GtkWidget *entry_box;
  GtkListStore *store;

  store = gtk_list_store_new (1, G_TYPE_STRING);

  entry_box = gtk_combo_box_entry_new_with_model (GTK_TREE_MODEL (store), 0);

  return entry_box;
}
