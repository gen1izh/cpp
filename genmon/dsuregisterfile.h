#ifndef DSUREGISTERFILE_H
#define DSUREGISTERFILE_H

#include "standartregisterformat.h"

#include <QTableWidgetItem>
#include <QTableWidget>

/*******************************************************************************
 *                      Работа с регистром DSUС
 ******************************************************************************/

/**
 * Карта регистра DSUC
 */
typedef union dsucBitMap {

 unsigned int  value;
  struct {
    unsigned te:       1;  /* Bit :  1 = ; 0 = */
    unsigned dcm:      1;  /* Bit :  1 = ; 0 = */
    unsigned bt:       1;  /* Bit :  1 = ; 0 = */
    unsigned ft:       1;  /* Bit :  1 = ; 0 = */
    unsigned be:       1;  /* Bit :  1 = ; 0 = */
    unsigned bw:       1;  /* Bit :  1 = ; 0 = */
    unsigned bs:       1;  /* Bit :  1 = ; 0 = */
    unsigned bn:       1;  /* Bit :  1 = ; 0 = */
    unsigned bd:       1;  /* Bit :  1 = ; 0 = */
    unsigned bx:       1;  /* Bit :  1 = ; 0 = */
    unsigned bz:       1;  /* Bit :  1 = ; 0 = */
    unsigned de:       1;  /* Bit :  1 = ; 0 = */
    unsigned dm:       1;  /* Bit :  1 = ; 0 = */
    unsigned eb:       1;  /* Bit :  1 = ; 0 = */
    unsigned ee:       1;  /* Bit :  1 = ; 0 = */
    unsigned pe:       1;  /* Bit :  1 = ; 0 = */
    unsigned ss:       1;  /* Bit :  1 = ; 0 = */
    unsigned lr:       1;  /* Bit :  1 = ; 0 = */
    unsigned dr:       1;  /* Bit :  1 = ; 0 = */
    unsigned re:       1;  /* Bit :  1 = ; 0 = */
    unsigned dcnt:     9;  /* Bits */
    unsigned reserv:   3;  /* Bits */

  } flags;

} dsucBitMapType;


/**
  * Регистр управления DSU
  */
class DsuControlRegister {
  public:
    DsuControlRegister();

  private:
    unsigned int   addr;
    dsucBitMapType data;

    QTableWidget *viewer;

    enum {
        VIEWER_POSITION_dcnt = 0,
        VIEWER_POSITION_re,
        VIEWER_POSITION_dr,
        VIEWER_POSITION_lr,
        VIEWER_POSITION_ss,
        VIEWER_POSITION_pe,
        VIEWER_POSITION_ee,
        VIEWER_POSITION_eb,
        VIEWER_POSITION_dm,
        VIEWER_POSITION_de,
        VIEWER_POSITION_bz,
        VIEWER_POSITION_bx,
        VIEWER_POSITION_bd,
        VIEWER_POSITION_bn,
        VIEWER_POSITION_bs,
        VIEWER_POSITION_bw,
        VIEWER_POSITION_be,
        VIEWER_POSITION_ft,
        VIEWER_POSITION_bt,
        VIEWER_POSITION_dcm,
        VIEWER_POSITION_te
    };

    QTableWidgetItem *dcnt ;
    QTableWidgetItem *re ;
    QTableWidgetItem *dr ;
    QTableWidgetItem *lr ;
    QTableWidgetItem *ss ;
    QTableWidgetItem *pe ;
    QTableWidgetItem *ee ;
    QTableWidgetItem *eb ;
    QTableWidgetItem *dm ;
    QTableWidgetItem *de ;
    QTableWidgetItem *bz ;
    QTableWidgetItem *bx ;
    QTableWidgetItem *bd ;
    QTableWidgetItem *bn ;
    QTableWidgetItem *bs ;
    QTableWidgetItem *bw ;
    QTableWidgetItem *be ;
    QTableWidgetItem *ft ;
    QTableWidgetItem *bt ;
    QTableWidgetItem *dcm ;
    QTableWidgetItem *te ;

public:
    void registerTableWidget( QTableWidget *view );
    void setItemsToTableWidget();
    void refresh();
    void setData( unsigned int value );
    void setDataViewColumn( unsigned int value, int num );
};

/*******************************************************************************
 *                      Работа с регистром TBCTL
 ******************************************************************************/

/**
 * Карта регистра TBCTL
 */
typedef union tbctlBitMap {

 unsigned int  value;
  struct {
    unsigned icnt:     9;  /* Bit :  1 = ; 0 = */
    unsigned reserv2:  3;  /* Bit :  1 = ; 0 = */
    unsigned bcnt:     9;  /* Bit :  1 = ; 0 = */
    unsigned reserv1:  3;  /* Bit :  1 = ; 0 = */
    unsigned ti:       1;  /* Bit :  1 = ; 0 = */
    unsigned ta:       1;  /* Bit :  1 = ; 0 = */
    unsigned af:       1;  /* Bits */
    unsigned reserv:   5;  /* Bits */

  } flags;

} tbctlBitMapType;

/**
  * Регистр управления буфером трассировки DSU
  */
class DsuTraceBufferControlRegister {
  public:
    DsuTraceBufferControlRegister();
  private:
    enum {
     VIEWER_POSITION_AF = 0,
     VIEWER_POSITION_TA,
     VIEWER_POSITION_TI,
     VIEWER_POSITION_BCNT,
     VIEWER_POSITION_ICNT
    };
      unsigned int    addr;
      tbctlBitMapType data;

      QTableWidget *viewer;

      QTableWidgetItem *icnt;
      QTableWidgetItem *bcnt;
      QTableWidgetItem *ti;
      QTableWidgetItem *ta;
      QTableWidgetItem *af;

public:
  void registerTableWidget( QTableWidget *view );
  void setItemsToTableWidget();
  int  getIcnt();
  void refresh();
  void setData( unsigned int value );
  void setDataViewColumn( unsigned int value, int num );

};

/*******************************************************************************
 *                      Работа с регистром TTC
 ******************************************************************************/
/**
 * Карта регистра TTC
 */
typedef union ttcBitMap {

 unsigned int  value;
  struct {
    unsigned cnt:     30;  /* Bit :  1 = ; 0 = */
    unsigned reserv:   2;  /* Bits */

  } flags;

} ttcBitMapType;

/**
  * Регистр счетчика меток времени
  */
class DsuTimeTagCounterlRegister {
  public:
    DsuTimeTagCounterlRegister();
  private:
    enum {
     VIEWER_POSITION_CNT = 0
    };
      unsigned int    addr;
      ttcBitMapType   data;

      QTableWidget   *viewer;

      QTableWidgetItem *cnt;

  public:
    void registerTableWidget( QTableWidget *view );
    void setItemsToTableWidget();
    void refresh();
    void setData( unsigned int value );
    void setDataViewColumn( unsigned int value, int num );
};


/*******************************************************************************
 *                      Работа с регистром BAD
 ******************************************************************************/

/**
 * Карта регистра BAD
 */
typedef union badBitMap {
 unsigned int  value;
  struct {
    unsigned addr:   30;  /* Bit :  1 = ; 0 = */
    unsigned reserv:  1;  /* Bits */
    unsigned ex:      1;  /* Bits */
  } flags;
} badBitMapType;

/**
  * Регистр адреса останова
  */
class DsuAHBBreakAddrRegister {
  public:
    DsuAHBBreakAddrRegister( int raddr );
  private:
    enum {
     VIEWER_POSITION_ADDR = 0,
     VIEWER_POSITION_EX
    };
      unsigned int    addr;
      badBitMapType   data;

      QTableWidget    *viewer;

      QTableWidgetItem *vaddr;
      QTableWidgetItem *ex;

  public:
    void registerTableWidget( QTableWidget *view );
    void setItemsToTableWidget();
    void refresh();
    void setData( unsigned int value );
    void setDataViewColumn( unsigned int value, int num );
};

/*******************************************************************************
 *                      Работа с регистром BMA
 ******************************************************************************/
/**
 * Карта регистра BMA
 */
typedef union bmaBitMap {
 unsigned int  value;
  struct {
    unsigned msk:  30;  /* Bit :  1 = ; 0 = */
    unsigned ld:    1;  /* Bits */
    unsigned st:    1;  /* Bits */
  } flags;
} bmaBitMapType;

/**
  * Регистр маски останова
  */
class DsuAHBMaskRegister {
  public:
    DsuAHBMaskRegister( int raddr );
  private:
    enum {
     VIEWER_POSITION_MASK = 0,
     VIEWER_POSITION_LD,
     VIEWER_POSITION_ST
    };
      unsigned int    addr;
      bmaBitMapType   data;

      QTableWidget    *viewer;

      QTableWidgetItem *msk;
      QTableWidgetItem *ld;
      QTableWidgetItem *st;

  public:
    void registerTableWidget( QTableWidget *view );
    void setItemsToTableWidget();
    void refresh();
    void setData( unsigned int value );
    void setDataViewColumn( unsigned int value, int num );
};


/*******************************************************************************
 *                       Работа с основными регистрами DSU
 ******************************************************************************/
class dsuRegisterFile {
  public:
    dsuRegisterFile();

    DsuControlRegister            *DSUC;    // регистр управления DSU
    DsuTraceBufferControlRegister *TBCTL;   // регистр управления буфером трассировки
    DsuTimeTagCounterlRegister    *TTC;     // регистр счетчика меток времени
    DsuAHBBreakAddrRegister       *BAD1;    // регистр адреса останова 1
    DsuAHBBreakAddrRegister       *BAD2;    // регистр адреса останова 2
    DsuAHBMaskRegister            *BMA1;    // регистр маски останова 1
    DsuAHBMaskRegister            *BMA2;    // регистр маски останова 2

};

#endif // DSUREGISTERFILE_H
