#ifndef SETUPAPI_MODULE_H
#define SETUPAPI_MODULE_H

#include <QSettings>
#include <QString>
#include <QStringList>
#include <QCoreApplication>

#include <frameWork/base.h>

#include "isetupapi.h"

class ModuleSetupApi : public ISetupApi {

  public:

    ModuleSetupApi() {
      defaultSetup();
    }


    /***************************************************************************
     *                          Комплексные операции
     **************************************************************************/

    /*!
     *  \brief Получает значение параметра компонента для ПО Module.
     */
    QString getModuleParam( QString component, QString key ) {

      // Подключение к Module.
      setSoftwareTypeAsModule();

      // Подключение к компоненту.
      setComponentName( component );

      QString sessionPath = Cve::instance().getParameterValue(QString("/sessionPath"), QString(""));

      // Установка пути до файла с конфигурацией.
      setFileName(QString("%1\\%2").arg(sessionPath).arg("app.ini"));

      // Получение значения параметра.
      QString result = getParam( key, QString("none") );

      return result;
    }

    /*!
     *  \brief Устанавливает значение параметра компонента для ПО Module.
     */
    void setModuleParam( QString component, QString key, QString value ) {

      // Подключение к Module.
      setSoftwareTypeAsModule();

      // Подключение к компоненту.
      setComponentName( component );

      QString sessionPath = Cve::instance().getParameterValue(QString("/sessionPath"), QString(""));
      // Установка пути до файла с конфигурацией.
      setFileName( QString("%1\\%2").arg(sessionPath)
                                    .arg("app.ini") );

      // Устанавливает значения параметра.
      setParam( key, value );

    }

    /*!
     *  \brief Проверяет наличие значения параметра компонента для ПО Module.
     */
    void checkModuleParam( QString component, QString key, QString value ) {

      // Подключение к Module.
      setSoftwareTypeAsModule();

      // Подключение к компоненту.
      setComponentName( component );

      QString sessionPath = Cve::instance().getParameterValue(QString("/sessionPath"), QString(""));
      // Установка пути до файла с конфигурацией.
      setFileName( QString("%1\\%2").arg(sessionPath)
                                    .arg("app.ini") );

      // Устанавливает значения параметра.
      checkParam( key, value );

    }



    /*
     *  TODO: Выше написанные функции не особо нужны, может имеет смысл от них
     *  отказаться.
     */



    /*!
     *  \brief Получает значение параметра компонента для ПО Module
     * в конфигурационном файле согласно path (путь до файла).
     */
    QString getModuleParamByPath( QString component, QString key, QString path ) {

      // Подключение к Module.
      setSoftwareTypeAsModule();

      // Подключение к компоненту.
      setComponentName( component );

      QString sessionPath = Cve::instance().getParameterValue(QString("/sessionPath"), QString(""));
      // Установка пути до файла с конфигурацией.
      setFileName( QString("%1\\%2").arg(sessionPath)
                                    .arg(path) );

      // Получение значения параметра.
      QString result = getParam( key, QString("none") );

      return result;
    }

    /*!
     *  \brief todo
     */
    void checkModuleParamByPath( QString component, QString key, QString value, QString path ) {

      // Подключение к Module.
      setSoftwareTypeAsModule();

      // Подключение к компоненту.
      setComponentName( component );

      QString sessionPath = Cve::instance().getParameterValue(QString("/sessionPath"), QString(""));
      // Установка пути до файла с конфигурацией.
      setFileName( QString("%1\\%2").arg(sessionPath)
                                    .arg(path) );

      // Устанавливает значения параметра.
      checkParam( key, value );
    }

    /*!
     *  \brief todo
     */
    void setModuleParamByPath( QString component, QString key, QString value, QString path ) {

      // Подключение к Module.
      setSoftwareTypeAsModule();

      // Подключение к компоненту.
      setComponentName( component );

      QString sessionPath = Cve::instance().getParameterValue(QString("/sessionPath"), QString(""));
      // Установка пути до файла с конфигурацией.
      setFileName( QString("%1\\%2").arg(sessionPath)
                                    .arg(path) );

      // Получение значения параметра.
      setParam( key, value );
    }

};

#endif // SETUPAPI_MODULE_H
