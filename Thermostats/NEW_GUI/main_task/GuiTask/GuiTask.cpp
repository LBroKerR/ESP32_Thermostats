#include "GuiTask.h"

TFT_eSPI lcd = TFT_eSPI(); // Define global variable
SPIClass *mySpi = new SPIClass(VSPI); // Define global variable
XPT2046_Touchscreen ts(XPT2046_CS, XPT2046_IRQ); // Define global variable

#if defined Display_35
uint16_t calData[5] = { 353, 3568, 269, 3491, 7 }; // Define global variable
#elif defined Display_24
uint16_t calData[5] = { 557, 3263, 369, 3493, 3 };
#elif defined Display_28
uint16_t calData[5] = { 189, 3416, 359, 3439, 1 };
#endif

uint16_t touchX = 0; // Define global variable
uint16_t touchY = 0; // Define global variable
bool Turn_ON_OFF=false;
 bool status=false;

void my_disp_flush( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p ){
  uint32_t w = ( area->x2 - area->x1 + 1 );
  uint32_t h = ( area->y2 - area->y1 + 1 );

  lcd.startWrite();
  lcd.setAddrWindow( area->x1, area->y1, w, h );
  lcd.pushColors( ( uint16_t * )&color_p->full, w * h, true );
  lcd.endWrite();

  lv_disp_flush_ready( disp );
}

void my_touchpad_read( lv_indev_drv_t * indev_driver, lv_indev_data_t * data ){
if(!ts.tirqTouched() && !ts.touched())
  {
        data->state = LV_INDEV_STATE_REL;
  }
  else
  {
   // Serial.println(String(touchX)+" "+String(touchY) );
        TS_Point p = ts.getPoint();
        uint16_t X, Y;
        X = map(p.x, 200, 3700, 1, screenWidth);  /* Touchscreen X calibration */
        Y = map(p.y, 240, 3800, 1, screenHeight); /* Touchscreen Y calibration */
        if(touchX!=X || touchY!=Y)
        {
          touchX=X;
          touchY=Y;
         data->state = LV_INDEV_STATE_PR;
        /*Set the coordinates*/
          data->point.x = X;
          data->point.y = Y;
        }
  }
}

void Gui_init(){
  //SPI init
  pinMode(25, OUTPUT);
  digitalWrite(25, LOW);
  mySpi->begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS); /* Start second SPI bus for touchscreen */
  ts.begin(*mySpi); /* Touchscreen init */
  ts.setRotation(1); /* Landscape orientation */
  //LCD init
  lcd.begin();          
  lcd.setRotation(1); 
  lcd.fillScreen(TFT_BLACK);
  delay(100);
    //background light pin
  pinMode(BACKLIGHT_PIN, OUTPUT);//27
  digitalWrite(BACKLIGHT_PIN, HIGH);//27 volt


#if defined USE_UI
  //lvgl init
  lv_init();
  lv_disp_draw_buf_init( &draw_buf, buf1, NULL, screenWidth * screenHeight / 13 );

  /*Display init*/
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init( &disp_drv );
  /*Display driver port of LVGL*/
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register( &disp_drv );

  /*touch driver port of LVGL*/
  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init( &indev_drv );
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_touchpad_read;
  lv_indev_drv_register( &indev_drv );

  ui_init();        //LVGL UI init
#endif
}
void is_user_interacted(DataHandler* data, unsigned *switch_of_screen){
  unsigned min=0;
  if(data->getTime()->getmin(&min)){
    if(Turn_ON_OFF && status){
        digitalWrite(BACKLIGHT_PIN, HIGH); 
        _ui_screen_change(&ui_Screen1, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 100, 0, &ui_Screen1_screen_init);
        Turn_ON_OFF=false;
        status=false;
      }
      else if( ts.touched() && !Turn_ON_OFF){
        *switch_of_screen=min+1;
        Turn_ON_OFF=true;
      }
      else if(*switch_of_screen<min) {
        _ui_screen_change(&ui_Screen5, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, &ui_Screen5_screen_init);
        digitalWrite(BACKLIGHT_PIN, LOW);  
        status=true;
      }
  }
}
bool changeTask(MainTask* screens,DataHandler* data, lv_chart_series_t * ui_TmpChart_series_1, char_listing *screen_number){
    char_listing str="1";
    if(convert_to_char_list(ui_BiosBool))==str){
      digitalWrite(BACKLIGHT_PIN, LOW);  
      _ui_screen_change(&ui_Screen5, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, &ui_Screen5_screen_init);
      return false;
    }

    *screen_number=convert_to_char_list(lv_label_get_text( ui_Screen_Number));
    screens->set_Active(screen_number->toInt());
    screens->Screen_Upgrading(data, ui_TmpChart_series_1);

    if(convert_to_char_list(lv_label_get_text(ui_SaveBool))==str){
      data->setProgSave(true);
      lv_label_set_text(ui_SaveBool, "0");
    }
    return true;
}
void GuiTask_main(MainTask* screens, DataHandler* data){
  Gui_init();
  char_listing screen_number="0";
  unsigned switch_of_screen=0;
  if(data->getTime()->getmin(&switch_of_screen)){
    switch_of_screen++;
    lv_chart_series_t * ui_TmpChart_series_1 = lv_chart_add_series(ui_TmpChart, lv_color_hex(0x19ACBA),LV_CHART_AXIS_PRIMARY_Y);
    screens->init_screens_datas(data, ui_TmpChart_series_1);
    bool task=true;
    while(task){
        task=changeTask(screens,data,ui_TmpChart_series_1, &screen_number);
        lv_timer_handler();
        is_user_interacted(data, &switch_of_screen);
      vTaskDelay(10 / portTICK_PERIOD_MS);
    }
  }
}