//---------------------------------------------------------------------------


#pragma hdrstop

#include "device_ops.h"
#include "device_ftdi_ops.h"

extern device_ftdi *dev;

//---------------------------------------------------------------------------


device_ops::device_ops() {
}

device_ops::~device_ops() {
}

void device_ops::set_configure(int cfg) {
	char data[4];

	data[0] = 0xFF & cfg;
	data[1] = 0xFF & (cfg >> 8);
	data[2] = 0xFF & (cfg >> 16);
	data[3] = 0xFF & (cfg >> 24);
	dev->device_write((char *)&data[0],4);
}

int device_ops::get_configure() {
return 0;
}

#pragma package(smart_init)
