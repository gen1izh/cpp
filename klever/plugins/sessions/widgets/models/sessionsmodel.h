#ifndef SESSIONS_MODEL_H
#define SESSIONS_MODEL_H

#include <QStringListModel>
#include <QtSql/QSqlDatabase>

class SessionsModel : public QStringListModel
{

    Q_OBJECT

    QSqlDatabase m_db;

public:
    SessionsModel();
    ~SessionsModel();

    /*!
     * \brief Возвращает список всех сессий
     * \return
     */
    QStringList selectAllSessions();

    /*!
     * \brief Добавить сессию
     * \param[in] name - имя сессии
     * \param[in] parameters - информация о сессии
     */
    void addSession(QString name, QString parameters);

    /*!
     * \brief Удалить сессию
     * \param[in] index - модельный индекс
     */
    void deleteSession(const QModelIndex &index);

    /*!
     * \brief Переименовать сессию
     * \param[in] index - модельный индекс
     */
    void renameSession(const QModelIndex &index, const QString &new_name);

    /*!
     * \brief Продублировать сессию
     * \param[in] index - модельный индекс
     */
    void dublicateSession(const QModelIndex &index);

public slots:
    /*!
     * \brief Обновить модель
     */
    void updateModel();

};

#endif // SESSIONS_MODEL_H
