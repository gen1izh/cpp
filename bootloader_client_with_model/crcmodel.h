#ifndef CM_DONE
#define CM_DONE
#include <QtGui>
 
typedef unsigned char      *p_ubyte_;
 
typedef struct
  {
    int             cm_width;   /* Parameter: Width in bits [8,32].       */
    unsigned long   cm_poly;    /* Parameter: The algorithm's polynomial. */
    unsigned long   cm_init;    /* Parameter: Initial register value.     */
    bool            cm_refin;   /* Parameter: Reflect input bytes?        */
    bool            cm_refot;   /* Parameter: Reflect output CRC?         */
    unsigned long   cm_xorot;   /* Parameter: XOR this to output CRC.     */
    unsigned long   cm_reg;     /* Context: Context during execution.     */
  } cm_t;
 
typedef cm_t *p_cm_t;
 
void cm_ini(p_cm_t p_cm);
void cm_nxt(p_cm_t p_cm,int ch);
void cm_blk(p_cm_t p_cm,p_ubyte_ blk_adr,unsigned long blk_len);
unsigned long cm_crc(p_cm_t p_cm);
unsigned long cm_tab(p_cm_t p_cm,int index);
 
#endif
