#ifndef PDFREPORTER_H
#define PDFREPORTER_H

#include <QObject>
#include <QList>
#include <qtrpt.h>

class PdfReporter : public QObject
{
  Q_OBJECT
private:
  QtRPT *report;
  QList<QPair<int, QString> > data;
  int counters[50];
  int current;

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
public:
  /*!
   * \brief Конструктор, инициализация переменных.
   */
  PdfReporter();
  ~PdfReporter();

  /*!
   * \brief Создание полей отчета.
   */
  void createDataFields();
  /*!
   * \brief Создание титульного листа.
   * \param testname - имя теста.
   * \param sender - имя отправителя.
   * \param reciever - имя приемщика.
   */
  void createTitle(QString test, QString sender, QString reciever);

  /*!
   * \brief Добавление элемента в отчет.
   * \param level - глубина в списке.
   * \param text  - текст элемента.
   */
  void addElement(int level, QString text);
  /*!
   * \brief Создание pdf файла.
   * \param filename - имя файла.
   */
  void createDocument(QString filename);

private slots:
  /*!
   * \brief Заполенение полей, слот вызывается при создании файла.
   * \param fieldObject - поле для редактирования.
   */
  void setField(RptFieldObject &fieldObject);
};

#endif // PDFREPORTER_H
