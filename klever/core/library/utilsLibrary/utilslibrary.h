#ifndef UTILSLIBRARY_H
#define UTILSLIBRARY_H

#include <QString>
#include <QDir>
#include <QMessageBox>
#include <QApplication>
#include <QDebug>

#include <QGridLayout>
#include <QProgressBar>

namespace SysLibrary {

  class UtilsLibrary {
    public:
      UtilsLibrary();
      bool isValidPath(QString title, QString info, QString path);
      bool checkFolder(QString path);
      bool deleteFolder(QString path);

      /*
       *  TODO не нашел ничего подобного
       */
      int unicValue(QString txt) {
        int sum;
        const char *j;
        j = txt.toStdString().c_str();
        for (int i=0; i<txt.size();i++){
          char ch = j[i];
          sum+=ch;
        }
        return sum;
      }

  };


template<typename T>
bool okToClearData(bool (T::*saveData)(), T *parent,
        const QString &title, const QString &text,
        const QString &detailedText=QString())
{
    Q_ASSERT(saveData && parent);
    QScopedPointer<QMessageBox> messageBox(new QMessageBox(parent));
    messageBox->setWindowModality(Qt::WindowModal);
    messageBox->setIcon(QMessageBox::Question);
    messageBox->setWindowTitle(QString("%1 - %2")
            .arg(QApplication::applicationName()).arg(title));
    messageBox->setText(text);
    if (!detailedText.isEmpty())
        messageBox->setInformativeText(detailedText);
    messageBox->addButton(QMessageBox::Save);
    messageBox->addButton(QMessageBox::Discard);
    messageBox->addButton(QMessageBox::Cancel);
    messageBox->setDefaultButton(QMessageBox::Save);
    messageBox->exec();
    if (messageBox->clickedButton() ==
        messageBox->button(QMessageBox::Cancel))
        return false;
    if (messageBox->clickedButton() ==
        messageBox->button(QMessageBox::Save))
        return (parent->*saveData)();
    return true;
}

}
#endif // UTILSLIBRARY_H
