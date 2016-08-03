#ifndef PRTANSWEREXTRACTOR_H
#define PRTANSWEREXTRACTOR_H

#include "prt/cmd_packet.h"

class ATMC_answerExtractor{
public:

  ATMC_answerExtractor();
  ~ATMC_answerExtractor();

  void answerPacketRoute( ATMC_cmdPacket pack, unsigned char *bf, int sz, quint8 bf_type );

private:
  unsigned char    *buf;
  unsigned int      size;
  quint8            buf_type;

  void answerPacketStateExtract(QString cmd_name);
  void answerPacketConfigureExtract(QString cmd_name);
  void answerPacketSpeedExtract(QString cmd_name);
  void answerPacketBufLengthExtract(QString cmd_name);
  void answerPacketStatsExtract(QString cmd_name);

  void answerPacketFreqInMcSecExtract(QString cmd_name);
  void answerPacketPrescalerValue(QString cmd_name);

  void answerPacketTODExtract(QString cmd_name);
};

#endif // PRTANSWEREXTRACTOR_H
