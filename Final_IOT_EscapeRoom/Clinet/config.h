#ifndef CONFIG_H
#define CONFIG_H

// ספריות נדרשות ל-ESP8266
#include <ESP8266WiFi.h>

// הגדרת פינים לחיבור החומרה
#define LIGHT_PIN D1 // פין לחיבור נורת תאורה
#define FAN_PIN D2 // פין לחיבור מאוורר
#define TEMP_SENSOR_PIN A0 // פין אנלוגי לחיישן טמפרטורה
#define BUTTON_RED_PIN D3 // פין לחיבור כפתור אדום
#define BUTTON_GREEN_PIN D4 // פין לחיבור כפתור ירוק
#define DISTANCE_SENSOR_TRIGGER_PIN D5 // פין להפעלת חיישן מרחק (שליחה)
#define DISTANCE_SENSOR_ECHO_PIN D6 // פין לקליטת חיישן מרחק (קליטה)
#define LED_RED D7 // פין לחיבור נורית אדומה
#define LED_GREEN D8 // פין לחיבור נורית ירוקה

// משתנים לניהול מצב המשחק
int currentStage = 0; // משתנה שמייצג את שלב המשחק הנוכחי
bool challengeSolved[4] = {false, false, false, false}; // מערך למעקב אחרי מצב פתרון החידות

// משתנים לחידה 2 - בקרת טמפרטורה
float initialTemperature = 0; // טמפרטורה התחלתית
bool temperatureChallengeActive = false; // האם חידת הטמפרטורה פעילה
unsigned long temperatureStartTime = 0; // זמן התחלת האתגר

// משתנים לחידה 3 - רצף הבהובים
int ledSequence[8]; // רצף ההבהובים (8 הבהובים)
int currentSequenceIndex = 0; // אינדקס נוכחי ברצף
bool sequencePlaying = false; // האם הרצף מתנגן
bool waitingForInput = false; // האם ממתין לקלט מהמשתמש
int userInputIndex = 0; // אינדקס הקלט של המשתמש

// משתנים לחידה 4 - מדידת מרחק
unsigned long distanceStartTime = 0; // זמן התחלת מדידת המרחק
bool distanceChallengeActive = false; // האם חידת המרחק פעילה
bool distanceMaintained = false; // האם המרחק נשמר

#endif
