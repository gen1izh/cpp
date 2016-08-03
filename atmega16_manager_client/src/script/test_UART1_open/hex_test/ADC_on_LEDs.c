
char  packet[100];

void main() {
  int i=0;
  int j=0;
  int iu=0;

DDRB = 0xFF;

  UART1_Init(9600);               // Initialize UART module at 9600 bps
  Delay_ms(100);                  // Wait for UART module to stabilize
  
  while (1) {
    if (UART1_Data_Ready() == 1) {          // if data is received
    UART1_Read_Text(packet, " ", 10);    // reads text until 'OK' is found
    
    if ((packet[0] == 0x11)&&(packet[1] == 0x01)
    &&(packet[2] == 0x00)&&(packet[3] == 0x55) ) {
      packet[0]  = 0x11;
      packet[1]  = 0x01;
      packet[2]  = 0x04;
      packet[3]  = 0x00;
      packet[4]  = 0x00;
      packet[5]  = 0x01;
      packet[6]  = 0x23;
      packet[7]  = 0x59;
      packet[8]  = 0xaa;
      UART1_Write(packet[0]);
      UART1_Write(packet[1]);
      UART1_Write(packet[2]);
      UART1_Write(packet[3]);
      UART1_Write(packet[4]);
      UART1_Write(packet[5]);
      UART1_Write(packet[6]);
      UART1_Write(packet[7]);
      UART1_Write(packet[8]);
    }
 }

}

   
//   while  (UART1_Data_Ready())  {
//      packet[i] = UART1_Read();
//      i++;
//   }
//   Delay_ms(100);
//   j=0;
//   while (i>0) {
//    UART1_Write(packet[j]);
//    j++;
//    i--;
//   }
   

  }