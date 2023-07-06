#pragma once

#include <qqml.h>
#include <QAbstractTableModel>
#include <QDir>

class FilesTableModel : public QAbstractTableModel
{
    Q_OBJECT
    QML_ELEMENT
    QML_ADDED_IN_MINOR_VERSION(1)

public:
    enum {
        ColumnName = 0,
        ColumnSize,
        ColumnModifiDate,
        CountOfColumns
    };

    FilesTableModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex & = QModelIndex()) const override;
    int columnCount(const QModelIndex & = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

private:
    QStringList m_columnNames;
    QStringList m_fileList;
    QDir m_directory{""};
};
