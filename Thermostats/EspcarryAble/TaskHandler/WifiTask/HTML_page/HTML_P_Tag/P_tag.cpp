#include "P_tag.h"

P_tag::P_tag(/* args */){
    id="null";
    name="null";
    Class="null";
}
P_tag::P_tag(String param, String param2, String param3){
    set_tag(param,param2,param3);
}

void P_tag::set_tag(String class_, String Id, String text){
  if(class_=="null"){
      id="null";
  }
  else{
    id=Id;
  }
    name=text;
    Class=class_;
}
String P_tag::get_name(){
  return name;
}
String P_tag::get_html_tag(){
  String str="<p ";
  if(Class!="null"){
    str+="class=\""+Class+"\">";
  }
  if(id!="null"){
    str+="<span id=\""+id+"\"></span>";
  }
  if(name!="null"){
    str+=name;
  }
  str+="</p>";
  return str;
}
