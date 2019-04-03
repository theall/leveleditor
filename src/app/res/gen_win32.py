##
# Script for generate foreplaer version information on win32
# Copyright (C) Bilge Theall, wazcd_1608@qq.com
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software Foundation,
# Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
##
import os
import sys
import time

g_keyMap = {
'BUILD_NUMBER':       '"0"',
'K_COMPANYNAME':      '"CompanyName"',
'K_FILEDESCRIPTION':  '"FileDescription"',
'K_FILEVERSION':      '"FileVersion"',
'K_INTERNALNAME':     '"InternalName"',
'K_LEGALCOPYRIGHT':   '"LegalCopyright"',
'K_ORIGINALFILENAME': '"OriginalFilename"',
'K_PRODUCTNAME':      '"ProductName"',
'K_PRODUCTVERSION':   '"ProductVersion"',
'K_COMPILEPLATFORM':  '"CompilePlatform"',
'K_BUILDNUMBER':      '"BuildNumber"',
'K_DOMAIN':           '"Domain"',
'K_BUILD_TIME':       '"BuildTime"',
'PRODUCT_ICON':       '"logo.ico"',
'VERSION_MAJOR':      '0',
'VERSION_MINOR':      '1',
'VERSION_PATCH':      '0',
'VERSION_BUILD':      '0',
'FILE_VERSION':       '0,1,0,0',
'FILE_VERSION_STR':   '"0.1.0.0"',
'PRODUCT_VERSION':    '0,1,0,0',
'PRODUCT_VERSION_STR':'"0.1.0.0"',
'COMPANY_NAME':       '"Bilge Theall"',
'DOMAIN_NAME':        '"Theall"',
'INTERNAL_NAME':      '"LevelEditor.exe"',
'FILE_DESCRIPTION':   '"Level Editor Preview Edition."',
'LEGAL_COPYRIGHT':    '"Copyright (C) 2016-2017 Bilge Theall, All rights reserved."',
'ORIGINAL_FILE_NAME': '"LevelEditor.exe"',
'PRODUCT_NAME':       '"Level Editor"',
'ORGANIZATION_DOMAIN':'"https://www.2dcombat.org/"',
'COMPILE_PLATFORM':   '"MingW 2013, 32 bit"',
'BUILD_TIME':         '"2017-01-19 19:08:18"'
}
    
def showHelp():
    print(help_string)
    
def main():
    version = os.environ.get("CHREDITOR_VERSION", '0.0.0.0')
    if version is None:
        version = '0.0.0.0'
    major,minjor,pajor,build = version.split('.')
    major,minjor,pajor,build = int(major),int(minjor),int(pajor),int(build)
    g_keyMap['BUILD_NUMBER'] = '"%d"'%build;
    g_keyMap['FILE_VERSION'] = '%d,%d,%d,%d'%(major,minjor,pajor,build);
    g_keyMap['FILE_VERSION_STR'] = '"%d.%d.%d.%d"'%(major,minjor,pajor,build);
    g_keyMap['PRODUCT_VERSION'] = '%d,%d,%d,%d'%(major,minjor,pajor,build);
    g_keyMap['PRODUCT_VERSION_STR'] = '"%d.%d.%d.%d"'%(major,minjor,pajor,build);
    g_keyMap['BUILD_TIME'] = '"%s"'%time.strftime("%Y-%m-%d %H:%M:%S", time.localtime()) 
    g_keyMap['LEGAL_COPYRIGHT'] = '"Copyright (C) 2016-%d Bilge Theall, All rights reserved."'%time.localtime().tm_year
    g_keyMap['VERSION_MAJOR'] = major
    g_keyMap['VERSION_MINOR'] = minjor
    g_keyMap['VERSION_PATCH'] = pajor
    g_keyMap['VERSION_BUILD'] = build
    f = open("win32_ver.h", "w")
    f.write("#ifndef WIN32_VER_H\n")
    f.write("#define WIN32_VER_H\n")
    for key in g_keyMap.keys():
        item = '#define %s %s\n'%(key, g_keyMap[key])
        f.write(item)
    f.write("#endif");
    f.close();
    
if __name__=='__main__':
    main()
    
    