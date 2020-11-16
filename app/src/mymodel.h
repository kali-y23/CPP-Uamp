#pragma once

#include <QtWidgets>

#include <deque>

#include "tags.h"

class MyTable;

class MyModel : public QAbstractTableModel
{
    Q_OBJECT
private:
    QVector<QString> m_headers = {"Title", "Artist", "Album", "Genre", "Year", "Track Number", "Rating"};
    std::deque<Tags *> m_data;
    bool editable = false;
    int m_cols = m_headers.size();

public:
    void setEditable(bool flag) {
        editable = flag;
    }

    MyModel(const std::deque<Tags *> data, QObject* pobj = 0);

    QVariant data(const QModelIndex& index, int nRole) const;

    Tags *rowData(const QModelIndex& index) const;

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

    void setNewData(std::deque<Tags *>&& data);

    void addData(Tags *tags);

    void sort(int column, Qt::SortOrder order = Qt::AscendingOrder);

    std::deque<Tags *> getData(void) const;

    void remove(const QModelIndex& index);

signals:
    void insertToQueue(Tags *song);
    void sortQueue(std::deque<Tags *> data, Qt::SortOrder order, int tag);
    void removeFromQueue(Tags *song);
};