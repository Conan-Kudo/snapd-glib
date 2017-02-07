/*
 * Copyright (C) 2016 Canonical Ltd.
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation; either version 2 or version 3 of the License.
 * See http://www.gnu.org/copyleft/lgpl.html the full text of the license.
 */

#include <snapd-glib/snapd-glib.h>

#include "Snapd/app.h"

QSnapdApp::QSnapdApp (void *snapd_object, QObject *parent) : QSnapdWrappedObject (snapd_object, g_object_unref, parent) {}

QString QSnapdApp::name () const
{
    return snapd_app_get_name (SNAPD_APP (wrapped_object));
}

QStringList QSnapdApp::aliases () const
{
    gchar **discharges = snapd_app_get_aliases (SNAPD_APP (wrapped_object));
    QStringList result;
    for (int i = 0; discharges[i] != NULL; i++)
        result.append (discharges[i]);
    return result;
}
