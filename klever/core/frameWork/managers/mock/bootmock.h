#ifndef BOOT_MOCK_H
#define BOOT_MOCK_H
#include <QDebug>
#include <QString>

#include "interfaces/ibootmanager.h"
#include <frameWork/cve.h>

class BootMock : public IBootManager
{
    /*!
     * \brief Пустой виджет настроек
     */
    QWidget *_wgt;


public:

    BootMock();
    ~BootMock();

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

#endif // BOOT_MOCK_H
