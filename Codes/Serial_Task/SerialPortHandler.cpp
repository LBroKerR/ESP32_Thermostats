#include "SerialPortHandler.h"
//  calculate the number of words in str
void SerialPortHandler::CalculateSize(char* str) {
	bool word = true;
	for (unsigned i = 0; str[i] !='\0'; i++){
		if ( str[i] != ' ' &&  str[i]!= '\t' &&  str[i] != '\n') {
			if (word) {
				stackSize++;
				word = false;
			}
		}
		else {
			word = true;
		}
	}
}
// searching the first letters of the words in the string
void SerialPortHandler::startpoints(char* str, unsigned* entris){
	bool entry = true; 
	unsigned pos = 0;
	for (unsigned index = 0; index < stackSize; index++){
		for (unsigned i = pos; str[i] !='\0'; i++) {
			if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n') {
				if (entry) {
					entris[index] = i;
					entry = false;
				}
			}
			else if(!entry){
				pos = i;
				entry = true; break;
			}

		}
	}
}

// place every word in a string, and collect them in a dynamic array
void SerialPortHandler::ConvertToStack(char*str) {
	unsigned startPoints[stackSize];
	CalculateSize(str);
	startpoints(str, startPoints);
	stackData = new String[stackSize];
	for (unsigned index = 0; index < stackSize; index++) {
		for (unsigned i = startPoints[index]; str[i]!= '\0'; i++){
			if ( str[i] != ' ' &&  str[i]!= '\t' &&  str[i] != '\n') {
				stackData[index] +=  str[i];
			}
			else {
				break;
			}
		}
	}
}

SerialPortHandler::SerialPortHandler(){
	stackData = nullptr;
	stackSize = 0;
}

SerialPortHandler::~SerialPortHandler(){
	delete[] stackData;
	stackData = nullptr;
}

// pop out the first string from the array, return it, and save the others
bool SerialPortHandler::useStack(String* param) {
	if (stackData == nullptr || stackSize == 0) {
		delete[] stackData;
		stackData = nullptr;
		return false;
	}
	String str = *stackData;
	String* tmp=nullptr;
	if (stackSize - 1 > 0 ) {
		tmp = new String[stackSize - 1];
		for (unsigned i = 1; i < stackSize; i++) {
			tmp[i-1] = stackData[i];
		}
	}
	delete[] stackData;
	stackData = tmp;
	stackSize--;
	*param = str;
	return true;
}

// Waiting input if needed, and print out the needed text
bool SerialPortHandler::Input(String*incomingData, String print) {
if (!useStack(incomingData)) {
    char ch[50]; 
    unsigned i = 0; 
    Serial.print((print+="Input available:\n\r"));
    while (i<49) {
      if(Serial.available()>0){
        ch[i] = (char)Serial.read();
        if(ch[i]!='\b'){
          Serial.print(ch[i]);
          if (ch[i] == '\n' || ch[i] == '\r') {
            ch[i] = '\0';
            ConvertToStack(ch);
            useStack(incomingData);
            return true;
          }
        i++;
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);
      }
    }
    return false;
  }
  return true;
}

bool SerialPortHandler::getdata(String* param)
{
  bool output=false;
	if (stackData != nullptr) {
		return output;
	}
	while(true){
    if(Input(param, "\n\rData input needed\n\r")){
      if( *param!="cancel" && *param!="quit" && *param!="help"){
        if(stackSize==0){//Input contain useStack function. Therefor if the next function need only one input, the stackData going to be zero after useStack function.
          output=true;
        }
        break;
      }
      else{
        output=false;
        break;
      }
    }
  }
  delete[] stackData;
	stackData = nullptr;
	return output;
}

// print up coming text
void SerialPortHandler::prints(String param){
	  Serial.println(param);
}
// print out the commands, and how the menu system is work.
void SerialPortHandler::printshelp(){
  Serial.begin(BAUDRATE);
  delay(100);
  Serial.println("Welcome in BIOS Menu system, where you can set your termostate device!\n");
  Serial.println("To interact with the menu just enter any commands from below!\n");
	Serial.println("Commands:");
  Serial.println("menu:");
  Serial.println("\tset");
  Serial.println("\thardrese\n");
  Serial.println("set menu:");
  Serial.println("\ttemp");
  Serial.println("\tclock");
  Serial.println("\twifimenu\n");
  Serial.println("wifimenu:");
  Serial.println("\tip");
  Serial.println("\thost");
  Serial.println("\tpass");
  Serial.println("\twifi\n");
  Serial.println("commands anywhere:\n");
  Serial.println("\tquit");
  Serial.println("\tcancel");
  Serial.println("\thelp\n");
	Serial.println("Menus can be work with only one command/menu.\n");
  Serial.println("\t\tOr\n");
  Serial.println("Use multiply command together, and use space between them.");
  Serial.println("For examle: \n");
  Serial.println("\tset wifimenu wifi \n");
  Serial.println("\tThen the program will be ask for data input! \n");
  Serial.println("\t\tOr\n");
  Serial.println("\tType one by one and hit enter after each command.\n");
  Serial.println("help: prints out the active menu commands.\n");
  Serial.println("cancel: returns to the main menu.\n");
  Serial.println("quit: exiting BIOS, and reseting the device!");
}
