#include "modbusHandler.h"
    //Serial2.begin(BAUDRATE, SERIAL_8N1, RX, TX);
// Konstruktor, amely inicializálja a slave ID-t, a regiszter címét és a regiszterek számát
modbusHandler::modbusHandler(uint8_t slaveID, uint16_t registerAddress, uint8_t numberOfRegisters): node() {
    this->slaveID = slaveID;
    this->registerAddress = registerAddress;
    this->numberOfRegisters = numberOfRegisters;
    this->successFlag = false;
    Serial2.begin(BAUDRATE, SERIAL_8N1, RX, TX);
    node.begin(slaveID, Serial2);  // ModbusMaster objektum inicializálása
}

// Az adat küldése
void modbusHandler::UsingModbus(uint8_t data) {
    uint8_t result=0;
    successFlag = false;

    // Az adat küldése Write Single Register (0x06) funkcióval
    result = node.writeSingleRegister(registerAddress, data);
    if (result == node.ku8MBSuccess) {
        successFlag = true;
        Serial2.print("Write succeeded: ");
        Serial2.println(data);
    } else {
        successFlag = false;
        Serial2.print("Write failed! Error code: ");
        Serial2.println(result, HEX);
    }
}

// Az adat küldésének állapota
bool modbusHandler::isSuccess() {
    return successFlag;
}
