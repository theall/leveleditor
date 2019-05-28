# -*- coding: utf-8 -*-
# Made by Bilge Theall
import os
import re
import os
import sys
import argparse

def readText(fn):
    f = open(fn)
    r = f.read()
    f.close()
    return r

def saveToFile(content, file):
    f = open(file, 'w')
    f.write(content)
    f.close()
    
def getClassNames(s):
    p = re.compile(r'\nclass T(\w+)[ \n]')
    return p.findall(s)

def getClassNamesFromFile(file):
    f = readText(file)
    return getClassNames(f)
    
def getCppFileNameFromHeaderName(name):
    if name.endswith('.h'):
        name = name[:-1]
    name = name + 'cpp'
    return name

def getRelativePathFromAbsolutePath(root, path):
    if path.startswith(root):
        path = path[len(root):]
    return path

def getHeaderContentFromClass(className):
    tpl = """#ifndef %s_H
#define %s_H

#include <QObject>

class %s : public QObject
{
    Q_OBJECT

public:
    explicit %s(QObject *parent = 0);

private Q_SLOTS:
    
};

#endif // %s_H"""
    classNameUpper = className.upper()
    return tpl%(classNameUpper,classNameUpper,className,className,classNameUpper)

def getCppContentFromClass(className, headerFileName):
    tpl = """#include "%s"

%s::%s(QObject *parent) : 
    QObject(parent)
{

}

"""
    return tpl%(headerFileName,className,className)
    
def generateHeaderByClass(className, fileFullPath):
    fileData = getHeaderContentFromClass(className)
    saveToFile(fileData, fileFullPath)
    
def generateCppByClass(className, headFile, fileFullPath):
    fileData = getCppContentFromClass(className, headFile)
    saveToFile(fileData, fileFullPath)
    
def generateByClass(className, outputPath, overwrite, verbose=False):
    if not os.path.exists(outputPath):
        os.makedirs(outputPath)

    tstFileName = 'tst_' + className.lower()
    className = 'Test' + className   
    headerFileName = tstFileName + '.h'
    cppFileName = tstFileName + '.cpp'
    headerFileFullPath = os.path.join(outputPath, headerFileName)
    cppFileFullPath = os.path.join(outputPath, cppFileName)
    if not os.path.exists(headerFileFullPath) or overwrite:
        generateHeaderByClass(className, headerFileFullPath)
        if verbose:
            print('Write to ' + headerFileFullPath)
    else:
        print('File exists ' + headerFileFullPath)
    if not os.path.exists(cppFileFullPath) or overwrite:
        generateCppByClass(className, headerFileName, cppFileFullPath)
        if verbose:
            print('Write to ' + cppFileFullPath)
    else:
        print('File exists ' + cppFileFullPath)
    
def process(src, dest, overwrite, verbose=False):
    if not os.path.exists(src):
        print('Path is not exists ' + src)
        return
        
    validFileList = []
    # First step: find all valid header file
    for dirpath,dirnames,filenames in os.walk(src):
        for filename in filenames:
            if filename.endswith(".h"):
                headFile = os.path.join(dirpath, filename) 
                cppFile = getCppFileNameFromHeaderName(headFile)
                if os.path.exists(cppFile):
                    relativePath = getRelativePathFromAbsolutePath(src, dirpath)
                    outputPath = dest + relativePath
                    #print(dest, relativePath, outputPath)
                    validFileList.append((outputPath, headFile))
        
    # Second step: get all class names 
    classNameMap = []
    for outpath, headFile in validFileList:
        for className in getClassNamesFromFile(headFile):
            classNameMap.append((className,outpath,headFile))
            #print((className,outpath,headFile))
    
    # Final step: generate .h/.cpp file by class name and outpath
    for className, outpath, headFile in classNameMap:
        generateByClass(className, outpath, overwrite, verbose)
        
def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--source', '-s', type=str, help='Source directory')
    parser.add_argument('--destination', '-d', type=str, help='Destination directory')
    parser.add_argument('--verbose', '-v', help='Display running details', action="store_true")
    parser.add_argument('--overwrite', '-f', help='Header file', action="store_true")
    args = parser.parse_args()
    if(not args.source or not args.destination):
        parser.print_usage()
        sys.exit(0)
    overwrite = False
    if args.overwrite:
        overwrite = args.overwrite
    verbose = False
    if args.verbose:
        verbose = args.verbose
    process(args.source, args.destination, overwrite, verbose)
    
if __name__=='__main__':
    main()