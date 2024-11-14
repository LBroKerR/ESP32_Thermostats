#include "JavaScript.h"

String get_script(){
    String str=R"rawliteral(
var websocket;
// Init web socket when the page loads
window.addEventListener('load', onload);

function onload(event) {
    initWebSocket();
}

function getReadings(){
    websocket.send("getReadings");
}

function initWebSocket() {
    console.log('Trying to open a WebSocket connection…');
    websocket = new WebSocket('ws://' + window.location.hostname + '/ws');
    websocket.onopen = onOpen;
    websocket.onclose = onClose;
    websocket.onmessage = onMessage;

    websocket.onerror = function(error) {
        console.error('WebSocket error:', error);
    };
}

// When websocket is established, call the getReadings() function
function onOpen(event) {
    console.log('Connection opened');
    getReadings();
}

function onClose(event) {
    console.log('Connection closed');
    setTimeout(initWebSocket, 2000);
}

// Function that receives the message from the ESP32 with the readings
//new
function onMessage(event) {
    console.log(event.data);
    var myObj = JSON.parse(event.data);

    // existing variable will be setted via Json msg. 
    Object.keys(myObj).forEach(key => {
        var element = document.getElementById(key);
        if (element) {
            element.innerHTML = myObj[key];
        }
    });
}
)rawliteral";

    return str;
}

/* old
function onMessage(event) {
    console.log(event.data);
    var myObj = JSON.parse(event.data);
    var keys = Object.keys(myObj);

    for (var i = 0; i < keys.length; i++){
        var key = keys[i];
        document.getElementById(key).innerHTML = myObj[key];
    }
}
*/