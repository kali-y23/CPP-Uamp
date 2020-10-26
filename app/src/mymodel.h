#pragma once

#include <QtWidgets>

#include "tags.h"

namespace Ui {
    class MyModel;
}

class MyModel : public QAbstractTableModel
{
    Q_OBJECT
private:
    QVector<QString> m_headers = {"Name", "Audio file path"};
    QVector<Tags> m_data;
    bool editable = false;
    int m_cols = m_headers.size();
public:
    void setEditable(bool flag) {
        editable = flag;
    }

    MyModel(const QVector<Tags> data, QObject* pobj = 0);

    QVariant data(const QModelIndex& index, int nRole) const;

    QVariant getPath(const QModelIndex& index) const;

    bool setData(const QModelIndex& index,
                const QVariant& value,
                int nRole);

    int rowCount(const QModelIndex& parent) const;

    int rowCount() const;

    int columnCount(const QModelIndex& parent) const;

    int columnCount() const;

    QVariant headerData(int nSection,
                        Qt::Orientation orientation,
                        int nRole
                        ) const;

    Qt::ItemFlags flags(const QModelIndex& index) const;

    void setNewData(QVector<Tags>&& data);

    void sort(int column, Qt::SortOrder order = Qt::AscendingOrder);
};