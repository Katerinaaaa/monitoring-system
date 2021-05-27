#include "historsmodel.h"

#include <QDebug>

HistorObject::HistorObject(const QString &p_status,
                           const QString &p_time,
                           const QString &p_date,
                           const QString &p_exe,
                           const QString &p_descrip)
    : m_status(p_status),
      m_time(p_time),
      m_date(p_date),
      m_exe(p_exe),
      m_descrip(p_descrip)

{
}

HistorsModel::HistorsModel(QObject *parent)
    : QAbstractListModel(parent)
{

}

void HistorsModel::addItem(const HistorObject &newItem)
{
    // благодаря beginInsertRows() и endInsertRows() QML реагирует на изменения модели
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_items << newItem; // добавляем данные в модель
    endInsertRows();
}

int HistorsModel::rowCount(const QModelIndex & parent) const
{
    // метод используется ListView в QML для определения числа элементов
    Q_UNUSED(parent);
    return m_items.count();
}

QVariant HistorsModel::data(const QModelIndex & index, int role) const
{
    if (index.row() < 0 || (index.row() >= m_items.count()))
        return QVariant();

    const HistorObject&itemToReturn = m_items[index.row()];

    if (role == status){
        return itemToReturn.getStatus();}

    else if (role == time)
        return itemToReturn.getTime();

    else if (role == date)
        return itemToReturn.getDate();

    else if (role == exe)
        return itemToReturn.getExe();

    else if (role == descrip)
        return itemToReturn.getDescrip();

    return QVariant();
}


QHash<int, QByteArray> HistorsModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[status] = "status";
    roles[time] = "time";
    roles[date] = "date";
    roles[exe] = "exe";
    roles[descrip] = "descrip";

    return roles;
}


void HistorsModel::clearR()
{
    // благодаря beginInsertRows() и endInsertRows()
    // QML реагирует на изменения модели
    beginRemoveRows(QModelIndex(), 0, rowCount()-1);
    m_items.clear();    // очищаем модель
    endRemoveRows();
}

QString HistorObject::getStatus() const
{
    return m_status;    // статус: good, warning, danger
}

QString HistorObject::getTime() const
{
    return m_time;  // время
}

QString HistorObject::getDate() const
{
    return m_date;  // дата
}

QString HistorObject::getExe() const
{
    return m_exe;   // название лога (exe)
}

QString HistorObject::getDescrip() const
{
    return m_descrip;   // описание лога (путь)
}



