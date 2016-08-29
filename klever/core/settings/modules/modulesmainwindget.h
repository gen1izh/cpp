#ifndef MODULESMAINWINDGET_H
#define MODULESMAINWINDGET_H

#include <QWidget>
#include <QDialog>
#include <QListWidget>
#include <QPushButton>
#include <QToolBox>
#include <QListView>
#include <QLabel>
#include <QComboBox>
#include <QTextEdit>
#include <QCheckBox>

#include "moduleslistmodel.h"

#include <library/setupApi/app.h>

/*!
 * \brief The ModulesMainWindget class
 */
class ModulesMainWindget : public QWidget
{
  Q_OBJECT
public:
  explicit ModulesMainWindget(QWidget *parent = 0);
  ~ModulesMainWindget(){}

  QListWidget *_modulesInformationList;
  QPushButton *moreButton;

  // Элементы для QDialog
  QToolBox *infoAndChangeLogTab;

  QTextEdit *informationTextEdit;
  QTextEdit *changeLogTextEdit;

  QDialog dlg;

  QListView        *_modulesList;


  QLabel        *_modFormsNamesLabel;
  QComboBox     *_modFormsNamesCombo;

  QLabel        *_debugModeLabel;
  QCheckBox     *_debugModeCheckBox;
  QLabel        *_modulesListLabel;

  void setModulesInformationList(QStringList lst);

  void setInfoAndChangeLog(QString info, QString changelog);
public slots:
    void openDialog();

signals:
    void openModulesInformationDialog(QString name, int row);
};

#endif // MODULESMAINWINDGET_H
