#include "config.h"
#include "game_logic.h"

void setup() {
    Serial.begin(9600);

    // הגדרת מצב פינים
    pinMode(LIGHT_PIN, OUTPUT);
    pinMode(FAN_PIN, OUTPUT);
    pinMode(BUTTON_RED_PIN, INPUT_PULLUP);
    pinMode(BUTTON_GREEN_PIN, INPUT_PULLUP);
    pinMode(LED_RED, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(DISTANCE_SENSOR_TRIGGER_PIN, OUTPUT);
    pinMode(DISTANCE_SENSOR_ECHO_PIN, INPUT);

    // אתחול WiFi
    WiFi.mode(WIFI_STA);
    WiFi.begin("NartRamadan", "19911991");
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");
}

void loop() {
    switch (currentStage) {
    case 0:
        if (digitalRead(BUTTON_RED_PIN) == LOW) {
            solveChallenge1(); // חידה 1
        }
        break;
    case 1:
        if (analogRead(TEMP_SENSOR_PIN) > 500) {
            solveChallenge2(); // חידה 2
        }
        break;
    case 2:
        if (digitalRead(BUTTON_GREEN_PIN) == LOW) {
            solveChallenge3(); // חידה 3
        }
        break;
    case 3:
        solveChallenge4(); // חידה 4
        break;
    default:
        Serial.println("All challenges solved!");
        break;
    }

    delay(100);
}
