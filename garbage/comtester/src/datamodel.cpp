// ---------------------------------------------------------------------------

#pragma hdrstop

#include "datamodel.h"

// ---------------------------------------------------------------------------

  // dl - dynamic list

point *dl_last_item;
point *dl_start_item;

  /**
  *  Initialize start and last elems
  */
void dl_init() {
  dl_last_item = NULL;
  dl_start_item = NULL;
}


/**
  *  Store element into list end
  */
void dl_store(point *i) {

  point *p;

  if (dl_last_item == NULL) {
    i->next = NULL;
    i->back = NULL;

    dl_last_item = i;
    dl_start_item = i;
    return;
  }

  p = dl_last_item;
  p->next = i;
  i->next = NULL;
  i->back = p;
  dl_last_item = i;
}

  /**
  *  Clean all elements
  */
void dl_delete_all() {
  point *item, *del_item;
  item = dl_start_item;
  while (item) {
    del_item = item;
    item = item->next;
    free(del_item);
  }
}

#pragma package(smart_init)
