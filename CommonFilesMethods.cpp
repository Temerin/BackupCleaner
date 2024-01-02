#include "CommonFilesMethods.h"
#include <QFile>
#include <QDebug>


QString CommonFilesMethods::formatFileSize(qint64 size)
{
    const qint64 KB = 1024;
    const qint64 MB = KB * 1024;
    const qint64 GB = MB * 1024;

    if (size >= GB) {
        // Если размер больше или равен 1 Гб
        return QString("%1 Гб").arg(static_cast<double>(size) / GB, 0, 'f', 2);
    } else if (size >= MB) {
        // Если размер больше или равен 1 Мб, но меньше 1 Гб
        return QString("%1 Мб").arg(static_cast<double>(size) / MB, 0, 'f', 2);
    } else if (size >= KB) {
        // Если размер больше или равен 1 Кб, но меньше 1 Мб
        return QString("%1 Кб").arg(static_cast<double>(size) / KB, 0, 'f', 2);
    } else {
        // Если размер меньше 1 Кб
        return QString("%1 байт").arg(size);
    }
}

bool CommonFilesMethods::compareBinaryFiles(const QString &filePath1, const QString &filePath2)
{
    QFile file1(filePath1);
    QFile file2(filePath2);

    if (!file1.open(QIODevice::ReadOnly) || !file2.open(QIODevice::ReadOnly)) {
        qWarning() << "Не удалось открыть файлы для сравнения.";
        return false;
    }

    QByteArray content1 = file1.readAll();
    QByteArray content2 = file2.readAll();

    file1.close();
    file2.close();

    // Сравниваем содержимое байт за байтом
    return content1 == content2;
}

bool CommonFilesMethods::compareFileInfo(const QFileInfo &fileInfo1, const QFileInfo &fileInfo2)
{
    return (fileInfo1.fileName() == fileInfo2.fileName()
            && fileInfo1.size() == fileInfo2.size()
            && fileInfo1.lastModified() == fileInfo2.lastModified());
}
