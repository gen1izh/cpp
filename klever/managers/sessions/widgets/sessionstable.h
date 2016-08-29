#ifndef SESSIONSTABLE_H
#define SESSIONSTABLE_H

/*!
 *  \brief Таблица сессий
 *
 *  Таблица сессий содержит список сессий, запись в нее производится при запуске приложения.
 *  Элементы управления позволяют добавлять новую сессию, удалять сессию\сессии,
 *  соединяться с определенной сессией.
 *
 *
 *  Название сессии(sessionName).
 *  Каждая сессия имеет свое имя, которое представлено обычной строкой.
 *  Сессий с одинаковыми именами и серийными номерами изделий быть не должно!
 *
 *
 *  Тип продукта(название бортовой машины productType).
 *  Могут быть разные типы бортовых машин.
 *  Тип продукта представлен строкой.
 *
 *
 *  Права доступа в сессии(rights).
 *  Каждая сессия должно быть обеспечена своими полномочиями.
 *  То есть например в сессии 1 должно быть реализован доступ  редактированию тестовых
 *  последовательностей, а в другой не доолжно.
 *  Пока права представлены строкой.
 * Менеджер ролей\прав не был проработан. Необходимо его продумать.
 * Возможно роли будут частью менеджера сессий, но с точки зрения правила
 * один объект - одна суть будет неправильно тогда.
 *
 *
 *  Серийный номер устройства(serialNumber).
 *  Представлен строкой.
 *
 *  Путь до сессии, то есть до каталога сессии(sessionPath).
 *  Представлен строкой. Этот путь предоставляет адрес до каталога сессии.
 *  Это необходимо для многих модулей ядра и модулей устройств.
 * Если модуль собирается работать с настройками через ini файл, то этот ini
 * файл должен быть разположен в определенной сессии.
 * Также журналы тоже создаются для каждой сессии свои.
 * Модуль журналирования обращается к sessionPath чтобды узнать где ему расположить
 * журналы работы с ПО.
 *
 *
 */


#include <QWidget>
#include <QComboBox>
#include <QDebug>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QObject>
#include <QPushButton>
#include <QSqlTableModel>
#include <QTableWidgetItem>
#include <QtSql>
#include <QDialog>

#include "sessionpropertydialog.h"
#include "sessioninfodialog.h"

#include <library/databasesapi/mysql/mysqldatabaseapi.h>

// Три категории пользователей
namespace SessionViewNamespace {

  const QString Developer = "Разработчик";
  const QString Operator  = "Оператор";

  const QString password  = "irz.476";

  enum {
    SESSION_ID = 0,
    SESSION_NAME,     // Название сессии
    PRODUCT_TYPE,     // Тип изделия
    RIGHTS,           // Права
    SERIAL_NUMBER,    // Серийный номер
    OTHER             // Другое
  };

  /*!
   * \brief Заполнение хеша заголшовка таблицы
   */
  void fillTableHeaderHash();


  class SessionsTable : public QDialog {

      Q_OBJECT

    /*!
     * \brief Слой на форму менеджера сессий.
     * \details Требуется для компоновки виджетов на форме.
     */
    QGridLayout       *_sessionManagerGridLayout;

    /*!
     * \brief Слой на группе управления сессиями.
     * \details Требуется для компоновки кнопок на группе.
     */
    QVBoxLayout       *_sessionManagerControlsVBoxLayout;

    /*!
     * \brief Группа управления сессиями.
     * \details Группа элементов управления сессиями содержит кнопки для добавления,
     * удаления и соединения с сессией.
     */
    QGroupBox         *_sessionManagerControlsGroupBox;

    /*!
     * \brief Таблица сессий.
     * \details Таблица сессий содержит перечень сессий, как показано на рисунке ниже.
     */
    QTableView       _sessionManagerTable;

    /*!
     * \brief Элемент управления группы - добавления новой сессии.
     * \details При нажатии на кнопку добавления сессии открывается окно параметров сессии.
     */
    QPushButton       *_addSession;

    /*!
     * \brief _deleteSession элемент управления группы - удаления выбранной сессии
     * \details При нажатии на кнопку удаления сессии нужно чтобы была выделена строка.
     */
    QPushButton       *_deleteSession;
    /*!
     * \brief _infoSession элемент управления группы - получения информации о выбранной сессии
     * \details При нажатии на кнопку получения информации о сессии нужно чтобы была выделена строка.
     */
    QPushButton       *_infoSession;

    /*!
     * \brief _connectToSession элемент управления группы - соединения с сессией
     * \details При нажатии на кнопку соединения с сессией нужно чтобы была выделена строка.
     */
    QPushButton       *_connectToSession;

    /*!
     * \brief Лейбл с паролем
     */
    QLabel            *_passwordLabel;

    /*!
     * \brief Поле с паролем
     */
    QLineEdit         *_passwordEdit;

    /*!
     * \brief Табличная модель сессий
     */
    QSqlTableModel  *_model;

    /*!
     * \brief Диалоговое окно создания новой сессии
     */
    SessionPropertyDialog _dlg;

    /*!
     * \brief Диалоговое окно создания новой сессии
     */
    SessionInfoDialog _infoDialog;

//    QSqlDatabase &_db;

  public:

      /*!
       * \brief Формирование диалогового окна менеджера сессий.
       * \details Подготовка виджетов к работе, компоновка их на форме.
       * Группа элементов управления сессиями содержит кнопки для добавления,
       * удаления и соединения с сессией.
       * \image latex session_manager_controls.png "Элементы управления сессиями" width=4cm
       */
      explicit SessionsTable(QDialog *parent = 0);

    ~SessionsTable();

    /*!
     * \brief Создание коннекторов.
     */
    void createConnectors();

    /*!
     * \brief Возвращает таблицу сессий
     */
    QTableView &table() {
      return _sessionManagerTable;
    }


    /*!
     * \brief Возвращает табличную модель сессий
     */
    QSqlTableModel *model(){
      return _model;
    }

  signals:

  public slots:
    /*!
     * \brief Обработчик добавления сессии.
     * \details При нажатии на кнопку добавления сессии открывается окно параметров сессии.
     * \image latex session_manager_add_dialog.png "Параметры сессии"  width=5cm
     */
    void addSession();

    /*!
     * \brief Обработчик удаления сессии.
     * \details При нажатии на кнопку удаления сессии нужно чтобы была выделена строка.
     * Как показано на рисунке ниже.
     * \image latex session_manager_selected.png "Удаление сессии" width=10cm
     */
    void deleteSession();

    /*!
     * \brief Обработчик получения информации о сессии.
     * \details ...
     */
    void infoSession();

    /*!
     * \brief Обработчик подключения к сессии.
     * \details При нажатии на кнопку соединения с сессией нужно чтобы была выделена строка.
     * Как показано на рисунке ниже.
     * \image latex session_manager_selected.png "Соединение с сессией" width=10cm
     */
    bool connectToSession();

    /*!
     * \brief Отобразить собержимое таблицы
     * \param[in] t таблица
     */
    void setModelToView();

    /*!
     * \brief Добавление новой сессии
     * \param name
     * \param product
     * \param right
     * \param serial
     */
    void insertNewSession(QString name, QString product, QString right, QString serial);

    /*!
     * \brief Слот ввода пароля
     */
    void passwordInputSlot(const QString &);

  };

}

#endif // SESSIONSTABLE_H
