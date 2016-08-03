#include "view.h"
#include "ui_view.h"
#include "ackextractor.h"
#include "threadsmodule.h"
#include <QSortFilterProxyModel>
#include <QTimer>


view::view(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::view)
{
    ui->setupUi(this);


}

view::~view()
{
    delete ui;
}


