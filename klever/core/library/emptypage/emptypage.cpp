#include "emptypage.h"

#include <QLabel>
#include <QVBoxLayout>


EmptyPage::EmptyPage(QWidget *parent, QString txt)
    : QWidget(parent) {
  QLabel *lbl = new QLabel(txt);
  QVBoxLayout *mainLayout = new QVBoxLayout;

  mainLayout->setAlignment(Qt::AlignHCenter);
  mainLayout->addWidget(lbl);
  setLayout(mainLayout);
}

