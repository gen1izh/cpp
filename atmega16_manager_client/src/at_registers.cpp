#include "at_registers.h"

void clear_reg_value(){
  int i=0;
  while(reg_map[i].reg_name != "0") {
      if ((reg_map[i].reg_name == "0")&&
        (reg_map[i].value ==0)) break;
      reg_map[i].value = 0;
    i++;
  }
}

bool get_reg_value(QString st, int *value){
  int i=0;
  bool ret_value = false;

  while(reg_map[i].reg_name != "0") {
      if ((reg_map[i].reg_name == "0")&&
        (reg_map[i].value ==0)) break;
    if (st == reg_map[i].reg_name) {
      *value = reg_map[i].value;
      return true;
      }
    i++;
  }
  return ret_value ;
}

bool set_reg_value(QString st, int value){
  int i=0;
  bool ret_value = false;

  while(reg_map[i].reg_name != "0") {
    if (st == reg_map[i].reg_name) {
      reg_map[i].value = value;
      return true;
      }
    i++;
  }

  return ret_value ;
}

at_reg_map_t reg_map [1000] =
{

  /*
   * Описание Флагового регистра
   */
  { 0,  "FReg"        },
  /*
   * Описание статусных состояний устройств
   */
  { 0,  "UART1_SuR"   },
  { 0,  "UART2_SuR"   },
  { 0,  "UART3_SuR"   },
  { 0,  "UART4_SuR"   },

  { 0,  "CAN1_SuR"    },
  { 0,  "CAN2_SuR"    },

  { 0,  "SPI1_SuR"    },
  { 0,  "SPI2_SuR"    },
  { 0,  "SPI3_SuR"    },

  { 0,  "BTS_SuR"    },

  { 0,  "TIMER1_SuR"  },
  { 0,  "TIMER2_SuR"  },
  { 0,  "TIMER3_SuR"  },
  { 0,  "TIMER4_SuR"  },
  { 0,  "TIMER5_SuR"  },
  { 0,  "TIMER6_SuR"  },
  { 0,  "TIMER7_SuR"  },
  { 0,  "TIMER8_SuR"  },
  { 0,  "TIMER9_SuR"  },
  { 0,  "TIMER10_SuR" },
  { 0,  "TIMER11_SuR" },
  { 0,  "TIMER12_SuR" },
  { 0,  "TIMER13_SuR" },
  { 0,  "TIMER14_SuR" },

  /*
   * Описание контрольных состояний устройств
   */
  { 0,  "UART1_CR"   },
  { 0,  "UART2_CR"   },
  { 0,  "UART3_CR"   },
  { 0,  "UART4_CR"   },

  { 0,  "CAN1_CR"    },
  { 0,  "CAN2_CR"    },

  { 0,  "SPI1_CR"    },
  { 0,  "SPI2_CR"    },
  { 0,  "SPI3_CR"    },

  { 0,  "BTS_CR"    },

  { 0,  "TIMER1_CR"  },
  { 0,  "TIMER2_CR"  },
  { 0,  "TIMER3_CR"  },
  { 0,  "TIMER4_CR"  },
  { 0,  "TIMER5_CR"  },
  { 0,  "TIMER6_CR"  },
  { 0,  "TIMER7_CR"  },
  { 0,  "TIMER8_CR"  },
  { 0,  "TIMER9_CR"  },
  { 0,  "TIMER10_CR" },
  { 0,  "TIMER11_CR" },
  { 0,  "TIMER12_CR" },
  { 0,  "TIMER13_CR" },
  { 0,  "TIMER14_CR" },

  { 0,  "TIMER1_INTERVAL"  },
  { 0,  "TIMER2_INTERVAL"  },
  { 0,  "TIMER3_INTERVAL"  },
  { 0,  "TIMER4_INTERVAL"  },
  { 0,  "TIMER5_INTERVAL"  },
  { 0,  "TIMER6_INTERVAL"  },
  { 0,  "TIMER7_INTERVAL"  },
  { 0,  "TIMER8_INTERVAL"  },
  { 0,  "TIMER9_INTERVAL"  },
  { 0,  "TIMER10_INTERVAL" },
  { 0,  "TIMER11_INTERVAL" },
  { 0,  "TIMER12_INTERVAL" },
  { 0,  "TIMER13_INTERVAL" },
  { 0,  "TIMER14_INTERVAL" },

  { 0,  "TIMER1_PRESCALER"  },
  { 0,  "TIMER2_PRESCALER"  },
  { 0,  "TIMER3_PRESCALER"  },
  { 0,  "TIMER4_PRESCALER"  },
  { 0,  "TIMER5_PRESCALER"  },
  { 0,  "TIMER6_PRESCALER"  },
  { 0,  "TIMER7_PRESCALER"  },
  { 0,  "TIMER8_PRESCALER"  },
  { 0,  "TIMER9_PRESCALER"  },
  { 0,  "TIMER10_PRESCALER" },
  { 0,  "TIMER11_PRESCALER" },
  { 0,  "TIMER12_PRESCALER" },
  { 0,  "TIMER13_PRESCALER" },
  { 0,  "TIMER14_PRESCALER" },

  /*
   * Описание состояний скорости передачи устройств
   */
  { 0,  "UART1_SPEED"   },
  { 0,  "UART2_SPEED"   },
  { 0,  "UART3_SPEED"   },
  { 0,  "UART4_SPEED"   },

  { 0,  "CAN1_SPEED"    },
  { 0,  "CAN2_SPEED"    },

  { 0,  "SPI1_SPEED"    },
  { 0,  "SPI2_SPEED"    },
  { 0,  "SPI3_SPEED"    },

  /*
   * Описание состояний программных буферов передачи устройств
   */
  { 0,  "UART1_RX_BL"   },
  { 0,  "UART1_TX_BL"   },
  { 0,  "UART2_RX_BL"   },
  { 0,  "UART2_TX_BL"   },
  { 0,  "UART3_RX_BL"   },
  { 0,  "UART3_TX_BL"   },
  { 0,  "UART4_RX_BL"   },
  { 0,  "UART4_TX_BL"   },

  { 0,  "CAN1_RX_BL"   },
  { 0,  "CAN1_TX_BL"   },
  { 0,  "CAN2_RX_BL"   },
  { 0,  "CAN2_TX_BL"   },

  { 0,  "SPI1_RX_BL"    },
  { 0,  "SPI1_TX_BL"    },
  { 0,  "SPI2_RX_BL"    },
  { 0,  "SPI2_TX_BL"    },
  { 0,  "SPI3_RX_BL"    },
  { 0,  "SPI3_TX_BL"    },

  /*
   * TODO: Описание полей статистики UART
   */
  { 0,  "UART1_CRC32_TX"      },
  { 0,  "UART1_CRC32_RX"      },
  { 0,  "UART1_SW_OV"         },
  { 0,  "UART1_HW_OV"         },
  { 0,  "UART1_HW_FE"         },
  { 0,  "UART1_HW_PE"         },
  { 0,  "UART1_TX_MSGS_LAST"  },
  { 0,  "UART1_RX_MSGS_LAST"  },
  { 0,  "UART1_TX_MSGS"       },
  { 0,  "UART1_RX_MSGS"       },

  { 0,  "UART2_CRC32_TX"      },
  { 0,  "UART2_CRC32_RX"      },
  { 0,  "UART2_SW_OV"         },
  { 0,  "UART2_HW_OV"         },
  { 0,  "UART2_HW_FE"         },
  { 0,  "UART2_HW_PE"         },
  { 0,  "UART2_TX_MSGS_LAST"  },
  { 0,  "UART2_RX_MSGS_LAST"  },
  { 0,  "UART2_TX_MSGS"       },
  { 0,  "UART2_RX_MSGS"       },

  { 0,  "UART3_CRC32_TX"      },
  { 0,  "UART3_CRC32_RX"      },
  { 0,  "UART3_SW_OV"         },
  { 0,  "UART3_HW_OV"         },
  { 0,  "UART3_HW_FE"         },
  { 0,  "UART3_HW_PE"         },
  { 0,  "UART3_TX_MSGS_LAST"  },
  { 0,  "UART3_RX_MSGS_LAST"  },
  { 0,  "UART3_TX_MSGS"       },
  { 0,  "UART3_RX_MSGS"       },

  { 0,  "UART4_CRC32_TX"      },
  { 0,  "UART4_CRC32_RX"      },
  { 0,  "UART4_SW_OV"         },
  { 0,  "UART4_HW_OV"         },
  { 0,  "UART4_HW_FE"         },
  { 0,  "UART4_HW_PE"         },
  { 0,  "UART4_TX_MSGS_LAST"  },
  { 0,  "UART4_RX_MSGS_LAST"  },
  { 0,  "UART4_TX_MSGS"       },
  { 0,  "UART4_RX_MSGS"       },


  /*
   * TODO: Описание полей статистики CAN
   */
  /*
   * TODO: Описание полей статистики SPI
   */
  /*
   * TODO: Описание полей статистики BTS
   */
  { 0,  "BTS_CFINT"           },
  { 0,  "BTS_CFEXT"           },

  /*
   * TODO: Описание полей статистики TIMER
   */

    { 0,  "TIMER1_EXEC_ISR_CNT"                 },
    { 0,  "TIMER1_TIMER_START_CNT"              },
    { 0,  "TIMER1_TIMER_STOP_CNT"               },
    { 0,  "TIMER1_MAX_ISR_START_DELAY"          },
    { 0,  "TIMER1_MAX_ISR_END_DELAY"            },
    { 0,  "TIMER1_START_STOP_ISR_CNT_ERROR"     },
    { 0,  "TIMER1_TIME_AT_START"                },
    { 0,  "TIMER1_TIME_AT_STOP"                 },
    { 0,  "TIMER1_MAX_ISR_EXEC_TIME"            },

  { 0,  "TIMER2_EXEC_ISR_CNT"                 },
  { 0,  "TIMER2_TIMER_START_CNT"              },
  { 0,  "TIMER2_TIMER_STOP_CNT"               },
  { 0,  "TIMER2_MAX_ISR_START_DELAY"          },
  { 0,  "TIMER2_MAX_ISR_END_DELAY"            },
  { 0,  "TIMER2_START_STOP_ISR_CNT_ERROR"     },
  { 0,  "TIMER2_TIME_AT_START"                },
  { 0,  "TIMER2_TIME_AT_STOP"                 },
  { 0,  "TIMER2_MAX_ISR_EXEC_TIME"            },

  { 0,  "TIMER3_EXEC_ISR_CNT"                 },
  { 0,  "TIMER3_TIMER_START_CNT"              },
  { 0,  "TIMER3_TIMER_STOP_CNT"               },
  { 0,  "TIMER3_MAX_ISR_START_DELAY"          },
  { 0,  "TIMER3_MAX_ISR_END_DELAY"            },
  { 0,  "TIMER3_START_STOP_ISR_CNT_ERROR"     },
  { 0,  "TIMER3_TIME_AT_START"                },
  { 0,  "TIMER3_TIME_AT_STOP"                 },
  { 0,  "TIMER3_MAX_ISR_EXEC_TIME"            },

  { 0,  "TIMER4_EXEC_ISR_CNT"                 },
  { 0,  "TIMER4_TIMER_START_CNT"              },
  { 0,  "TIMER4_TIMER_STOP_CNT"               },
  { 0,  "TIMER4_MAX_ISR_START_DELAY"          },
  { 0,  "TIMER4_MAX_ISR_END_DELAY"            },
  { 0,  "TIMER4_START_STOP_ISR_CNT_ERROR"     },
  { 0,  "TIMER4_TIME_AT_START"                },
  { 0,  "TIMER4_TIME_AT_STOP"                 },
  { 0,  "TIMER4_MAX_ISR_EXEC_TIME"            },

  { 0,  "TIMER5_EXEC_ISR_CNT"                 },
  { 0,  "TIMER5_TIMER_START_CNT"              },
  { 0,  "TIMER5_TIMER_STOP_CNT"               },
  { 0,  "TIMER5_MAX_ISR_START_DELAY"          },
  { 0,  "TIMER5_MAX_ISR_END_DELAY"            },
  { 0,  "TIMER5_START_STOP_ISR_CNT_ERROR"     },
  { 0,  "TIMER5_TIME_AT_START"                },
  { 0,  "TIMER5_TIME_AT_STOP"                 },
  { 0,  "TIMER5_MAX_ISR_EXEC_TIME"            },

  { 0,  "TIMER6_EXEC_ISR_CNT"                 },
  { 0,  "TIMER6_TIMER_START_CNT"              },
  { 0,  "TIMER6_TIMER_STOP_CNT"               },
  { 0,  "TIMER6_MAX_ISR_START_DELAY"          },
  { 0,  "TIMER6_MAX_ISR_END_DELAY"            },
  { 0,  "TIMER6_START_STOP_ISR_CNT_ERROR"     },
  { 0,  "TIMER6_TIME_AT_START"                },
  { 0,  "TIMER6_TIME_AT_STOP"                 },
  { 0,  "TIMER6_MAX_ISR_EXEC_TIME"            },

  { 0,  "TIMER7_EXEC_ISR_CNT"                 },
  { 0,  "TIMER7_TIMER_START_CNT"              },
  { 0,  "TIMER7_TIMER_STOP_CNT"               },
  { 0,  "TIMER7_MAX_ISR_START_DELAY"          },
  { 0,  "TIMER7_MAX_ISR_END_DELAY"            },
  { 0,  "TIMER7_START_STOP_ISR_CNT_ERROR"     },
  { 0,  "TIMER7_TIME_AT_START"                },
  { 0,  "TIMER7_TIME_AT_STOP"                 },
  { 0,  "TIMER7_MAX_ISR_EXEC_TIME"            },

  { 0,  "TIMER8_EXEC_ISR_CNT"                 },
  { 0,  "TIMER8_TIMER_START_CNT"              },
  { 0,  "TIMER8_TIMER_STOP_CNT"               },
  { 0,  "TIMER8_MAX_ISR_START_DELAY"          },
  { 0,  "TIMER8_MAX_ISR_END_DELAY"            },
  { 0,  "TIMER8_START_STOP_ISR_CNT_ERROR"     },
  { 0,  "TIMER8_TIME_AT_START"                },
  { 0,  "TIMER8_TIME_AT_STOP"                 },
  { 0,  "TIMER8_MAX_ISR_EXEC_TIME"            },

  { 0,  "TIMER9_EXEC_ISR_CNT"                 },
  { 0,  "TIMER9_TIMER_START_CNT"              },
  { 0,  "TIMER9_TIMER_STOP_CNT"               },
  { 0,  "TIMER9_MAX_ISR_START_DELAY"          },
  { 0,  "TIMER9_MAX_ISR_END_DELAY"            },
  { 0,  "TIMER9_START_STOP_ISR_CNT_ERROR"     },
  { 0,  "TIMER9_TIME_AT_START"                },
  { 0,  "TIMER9_TIME_AT_STOP"                 },
  { 0,  "TIMER9_MAX_ISR_EXEC_TIME"            },

  { 0,  "TIMER10_EXEC_ISR_CNT"                 },
  { 0,  "TIMER10_TIMER_START_CNT"              },
  { 0,  "TIMER10_TIMER_STOP_CNT"               },
  { 0,  "TIMER10_MAX_ISR_START_DELAY"          },
  { 0,  "TIMER10_MAX_ISR_END_DELAY"            },
  { 0,  "TIMER10_START_STOP_ISR_CNT_ERROR"     },
  { 0,  "TIMER10_TIME_AT_START"                },
  { 0,  "TIMER10_TIME_AT_STOP"                 },
  { 0,  "TIMER10_MAX_ISR_EXEC_TIME"            },

  { 0,  "TIMER11_EXEC_ISR_CNT"                 },
  { 0,  "TIMER11_TIMER_START_CNT"              },
  { 0,  "TIMER11_TIMER_STOP_CNT"               },
  { 0,  "TIMER11_MAX_ISR_START_DELAY"          },
  { 0,  "TIMER11_MAX_ISR_END_DELAY"            },
  { 0,  "TIMER11_START_STOP_ISR_CNT_ERROR"     },
  { 0,  "TIMER11_TIME_AT_START"                },
  { 0,  "TIMER11_TIME_AT_STOP"                 },
  { 0,  "TIMER11_MAX_ISR_EXEC_TIME"            },

  { 0,  "TIMER12_EXEC_ISR_CNT"                 },
  { 0,  "TIMER12_TIMER_START_CNT"              },
  { 0,  "TIMER12_TIMER_STOP_CNT"               },
  { 0,  "TIMER12_MAX_ISR_START_DELAY"          },
  { 0,  "TIMER12_MAX_ISR_END_DELAY"            },
  { 0,  "TIMER12_START_STOP_ISR_CNT_ERROR"     },
  { 0,  "TIMER12_TIME_AT_START"                },
  { 0,  "TIMER12_TIME_AT_STOP"                 },
  { 0,  "TIMER12_MAX_ISR_EXEC_TIME"            },

  { 0,  "TIMER13_EXEC_ISR_CNT"                 },
  { 0,  "TIMER13_TIMER_START_CNT"              },
  { 0,  "TIMER13_TIMER_STOP_CNT"               },
  { 0,  "TIMER13_MAX_ISR_START_DELAY"          },
  { 0,  "TIMER13_MAX_ISR_END_DELAY"            },
  { 0,  "TIMER13_START_STOP_ISR_CNT_ERROR"     },
  { 0,  "TIMER13_TIME_AT_START"                },
  { 0,  "TIMER13_TIME_AT_STOP"                 },
  { 0,  "TIMER13_MAX_ISR_EXEC_TIME"            },

  { 0,  "TIMER14_EXEC_ISR_CNT"                 },
  { 0,  "TIMER14_TIMER_START_CNT"              },
  { 0,  "TIMER14_TIMER_STOP_CNT"               },
  { 0,  "TIMER14_MAX_ISR_START_DELAY"          },
  { 0,  "TIMER14_MAX_ISR_END_DELAY"            },
  { 0,  "TIMER14_START_STOP_ISR_CNT_ERROR"     },
  { 0,  "TIMER14_TIME_AT_START"                },
  { 0,  "TIMER14_TIME_AT_STOP"                 },
  { 0,  "TIMER14_MAX_ISR_EXEC_TIME"            },

    { 0,  "BTS_YEAR"          },
    { 0,  "BTS_DAY"           },
    { 0,  "BTS_HOUR"          },
    { 0,  "BTS_MINUTE"        },
    { 0,  "BTS_SECOND"        },


  /*
   * Пользовательские регистры
   */
  { 0,  "UReg1" },
  { 0,  "UReg2" },
  { 0,  "UReg3" },
  { 0,  "UReg4" },
  { 0,  "UReg5" },
  { 0,  "UReg6" },
  { 0,  "UReg7" },
  { 0,  "UReg8" },


  /*
   * Регистры работы с портами ввода\вывода
   */
  { 0,  "PORTA"   },
  { 0,  "PORTB"   },
  { 0,  "PORTC"   },
  { 0,  "PORTD"   },

  { 0,  "DDRA"   },
  { 0,  "DDRB"   },
  { 0,  "DDRC"   },
  { 0,  "DDRD"   },

  { 0,  "PORTA_CNT"   },
  { 0,  "PORTB_CNT"   },
  { 0,  "PORTC_CNT"   },
  { 0,  "PORTD_CNT"   },


  { 0,   "0" }
};

