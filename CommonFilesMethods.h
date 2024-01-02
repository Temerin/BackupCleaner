#pragma once

#include <string>
#include <QString>
#include <QFileInfo>

namespace CommonFilesMethods
{
    const std::string GLOBAL_STR_CONST = "TEST";

    QString formatFileSize(qint64 size);
    bool compareFileInfo(const QFileInfo &fileInfo1, const QFileInfo &fileInfo2);
    bool compareBinaryFiles(const QString &filePath1, const QString &filePath2);

}
