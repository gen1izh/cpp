#include "optimemanager.h"
#include <library/loggerapi/loggerapi.h>

using namespace Library::Logger;

OptimeManager::OptimeManager() {
  setName("/optime");           // Установка имени модуля (внутреннее)
  setTextName("Наработка");     // Установка имени модуля (внешнее)
  setObjectName("Наработка");
  checkManagerState();          // Проверка состояния менеджера (вкл. или выкл.)
  _settings = NULL;
  createWidgets();

  _cveOperationTime = new QTime();
  _cveOperationTimer = new QTimer();
  _cveOperationTimer->setInterval(120000);
  _cveOperationTimer->start();

  _productOperationTime = new QTime();
  _productOperationTimer = new QTimer();
  _productOperationTimer->setInterval(50000);
  _productOperationTimer->start();

  _pollingOptimesFlagsTimer = new QTimer();
  _pollingOptimesFlagsTimer->setInterval(2000);
  _pollingOptimesFlagsTimer->start();

  _cveOperationTimeAccumulateFlag = false;
  _productOperationTimeAccumulateFlag = false;

  Cve::instance().setParameterValue(QString("/isCveOperationTimeAccumulated"), false);
  Cve::instance().setParameterValue(QString("/isProductOperationTimeAccumulated"), false);

  QTimer::singleShot(10000, this, SLOT(readCveAndProductOperationTime()));

}

void OptimeManager::createConnectors()
{
  connect(_cveOperationTimer, SIGNAL(timeout()), this, SLOT(cveOperationTimerTick()));
  connect(_productOperationTimer, SIGNAL(timeout()), this, SLOT(productOperationTimerTick()));
  connect(_pollingOptimesFlagsTimer, SIGNAL(timeout()), this, SLOT(pollingOptimesFlagsTimerTick()));


  connect(_settings, SIGNAL(clearCveOperationTimeSignal()), this, SLOT(readCveAndProductOperationTime()));
  connect(_settings, SIGNAL(clearProductOperationTimeSignal()), this, SLOT(readCveAndProductOperationTime()));
}

void OptimeManager::pollingOptimesFlagsTimerTick() {

  int isCveOperationTimeAccumulated =
      Cve::instance().getParameterValue(QString("/isCveOperationTimeAccumulated"), false);

  int isProductOperationTimeAccumulated =
      Cve::instance().getParameterValue(QString("/isProductOperationTimeAccumulated"), false);

  if (_cveOperationTimeAccumulateFlag != isCveOperationTimeAccumulated) {
    _cveOperationTimeAccumulateFlag = isCveOperationTimeAccumulated;
    if (isCveOperationTimeAccumulated) {
      _cveOperationTime->restart();
    }
  }

  if (_productOperationTimeAccumulateFlag != isProductOperationTimeAccumulated) {
    _productOperationTimeAccumulateFlag = isProductOperationTimeAccumulated;
    if (isProductOperationTimeAccumulated) {
      _productOperationTime->restart();
    }
  }

}

void OptimeManager::cveOperationTimerTick()
{
  if (_cveOperationTimeAccumulateFlag) {

    int accumulatedTime = Cve::instance().getParameterValue(QString("/cveOperationTime"), 0);

    qDebug() << "cveOperationTime" << accumulatedTime;

    accumulatedTime += _cveOperationTime->elapsed()/1000;

    qDebug() << "accumulatedTime" << accumulatedTime;

    Cve::instance().setParameterValue(QString("/cveOperationTime"), accumulatedTime);

    writeCveAndProductOperationTime();
  }

}

void OptimeManager::productOperationTimerTick()
{
  if (_productOperationTimeAccumulateFlag) {

    int accumulatedTime = Cve::instance().getParameterValue(QString("/productOperationTime"), 0);

    accumulatedTime += _productOperationTime->elapsed()/1000;

    Cve::instance().setParameterValue(QString("/productOperationTime"), accumulatedTime);

    writeCveAndProductOperationTime();
  }
}

/*
 * Создание виджетов модуля
 */
void OptimeManager::createWidgets() {

  // Необходимо добавить остальные виджеты

  // Создание виджета настроек
  if (_settings==NULL) {
    _settings = new OptimeSettings(NULL);
  }

}

/*
 * Деинициализация элементов менеджера
 */
void OptimeManager::finalize() {

}


/*
 * Возвращает виджет настроек менеджера
 */
QWidget *OptimeManager::getSettingPage() {
  QWidget* wgt=static_cast<QWidget *>(_settings);
  return wgt;
}

/*
 *  Возвращает иконку для настроек
 */
QIcon OptimeManager::settingIcon() {
  return QIcon(":/optimemanager/img/manager.png");
}

/*
 * Запись значения времени наработки
 */
void OptimeManager::writeCveAndProductOperationTime() {
  QSettings settings("Irz", "OptimeManager");
  // Актуализация значения времени наработки КПА
  int cveOperationTime = Cve::instance().getParameterValue(QString("/cveOperationTime"), 0);

  // Актуализация значения времени наработки Изделия
  int productOperationTime = Cve::instance().getParameterValue(QString("/productOperationTime"), 0);

  qDebug() << "writeCveAndProductOperationTime " << " cveOperationTime = " << cveOperationTime;

  int days = ( ( ( ( cveOperationTime ) / 60 ) / 60 ) / 24 );
  int hour = ( ( ( ( cveOperationTime ) / 60 ) / 60 ) % 24 );
  int min  = ( ( ( cveOperationTime ) / 60 ) ) % 60 ;
  int sec  = ( cveOperationTime ) % 60;

  QString cveTime = QString("%1 дней %2 часов %3 минут %4 секунд")
                .arg(days)
                .arg(hour)
                .arg(min,  2, 10, QChar('0'))
                .arg(sec,  2, 10, QChar('0'));

  days = ( ( ( ( productOperationTime ) / 60 ) / 60 ) / 24 );
  hour = ( ( ( ( productOperationTime ) / 60 ) / 60 ) % 24 );
  min  = ( ( ( productOperationTime ) / 60 ) ) % 60 ;
  sec  = ( productOperationTime ) % 60;

  QString productTime = QString("%1 дней %2 часов %3 минут %4 секунд")
                .arg(days)
                .arg(hour)
                .arg(min,  2, 10, QChar('0'))
                .arg(sec,  2, 10, QChar('0'));

  logInfo(this, QString("Время наработки КПА = %1 ").arg(cveTime));
  logInfo(this, QString("Время наработки изделия = %2").arg(productTime));

  settings.beginGroup("operation_time");
  settings.setValue("cve", cveOperationTime);
  settings.setValue(QString("product_%1").arg(Cve::instance().getParameterValue(QString("/serialNumber"),
                                                                                QString("000000"))),
                                                                                productOperationTime);
  settings.endGroup();
}


/*
 * Чтение значения времени наработки из реестра
 */
void OptimeManager::readCveAndProductOperationTime() {

  QSettings settings("Irz", "OptimeManager");

  bool ok;

  settings.beginGroup("operation_time");

  int cveOperationTime = settings.value("cve", 0).toInt(&ok);

  // Актуализация значения времени наработки КПА
  Cve::instance().setParameterValue(QString("/cveOperationTime"),
                                    cveOperationTime);

  // TODO: если менеджер сессий подгрузится позже, то тут будет фейл
  int productOperationTime = settings.value(QString("product_%1").arg(
                                           Cve::instance().getParameterValue(QString("/serialNumber"),
                                                                             QString("000000"))), 0).toInt(&ok);;

  Cve::instance().setParameterValue(QString("/productOperationTime"),
                                    productOperationTime);

  settings.endGroup();

  int days = ( ( ( ( cveOperationTime ) / 60 ) / 60 ) / 24 );
  int hour = ( ( ( ( cveOperationTime ) / 60 ) / 60 ) % 24 );
  int min  = ( ( ( cveOperationTime ) / 60 ) ) % 60 ;
  int sec  = ( cveOperationTime ) % 60;

  QString cveTime = QString("%1 дней %2 часов %3 минут %4 секунд")
                .arg(days)
                .arg(hour)
                .arg(min,  2, 10, QChar('0'))
                .arg(sec,  2, 10, QChar('0'));

  days = ( ( ( ( productOperationTime ) / 60 ) / 60 ) / 24 );
  hour = ( ( ( ( productOperationTime ) / 60 ) / 60 ) % 24 );
  min  = ( ( ( productOperationTime ) / 60 ) ) % 60 ;
  sec  = ( productOperationTime ) % 60;

  QString productTime = QString("%1 дней %2 часов %3 минут %4 секунд")
                .arg(days)
                .arg(hour)
                .arg(min,  2, 10, QChar('0'))
                .arg(sec,  2, 10, QChar('0'));

  logInfo(this, QString("Время наработки КПА = %1 ").arg(cveTime));
  logInfo(this, QString("Время наработки изделия = %2").arg(productTime));

  _settings->setOperationTimes(cveTime, productTime);
}

