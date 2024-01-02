#include "FilesTableModel.h"
#include "CommonFilesMethods.h"


FilesTableModel::FilesTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    m_columnNames << tr("Name") << tr("Size") << tr("Modified Date");


    // Check if the directory exists
    if (!m_directory.exists()) {
        qDebug() << "Directory does not exist.";
    }

    QString file1 = "C:\\Projects\\build-BackuoCleaner-Desktop_Qt_6_5_2_MinGW_64_bit-Debug\\Test1.txt";
    QString file2 = "C:\\Projects\\build-BackuoCleaner-Desktop_Qt_6_5_2_MinGW_64_bit-Debug\\Test2.txt";
    QString file3 = "C:\\Projects\\Test1.txt";

    qDebug() << CommonFilesMethods::compareBinaryFiles(file1,file2);
    qDebug() << CommonFilesMethods::compareFileInfo(QFileInfo(file1),QFileInfo(file3));





    // Set the filter to list only files
    m_directory.setFilter(QDir::Files | QDir::NoDotAndDotDot);
    m_fileList = m_directory.entryList();
//    foreach (QString file, m_fileList) {
//        qDebug() << file;
//    }
}

int FilesTableModel::rowCount(const QModelIndex &) const //TODO sizetype
{
    return m_fileList.count();
}

int FilesTableModel::columnCount(const QModelIndex &) const  //TODO sizetype
{
    return CountOfColumns;
}

QVariant FilesTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    int row = index.row();
    int col = index.column();

    if (row >= rowCount() || col >= columnCount() || role !=  Qt::DisplayRole)
        return QVariant();

    QString file = m_fileList.at(row);
    if (col == ColumnName)
        return file;
    QString filePath = m_directory.filePath(file);
    QFileInfo fileInfo(filePath);
    switch (col)
    {
    case ColumnSize:
        return CommonFilesMethods::formatFileSize(fileInfo.size());
    case ColumnModifiDate:
        return fileInfo.lastModified().toString("dd.MM.yyyy HH:mm:ss");
    }

    return QVariant();
}

QVariant FilesTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation != Qt::Horizontal || role != Qt::DisplayRole || section >= columnCount())
        return QVariant();

    return m_columnNames.at(section);
}

QHash<int, QByteArray> FilesTableModel::roleNames() const
{
    return { {Qt::DisplayRole, "display"} };
}
