#include "appsettings.h"
#include <frameWork/base.h>
#include <interfaces/isessionmanager.h>
#include <frameWork/plugins.h>

AppSettings::AppSettings(QWidget *parent) :
    QWidget(parent)
{
    m_contentsWidget = new QListWidget;
    m_contentsWidget->setViewMode(QListView::IconMode);
    m_contentsWidget->setIconSize(QSize(96, 84));
    m_contentsWidget->setMovement(QListView::Static);
    m_contentsWidget->setMaximumWidth(170);
    m_contentsWidget->setSpacing(12);

    m_pagesWidget = new QStackedWidget;

    QHashIterator<QString, PluginInterface *>  i(Core::Plugins::instance().plugins());
    while (i.hasNext()) {
        i.next();
        if (i.key() == "logger") {
            m_pagesWidget->addWidget(Core::Plugins::instance().logger()->settingPage());
        }
        else if (i.key() == "boot") {
            m_pagesWidget->addWidget(Core::Plugins::instance().boot()->settingPage());
        }
        else {
            // если виджет настроек существует и плагин включен
            if ((static_cast<PluginInterface*>(i.value()))->settingPage()) {
                m_pagesWidget->addWidget((static_cast<PluginInterface*>(i.value()))->settingPage());
            }
        }
    }

    m_pagesWidget->addWidget(new OptionsForm); // основные настройки приложения

    createIcons();

    m_contentsWidget->setCurrentRow(0);

    QHBoxLayout *horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(m_contentsWidget);
    horizontalLayout->addWidget(m_pagesWidget, 1);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(horizontalLayout);
    mainLayout->setContentsMargins(1,1,1,1);
    setLayout(mainLayout);

    setContentsMargins(1,1,1,1);
    setWindowTitle(tr("Config Dialog"));

    setWindowIcon(QIcon(":/images/base/settings.png"));

}


// Функция создания иконок настроек
void AppSettings::createIcons() {

    QHashIterator<QString, PluginInterface *>  i(Core::Plugins::instance().plugins());
    while (i.hasNext()) {
        i.next();

        QListWidgetItem *pluginButton = new QListWidgetItem(m_contentsWidget);
        pluginButton->setIcon(i.value()->settingIcon());
        pluginButton->setText(i.value()->textName());
        pluginButton->setTextAlignment(Qt::AlignHCenter);
        pluginButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    }

  QListWidgetItem *optionsButton = new QListWidgetItem(m_contentsWidget);
  optionsButton->setIcon(QPixmap(":/settings/img/configure.png"));
  optionsButton->setText(tr("Опции"));
  optionsButton->setTextAlignment(Qt::AlignHCenter);
  optionsButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

  connect( m_contentsWidget,
           SIGNAL( currentItemChanged( QListWidgetItem*, QListWidgetItem* ) ),
           this, SLOT( changePage( QListWidgetItem*, QListWidgetItem* ) ) );
}


// Функция выбора страницы настроек
void AppSettings::changePage(QListWidgetItem *current,
                             QListWidgetItem *previous) {
  if (!current) {
    current = previous;
  }

  m_pagesWidget->setCurrentIndex(m_contentsWidget->row(current));
}

