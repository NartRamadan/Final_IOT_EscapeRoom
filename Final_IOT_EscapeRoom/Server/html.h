#ifndef HTML_H
#define HTML_H

// פונקציה המחזירה HTML לפי המצב הנוכחי של המשחק
String generateHTML(String message = "") {
    String html = R"rawliteral(
        <!DOCTYPE html>
        <html lang="he">
        <head>
            <meta charset="UTF-8">
            <title>Escape Room</title>
            <style>
                body {
                    font-family: Arial, sans-serif;
                    background-color: #111;
                    color: #fff;
                    text-align: center;
                    padding: 20px;
                }
                input, button {
                    padding: 10px;
                    margin: 10px;
                    font-size: 16px;
                }
            </style>
        </head>
        <body>
            <h1>Enter Code</h1>
            <form method="get">
                <input type="text" name="password" maxlength="4" placeholder="****" required>
                <button type="submit">Open Lock</button>
            </form>
    )rawliteral";

    // אם יש הודעה (כמו הצלחה או כישלון), מוסיף אותה לדף ה-HTML
    if (message.length() > 0) {
        html += "<p>" + message + "</p>";
    }

    html += R"rawliteral(
        </body>
        </html>
    )rawliteral";

    return html; // מחזיר את קוד ה-HTML שנוצר
}

#endif
