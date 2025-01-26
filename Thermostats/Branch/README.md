# TO DO:
    - Flag bool vars change to mutex vars!!
        - TemperatureMeasuirng.cpp: changed vars shall set to mutex var!! 

        error log: 

13:45:33.087 -> measuringTask
13:45:33.294 -> 

13:45:33.294 -> sensor1
13:45:33.294 -> sensor2
13:45:33.294 -> clock1
13:45:33.294 -> clock2
13:45:33.294 -> Wifi Task
13:45:33.294 -> 

13:45:33.294 -> SaveTask
13:45:33.294 -> 

13:45:33.523 -> ModbusCommunicationTask
13:45:33.523 -> 

13:45:33.523 -> measuringTask
13:45:33.707 -> 

13:45:33.707 -> sensor1

// ERROR log

13:45:34.051 -> Guru Meditation Error: Core  0 panic'ed (Interrupt wdt timeout on CPU0). 
13:45:34.051 -> 
13:45:34.051 -> Core  0 register dump:
13:45:34.051 -> PC      : 0x401257e9  PS      : 0x00060135  A0      : 0x800dc94c  A1      : 0x3ffaf900  
13:45:34.051 -> A2      : 0x0000001b  A3      : 0x00000000  A4      : 0x59cfe4fd  A5      : 0x08000000  
13:45:34.051 -> A6      : 0x00000028  A7      : 0xff000000  A8      : 0x801257f6  A9      : 0x3ffaf8d0  
13:45:34.085 -> A10     : 0x00000001  A11     : 0x00000001  A12     : 0x00000027  A13     : 0x3ffd3df8  
13:45:34.085 -> A14     : 0x0016fdb9  A15     : 0x00000000  SAR     : 0x0000001b  EXCCAUSE: 0x00000005  
13:45:34.085 -> EXCVADDR: 0x00000000  LBEG    : 0x40084b5d  LEND    : 0x40084b65  LCOUNT  : 0x00000027  
13:45:34.085 -> 
13:45:34.085 -> 
 Backtrace: 0x401257e6:0x3ffaf900 0x400dc949:0x3ffaf920 0x400dca45:0x3ffaf940 0x400dcb17:0x3ffafaa0 0x400d6bfc:0x3ffafad0 0x400d6cd9:0x3ffafaf0 0x400d967d:0x3ffafb10 0x4008ff6a:0x3ffafba0

 13:45:34.118 -> Core  1 register dump:
13:45:34.118 -> PC      : 0x400901a8  PS      : 0x00060f35  A0      : 0x8008e03c  A1      : 0x3ffb21a0  
13:45:34.118 -> A2      : 0x0000abab  A3      : 0x00060f20  A4      : 0x00000004  A5      : 0x00060f23  
13:45:34.118 -> A6      : 0xb33fffff  A7      : 0xb33fffff  A8      : 0xb33fffff  A9      : 0x0000abab  
13:45:34.151 -> A10     : 0x00060f23  A11     : 0x0000009c  A12     : 0x00000004  A13     : 0x3f4393f8  
13:45:34.151 -> A14     : 0xb33fffff  A15     : 0xb33fffff  SAR     : 0x00000004  EXCCAUSE: 0x00000005  
13:45:34.151 -> EXCVADDR: 0x00000000  LBEG    : 0x4008ae5d  LEND    : 0x4008ae6d  LCOUNT  : 0xfffffff9  
13:45:34.151 -> 
13:45:34.151 -> 
Backtrace: 0x400901a5:0x3ffb21a0 0x4008e039:0x3ffb21c0 0x40127b22:0x3ffb2200 0x40121979:0x3ffb2230 0x40121a1e:0x3ffb2250 0x40128610:0x3ffb2270 0x4008ff6a:0x3ffb2290

// simple reboot

13:45:34.188 -> ELF file SHA256: 02dccd5c69247821
13:45:34.188 -> 
13:45:34.297 -> Rebooting...
13:45:34.297 -> ets Jul 29 2019 12:21:46
13:45:34.297 -> 
13:45:34.297 -> rst:0xc (SW_CPU_RESET),boot:0x13 (SPI_FAST_FLASH_BOOT)
13:45:34.297 -> configsip: 0, SPIWP:0xee
13:45:34.297 -> clk_drv:0x00,q_drv:0x00,d_drv:0x00,cs0_drv:0x00,hd_drv:0x00,wp_drv:0x00
13:45:34.344 -> mode:DIO, clock div:1
13:45:34.344 -> load:0x3fff0030,len:4832
13:45:34.344 -> load:0x40078000,len:16460
13:45:34.344 -> load:0x40080400,len:4
13:45:34.344 -> load:0x40080404,len:3504
13:45:34.344 -> entry 0x400805cc