#include "config.h"
#include "game_logic.h"

void setup() {
    Serial.begin(9600); // אתחול תקשורת סריאלית

    // הגדרת מצב פינים
    pinMode(LIGHT_PIN, OUTPUT); // מחבר את פין התאורה כיציאה
    pinMode(FAN_PIN, OUTPUT); // מחבר את פין המאוורר כיציאה
    pinMode(BUTTON_RED_PIN, INPUT_PULLUP); // כפתור אדום – קלט
    pinMode(BUTTON_GREEN_PIN, INPUT_PULLUP); // כפתור ירוק – קלט
    pinMode(LED_RED, OUTPUT); // נורית אדומה – יציאה
    pinMode(LED_GREEN, OUTPUT); // נורית ירוקה – יציאה
    pinMode(DISTANCE_SENSOR_TRIGGER_PIN, OUTPUT); // חיישן מרחק – שליחה
    pinMode(DISTANCE_SENSOR_ECHO_PIN, INPUT); // חיישן מרחק – קליטה

    // התחברות ל-WiFi
    WiFi.mode(WIFI_STA); // מצב תחנת WiFi
    WiFi.begin("NartRamadan", "19911991");
    
    // מחכה לחיבור לרשת
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
            solveChallenge1(); // פותר חידה 1
        }
        break;

    case 1:
        if (analogRead(TEMP_SENSOR_PIN) > 500) { 
            solveChallenge2(); // פותר חידה 2
        }
        break;

    case 2:
        if (digitalRead(BUTTON_GREEN_PIN) == LOW) { 
            solveChallenge3(); // פותר חידה 3
        }
        break;

    case 3:
        solveChallenge4(); // פותר חידה 4
        break;

    default:
        Serial.println("All challenges solved!"); // כל החידות נפתרו
        break;
    }

    delay(100); // מונע עבודה מאומצת מדי של הלולאה
}

//מה אומר
