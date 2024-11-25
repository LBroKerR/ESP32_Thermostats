#include "HTML_page.h"

HTML_page::HTML_page(){
    list=nullptr;
    number_of_listelem=0;
    data=nullptr;
    number_of_tags=0;
    cssScript="null";
    JavaScipt="null";

    head="<head><title>Null</title></head>";
}
HTML_page::HTML_page(String HEAD){
    list=nullptr;
    number_of_listelem=0;
    data=nullptr;
    number_of_tags=0;
    setHead(HEAD);
    cssScript="null";
    JavaScipt="null";
}
HTML_page::~HTML_page(){
    if(list!=nullptr){
        delete[] list;
    }
    if(data!=nullptr){
        delete[] data;
    }
}

void HTML_page::setHead(String param){
    head=
        "<head><title>"+ param +"</title>"
        "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"
        "<link rel=\"stylesheet\" type=\"text/css\" href=\"styles.css\">"
        "</head>";
}
void  HTML_page::add_tag(String param, String param2, String param3){
    if(data==nullptr || number_of_tags==0){
        delete[] data;
        number_of_tags=0;
    }
    P_tag*tmp=new P_tag[number_of_tags+1];
    if(data!=nullptr){
        for(unsigned i=0; i<number_of_tags; i++){
            tmp[i]=data[i];
        }
        delete[] data;
    }
    tmp[number_of_tags].set_tag(param, param2, param3);
    data=tmp;
    number_of_tags++;
}
void  HTML_page::remove_tag(unsigned param){
    if(param > number_of_tags){
        return;
    }
    if(data==nullptr){
        delete[] data;
        number_of_tags=0;
        return;
    }
    P_tag*tmp=new P_tag[number_of_tags-1];
    for (unsigned i = 0; i < number_of_tags-1; i++){
        if(i<param){
            tmp[i]=data[i];
        }
        else if(i>=param){
            tmp[i]=data[i+1];
        }
    }
    delete[] data; 
    data=tmp;
    number_of_tags--;   
}
void  HTML_page::add_list_elem(String url, String text){
    if(list==nullptr || number_of_listelem==0){
        delete[] list;
        number_of_listelem=0;
    }
    UnorderedList*tmp=new UnorderedList[number_of_listelem+1];
    if(list!=nullptr){
        for(unsigned i=0; i<number_of_listelem; i++){
            tmp[i]=list[i];
        }
        delete[] list;
    }
    tmp[number_of_listelem].set_elem_vaule(url,text);
    list=tmp;
    number_of_listelem++;
}
void  HTML_page::remove_list_elem(String param){
    if(list==nullptr || number_of_listelem==0){
        delete[] list;
        number_of_listelem=0;
        return;
    }
    int index=-1;
    for (unsigned i = 0; i < number_of_listelem; i++){
        if(param==list[i].get_text()){
            index=i;
        }
    }
    UnorderedList*tmp=nullptr;
    if(index!=-1 && number_of_listelem>1){
        tmp=new UnorderedList[number_of_listelem-1];
        for(unsigned i=0; i< number_of_listelem-1; i++){
          if(i<index){
              tmp[i]=list[i];
          }
          else if(i>=index){
              tmp[i]=list[i+1];
          }
        }
    }
    delete[] list;
    list=tmp;
    number_of_listelem--;
}

String HTML_page::get_page(){
    String str;
    str="<html>";
    str+=head;
    str+="<body><div class=\"content\">"
    "<div class=\"card-grid\">";
    for (unsigned i = 0; i < number_of_tags; i=i+2){
        str+="<div class=\"card\">";
        for (unsigned ii = i; ii < (i+2); ii++){
            str+=data[ii].get_html_tag();
            if(LIST_P_TAG==data[ii].get_name()){
                str+="<ul>";
                for (unsigned i = 0; i < number_of_listelem; i++){
                    str+=list[i].get_html_link();
                }
                str+="</ul>";
            }
        }
        str+="</div>";
    }
    str+="</div></div><script src=\"script.js\"></script></body></html>";
    return str;
}

void HTML_page::set_java_script(String param){
  JavaScipt=param;
}
String HTML_page::get_java_script(){
  return JavaScipt;
}

void HTML_page::set_css(String param){
    cssScript=param;
}
String HTML_page::get_css(){
    return cssScript;
}

