#include "styles.h"

String get_styles(){
String str=R"rawliteral(

html {
    font-family: Arial, Helvetica, sans-serif;
    display: inline-block;
    text-align: center;
}
body {
    margin: 0;
}
.content {
    padding: 50px;
}
.card-grid {
    max-width: 800px;
    margin: 0 auto;
    display: grid;
    grid-gap: 2rem;
    grid-template-columns: repeat(auto-fit, minmax(200px, 1fr));
}
.card {
    background-color: white;
    box-shadow: 2px 2px 12px 1px rgba(140,140,140,.5);
}
.card-title {
    font-size: 1.2rem;
    font-weight: bold;
    color: #034078
}
.reading {
    font-size: 1.2rem;
    color: #1282A2;
}

)rawliteral";

    return str;

}