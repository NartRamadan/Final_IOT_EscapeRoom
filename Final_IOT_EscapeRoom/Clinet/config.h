#ifndef CONFIG_H
#define CONFIG_H

// ספריות נדרשות ל-ESP8266
#include <ESP8266WiFi.h>

// פינים לחיבור חיישנים ונוריות
#define LIGHT_PIN D1
#define FAN_PIN D2
#define TEMP_SENSOR_PIN A0
#define BUTTON_RED_PIN D3
#define BUTTON_GREEN_PIN D4
#define DISTANCE_SENSOR_TRIGGER_PIN D5
#define DISTANCE_SENSOR_ECHO_PIN D6
#define LED_RED D7
#define LED_GREEN D8

// משתנים למצב המשחק
int currentStage = 0; // עוקב אחרי השלב הנוכחי של המשחק
bool challengeSolved[4] = {false, false, false, false};

#endif
