#pragma once

#include <QtWidgets>
#include <list>
#include <vector>

#include "playlist.h"

class ListModel : public QAbstractListModel
{
    Q_OBJECT
private:
    std::vector<Playlist *> m_data;
    bool editable = false;

public:
    void setEditable(bool flag) {
        editable = flag;
    }

    ListModel(const std::vector<Playlist *> data, QObject* pobj = 0);

    QVariant data(const QModelIndex& index, int nRole) const;

    bool setData(const QModelIndex& index,
                const QVariant& value,
                int nRole);

    int rowCount(const QModelIndex& parent) const;

    int rowCount() const;

    QVariant headerData(int nSection,
                        Qt::Orientation orientation,
                        int nRole
                        ) const;

    Qt::ItemFlags flags(const QModelIndex& index) const;

    void setNewData(std::vector<Playlist *>&& data);

    void addData(Playlist *data);

    void clear() {
        m_data.clear();
    }

    std::vector<Playlist *> data() {
        return m_data;
    }

    Playlist *data(int row) {
        return m_data[row];
    }

    void remove(const QModelIndex& index);

};