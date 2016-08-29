#ifndef APP_DATA_INITIALIZER_H
#define APP_DATA_INITIALIZER_H

#include <QObject>
#include <QTimer>
#include <QMainWindow>
#include <QSplashScreen>
#include <QScriptEngine>

/* Системные модули */
//#include <managers/testsequence/cveTestSequences.h>

#include <settings/appsettings.h>

/* Библиотека утилит */
#include <library/utilsLibrary/utilslibrary.h>

/* Модуль журналирования */
#include <managers/logger/logger/logger.h>
#include <managers/logger/logger/loggerssettingspage.h>

/* Включения для объектов-оберток модуля скриптов */
#include "sysscripts/systemoperations.h"
#include <interfaces/moduleinterface.h>
#include <settings/modules/modulesmanager.h>


/* Работа с параметрами */
#include <library/parameters/parameter.h>

#include <library/databasesapi/mysql/mysqldatabaseapi.h>

#include <frameWork/gui/cvegui.h>

/*!
 * Константы стилей ПО КПА графической оболочки
 */
enum {
  QPLASTIQUESTYLE = 0,
  QWINDOWSXPSTYLE,
  QMACSTYLE,
  QWINDOWSSTYLE,
  QCDESTYLE,
  QMOTIFSTYLE
};

/*!
 * \brief Класс основных переменных приложения
 */
class Cve : public QObject {

  Q_OBJECT

  /*!
   * \brief Системные операции
   */
  SystemOperations *_sysops;

  /*!
   * \brief Список  глобальных значений
   */
  QList<QScriptValue> _value;

  /*!
   * Движок для исполнения скриптов
   */
  QScriptEngine  *_scriptEvaluteEngine;

  /*!
   * \brief AppDataInitializerObject
   */
  Cve(){
    setObjectName(tr("ПО КПА"));
    MySQLDataBaseApi::instance();

    _sysops               = new SystemOperations();
    _scriptEvaluteEngine  = new QScriptEngine();

    QScriptValue value = _scriptEvaluteEngine->newQObject(_sysops);


    _value.append(value);
    _scriptEvaluteEngine->globalObject().setProperty(tr("iam"), value);

    // Передаем указатель на движок qtscript.
    // Необходим для реализации функции setEngine.
    _sysops->setEngine(_scriptEvaluteEngine);

    connect(_sysops, SIGNAL(showMessageSignal(QString,QString,QString)),
            this, SLOT(showMessage(QString,QString,QString)));

    connect(_sysops, SIGNAL(executeApp(QString,QString)),
            this, SLOT(executeApplication(QString,QString)));

    connect(_sysops, SIGNAL(openDocument(QString)),
            this, SLOT(openDocument(QString)));
  }
  /*!
   * \brief AppDataInitializerObject
   * \param root
   */
  Cve(const Cve& root);
  /*!
   * \brief operator =
   * \return
   */
  Cve& operator=(const Cve&);

  /*!
   * \brief Общий словарь параметров.
   *
   * Используется модулями и менеджерами для сохранения своего состояния в виде
   * отдельных параметров и для получения состояния других модулей или менеджеров.
   *
   * \sa getParameter().
   */
  QHash<QString, Parameter *> _parameters;

  /*!
   * \brief Настройки приложения
   */
  AppSettings                *_appSettings;

  /*!
   * \brief Слот запуска стороннего приложения
   * \param exeName - путь до исполняемого файла
   * \param arguments - параметры вызова
   */
  void startApp(QString exeName, QString arguments);

public:

  /*!
   * \brief Инстанцирование объекта Cve
   * \return
   */
  static Cve& instance();

  /*!
    \name Работа с параметрами
    \{
   */
  /*!
   * \brief Возвращает параметр с указанным именем.
   * \param[in] name  Имя параметра
   * \returns параметр с указанным именем.
   *          Если данный параметр не существует, возвращается 0.
   */
  Parameter *getParameter(const QString &name) const {
    return _parameters.value(name);
  }

  /*!
   * \brief Возвращает значение параметра с указанным именем.
   * \param[in] name          имя параметра
   * \param[in] defaultValue  значение, которое должна вернуть функция,
   *                          если указанный параметр не существует
   * \return значение параметра, или значение \a defaultValue,
   *                          если указанный параметр не существует
   */
  template <typename T>
  T getParameterValue(const QString &name,
                             const T &defaultValue = T()) const {
    Parameter *parameter = getParameter(name);
    return (parameter ? parameter->getValue<T>() : defaultValue);
  }

  /*!
   * \brief Добавляет в общий словарь параметров указанный параметр.
   * \param[in] key   ключ
   * \param[in] value значение по ключу
   *
   * Функция используется для добавления параметров, которые предоставляет модуль
   * или менеджер в общий словарь параметров.
   *
   */
  template <typename T>
  void setParameterValue(QString key, T value) {

    QHashIterator<QString, Parameter *> i(_parameters);
    while (i.hasNext()) {
      i.next();
      if (i.key() == key) { 
        i.value()->setValue(value); // Установка значения в уже созданный Parameter

        emit parameterValueChanged(key, value);
        return;
      }
    }

    Parameter *prm = new Parameter(key); // Создание объекта Parameter с именем key
    prm->setValue(value);                // Установка значения в объект Parameter
    _parameters[key] = prm;              // Создание записи в хеше

    emit parameterValueChanged(key, value);
  }

  /*!
   * \brief Возвращает хеш параметров
   * \return
   */
  QHash<QString, Parameter *> params() {
    return _parameters;
  }

      /*! \} */

  /*!
   * \brief Инициализация настроек
   */
  void initializeSettings();

  /*!
   * \brief Запуск модулей через 100 мс после прогрузки модулей
   */
  void startModulesBy100ms();

  /*!
   * \brief Настройки приложения
   * \return возвращает указатель на объект настроек приложения
   */
  AppSettings *setting() {
    return _appSettings;
  }

  /*!
   * \brief  Возвращает указатель на движок скриптов
   * \return
   */
  QScriptEngine *scriptEngine() const{
    return _scriptEvaluteEngine;
  }

  /*!
   * \brief Возвращает список глобальных переменных
   * \return
   */
  QList<QScriptValue> globalValueList() const { return _value; }

  /*!
   * \brief Возвращает указатель на операции
   * \return
   */
  SystemOperations *operations() const { return _sysops; }

  /*!
   * \brief Добавить переменную в списко глобальных
   * \param[in] v - переменная, которую добавляют в список доступных из под скрипта
   */
  void addToGlobalValueList(QScriptValue v) { _value.append(v); }

  /*!
   * \brief Удаление объектов модулей устройств
   */
  void finalize();

signals:
  /*!
   * \brief Сигнал изменения значения параметра
   * \param[in] name - название параметра
   * \param[in] value - значение
   */
  void parameterValueChanged(QString name, QVariant value);

public slots:

  /*!
   * \brief Открытие окна сообщений
   * \param[in] text - текст сообщения
   * \param[in] okText - текст кнопки Ok
   * \param[in] cancelText - текст кнопки Cancel
   */
  void showMessage(QString text, QString okText, QString cancelText);

  /*!
   * \brief Исполнение приложения
   * \param[in] exeName - название приложения
   * \param[in] arguments - аргументы
   */
  void executeApplication(QString exeName, QString arguments);

  /*!
   * \brief Слот открытия документа
   * \param[in] filename - путь до файла
   */
  void openDocument(QString filename);
};


#endif // APP_DATA_INITIALIZER_H


