#ifndef EASYFILE_H
#define EASYFILE_H

#include <QDir>

class EasyFile
{
public:
    EasyFile();
    static bool RemoveDirectory(QString dirPath);
    static QString GetMinecraftDirectory();
};

#endif // EASYFILE_H
