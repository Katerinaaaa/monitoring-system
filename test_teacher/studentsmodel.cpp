#include "studentsmodel.h"

#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

StudentObject::StudentObject(const QString &p_addr,
                             const QString &p_status  )
    : m_addr(p_addr),
      m_status(p_status)
{
}

StudentsModel::StudentsModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

void StudentsModel::addItem(const StudentObject &newItem)
{
    // благодаря beginInsertRows() и endInsertRows() QML реагирует на изменения модели
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_items << newItem;
    endInsertRows();
}

int StudentsModel::rowCount(const QModelIndex & parent) const
{
    // метод используется ListView в QML для определения числа элементов
    Q_UNUSED(parent);
    return m_items.count();
}

QVariant StudentsModel::data(const QModelIndex & index,int role) const
{
    if (index.row() < 0 || (index.row() >= m_items.count()))
        return QVariant();

    const StudentObject&itemToReturn = m_items[index.row()];

    if (role == addr)
        return itemToReturn.getAddr();

    else if (role == status)
        return itemToReturn.getStatus();

    return QVariant();
}

QHash<int, QByteArray> StudentsModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[addr] = "addr";
    roles[status] = "status";

    return roles;
}

QString StudentObject::getAddr() const
{
    return m_addr;      // адрес подключённого ПК
}

QString StudentObject::getStatus() const
{
    return m_status;    // его "статус" - цвет
}
