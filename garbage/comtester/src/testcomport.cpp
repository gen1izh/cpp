// ---------------------------------------------------------------------------

#include  <vcl.h>
#pragma   hdrstop

#include  "testcomport.h"


// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Chart"
#pragma link "TeEngine"
#pragma link "TeeProcs"
#pragma link "Series"
#pragma resource "*.dfm"

#include <vector>

using namespace std;

Tmain *main;

/**
 *  Wrapper Api for Device work
 */
DeviceFtdi    *dev;
/**
 * Receiver thread
 */
ThreadAdapter *thr;

extern point    *dl_start_item;

// ---------------------------------------------------------------------------
__fastcall Tmain::Tmain(TComponent* Owner) : TForm(Owner) {
}

// ---------------------------------------------------------------------------
void __fastcall Tmain::startButtonClick(TObject *Sender) {
  /**
   *  Create thread and clear chart
   */
  if ( startButton->Caption == "ÑÒÀÐÒ" ) {
    startButton->Caption = "ÑÒÎÏ";
    dl_init();
    refreshTimer->Enabled = true;
    if (!thr) {
      thr = new ThreadAdapter();
    }
    else {
      thr->_create();
    }
    viewerChart->Series[0]->Clear();
  }
  else {
  /**
   *  Close thread and clear data
   */
    startButton->Caption  = "ÑÒÀÐÒ";
    refreshTimer->Enabled = false;
    thr->_exit();
    dl_delete_all();
  }
}

// ---------------------------------------------------------------------------
void __fastcall Tmain::FormCreate(TObject *Sender) {
 /**
  *  Create\open device
  */
  dev = new DeviceFtdi();
  dev->device_open(0);
  dl_init();
}
// ---------------------------------------------------------------------------

void __fastcall Tmain::FormClose(TObject *Sender, TCloseAction &Action) {
 /**
  *  Delete\close device and receiver thread
  */
  dev->device_close();
  if (dev)
    delete dev;
  if (thr)
    delete thr;
}

// ---------------------------------------------------------------------------
void __fastcall Tmain::refreshTimerTimer(TObject *Sender) {
  point *item;
  item = dl_start_item;
  while (item) {
    if ( item->draw_flag == false ) {
      main->viewerChart->Series[0]->AddXY( item->x, item->y );
      item->draw_flag = true;
    }
    item = item->next;
  }
}
// ---------------------------------------------------------------------------
