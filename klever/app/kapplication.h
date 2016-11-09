#ifndef KAPPLICATION_H
#define KAPPLICATION_H

#include <QString>
#include <QDir>
#include <QDebug>
#include <QCoreApplication>

#include <frameWork/managers.h>


namespace KApplication {

    enum {
        KAPP_SUCCESSFUL = 0,
        KAPP_SOME_ERROR = 100,
        KAPP_SYSTEM_FINALIZE_ERROR,
        KAPP_GUI_FINALIZE_ERROR
    };


    void instanceTopManagers();

    /*!
     * \brief Инициализация пути к плагинам приложения
     * \return
     */
    QString initPluginsPath();

    /*!
     * \brief Чтение информации о программе.
     */
    void readInformation();

    /*!
     * \brief Финализация приложения
     * \return
     */
    int finalize();

    /*!
     * \brief Соединение элементов менеджеров
     */
    void connect();

    /*!
     * \brief Установка сплеш-скрина  видимым
     * \param[in] value
     */
    void setSplashScreenVisible(bool value);

    /*!
     * \brief Подготовка. Стадия 1.
     */
    void prepareStage1();

    /*!
     * \brief Подготовка. Стадия 2.
     */
    void prepareStage2();

    /*!
     * \brief Подготовка. Стадия 3.
     */
    void prepareStage3();

}

#endif // KAPPLICATION_H
