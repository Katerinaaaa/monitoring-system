#ifndef STUDENTSMODEL_H
#define STUDENTSMODEL_H

#include <QObject>
#include <QAbstractListModel>

/**
 * @brief The StudentObject class Класс для графического отображения карточек студентов
 */
class StudentObject
{
public:
    /**
     * @brief StudentObject
     * @param p_addr адрес подключённого ПК
     * @param p_status "статус" ПК - цвет
     */
    StudentObject(const QString &p_addr,
                  const QString &p_status);

    /**
     * @brief getAddr
     * @return адрес подключённого ПК
     */
    QString getAddr() const;
    /**
     * @brief getStatus
     * @return "статус" ПК - цвет
     */
    QString getStatus() const;

private:
    /**
     * @brief m_addr Адрес подключённого ПК
     */
    QString m_addr;
    /**
     * @brief m_status "Статус" ПК - цвет
     */
    QString m_status;
};

/**
 * @brief The StudentsModel class Класс для формирование модели с карточками студентов
 */
class StudentsModel : public QAbstractListModel
{
    Q_OBJECT

public:
    /**
     * @brief The enmRoles enum Определение параметров
     */
    enum enmRoles {
        addr= Qt::UserRole + 1,
        status
    };

    /**
     * @brief StudentsModel Оболочка для модели
     * @param parent
     */
    StudentsModel(QObject *parent = nullptr);

    /**
     * @brief addItem Добавление новой записи в модель
     * @param newItem новая запись
     */
    void addItem(const StudentObject & newItem);

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
    QList<StudentObject> m_items;
};

#endif //
