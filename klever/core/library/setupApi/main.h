#ifndef SETUPAPI_MAIN_H
#define SETUPAPI_MAIN_H

#include <QSettings>
#include <QString>
#include <QStringList>
#include <QCoreApplication>
#include <QDir>

#include "isetupapi.h"

class MainSetupApi: public ISetupApi {

  public:

    MainSetupApi() {
      defaultSetup();
    }

    /***************************************************************************
     *                          Комплексные операции
     **************************************************************************/


    /*!
     * \brief Получает значение параметра компонента для ПО Application.
     * Источник настроек находится в корневом каталоге с программой.
     */
    QString getMainParam(QString component, QString key) {
      // Подключение к Application.
      setSoftwareTypeAsApplication();
      // Подключение к компоненту.
      setComponentName( component );
      // Устанавливаем путь до файла настроек
      setFileName(QString("%1\\%2").arg(QDir::currentPath())
                  .arg("main.ini"));
      // Получение значения параметра.
      QString result = getParam( key, QString("none") );
      return result;
    }


    /*!
     * \brief Проверяет наличие значения параметра компонента для ПО Application.
     * Источник настроек находится в корневом каталоге с программой.
     */
    void checkMainParam(QString component, QString key, QString value) {
      // Подключение к Application.
      setSoftwareTypeAsApplication();
      // Подключение к компоненту.
      setComponentName( component );
      // Устанавливаем путь до файла настроек
      setFileName(QString("%1\\%2").arg(QDir::currentPath())
                    .arg("main.ini"));
      // Устанавливает значения параметра.
      checkParam( key, value );
    }

    /*!
     * \brief
     */
    QStringList getListKeysMainParam(QString component) {
      // Подключение к Application.
      setSoftwareTypeAsApplication();
      // Подключение к компоненту.
      setComponentName( component );
      // Устанавливаем путь до файла настроек
      setFileName(QString("%1\\%2").arg(QDir::currentPath())
                    .arg("main.ini"));
      // Устанавливает значения параметра.
      return getListKeys();
    }

};

#endif // SETUPAPI_MAIN_H
