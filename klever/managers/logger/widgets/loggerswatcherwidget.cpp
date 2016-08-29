#include "loggerswatcherwidget.h"


LoggersWatcherWidget::LoggersWatcherWidget(QWidget *parent, LoggersTabsWidgets *lo) : QWidget(parent)
{
  _prevButton       = new QPushButton("Предыдущая страница");
  _nextButton       = new QPushButton("Следующая страница");
  _pageNumberEdit   = new QLineEdit();
  _pagesCountLabel  = new QLabel();
  _pagesCountLabel->setText("Всего страниц: ");
  _pageNumberEdit->setText("0");

  _ltw = static_cast<LoggersTabsWidgets *>(lo);

  _ltw->loggers()->insert(1000/*"watch"*/,new Logger( NULL, NULL, "", true, true, true ));
  _ltw->loggers()->value(1000/*"watch"*/)->setObjectName("watcher");

  // Инициализация сетки расположения графических компонентов
  QGridLayout *grid = new QGridLayout();
  grid->setSizeConstraint(QLayout::SetDefaultConstraint);

  grid->addWidget( _ltw->loggers()->value(1000/*"watch"*/)->logViewer, 0, 0, 1, 4 );
  grid->addWidget( _prevButton, 1, 0, 1, 1  );
  grid->addWidget( _pagesCountLabel, 1, 1, 1, 1  );
  grid->addWidget( _pageNumberEdit, 1, 2, 1, 1  );
  grid->addWidget( _nextButton, 1, 3, 1, 1  );

  QObject::connect( _prevButton, SIGNAL( clicked() ),
                    this, SLOT( prevButtonHandler() ) );

  QObject::connect( _nextButton, SIGNAL( clicked() ),
                    this, SLOT( nextButtonHandler() ) );

  QObject::connect( _ltw->loggers()->value(1000/*"watch"*/)->logTableModel,
                    SIGNAL( setPageCountsAndCurrentPageSignal(int,int) ),
                    this, SLOT(setPageCountsAndCurrentPage(int,int)) );

  /* Добавление сетки на слой виджета */
  setLayout(grid);
  setWindowTitle("Просмотрщик журналов");
  setMinimumSize(600,400);

  setWindowIcon(_ltw->loggers()->value(1000/*"watch"*/)->logViewer->windowIcon());
}


/*
 *
 */
void LoggersWatcherWidget::prevButtonHandler()
{
  bool ok;
  int count;
  int page = _pageNumberEdit->text().toInt(&ok,10);
  page--;

  int i = _ltw->loggers()->value(1000/*"watch"*/)->logTableModel->openOnePageOfReport(page, &count);

  setPageCountsAndCurrentPage(i,count);
}


/*
 *
 */
void LoggersWatcherWidget::setPageCountsAndCurrentPage( int i, int count )
{
  _pageNumberEdit->setText(QString("%1").arg(i));
  _pagesCountLabel->setText( QString("Всего страниц: %1").arg(count) );
}

/*
 *
 */
void LoggersWatcherWidget::nextButtonHandler()
{
  bool ok;
  int count;

  int page = _pageNumberEdit->text().toInt(&ok,10);
  page++;

  int i = _ltw->loggers()->value(1000/*"watch"*/)->logTableModel->openOnePageOfReport(page, &count);

  setPageCountsAndCurrentPage(i,count);
}
