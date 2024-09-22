#include "EEPROMHandler.h"
//private functions:

  bool isnumber(String str){
    bool decimalPointFound = false;
    int len = str.length();
    if (len == 0) {
      return false;
    }
    int startIndex=0;
    if(str[0]=='-'){ // Allow first character to be a negative sign
      startIndex=1;
    }
    for (int i = startIndex; i < len; i++) {
      if (str[i] == '.') {
        if (decimalPointFound) {// More than one decimal point
          return false;
        }
        decimalPointFound = true;
      } 
      else if (!isDigit(str[i])) {// Not a digit or decimal point
        return false;
      }
    }
    return true;//if all character correctly create a number, int, uint, double, float
  }
  /// <MywriteString>
  /// !! write out a String, char by char, or byte by byte. 
  /// </MywriteString>
  void MywriteString(unsigned address, String str) {
      for (int i = 0; i < str.length(); i++) {
          EEPROM.write(address + i, str[i]);  //write to eeprom 
      }

      EEPROM.write(address + str.length(), '\0'); // closing 
      EEPROM.commit();  // save to eeprom
  }
  /// < MyreadString>
  /// !! read char from address, save it in a char array, then return it as a String
  /// </ MyreadString>
  String MyreadString(unsigned address, unsigned size) {
      char str[size];
      int i = 0;
      char c;
      // reading while not reaching the closing
      while ((c = EEPROM.read(address + i)) != '\0' && i < (size-1)) {
          str[i] = c;
          i++;
      }
      str[i] = '\0';  // closing 
      return String(str);
  }

//public functions:
        //need to check all data before dot(.) 
        //is it number? smaller then 255, bigger then 0? need?>>if smaller then 100 has 0 before the number?
        //return false, if not correct form, or data/ nullptr comes
        //return true, if EEPROM.write.. successfully done
bool check_IP_datagramm(void* param){
  String *str = (String*)param;
  if (str == nullptr) {
    return false;
  }
  else {
      int octets = 0, value = 0;
      for (int i = 0; i < str->length(); i++) {
          char c = (*str)[i];
          if (c == '.') {
              if (++octets > 3 || value > 255) return false;
              value = 0;
          }
          else if (c >= '0' && c <= '9') {
              value = value * 10 + (c - '0');
          }
          else {
              return false;
          }
      }
      if (octets == 3 && value <= 255) {
          MywriteString(IP, *str);
          return true;
      }
  }
    return false;
}

    bool check_host_datagramm(void* param){
        String *str=(String*)param;
        unsigned host=0;
        if(str==nullptr){
          return false;
        }
        if(!isnumber(*str)){
          return false;
        }
        host=str->toInt();
        if(host<1024 || host >-1){
          return false;
        }
        EEPROM.writeUInt(HOST,host);
        EEPROM.commit();
        return true;
    }

    bool check_pass_datagramm(void* param){
        String *str=(String*)param;
        if(str==nullptr){
            return false;
        }
        if(str->length()<=UPSIZE){
            MywriteString(PW, *str);
            return true;
        }
        return false;
    }

    bool check_user_datagramm(void* param){
        String *str=(String*)param;
        if(str==nullptr){
            return false;
        }
        if (str->length() <= UPSIZE) {
            MywriteString(USER, *str);
            return true;
        }
        return true;
    }

    bool check_switch_datagramm(void* param){
        String *str=(String*)param;
        if(str==nullptr){
            return false;
        }
        if(*str=="enable"){
            EEPROM.writeBool(ENABLE, true);
        }
        else if(*str=="disable"){
            EEPROM.writeBool(ENABLE, false);
        }
        else{
            return false;
        }   
        EEPROM.commit();
        return true;
    }

    bool check_temp_datagramm(void* param){
        String *str=(String*)param;
        double temp=0.0;
        if(str==nullptr){
            return false;
        }
        if(!isnumber(*str)){
          return false;
        }
        temp=str->toDouble();
        if(temp>=-10 && temp <=10){
          EEPROM.writeDouble(TMPOFFSET,temp);
          EEPROM.commit();
          return true;
        }
        return false;
    }
    bool write_out_clock(unsigned hour, unsigned min){
        EEPROM.writeUInt(HOUR, hour);
        EEPROM.writeUInt(MIN, min);
        EEPROM.commit();
        return true;
    }
    bool check_clock_datagramm(void* param){
        String* str = (String*)param;
        if (str == nullptr || str->length() < 5) {
            return false;
        }
        unsigned hour = 0, min = 0;
        char* endptr;
        hour = strtol(str->c_str(), &endptr, 10);
        if (endptr == str->c_str() || hour >= 24) {
            return false; 
        }
        min = strtol(endptr, &endptr, 10);
        if (endptr == str->c_str() || min >= 60) {
            return false; 
        }
        return write_out_clock(hour, min);
    }
// will be part of the autosave functions!
    bool write_out_active_program_number(unsigned param){
        if (param < 5 && param >= 0) {
            EEPROM.writeUInt(PROG, param);
            EEPROM.commit();
            return true;
        }
        return false;
    }

    bool write_out_full_program(unsigned index, double* program){
        unsigned address=0;
        switch (index){
            case 0:address=FPROG1;break;
            case 1:address=FPROG2;break;
            case 2:address=FPROG3;break;
            case 3:address=FPROG4;break;
            case 4:address=FPROG5;break;
            default: return false;
        }
        for(unsigned i=0; i<PSIZE; i++){
            EEPROM.writeDouble(address, program[i]);
            address+=NEXT;
        }
        EEPROM.commit();
        return true;
    }

    bool Hardreset(void*param){
       String* str = (String*)param;
       if(str!=nullptr){
          if(*str==getPASS(UPSIZE)){
            for(unsigned i=FPROG1; i< EEPROM_SIZE; i++){
              EEPROM.writeBool(i, false);
            }
            EEPROM.commit();
            return true;
          }
        }
      *str="\n\rType like 'Hardreset PASSWORD' if you want to clear EEPROM.\n\r";
      param=str;
      return false;
    }

    // print out all the data from eeprom to serial port, except full programs.
    // use like "read PASSWORD" if you want to see the password
    bool print(void* param){
      String*str=(String*)param;
      bool showPW = false;
      unsigned hourtmp = 0, mintmp = 0;
      if (str != nullptr) {
          if (*str == getPASS(UPSIZE)) {
              showPW = true;
          }
          *str = "";
          *str += "\n\r IP address: "+ getIP() + "\n\r Username: "+getUser(UPSIZE)+ "\n\r password: ";
          if (!showPW) {
              *str += "**********";
          }
          else {
              *str += getPASS(UPSIZE);
          }
          *str += "\n\r HOST: "+ String(getHost())+"\n\r Wifi state: ";
          if (getSwitch()) {
              *str += "Enabled";
          }
          else {
              *str += "Disabled";
          }
          *str += "\n\r Offset for temperature sensor: "+ String(getOffset())+ "°C"+ "\n\r Last saved Time: ";
          getClock(&hourtmp, &mintmp);
          *str += String(hourtmp) + " " + String(mintmp) + "\n\r Last active program: " + String(getActiveprog())+"\n\r";
      }
        return true;
    }

    // return a boolen variable, about to enable or not the wifi task on the device 
    bool getSwitch(){
      bool param=EEPROM.readBool(ENABLE);
      return param;
    }

    //return the last active programram index.
    unsigned getActiveprog(){
        return EEPROM.readUInt(PROG);
    }

    //return the last clock numbers
    void getClock(unsigned* hour, unsigned*min){
      *hour=EEPROM.readUInt(HOUR);
      *min=EEPROM.readUInt(MIN);
    }

    //return nullptr if index not valid, else return an array which contain 24 double data. 
    //Every data means a temp, and every index means the hour where the data will be actice
    bool getProgram(unsigned index, double *prog){
        
        unsigned address=0;
        switch (index){
            case 0:address=FPROG1;break;
            case 1:address=FPROG2;break;
            case 2:address=FPROG3;break;
            case 3:address=FPROG4;break;
            case 4:address=FPROG5;break;
            default: return false;
        }
        for (unsigned i = 0; i < PSIZE; i++)
        {
            prog[i]=EEPROM.readDouble(address);
            address+=NEXT;
        }
        return true;
    }

    //return offset to mesure corretly
    double getOffset(){
       return EEPROM.readDouble(TMPOFFSET);
    }

    //return the server host
    unsigned getHost() {
        return EEPROM.readUInt(HOST);
    }

    //return router username 
    String getUser(unsigned size){
        return MyreadString(USER, size);
    }

    //return router pass
    String getPASS(unsigned size){
        return MyreadString(PW, size);
    }

    //return server ip
    String getIP(){
        return MyreadString(IP, IPSIZE);
    }