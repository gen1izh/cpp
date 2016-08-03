#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "ethcan_api.h"

int do_write(int s, void *_buf, int len)
{
    int total, slen, rlen;
    unsigned char *buf = (unsigned char *)_buf;
    total = 0;
    rlen = len;
    while (total < len) {
        slen = send(s, buf, rlen, 0);
        if (slen != rlen) {
	  if (slen < 0) {
	    if (errno == EWOULDBLOCK) {
	      continue;
	    }
	    perror("do_write");
	    return -1;
	  }
	  else if (slen > 0) {
	    rlen -= slen;
	    buf += slen;
	  }
	  else if (slen == 0) return 0;
        }
        total += slen;
    }
    return total;
}


int do_read(int s, void *_buf, int len)
{
  int total, slen, rlen;
  unsigned char *buf = (unsigned char *)_buf;
  total = 0;
  rlen = len;
  while (total < len) {
    slen = recv(s, buf, rlen, 0);
    if (slen != rlen) {
      if (slen < 0) {
	if (!(errno == EWOULDBLOCK && total != 0))  /* don't return because of block if we have begun to read */
	  return -1;
      }
      else if (slen == 0) {
	return 0;
      }
      rlen -= slen;
      buf += slen;
    }
    total += slen;
  }
  return total;
}

int can_send(int s, int ff, int rtr, int id, int dlc, unsigned char *data) {

  unsigned char message[14];
  unsigned int nbid;
  int len = (dlc <= 8) ? dlc : 8;

  message[0] = 0;
  message[1] = (ff&1)<<7 | (rtr&1) << 6 | dlc&0xF;

  nbid = htonl(id);

  memcpy(&message[2], &nbid, 4);

  memcpy(&message[6], data, len);

  return do_write(s, message, 6+len);
}

int can_recv(int s, int *ff, int *rtr, int *id, int *dlc, unsigned char *data) {
  unsigned char header[6];
  int res;
  unsigned int nbid;

  if ((res = do_read(s, header, 6)) <= 0) return res;

  *ff = (header[1] & 0x80) >> 7;
  *rtr = (header[1] & 0x40) >> 6;
  *dlc = header[1] & 0xF;

  memcpy(&nbid, &header[2], 4);
  *id = ntohl(nbid);

  return do_read(s, data, (*dlc <= 8) ? *dlc : 8);

}

int can_setbaud(int s, unsigned int baud) {

  unsigned char conf[6];
  unsigned int nbbaud;

  conf[0] = 1; /* conf protocol */
  conf[1] = 0; /* option 0, BTR */


  nbbaud = htonl(baud);

  memcpy(&conf[2], &nbbaud, 4);

  return do_write(s, conf, 6);
}

int can_setacr(int s, unsigned int acr) {

  unsigned char conf[6];
  unsigned int nbacr;

  conf[0] = 1; /* conf protocol */
  conf[1] = 1; /* option 1, ACR */


  nbacr = htonl(acr);

  memcpy(&conf[2], &nbacr, 4);

  return do_write(s, conf, 6);
}

int can_setamr(int s, unsigned int amr) {

  unsigned char conf[6];
  unsigned int nbamr;

  conf[0] = 1; /* conf protocol */
  conf[1] = 2; /* option 1, AMR */


  nbamr = htonl(amr);

  memcpy(&conf[2], &nbamr, 4);

  return do_write(s, conf, 6);
}

int can_getstats(int s, struct can_stats *stat) {

  unsigned char packet[8];
  int res;

  packet[0] = 2; /* status protocol */
  packet[1] = 0; /* Get all stats */

  do_write(s, packet, 2);

  if ( (res = do_read(s, packet, 8)) <= 0) return res;

  if (packet[0] != 2 && packet[1] != 0)
    return -1;

  stat->sr = packet[2];
  stat->baud = (packet[3]<<8) | packet[4];
  stat->txerr = packet[5];
  stat->rxerr = packet[6];
  stat->errorcode = packet[7];

  return 0;

}
