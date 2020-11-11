#include "listmodel.h"

ListModel::ListModel(const std::vector<Playlist *> data, QObject* pobj)
        : QAbstractListModel(pobj)
        , m_data(data)
{
}

QVariant ListModel::data(const QModelIndex& index, int nRole) const
{
    if (!index.isValid()) {
        return QVariant();
    }
    if (index.row() < 0 || index.row() >= m_data.size()) {
        return QVariant();
    }
    if (nRole != Qt::DisplayRole && nRole != Qt::EditRole) {
        return QVariant();
    }
    return m_data[index.row()]->getName();
}

bool ListModel::setData(const QModelIndex& index,
                      const QVariant& value,
                      int nRole)
{
    if (index.isValid() && nRole == Qt::EditRole) {
        m_data[index.row()]->setName(value.toString());

        emit dataChanged(index, index);
        return true;
    }
    return false;
}

int ListModel::rowCount(const QModelIndex& parent) const {
    if (parent.isValid()) {
        return 0;
    }
    return m_data.size();
}

int ListModel::rowCount() const {
    return m_data.size();
}

QVariant ListModel::headerData(int nSection,
                    Qt::Orientation orientation,
                    int nRole
                    ) const
{
    if (nRole != Qt::DisplayRole) {
        return QVariant();
    }
    if(orientation != Qt::Horizontal) {
        return QVariant();
    }
    return "Name";
}

Qt::ItemFlags ListModel::flags(const QModelIndex& index) const
{
    Qt::ItemFlags flags = QAbstractListModel::flags(index);

    if (index.isValid() && editable == true) {
        flags |= Qt::ItemIsEditable;
    }
    return flags;
}

void ListModel::setNewData(std::vector<Playlist *>&& data) {
    m_data.clear();
    m_data = data;
    emit layoutChanged();
}

void ListModel::addData(Playlist *data) {
    m_data.push_back(data);
    emit layoutChanged();
}
