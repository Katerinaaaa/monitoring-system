#ifndef HISTORSMODEL_H
#define HISTORSMODEL_H

#include <QObject>
#include <QAbstractListModel>

/**
 * @brief The HistorObject class Класс для графического отображения истории логов
 */
class HistorObject
{
public:
    /**
     * @brief HistorObject
     * @param p_status статус: good, warning, danger
     * @param p_time время события
     * @param p_date дата события
     * @param p_exe название лога (exe)
     * @param p_descrip описание лога (путь)
     */
    HistorObject(const QString &p_status,
                 const QString &p_time,
                 const QString &p_date,
                 const QString &p_exe,
                 const QString &p_descrip);

    /**
     * @brief getStatus
     * @return статус: good, warning, danger
     */
    QString getStatus() const;
    /**
     * @brief getTime
     * @return время события
     */
    QString getTime() const;
    /**
     * @brief getDate
     * @return дата события
     */
    QString getDate() const;
    /**
     * @brief getExe
     * @return название лога (exe)
     */
    QString getExe() const;
    /**
     * @brief getDescrip
     * @return описание лога (путь)
     */
    QString getDescrip() const;

private:
    /**
     * @brief m_status Статус: good, warning, danger
     */
    QString m_status;
    /**
     * @brief m_time Время события
     */
    QString m_time;
    /**
     * @brief m_date Дата события
     */
    QString m_date;
    /**
     * @brief m_exe Название лога (exe)
     */
    QString m_exe;
    /**
     * @brief m_descrip Описание лога (путь)
     */
    QString m_descrip;
};

/**
 * @brief The HistorsModel class Класс для формирование модели с историей логов
 */
class HistorsModel : public QAbstractListModel
{
    Q_OBJECT

public:
    /**
     * @brief The enmRoles enum Определение параметров
     */
    enum enmRoles {
        status= Qt::UserRole + 1,
        time,
        date,
        exe,
        descrip
    };

    /**
     * @brief HistorsModel Оболочка для модели
     * @param parent
     */
    HistorsModel(QObject *parent = nullptr);

    /**
     * @brief addItem Добавление новой записи в модель
     * @param newItem новая запись
     */
    void addItem(const HistorObject & newItem);

    /**
     * @brief rowCount Определение количества элементов
     * @param parent
     * @return Количество элементов в модели
     */
    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    /**
     * @brief data Содержимое записи в модели
     * @param index Порядковый номер записи
     * @param role Наименование параметра
     * @return Описание всех полей одной записи
     */
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

public slots:
    /**
     * @brief clearR Очищение модели
     */
    void clearR();

protected:
    /**
     * @brief roleNames Назначение ролей для параметров
     * @return "ключ" - значение
     */
    QHash<int, QByteArray> roleNames() const; // "ключ" - значение

private:
    /**
     * @brief m_items Полный список записей
     */
    QList<HistorObject> m_items;
};

#endif // HISTORYSMODEL_H

