#include "testsequencesavedialog.h"
#include "ui_testsequencesavedialog.h"

using namespace Library::LoggerApi;
//using namespace TestsequenceData;


TestsequenceSaveDialog::TestsequenceSaveDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::TestsequenceSaveDialog)
{
  ui->setupUi(this);

  // Установка флагов для диалогового окна
  setWindowFlags( Qt::Window
                | Qt::MSWindowsFixedSizeDialogHint
                | Qt::WindowCloseButtonHint);
}

TestsequenceSaveDialog::~TestsequenceSaveDialog()
{
  delete ui;
}

void TestsequenceSaveDialog::createConnectors(){}

/*
 * Открыть окно ввода имени тестовой последовательности
 * для ее последующего сохранения
 */
bool TestsequenceSaveDialog::showSaveTestsequenceDialog() {
  // Обработка нажатия на кнопку Ok
  if (exec() == QDialog::Accepted) {

    // TODO: добавить запись в таблицу testcases
    if (!MySQLDataBaseApi::instance().insertIntoTable("cve_testsequence", "testsequence_gui", QString("testcases"),
         QString("(NULL,'%1','%2')").arg(ui->_testInternalEdit->text()).arg(ui->_testExternalEdit->text()), "testsequencelist" )) {

      logWarning(this,QString("Не удалось создать тестовую последовательность!"));

    }
    *_testInternalName = ui->_testInternalEdit->text();
    *_testExternalName = ui->_testExternalEdit->text();
    return true;
  }
  else {
    return false;
  }
}


/*
 * Сохранение тестовой последовательности
 */
void TestsequenceSaveDialog::saveTestsequenceStructure() {

  // Проверяем создали новую тестовую последовательность
  // или открыли существующую тестовую последовательность
  if (_testInternalName->isEmpty()) {
    showSaveTestsequenceDialog();
    // Если создали тестовую последовательнсть, то вызываем
    // диалоговое окно для ввода названия.
    // Это название
    return saveTestsequenceStructure();
  }
  else {
    _model->save();
  }

  emit updateTestsList();
}

/*
 * Сохранение тестовой последовательности
 */
//bool TestsequenceSaveDialog::fileSaveAs() {
//  if (!_model->filename().isEmpty()) {
//    QMessageBox msgBox;
//    msgBox.setText("Создание новой тестовой последовательности");
//    msgBox.setIcon(QMessageBox::Question);
//    msgBox.setInformativeText("Вы действиельно хотите сохранить как "\
//                              "новую тестовую последовательность?");
//    msgBox.setStandardButtons( QMessageBox::Ok | QMessageBox::Cancel);
//    msgBox.setDefaultButton( QMessageBox::Cancel );
//    int ret = msgBox.exec();

//    switch ( ret ) {
//      case QMessageBox::Ok:
//        model->showSaveTestsequenceDialog();
//        break;
//      case QMessageBox::Cancel:
//          // Cancel was clicked
//        break;
//      default:
//          // should never be reached
//        break;
//    }
//  }

//  return saveTestsequenceStructure();
//}


