#ifndef CONFIG_H
#define CONFIG_H

// ספריות נדרשות ל-ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DIYables_4Digit7Segment_74HC595.h>

// הגדרת פינים לחיבור החומרה
#define SCLK D5  
#define RCLK D6 
#define DIO D7  
#define LOCKING_PIN D4  

// הגדרת שם וסיסמה לרשת ה-WiFi
const char* ssid = "NartRamadan";
const char* password = "19911991";

// הגדרת כתובת IP לשרת
IPAddress apIP(12, 34, 56, 78);

// הגדרת משתנים לניהול מצב המשחק
String gamePassword = "1234"; // קוד ברירת מחדל לנעילה
unsigned long wifiMillisTime = 0;

// יצירת אובייקט לשרת ולתצוגת 7-סגמנט
ESP8266WebServer server(80);
DIYables_4Digit7Segment_74HC595 display(SCLK, RCLK, DIO);

#endif
