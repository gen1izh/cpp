#include "appsettings.h"

/* Глобальные данные */
#include <frameWork/base.h>
#include <interfaces/isession.h>


#include <frameWork/cveManager.h>

using namespace Core;


AppSettings::AppSettings(QWidget *parent) :
    QWidget(parent)
{
  _contentsWidget = new QListWidget;
  _contentsWidget->setViewMode(QListView::IconMode);
  _contentsWidget->setIconSize(QSize(96, 84));
  _contentsWidget->setMovement(QListView::Static);
  _contentsWidget->setMaximumWidth(170);
  _contentsWidget->setSpacing(12);

  _pagesWidget = new QStackedWidget;

  // TODO: Необходимо продумать менеджер прав доступа
  if (CveManager::instance().boot()->hasRightUser(CAN_SEE_MANAGERS_SETTINGS)) {
    QHashIterator<QString, ManagerInterface *>  i(CveManager::instance().managers());
    while (i.hasNext()) {
      i.next();
      // если менеджер включен
      if (i.value()->isOn()) {

        if (i.key() == "logger") {
          _pagesWidget->addWidget(CveManager::instance().logger()->getSettingPage());
        }
        else if (i.key() == "boot") {
          _pagesWidget->addWidget(CveManager::instance().boot()->getSettingPage());
        }
        else {
          // если виджет настроек существует и менеджер включен
          if (((static_cast<ManagerInterface*>(i.value()))->getSettingPage()) && (i.value()->isOn())) {
            _pagesWidget->addWidget((static_cast<ManagerInterface*>(i.value()))->getSettingPage());
          }
        }
      }
    }

    _pagesWidget->addWidget(new OptionsPage); /* основные настройки приложения */
    _pagesWidget->addWidget(new ModulesPage); /* модули */
  }

  createIcons();

  _contentsWidget->setCurrentRow(0);

  QHBoxLayout *horizontalLayout = new QHBoxLayout;
  horizontalLayout->addWidget(_contentsWidget);
  horizontalLayout->addWidget(_pagesWidget, 1);

  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addLayout(horizontalLayout);
  mainLayout->setContentsMargins(1,1,1,1);
  setLayout(mainLayout);

  setContentsMargins(1,1,1,1);
  setWindowTitle(tr("Config Dialog"));

  setWindowIcon(QIcon(":/settings/img/settings.png"));

}

/*
 * Функция создания иконок на менюшку настроек
 */
void AppSettings::createIcons() {

  // TODO: Необходимо продумать менеджер прав доступа
  if (CveManager::instance().boot()->hasRightUser(CAN_SEE_MANAGERS_SETTINGS)) {

    QHashIterator<QString, ManagerInterface *>  i(CveManager::instance().managers());
    while (i.hasNext()) {
      i.next();

      // если менеджер включен
      if (i.value()->isOn()) {
        QListWidgetItem *managerButton = new QListWidgetItem(_contentsWidget);
        managerButton->setIcon(i.value()->settingIcon());
        managerButton->setText(i.value()->textName());
        managerButton->setTextAlignment(Qt::AlignHCenter);
        managerButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
      }
    }

  }

  QListWidgetItem *optionsButton = new QListWidgetItem(_contentsWidget);
  optionsButton->setIcon(QPixmap(":/settings/img/configure.png"));
  optionsButton->setText(tr("Опции"));
  optionsButton->setTextAlignment(Qt::AlignHCenter);
  optionsButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

  // TODO: В случае отсутсвия модулей эту вкладку не надо отображать
  QListWidgetItem *devicesButton = new QListWidgetItem(_contentsWidget);
  devicesButton->setIcon(QPixmap(":/settings/img/devices.png"));
  devicesButton->setText(tr("Модули"));
  devicesButton->setTextAlignment(Qt::AlignHCenter);
  devicesButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

  connect( _contentsWidget,
           SIGNAL( currentItemChanged( QListWidgetItem*, QListWidgetItem* ) ),
           this, SLOT( changePage( QListWidgetItem*, QListWidgetItem* ) ) );
}

/*
 * Функция выбора страницы настроек
 */
void AppSettings::changePage(QListWidgetItem *current,
                             QListWidgetItem *previous) {
  if ( !current ) {
    current = previous;
  }

  _pagesWidget->setCurrentIndex( _contentsWidget->row( current ) );
}

