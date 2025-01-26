#include <Arduino.h>
#include <EEPROM.h>
#include "EEPROMhandler.h"
#define IP_ADDRESS_START 0 
bool start=false;
String IPtest(String teststr){
  String output="TEST ";
  if(check_IP_datagramm((void*)&teststr))
  {
    if(getIP()==teststr)
    {
    output+="\033[1m\033[42mSUCCEEDED\033[0m\n\r";
    }
    else
    {
      output+="\033[1m\033[41m";
      output+="FAILED: '";
      output+=getIP();
      output+="'\033[0m\n\r";
    }
  }
  else
  {
    output+="\033[1m\033[41mFAILED\033[0m\n\r";
  }
  return output;
}
String failIPtest(String teststr){
  String output="TEST ";
  if(!check_IP_datagramm((void*)&teststr)){
    output+="\033[1m\033[42mSUCCEEDED\033[0m\n\r";
  }
  else{
    output+="\033[1m\033[41mFAILED\033[0m\n\r";
  }
  return output;
}
String HOSTtest(String teststr){
  String output="TEST ";
  if(check_host_datagramm((void*)&teststr)){
    if(getHost()==teststr.toInt()){
    output+="\033[1m\033[42mSUCCEEDED\033[0m\n\r";
    }
    else{
      output+="\033[1m\033[41m";
      output+="FAILED: '";
      output+=getHost();
      output+="'\033[0m\n\r";
    }
  }
  else{
    output+="\033[1m\033[41mFAILED\033[0m\n\r";
  }
  return output;
}
String PASStest(String teststr){
  String output="TEST ";
  if(check_pass_datagramm((void*)&teststr)){
    if(getPASS(10)==teststr){
    output+="\033[1m\033[42mSUCCEEDED\033[0m\n\r";
    }
    else{
      output+="\033[1m\033[41m";
      output+="FAILED: '";
      output+=getPASS(10);
      output+="'\033[0m\n\r";
    }
  }
  else{
    output+="\033[1m\033[41mFAILED\033[0m\n\r";
  }
  return output;
}
String USERtest(String teststr){
  String output="TEST ";
  if(check_user_datagramm((void*)&teststr)){
    if( getUser(10)==teststr){
    output+="\033[1m\033[42mSUCCEEDED\033[0m\n\r";
    }
    else{
      output+="\033[1m\033[41m";
      output+="FAILED: '";
      output+= getUser(10);
      output+="'\033[0m\n\r";
    }
  }
  else{
    output+="\033[1m\033[41mFAILED\033[0m\n\r";
  }
  return output;
}
String SWITCHtest(String teststr){
  String output="TEST ";
  String Switch="";
  if(check_switch_datagramm((void*)&teststr)){
    if(getSwitch())
    {
      Switch="enable";
    }
    else{
      Switch="disable";
    }
    if( Switch==teststr){
    output+="\033[1m\033[42mSUCCEEDED\033[0m\n\r";
    }
    else{
      output+="\033[1m\033[41m";
      output+="FAILED: '";
      output+= getUser(10);
      output+="'\033[0m\n\r";
    }
  }
  else{
    output+="\033[1m\033[41mFAILED\033[0m\n\r";
  }
  return output;
}
String TEMPERATUREtest(String teststr){
  String output="TEST ";
  if(check_temp_datagramm((void*)&teststr)){
    if(  getOffset()==teststr.toDouble()){
    output+="\033[1m\033[42mSUCCEEDED\033[0m\n\r";
    }
    else{
      output+="\033[1m\033[41m";
      output+="FAILED: '";
      output+= getOffset();
      output+="'\033[0m\n\r";
    }
  }
  else{
    output+="\033[1m\033[41mFAILED\033[0m\n\r";
  }
  return output;
}
String failTEMPERATUREtest(String teststr){
  String output="TEST ";
  if(! check_temp_datagramm((void*)&teststr)){
    output+="\033[1m\033[42mSUCCEEDED\033[0m\n\r";
  }
  else{
    output+="\033[1m\033[41mFAILED\033[0m\n\r";
  }
  return output;
}
String CLOCKtest(String teststr){
   String output="TEST ";
   String clock="";
   unsigned hour=0;
   unsigned min=0;
  if(check_clock_datagramm((void*)&teststr)){
    getClock(&hour, &min);
    clock+=hour;
    clock+=" ";
    clock+=min;
    if(clock==teststr){
    output+="\033[1m\033[42mSUCCEEDED\033[0m\n\r";
    }
    else{
      output+="\033[1m\033[41m";
      output+="FAILED: '";
      output+=clock;
      output+="'\033[0m\n\r";
    }
  }
  else{
    output+="\033[1m\033[41mFAILED\033[0m\n\r";
  }
  return output;
}
String failCLOCKtest(String teststr){
  String output="TEST ";
  if(! check_clock_datagramm((void*)&teststr)){
    output+="\033[1m\033[42mSUCCEEDED\033[0m\n\r";
  }
  else{
    output+="\033[1m\033[41mFAILED\033[0m\n\r";
  }
  return output;
}
String ACTIVEPROGtest(){
  String output="TEST ";
  unsigned test=3;
  if(write_out_active_program_number(test)){
    if(getActiveprog()==test){
      output+="\033[1m\033[42mSUCCEEDED\033[0m\n\r";
    }
    else{
      output+="\033[1m\033[41m";
      output+="FAILED: '";
      output+=getActiveprog();
      output+="'\033[0m\n\r";
    }
  }
  else{
      output+="\033[1m\033[41mFAILED\033[0m\n\r";
  }
  return output;
}
String PROGRAMStest(){
  String output="TEST ";
  double test[24];
  double prog[24];
  for(unsigned i=0; i<24; i++){
    prog[i]=0.0;
  }
  for(unsigned i=0; i<5; i++){
      for(unsigned index=0; index<24; index++){
        test[index]=20.15;
        test[index]+=(double)i;
      }
    if(!write_out_full_program(i,test)){
      output+="\033[1m\033[41mFAILED write: ";
      output+="index:";
      output+=String(i);
      output+="\033[0m\n\r";
    }
  }
  for(unsigned i=0; i<5; i++){
      if(!getProgram(i,prog)){
        output+="\033[1m\033[41mFAILED\033[0m\n\r";
      }else{
      for(unsigned index=0; index<24; index++){
        test[index]=20.15;
        test[index]+=(double)i;
      }
        //output+=String(i)+":\n\r ";
        for(unsigned index=0; index<24;index++){
          //output+=String(index)+": "+String(prog[index])+ " "+ String(test[index])+"\n\r";
          if(prog[index]!=test[index]){
            output+="\033[1m\033[41m";
            output+="FAILED: index:";
            output+=index;
            output+=" test number: ";
            output+=test[index];
            output+=" returned number: ";
            output+=prog[index];
            output+="'\033[0m\n\r";
            return output;
          }
        }
        //output+="\n\r";
      }
  }
  output+="\033[1m\033[42mSUCCEEDED\033[0m\n\r";
  return output;
}


void Taskcore(void*param){
  EEPROM.begin(1024);
  String str[19];
  for(unsigned i=0; i<19;i++){
    str[i]="";
  }
  delay(100);
  str[0]+="save IP test 1: ";
  str[0]+=IPtest("123.123.123.123");
  delay(100);
    str[1]+="save IP test 2: ";
  str[1]+=IPtest("123.123.0.123");
  delay(100);
    str[2]+="save IP test 3: ";
  str[2]+=failIPtest("123.123.123.123.");
delay(100);
      str[3]+="save IP test 4: ";
  str[3]+=failIPtest("123.300.123.123");
delay(100);
      str[4]+="save IP test 5: ";
  str[4]+=failIPtest("123.asd.123.123");
delay(100);
  str[5]+="save HOST test: ";
   str[5]+=HOSTtest("1200");
delay(100);
  str[6]+="save PASS test: ";
   str[6]+=PASStest("TEST");
delay(100);
  str[7]+="save USER test: ";
  str[7]+=USERtest("ADMIN");
delay(100);
  str[8]+="save SWITCH test 1 : ";
  str[8]+=SWITCHtest("enable");
delay(100);
  str[9]+="save SWITCH test 2 : ";
  str[9]+=SWITCHtest("disable");
delay(100);
  str[10]+="save TEMPERATURE test 1: ";
  str[10]+=TEMPERATUREtest("-9.3");
delay(100);
   str[11]+="save TEMPERATURE test 2: ";
  str[11]+=TEMPERATUREtest("5.3");
  delay(100);
   str[12]+="save TEMPERATURE test 3: ";
  str[12]+=TEMPERATUREtest("-3");
delay(100);
   str[13]+="save TEMPERATURE test 4: ";
  str[13]+=failTEMPERATUREtest("sad25.0");
delay(100);
  str[14]+="save CLOCK test 1: ";
  str[14]+=CLOCKtest("22 50");
delay(100);
    str[15]+="save CLOCK test 2: ";
  str[15]+=failCLOCKtest("35 50");
delay(100);
    str[16]+="save CLOCK test 3: ";
  str[16]+=failCLOCKtest("asd 50");
delay(100);
  str[17]+="save ACTIVEPROG test: ";
  str[17]+=ACTIVEPROGtest();
delay(100);
  str[18]+="save FULL PROGRAMS test: ";//ERROR!
  str[18]+=PROGRAMStest();
delay(100);
  //String pass=getPASS(10);
  //Hardreset((void*)&pass);
delay(100);
  EEPROM.end();
  delay(100);
  Serial.begin(115200);
  delay(100);
  for(unsigned i=0; i<19;i++){
    Serial.println(str[i]);
    delay(100);
  }
  Serial.end();
  start=true;
  vTaskDelete(nullptr);
}
void writeIPToEEPROM(String ip) {
    for (int i = 0; i < ip.length(); i++) {
        EEPROM.write(IP_ADDRESS_START + i, ip[i]);  // Karakterenként írjuk
    }
    
    EEPROM.write(IP_ADDRESS_START + ip.length(), '\0');  // Null terminátor hozzáadása a végére
    EEPROM.commit();  // Mentés az EEPROM-ba
}
String readIPFromEEPROM() {
    
    char ip[16];  // Maximum 15 karakter hosszú IP cím, plusz null terminátor
    int i = 0;
    char c;
    
    // Karakterenként olvassuk az EEPROM-ból, amíg nem érünk null terminátorhoz
    while ((c = EEPROM.read(IP_ADDRESS_START + i)) != '\0' && i < 15) {
        ip[i] = c;
        i++;
    }
    ip[i] = '\0';  // Null terminátor hozzáadása
    return String(ip);  // Visszatérünk a kiolvasott IP-címmel
}
void newipfunc(void*param){
  String ip="123.123.123.123";
  String str="";
  EEPROM.begin(EEPROM_SIZE);
  writeIPToEEPROM(ip);
  str=readIPFromEEPROM();
   EEPROM.end();

   delay(1000);
   Serial.begin(115200);
   delay(1000);
   Serial.print("Readed ip: ");
   Serial.println(str);
   delay(10000);
   Serial.end();
  vTaskDelete(nullptr);
}
void setup() {
  // put your setup code here, to run once:
  TaskHandle_t serialTask;
   //xTaskCreatePinnedToCore(newipfunc, "serialTask", 10000, NULL, 5, &serialTask, 1);
 xTaskCreatePinnedToCore(Taskcore, "serialTask", 10000, NULL, 5, &serialTask, 1);


}

void loop() {
  // put your main code here, to run repeatedly:

}
