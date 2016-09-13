#include "sessionmanager.h"
#include <frameWork/base.h>
#include <interfaces/isessionmanager.h>
#include <QByteArray>

// Проверка существования каталога sessions
void SessionManager::checkSessionContent()
{
  SysLibrary::UtilsLibrary utils;
  // Если каталог sessions не существовал, то создаем его...
  utils.checkFolder(QString("%1//%2").arg(QDir::currentPath()).arg("sessions"));
}

// Открытие всех сессий
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

// Деинициализация элементов менеджера сессии
int SessionManager::finalize() {

}
