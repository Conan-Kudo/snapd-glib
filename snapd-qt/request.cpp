/*
 * Copyright (C) 2016 Canonical Ltd.
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation; either version 2 or version 3 of the License.
 * See http://www.gnu.org/copyleft/lgpl.html the full text of the license.
 */

#include <snapd-glib/snapd-glib.h>

#include "Snapd/request.h"

struct QSnapdRequestPrivate
{
    QSnapdRequestPrivate (void *snapd_client)
    {
        client = SNAPD_CLIENT (g_object_ref (snapd_client));
        cancellable = g_cancellable_new ();
    }
  
    ~QSnapdRequestPrivate ()
    {
        g_cancellable_cancel (cancellable);
        g_object_unref (cancellable);      
        g_object_unref (client);
    }

    SnapdClient *client;
    GCancellable *cancellable;
    bool finished;
    QSnapdRequest::QSnapdError error;
    QString errorString;
};

QSnapdRequest::QSnapdRequest (void *snapd_client, QObject *parent) :
    QObject (parent),
    d_ptr (new QSnapdRequestPrivate (snapd_client)) {}

void* QSnapdRequest::getClient ()
{
    Q_D(QSnapdRequest);  
    return d->client;
}

void* QSnapdRequest::getCancellable ()
{
    Q_D(QSnapdRequest);
    return d->cancellable;
}

void QSnapdRequest::finish (void *error)
{
    Q_D(QSnapdRequest);

    d->finished = true;
    if (error == NULL) {
        d->error = NoError;
        d->errorString = "";
    }
    else {
        GError *e = (GError *) error;
        if (e->domain == SNAPD_ERROR) {
            switch ((SnapdError) e->code) 
            {
            case SNAPD_ERROR_CONNECTION_FAILED:
                d->error = QSnapdRequest::QSnapdError::ConnectionFailed;
                break;
            case SNAPD_ERROR_WRITE_FAILED:
                d->error = QSnapdRequest::QSnapdError::WriteFailed;
                break;
            case SNAPD_ERROR_READ_FAILED:
                d->error = QSnapdRequest::QSnapdError::ReadFailed;
                break;
            case SNAPD_ERROR_BAD_REQUEST:
                d->error = QSnapdRequest::QSnapdError::BadRequest;
                break;
            case SNAPD_ERROR_BAD_RESPONSE:
                d->error = QSnapdRequest::QSnapdError::BadResponse;
                break;
            case SNAPD_ERROR_AUTH_DATA_REQUIRED:
                d->error = QSnapdRequest::QSnapdError::AuthDataRequired;
                break;
            case SNAPD_ERROR_AUTH_DATA_INVALID:
                d->error = QSnapdRequest::QSnapdError::AuthDataInvalid;
                break;
            case SNAPD_ERROR_TWO_FACTOR_REQUIRED:
                d->error = QSnapdRequest::QSnapdError::TwoFactorRequired;
                break;
            case SNAPD_ERROR_TWO_FACTOR_INVALID:
                d->error = QSnapdRequest::QSnapdError::TwoFactorInvalid;
                break;
            case SNAPD_ERROR_PERMISSION_DENIED:
                d->error = QSnapdRequest::QSnapdError::PermissionDenied;
                break;
            case SNAPD_ERROR_FAILED:
                d->error = QSnapdRequest::QSnapdError::Failed;
                break;
            case SNAPD_ERROR_TERMS_NOT_ACCEPTED:
                d->error = QSnapdRequest::QSnapdError::TermsNotAccepted;
                break;
            case SNAPD_ERROR_PAYMENT_NOT_SETUP:
                d->error = QSnapdRequest::QSnapdError::PaymentNotSetup;
                break;
            case SNAPD_ERROR_PAYMENT_DECLINED:
                d->error = QSnapdRequest::QSnapdError::PaymentDeclined;
                break;
            default:
                /* This indicates we should add a new entry here... */
                d->error = QSnapdRequest::QSnapdError::UnknownError;
                break;
            }
            d->error = (QSnapdRequest::QSnapdError) e->code;
        }
        else
            d->error = QSnapdRequest::QSnapdError::UnknownError;
        d->errorString = e->message;
    }
    emit complete ();
}

bool QSnapdRequest::isFinished ()
{
    Q_D(QSnapdRequest);
    return d->finished;
}

QSnapdRequest::QSnapdError QSnapdRequest::error ()
{
    Q_D(QSnapdRequest);
    return d->error;
}

QString QSnapdRequest::errorString ()
{
    Q_D(QSnapdRequest);
    return d->errorString;
}

void QSnapdRequest::cancel ()
{
    Q_D(QSnapdRequest);
    g_cancellable_cancel (d->cancellable);
}
