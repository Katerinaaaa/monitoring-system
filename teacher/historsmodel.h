#ifndef HISTORSMODEL_H
#define HISTORSMODEL_H

#include <QObject>
#include <QAbstractListModel>

class HistorObject
{
public:
    HistorObject(const QString &p_status,
                 const QString &p_time,
                 const QString &p_date,
                 const QString &p_exe,
                 const QString &p_descrip);

    QString getStatus() const;
    QString getTime() const;
    QString getDate() const;
    QString getExe() const;
    QString getDescrip() const;

private:
    QString m_status;
    QString m_time;
    QString m_date;
    QString m_exe;
    QString m_descrip;
};

class HistorsModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum enmRoles {
        status= Qt::UserRole + 1,
        time,
        date,
        exe,
        descrip
    };

    HistorsModel(QObject *parent = nullptr);

    void addItem(const HistorObject & newItem);

    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

public slots:
    void clearR();

protected:
    QHash<int, QByteArray> roleNames() const; // "ключ" - значение

private:
    QList<HistorObject> m_items;
};

#endif // HISTORYSMODEL_H

