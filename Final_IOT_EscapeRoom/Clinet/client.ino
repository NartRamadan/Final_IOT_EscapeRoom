#include "config.h"
#include "game_logic.h"

// משתנים לניהול התאורה הראשונית
bool roomLightOn = false; // האם האור בחדר דולק
bool doorLocked = false; // האם הדלת נעולה

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
    
    // אתחול גנרטור מספרים אקראיים
    randomSeed(analogRead(A0));
    
    // אתחול מצב התאורה - כבוי בהתחלה
    analogWrite(LIGHT_PIN, 0);
    Serial.println("Escape Room Ready! Turn on the light to start...");
}

void loop() {
    // בדיקה אם האור הודלק בפעם הראשונה (בדיקה של חיישן אור או כפתור)
    if (!roomLightOn && digitalRead(BUTTON_RED_PIN) == LOW) {
        roomLightOn = true;
        doorLocked = true;
        Serial.println("Light turned on! Door is now locked. Solve the challenges to escape!");
        
        // הדלקת האור בעוצמה מלאה
        analogWrite(LIGHT_PIN, 255);
        delay(1000); // מניעת ריבאונד
    }
    
    // רק אם הדלת נעולה, מתחיל את החידות
    if (doorLocked) {
        switch (currentStage) {
        case 0: 
            // חידה 1 - שליטה על התאורה
            if (digitalRead(BUTTON_GREEN_PIN) == LOW) { 
                solveChallenge1(); // פותר חידה 1
            }
            break;

        case 1:
            // חידה 2 - בקרת טמפרטורה
            solveChallenge2(); // פותר חידה 2
            break;

        case 2:
            // חידה 3 - רצף הבהובים
            solveChallenge3(); // מטפל בחידה 3
            
            // בדיקת קלט מהמשתמש (בחידה 3)
            if (digitalRead(BUTTON_RED_PIN) == LOW) {
                handleUserInput(LED_RED);
                delay(200); // מניעת ריבאונד
            }
            if (digitalRead(BUTTON_GREEN_PIN) == LOW) {
                handleUserInput(LED_GREEN);
                delay(200); // מניעת ריבאונד
            }
            break;

        case 3:
            // חידה 4 - מדידת מרחק
            solveChallenge4(); // פותר חידה 4
            break;

        default:
            Serial.println("All challenges solved! Enter the code on the server to unlock the door!");
            break;
        }
    }

    delay(100); // מונע עבודה מאומצת מדי של הלולאה
}
