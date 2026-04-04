#include <Arduino.h>
#include "App.h"

App app;

void setup() {
    Serial.begin(9600);
    app.begin();
}

void loop(){
    app.run();
}