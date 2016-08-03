#include "dsuregisterfile.h"

/*******************************************************************************
 *                      Работа с регистрами DSU
 ******************************************************************************/
dsuRegisterFile::dsuRegisterFile() {
  DSUC = new DsuControlRegister();
  TBCTL = new DsuTraceBufferControlRegister();
  TTC   = new DsuTimeTagCounterlRegister();
  BAD1  = new DsuAHBBreakAddrRegister(0x90000010);
  BAD2  = new DsuAHBBreakAddrRegister(0x90000018);
  BMA1  = new DsuAHBMaskRegister(0x90000014);;
  BMA2  = new DsuAHBMaskRegister(0x9000001C);;
}

/*******************************************************************************
 *                      Работа с регистром управления DSU
 ******************************************************************************/

/**
  * Инициализация регистра управления DSU
  */
DsuControlRegister::DsuControlRegister() {
  addr      = 0x90000000;

  dcnt = new QTableWidgetItem(QString( "%1" ).arg( data.flags.dcnt, 0, 16 ));
  re = new QTableWidgetItem(QString( "%1" ).arg( data.flags.re, 0, 16 ));
  dr = new QTableWidgetItem(QString( "%1" ).arg( data.flags.dr, 0, 16 ));
  lr = new QTableWidgetItem(QString( "%1" ).arg( data.flags.lr, 0, 16 ));
  ss = new QTableWidgetItem(QString( "%1" ).arg( data.flags.ss, 0, 16 ));
  pe = new QTableWidgetItem(QString( "%1" ).arg( data.flags.pe, 0, 16 ));
  ee = new QTableWidgetItem(QString( "%1" ).arg( data.flags.ee, 0, 16 ));
  eb = new QTableWidgetItem(QString( "%1" ).arg( data.flags.eb, 0, 16 ));
  dm = new QTableWidgetItem(QString( "%1" ).arg( data.flags.dm, 0, 16 ));
  de = new QTableWidgetItem(QString( "%1" ).arg( data.flags.de, 0, 16 ));
  bz = new QTableWidgetItem(QString( "%1" ).arg( data.flags.bz, 0, 16 ));
  bx = new QTableWidgetItem(QString( "%1" ).arg( data.flags.bx, 0, 16 ));
  bd = new QTableWidgetItem(QString( "%1" ).arg( data.flags.bd, 0, 16 ));
  bn = new QTableWidgetItem(QString( "%1" ).arg( data.flags.bn, 0, 16 ));
  bs = new QTableWidgetItem(QString( "%1" ).arg( data.flags.bs, 0, 16 ));
  bw = new QTableWidgetItem(QString( "%1" ).arg( data.flags.bw, 0, 16 ));
  be = new QTableWidgetItem(QString( "%1" ).arg( data.flags.be, 0, 16 ));
  ft = new QTableWidgetItem(QString( "%1" ).arg( data.flags.ft, 0, 16 ));
  bt = new QTableWidgetItem(QString( "%1" ).arg( data.flags.bt, 0, 16 ));
  dcm= new QTableWidgetItem(QString( "%1" ).arg( data.flags.dcm, 0, 16 ));
  te = new QTableWidgetItem(QString( "%1" ).arg( data.flags.te, 0, 16 ));
}

/**
  *
  */
void DsuControlRegister::refresh() {

  viewer->item( 0 , 0 )->setText(QString( "%1" ).arg( data.flags.dcnt, 0, 16 ));
  viewer->item( 0 , 1 )->setText(QString( "%1" ).arg( data.flags.re, 0, 16 ));
  viewer->item( 0 , 2 )->setText(QString( "%1" ).arg( data.flags.dr, 0, 16 ));
  viewer->item( 0 , 3 )->setText(QString( "%1" ).arg( data.flags.lr, 0, 16 ));
  viewer->item( 0 , 4 )->setText(QString( "%1" ).arg( data.flags.lr, 0, 16 ));
  viewer->item( 0 , 5 )->setText(QString( "%1" ).arg( data.flags.pe, 0, 16 ));
  viewer->item( 0 , 6 )->setText(QString( "%1" ).arg( data.flags.ee, 0, 16 ));
  viewer->item( 0 , 7 )->setText(QString( "%1" ).arg( data.flags.eb, 0, 16 ));
  viewer->item( 0 , 8 )->setText(QString( "%1" ).arg( data.flags.dm, 0, 16 ));
  viewer->item( 0 , 9 )->setText(QString( "%1" ).arg( data.flags.de, 0, 16 ));
  viewer->item( 0 , 10 )->setText(QString( "%1" ).arg( data.flags.bz, 0, 16 ));
  viewer->item( 0 , 11 )->setText(QString( "%1" ).arg( data.flags.bx, 0, 16 ));
  viewer->item( 0 , 12 )->setText(QString( "%1" ).arg( data.flags.bd, 0, 16 ));
  viewer->item( 0 , 13 )->setText(QString( "%1" ).arg( data.flags.bn, 0, 16 ));
  viewer->item( 0 , 14 )->setText(QString( "%1" ).arg( data.flags.bs, 0, 16 ));
  viewer->item( 0 , 15 )->setText(QString( "%1" ).arg( data.flags.bw, 0, 16 ));
  viewer->item( 0 , 16 )->setText(QString( "%1" ).arg( data.flags.be, 0, 16 ));
  viewer->item( 0 , 17 )->setText(QString( "%1" ).arg( data.flags.ft, 0, 16 ));
  viewer->item( 0 , 18 )->setText(QString( "%1" ).arg( data.flags.bt, 0, 16 ));
  viewer->item( 0 , 19 )->setText(QString( "%1" ).arg( data.flags.dcm, 0, 16 ));
  viewer->item( 0 , 20 )->setText(QString( "%1" ).arg( data.flags.te, 0, 16 ));
}

/**
  * Установка данных
  */
void DsuControlRegister::setData( unsigned int value ) {
  data.value = value;
}

/**
  *
  */
void DsuControlRegister::setDataViewColumn( unsigned int value, int num ) {

/* TODO: magic number */
  switch ( num ) {
    case 1:
      data.flags.dcnt = value;
      break;
    case 2:
      data.flags.re = value;
      break;
    case 3:
      data.flags.dr = value;
      break;
    case 4:
      data.flags.lr = value;
      break;
    case 5:
      data.flags.ss = value;
      break;
    case 6:
      data.flags.pe = value;
      break;
    case 7:
      data.flags.ee = value;
      break;
    case 8:
      data.flags.eb = value;
      break;
    case 9:
      data.flags.dm = value;
      break;
    case 10:
      data.flags.de = value;
      break;
    case 11:
      data.flags.bz = value;
      break;
    case 12:
      data.flags.bx = value;
      break;
    case 13:
      data.flags.bd = value;
      break;
    case 14:
      data.flags.bn = value;
      break;
    case 15:
      data.flags.bs = value;
      break;
    case 16:
      data.flags.bw = value;
      break;
    case 17:
      data.flags.be = value;
      break;
    case 18:
      data.flags.ft = value;
      break;
    case 19:
      data.flags.bt = value;
      break;
    case 20:
      data.flags.dcm = value;
      break;
    case 21:
      data.flags.te = value;
      break;
    default:
      break;
  };
}

/**
  *
  */
void DsuControlRegister::registerTableWidget( QTableWidget *view ) {
  viewer = view;
}

/**
  *
  */
void DsuControlRegister::setItemsToTableWidget() {
  viewer ->setItem( 0 , 0, dcnt );
  viewer ->setItem( 0 , 1, re );
  viewer ->setItem( 0 , 2, dr );
  viewer ->setItem( 0 , 3, lr );
  viewer ->setItem( 0 , 4, ss );
  viewer ->setItem( 0 , 5, pe );
  viewer ->setItem( 0 , 6, ee );
  viewer ->setItem( 0 , 7, eb );
  viewer ->setItem( 0 , 8, dm );
  viewer ->setItem( 0 , 9, de );
  viewer ->setItem( 0 , 10, bz );
  viewer ->setItem( 0 , 11, bx );
  viewer ->setItem( 0 , 12, bd );
  viewer ->setItem( 0 , 13, bn );
  viewer ->setItem( 0 , 14, bs );
  viewer ->setItem( 0 , 15, bw );
  viewer ->setItem( 0 , 16, be );
  viewer ->setItem( 0 , 17, ft );
  viewer ->setItem( 0 , 18, bt );
  viewer ->setItem( 0 , 19, dcm );
  viewer ->setItem( 0 , 20, te );
}

/*******************************************************************************
 *                      Работа с регистром TBCTL DSU
 ******************************************************************************/

/**
  * Инициализация TBCTL регистра
  */
DsuTraceBufferControlRegister::DsuTraceBufferControlRegister() {
  addr      = 0x90000004;

  af    = new QTableWidgetItem(QString( "%1" ).arg( data.flags.af, 0, 16 ));
  bcnt  = new QTableWidgetItem(QString( "%1" ).arg( data.flags.bcnt, 0, 16 ));
  icnt  = new QTableWidgetItem(QString( "%1" ).arg( data.flags.icnt, 0, 16 ));
  ta    = new QTableWidgetItem(QString( "%1" ).arg( data.flags.ta, 0, 16 ));
  ti    = new QTableWidgetItem(QString( "%1" ).arg( data.flags.ti, 0, 16 ));
}

/**
  *
  */
int DsuTraceBufferControlRegister::getIcnt() {
  return data.flags.icnt;
}


/**
  *
  */
void DsuTraceBufferControlRegister::refresh() {
  viewer->item( 0 , VIEWER_POSITION_AF )->setText(QString( "%1" ).arg( data.flags.af, 0, 16 ));
  viewer->item( 0 , VIEWER_POSITION_BCNT )->setText(QString( "%1" ).arg( data.flags.bcnt, 0, 16 ));
  viewer->item( 0 , VIEWER_POSITION_ICNT )->setText(QString( "%1" ).arg( data.flags.icnt, 0, 16 ));
  viewer->item( 0 , VIEWER_POSITION_TA )->setText(QString( "%1" ).arg( data.flags.ta, 0, 16 ));
  viewer->item( 0 , VIEWER_POSITION_TI )->setText(QString( "%1" ).arg( data.flags.ti, 0, 16 ));
}

/**
  * Установка данных
  */
void DsuTraceBufferControlRegister::setData( unsigned int value ) {
  data.value = value;
}

/**
  *
  */
void DsuTraceBufferControlRegister::setDataViewColumn( unsigned int value, int num ) {

/* TODO: magic number */
  switch ( num ) {
    case VIEWER_POSITION_AF:
      data.flags.af = value;
      break;
    case VIEWER_POSITION_BCNT:
      data.flags.bcnt = value;
      break;
    case VIEWER_POSITION_ICNT:
      data.flags.bcnt = value;
      break;
    case VIEWER_POSITION_TA:
      data.flags.ta = value;
      break;
    case VIEWER_POSITION_TI:
      data.flags.ti = value;
      break;
    default:
      break;
  };
}

/**
  *
  */
void DsuTraceBufferControlRegister::registerTableWidget( QTableWidget *view ) {
  viewer = view;
}

/**
  *
  */
void DsuTraceBufferControlRegister::setItemsToTableWidget() {
  viewer ->setItem( 0, VIEWER_POSITION_AF,     af );
  viewer ->setItem( 0, VIEWER_POSITION_BCNT,   bcnt );
  viewer ->setItem( 0, VIEWER_POSITION_ICNT,   icnt );
  viewer ->setItem( 0, VIEWER_POSITION_TA,     ta );
  viewer ->setItem( 0, VIEWER_POSITION_TI,     ti );
}

/*******************************************************************************
 *                      Работа с регистром TTC
 ******************************************************************************/
/**
  * Инициализация TTC регистра
  */
DsuTimeTagCounterlRegister::DsuTimeTagCounterlRegister() {
  addr  = 0x90000008;
  cnt   = new QTableWidgetItem(QString( "%1" ).arg( data.flags.cnt, 0, 16 ));
}

/**
  *
  */
void DsuTimeTagCounterlRegister::refresh() {
  viewer->item( 0 , VIEWER_POSITION_CNT )->setText(QString( "%1" ).arg( data.flags.cnt, 0, 16 ));
}

/**
  * Установка данных
  */
void DsuTimeTagCounterlRegister::setData( unsigned int value ) {
  data.value = value;
}

/**
  *
  */
void DsuTimeTagCounterlRegister::setDataViewColumn( unsigned int value, int num ) {
  data.flags.cnt = value;
}

/**
  *
  */
void DsuTimeTagCounterlRegister::registerTableWidget( QTableWidget *view ) {
  viewer = view;
}

/**
  *
  */
void DsuTimeTagCounterlRegister::setItemsToTableWidget() {
  viewer ->setItem( 0, VIEWER_POSITION_CNT,  cnt );
}



/*******************************************************************************
 *                      Работа с регистром BAD
 ******************************************************************************/

/**
  * Инициализация BAD регистра
  */
DsuAHBBreakAddrRegister::DsuAHBBreakAddrRegister( int raddr ) {
  addr   = raddr;
  vaddr   = new QTableWidgetItem(QString( "%1" ).arg( data.flags.addr, 0, 16 ));
  ex   = new QTableWidgetItem(QString( "%1" ).arg( data.flags.ex, 0, 16 ));
}
/**
  *
  */
void DsuAHBBreakAddrRegister::refresh() {
  viewer->item( 0 , VIEWER_POSITION_ADDR )->setText(QString( "%1" ).arg( data.flags.addr, 0, 16 ));
  viewer->item( 0 , VIEWER_POSITION_EX )->setText(QString( "%1" ).arg( data.flags.ex, 0, 16 ));
}

/**
  * Установка данных
  */
void DsuAHBBreakAddrRegister::setData( unsigned int value ) {
  data.value = value;
}

/**
  *
  */
void DsuAHBBreakAddrRegister::setDataViewColumn( unsigned int value, int num ) {
  /* TODO: magic number */
    switch ( num ) {
      case VIEWER_POSITION_ADDR:
        data.flags.addr = value;
        break;
      case VIEWER_POSITION_EX:
        data.flags.ex = value;
        break;
      default:
        break;
    };
}

/**
  *
  */
void DsuAHBBreakAddrRegister::registerTableWidget( QTableWidget *view ) {
  viewer = view;
}

/**
  *
  */
void DsuAHBBreakAddrRegister::setItemsToTableWidget() {
  viewer ->setItem( 0, VIEWER_POSITION_ADDR,  vaddr );
  viewer ->setItem( 0, VIEWER_POSITION_EX,    ex );
}

/*******************************************************************************
 *                      Работа с регистром BMA
 ******************************************************************************/

/**
  * Инициализация BMA регистра
  */
DsuAHBMaskRegister::DsuAHBMaskRegister( int raddr ) {
  addr  = raddr;
  msk   = new QTableWidgetItem(QString( "%1" ).arg( data.flags.msk, 0, 16 ));
  ld    = new QTableWidgetItem(QString( "%1" ).arg( data.flags.ld, 0, 16 ));
  st    = new QTableWidgetItem(QString( "%1" ).arg( data.flags.st, 0, 16 ));
}
/**
  *
  */
void DsuAHBMaskRegister::refresh() {
  viewer->item( 0 , VIEWER_POSITION_MASK )->setText(QString( "%1" ).arg( data.flags.msk, 0, 16 ));
  viewer->item( 0 , VIEWER_POSITION_LD )->setText(QString( "%1" ).arg( data.flags.ld, 0, 16 ));
  viewer->item( 0 , VIEWER_POSITION_ST )->setText(QString( "%1" ).arg( data.flags.st, 0, 16 ));
}

/**
  * Установка данных
  */
void DsuAHBMaskRegister::setData( unsigned int value ) {
  data.value = value;
}

/**
  *
  */
void DsuAHBMaskRegister::setDataViewColumn( unsigned int value, int num ) {
  /* TODO: magic number */
    switch ( num ) {
      case VIEWER_POSITION_MASK:
        data.flags.msk = value;
        break;
      case VIEWER_POSITION_LD:
        data.flags.ld = value;
        break;
      case VIEWER_POSITION_ST:
        data.flags.st = value;
        break;
      default:
        break;
    };
}

/**
  *
  */
void DsuAHBMaskRegister::registerTableWidget( QTableWidget *view ) {
  viewer = view;
}

/**
  *
  */
void DsuAHBMaskRegister::setItemsToTableWidget() {
  viewer ->setItem( 0, VIEWER_POSITION_MASK,  msk );
  viewer ->setItem( 0, VIEWER_POSITION_LD,   ld );
  viewer ->setItem( 0, VIEWER_POSITION_ST,   st );
}

