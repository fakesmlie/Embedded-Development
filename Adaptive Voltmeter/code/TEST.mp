NOTE: AVR Code addresses are word addresses
All other addresses (including ones in FLASH) are byte addresses

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             lit   00E4   0020 =     32. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       00E4  __lit_start
       0104  __lit_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                           idata   0104   0031 =     49. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0104  __idata_start
       0135  __idata_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   0136   0BC0 =   3008. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       009B  __start
       009B  __text_start
       00BD  _exit
       00BE  _main
       01D9  _LED_Init
       01E0  _LED_open
       01FF  _Key_Init
       0204  _Key_1
       020F  _Key_2
       021A  _delay_ms
       022D  _Delay_1ms
       0238  _Nixie_Init
       024A  _Nixie
       0293  _ADC_Init
       029F  _switch_open
       02B8  _voltage_AD
       02EA  _ADC_show
       031C  _UART_Init
       033E  _USART_Send
       0345  _UART_Send_String
       0356  _USART_Send_voltage
       0387  mod16s
       038B  div16s
       03A5  mod16u
       03A7  div16u
       03A8  xdiv16u
       03C1  mod8u
       03C3  div8u
       03C4  xdiv8u
       03D9  elpm32
       03ED  empy16s
       03FD  push_xgsetF000
       0402  pop_xgsetF000
       0407  push_xgset303C
       040E  pop_xgset303C
       0415  neg32
       041E  fpsub
       0420  fpadd
       0421  fpadd_alt
       0488  fpsub2
       0493  fpint
       04C5  uint2fp
       04C7  int2fp
       04D0  ulong2fp
       04D2  long2fp
       04E9  fpdiv1
       04F2  fpdiv2
       04FC  fpdiv1x
       0508  fpdiv2x
       0583  unpacks
       058B  tstR16_R19
       0593  unpacku
       05AC  normalize_and_pack
       05E1  pack
       05F1  saveFPRegs
       0600  restoreFPRegs
       060F  fpmule
       0662  fpmule2
       066D  fpmule2x
       067B  __text_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            data   0200   0031 =     49. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0200  __data_start
       0212  _NixieTable
       0231  __data_end

Area                               Start  End    Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                          vector   0000   0004 =      4. bytes (abs,ovr,rom)

Files Linked      [ module(s) ]

C:\iccv7avr\lib\crtatmega.o	[ crtatmega.s ]
main.o	[ main.c ]
led.o	[ led.c ]
key.o	[ key.c ]
Nixie.o	[ Nixie.c ]
ADC.o	[ ADC.c ]
UART.o	[ UART.c ]
<library>	[ div16s.s, div16u.s, div8u.s, elpm32.s, emul16s.s, gpushy.s, gpusha.s, lneg.s, fpadd.s, fpsub2.s, fpint.s ]
[ int2fp.s, fpdiv_new.s, fputil.s, fpmule.s, fpmule2.s, fpmule2x.s ]

User Global Definitions

ram_end = 0x21ff
hwstk_size = 0x1e

User Base Address Definitions

func_lit = 0xe4
data = 0x200
eeprom:0.4096

