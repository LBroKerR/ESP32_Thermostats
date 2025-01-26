#include "Taskhandler.h"

DataHandler Taskhandler::data;
bool Taskhandler::end_task_on_core_0;
//DHT sensor(DHTPIN,DHTTYPE);
Taskhandler::Taskhandler(){
    //data=new DataHandler();
    myQueue1 = xQueueCreate(NUMBER_OF_TASKS_CORE1, sizeof(TaskHandle_t));
   // myQueue0 = xQueueCreate(NUMBER_OF_TASKS_CORE0, sizeof(TaskHandle_t));
}
Taskhandler::~Taskhandler(){
        //delete data;
}

void Taskhandler::BIOSTask(void*parameters){
  QueueHandle_t Queue=*(QueueHandle_t*)parameters;
  TaskHandle_t receivedTaskHandle;
  if (xQueueReceive(Queue, &receivedTaskHandle, portMAX_DELAY) == pdTRUE ) {
    SerialTask *bios=new SerialTask();
    bios->main();
    delete bios;
    delay(1000);
    Serial.begin(115200);
    Serial.println("Rebooting device...\n\r");
    delay(1000);
    Serial.end();
  //tells the SDK to reboot, so its a more clean reboot, use this one if possible.
    ESP.restart();
  }
  TaskHandle_t taskHandle = xTaskGetCurrentTaskHandle();
  xQueueSend(Queue, &taskHandle, portMAX_DELAY);
  vTaskDelete(nullptr);
}


void Taskhandler::Guitask(void*parameters){
  QueueHandle_t Queue=*(QueueHandle_t*)parameters;
  TaskHandle_t receivedTaskHandle;
  if (xQueueReceive(Queue, &receivedTaskHandle, portMAX_DELAY) == pdTRUE ) {
    // Code comes here!
    end_task_on_core_0=false;
    MainTask *update=new MainTask(SCREENS);
    update->setSensor_Location(&data);
    if(data.getHeater()->getHeatingCircleHandler()[update->getSensorLocation()].getSensor()!=nullptr){
      TaskHandle_t core0;
      xTaskCreatePinnedToCore(Taskhandler::OtherTasks, "core0", 5000,nullptr, 5, &core0, 0);
      GuiTask_main(update, &data);
      Serial.end();
      end_task_on_core_0=true;
      vTaskDelete(core0);
      delete update;
    }
  }
  TaskHandle_t taskHandle = xTaskGetCurrentTaskHandle();
  xQueueSend(Queue, &taskHandle, portMAX_DELAY);
  vTaskDelete(nullptr);
}


void Taskhandler::initTask(void*parameters){
  QueueHandle_t Queue=*(QueueHandle_t*)parameters;
  TaskHandle_t receivedTaskHandle;
  //if (xQueueReceive(Queue, &receivedTaskHandle, portMAX_DELAY) == pdTRUE) {
    InitTask *init=new InitTask();
    init->main(&data);
    delete init;
  //}
  TaskHandle_t taskHandle = xTaskGetCurrentTaskHandle();
  xQueueSend(Queue, &taskHandle, portMAX_DELAY);
  vTaskDelete(nullptr);
}

void Taskhandler::OtherTasks(void*parameters){
  //measure, wifi, autosave, modbus
  //sensor.begin();
  InitTask *autoSave=new InitTask();
  MeasuringTask measure(&data);
  wifiTask wifi(&data);
  HeatingCommunicationTask Controlling(&data);
  Controlling.set_modbus_communication(data.getHeater()->get_modbus_data().get_ID(),data.getHeater()->get_modbus_data().get_address(),data.getHeater()->get_modbus_data().get_number());
  ESP32Time rtc;
  unsigned hour_tmp=0, min_tmp=0;
  data.getTime()->getmin(&min_tmp);
  data.getTime()->gethour(&hour_tmp);
  rtc.setTime(1, min_tmp, hour_tmp, DAY, MONTH, YEAR);
         //          s   m   h+1  d    m      y
  while(!end_task_on_core_0){
    measure.measurning(nullptr/*&sensor*/, &rtc);
    wifi.main();
    autoSave->save(&data);
    if(measure.get_sensor_ready()){
      Controlling.Communicate_with_PLC();
    }
    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
  while(true){
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
  vTaskDelete(nullptr);
}

void Taskhandler::switch_wdt(bool Switch) {
    // Watchdog konfiguráció 
    esp_task_wdt_deinit();
    esp_task_wdt_config_t wdt_config = {
        .timeout_ms = WDT_TIMEOUT_SECONDS * 1000, // Időtúllépés milliszekundumban
        .idle_core_mask = (1 << 0) | (1 << 1),    // Core 0,1 figyelése
        .trigger_panic = Switch                  // Nincs újraindítás időtúllépés esetén
    };
    esp_task_wdt_init(&wdt_config);
}


void Taskhandler::main(){
  //switch_wdt(true);
  xTaskCreatePinnedToCore(Taskhandler::initTask, "core1", 5000, &myQueue1, 5, &core1, 1);
  xTaskCreatePinnedToCore(Taskhandler::Guitask, "core1", 5000, &myQueue1, 5, &core1, 1);
  xTaskCreatePinnedToCore(Taskhandler::BIOSTask, "core1", 5000, &myQueue1, 5, &core1, 1);
}