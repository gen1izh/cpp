#include "app.h"
#include <frameWork/cve.h>

/*!
 *  \brief Получает значение параметра компонента для ПО Application.
 */
QString AppSetupApi::getApplicationParam(QString component, QString key) {

  // Подключение к Application.
  setSoftwareTypeAsApplication();

  // Подключение к компоненту.
  setComponentName( component );

  QString sessionPath =Cve::instance().getParameterValue(QString("/sessionPath"), QString(""));

  // Установка пути до файла с конфигурацией.
  setFileName( QString("%1\\%2").arg(sessionPath)
                                .arg("app.ini") );

  // Получение значения параметра.
  QString result = getParam( key, QString("none") );

  return result;
}


/*!
 *  \brief Проверяет наличие значения параметра компонента для ПО Application.
 */
void AppSetupApi::checkApplicationParam(QString component, QString key, QString value) {

  // Подключение к Application.
  setSoftwareTypeAsApplication();

  // Подключение к компоненту.
  setComponentName(component);

  QString sessionPath = Cve::instance().getParameterValue(QString("/sessionPath"), QString(""));

  // Установка пути до файла с конфигурацией.
  setFileName( QString("%1\\%2").arg(sessionPath)
                                .arg("app.ini") );

  // Устанавливает значения параметра.
  checkParam(key, value);

}


/*!
 *  \brief Устанавливает значение параметра компонента для ПО Application.
 */
void AppSetupApi::setApplicationParam(QString component, QString key, QString value) {

  // Подключение к Application.
  setSoftwareTypeAsApplication();

  // Подключение к компоненту.
  setComponentName( component );

  QString sessionPath =Cve::instance().getParameterValue(QString("/sessionPath"), QString(""));

  // Установка пути до файла с конфигурацией.
  setFileName( QString("%1\\%2").arg(sessionPath)
                                .arg("app.ini") );

  // Устанавливает значения параметра.
  setParam( key, value );

}
