#include "config.h"
#include "html.h"

// משתנים לניהול התצוגה
int revealedDigits = 0; // מספר הספרות שנחשפו
int displayCode[4] = {0, 0, 0, 0}; // הקוד שמוצג בתצוגה

// API endpoint לקבלת עדכונים מהלקוח
void handleAPI() {
    if (server.hasArg("missionCode")) {
        int missionCode = server.arg("missionCode").toInt();
        
        if (missionCode >= 1 && missionCode <= 4 && revealedDigits < 4) {
            // חושף ספרה נוספת מהקוד הסודי
            displayCode[revealedDigits] = secretCode.charAt(missionCode - 1) - '0';
            revealedDigits++;
            
            // מעדכן את התצוגה
            updateDisplay();
            
            Serial.println("Mission " + String(missionCode) + " completed! Revealed digit: " + String(displayCode[revealedDigits-1]));
        }
        
        server.send(200, "text/plain", "OK");
    } else {
        server.send(400, "text/plain", "Missing missionCode parameter");
    }
}

// פונקציה לעדכון התצוגה
void updateDisplay() {
    if (revealedDigits == 0) {
        display.printInt(0, true);
    } else {
        // מציג את הספרות שנחשפו עד כה
        int displayValue = 0;
        for (int i = 0; i < revealedDigits; i++) {
            displayValue = displayValue * 10 + displayCode[i];
        }
        display.printInt(displayValue, true);
    }
}

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
    digitalWrite(LOCKING_PIN, HIGH); // נעילה סגורה בהתחלה
    
    display.clear(); // מנקה את התצוגה
    updateDisplay(); // מציג 0 בתצוגה

    server.on("/", handleMissionCompleted); // מאזין לבקשות לנתיב הראשי "/"
    server.on("/api", handleAPI); // מאזין לבקשות API
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
