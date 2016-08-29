#include "customfilterdialog.h"

/**************************************************************************
 *              Реализация диалогового окна фильтрации сообщений
 **************************************************************************/

/*
 * Инициализация окна фильтра сообщений
 */
CustomFilterDialog::CustomFilterDialog(QWidget *parent) :
   QDialog(parent) {

  setWindowFlags( Qt::Window
                  | Qt::MSWindowsFixedSizeDialogHint
                  | Qt::WindowCloseButtonHint );

  QGridLayout* grid = new QGridLayout;

  tableView = new QTableView;

  grid->setSizeConstraint( QLayout::SetMinAndMaxSize );

  /* Создание  верхней части элементов */
  selectAllButton = new QPushButton( "Выделить все" );
  grid->addWidget( selectAllButton, 0, 0 );
  deselectAllButton = new QPushButton( "Снять все" );
  grid->addWidget( deselectAllButton, 0, 1 );
  QVBoxLayout* msgTypeLayout = new QVBoxLayout;
  msgTypeComboBox = new QComboBox();
  QStringList msgTypes;
  msgTypes.append( "все" );
  msgTypes.append( "[error]" );
  msgTypes.append( "[info]" );
  msgTypes.append( "[warning]" );
  msgTypeComboBox->addItems( msgTypes );
  msgTypeLayout->addWidget( msgTypeComboBox );
  QGroupBox *gbx = new QGroupBox();
  gbx->setTitle( " Оставить сообщения по типу: " );
  gbx->setLayout( msgTypeLayout );
  grid->addWidget( gbx, 0, 3 );

  /* Создание средней части элементов */
  _model         = new CustomFilterTableModel( this );
  _itemDelegate = new CustomFilterItemDelegate( this );

  tableView->setItemDelegate( _itemDelegate );
  tableView->setModel( _model );
  tableView->verticalHeader()->setDefaultSectionSize( 16 );
  tableView->horizontalHeader()->setSectionResizeMode( QHeaderView::ResizeToContents );
  tableView->horizontalHeader()->setStretchLastSection( true );

  grid->addWidget( tableView, 1, 0, 1, 4 );

  /* Создание нижней части элементов */
  byDateFilterEnableCheckBox = new QCheckBox( "С учетом даты и времени" );
  grid->addWidget( byDateFilterEnableCheckBox, 2, 0, 1, 1 );

  QHBoxLayout* dateLayout = new QHBoxLayout;

  gbx2 = new QGroupBox();
  gbx2->setTitle( "Временной диапазон" );
  gbx2->setEnabled( false );

  startDatePointLabel     = new QLabel( "от" );
  stopDatePointLabel      = new QLabel( "до" );
  startDatePointLineEdit  = new QDateTimeEdit();
  stopDatePointLineEdit   = new QDateTimeEdit();

  startDatePointLineEdit->setDisplayFormat( "dd.MM.yyyy hh:mm:ss.zzz" );
  stopDatePointLineEdit->setDisplayFormat( "dd.MM.yyyy hh:mm:ss.zzz" );

  dateLayout->addWidget(startDatePointLabel);
  dateLayout->addWidget(startDatePointLineEdit);
  dateLayout->addWidget(stopDatePointLabel);
  dateLayout->addWidget(stopDatePointLineEdit);

  gbx2->setLayout( dateLayout );
  grid->addWidget( gbx2, 3, 0, 1, 4 );

  okButton = new QPushButton( "Начать фильтрацию" );
  grid->addWidget( okButton, 4, 0 );
  closeButton = new QPushButton( "Закрыть" );
  grid->addWidget( closeButton, 4, 3 );


  setWindowTitle( tr("Фильтр сообщений") );
  setLayout( grid );

  QObject::connect( okButton, SIGNAL( clicked() ), this, SLOT( accept() ) );
  QObject::connect( closeButton, SIGNAL( clicked() ), this, SLOT( reject() ) );

  QObject::connect( selectAllButton, SIGNAL(clicked()),_model,SLOT(selectAll()));
  QObject::connect( deselectAllButton, SIGNAL(clicked()),_model,SLOT(deselectAll()));

  QObject::connect( byDateFilterEnableCheckBox,
                   SIGNAL( toggled(bool) ),
                   gbx2,
                   SLOT( setEnabled(bool) ) );

}

/*
 * Удаление модели и делегата
 */
CustomFilterDialog::~CustomFilterDialog() {
 delete _model;
 delete _itemDelegate;
}

/*
 * Установка фильтра данных
 */
bool CustomFilterDialog::setSourcesMap( MessagesSourcesMap *filter ) {

 /* Создание временного фильтра */
 MessagesSourcesMap *a_filter = new MessagesSourcesMap();

 /* Перезаписали все значения фильтра filter во временный */
 for ( int i = 0; i < filter->count(); i++ ) {
   a_filter->insert( filter->keys().at(i), filter->values().at(i)  );
 }

 /* Присвоения указателя на фильтр */
 /* То есть при нажатии на чекбоксы будет меняться model->filter
    а для того чтобы получить доступ к этому фильтру производится таким образом
    присвоение указателя */
 _model->filter = filter;
 _model->update();

 bool res = ( exec() == QDialog::Accepted );

 /* Обработка нажатия кнопки Отмены */
 if ( !res ) {
   filter->clear();
   for ( int i = 0; i < a_filter->count(); i++ ) {
     filter->insert( a_filter->keys().at( i ), a_filter->values().at( i ) );
   }
 }

 delete a_filter;

 return res;
}

