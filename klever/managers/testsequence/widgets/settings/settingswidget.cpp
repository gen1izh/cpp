#include "settingswidget.h"
#include "ui_testsequencesettingswidget.h"
#include <QFileInfo>
#include <QFileDialog>
#include <library/setupApi/app.h>
#include <library/message/messagelibrary.h>
#include <frameWork/cve.h>

TestsequenceSettingsWidget::TestsequenceSettingsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestsequenceSettingsWidget)
{
  ui->setupUi(this);

  initializeWidget();

  createConnectors();
}

TestsequenceSettingsWidget::~TestsequenceSettingsWidget()
{
  delete ui;
}

/*
 * Инициализация виджета настроек
 */
void TestsequenceSettingsWidget::initializeWidget() {
  AppSetupApi setting;

  setting.checkApplicationParam(QString("Testsequence"), QString("/path"), QString(""));

  // Настройки внешнего вида
  setting.checkApplicationParam(QString("Testsequence"), QString("/executorWindowNameEdit"),
                                QString("Исполнитель тестовой последовательности"));
  setting.checkApplicationParam(QString("Testsequence"), QString("/chooseReportTabNameEdit"),
                                QString("Выбор отчета"));
  setting.checkApplicationParam(QString("Testsequence"), QString("/reportHtmlTabNameEdit"),
                                QString("Отчет Html"));
  setting.checkApplicationParam(QString("Testsequence"), QString("/reportTabNameEdit"),
                                QString("Отчет"));
  setting.checkApplicationParam(QString("Testsequence"), QString("/testsequenceNavigationEdit"),
                                QString("Тестовые последовательности"));
  setting.checkApplicationParam(QString("Testsequence"), QString("/testsequenceNavigationEdit"),
                                QString("Тестовые последовательности"));
  setting.checkApplicationParam(QString("Testsequence"), QString("/scriptNavigationEdit"),
                                QString("Скрипты"));

  setting.checkApplicationParam(QString("Testsequence"),
                                QString("/abortAfterError"), "false");

  QString abortAfterError  = setting.getApplicationParam(QString("Testsequence"),
                                                      QString("/abortAfterError"));

  if (abortAfterError == "true") {
    Cve::instance().setParameterValue(QString("AbortAfterError"), true);
    ui->abortAfterErrorBox->setChecked(true);
  }
  else {
    Cve::instance().setParameterValue(QString("AbortAfterError"), false);
    ui->abortAfterErrorBox->setChecked(false);
  }

  QString executorWindowNameEdit  = setting.getApplicationParam(QString("Testsequence"),
                                                                QString("/executorWindowNameEdit"));
  QString chooseReportTabNameEdit = setting.getApplicationParam(QString("Testsequence"),
                                                                QString("/chooseReportTabNameEdit"));
  QString reportHtmlTabNameEdit   = setting.getApplicationParam(QString("Testsequence"),
                                                                QString("/reportHtmlTabNameEdit"));
  QString reportTabNameEdit       = setting.getApplicationParam(QString("Testsequence"),
                                                                QString("/reportTabNameEdit"));
  QString testsequenceNavigationEdit  = setting.getApplicationParam(QString("Testsequence"),
                                                                QString("/testsequenceNavigationEdit"));
  QString scriptNavigationEdit       = setting.getApplicationParam(QString("Testsequence"),
                                                                QString("/scriptNavigationEdit"));

  ui->chooseReportTabNameEdit->setText(chooseReportTabNameEdit);
  ui->executorWindowNameEdit->setText(executorWindowNameEdit);
  ui->reportHtmlTabNameEdit->setText(reportHtmlTabNameEdit);
  ui->reportTabNameEdit->setText(reportTabNameEdit);
  ui->testsequenceNavigationEdit->setText(testsequenceNavigationEdit);
  ui->scriptNavigationEdit->setText(scriptNavigationEdit);

  QString path = setting.getApplicationParam(QString("Testsequence"), QString("/path"));

  if (path.isEmpty()) {
    // Блокнот, по-умолчанию
    QString windowsNotepad = "C:/WINDOWS/system32/notepad.exe";
    QFileInfo file(windowsNotepad);
    if (file.exists()) {
      setting.setApplicationParam(QString("Testsequence"),
                                  QString("/path"),
                                  QString(windowsNotepad) );
    }
  }

  path = setting.getApplicationParam(QString("Testsequence"),
                                     QString("/path"));

  // Установка пути до редактора
  ui->pathEdit->setText(path);

  setEditorPath(path);
}

/*
 * Возвращает путь до редактора
 */
QString TestsequenceSettingsWidget::getEditorPath() {
  return _editorPath;
}

/*
 * Установка пути до редактора
 */
void TestsequenceSettingsWidget::setEditorPath(QString path) {
  _editorPath = path;
}

/*
 * Создание коннекторов
 */
void TestsequenceSettingsWidget::createConnectors() {
  connect(ui->pathBrowserButton, SIGNAL(clicked()),
          this, SLOT(openPathDialog()));
}

/*
 * Открытие диалогового окна
 * Необходимо для выбора редактора скриптов
 */
void TestsequenceSettingsWidget::openPathDialog() {
  AppSetupApi setting;

  QString path = QFileDialog::getOpenFileName( NULL,
                              tr("Выберите редактор скриптов"),
                              QString("C:\\" ),
                              tr("Приложение (*.exe )"),
                              NULL,
                              QFileDialog::DontUseNativeDialog );

  ui->pathEdit->setText(path);

  setting.setApplicationParam(QString("Testsequence"),
                              QString("/path"),
                              path);

  setEditorPath(path);
}

/*
 * Кнопка сохранения параметров текстовых полей
 */
void TestsequenceSettingsWidget::on_saveButton_clicked()
{
  AppSetupApi setting;

  setting.setApplicationParam(QString("Testsequence"),
                              QString("/executorWindowNameEdit"),
                              ui->executorWindowNameEdit->text());
  setting.setApplicationParam(QString("Testsequence"),
                              QString("/chooseReportTabNameEdit"),
                              ui->chooseReportTabNameEdit->text());
  setting.setApplicationParam(QString("Testsequence"),
                              QString("/reportHtmlTabNameEdit"),
                              ui->reportHtmlTabNameEdit->text());
  setting.setApplicationParam(QString("Testsequence"),
                              QString("/reportTabNameEdit"),
                              ui->reportTabNameEdit->text());
  setting.setApplicationParam(QString("Testsequence"),
                              QString("/testsequenceNavigationEdit"),
                              ui->testsequenceNavigationEdit->text());
  setting.setApplicationParam(QString("Testsequence"),
                              QString("/scriptNavigationEdit"),
                              ui->scriptNavigationEdit->text());

  messageLibrary msg;
  msg.createInfoMessage(tr("Информация"), tr("Спасибо, что изменили значения текстовых послей! "
                                             "А теперь перезапутите ПО!"));
}

void TestsequenceSettingsWidget::on_abortAfterErrorBox_stateChanged(int arg1)
{
  Q_UNUSED(arg1)

  AppSetupApi setting;

  if (ui->abortAfterErrorBox->isChecked()) {
    setting.setApplicationParam(QString("Testsequence"),
                                QString("/abortAfterError"),
                                "true");
  }
  else {
    setting.setApplicationParam(QString("Testsequence"),
                                QString("/abortAfterError"),
                                "false");
  }

  Cve::instance().setParameterValue(QString("AbortAfterError"), ui->abortAfterErrorBox->isChecked());

}
