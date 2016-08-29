#ifndef SESSIONMANAGER
#define SESSIONMANAGER

#include <QHash>

enum Right {
  // Менеджеры
  CAN_SEE_MANAGERS_SETTINGS,  // имеет право видеть настройки приложения
  CAN_SEE_MANAGERS_TOOLBAR,   // имеет право видеть панель быстрого запуска
  CAN_SEE_MANAGERS_MENU,      // имеет право видеть главное меню
  // имеет право видеть элементы управления менеджера
  CAN_SEE_MANAGERS_ALL_CONTROLS,    // Видит все элементы управления
  CAN_SEE_MANAGERS_MAIN_CONTROLS,   // Видит только основные элементы управления
  CAN_SEE_MANAGERS_CUSTOM_CONTROLS, // Видит дополнительные элементы управления
  // Модули
  CAN_SEE_MODULES_SETTINGS,  // имеет право видеть настройки приложения
  CAN_SEE_MODULES_TOOLBAR,   // имеет право видеть панель быстрого запуска
  CAN_SEE_MODULES_MENU,      // имеет право видеть главное меню
  // имеет право видеть элементы управления модулей
  CAN_SEE_MODULES_ALL_CONTROLS,    // Видит все элементы управления
  CAN_SEE_MODULES_MAIN_CONTROLS,   // Видит только основные элементы управления
  CAN_SEE_MODULES_CUSTOM_CONTROLS, // Видит дополнительные элементы управления
  // Другие компоненты
  CAN_SEE_APP_DOCS,           // Имеет право смотреть документы
  CAN_SEE_APP_SETTINGS,       // Имеет право видеть настройки приложения
  DEBUG_MODE                  // Отладочный режим

};

/*!
 * \brief
 */
class AccessInterface {

 protected:

   QHash<QString, QHash<int, QPair<bool,QString> > > _rights;

  public:
    AccessInterface(){
      _rights.clear();
    }

    virtual ~AccessInterface(){}

    /*!
     * \brief Проверяет значения доступа на право r у роли role
     * \param role
     * \param r
     * \return
     */
    virtual bool hasRight(QString role, Right r) {
      return _rights[role].value(r).first;
    }

    virtual QHash<QString,QHash<int, QPair<bool,QString> > > rights() {
      return _rights;
    }

    virtual QHash<int, QPair<bool,QString> > rightsByRole(QString role) {
      return _rights[role];
    }

    virtual void setRight(QString role, int r, bool value) {
      ((_rights[role])[r]).first = value;
    }
};

#endif // SESSIONMANAGER

