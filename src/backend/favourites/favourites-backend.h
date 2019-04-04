/*
 * This file is part of brisk-menu.
 *
 * Copyright © 2017-2019 Brisk Menu Developers
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#pragma once

#include "../backend.h"
#include <glib-object.h>

G_BEGIN_DECLS

typedef struct _BriskFavouritesBackend BriskFavouritesBackend;
typedef struct _BriskFavouritesBackendClass BriskFavouritesBackendClass;

struct _BriskFavouritesBackendClass {
        BriskBackendClass parent_class;
};

/**
 * BriskFavouritesBackend implements support for favourites in Brisk
 */
struct _BriskFavouritesBackend {
        BriskBackend parent;
        GSettings *settings;
        GHashTable *favourites;

        /* Action management */
        BriskItem *active_item;
        GSimpleAction *action_remove;
        GSimpleAction *action_add;
        GSimpleAction *action_add_desktop;
        GSimpleAction *action_remove_desktop;
};

#define BRISK_TYPE_FAVOURITES_BACKEND brisk_favourites_backend_get_type()
#define BRISK_FAVOURITES_BACKEND(o)                                                                \
        (G_TYPE_CHECK_INSTANCE_CAST((o), BRISK_TYPE_FAVOURITES_BACKEND, BriskFavouritesBackend))
#define BRISK_IS_FAVOURITES_BACKEND(o)                                                             \
        (G_TYPE_CHECK_INSTANCE_TYPE((o), BRISK_TYPE_FAVOURITES_BACKEND))
#define BRISK_FAVOURITES_BACKEND_CLASS(o)                                                          \
        (G_TYPE_CHECK_CLASS_CAST((o), BRISK_TYPE_FAVOURITES_BACKEND, BriskFavouritesBackendClass))
#define BRISK_IS_FAVOURITES_BACKEND_CLASS(o)                                                       \
        (G_TYPE_CHECK_CLASS_TYPE((o), BRISK_TYPE_FAVOURITES_BACKEND))
#define BRISK_FAVOURITES_BACKEND_GET_CLASS(o)                                                      \
        (G_TYPE_INSTANCE_GET_CLASS((o), BRISK_TYPE_FAVOURITES_BACKEND, BriskFavouritesBackendClass))

GType brisk_favourites_backend_get_type(void);

BriskBackend *brisk_favourites_backend_new(void);

gboolean brisk_favourites_backend_is_pinned(BriskFavouritesBackend *self, BriskItem *item);
gint brisk_favourites_backend_get_item_order(BriskFavouritesBackend *self, BriskItem *item);
void brisk_favourites_backend_init_desktop(BriskFavouritesBackend *backend);
void brisk_favourites_backend_menu_desktop(BriskFavouritesBackend *backend, GMenu *menu,
                                           GActionGroup *group);

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
