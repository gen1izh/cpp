//---------------------------------------------------------------------------

#ifndef testcomportH
#define testcomportH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Chart.hpp"
#include "TeEngine.hpp"
#include "TeeProcs.hpp"
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include "Series.hpp"
#include "ftd2xx.h"
#include "datamodel.h"
#include "receiverthread.h"
#include "ftdiapiwrapper.h"



//---------------------------------------------------------------------------
class Tmain : public TForm {
__published: // IDE-managed Components
  TButton *startButton;
  TChart *viewerChart;
  TFastLineSeries *Series1;
  TTimer *refreshTimer;

  void __fastcall startButtonClick(TObject *Sender);
  void __fastcall FormCreate(TObject *Sender);
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
  void __fastcall refreshTimerTimer(TObject *Sender);

private: // User declarations
public: // User declarations
  __fastcall Tmain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tmain *main;

extern  DeviceFtdi    *dev;
extern  ThreadAdapter *thr;
//---------------------------------------------------------------------------
#endif
