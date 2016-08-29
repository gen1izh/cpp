#include "testcaseeditordialog.h"
#include "ui_testcaseeditordialog.h"


TestcaseEditorDialog::TestcaseEditorDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::TestcaseEditorDialog)
{
  ui->setupUi(this);

  // Установка флагов для диалогового окна
  setWindowFlags( Qt::Window
                | Qt::MSWindowsFixedSizeDialogHint
                | Qt::WindowCloseButtonHint);

  setWindowTitle(tr("Редактирование тест-кейса..."));
}

TestcaseEditorDialog::~TestcaseEditorDialog()
{
  delete ui;
}

void TestcaseEditorDialog::createConnectors()
{
}

void TestcaseEditorDialog::createActions()
{

}

/*
 * Диалоговое окно редактора тест-кейса
 */
void TestcaseEditorDialog::testSequenceEditorDialog(TestSequencesEditorTreeItem *itm) {

  QTableWidgetItem *item;

  ui->nameEdit->setText(itm->name());
  ui->descriptionEdit->setText(itm->description());
  ui->pathEdit->setText(itm->path());

  // Создание виджета параметров
  ui->testcaseParamsTableWidget->setColumnCount(2);
  ui->testcaseParamsTableWidget->setRowCount(100);

  QList< QPair < QString, QString > > p = itm->params();

  for (int i = 0; i < 100; i++) {
    for (int j = 0; j < 2; j++) {
      if (i < p.size()) {
        if (j == 0) {
          item = new QTableWidgetItem(p.at(i).first);
        }
        if ( j == 1 ) {
          item = new QTableWidgetItem(p.at(i).second);
        }
      }
      else {
        item = new QTableWidgetItem("");
      }
      ui->testcaseParamsTableWidget->setItem(i,j, item);
    }
  }

  // Обработка нажатия на кнопку "Ok"
  if (exec() == QDialog::Accepted) {
    // Установка параметров тест-кейса
    itm->setName(ui->nameEdit->text());
    itm->setDescription(ui->descriptionEdit->toPlainText());
    itm->setPath(ui->pathEdit->text());
    itm->setParams(ui->testcaseParamsTableWidget);

    emit onChange();
  }
}

/*
 * Установка пути к файлу скрипта в поле пути
 */
void TestcaseEditorDialog::setScriptPath() {

  QString str;

  QString fileName = QFileDialog::getOpenFileName(this, tr("Выбрать скрипт"),
                                                  QDir::currentPath(), tr("Скрипт (*.scr)"),
                                                  0, QFileDialog::DontUseNativeDialog);

  str = QString("%1/files/scripts").arg(QDir::currentPath());
  fileName.replace(str, QString(""));

  if (!fileName.isEmpty()) {
    ui->pathEdit->setText(fileName);
  }

  return;
}

/*
 * Выбор скрипта для тест-кейса
 */
void TestcaseEditorDialog::on_browserButton_clicked()
{
  setScriptPath();
}
