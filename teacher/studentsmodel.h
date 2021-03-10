#ifndef STUDENTSMODEL_H
#define STUDENTSMODEL_H

#include <QObject>
#include <QAbstractListModel>

class StudentObject
{
public:
    StudentObject(const QString &p_addr,
                  const QString &p_status);

    QString getAddr() const;
    QString getStatus() const;

private:
    QString m_addr;
    QString m_status;
};

class StudentsModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum enmRoles {
        addr= Qt::UserRole + 1,
        status
    };

    StudentsModel(QObject *parent = nullptr);

    void addItem(const StudentObject & newItem);

    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

protected:
    QHash<int, QByteArray> roleNames() const; // "ключ" - значение

private:
    QList<StudentObject> m_items;
};

#endif //
