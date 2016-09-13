#ifndef SESSION_MOCK_H
#define SESSION_MOCK_H

#include <QDebug>
#include <QString>

#include "interfaces/isessionmanager.h"
#include <frameWork/base.h>

class SessionMock : public ISessionManager
{
    /*!
     * \brief Пустой виджет настроек
     */
    QWidget *_wgt;


public:

    SessionMock();
    ~SessionMock();

    /*!
     * \brief Запустить загрузчик
     * \return
     */
    bool execute();

    /*!
     * \brief Возвращает результат ответа имеет ли пользователь права
     * \param[in] r - право
     * \return
     */
    bool hasRightUser(int r);

    /*!
     * \brief Возвращает иконку
     * \return
     */
    QIcon settingIcon();

    /*!
     * \brief Возвращает указатель на виджет настроек
     * \return
     */
    QWidget *getSettingPage();

    /*!
     * \brief Создание виджетов
     */
    void createWidgets();

    /*!
     * \brief Создание действий
     */
    void createActions();

    /*!
     * \brief Создание коннекторов
     */
    void createConnectors();
};

#endif // SESSION_MOCK_H
