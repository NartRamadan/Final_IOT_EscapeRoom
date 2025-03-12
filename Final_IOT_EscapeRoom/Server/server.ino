#include "config.h"
#include "html.h"

// אם הנתיב של הבקשה לא נמצא → מחזיר 404
void handleNotFound() {
    server.send(404, "text/plain", "404 - Not Found");
}

// טיפול בקוד שמוזן על ידי המשתמש
void handleMissionCompleted() {
    if (server.hasArg("password")) { // בודק אם נשלח פרמטר בשם "password"
        String inputPassword = server.arg("password");

        if (inputPassword == secretCode) {
            digitalWrite(LOCKING_PIN, LOW); // פותח את הנעילה
            server.send(200, "text/html", generateHTML("הדלת נפתחה!"));
        } else {
            server.send(200, "text/html", generateHTML("קוד שגוי, נסה שוב."));
        }
    } else {
        server.send(200, "text/html", generateHTML("הכנס את הקוד הסודי"));
    }
}

// הגדרת חיבור ל-WiFi והפעלת השרת
void wifiSetup() {
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid, password); // מגדיר את ה-ESP כנקודת גישה
    WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0)); // הגדרת כתובת IP

    pinMode(LOCKING_PIN, OUTPUT); // מגדיר את פין הנעילה כיציאה
    display.clear(); // מנקה את התצוגה
    display.printInt(0, true); // מציג 0 בתצוגה

    server.on("/", handleMissionCompleted); // מאזין לבקשות לנתיב הראשי "/"
    server.onNotFound(handleNotFound); // מאזין לבקשות לנתיב לא מוגדר

    server.begin(); // מפעיל את השרת
    Serial.println("שרת פעיל על IP: " + apIP.toString());
}

// מאזין ללקוחות ומרענן את התצוגה
void wifiLoop() {
    if (millis() - wifiMillisTime >= 10) {
        wifiMillisTime = millis();
        server.handleClient(); // מאזין לבקשות HTTP חדשות
    }
    display.loop(); // מעדכן את התצוגה
}

void setup() {
    Serial.begin(9600); // אתחול תקשורת סריאלית
    wifiSetup(); // קריאה לפונקציה שמאתחלת את החיבור
}

void loop() {
    wifiLoop(); // קריאה לפונקציה שמטפלת בבקשות HTTP
}
