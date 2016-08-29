#include "loggerstabswidgets.h"
#include "../logger/loggerssettingspage.h"
#include <library/utilsLibrary/utilslibrary.h>
#include "../logger/loggerssettingspage.h"
#include <interfaces/ilogger.h>
#include <frameWork/cve.h>

LoggersTabsWidgets::LoggersTabsWidgets(QWidget *parent) : QWidget(parent)
{
  QTabWidget *tabLogger = new QTabWidget();
  AppSetupApi appsetup;
  QString name;
  QString enabled;

  QString sessionPath =
     Cve::instance().getParameterValue(QString("/sessionPath"), QString(""));

  for (int i = 0; i < LoggersSettingsPage::COUNT; i++) {

    QString preff = ((i == SYSTEM_LOG)   ? "sys"  :
                     (i == USER_LOG)     ? "user" :
                     (i == MODULE_LOG)   ? "module" :
                     (i == SCRIPT_LOG)   ? "script" : "none");


    SysLibrary::UtilsLibrary pathChecker;
    QString logPath = QString("%1/logs/%2").arg(sessionPath).arg(preff);

    if (pathChecker.isValidPath("APP_MAIN","Попытка открыть журнал.", logPath)) {
      FileStorage *fs = new FileStorage();
      addDataStorage(fs);

      name = appsetup.getApplicationParam(QString("Logger"),
                                          QString("/name%1").arg(i));

      enabled = appsetup.getApplicationParam(QString("Logger"),
                                             QString("/enable%1").arg(i));

      bool isLogOn = ((enabled == "true") ? true : false);

      Logger *lg = new Logger(NULL, fs, logPath, false, false, isLogOn);
      lg->setObjectName(preff);


      int preff_i = ((preff == "sys" )  ? SYSTEM_LOG :
                    (preff == "user")   ? USER_LOG :
                    (preff == "module") ? MODULE_LOG :
                    (preff == "script") ? SCRIPT_LOG : -1);

      setLogger(preff_i, lg);

      if (isLogOn /* если журнал включен */) {
        tabLogger->addTab(lg->logViewer, name);
      }
    }
  }


  QGridLayout *mainLayout = new QGridLayout();
  mainLayout->addWidget(tabLogger);
  setLayout(mainLayout);

}

