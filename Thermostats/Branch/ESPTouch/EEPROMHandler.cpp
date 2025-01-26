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


bool check_Nickname_datagramm(void* param){
    String *str = (String*)param;
    if (str == nullptr) {
        return false;
    }
    if(str->length()<NAMESIZE){
        MywriteString(NICKNAME, *str);
        return true;
    }
    return false;
}
bool check_ID_datagramm(void* param){
    String *str = (String*)param;
    if (str == nullptr) {
        return false;
    }
    if(isnumber(*str)){
        int id=str->toInt();
    #if(ESPTOUCH && !ESPCARRY)
        if(id>0 && id<=getNumber_of_heating_circle()){
          EEPROM.writeUInt(HEATING_CIRLE_ID,id);
          EEPROM.commit();
          return true;
        }
    #endif
    #if(!ESPTOUCH && ESPCARRY)
        if(id>0 ){
          EEPROM.writeUInt(HEATING_CIRLE_ID,id);
          EEPROM.commit();
          return true;
        }
    #endif
    }
return false;
}

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

    bool check_hour_datagramm(void* param){
        String* str = (String*)param;
        if (str == nullptr ) {
            return false;
        }
        if(isnumber(*str)){
            unsigned tmp=(unsigned)str->toInt();
            if(tmp>=0 && tmp<60){
                EEPROM.writeUInt(HOUR, tmp);
                EEPROM.commit();
                return true;
            }
        }
        return false;;
    }
    bool check_min_datagramm(void* param){
        String* str = (String*)param;
        if (str == nullptr ) {
            return false;
        }
        if(isnumber(*str)){
            unsigned tmp=(unsigned)str->toInt();
            if(tmp>=0 && tmp<60){
                EEPROM.writeUInt(MIN, tmp);
                EEPROM.commit();
                return true;
            }
        }
        return false;;
    }
#if(ESPTOUCH && !ESPCARRY)
    bool check_modbus_id(void* param){
        String* str = (String*)param;
        if (str == nullptr ) {
            return false;
        }
        if(isnumber(*str)){
            unsigned tmp=(unsigned)str->toInt();
            if(tmp<=255){
                EEPROM.writeUInt(MODBUS_ID, tmp);
                EEPROM.commit();
                return true;
            }
        }
        return false;
    }
    bool check_modbus_register_address(void* param){
        String* str = (String*)param;
        if (str == nullptr ) {
            return false;
        }
        if(isnumber(*str)){
            unsigned tmp=(unsigned)str->toInt();
                EEPROM.writeUInt(MODBUS_REGISTER_ADDRESS, tmp);
                EEPROM.commit();
                return true;
        }
        return false;
    }
    bool check_modbus_register_number(void* param){
        String* str = (String*)param;
        if (str == nullptr ) {
            return false;
        }
        if(isnumber(*str)){
            unsigned tmp=(unsigned)str->toInt();
                EEPROM.writeUInt(MODBUS_REGISTER_NUMBER, tmp);
                EEPROM.commit();
                return true;
        }
        return false;
    }
#endif

// will be part of the autosave functions!
    bool write_out_active_program_number(unsigned param){
        if (param < 5 && param >= 0) {
            EEPROM.writeUInt(PROG, param);
            EEPROM.commit();
            return true;
        }
        return false;
    }
#if(ESPTOUCH && !ESPCARRY)
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
    void save_heating_mode(bool param){
        EEPROM.writeBool(HEATING_MODE,param);
    }
#endif
    bool check_number_of_heating_circle_datagramm(void * param){
        String* str = (String*)param;
        if (str == nullptr ) {
            return false;
        }
        if(isnumber(*str)){
            int tmp=str->toInt();
            if(tmp<getID() && tmp > 0){
                *str="1";
                check_ID_datagramm((void*)str);
            }
            if(tmp > 0 && tmp > getID()){
              EEPROM.writeUInt(NUMBER_OF_HEATING_CIRLE, tmp);
              EEPROM.commit();
              print(param);
              return true;
            }
        }
        return false;
    }
    bool Hardreset(void*param){
       String* str = (String*)param;
       if(str!=nullptr){
          if(*str==getPASS(UPSIZE)){
            for(unsigned i=0; i< EEPROM_SIZE; i++){
              EEPROM.writeBool(i, false);
            }
            EEPROM.commit();
#if(ESPTOUCH && !ESPCARRY)
            *str="1";
            check_number_of_heating_circle_datagramm((void*)str);
            check_ID_datagramm((void*)str);
            double tmp[24];
            for(unsigned i=0; i<24; i++){tmp[i]=15.5;};
            for(unsigned i=0;i < 5; i++){
              write_out_full_program(i,tmp);
            }
#endif
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
      //double tmp[24];
      //for(unsigned i=0; i<24; i++){tmp[i]=-1.0;};
      if (str != nullptr) {
          if (*str == getPASS(UPSIZE)) {
              showPW = true;
          }
          *str = "";
#if(ESPCARRY && !ESPTOUCH)
          *str += "\n\r IP address: "+ getIP();
#endif
          *str+= "\n\r Username: "+getUser(UPSIZE)+ "\n\r password: ";
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
          *str += String(hourtmp) + " " + String(mintmp)  +"\n\r"+" Device loaction/name: "+getName()+"\n\r Heating Cirle number: "+String(getNumber_of_heating_circle())+"\n\r";
          *str +=" Sensor location on heatingcircles (ID): "+String(getID())+"\n\r";
          *str+=" modbus id: "+String(get_modbus_id())+"\n\r";
          *str+=" modbus register address: "+String(get_modbus_register_address())+"\n\r";
          *str+=" modbus register number: "+String(get_modbus_register_number())+"\n\r";
          /*for(unsigned i=0; i<5; i++){
            getProgram(i,tmp);
            *str+=String(i)+".\n\r";
            for(unsigned k=0; k<24; k++){
                *str+=String(tmp[k]);
                *str+=" ";
            }
            *str+="\n\r";
          }*/

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
#if(ESPTOUCH && !ESPCARRY)
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
    bool read_heating_mode(){
        return EEPROM.readBool(HEATING_MODE);
    }
#endif
    unsigned getNumber_of_heating_circle(){
        return  EEPROM.readUInt(NUMBER_OF_HEATING_CIRLE);
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
    String getName(){
        return MyreadString(NICKNAME, NAMESIZE);
    }
    unsigned getID(){
        return EEPROM.readUInt(HEATING_CIRLE_ID);
    }
#if(ESPTOUCH && !ESPCARRY)

    unsigned get_modbus_id(){
         return EEPROM.readUInt(MODBUS_ID);
    }
    unsigned get_modbus_register_address(){
         return EEPROM.readUInt(MODBUS_REGISTER_ADDRESS);
    }
    unsigned get_modbus_register_number(){
         return EEPROM.readUInt(MODBUS_REGISTER_NUMBER);
    }

    void EEPROM_CLEARED(){
        EEPROM.writeDouble(EEPROM_CRASHED, 0.0);
        EEPROM.commit();
    }
    double is_EEPROM_crashed(){
        return EEPROM.readDouble(EEPROM_CRASHED);
    }
#endif