#include "reportupdatethread.h"
#include <frameWork/gui/cvegui.h>

ReportUpdateThread::ReportUpdateThread()
{
  _onUpdate = false;
  _timeout  = 5000;
}


void ReportUpdateThread::run()
{
  //
  isExecuting = true;
  int  operation;

  while(isExecuting) {
    if (_onUpdate == false) {
      if (!_commmand.isEmpty()) {
        operation = _commmand.dequeue();
      }
      else {
        msleep(_timeout);
      }
    }
    else {
      if (!_commmand.isEmpty()) {
        operation = _commmand.dequeue();
        switch (operation) {

          case RECURSIVE_SET_STATES:
            CveGui::instance().blockMainWindowByDialog("Подождите! \n"
                                                       "Идет актуализация состояний тест-кейсов \n"
                                                       "для тестовой последовательности!");
            while (CveGui::instance().isNeedWait()) { msleep(100); }
            _reportModel->finalizeTestState();
            CveGui::instance().unblockMainWindowByDialog();
            while (CveGui::instance().isNeedWait()) { msleep(100); }
            break;

          case UPDATE_REPORT_MODEL:
            CveGui::instance().blockMainWindowByDialog("Подождите! \n"
                                                       "Идет актуализация состояния \n"
                                                       "тестовой последовательности!");
            while (CveGui::instance().isNeedWait()) { msleep(100); }
            _reportModel->readReportTreeFromDatabase(_reportModel->getRootItem());
            emit updateModel();
            CveGui::instance().unblockMainWindowByDialog();
            while (CveGui::instance().isNeedWait()) { msleep(100); }
            break;

          case RECURSIVE_SET_TIME:
            CveGui::instance().blockMainWindowByDialog("Подождите! \n"
                                                       "Идет актуализация времени исполнения тест-кейсов \n"
                                                       "для тестовой последовательности!");
            while (CveGui::instance().isNeedWait()) { msleep(100); }
            _model->treewalkSetAvarageTimeTestSequence(QModelIndex());
            CveGui::instance().unblockMainWindowByDialog();
            while (CveGui::instance().isNeedWait()) { msleep(100); }
            break;

          case IDLE:
            msleep(_timeout);
            break;

          default:
            break;
        };
      }
    }

  }

}

/*
 *
 */
void ReportUpdateThread::setTestsequenceExternalName(QString *e) {
  _testExternalName = e;
}

/*
 *
 */
void ReportUpdateThread::setTestsequenceInternalName(QString *i) {
  _testInternalName = i;
}



/*
 *
 */
void ReportUpdateThread::setModels(TestsequenceExecutorTreeModel *tm, ReportModel *rm) {
  _model = tm;
  _reportModel = rm;
}
