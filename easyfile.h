#ifndef EASYFILE_H
#define EASYFILE_H

#import <QDir>

class EasyFile
{
public:
    EasyFile();
    static bool RemoveDirectory(QString dirPath);
};

#endif // EASYFILE_H
