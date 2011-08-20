#ifndef EASYZIP_H
#define EASYZIP_H

#include "quazip/quazip.h"
#include "quazip/quazipfile.h"
#include <QDirIterator>

class EasyZip
{
public:
    EasyZip();
    static bool Zip(QString fileToZip, QString zipFileName);
    static bool Unzip(QString fileToUnzip, QString unzipFileName);
    static bool RemoveDirectory(QString dirPath);
};

#endif // EASYZIP_H
