 #include "wifi_data.h"

wifi_data::wifi_data(/* args */){
    ssid="null";
    pass="null";
    host=0;
    Switch=false;
    ip="Offline";
}

void wifi_data::setWifi_datas(String Ssid, String Pass, unsigned Host,bool SSwitch){
    ssid=Ssid;
    pass=Pass;
    host=Host;
    Switch=SSwitch;
}
String wifi_data::get_ssid()const{
    return ssid;
}
String wifi_data::get_pass()const{
    return pass;
}
unsigned wifi_data::get_host()const{
    return host;
}
bool wifi_data::get_switch()const{
    return Switch;
}
void wifi_data::set_ip(String param){
    ip = param;
}
String wifi_data::get_ip(){
    return ip;
}
