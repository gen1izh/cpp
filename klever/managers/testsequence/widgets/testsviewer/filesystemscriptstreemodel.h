#ifndef FILE_SYSTEM_SCRIPTS_TREE_MODEL_H
#define FILE_SYSTEM_SCRIPTS_TREE_MODEL_H

#include <QFileSystemModel>

class FileSystemScriptsTreeModel : public QFileSystemModel {

  public:

  FileSystemScriptsTreeModel(){}

    // Руссифицируем headerData дерева скриптов
    QVariant headerData(int section,
            Qt::Orientation orientation, int role) const {
      if ( orientation == Qt::Horizontal && role == Qt::DisplayRole ) {


        if (section == 0) {
          return tr("Название");
        }
        else if (section == 1) {
          return tr("Размер");
        }
        else if (section == 2) {
          return tr("Тип");
        }
        else if (section == 3) {
          return tr("Изменения");
        }
      }
      return QVariant();
    }

};

#endif // FILE_SYSTEM_SCRIPTS_TREE_MODEL_H
