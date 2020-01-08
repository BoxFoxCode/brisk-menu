/*
 * This file is part of brisk-menu.
 *
 * Copyright © 2016-2020 Brisk Menu Developers
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#pragma once

#include <glib-object.h>
#include <gtk/gtk.h>

#include "backend/item.h"
#include "launcher.h"

G_BEGIN_DECLS

typedef struct _BriskMenuEntryButton BriskMenuEntryButton;
typedef struct _BriskMenuEntryButtonClass BriskMenuEntryButtonClass;

struct _BriskMenuEntryButtonClass {
        GtkButtonClass parent_class;
        void (*show_context_menu)(BriskMenuEntryButton *button, BriskItem *item);
};

/**
 * BriskMenuEntryButton is the toplevel window type used within the applet.
 */
struct _BriskMenuEntryButton {
        GtkButton parent;
        BriskMenuLauncher *launcher;
        BriskItem *item;
};

#define BRISK_TYPE_MENU_ENTRY_BUTTON brisk_menu_entry_button_get_type()
#define BRISK_MENU_ENTRY_BUTTON(o)                                                                 \
        (G_TYPE_CHECK_INSTANCE_CAST((o), BRISK_TYPE_MENU_ENTRY_BUTTON, BriskMenuEntryButton))
#define BRISK_IS_MENU_ENTRY_BUTTON(o)                                                              \
        (G_TYPE_CHECK_INSTANCE_TYPE((o), BRISK_TYPE_MENU_ENTRY_BUTTON))
#define BRISK_MENU_ENTRY_BUTTON_CLASS(o)                                                           \
        (G_TYPE_CHECK_CLASS_CAST((o), BRISK_TYPE_MENU_ENTRY_BUTTON, BriskMenuEntryButtonClass))
#define BRISK_IS_MENU_ENTRY_BUTTON_CLASS(o)                                                        \
        (G_TYPE_CHECK_CLASS_TYPE((o), BRISK_TYPE_MENU_ENTRY_BUTTON))
#define BRISK_MENU_ENTRY_BUTTON_GET_CLASS(o)                                                       \
        (G_TYPE_INSTANCE_GET_CLASS((o), BRISK_TYPE_MENU_ENTRY_BUTTON, BriskMenuEntryButtonClass))

void brisk_menu_entry_button_launch(BriskMenuEntryButton *button);

GType brisk_menu_entry_button_get_type(void);

G_END_DECLS

/*
 * Editor modelines  -  https://www.wireshark.org/tools/modelines.html
 *
 * Local variables:
 * c-basic-offset: 8
 * tab-width: 8
 * indent-tabs-mode: nil
 * End:
 *
 * vi: set shiftwidth=8 tabstop=8 expandtab:
 * :indentSize=8:tabSize=8:noTabs=true:
 */
