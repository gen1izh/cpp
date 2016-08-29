#ifndef REPORT_UPDATE_THREAD_H
#define REPORT_UPDATE_THREAD_H

#include <QObject>
#include <QThread>
#include <QQueue>

#include "reportmodel.h"
#include "../testsequenceexecutortreemodel.h"

class ReportUpdateThread : public QThread {
  Q_OBJECT

  /*!
   * \brief Состояние потока
   */
  int _state;

  /*!
   * \brief Задержка
   */
  int _timeout;

  /*!
   * \brief
   */
  int _onUpdate;

  /*!
   * \brief Список команд
   */
  QQueue<int> _commmand;

  /*!
   * \brief Указатель на модель отчетов
   */
  ReportModel *_reportModel;

  /*!
   * \brief Модель дерева тестовых последовательностей
   */
  TestsequenceExecutorTreeModel   *_model;

  /*!
   * \brief Название тестовой последовательности открытой для редактирования(внешнее представление)
   * Если создаем тест, то первоначально это поле будет пустым
   */
  QString *_testExternalName;

  /*!
   * \brief Название тестовой последовательности открытой для редактирования(внутреннее представление)
   * Если создаем тест, то первоначально это поле будет пустым
   */
  QString *_testInternalName;

  /*!
   * Состояния потока обновления отчета
   */
   enum {
     IDLE,
     RECURSIVE_SET_STATES, //
     UPDATE_REPORT_MODEL,  //
     RECURSIVE_SET_TIME    //
   };

public:
    ReportUpdateThread();

    void run();

    bool isExecuting;

public slots:
    void setModels(TestsequenceExecutorTreeModel   *tm, ReportModel *rm);
    void setTestsequenceExternalName(QString *e);
    void setTestsequenceInternalName(QString *i);
    /*!
     * \brief setRecursiveSetStatesState
     */
    void setRecursiveSetStatesState()   {
      _state = RECURSIVE_SET_STATES;
      _commmand.enqueue(RECURSIVE_SET_STATES);
    }

    /*!
     * \brief setUpdateReportModelState
     */
    void setUpdateReportModelState() {
      _state=UPDATE_REPORT_MODEL;
      _commmand.enqueue(UPDATE_REPORT_MODEL);
    }

    /*!
     * \brief Перевод потока в состояние простоя
     */
    void setIdleState() {
      _state = IDLE;
      _commmand.enqueue(IDLE);
    }

    /*!
     * \brief setRecursiveSetTimeState
     */
    void setRecursiveSetTimeState() {
      _state=RECURSIVE_SET_TIME;
      _commmand.enqueue(RECURSIVE_SET_TIME);
    }

    /*!
     * \brief Отключение потока
     */
    void setTerminateState() {
      isExecuting = false;
    }

    void onUpdate() {
      _onUpdate = true;
    }

    void offUpdate() {
      _onUpdate = false;
    }

    void setTimeout(int timeout) {
      _timeout = timeout*1000;
    }


  signals:
    /*!
     * \brief updateModel
     */
    void updateModel();
};

#endif // REPORT_UPDATE_THREAD_H
