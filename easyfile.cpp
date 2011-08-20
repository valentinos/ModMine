#include "easyfile.h"

EasyFile::EasyFile()
{
}

bool EasyFile::RemoveDirectory(QString dirPath)
{
    QDir dir(dirPath);
    bool success=true;
    if (dir.exists())
    {
        QFileInfoList entries = dir.entryInfoList(QDir::NoDotAndDotDot | QDir::Dirs | QDir::Files);

        for (int i=0,m=entries.size();i<m;++i)
        {
            QString path = entries[i].absoluteFilePath();
            if (!entries[i].isDir())
            {
                QFile file(path);
                if (!file.remove())
                    success=false;
            }
            else
            {
                success=RemoveDirectory(path);
            }
        }
        if (!dir.rmdir(dir.absolutePath()))
            success=false;
    }
    return success;
}
