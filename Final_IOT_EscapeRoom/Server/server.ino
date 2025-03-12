#include "config.h"
#include "html.h"

// טיפול במקרה של כתובת לא מוכרת
void handleNotFound() {
    server.send(404, "text/plain", "404 - Not Found");
}

// פונקציה לניהול הכנסת הקוד ונעילת הדלת
void handleMissionCompleted() {
    if (server.hasArg("password")) {
        String inputPassword = server.arg("password");

        if (inputPassword == gamePassword) {
            digitalWrite(LOCKING_PIN, LOW);
            server.send(200, "text/html", generateHTML("הדלת נפתחה!"));
        } else {
            gamePassword = ""; // איפוס הקוד אחרי ניסיון כושל
            server.send(200, "text/html", generateHTML("קוד שגוי, נסה שוב."));
        }
    } else {
        server.send(200, "text/html", generateHTML("הכנס את הקוד הסודי"));
    }
}

// פונקציה להגדרת השרת והחיבור לרשת
void wifiSetup() {
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid, password);
    WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));

    pinMode(LOCKING_PIN, OUTPUT);
    display.clear();
    display.printInt(0, true);

    server.on("/", handleMissionCompleted);
    server.onNotFound(handleNotFound);

    server.begin();
    Serial.println("שרת פעיל על IP: " + apIP.toString());
}

// פונקציה שרצה בלולאה ללא הפסקה
void wifiLoop() {
    if (millis() - wifiMillisTime >= 10) {
        wifiMillisTime = millis();
        server.handleClient();
    }
    display.loop();
}

// פונקציה להרצה פעם אחת עם הדלקת המכשיר
void setup() {
    Serial.begin(9600);
    wifiSetup();
}

// פונקציה שחוזרת על עצמה כל הזמן
void loop() {
    wifiLoop();
}
