#ifndef CONFIG_H
#define CONFIG_H

// ספריות נדרשות ל-ESP8266 (WiFi ותצוגת 7-סגמנט)
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DIYables_4Digit7Segment_74HC595.h>

// הגדרת פינים לחיבור החומרה
#define SCLK D5  // פין ל-Clock של ה-7-סגמנט
#define RCLK D6  // פין ל-Latch של ה-7-סגמנט
#define DIO D7   // פין לדאטה של ה-7-סגמנט
#define LOCKING_PIN D4  // פין שמחובר למנעול האלקטרוני

// הגדרת שם וסיסמה לרשת ה-WiFi
const char* ssid = "NartRamadan"; // שם הרשת
const char* password = "19911991"; // סיסמה לרשת

// הגדרת כתובת IP לשרת
IPAddress apIP(12, 34, 56, 78); // כתובת IP סטטית לשרת

// הגדרת משתנים לניהול מצב המשחק
String gamePassword = ""; // מחזיק את הקוד שמוזן על ידי המשתמש
String secretCode = "1234"; // הקוד הסודי שנחשף בהדרגה
unsigned long wifiMillisTime = 0; // משתנה לסנכרון זמן עם millis()

// יצירת אובייקטים לשרת ולתצוגת 7-סגמנט
ESP8266WebServer server(80); // יצירת שרת HTTP על פורט 80
DIYables_4Digit7Segment_74HC595 display(SCLK, RCLK, DIO); // יצירת אובייקט לתצוגת 7-סגמנט

#endif
