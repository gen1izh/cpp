//---------------------------------------------------------------------------

#ifndef datamodelH
#define datamodelH
//---------------------------------------------------------------------------
#include <vector>

using namespace std;

/**
  *  Element structure
  */
struct point{
  int     i;
  double  x;
  double  y;
  point   *next;
  point   *back;
  bool    draw_flag;
};

/**
  *  Initialize start and last elems
  */
void dl_init();
/**
  *  Store element into list end
  */
void dl_store(point *i);
/**
  *  Clean all elements
  */
void dl_delete_all();

#endif
