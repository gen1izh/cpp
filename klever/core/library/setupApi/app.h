#ifndef SETUPAPI_APP_H
#define SETUPAPI_APP_H

#include <QSettings>
#include <QString>
#include <QStringList>
#include <QCoreApplication>

#include "isetupapi.h"
#include "main.h"

class AppSetupApi : public ISetupApi  {

  public:

    AppSetupApi() {
      defaultSetup();
    }

    /*!
     *  \brief Получает значение параметра компонента для ПО Application.
     */
    QString getApplicationParam(QString component, QString key);

    /*!
     *  \brief Проверяет наличие значения параметра компонента для ПО Application.
     */
    void checkApplicationParam(QString component, QString key, QString value);

    /*!
     *  \brief Устанавливает значение параметра компонента для ПО Application.
     */
    void setApplicationParam(QString component, QString key, QString value);
};

#endif // SETUPAPI_APP_H
