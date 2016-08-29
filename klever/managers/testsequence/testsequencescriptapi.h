#ifndef TESTSEQUENCE_SCRIPT_API_H
#define TESTSEQUENCE_SCRIPT_API_H

#include <QObject>
#include <QDebug>

#include <frameWork/cve.h>

#include "widgets/executor/testsequenceexecutortreeitem.h"

class TestsequenceScriptApi : public QObject
{
  Q_OBJECT

  /*!
   * \brief Элемент тест-кейса
   */
  TestsequenceExecutorTreeItem *_item = nullptr;

  public:
    explicit TestsequenceScriptApi(QObject *parent = 0);

    /*!
     * \brief Установка тест-кейса
     * \param[in] item - элемент тест-кейса
     */
    void setItem(TestsequenceExecutorTreeItem *item) {
      _item = item;
    }

  signals:

  public slots:
    /*!
     * \brief Получить параметр по имени в тест-кейсе
     * \param[in] name - имя параметра
     * \return
     */
    QString getArg(QString name);

    QString getArg(QString name, QString defaultValue);

    /*!
     * \brief Запись информационного сообщения в таблицу отчета
     * \param[in] content содержимое сообщения
     */
    void information(QString content);

    /*!
     * \brief Запись сообщения предупреждения в таблицу отчета
     * \param[in] content содержимое сообщения
     */
    void warning(QString content);

    /*!
     * \brief Запись ошибочного сообщения в таблицу отчета
     * \param[in] content содержимое сообщения
     */
    void error(QString content);


};

#endif // TESTSEQUENCE_SCRIPT_API_H
