#ifndef TESTCASE_EDITOR_DIALOG_H
#define TESTCASE_EDITOR_DIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QDir>

#include "testsequenceeditortreeitem.h"
#include "testsequenceeditortreemodel.h"

namespace Ui {
class TestcaseEditorDialog;
}

class TestcaseEditorDialog : public QDialog
{
  Q_OBJECT

  void createConnectors();

  void createActions();

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
   * \brief Модель дерева тестовых последовательностей
   */
  TestSequencesEditorTreeModel   *_model;

  public:
    explicit TestcaseEditorDialog(QWidget *parent = 0);
    ~TestcaseEditorDialog();

    /*!
     * \brief Установка модели тестовой последовательности
     * \param[in] model - указатель на модель
     */
    void setModel(TestSequencesEditorTreeModel *model) { _model = model; }

    /*!
     * \brief Установка внешнего имени тестовой последовательности
     * \param[in] name - название
     */
    void setTestsequenceExternalName(QString *name) { _testExternalName = name; }

    /*!
     * \brief Установка внутреннего имени тестовой последовательности
     * \param[in] name - название
     */
    void setTestsequenceInternalName(QString *name) { _testInternalName = name; }

    /*!
     * \brief Открытие диалогового окна для реадктирования тест-кейса
     * \param[in] itm - элемент дерева тестовой последовательности
     */
    void testSequenceEditorDialog(TestSequencesEditorTreeItem *itm);

  public slots:
    /*!
     * \brief Установка пути к файлу скрипта в поле пути
     */
    void setScriptPath();

  private:
    Ui::TestcaseEditorDialog *ui;

  signals:
    /*!
     * \brief Сигнал изменения тест-кейса
     */
    void onChange();

  private slots:

    /*!
     * \brief Выбор скрипта для тест-кейса
     */
    void on_browserButton_clicked();
};

#endif // TESTCASE_EDITOR_DIALOG_H
