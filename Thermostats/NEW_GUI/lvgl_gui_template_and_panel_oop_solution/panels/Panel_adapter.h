#pragma once 
#ifndef PANEL_ADAPTER_H
#define PANEL_ADAPTER_H


class Panel_adapter{

public:
    Panel_adapter(/* args */);
    ~Panel_adapter();

    virtual bool get_Panel_elemnts(unsigned selector_id, void (**func)(void*))=0;
};



#endif /*PANEL_ADAPTER_H*/