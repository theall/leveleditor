/*
 * Copyright (C) Bilge Theall, wazcd_1608@qq.com
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */
#include "version.h"

#ifdef Q_OS_WIN32
    #include "win32_ver.h"
#endif

TVersionInfo *TVersionInfo::mInstance = NULL;

TVersionInfo::TVersionInfo(QObject *parent) :
    QObject(parent)
  , mVerMajor(0)
  , mVerSecond(0)
  , mVerMin(0)
  , mBuildNo(0)
{
#ifdef Q_OS_WIN32
    mVerMajor = VERSION_MAJOR;
    mVerSecond = VERSION_MINOR;
    mVerMin = VERSION_PATCH;
    mBuildNo = VERSION_BUILD;

    mProductVersion = tr(PRODUCT_VERSION_STR);
    mCompanyName = tr(COMPANY_NAME);
    mDomain = tr(DOMAIN_NAME);
    mInternalName = tr(INTERNAL_NAME);
    mFileDescription = tr(FILE_DESCRIPTION);
    mLegalCopyright = tr(LEGAL_COPYRIGHT);
    mOriginalFilename = tr(ORIGINAL_FILE_NAME);
    mProductName = tr(PRODUCT_NAME);
    mCompilePlatform = tr(COMPILE_PLATFORM);
    mBuildTime = tr(BUILD_TIME);
#endif
}

TVersionInfo::~TVersionInfo()
{

}

TVersionInfo *TVersionInfo::instance()
{
    if(!mInstance)
        mInstance = new TVersionInfo;

    return mInstance;
}

void TVersionInfo::deleteInstance()
{
    if(mInstance)
    {
        delete mInstance;
        mInstance = NULL;
    }
}

int TVersionInfo::major()
{
    return mVerMajor;
}

int TVersionInfo::minor()
{
    return mVerSecond;
}

int TVersionInfo::patch()
{
    return mVerMin;
}

int TVersionInfo::build()
{
    return mBuildNo;
}

QString TVersionInfo::companyName()
{
    return mCompanyName;
}

QString TVersionInfo::fileDescription()
{
    return mFileDescription;
}

QString TVersionInfo::fileVersion()
{
    return mFileVersion;
}

QString TVersionInfo::internalName()
{
    return mInternalName;
}

QString TVersionInfo::legalCopyright()
{
    return mLegalCopyright;
}

QString TVersionInfo::originalFilename()
{
    return mOriginalFilename;
}

QString TVersionInfo::productName()
{
    return mProductName;
}

QString TVersionInfo::productVersion()
{
    return mProductVersion;
}

QString TVersionInfo::compilePlatform()
{
    return mCompilePlatform;
}

QString TVersionInfo::buildTime()
{
    return mBuildTime;
}

QString TVersionInfo::domain()
{
    return mDomain;
}
