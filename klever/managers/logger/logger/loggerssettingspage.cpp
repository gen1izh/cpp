#include "loggerssettingspage.h"

#include <library/setupApi/app.h>
#include <library/utilsLibrary/utilslibrary.h>
#include <frameWork/cve.h>

LoggersSettingsPage::LoggersSettingsPage( QWidget *parent )
    : QWidget(parent)
{
  AppSetupApi appsetup;

  loggerTypeLabel       = new QLabel(tr("Тип журнала"));
  loggerTypeBox         = new QComboBox();
  loggerTextNameLabel   = new QLabel(tr("Название журнала"));;
  loggerTextNameEdit    = new QLineEdit;
  loggerEnabledCheckBox = new QCheckBox;

  currentLogger = 0;

  for (int i = 0; i < LoggersSettingsPage::COUNT ; i++ ) {

    QString preff = ((i == SYSTEM_LOG) ? "sys"  :
                     (i == USER_LOG)   ? "user" :
                     (i == MODULE_LOG) ? "module" :
                     (i == SCRIPT_LOG) ? "script" : "none");

    QString name;
    QString enabled;

    getLoggerProperty(i, name, enabled);
    currentLogger = i;
    loggerTextNameEdit->setText(name);
    bool pr = ((enabled == "true") ? true : false);
    loggerEnabledCheckBox->setChecked(pr);

    appsetup.checkApplicationParam( QString("Logger"),
                                    QString("/name%1").arg(i),
                                    QString("Журнал"));

    appsetup.checkApplicationParam( QString("Logger"),
                                    QString("/path%1").arg(i),
                                    QString("/%1").arg(preff));

    appsetup.checkApplicationParam( QString("Logger"),
                                    QString("/objname%1").arg(i),
                                    preff);

    // Системный журнал всегда должен быть включен
    if (i == SYSTEM_LOG) {
      appsetup.checkApplicationParam( QString("Logger"),
                                      QString("/enable%1").arg(i),
                                      QString("true") );
    }
    else {
      appsetup.checkApplicationParam( QString("Logger"),
                                      QString("/enable%1").arg(i),
                                      QString("false") );
    }

    loggerTypeBox->addItem(preff);

    // Получили путь до сессий
    QString sessionPath =
        Cve::instance().getParameterValue(QString("/sessionPath"),
                                          QString(""));
    SysLibrary::UtilsLibrary pathChecker;
    // Проверили существование каталога logs
    pathChecker.checkFolder(QString("%1/logs").arg(sessionPath));

    // Путь до журналов
    QString logPath = QString("%1/logs/%2").arg(sessionPath).arg(preff);

    // Создаем каталог журнала
    pathChecker.checkFolder(logPath);

    // Создание коннекторов
    createConnections();

  }

  currentLogger = 0;
  // Системный журнал
  loggerType_onChanged("sys");

  QGridLayout *mainLayout = new QGridLayout();
  mainLayout->addWidget(loggerTypeLabel,      0, 0);
  mainLayout->addWidget(loggerTypeBox,        0, 1);
  mainLayout->addWidget(loggerEnabledCheckBox,0, 2);
  mainLayout->addWidget(loggerTextNameLabel,  1, 0);
  mainLayout->addWidget(loggerTextNameEdit,   1, 1);

  mainLayout->setAlignment(Qt::AlignTop);

  setLayout(mainLayout);
}

/*
 * Получить свойства логгера
 */
void LoggersSettingsPage::getLoggerProperty(int type, QString &name, QString &enabled)
{
  AppSetupApi appsetup;
  name = appsetup.getApplicationParam(QString("Logger"),
                                      QString("/name%1").arg(type));

  enabled = appsetup.getApplicationParam(QString("Logger"),
                                         QString("/enable%1").arg(type));
}

/*
 * Установить текстовое название логгера
 */
void LoggersSettingsPage::setLoggerTextName(const QString &name)
{
  AppSetupApi appsetup;
  appsetup.setApplicationParam( QString("Logger"),
                                QString("/name%1").arg(currentLogger),
                                name);
}

/*
 * Установить состояние логгера
 */
void LoggersSettingsPage::setLoggerEnabled(int checked)
{
  AppSetupApi appsetup;
  QString  enabled;

  (checked==Qt::Checked)?enabled="true":enabled="false";

  appsetup.setApplicationParam( QString("Logger"),
                                QString("/enable%1").arg(currentLogger),
                                enabled);
}

/*
 * Деструктор страницы настроек
 */
LoggersSettingsPage::~LoggersSettingsPage()
{
}

/*
 * Создание коннекторов класса виджета настройки
 */
void LoggersSettingsPage::createConnections() {
  QObject::connect(loggerTypeBox, SIGNAL(currentTextChanged(const QString&)),
                   this, SLOT(loggerType_onChanged(const QString&)));

  QObject::connect(loggerTextNameEdit, SIGNAL(textChanged(const QString &)),
                   this, SLOT(setLoggerTextName(const QString &)));

  QObject::connect(loggerEnabledCheckBox, SIGNAL(stateChanged(int)),
                   this, SLOT(setLoggerEnabled(int)));

}

/*
 * Обработчик изменения текстового поля имени журнала
 */
void LoggersSettingsPage::loggerType_onChanged(const QString &type) {
  QString name;
  QString enabled;

  int preff = ((type == "sys" )   ? SYSTEM_LOG :
               (type == "user")   ? USER_LOG :
               (type == "module") ? MODULE_LOG :
               (type == "script") ? SCRIPT_LOG : -1);

  currentLogger = preff;

  getLoggerProperty(preff, name, enabled);

  loggerTextNameEdit->setText(name);
  bool pr = ((enabled == "true") ? true : false);
  loggerEnabledCheckBox->setChecked(pr);
}
