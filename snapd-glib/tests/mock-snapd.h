/*
 * Copyright (C) 2017 Canonical Ltd.
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation; either version 2 or version 3 of the License.
 * See http://www.gnu.org/copyleft/lgpl.html the full text of the license.
 */

#ifndef __MOCK_SNAPD_H__
#define __MOCK_SNAPD_H__

#include <glib-object.h>
#include <gio/gio.h>

G_BEGIN_DECLS

#define MOCK_TYPE_SNAPD  (mock_snapd_get_type ())

G_DECLARE_FINAL_TYPE (MockSnapd, mock_snapd, MOCK, SNAPD, GObject)

struct _MockSnapdClass
{
    /*< private >*/
    GObjectClass parent_class;
};

typedef struct
{
    gchar *username;
    gchar *password;
    gchar *otp;
    gchar *macaroon;
    gchar **discharges;
    gboolean terms_accepted;
    gboolean has_payment_methods;
    GList *private_snaps;
} MockAccount;

typedef struct
{
    GList *apps;
    gchar *channel;
    gchar *confinement;
    gchar *description;
    gchar *developer;
    gboolean devmode;
    int download_size;
    gchar *icon;
    gchar *id;
    gchar *install_date;
    int installed_size;
    gchar *name;
    GList *prices;
    gboolean private;
    gchar *revision;
    GList *screenshots;
    gchar *status;
    gchar *summary;
    gboolean trymode;
    gchar *type;
    gchar *version;
    GList *plugs;
    GList *slots;
    gboolean disabled;
} MockSnap;

typedef struct
{
    gchar *name;
    GList *aliases;
} MockApp;

typedef struct
{
    gdouble amount;
    gchar *currency;
} MockPrice;

typedef struct
{
    gchar *url;
    int width;
    int height;
} MockScreenshot;

typedef struct _MockSlot MockSlot;

typedef struct
{
    MockSnap *snap;
    gchar *name;
    gchar *interface;
    // FIXME: Attributes
    gchar *label;
    MockSlot *connection;
} MockPlug;

struct _MockSlot
{
    MockSnap *snap;
    gchar *name;
    gchar *interface;
    // FIXME: Attributes
    gchar *label;
};

MockSnapd      *mock_snapd_new                    (void);

GSocket        *mock_snapd_get_client_socket      (MockSnapd   *snapd);

void            mock_snapd_set_suggested_currency (MockSnapd   *snapd,
                                                   const gchar *currency);

void            mock_snapd_set_progress_total     (MockSnapd   *snapd,
                                                   int          total);

void            mock_snapd_set_spawn_time         (MockSnapd   *snapd,
                                                   const gchar *spawn_time);

void            mock_snapd_set_ready_time         (MockSnapd   *snapd,
                                                   const gchar *ready_time);

MockAccount    *mock_snapd_add_account            (MockSnapd   *snapd,
                                                   const gchar *username,
                                                   const gchar *password,
                                                   const gchar *otp);

MockSnap       *mock_account_add_private_snap     (MockAccount *account,
                                                   const gchar *name);

MockSnap       *mock_snapd_add_snap               (MockSnapd   *snapd,
                                                   const gchar *name);

MockSnap       *mock_snapd_find_snap              (MockSnapd   *snapd,
                                                   const gchar *name);

MockSnap       *mock_snapd_add_store_snap         (MockSnapd   *snapd,
                                                   const gchar *name);

MockApp        *mock_snap_add_app                 (MockSnap    *snap,
                                                   const gchar *name);

void            mock_app_add_alias                (MockApp     *app,
                                                   const gchar *alias);

void            mock_snap_set_channel             (MockSnap    *snap,
                                                   const gchar *channel);

void            mock_snap_set_id                  (MockSnap    *snap,
                                                   const gchar *id);

void            mock_snap_set_install_date        (MockSnap    *snap,
                                                   const gchar *install_date);

MockPrice      *mock_snap_add_price               (MockSnap    *snap,
                                                   gdouble      amount,
                                                   const gchar *currency);

void            mock_snap_set_revision            (MockSnap    *snap,
                                                   const gchar *revision);

MockScreenshot *mock_snap_add_screenshot          (MockSnap    *snap,
                                                   const gchar *url,
                                                   int          width,
                                                   int          height);

void            mock_snap_set_version             (MockSnap    *snap,
                                                   const gchar *version);

MockPlug       *mock_snap_add_plug                (MockSnap    *snap,
                                                   const gchar *name);

MockSlot       *mock_snap_add_slot                (MockSnap    *snap,
                                                   const gchar *name);

G_END_DECLS

#endif /* __MOCK_SNAPD_H__ */
