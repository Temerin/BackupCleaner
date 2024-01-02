#include "CommonFilesMethods.h"
#include <QFile>
#include <QDebug>
#include <QDir>


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
    // qDebug() << "compare " <<  filePath1 << "and" << filePath2;
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
    // qDebug() << "compare " <<  fileInfo1.absoluteFilePath() << "and" << fileInfo2.absoluteFilePath();
    return (fileInfo1.fileName() == fileInfo2.fileName()
            && fileInfo1.size() == fileInfo2.size()
            && fileInfo1.lastModified() == fileInfo2.lastModified());
}

QStringList CommonFilesMethods::findMatchingFiles(QDir dir1, QDir dir2)
{
    qDebug() << __PRETTY_FUNCTION__;
    QStringList result;
    if (!dir1.exists()) {
        qDebug() << "Directory 1 does not exist.";
        return result;
    }
    if (!dir2.exists()) {
        qDebug() << "Directory 2 does not exist.";
        return result;
    }

    QStringList files1 = dir1.entryList(QDir::Files | QDir::NoDotAndDotDot);
    QStringList files2 = dir2.entryList(QDir::Files | QDir::NoDotAndDotDot);

    // Проходим по каждому файлу в первой директории
    for (const QString &file1 : files1) {
        QFileInfo fileInfo1(dir1.filePath(file1));
         // qDebug() << file1;

        // Проходим по каждому файлу во второй директории
        for (const QString &file2 : files2) {
            // qDebug() << file2;
            QFileInfo fileInfo2(dir2.filePath(file2));

            // Если файлы совпадают по вашему сравнению, добавляем путь файла из dir1 в результат
            if (compareFileInfo(fileInfo1, fileInfo2)) {
                if (compareBinaryFiles(fileInfo1.absoluteFilePath(), fileInfo2.absoluteFilePath())) {
                    // qDebug() << fileInfo1.absoluteFilePath() << "==" << fileInfo2.absoluteFilePath();
                    result.append(fileInfo1.filePath());
                    break;  // Выход из цикла, так как нашли совпадение
                }
            }
        }
    }

     return result;
}
