#include "P_tag.h"

P_tag::P_tag(/* args */){
    id="null";
    name="null";
    SI="null";
}
P_tag::P_tag(String param, String param2, String param3){
    set_tag(param,param2,param3);
}

void P_tag::set_tag(String param, String param2, String param3){
  if(param=="simple tag"){
      id="null";
  }
  else{
    id=param;
  }
    name=param2;
    SI=param3;
}
String P_tag::get_html_tag(){
  String str="<p>";
  if(name!="null"){
    str+=name;
  }
  if(id!="null"){
    str+="<span id=\""+id+"\"></span>";
  }
  if(SI!="null"){
    str+=SI;
  }
  str+="</p>";
  return str;
}
