#ifndef SYSTEMOPERATIONS_H
#define SYSTEMOPERATIONS_H

#include <QtWidgets>
#include <QObject>
#include <QTextCodec>
#include <QDebug>
#include <QtScript>
#include <QFile>
#include <QTime>
#include <unistd.h>

class SystemOperations : public QObject {
  Q_OBJECT

  enum {
    SUCC = 0,
    ERR  = -1,
    WARN = -2
  };

  /*!
   * \brief Список названий функций
   */
  QStringList _prompting;

  /*!
   * Имя сессии при запуске тестовой последовательности
   */
  QString _fileName;

  /*!
   * Указатель на движок исполнения скриптов
   */
  QScriptEngine *_e;

  /*!
   * \brief _waitAnswerFlag
   */
  bool            _waitAnswerFlag;

  bool            _showMessageFlag;

  public:
    /*!
     * Конструктор библиотеки системных операций
     */
  SystemOperations();

  /*!
   * \brief msgNumber
   */
  int msgNumber;

    /*!
     * \brief     Установка указателя на движок скриптов.
     * \param[in] e - движок скриптов приложения.
     * \param[out] ничего не возвращает.
     */
    void setEngine(QScriptEngine *e) {
      _e = e;
    }

    /*!
     * \brief     Печать(добавление) текста в файл (в кодировке Koi8r).
     * \param[in] txt - произвольный текст.
     * \param[out] ничего не возвращает.
     * \details печатает(добавляет) текст в файл.
     *  _printKoi8r_a - "a" - append.
     * TODO: возможно требует рефакторинга.
     */
    void _printKoi8r_a(QString txt);

    /*!
     * \brief     Печать(создание с перезаписью) текста в файл (в кодировке Koi8r).
     * \param[in] txt - произвольный текст.
     * \param[out] ничего не возвращает.
     * \details печатает(создает файл заново) текст в файл.
     *  _printKoi8r_w - "w" - write.
     * TODO: возможно требует рефакторинга.
     */
    void _printKoi8r_w(QString txt);

    /*!
     * \brief     Печать(добавление) текста в файл (в кодировке utf-8).
     * \param[in] txt - произвольный текст.
     * \param[out] ничего не возвращает.
     * \details печатает(добавляет) текст в файл.
     *  _printUtf8_a - "a" - append.
     * TODO: возможно требует рефакторинга.
     */
    void _printUtf8_a(QString txt);

    /*!
     * \brief     Печать(создание с перезаписью) текста в файл (в кодировке utf-8).
     * \param[in] txt - произвольный текст.
     * \param[out] ничего не возвращает.
     * \details печатает(добавляет) текст в файл.
     *  _printUtf8_w - "w" - write.
     * TODO: возможно требует рефакторинга.
     */
    void _printUtf8_w(QString txt);

    /*!
     * \brief checkDatabaseAndTables
     */
    void checkDatabaseAndTables();

public slots:

    /*******************************************************************************
     *                  Работа с файлами системы
     ******************************************************************************/

    /*!
     * \brief     Cоздание с перезаписью текстового файла (в кодировке Koi8r).
     * \param[in] txt - произвольный текст.
     * \param[out] ничего не возвращает.
     * \details Создает файл заново.
     */
    void createKoi8rFile(QString txt);

    /*!
     * \brief     Cоздание с перезаписью текстового файла (в кодировке Utf8).
     * \param[in] txt - произвольный текст.
     * \param[out] ничего не возвращает.
     * \details Создает файл заново.
     */
    void createUtf8File(QString txt);

    /*!
     * \brief     Установка имени файла, с которым будет производиться работа в скрипте.
     * \param[in] filename - путь до файла.
     * \param[out] ничего не возвращает.
     * \details Сначала вызывается эта функция в скрипте, оперделяется путь до файла.
     * Затем вызывается функция create<CodePage>File() для начала формирования файла.
     * И только потом можно использовать функции записи в файл тегов (либо произвольного текста).
     */
    void setFileName(QString filename);

    /*!
     * \brief     Запись в файл произвольный текст(в кодировке Koi8r).
     * \param[in] txt - произвольный текст.
     * \param[out] ничего не возвращает.
     * \details .
     */
    void printKoi8rSomeText(QString txt);

    /*!
     * \brief     Запись в файл произвольный текст(в кодировке Utf8).
     * \param[in] txt - произвольный текст.
     * \param[out] ничего не возвращает.
     * \details .
     */
    void printUtf8SomeText(QString txt);

    /*******************************************************************************
     *                  Системные вспомогательные операции
     ******************************************************************************/

    /*!
     * \brief     Подключение других скриптов.
     * \param[in] filename - имя до стороннего скрипта. Абсолютный путь до файла.
     *            Относительные пути не проверялись.
     * \param[out] ничего не возвращает.
     * \details Для вызова функций скрипта из другого скрипта применять эту функцию.
     */
    void includeScript(QString filename);

    /*!
     * \brief Установка имени источника журналирования
     * \param[in] name имя источника
     * \details Данная функция необходима для того чтобы в журнале
     *          приложения при записи сообщений
     *          выводился источник.
     */
    void setMeName(QString name);

    /*!
     * \brief Возвращает имя источника(скрипта)
     * \return Возвращает имя
     */
    QString getMyName();

    /*!
     * \brief Пауза исполнения скрипта
     * \param[in] value - количество секунд
     */
    void sleep(int value);

    /*!
     * \brief Пауза исполнения скрипта
     * \param[in] value - количество миллисекунд
     */
    void msleep(int value);

    /*!
     * \brief Прекращение исполнения тестовой последовательности
     */
    void exitFromTestsequence();

    /*!
     * \brief Возвращает текущую дату
     * \return
     */
    QString getCurrentDate();

    /*!
     * \brief Возвращает текущее время
     * \return
     */
    QString getCurrentTime();


    /*!
     * \brief getStringParameter возвращает значение указанной переменной
     * \param name имя переменной
     * \return значение переменной
     */
    QString getStringParameter(QString name);


    /*!
     * \brief setStringParameter устанавливает значение заданной переменной
     * \param name имя переменной
     * \param value значение переменной
     */
    void setStringParameter(QString name, QString value);

    /*!
     * \brief getElapsedTime Костыль для подсчета прошедшего с начала проверки функционирования времени.
     * Нужен конкретно в ПСК
     *
     */
    int getElapsedTime();


  /*!
   * \brief Отображение сообщения пользователю
   * \param[in] text - текстовое сообщение
   * \param[in] okText - название кнопки ok
   * \param[in] cancelText - название кнопки отмены
   * \return
   */
  void showMessage(QString text, QString okText, QString cancelText);

  /*!
   * \brief Сбросить флаг ожидания диалогового окна
   */
  void resetWaitUserAnswerFlag() {
    _waitAnswerFlag = false;
  }

  /*!
   * \brief Результат исполнения диалогового окна
   * \param[in] value - значение
   */
  void setShowMessageResult(bool value) {
    _showMessageFlag = value;
  }

  /*!
   * \brief Выполнение сообщения (диалогового окна)
   * \return
   */
  bool execShowMessage() {
    while(_waitAnswerFlag) {
      ;;;
    }
    return _showMessageFlag;
  }

  /*!
   * \brief executeApplication
   * \param exeName
   * \param arguments
   */
  void executeApplication(QString exeName, QString arguments);

  /*!
   * \brief Открыть документ
   * \param[in] filename - путь до документа, который требуется открыть
   */
  void openDoc(QString filename);

  /*!
   * \brief Получение пути до сессии
   * \return
   */
  QString getSessionPath();

  /*!
   * \brief replaceText Функция подмены текста
   * \param origin Оригинальный текст
   * \param replacement Замена
   */
  void replaceText(QString origin, QString replacement);

  /*!
   * \brief getSerialNumber Возвращает серийный номер, введенный в начале тестирования
   * \return Строка с серийным номером
   */
  QString getSerialNumber();

  /*!
   * \brief containsText Функция поиска текста по файлу
   * \param str Искомый текст
   * \return true - в случае наличия, false - в случае ошибки или отстутствия
   */
  bool containsText(QString str);
signals:

  /*!
   * \brief Сигнал открытия сообщения
   * \param[in] text - текст сообщения
   * \param[in] okText - название кнопки Ок
   * \param[in] cancelText - название кнопки Отмена
   * \return
   */
  void showMessageSignal(QString text, QString okText, QString cancelText);

  /*!
   * \brief Сигнал исполнения  приложения
   * \param[in] exeName - путь до исполняемого файла
   * \param[in] arguments - аргументы передаваемые программе
   */
  void executeApp(QString exeName, QString arguments);

  /*!
   * \brief Сигнал открытия документа
   * \param[in] filename - путь до документа
   */
  void openDocument(QString filename);

};

#endif // SYSTEMOPERATIONS_H
