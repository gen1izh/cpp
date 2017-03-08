#ifndef SESSION_MOCK_H
#define SESSION_MOCK_H

#include <QDebug>
#include <QString>

#include "interfaces/isessionmanager.h"
#include <frameWork/base.h>

class SessionMock : public ISessionPlugin
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
     * \brief Возвращает иконку
     * \return
     */
    QIcon settingIcon();

    /*!
     * \brief Возвращает указатель на виджет настроек
     * \return
     */
    QWidget *settingPage();

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
