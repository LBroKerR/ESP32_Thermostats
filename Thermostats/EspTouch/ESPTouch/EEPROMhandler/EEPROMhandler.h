#pragma once
#ifndef EEPROMHANDLER_H
#define EEPROMHANDLER_H

#include <Arduino.h>
#include <EEPROM.h>
#define ESPTOUCH       1
#define ESPCARRY       0  

#if(ESPCARRY && !ESPTOUCH)
    #define EEPROM_SIZE      0x0080 // 84 byte needed-> allocate 128 byte
    #define USER             0x0000	// wifi data addresses
    #define PW               0x0017
    #define UPSIZE           0x0015
    #define IP               0x002E
    #define HOST             0x0040 //unsigned
    #define ENABLE           0x0044 // bool
    #define IPSIZE           0x0010

    #define HOUR             0x0045	// other data addresses // unsigned
    #define MIN              0x0049 // unsigned
    #define PROG             0x004D	//active prog // unsigned
    #define TMPOFFSET        0x0051 //double
    #define NICKNAME         0x0059 //string
    #define NAMESIZE         0x0009
    #define HEATING_CIRLE_ID 0x0063 //unsigned
    #define NUMBER_OF_HEATING_CIRLE 0x0067
#endif
#if(ESPTOUCH && !ESPCARRY)
    #define EEPROM_SIZE      0x0450 // 84 byte needed-> allocate 128 byte
    #define FPROG1           0x0000	// daily programs addresses
    #define FPROG2           0x00C0	// contain 24 double data/ daily program. 
    #define FPROG3           0x0180
    #define FPROG4           0x0240
    #define FPROG5           0x0301
    #define PSIZE            0x0018
    #define NEXT             0x0008

    #define USER             0x03C1	// wifi data addresses
    #define PW               0x03D6
    #define UPSIZE           0x0015
    #define IP               0x03EB
    #define HOST             0x03FB //unsigned
    #define ENABLE           0x03FF // bool
    #define IPSIZE           0x0010

    #define HOUR             0x0400	// other data addresses // unsigned
    #define MIN              0x0404 // unsigned
    #define PROG             0x0408	//active prog // unsigned
    #define TMPOFFSET        0x040C //double
    #define NICKNAME         0x0414 //string
    #define NAMESIZE         0x0009
    #define HEATING_CIRLE_ID 0x041D //unsigne
    #define NUMBER_OF_HEATING_CIRLE 0x0421 //unsigned
    #define HEATING_MODE     0x0428 //bool
    #define MODBUS_ID        0x0429                //uint
    #define MODBUS_REGISTER_ADDRESS   0x042D              //uint
    #define MODBUS_REGISTER_NUMBER    0x0431               //uint
#endif


    bool isnumber(String);
//setters
    void MywriteString(unsigned address, String str);
    String MyreadString(unsigned address, unsigned size);
// bool function_name(void*param) is the functions that can be added to a menu as function variable. 
    bool check_Nickname_datagramm(void* param);
    bool check_ID_datagramm(void* param);
    bool check_IP_datagramm(void* param);
    bool check_host_datagramm(void* param);
    bool check_pass_datagramm(void* param);
    bool check_user_datagramm(void* param);
    bool check_switch_datagramm(void* param);
    bool check_temp_datagramm(void* param);

    //auto and manualy override enabled.
    bool write_out_clock(unsigned, unsigned);
    bool check_clock_datagramm(void* param);
    bool check_hour_datagramm(void* param);
    bool check_min_datagramm(void* param); 
#if(ESPTOUCH && !ESPCARRY)
    bool check_modbus_id(void* param);
    bool check_modbus_register_address(void* param);
    bool check_modbus_register_number(void* param);
#endif
    //autosave
    bool write_out_active_program_number(unsigned param);
#if(ESPTOUCH && !ESPCARRY)
    bool write_out_full_program(unsigned index, double* program);
    void save_heating_mode(bool param);
#endif 
    bool check_number_of_heating_circle_datagramm(void * param);
    bool Hardreset(void*parma);

    bool print(void*);
//getters
    bool getSwitch();
    unsigned getActiveprog();
    void getClock(unsigned*, unsigned*);
#if(ESPTOUCH && !ESPCARRY)
    bool getProgram(unsigned, double *);
    bool read_heating_mode();
#endif 
    unsigned getNumber_of_heating_circle();
    double getOffset();
    unsigned getHost();
    String getUser(unsigned size);
    String getPASS(unsigned size);
    String getIP();
    String getName();
    unsigned getID();
#if(ESPTOUCH && !ESPCARRY)
    unsigned get_modbus_id();
    unsigned get_modbus_register_address();
    unsigned get_modbus_register_number();
#endif


#endif //EEPROMHANDLER_H


/// <basics>
///  carefully choosing the EEPROM size and minimalizing write operations, you can effectively use the emulated EEPROM for storing persistent data on the ESP32.
/// ESP32 do not has EEPROM directly, it is emulated in flash memory.
/// Flash memory is 4-16 MB, it is depend on used modell.
/// get to know where is the free memory space!!! 

/// stored data in eeprom:(recommended, if it is not a 1 byte data)
/// 
///		0. #include <EEPROM.h>
///		1. size of the data -> x bytes
///		2. data -> y bytes
/// 
/// write:
/// 
///		address -> start point of data frame
///		data -> x bytes
/// 
/// read:
/// 
///		read from address
/// 
/// Warnings: 
/// 
///		each type of data stored differently
///		eeprom storing data byte by byte
///		Therefor becarefull about how you store a data.
///			Think about the size of data type, for example float is 32 bit, or 4 bytes. 
///			This means that float needs minimum of 5 byte to store, 1 for the size, 4  for the dataframe.
/// 
/// bonus:
/// 
///		Callculate the minimum needed size of the eeprom, and define it at the starting point!
///			sort local datas in order of importance, and pick few data which need to run the device perfectly after a hard reset, or power lost.
///			Callculate each data size and store it  in  recommeneded way
/// 
///		store the address of the datas, or define each datas starting points(address).
/// 
/// data types:
/// 
///		bool:			1 byte
///		int:			4 bytes
///		unsigned int:	4 bytes
///		double:			8 bytes
///		float:			4 bytes
///		char:			1 byte
///		string:			24 bytes
///		array-s:		as many as the number of data stored in the array, and specified by the data type.
/// 
/// stored data:							unit(s)/byte(s)
/// 
///		char array: 
/// 
///		>*	IP: 255.255.255.255 -> 1+15 char	16x1
///		>*	SSID: 1+ max 10 char				11x1
///		>*	PassWord: 1+ max 10 char			11x1
/// 
///		int:
/// 
///		>*	host								1x4
///		>	active program index				1x4
///		>	clock: hour and minute				2x4
///		
///		float:
/// 
///		*	temperature offset	1				1x4
///		>	temperature offset	2				1x4
///		*	humidity offset		1				1x4
///		>	humidity offset		2				1x4
///		>	5x24 programable data				120x8
/// 
///		Summa for a minimum EEPROM size:
/// 
///			EspTouch(>):  						
///			EspCarryable(*):					
/// 
///			
/// </basics>


/// <defines>
/// 
/// memory accesspoints for each data defined in a <file_name>.cpp
/// 
///	#define IP	
///	#define SSID
/// #define PW
/// #define HOST
/// 
/// #define ACTIVEPROG
/// #define PROGS
/// 
/// #define HOUR
/// #define MINUTE
/// 
/// #define TMP_OFFSET //espcarry
/// 
/// #define TMP_OFFSET //esptouch
/// 
/// </defines>

/// <example code>
/// 
/// #include <EEPROM.h>
/// 
/// // Define the EEPROM size (in bytes)
/// #define EEPROM_SIZE 1024  // For example, 1 KB
/// 
/// void main(){
/// Serial.begin(115200);
///
///  // Initialize EEPROM with the defined size
/// if (!EEPROM.begin(EEPROM_SIZE)) {
///	 Serial.println("Failed to initialize EEPROM"); //-> log out to a file with date, Then reset board!
///	 return;
/// }
///
/// // Example write and commit
/// EEPROM.write(0, 123);  // Write a value to the EEPROM
/// EEPROM.commit();  // Commit the changes/save
///
/// // Example read
/// int value = EEPROM.read(0);  // Read the value back
/// Serial.print("Read value: ");
/// Serial.println(value);
/// }
/// </example code>