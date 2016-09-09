#include "rightslistmodel.h"
#include <frameWork/cveManager.h>
#include "frameWork/base.h"

RightsListModel::RightsListModel(QWidget *parent)
{
  Q_UNUSED(parent)

  QString rights = Core::Base::instance().getParameterValue(QString("/rights"),QString());

  QHashIterator<int, QPair<bool,QString> > i(Core::CveManager::instance().boot()->rightsByRole(rights));
  while (i.hasNext()) {
    i.next();
    _rightsStringList << i.value().second;
  }

  setStringList(_rightsStringList);

}


/*
 * Обработчик данных
 */
QVariant RightsListModel::data(const QModelIndex &index, int role) const {
  QString currentText;

  currentText = (QString)_rightsStringList.at(index.row());

  if ( !index.isValid() ) {
    return QVariant();
  }

  if ( (role == Qt::CheckStateRole) && (index.column() == 0) ) {
    QString txt = (QString)(_rightsStringList.at(index.row()));
    QHashIterator<int, QPair<bool,QString> > i(Core::CveManager::instance().boot()->rightsByRole(_role));
    while (i.hasNext()) {
      i.next();
      if (i.value().second == txt) {
        return static_cast<int>(((bool)i.value().first)
            ? Qt::Checked
            : Qt::Unchecked);
      }
    }
  }

  if ( role == Qt::DisplayRole ) {
    return currentText;
  }

  if (role == Qt::BackgroundColorRole) {
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
Qt::ItemFlags RightsListModel::flags(const QModelIndex &index) const
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
bool RightsListModel::setData( const QModelIndex &index,
                                const QVariant &value,
                                int role) {

  if ( !index.isValid() ) {
    return false;
  }

  if ( role == Qt::CheckStateRole ) {

    QHashIterator<int, QPair<bool,QString> > i(Core::CveManager::instance().boot()->rightsByRole(_role));
    while (i.hasNext()) {
      i.next();
      if (_rightsStringList.at(index.row()) == i.value().second) {
        Core::CveManager::instance().boot()->setRight(_role, i.key(),value.toBool());
      }

    }

    return true;
  }

  return false;
}


