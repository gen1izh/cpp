#ifndef ISETUPAPI
#define ISETUPAPI

#include <QString>

#include <frameWork/information.h>

class ISetupApi {

  protected:
    QString __moduleName;          // имя модуля
    QString __moduleType;          // тип ПО
    QString __softwareNamePreffix; // префикс имени ПО (kpa, psk ...)
    QString __iniFileName;         // имя ini файла

  public:
    /*!
     *  \brief Устанавливает имя компонента (logger, power ...)
     */
    void setComponentName( QString key ) {
      __moduleName = key;
    }

    /*!
     *  \brief Устанавливает имя ini файла
     *  \return
     */
    void setFileName( QString name ) {
      __iniFileName = name;
    }

    /*!
     *  \brief Устанавливает префикс имени программного продукта
     *  \return
     */
    void setSoftwareNamePreffix( QString preffix ) {
      __softwareNamePreffix = preffix;
    }

    /*!
     * \brief значения по умолчанию
     */
    void defaultSetup() {
      __softwareNamePreffix = Information::instance().softwareNamePrefix();
      __iniFileName         = "default.ini";
    }


    /*!
     *  \brief Устанавливает тип части ПО как модуль.
     *  В настройках первый ключ может быть либо Module, либо Application.
     */
    void setSoftwareTypeAsModule() {
      __moduleType = "Module";
    }

    /*!
     *  \brief  Устанавливает тип части ПО как приложение.
     * В настройках первый ключ может быть либо Module, либо Application.
     */
    void setSoftwareTypeAsApplication() {
      __moduleType = "Application";
    }

    /***************************************************************************
     *                          Основные операции
     **************************************************************************/

    /*!
     *  \brief Устанавливает значение по ключу
     *  \return
     */
    template <class T> void setParam( QString key, T value ) {

      QCoreApplication::setOrganizationName( Information::instance().company() );
      QCoreApplication::setApplicationName( QString( "%1-%2 " )
                                            .arg( __softwareNamePreffix )
                                            .arg( Information::instance().softwareNameSuffix() ));

      QSettings settings( __iniFileName, QSettings::IniFormat );

      QString initKeyString = QString("/%1/%2/%3")
          .arg( Information::instance().version() )
          .arg(__moduleType)
          .arg(__moduleName);

      settings.beginGroup( initKeyString );
      settings.setValue( key, value );
      settings.endGroup();
    }

    /*!
     *  \brief Удаляет все значения по ключу
     *  \return
     */
    void removeParamsByKey( QString key ) {

      QCoreApplication::setOrganizationName( Information::instance().company() );
      QCoreApplication::setApplicationName( QString( "%1-%2 " )
                                            .arg( __softwareNamePreffix )
                                            .arg( Information::instance().softwareNameSuffix() ));

      QSettings settings( __iniFileName, QSettings::IniFormat );

      QString initKeyString = QString("/%1/%2/%3")
          .arg( Information::instance().version() )
          .arg(__moduleType)
          .arg(__moduleName);

      settings.beginGroup( initKeyString );
      settings.remove( key );
      settings.endGroup();
    }

    /*!
     *  \brief Получает значение типа T по ключу
     *  \return
     */
    template <class T> T getParam( QString key, T value = 0 ) {
      Q_UNUSED(value);
      QCoreApplication::setOrganizationName( Information::instance().company() );
      QCoreApplication::setApplicationName( QString( "%1-%2 " )
                                            .arg( __softwareNamePreffix )
                                            .arg( Information::instance().softwareNameSuffix() ));

      QSettings settings( __iniFileName, QSettings::IniFormat );

      QString initKeyString = QString("/%1/%2/%3")
          .arg( Information::instance().version() ).arg(__moduleType)
          .arg(__moduleName);

      settings.beginGroup( initKeyString );
      T result = settings.value( key ).value< T >();
      settings.endGroup();
      return result;
    }

    /*!
     *  \brief Получает все значения типа T по ключу
     *  \return
     */
    QStringList getListKeys() {
      QCoreApplication::setOrganizationName( Information::instance().company() );
      QCoreApplication::setApplicationName( QString( "%1-%2 " )
                                            .arg( __softwareNamePreffix )
                                            .arg( Information::instance().softwareNameSuffix() ));

      QSettings settings( __iniFileName, QSettings::IniFormat );

      QString initKeyString = QString("/%1/%2/%3")
          .arg( Information::instance().version() ).arg(__moduleType)
          .arg(__moduleName);

      settings.beginGroup( initKeyString );

      QStringList result = settings.allKeys();

      settings.endGroup();
      return result;
    }


    /*!
     *  \brief Проверяет значение паарметра ключа
     *         и устанавливает его по умолчанию, если его нет.
     *  \return
     */
    template <class T> void checkParam( QString key, T value ) {

      QCoreApplication::setOrganizationName( Information::instance().company() );
      QCoreApplication::setApplicationName( QString( "%1-%2 " )
                                            .arg( __softwareNamePreffix )
                                            .arg( Information::instance().softwareNameSuffix() ));

      QSettings settings( __iniFileName, QSettings::IniFormat );

      QString initKeyString = QString("/%1/%2/%3")
          .arg( Information::instance().version() )
          .arg(__moduleType)
          .arg(__moduleName);

      settings.beginGroup( initKeyString );

      QStringList keys = settings.childKeys();

      /*
        TODO: key.right(2) - заменить.
        по сути /UObcMax удаление 1 символа
       */
      if ( keys.contains( key.right( key.size() - 1 ) ) ) {
      }
      else {
        settings.setValue( key, value );
      }

      settings.endGroup();
    }


};

#endif // ISETUPAPI

