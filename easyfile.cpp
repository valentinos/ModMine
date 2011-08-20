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

QString EasyFile::GetMinecraftDirectory()
{
    #ifdef Q_WS_X11
        return QString(QDir::homePath());
    #endif
    #ifdef Q_WS_MAC
        return QString(QDir::homePath()+"/Library/Application Support/");
    #endif
    #ifdef Q_WS_WIN
        if(!QSettings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\User Shell Folders").contains("AppData"))
            return QString("");
        return QString(QSettings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\User Shell Folders").value("AppData").toString()+"\\Roaming\\")
    #endif
    return QString("");
}
