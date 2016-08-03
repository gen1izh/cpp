
struct can_stats {
  unsigned char sr;           /* CAN Controller status register */
  unsigned int  baud;         /* Baud rate  */
  unsigned char txerr;        /* TX error counter */
  unsigned char rxerr;        /* RX error counter */
  unsigned char errorcode;    /* Error code */
};

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

int do_write(int s, void *_buf, int len);
int do_read(int s, void *_buf, int len);
int can_send(int s, int ff, int rtr, int id, int dlc, unsigned char *data );
int can_recv(int s, int *ff, int *rtr, int *id, int *dlc, unsigned char *data );
int can_setacr(int s, unsigned int acr);
int can_setamr(int s, unsigned int amr);
int can_setbaud(int s, unsigned int baud);
int can_getstats(int s, struct can_stats *stat);

#ifdef __cplusplus
}
#endif // __cplusplus
