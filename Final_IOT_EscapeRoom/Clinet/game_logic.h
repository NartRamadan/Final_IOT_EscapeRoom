#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "config.h"

// פונקציה לשליחת עדכון לשרת על פתרון חידה
void revealNextDigit(int digit) {
    WiFiClient client;
    
    // פותח חיבור לשרת
    if (client.connect("12.34.56.78", 80)) {
        client.print("GET /api?missionCode=" + String(digit) + " HTTP/1.1\r\n");
        client.print("Host: 12.34.56.78\r\n");
        client.print("Connection: close\r\n\r\n");
        client.stop(); // סוגר את החיבור לאחר השליחה
    }
}

// פונקציה להמרת קריאת חיישן טמפרטורה לטמפרטורה בפועל
float getTemperature() {
    int sensorValue = analogRead(TEMP_SENSOR_PIN);
    // המרה לקריאת טמפרטורה (התאם לפי החיישן שלך)
    float voltage = sensorValue * (3.3 / 1023.0);
    float temperature = (voltage - 0.5) * 100; // עבור LM35
    return temperature;
}

// פונקציה ליצירת רצף אקראי של הבהובים
void generateRandomSequence() {
    for (int i = 0; i < 8; i++) {
        ledSequence[i] = random(2) == 0 ? LED_RED : LED_GREEN;
    }
}

// פונקציה למדידת מרחק
int getDistance() {
    long duration;
    int distance;
    
    // שליחת אות לחיישן מרחק
    digitalWrite(DISTANCE_SENSOR_TRIGGER_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(DISTANCE_SENSOR_TRIGGER_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(DISTANCE_SENSOR_TRIGGER_PIN, LOW);

    // מדידת האות שחזר מחיישן המרחק
    duration = pulseIn(DISTANCE_SENSOR_ECHO_PIN, HIGH);
    distance = duration * 0.034 / 2; // חישוב מרחק בס"מ
    
    return distance;
}

// פתרון חידה 1 – שליטה על התאורה
void solveChallenge1() {
    analogWrite(LIGHT_PIN, 204); // עמעום תאורה ל-80% עוצמה (255 * 0.8 = 204)
    delay(2000); // ממתין 2 שניות
    analogWrite(LIGHT_PIN, 255); // מחזיר את התאורה לעוצמה מלאה
    
    challengeSolved[0] = true; // מעדכן שחידה 1 נפתרה
    currentStage++; // מקדם את שלב המשחק
    
    // מתחיל חידה 2
    initialTemperature = getTemperature();
    temperatureChallengeActive = true;
    temperatureStartTime = millis();
    
    revealNextDigit(1); // שליחת הודעה לשרת על פתרון חידה 1
}

// פתרון חידה 2 – בקרת טמפרטורה
void solveChallenge2() {
    if (!temperatureChallengeActive) return;
    
    float currentTemp = getTemperature();
    unsigned long currentTime = millis();
    
    // בודק אם הטמפרטורה ירדה ב-2°C
    if (currentTemp <= (initialTemperature - 2.0)) {
        if (currentTime - temperatureStartTime >= 2000) { // 2 שניות
            digitalWrite(FAN_PIN, LOW); // מכבה את המאוורר
            temperatureChallengeActive = false;
            
            challengeSolved[1] = true; // מעדכן שחידה 2 נפתרה
            currentStage++; // מקדם את שלב המשחק
            
            // מתחיל חידה 3
            generateRandomSequence();
            sequencePlaying = true;
            currentSequenceIndex = 0;
            
            revealNextDigit(2); // שליחת הודעה לשרת על פתרון חידה 2
        }
    } else {
        // אם הטמפרטורה לא ירדה מספיק, מפעיל מאוורר
        digitalWrite(FAN_PIN, HIGH);
        temperatureStartTime = currentTime; // מאפס את הטיימר
    }
}

// פתרון חידה 3 – זיהוי רצף הבהובים
void solveChallenge3() {
    if (!sequencePlaying && !waitingForInput) return;
    
    if (sequencePlaying) {
        // מנגן את הרצף
        if (currentSequenceIndex < 8) {
            unsigned long currentTime = millis();
            static unsigned long lastBlink = 0;
            
            if (currentTime - lastBlink >= 500) { // הבהוב כל 500ms
                digitalWrite(ledSequence[currentSequenceIndex], HIGH);
                delay(200);
                digitalWrite(ledSequence[currentSequenceIndex], LOW);
                currentSequenceIndex++;
                lastBlink = currentTime;
            }
        } else {
            // סיים להציג את הרצף, מתחיל לקבל קלט
            sequencePlaying = false;
            waitingForInput = true;
            userInputIndex = 0;
        }
    }
}

// פונקציה לטיפול בקלט מהמשתמש בחידה 3
void handleUserInput(int buttonPressed) {
    if (!waitingForInput) return;
    
    if (buttonPressed == ledSequence[userInputIndex]) {
        userInputIndex++;
        
        if (userInputIndex >= 8) {
            // כל הרצף נכון
            waitingForInput = false;
            challengeSolved[2] = true;
            currentStage++;
            
            // מתחיל חידה 4
            distanceChallengeActive = true;
            distanceStartTime = millis();
            
            revealNextDigit(3);
        }
    } else {
        // טעות ברצף - מתחיל מחדש
        waitingForInput = false;
        sequencePlaying = true;
        currentSequenceIndex = 0;
        userInputIndex = 0;
    }
}

// פתרון חידה 4 – מדידת מרחק
void solveChallenge4() {
    if (!distanceChallengeActive) return;
    
    int distance = getDistance();
    unsigned long currentTime = millis();
    
    if (distance <= 20) {
        if (!distanceMaintained) {
            distanceStartTime = currentTime;
            distanceMaintained = true;
        } else if (currentTime - distanceStartTime >= 2000) {
            // החזיק יד במרחק הנכון למשך 2 שניות
            distanceChallengeActive = false;
            distanceMaintained = false;
            
            challengeSolved[3] = true;
            currentStage++;
            
            revealNextDigit(4);
        }
    } else {
        // המרחק לא נכון - מאפס את הטיימר
        distanceMaintained = false;
    }
}

#endif
