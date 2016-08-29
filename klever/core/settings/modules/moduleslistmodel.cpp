#include "moduleslistmodel.h"

/*
 * Конструктор модели списка модулей
 */
ModulesListModel::ModulesListModel(QWidget *parent)
{
  Q_UNUSED(parent)

  AppSetupApi appsetup;

  QDir pluginsDir(QCoreApplication::applicationDirPath());
  pluginsDir.cd("modules");

  pluginsDir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);

  QStringList filters;
  filters << "*.dll";
  pluginsDir.setNameFilters(filters);

  pluginsDir.setSorting(QDir::Size | QDir::Reversed);

  QFileInfoList list = pluginsDir.entryInfoList();

  for (int i = 0; i < list.size(); i++){
    if ( list.at(i).fileName() == "formsManager.dll" ) {
      list.removeAt(i);
    }
  }

  QStringList pluginsList;

  bool loadPluginsProceed = true;

  int i = 0;
  while (loadPluginsProceed) {
    QString st;
    st.clear();
    st = appsetup.getApplicationParam(QString("Main"),
                                      QString("/module%1").arg(i));
    pluginsList << st;
    if ( i>40 ) {
      loadPluginsProceed = false;
    }
    i++;
  }

  for (int i = 0; i < list.size(); ++i) {
      QFileInfo fileInfo = list.at(i);
      _modulesStringList << fileInfo.fileName();

      for ( int j = 0; j < pluginsList.size(); j++ ) {
        if ( pluginsList.at(j) == fileInfo.fileName()) {
          _isChecked[fileInfo.fileName()] = true;
          break;
        }
        else {
          _isChecked[fileInfo.fileName()] = false;
        }
      }

  }

  setStringList( _modulesStringList );
}

/*
 * Обработчик данных
 */
QVariant ModulesListModel::data(const QModelIndex &index, int role) const
{
  QString currentText;

  currentText = (QString)_modulesStringList.at(index.row());

  if ( !index.isValid() ) {
    return QVariant();
  }

  if ( (role == Qt::CheckStateRole) && (index.column() == 0) ) {
    QString txt = (QString)(_modulesStringList.at(index.row()));
      return static_cast<int>( ( (bool) _isChecked[txt] )
          ? Qt::Checked
          : Qt::Unchecked);
  }

  if ( role == Qt::DisplayRole ) {
    return currentText;
  }

  if (role == Qt::BackgroundColorRole){
    for ( int i = 0; i < bugModules.size(); i++) {
      if (currentText == bugModules.at(i)) {
        return QColor(Qt::red);
      }
    }
    if (index.row() & 1)
      return QColor(Qt::white);
    else
      return QColor(240,240,240);
  }

  return QVariant();
}

/*
 * Флаги
 */
Qt::ItemFlags ModulesListModel::flags(const QModelIndex &index) const
{
  Qt::ItemFlags theFlags = QStringListModel::flags(index);
  if (index.isValid()) {
    theFlags |= Qt::ItemIsSelectable | Qt::ItemIsEnabled;
    if (index.column() == 0) {
      theFlags |= Qt::ItemIsUserCheckable | Qt::ItemIsSelectable |
                  Qt::ItemIsEnabled;
      theFlags &= ~(Qt::ItemIsEditable);
    }
  }
  return theFlags;
}


/*
 * Установка данных в модель
 */
bool ModulesListModel::setData( const QModelIndex &index,
                                const QVariant &value,
                                int role) {
  AppSetupApi  appsetup;

  if ( !index.isValid() ) {
    return false;
  }

  if ( role == Qt::CheckStateRole ) {
    QString moduleNameText = (QString)(_modulesStringList.at(index.row()));
    _isChecked[moduleNameText] = value.toBool();
    appsetup.setApplicationParam(QString("Main"),
                                 QString("/module%1").arg(index.row()),
                                 moduleNameText);

    appsetup.setApplicationParam(QString("Main"),
                                 QString("/moduleCount%1").arg( index.row()),
                                 QString("1") );
    if (!_isChecked[moduleNameText]) {
      appsetup.removeParamsByKey( QString( "/module%1" ) .arg( index.row() ) );
      appsetup.removeParamsByKey( QString( "/moduleCount%1" ) .arg( index.row() ) );
    }
    return true;
  }
  else {
    return false;
  }

  return false;
}


