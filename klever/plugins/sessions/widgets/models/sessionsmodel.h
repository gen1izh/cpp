#ifndef SESSIONS_MODEL_H
#define SESSIONS_MODEL_H

#include <QStringListModel>
#include <QtSql/QSqlDatabase>

class SessionsModel : public QStringListModel
{

    Q_OBJECT

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
     * \brief Продублировать сессию
     * \param[in] index - модельный индекс
     */
    void dublicateSession(const QModelIndex &index, const QString &cloneName);

    void setSessionInformation(const QString &name, const QString &information);
    QString getSessionInformation(const QString &name);
public slots:
    /*!
     * \brief Обновить модель
     */
    void updateModel();

};

#endif // SESSIONS_MODEL_H
