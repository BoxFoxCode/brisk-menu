/*
 * This file is part of brisk-menu.
 *
 * Copyright © 2017-2020 Brisk Menu Developers
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#pragma once

#include <gio/gio.h>
#include <glib-object.h>

#include "../section.h"

G_BEGIN_DECLS

typedef struct _BriskAllItemsSection BriskAllItemsSection;
typedef struct _BriskAllItemsSectionClass BriskAllItemsSectionClass;

#define BRISK_TYPE_ALL_ITEMS_SECTION brisk_all_items_section_get_type()
#define BRISK_ALL_ITEMS_SECTION(o)                                                                 \
        (G_TYPE_CHECK_INSTANCE_CAST((o), BRISK_TYPE_ALL_ITEMS_SECTION, BriskAllItemsSection))
#define BRISK_IS_ALL_ITEMS_SECTION(o)                                                              \
        (G_TYPE_CHECK_INSTANCE_TYPE((o), BRISK_TYPE_ALL_ITEMS_SECTION))
#define BRISK_ALL_ITEMS_SECTION_CLASS(o)                                                           \
        (G_TYPE_CHECK_CLASS_CAST((o), BRISK_TYPE_ALL_ITEMS_SECTION, BriskAllItemsSectionClass))
#define BRISK_IS_ALL_ITEMS_SECTION_CLASS(o)                                                        \
        (G_TYPE_CHECK_CLASS_TYPE((o), BRISK_TYPE_ALL_ITEMS_SECTION))
#define BRISK_ALL_ITEMS_SECTION_GET_CLASS(o)                                                       \
        (G_TYPE_INSTANCE_GET_CLASS((o), BRISK_TYPE_ALL_ITEMS_SECTION, BriskAllItemsSectionClass))

GType brisk_all_items_section_get_type(void);

BriskSection *brisk_all_items_section_new(void);

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
