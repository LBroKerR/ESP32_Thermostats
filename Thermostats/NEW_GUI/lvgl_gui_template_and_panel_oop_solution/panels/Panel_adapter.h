#pragma once 
#ifndef PANEL_ADAPTER_H
#define PANEL_ADAPTER_H


class Panel_adapter{

public:
    Panel_adapter(/* args */);
    ~Panel_adapter();

    virtual bool get_Panel_elements(unsigned *selector_id)=0;
    virtual void flag_for_hide_element(bool flag)=0;
};
bool Panel_adapter::get_Panel_elements(unsigned *selector_id){
    return false;
}
void Panel_adapter::flag_for_hide_element(bool flag){

}


#endif /*PANEL_ADAPTER_H*/