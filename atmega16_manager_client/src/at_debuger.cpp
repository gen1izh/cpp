#include "at_debuger.h"
#include "at_registers.h"
#include "at_report.h"
#include "macro.h"
#include "at_thread.h"


/* ========================================================================== */
/*                                                                            */
/* ========================================================================== */

ATMC_virtualDebbuger virtualDebbuger;

ATMC_virtualDebbuger::ATMC_virtualDebbuger() {
  PC = 0;
}

ATMC_virtualDebbuger::~ATMC_virtualDebbuger() {
}


void ATMC_virtualDebbuger::add_dbg_line(ATMC_obCodeLine dbg) {
  cmdSequence.append(dbg);
}

void ATMC_virtualDebbuger::set_exec() {
}
