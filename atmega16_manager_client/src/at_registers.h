#ifndef AT_REGISTERS_H
#define AT_REGISTERS_H
#include <QtGui>

typedef struct {
  unsigned int  value;
  QString       reg_name;
} at_reg_map_t;

extern at_reg_map_t reg_map[1000];


bool get_reg_value(QString st, int *value);

void clear_reg_value();

bool set_reg_value(QString st, int value);

#endif // AT_REGISTERS_H
