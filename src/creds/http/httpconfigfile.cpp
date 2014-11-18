/*
 * Copyright (C) by Krzesimir Nowak <krzesimir@endocode.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 */

#include "creds/http/httpconfigfile.h"

namespace Mirall
{

namespace
{

const char userC[] = "user";
const char passwdC[] = "passwd";
const char oldPasswdC[] = "password";
const char certPath[] = "certificatePath"; //#UJF
const char certDate[] = "certificateDate";
const char certPasswd[] = "certificatePasswd";

} // ns

QString HttpConfigFile::user() const
{
    return retrieveData(QString(), QLatin1String(userC)).toString();
}

void HttpConfigFile::setUser(const QString& user)
{
    storeData(QString(), QLatin1String(userC), QVariant(user));
}

QString HttpConfigFile::password() const
{
    const QVariant passwd(retrieveData(QString(), QLatin1String(passwdC)));

    if (passwd.isValid()) {
        return QString::fromUtf8(QByteArray::fromBase64(passwd.toByteArray()));
    }

    return QString();
}

void HttpConfigFile::setPassword(const QString& password)
{
    QByteArray pwdba = password.toUtf8();
    storeData( QString(), QLatin1String(passwdC), QVariant(pwdba.toBase64()) );
    removeOldPassword();
}

bool HttpConfigFile::passwordExists() const
{
    return dataExists(QString(), QLatin1String(passwdC));
}

void HttpConfigFile::removePassword()
{
    removeOldPassword();
    removeData(QString(), QLatin1String(passwdC));
}

void HttpConfigFile::fixupOldPassword()
{
    const QString old(QString::fromLatin1(oldPasswdC));

    if (dataExists(QString(), old)) {
        setPassword(retrieveData(QString(), old).toString());
    }
}

void HttpConfigFile::removeOldPassword()
{
    removeData(QString(), QLatin1String(oldPasswdC));
}

QString HttpConfigFile::certificatePath() const //#UJF
{
    return retrieveData(QString(), QLatin1String(certPath)).toString();
}

void HttpConfigFile::setCertificatePath(const QString& cPath)
{
     storeData(QString(), QLatin1String(certPath), QVariant(cPath));
}

QString HttpConfigFile::certificateDate() const
{
    return retrieveData(QString(), QLatin1String(certDate)).toString();
}

void HttpConfigFile::setCertificateDate(const QString& cDate)
{
     storeData(QString(), QLatin1String(certDate), QVariant(cDate));
}

QString HttpConfigFile::certificatePasswd() const
{
    return retrieveData(QString(), QLatin1String(certPasswd)).toString();
}

void HttpConfigFile::setCertificatePasswd(const QString& cPasswd)
{
     storeData(QString(), QLatin1String(certPasswd), QVariant(cPasswd));
}

} // ns Mirall
