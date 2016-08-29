#include "utilslibrary.h"

SysLibrary::UtilsLibrary::UtilsLibrary() {

}

/*
* Если каталог не существует, то вывести сообщение об этом
*/
bool SysLibrary::UtilsLibrary::isValidPath(QString title, QString info, QString path) {
  QDir folder;

  bool pr = folder.exists(path);

  if (!pr) {
    QMessageBox msgBox;
    msgBox.setWindowTitle(title);
    msgBox.setInformativeText(info);
    msgBox.setText("Путь некорректный");
    msgBox.exec();
  }

  return pr;
}

/*
 * Если каталог не существует, то создать его...
 */
bool SysLibrary::UtilsLibrary::checkFolder( QString path ) {
  QDir folder( path );
  if ( !folder.exists() ) {
    if ( !folder.cdUp() ) {
      QString path2 = path.left(path.lastIndexOf(QString("/")));
      if ( checkFolder( path2 ) ) {
        if ( !folder.mkdir( path ) ) {
          return false;
        }
      }
    }
    else {
      if ( !folder.mkdir( path ) ) {
        return false;
      }
    }
  }
  return true;
}

bool SysLibrary::UtilsLibrary::deleteFolder(QString path)
{
  QDir folder(path);
  if (folder.exists()) {
    return folder.removeRecursively();
  }

  return true;
}

