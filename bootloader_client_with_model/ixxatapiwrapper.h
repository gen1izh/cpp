#ifndef ECI_CAN_H
#define ECI_CAN_H

#include "inc/ECI10A.h"
#include "inc/ECI.h"
#include "inc/ECI_pshpack1.h"
#include "inc/ECI_poppack.h"
#include "inc/OsEci.h"
#include "inc/ecicommand.h"

#include <QList>

#include "interfaceStrategy.h"


/**
  * Can interfaces numbers
  */
#define CAN_INTERFACE0  0
#define CAN_INTERFACE1  1


/**
 * Static constants, types, macros, variables
 */

/**
 * ECI Demo send timeout in [ms]
 */
#define ECIDEMO_TX_TIMEOUT 500

/**
 * ECI Demo TX message count for CAN
 */
#define ECIDEMO_TX_MSGCOUNT_CAN 0x1

/**
 * ECI Demo TX message count for LIN
 */
#define ECIDEMO_TX_MSGCOUNT_LIN (0x800 * 1)

/**
 * ECI Demo receive timeout in [ms]
 */
#define ECIDEMO_RX_TIMEOUT 200

/**
 * ECI Demo total receive timeout in [ms]
 */
#define ECIDEMO_RX_TOTALTIMEOUT 30000

//#define ECIDEMO_HWUSEPOLLINGMODE


class IXXATApiWrapper {
private:
    ECI_RESULT          hResult;
    ECI_HW_PARA         stcHwPara;
    ECI_HW_INFO         stcHwInfo;
    DWORD               dwHwIndex;
    DWORD               dwCtrlIndex[2];
    ECI_CTRL_HDL        dwCtrlHandle[2];

public:
    IXXATApiWrapper();
    ~IXXATApiWrapper();

    void _initialization();
    void _open( int canInterfaceNumber );

    ECI_RESULT _read(int canInterfaceNumber, ECI_CTRL_MESSAGE *msg, int *read_cnt);
    ECI_RESULT _write(int canInterfaceNumber, ECI_CTRL_MESSAGE msg, int msgType );

    void _start(int canInterfaceNumber);
    void _stop(int canInterfaceNumber);
    void _close(int canInterfaceNumber);

    void _errorToText();
};






#endif // ECI_CAN_H
