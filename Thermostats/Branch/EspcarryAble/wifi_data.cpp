 #include "wifi_data.h"

wifi_data::wifi_data(/* args */){
    ip="null";
    ssid="null";
    pass="null";
    host=0;
    Switch=false;
}

void wifi_data::setWifi_datas(String IP,String Ssid, String Pass, unsigned Host,bool SSwitch){
    ip=IP;
    ssid=Ssid;
    pass=Pass;
    host=Host;
    Switch=SSwitch;
}
String wifi_data::get_ip()const{
    return ip;
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
