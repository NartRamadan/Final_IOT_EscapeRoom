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

// פתרון חידה 1 – שליטה על התאורה
void solveChallenge1() {
    analogWrite(LIGHT_PIN, 204); // עמעום תאורה ל-80% עוצמה
    delay(2000); // ממתין 2 שניות
    analogWrite(LIGHT_PIN, 255); // מחזיר את התאורה לעוצמה מלאה
    
    challengeSolved[0] = true; // מעדכן שחידה 1 נפתרה
    currentStage++; // מקדם את שלב המשחק
    
    revealNextDigit(1); // שליחת הודעה לשרת על פתרון חידה 1
}

// פתרון חידה 2 – בקרת טמפרטורה
void solveChallenge2() {
    digitalWrite(FAN_PIN, HIGH); // מפעיל את המאוורר
    delay(2000); // ממתין 2 שניות
    digitalWrite(FAN_PIN, LOW); // מכבה את המאוורר
    
    challengeSolved[1] = true; // מעדכן שחידה 2 נפתרה
    currentStage++; // מקדם את שלב המשחק
    
    revealNextDigit(2); // שליחת הודעה לשרת על פתרון חידה 2
}

// פתרון חידה 3 – זיהוי רצף הבהובים
void solveChallenge3() {
    int sequence[] = {LED_RED, LED_GREEN, LED_RED, LED_GREEN}; // רצף ההבהובים
    
    // מהבהב בסדר הרצף
    for (int i = 0; i < 4; i++) {
        digitalWrite(sequence[i], HIGH);
        delay(500);
        digitalWrite(sequence[i], LOW);
        delay(500);
    }
    
    challengeSolved[2] = true; // מעדכן שחידה 3 נפתרה
    currentStage++; // מקדם את שלב המשחק
    
    revealNextDigit(3); // שליחת הודעה לשרת על פתרון חידה 3
}

// פתרון חידה 4 – מדידת מרחק
void solveChallenge4() {
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
    
    if (distance <= 20) { // אם המרחק קטן מ-20 ס"מ
        delay(2000); // ממתין 2 שניות
        challengeSolved[3] = true; // מעדכן שחידה 4 נפתרה
        currentStage++; // מקדם את שלב המשחק
        
        revealNextDigit(4); // שליחת הודעה לשרת על פתרון חידה 4
    }
}

#endif
