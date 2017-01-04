#include "appsettings.h"

/* Глобальные данные */
#include <frameWork/base.h>
#include <interfaces/isessionmanager.h>

#include <frameWork/plugins.h>

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

    QHashIterator<QString, PluginInterface *>  i(Core::Plugins::instance().plugins());
    while (i.hasNext()) {
      i.next();
      // если менеджер включен
      if (i.value()->isOn()) {

        if (i.key() == "logger") {
          _pagesWidget->addWidget(Core::Plugins::instance().logger()->getSettingPage());
        }
        else if (i.key() == "boot") {
          _pagesWidget->addWidget(Core::Plugins::instance().boot()->getSettingPage());
        }
        else {
          // если виджет настроек существует и плагин включен
          if (((static_cast<PluginInterface*>(i.value()))->getSettingPage()) && (i.value()->isOn())) {
            _pagesWidget->addWidget((static_cast<PluginInterface*>(i.value()))->getSettingPage());
          }
        }
      }
    }

    _pagesWidget->addWidget(new OptionsForm); /* основные настройки приложения */

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

    setWindowIcon(QIcon(":/images/base/settings.png"));

}

/*
 * Функция создания иконок на менюшку настроек
 */
void AppSettings::createIcons() {

    QHashIterator<QString, PluginInterface *>  i(Core::Plugins::instance().plugins());
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

  QListWidgetItem *optionsButton = new QListWidgetItem(_contentsWidget);
  optionsButton->setIcon(QPixmap(":/settings/img/configure.png"));
  optionsButton->setText(tr("Опции"));
  optionsButton->setTextAlignment(Qt::AlignHCenter);
  optionsButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

  connect( _contentsWidget,
           SIGNAL( currentItemChanged( QListWidgetItem*, QListWidgetItem* ) ),
           this, SLOT( changePage( QListWidgetItem*, QListWidgetItem* ) ) );
}

/*
 * Функция выбора страницы настроек
 */
void AppSettings::changePage(QListWidgetItem *current,
                             QListWidgetItem *previous) {
  if (!current) {
    current = previous;
  }

  _pagesWidget->setCurrentIndex(_contentsWidget->row(current));
}

