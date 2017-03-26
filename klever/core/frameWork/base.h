#ifndef BASE_H
#define BASE_H

#include <QObject>
#include <QTimer>
#include <QMainWindow>
#include <QSplashScreen>
#include <QScriptEngine>


#include <settings/appsettings.h>

/* Библиотека утилит */
#include <library/utilsLibrary/utilslibrary.h>

/* Модуль журналирования */
#include <plugins/logger/logger.h>
#include <plugins/logger/widgets/settings/settingsform.h>

/* Включения для объектов-оберток модуля скриптов */
#include "sysscripts/systemoperations.h"

/* Работа с параметрами */
#include <library/parameters/parameter.h>

#include <frameWork/gui/klevergui.h>
#include <interfaces/itopmanager.h>

namespace Core {

    /*!
     * \brief Класс основных переменных приложения
     */
    class Base : public QObject, public ITopManager {

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




      Base();
      Base(const Base& root);
      Base& operator=(const Base&);

      /*!
       * \brief Общий словарь параметров.
       *
       * Используется модулями и плагинами для сохранения своего состояния в виде
       * отдельных параметров и для получения состояния других модулей или плагинов.
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

      QSqlDatabase *m_db;
      QSqlDatabase *m_session_db;

      void closeDatabase();
    public:
      /*!
       * \brief Инициализация базы данных
       * \return
       */
      int initializeDatabase();
      /*!
       * \brief Инстанцирование объекта Cve
       * \return
       */
      static Base& instance();

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
      QScriptEngine *scriptEngine() const {
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
       * \brief Загрузка системы
       * \return
       */
      int load();

      /*!
       * \brief Завершаем работу всех плагинов
       */
      int finalize();

      void createTables();
      QSqlDatabase *database();
      int initializeSessionDatabase(const QString &name);
      QSqlDatabase *sessionDatabase();
      void closeSessionDatabase();
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

}
#endif // BASE_H


