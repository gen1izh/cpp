#include "sessionmanager.h"
#include <frameWork/base.h>
#include <interfaces/isession.h>
#include <QByteArray>

/*
 * Проверка существования каталога sessions и ini файла
 */
void SessionManager::checkSessionContent()
{
  SysLibrary::UtilsLibrary utils;

  // Если каталог sessions не существовал, то создаем его...
  if (!utils.checkFolder(
         QString("%1//%2").arg(QDir::currentPath()).arg("sessions"))) {
    /*
     * TODO: создание каталога с ошибкой...
     */
  }

  QString query = "SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = 'cve_base'";

  MySQLDataBaseApi::instance().sqlquery("mysql", "session_manager_create_cve_base",
                                         query, "sessions");

  if (MySQLDataBaseApi::instance().query()["sessions"]->size() == 0) {
    MySQLDataBaseApi::instance().createDatabase("cve_base", "session_manager", "sessions");
  }

  // Проверка существования таблицы тестовых последовательностей
  if (!MySQLDataBaseApi::instance().isTableInDatabaseExisting("cve_base", "session_manager", "sessions", "sessions")) {
    MySQLDataBaseApi::instance().createTable("cve_base", "session_manager", "sessions",
                                             "(id INT NOT NULL PRIMARY KEY AUTO_INCREMENT, "
                                             "Name TEXT, "
                                             "Product_type TEXT, "
                                             "Rights TEXT, "
                                             "Serial_number TEXT, "
                                             "Other TEXT );", "sessions");
  }
}

/*!
 * \brief Запуск кода загрузчика
 * \return Результат выполнения
 */
bool SessionManager::execute() {
  bool result=false;
  if (isOn()) {
    // Подготовка менеджера сессий к работе
    // Открытие файла сессий
    checkSessionContent();

    // Установка модели во вьювер
    _sessionsDialog.setModelToView();

    // Проверка наличия сессий по-умолчанию
    checkDefaultSessions();

    // Отобразить диалоговое окно менеджера сессий
    while (!result) {
      try {
        if (showSessions())  {
            result = true;

            // Переключить контекст на текущую сессию
            switchToCurrentSession();
        }
      }
      catch (QString) {
        return false;
      }
    }

//      delete _sessionsDialog.model();
//      delete _sessionsDialog;
    return result;
  }
  return true;
}

/*
 * Проверка наличия сессий по-умолчанию
 */
void SessionManager::checkDefaultSessions() {
  // Чтение перечня менеджеров из настроек
  MainSetupApi mainsetup;
//  mainsetup.checkMainParam(QString("iam"), QString("name"), QString("УСТРОЙСТВО"));
  QString devname = mainsetup.getMainParam(QString("iam"), QString("devname"));
  mainsetup.checkMainParam(QString("iam"), QString("serial"), QString("000000"));
  QString serialNumber = mainsetup.getMainParam(QString("iam"), QString("serial"));
  QString operatorName  = mainsetup.getMainParam(QString("iam"), QString("operator_name"));
  QString developerName = mainsetup.getMainParam(QString("iam"), QString("developer_name"));

  Core::Base::instance().setParameterValue(QString("/device_cve_name"), devname);

  // Получение модельного индекса выделенной ячейки
  int count = _sessionsDialog.model()->rowCount();

  bool isDefaultDeveloperExist = false;
  bool isDefaultOperatorExist  = false;

  for (int i=0; i<count; i++) {
    QString productType  = _sessionsDialog.model()->index(i, PRODUCT_TYPE).data().toString();
    QString sessionRight = _sessionsDialog.model()->index(i, RIGHTS).data().toString();
    if (devname == productType) {
      if (sessionRight == Developer) {
        isDefaultDeveloperExist = true;
      }
      if (sessionRight == Operator) {
        isDefaultOperatorExist = true;
      }
    }
  }

  /*
   * Если сессия по-умолчанию для разработчика не собрана
   */
  if (!isDefaultDeveloperExist) {
    _sessionsDialog.model()->insertRows(0,1);
    _sessionsDialog.model()->setData(_sessionsDialog.model()->index(0, SESSION_NAME),  developerName);
    _sessionsDialog.model()->setData(_sessionsDialog.model()->index(0, PRODUCT_TYPE),  devname);
    _sessionsDialog.model()->setData(_sessionsDialog.model()->index(0, RIGHTS),        Developer);
    _sessionsDialog.model()->setData(_sessionsDialog.model()->index(0, SERIAL_NUMBER), serialNumber);

    if (!_sessionsDialog.model()->submitAll()) {
      qDebug() << "err: boot: create developer session " << _sessionsDialog.model()->lastError();
    }
  }

  /*
   * Если сессия по-умолчанию для оператора не собрана
   */
  if (!isDefaultOperatorExist) {
    _sessionsDialog.model()->insertRows(0,1);
    _sessionsDialog.model()->setData(_sessionsDialog.model()->index(0, SESSION_NAME),  operatorName);
    _sessionsDialog.model()->setData(_sessionsDialog.model()->index(0, PRODUCT_TYPE),  devname);
    _sessionsDialog.model()->setData(_sessionsDialog.model()->index(0, RIGHTS),        Operator);
    _sessionsDialog.model()->setData(_sessionsDialog.model()->index(0, SERIAL_NUMBER), serialNumber);

    if (!_sessionsDialog.model()->submitAll()) {
      qDebug() << "err: boot: create operator session " << _sessionsDialog.model()->lastError();
    }
  }
}



/*
 *  Функция переключения на текущую сессию
 */
void SessionManager::switchToCurrentSession() {

  QString name, right, serial, producttype;
  bool ok;

  // Получение модельного индекса выделенной ячейки
  int row = _sessionsDialog.table().currentIndex().row();

  name        = _sessionsDialog.model()->index(row,SESSION_NAME).data().toString();
  producttype = _sessionsDialog.model()->index(row,PRODUCT_TYPE).data().toString();
  right       = _sessionsDialog.model()->index(row,RIGHTS).data().toString();
  serial      = _sessionsDialog.model()->index(row,SERIAL_NUMBER).data().toString();
  int id          = _sessionsDialog.model()->index(row,SESSION_ID).data().toInt(&ok);

  Core::Base::instance().setParameterValue(QString("/sessionId"),id);

  Core::Base::instance().setParameterValue(QString("/rights"),right);

  Core::Base::instance().setParameterValue(QString("/sessionName"),name);

  Core::Base::instance().setParameterValue(QString("/productType"),producttype);

  Core::Base::instance().setParameterValue(QString("/serialNumber"),serial);

  Core::Base::instance().setParameterValue(QString("/sessionPath"),
                                    QString("%1/%2/%3")
                                    .arg(QDir::currentPath())
                                    .arg("sessions")
                                    .arg(name ));

  setRights(); // после того как выбрали роль устанавливаем права доступа
}


/*
 * Установка прав доступа на роли
 */
void SessionManager::setRights() {
  AppSetupApi         appsetup;
  QPair<bool,QString> pair;
  QHash<int, QPair<bool,QString> > h;
  bool ok;

  _rights.insert(Developer, h);
  _rights.insert(Operator,  h);

  QHashIterator<QString, QHash<int, QPair<bool,QString> > >
      j(Core::CveManager::instance().boot()->rights());
  while (j.hasNext()) {
    j.next();

    QString txt = j.key();
    quint16 unic = qChecksum(txt.toStdString().c_str(),txt.size());

    // Проверяем наличие этих параметров, если они не заданы, то создаем их
    // По-умолчанию включаем все.
      appsetup.checkApplicationParam(QString("Session"),
                                     QString("/CAN_SEE_MANAGERS_SETTINGS_%1").arg(unic),
                                     QString("1"));

      appsetup.checkApplicationParam(QString("Session"),
                                     QString("/CAN_SEE_MANAGERS_TOOLBAR_%1").arg(unic),
                                     QString("1"));

      appsetup.checkApplicationParam(QString("Session"),
                                     QString("/CAN_SEE_MANAGERS_MENU_%1").arg(unic),
                                     QString("1"));

      appsetup.checkApplicationParam(QString("Session"),
                                     QString("/CAN_SEE_MANAGER_ALL_CONROLS_%1").arg(unic),
                                     QString("1"));

      appsetup.checkApplicationParam(QString("Session"),
                                     QString("/CAN_SEE_MANAGER_MAIN_CONROLS_%1").arg(unic),
                                     QString("1"));

      appsetup.checkApplicationParam(QString("Session"),
                                     QString("/CAN_SEE_MANAGER_CUSTOM_CONROLS_%1").arg(unic),
                                     QString("1"));



      appsetup.checkApplicationParam(QString("Session"),
                                     QString("/CAN_SEE_MODULES_SETTINGS_%1").arg(unic),
                                     QString("1"));

      appsetup.checkApplicationParam(QString("Session"),
                                     QString("/CAN_SEE_MODULES_TOOLBAR_%1").arg(unic),
                                     QString("1"));

      appsetup.checkApplicationParam(QString("Session"),
                                     QString("/CAN_SEE_MODULES_MENU_%1").arg(unic),
                                     QString("1"));

      appsetup.checkApplicationParam(QString("Session"),
                                     QString("/CAN_SEE_MODULES_ALL_CONROLS_%1").arg(unic),
                                     QString("1"));

      appsetup.checkApplicationParam(QString("Session"),
                                     QString("/CAN_SEE_MODULES_MAIN_CONROLS_%1").arg(unic),
                                     QString("1"));

      appsetup.checkApplicationParam(QString("Session"),
                                     QString("/CAN_SEE_MODULES_CUSTOM_CONROLS_%1").arg(unic),
                                     QString("1"));



      appsetup.checkApplicationParam(QString("Session"),
                                     QString("/CAN_SEE_APP_DOCS_%1").arg(unic),
                                     QString("1"));

      appsetup.checkApplicationParam(QString("Session"),
                                     QString("/CAN_SEE_APP_SETTINGS_%1").arg(unic),
                                     QString("1"));

      appsetup.checkApplicationParam(QString("Session"),
                                     QString("/DEBUG_MODE_%1").arg(unic),
                                     QString("1"));


      // считываем значения и записываем в хэш роле с правами доступа
      pair.first  = static_cast<bool>((appsetup.getApplicationParam(QString("Session"),
                                     QString("CAN_SEE_MANAGERS_SETTINGS_%1").arg(unic))).toInt(&ok,10));
      pair.second = "CAN_SEE_MANAGERS_SETTINGS";
      h.insert(CAN_SEE_MANAGERS_SETTINGS,pair);

      pair.first  = static_cast<bool>((appsetup.getApplicationParam(QString("Session"),
                                     QString("CAN_SEE_MANAGERS_TOOLBAR_%1").arg(unic))).toInt(&ok,10));
      pair.second = "CAN_SEE_MANAGERS_TOOLBAR";
      h.insert(CAN_SEE_MANAGERS_TOOLBAR,pair);


      pair.first  = static_cast<bool>((appsetup.getApplicationParam(QString("Session"),
                                     QString("CAN_SEE_MANAGERS_MENU_%1").arg(unic))).toInt(&ok,10));
      pair.second = "CAN_SEE_MANAGERS_MENU";
      h.insert(CAN_SEE_MANAGERS_MENU,pair);


      pair.first  = static_cast<bool>((appsetup.getApplicationParam(QString("Session"),
                                     QString("CAN_SEE_MANAGER_ALL_CONROLS_%1").arg(unic))).toInt(&ok,10));
      pair.second = "CAN_SEE_MANAGER_ALL_CONROLS";
      h.insert(CAN_SEE_MANAGERS_ALL_CONTROLS,pair);


      pair.first  = static_cast<bool>((appsetup.getApplicationParam(QString("Session"),
                                     QString("CAN_SEE_MANAGER_MAIN_CONROLS_%1").arg(unic))).toInt(&ok,10));
      pair.second = "CAN_SEE_MANAGER_MAIN_CONROLS";
      h.insert(CAN_SEE_MANAGERS_MAIN_CONTROLS,pair);


      pair.first  = static_cast<bool>((appsetup.getApplicationParam(QString("Session"),
                                     QString("CAN_SEE_MANAGER_CUSTOM_CONROLS_%1").arg(unic))).toInt(&ok,10));
      pair.second = "CAN_SEE_MANAGER_CUSTOM_CONROLS";
      h.insert(CAN_SEE_MANAGERS_CUSTOM_CONTROLS,pair);




      // считываем значения и записываем в хэш роле с правами доступа
      pair.first  = static_cast<bool>((appsetup.getApplicationParam(QString("Session"),
                                     QString("CAN_SEE_MODULES_SETTINGS_%1").arg(unic))).toInt(&ok,10));
      pair.second = "CAN_SEE_MODULES_SETTINGS";
      h.insert(CAN_SEE_MODULES_SETTINGS,pair);

      pair.first  = static_cast<bool>((appsetup.getApplicationParam(QString("Session"),
                                     QString("CAN_SEE_MODULES_TOOLBAR_%1").arg(unic))).toInt(&ok,10));
      pair.second = "CAN_SEE_MODULES_TOOLBAR";
      h.insert(CAN_SEE_MODULES_TOOLBAR,pair);


      pair.first  = static_cast<bool>((appsetup.getApplicationParam(QString("Session"),
                                     QString("CAN_SEE_MODULES_MENU_%1").arg(unic))).toInt(&ok,10));
      pair.second = "CAN_SEE_MODULES_MENU";
      h.insert(CAN_SEE_MODULES_MENU,pair);


      pair.first  = static_cast<bool>((appsetup.getApplicationParam(QString("Session"),
                                     QString("CAN_SEE_MODULES_ALL_CONROLS_%1").arg(unic))).toInt(&ok,10));
      pair.second = "CAN_SEE_MODULES_ALL_CONROLS";
      h.insert(CAN_SEE_MODULES_ALL_CONTROLS,pair);


      pair.first  = static_cast<bool>((appsetup.getApplicationParam(QString("Session"),
                                     QString("CAN_SEE_MODULES_MAIN_CONROLS_%1").arg(unic))).toInt(&ok,10));
      pair.second = "CAN_SEE_MODULES_MAIN_CONROLS";
      h.insert(CAN_SEE_MODULES_MAIN_CONTROLS,pair);


      pair.first  = static_cast<bool>((appsetup.getApplicationParam(QString("Session"),
                                     QString("CAN_SEE_MODULES_CUSTOM_CONROLS_%1").arg(unic))).toInt(&ok,10));
      pair.second = "CAN_SEE_MODULES_CUSTOM_CONROLS";
      h.insert(CAN_SEE_MODULES_CUSTOM_CONTROLS,pair);






      pair.first  = static_cast<bool>((appsetup.getApplicationParam(QString("Session"),
                                     QString("CAN_SEE_APP_DOCS_%1").arg(unic))).toInt(&ok,10));
      pair.second = "CAN_SEE_APP_DOCS";
      h.insert(CAN_SEE_APP_DOCS,pair);


      pair.first  = static_cast<bool>((appsetup.getApplicationParam(QString("Session"),
                                     QString("CAN_SEE_APP_SETTINGS_%1").arg(unic))).toInt(&ok,10));
      pair.second = "CAN_SEE_APP_SETTINGS";
      h.insert(CAN_SEE_APP_SETTINGS,pair);


      pair.first  = static_cast<bool>((appsetup.getApplicationParam(QString("Session"),
                                     QString("DEBUG_MODE_%1").arg(unic))).toInt(&ok,10));
      pair.second = "DEBUG_MODE";
      h.insert(DEBUG_MODE,pair);


      _rights.insert(j.key(),h);

  }

}


//  Запуск диалогового окна
bool SessionManager::showSessions() {

  bool res = ( _sessionsDialog.exec() == QDialog::Accepted );

  /* Обработка нажатия кнопки Отмены */
  if (!res) {
    throw QString("ExitException");
  }
  else{
    return _sessionsDialog.connectToSession();
  }
}

/*
 * Деинициализация элементов менеджера сессии
 */
void SessionManager::finalize() {

}
