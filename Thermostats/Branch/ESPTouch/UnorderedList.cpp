#include "UnorderedList.h"

UnorderedList::UnorderedList(){
    list_elem_vaule="null";
    text="null";
}
void UnorderedList::set_elem_vaule(String param, String param2){
    list_elem_vaule=param;
    text=param2;
}
String UnorderedList::get_text()const{
    return text;
}
String UnorderedList::get_link()const{
    return list_elem_vaule;
}
String UnorderedList::get_html_link(){
    String str="<li><a href=http://"+get_link()+"/>"+get_text()+"</a>";
    return str;
}
