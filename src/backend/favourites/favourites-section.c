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

#define _GNU_SOURCE

#include "util.h"

BRISK_BEGIN_PEDANTIC
#include "favourites-backend.h"
#include "favourites-section.h"
#include <gio/gio.h>
#include <glib/gi18n.h>
BRISK_END_PEDANTIC

struct _BriskFavouritesSectionClass {
        BriskSectionClass parent_class;
};

struct _BriskFavouritesSection {
        BriskSection parent;
        GIcon *icon; /**<Display icon */
        BriskFavouritesBackend *backend;
};

G_DEFINE_TYPE(BriskFavouritesSection, brisk_favourites_section, BRISK_TYPE_SECTION)

enum { PROP_BACKEND = 1, N_PROPS };

static GParamSpec *obj_properties[N_PROPS] = {
        NULL,
};

static void brisk_favourites_section_set_property(GObject *object, guint id, const GValue *value,
                                                  GParamSpec *spec)
{
        BriskFavouritesSection *self = BRISK_FAVOURITES_SECTION(object);

        switch (id) {
        case PROP_BACKEND:
                self->backend = g_value_get_pointer(value);
                break;
        default:
                G_OBJECT_WARN_INVALID_PROPERTY_ID(object, id, spec);
                break;
        }
}

static void brisk_favourites_section_get_property(GObject *object, guint id, GValue *value,
                                                  GParamSpec *spec)
{
        BriskFavouritesSection *self = BRISK_FAVOURITES_SECTION(object);

        switch (id) {
        case PROP_BACKEND:
                g_value_set_pointer(value, self->backend);
                break;
        default:
                G_OBJECT_WARN_INVALID_PROPERTY_ID(object, id, spec);
                break;
        }
}

/**
 * Basic subclassing
 */
static const gchar *brisk_favourites_section_get_id(BriskSection *section);
static const gchar *brisk_favourites_section_get_name(BriskSection *section);
static const GIcon *brisk_favourites_section_get_icon(BriskSection *section);
static const gchar *brisk_favourites_section_get_backend_id(BriskSection *section);
static gint brisk_favourites_section_get_sort_order(BriskSection *section, BriskItem *item);
static gboolean brisk_favourites_section_can_show_item(BriskSection *section, BriskItem *item);

/**
 * brisk_favourites_section_dispose:
 *
 * Clean up a BriskFavouritesSection instance
 */
static void brisk_favourites_section_dispose(GObject *obj)
{
        BriskFavouritesSection *self = BRISK_FAVOURITES_SECTION(obj);

        g_clear_object(&self->icon);

        G_OBJECT_CLASS(brisk_favourites_section_parent_class)->dispose(obj);
}

/**
 * brisk_favourites_section_class_init:
 *
 * Handle class initialisation
 */
static void brisk_favourites_section_class_init(BriskFavouritesSectionClass *klazz)
{
        BriskSectionClass *s_class = BRISK_SECTION_CLASS(klazz);
        GObjectClass *obj_class = G_OBJECT_CLASS(klazz);

        /* item vtable hookup */
        s_class->get_id = brisk_favourites_section_get_id;
        s_class->get_name = brisk_favourites_section_get_name;
        s_class->get_icon = brisk_favourites_section_get_icon;
        s_class->get_backend_id = brisk_favourites_section_get_backend_id;
        s_class->can_show_item = brisk_favourites_section_can_show_item;
        s_class->get_sort_order = brisk_favourites_section_get_sort_order;

        obj_class->dispose = brisk_favourites_section_dispose;
        obj_class->set_property = brisk_favourites_section_set_property;
        obj_class->get_property = brisk_favourites_section_get_property;

        obj_properties[PROP_BACKEND] = g_param_spec_pointer("backend",
                                                            "The BriskBackend",
                                                            "Owning backend for this section",
                                                            G_PARAM_CONSTRUCT | G_PARAM_READWRITE);
        g_object_class_install_properties(obj_class, N_PROPS, obj_properties);
}

/**
 * brisk_favourites_section_init:
 *
 * Handle construction of the BriskFavouritesSection. Does absolutely nothing
 * special outside of creating our icon.
 */
static void brisk_favourites_section_init(BriskFavouritesSection *self)
{
        self->icon = g_themed_icon_new_with_default_fallbacks("emblem-favorite");
}

static gboolean brisk_favourites_section_get_item_is_pinned(BriskSection *section, BriskItem *item)
{
        BriskFavouritesSection *self = BRISK_FAVOURITES_SECTION(section);
        return brisk_favourites_backend_is_pinned(self->backend, item);
}

static const gchar *brisk_favourites_section_get_id(__brisk_unused__ BriskSection *section)
{
        return "favourites";
}

static const gchar *brisk_favourites_section_get_name(__brisk_unused__ BriskSection *section)
{
        return _("Favourites");
}

static const GIcon *brisk_favourites_section_get_icon(BriskSection *section)
{
        BriskFavouritesSection *self = BRISK_FAVOURITES_SECTION(section);
        return (const GIcon *)self->icon;
}

static const gchar *brisk_favourites_section_get_backend_id(__brisk_unused__ BriskSection *item)
{
        return "favourites";
}

static gboolean brisk_favourites_section_can_show_item(__brisk_unused__ BriskSection *section,
                                                       __brisk_unused__ BriskItem *item)
{
        return brisk_favourites_section_get_item_is_pinned(section, item);
}

static gint brisk_favourites_section_get_sort_order(BriskSection *section, BriskItem *item)
{
        BriskFavouritesSection *self = BRISK_FAVOURITES_SECTION(section);

        return brisk_favourites_backend_get_item_order(self->backend, item);
}

/**
 * brisk_favourites_section_new:
 *
 * Return a new BriskFavouritesSection
 */
BriskSection *brisk_favourites_section_new(BriskFavouritesBackend *backend)
{
        return g_object_new(BRISK_TYPE_FAVOURITES_SECTION, "backend", backend, NULL);
}

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
