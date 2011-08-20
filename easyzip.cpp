#include "easyzip.h"

EasyZip::EasyZip()
{

}

bool EasyZip::Zip(QString fileToZip, QString zipFileName){
    QuaZip zip(zipFileName);
    if(!zip.open(QuaZip::mdCreate)) {
        qWarning("testCreate(): zip.open(): %d", zip.getZipError());
        return false;
    }
    zip.setFileNameCodec("UTF-8");
    /* Pour lire le fichier par blocs de 64Ko */
    QByteArray buffer(65536, Qt::Uninitialized);
    QDir dir(fileToZip);
    QDirIterator iter(fileToZip, QDir::Files, QDirIterator::Subdirectories);
    while(iter.hasNext())
    {
        iter.next();

        if(iter.fileInfo() == QFileInfo(zipFileName))
            continue;

        QString sourceFilename = iter.fileInfo().absoluteFilePath();
        /* Le nom de fichier qui sera stocké dans le .zip */
        QString zipFilename = dir.relativeFilePath(sourceFilename);

        QFile inFile(iter.filePath());
        if(!inFile.open(QIODevice::ReadOnly)) {
            qWarning("testCreate(): inFile.open(): %s", inFile.errorString().toLocal8Bit().constData());
            return false;
        }

        QuaZipFile outFile(&zip);
        if(!outFile.open(QIODevice::WriteOnly, QuaZipNewInfo(zipFilename, sourceFilename))) {
            qWarning("testCreate(): outFile.open(): %d", outFile.getZipError());
            return false;
        }
        while(!inFile.atEnd())
        {
            qint64 nbRead = inFile.read(buffer.data(), buffer.size());
            outFile.write(buffer.data(), nbRead);
        }
        if(outFile.getZipError()!=UNZ_OK) {
            qWarning("testCreate(): outFile.putChar(): %d", outFile.getZipError());
            return false;
        }
        outFile.close();
        if(outFile.getZipError()!=UNZ_OK) {
            qWarning("testCreate(): outFile.close(): %d", outFile.getZipError());
            return false;
        }
        inFile.close();
    }
    zip.close();
    if(zip.getZipError()!=0) {
        qWarning("testCreate(): zip.close(): %d", zip.getZipError());
        return false;
    }
    return true;
}

bool EasyZip::Unzip(QString fileToUnzip, QString unzipFileName)
{
    QFile zipFile(fileToUnzip);
    QuaZip zip(&zipFile);
    if(!zip.open(QuaZip::mdUnzip)) {
      qWarning("testRead(): zip.open(): %d", zip.getZipError());
      return false;
    }
    zip.setFileNameCodec("UTF-8");
    QuaZipFile file(&zip);
    QFile out;
    QString name;
    char c;
    for(bool more=zip.goToFirstFile(); more; more=zip.goToNextFile()) {
      if(!file.open(QIODevice::ReadOnly)) {
        qWarning("testRead(): file.open(): %d", file.getZipError());
        return false;
      }
      name=file.getActualFileName();
      if(file.getZipError()!=UNZ_OK) {
        qWarning("testRead(): file.getFileName(): %d", file.getZipError());
        return false;
      }
      QString dirn = unzipFileName + name;
      if (name.contains('/')) { // subdirectory support
        // there must be a more elegant way of doing this
        // but I couldn't find anything useful in QDir
        dirn.chop(dirn.length() - dirn.lastIndexOf("/"));
        QDir().mkpath(dirn);
      }
      out.setFileName(unzipFileName + name);
      out.open(QIODevice::WriteOnly);
      char buf[4096];
      int len = 0;
      while (file.getChar(&c)) {
        // we could just do this, but it's about 40% slower:
        // out.putChar(c);
        buf[len++] = c;
        if (len >= 4096) {
          out.write(buf, len);
          len = 0;
        }
      }
      if (len > 0) {
        out.write(buf, len);
      }
      out.close();
      if(file.getZipError()!=UNZ_OK) {
        qWarning("testRead(): file.getFileName(): %d", file.getZipError());
        return false;
      }
      if(!file.atEnd()) {
        qWarning("testRead(): read all but not EOF");
        return false;
      }
      file.close();
      if(file.getZipError()!=UNZ_OK) {
        qWarning("testRead(): file.close(): %d", file.getZipError());
        return false;
      }
    }
    zip.close();
    if(zip.getZipError()!=UNZ_OK) {
      qWarning("testRead(): zip.close(): %d", zip.getZipError());
      return false;
    }
    return true;

}
