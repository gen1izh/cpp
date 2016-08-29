#ifndef TESTSEQUENCE_SAVE_DIALOG_H
#define TESTSEQUENCE_SAVE_DIALOG_H

#include <QDialog>

#include <library/databasesapi/mysql/mysqldatabaseapi.h>
#include <library/loggerapi/loggerapi.h>

#include "testsequenceeditortreemodel.h"

namespace Ui {
class TestsequenceSaveDialog;
}

class TestsequenceSaveDialog : public QDialog
{
  Q_OBJECT

  void createConnectors();

  /*!
   * \brief Открыть окно ввода имени тестовой последовательности
   * для ее последующего сохранения
   */
  bool showSaveTestsequenceDialog();

  /*!
   * \brief Модель дерева тестовых последовательностей
   */
  TestSequencesEditorTreeModel *_model;

  /*!
   * \brief Название тестовой последовательности открытой для редактирования(внешнее представление)
   * Если создаем тест, то первоначально это поле будет пустым
   */
  QString *_testInternalName;

  /*!
   * \brief Название тестовой последовательности открытой для редактирования(внутреннее представление)
   * Если создаем тест, то первоначально это поле будет пустым
   */
  QString *_testExternalName;


  public:
    explicit TestsequenceSaveDialog(QWidget *parent = 0);
    ~TestsequenceSaveDialog();

    /*!
     * \brief Установка модели
     * \param[in] model - указатель на модель
     */
    void setModel(TestSequencesEditorTreeModel *model) { _model = model; }

    /*!
     * \brief Установка внешнего имени тестовой последовательности
     * \param[in] name - присваиваем внутренне имя
     */
    void setTestsequenceExternalName(QString *name) { _testExternalName = name; }

    /*!
     * \brief Установка внутреннего имени тестовой последовательности
     * \param[in] name - присваиваем внешнее имя
     */
    void setTestsequenceInternalName(QString *name) { _testInternalName = name; }


  public slots:
    /*!
     * \brief Сохранение тестовой структуры
     */
    void saveTestsequenceStructure();

  private:
    Ui::TestsequenceSaveDialog *ui;

  signals:
    /*!
     * \brief Обновление списка тестовых последовательностей
     */
    void updateTestsList();
};

#endif // TESTSEQUENCE_SAVE_DIALOG_H
