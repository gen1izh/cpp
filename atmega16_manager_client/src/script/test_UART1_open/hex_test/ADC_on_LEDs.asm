
_main:
	LDI        R27, 255
	OUT        SPL+0, R27
	LDI        R27, 0
	OUT        SPL+1, R27

;ADC_on_LEDs.c,4 :: 		void main() {
;ADC_on_LEDs.c,5 :: 		int i=0;
	PUSH       R2
	PUSH       R3
	PUSH       R4
	PUSH       R5
	PUSH       R6
;ADC_on_LEDs.c,6 :: 		int j=0;
;ADC_on_LEDs.c,7 :: 		int iu=0;
;ADC_on_LEDs.c,9 :: 		DDRB = 0xFF;
	LDI        R27, 255
	OUT        DDRB+0, R27
;ADC_on_LEDs.c,11 :: 		UART1_Init(9600);               // Initialize UART module at 9600 bps
	LDI        R27, 51
	OUT        UBRRL+0, R27
	LDI        R27, 0
	OUT        UBRRH+0, R27
	CALL       _UART1_Init+0
;ADC_on_LEDs.c,12 :: 		Delay_ms(100);                  // Wait for UART module to stabilize
	LDI        R18, 5
	LDI        R17, 15
	LDI        R16, 242
L_main0:
	DEC        R16
	BRNE       L_main0
	DEC        R17
	BRNE       L_main0
	DEC        R18
	BRNE       L_main0
;ADC_on_LEDs.c,14 :: 		while (1) {
L_main2:
;ADC_on_LEDs.c,15 :: 		if (UART1_Data_Ready() == 1) {          // if data is received
	CALL       _UART1_Data_Ready+0
	CPI        R16, 1
	BREQ       L__main14
	JMP        L_main4
L__main14:
;ADC_on_LEDs.c,16 :: 		UART1_Read_Text(packet, " ", 10);    // reads text until 'OK' is found
	LDI        R27, 10
	MOV        R6, R27
	LDI        R27, #lo_addr(?lstr1_ADC_on_LEDs+0)
	MOV        R4, R27
	LDI        R27, hi_addr(?lstr1_ADC_on_LEDs+0)
	MOV        R5, R27
	LDI        R27, #lo_addr(_packet+0)
	MOV        R2, R27
	LDI        R27, hi_addr(_packet+0)
	MOV        R3, R27
	CALL       _UART1_Read_Text+0
;ADC_on_LEDs.c,18 :: 		if ((packet[0] == 0x11)&&(packet[1] == 0x01)
	LDS        R16, _packet+0
	CPI        R16, 17
	BREQ       L__main15
	JMP        L__main12
L__main15:
	LDS        R16, _packet+1
	CPI        R16, 1
	BREQ       L__main16
	JMP        L__main11
L__main16:
;ADC_on_LEDs.c,19 :: 		&&(packet[2] == 0x00)&&(packet[3] == 0x55) ) {
	LDS        R16, _packet+2
	CPI        R16, 0
	BREQ       L__main17
	JMP        L__main10
L__main17:
	LDS        R16, _packet+3
	CPI        R16, 85
	BREQ       L__main18
	JMP        L__main9
L__main18:
L__main8:
;ADC_on_LEDs.c,20 :: 		packet[0]  = 0x11;
	LDI        R27, 17
	STS        _packet+0, R27
;ADC_on_LEDs.c,21 :: 		packet[1]  = 0x01;
	LDI        R27, 1
	STS        _packet+1, R27
;ADC_on_LEDs.c,22 :: 		packet[2]  = 0x04;
	LDI        R27, 4
	STS        _packet+2, R27
;ADC_on_LEDs.c,23 :: 		packet[3]  = 0x00;
	LDI        R27, 0
	STS        _packet+3, R27
;ADC_on_LEDs.c,24 :: 		packet[4]  = 0x00;
	LDI        R27, 0
	STS        _packet+4, R27
;ADC_on_LEDs.c,25 :: 		packet[5]  = 0x01;
	LDI        R27, 1
	STS        _packet+5, R27
;ADC_on_LEDs.c,26 :: 		packet[6]  = 0x23;
	LDI        R27, 35
	STS        _packet+6, R27
;ADC_on_LEDs.c,27 :: 		packet[7]  = 0x59;
	LDI        R27, 89
	STS        _packet+7, R27
;ADC_on_LEDs.c,28 :: 		packet[8]  = 0xaa;
	LDI        R27, 170
	STS        _packet+8, R27
;ADC_on_LEDs.c,29 :: 		UART1_Write(packet[0]);
	LDS        R2, _packet+0
	CALL       _UART1_Write+0
;ADC_on_LEDs.c,30 :: 		UART1_Write(packet[1]);
	LDS        R2, _packet+1
	CALL       _UART1_Write+0
;ADC_on_LEDs.c,31 :: 		UART1_Write(packet[2]);
	LDS        R2, _packet+2
	CALL       _UART1_Write+0
;ADC_on_LEDs.c,32 :: 		UART1_Write(packet[3]);
	LDS        R2, _packet+3
	CALL       _UART1_Write+0
;ADC_on_LEDs.c,33 :: 		UART1_Write(packet[4]);
	LDS        R2, _packet+4
	CALL       _UART1_Write+0
;ADC_on_LEDs.c,34 :: 		UART1_Write(packet[5]);
	LDS        R2, _packet+5
	CALL       _UART1_Write+0
;ADC_on_LEDs.c,35 :: 		UART1_Write(packet[6]);
	LDS        R2, _packet+6
	CALL       _UART1_Write+0
;ADC_on_LEDs.c,36 :: 		UART1_Write(packet[7]);
	LDS        R2, _packet+7
	CALL       _UART1_Write+0
;ADC_on_LEDs.c,37 :: 		UART1_Write(packet[8]);
	LDS        R2, _packet+8
	CALL       _UART1_Write+0
;ADC_on_LEDs.c,18 :: 		if ((packet[0] == 0x11)&&(packet[1] == 0x01)
L__main12:
L__main11:
;ADC_on_LEDs.c,19 :: 		&&(packet[2] == 0x00)&&(packet[3] == 0x55) ) {
L__main10:
L__main9:
;ADC_on_LEDs.c,39 :: 		}
L_main4:
;ADC_on_LEDs.c,41 :: 		}
	JMP        L_main2
;ADC_on_LEDs.c,57 :: 		}
L_end_main:
L__main_end_loop:
	JMP        L__main_end_loop
; end of _main
