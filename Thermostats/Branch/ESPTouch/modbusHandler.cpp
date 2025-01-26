#include "modbusHandler.h"

// Constructor: Initializes the ModbusMaster object with slave ID, register address, and number of registers
modbusHandler::modbusHandler(uint8_t slaveID, uint16_t registerAddress, uint8_t numberOfRegisters) : node() {
    this->slaveID = slaveID;
    this->registerAddress = registerAddress;
    this->numberOfRegisters = numberOfRegisters;
    this->successFlag = false;

    // Initialize ModbusMaster node with the provided slave ID and Serial2 port for RS485 communication
    Serial2.begin(BAUDRATE, SERIAL_8N1, RX, TX);  // Set up UART2 communication
    node.begin(slaveID, Serial2);  // Initialize ModbusMaster with slave ID and Serial2
}

// UsingModbus: Function to send data to the slave via Modbus
void modbusHandler::UsingModbus(uint8_t data) {
    uint8_t result = 0;
    successFlag = false;

    // Write data to the register using Modbus Write Single Register (0x06) command
    result = node.writeSingleRegister(registerAddress, data);
    // Check if the Modbus operation was successful
    if (result == node.ku8MBSuccess) {
        successFlag = true;
        Serial2.println("Write succeeded: ");
        Serial2.println(data);
    } else {
        successFlag = false;
        Serial2.println("Write failed! Error code: ");
        Serial2.println(result, HEX);  // Print the error code in hexadecimal
    }
}

// isSuccess: Returns whether the last Modbus operation was successful
bool modbusHandler::isSuccess() {
    return successFlag;
}

