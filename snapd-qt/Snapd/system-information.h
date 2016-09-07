/*
 * Copyright (C) 2016 Canonical Ltd.
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation; either version 2 or version 3 of the License.
 * See http://www.gnu.org/copyleft/lgpl.html the full text of the license.
 */

#ifndef SNAPD_SYSTEM_INFORMATION_H
#define SNAPD_SYSTEM_INFORMATION_H

#include <QtCore/QObject>

namespace Snapd
{
struct SystemInformationPrivate;
  
class Q_DECL_EXPORT SystemInformation : public QObject
{
    Q_OBJECT

public:
    explicit SystemInformation (QObject* parent, void* snapd_object);
    SystemInformation (const SystemInformation&);

    QString osId ();
    QString osVersion ();
    QString series ();
    QString version ();

private:
    SystemInformationPrivate *d_ptr;
    Q_DECLARE_PRIVATE (SystemInformation);
};

}

#endif
