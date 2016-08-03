//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("testcomport.cpp", main);
//---------------------------------------------------------------------------
WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int) {
  try {
    Application->Initialize();
    Application->MainFormOnTaskBar = true;
    Application->CreateForm(__classid(Tmain), &main);
     Application->Run();
  }
  catch(Exception & exception) {
    Application->ShowException(&exception);
  }
  catch(...) {
    try {
      throw Exception("");
    }
    catch(Exception & exception) {
      Application->ShowException(&exception);
    }
  }
  return 0;
}
//---------------------------------------------------------------------------
