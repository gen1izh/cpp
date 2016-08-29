#ifndef SETUPAPI_SESSION_H
#define SETUPAPI_SESSION_H

#include <QSettings>
#include <QString>
#include <QStringList>
#include <QCoreApplication>

#include "isetupapi.h"

class SessionSetupApi : public ISetupApi {

  public:

    SessionSetupApi() {
      defaultSetup();
    }

    /***************************************************************************
     *                          При работе с session.ini
     **************************************************************************/
    /*!
     *  \brief Устанавливает второй уровень ключа
     */
    void setSecondKey( QString st ) {
      __moduleType = st;
    }

    /*!
     *  \brief Устанавливает третий уровень ключа
     */
    void setThirdKey( QString st ) {
      __moduleName = st;
    }
};

#endif // SETUPAPI_SESSION_H
