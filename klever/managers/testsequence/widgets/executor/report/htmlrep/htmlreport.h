#ifndef HTMLREPORT_H
#define HTMLREPORT_H

#include <QObject>
#include <QFileInfo>
#include <QDesktopServices>
#include <QPlainTextEdit>
#include <QDate>
#include <QTextStream>
#include <QPushButton>
#include <QLayout>
#include <QCoreApplication>
#include <QDir>

/*!
 * \brief Тип отчета.
 * \details FULL - подробный отчета в виде дерева. SHORT - краткий в виде списка.
 */
enum Type{
  FULL_REPORT,
  SHORT_REPORT
};

const QString infoClass = "ui-corner-all";
const QString warnClass = "ui-state-highlight ui-corner-all";
const QString errorClass = "ui-state-error ui-corner-all";

class HtmlReport : public QObject
{
  Q_OBJECT
private:
  //Константы
  enum {
    COUNTER_SIZE = 10,
    COLNUM = 3
  };

  Type type;
  int counters[COUNTER_SIZE];
  int current;
  QPlainTextEdit data;
  /*!
   * \brief измненение уровня глубины списка.
   * \param level - новая глубина списка.
   */
  void changeLevel(int level);
  /*!
   * \brief Получение номера, в соотвествии с текущим уровнем глубины.
   * \return Номер элемента списка.
   */
  QString getNumber();

  /*!
   * \brief Копирование необходимых для отчета файлов.
   * \param filepath - путь, куда будут скопированы файлы.
   * \param filename - имя копируемого файла.
   * \return Результат операции.
   */
  bool writeFile(QString filepath, QString filename);
public:
  /*!
   * \brief Конструктор, инициализация переменных.
   * \param type - тип отчета(Краткий или подробный).
   * \param parent
   */
  explicit HtmlReport(Type type, QObject *parent = 0);

  /*!
   * \brief Добавление элемента в краткий отчет.
   * \param result - результат тестирования.
   * \param text  - текст результата теста.
   * \param duration - длительность теста.
   */
  void addElement(QString result, QString text, QString duration);

  /*!
   * \brief Создание html отчета.
   * \details При создании html файла, также создается каталог resources,
   * в который копируются необходимые для отчета файлы.
   * \param filename - имя файла или абсолютный путь.
   */
  void createDocument(QString filename, bool isNeedOpen = false, bool isNeedCopyJsFiles=false);

  /*!
   * \brief Добавление заголовка.
   * \param текст заголовка.
   */
  void addHeader(QString text);
  /*!
   * \brief Добавление информации о тесте.
   * \param testname - Название тестовой последовательности.
   * \param project - Название изделия.
   * \param reciever - Название сессии.
   * \param date - Дата проведения испытания.
   */
  void addInformation(QString testname, QString project, QString reciever, QString date);

  /*!
   * \brief Добавление элемента в подробный отчет.
   * \param level - Уровень вложенности элемента.
   * \param result - Результат тестирования.
   * \param text - Текст хода испытаний.
   * \param description - Описание испытания.
   * \param duration - Длительность испытания.
   * \param hasChilds - Имеет ли элемент вложенные элементы.
   */
  void addToTree(int level, QString result, QString text, QString description, QString duration, bool hasChilds);
signals:

public slots:
};

#endif // HTMLREPORT_H
