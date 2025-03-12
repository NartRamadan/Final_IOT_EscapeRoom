#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "config.h"

void solveChallenge1() {
    analogWrite(LIGHT_PIN, 204);
    delay(2000);
    analogWrite(LIGHT_PIN, 255);
    challengeSolved[0] = true;
    currentStage++;
    Serial.println("Challenge 1 solved");

    WiFiClient client;
    if (client.connect("12.34.56.78", 80)) {
        client.print("GET /api?missionCode=1 HTTP/1.1\r\n");
        client.print("Host: 12.34.56.78\r\n");
        client.print("Connection: close\r\n\r\n");
        client.stop();
    }
}

void solveChallenge2() {
    digitalWrite(FAN_PIN, HIGH);
    delay(2000);
    digitalWrite(FAN_PIN, LOW);
    challengeSolved[1] = true;
    currentStage++;
    Serial.println("Challenge 2 solved");

    WiFiClient client;
    if (client.connect("12.34.56.78", 80)) {
        client.print("GET /api?missionCode=2 HTTP/1.1\r\n");
        client.print("Host: 12.34.56.78\r\n");
        client.print("Connection: close\r\n\r\n");
        client.stop();
    }
}

void solveChallenge3() {
    int sequence[] = {LED_RED, LED_GREEN, LED_RED, LED_GREEN};
    for (int i = 0; i < 4; i++) {
        digitalWrite(sequence[i], HIGH);
        delay(500);
        digitalWrite(sequence[i], LOW);
        delay(500);
    }
    challengeSolved[2] = true;
    currentStage++;
    Serial.println("Challenge 3 solved");

    WiFiClient client;
    if (client.connect("12.34.56.78", 80)) {
        client.print("GET /api?missionCode=3 HTTP/1.1\r\n");
        client.print("Host: 12.34.56.78\r\n");
        client.print("Connection: close\r\n\r\n");
        client.stop();
    }
}

void solveChallenge4() {
    long duration;
    int distance;
    
    digitalWrite(DISTANCE_SENSOR_TRIGGER_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(DISTANCE_SENSOR_TRIGGER_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(DISTANCE_SENSOR_TRIGGER_PIN, LOW);

    duration = pulseIn(DISTANCE_SENSOR_ECHO_PIN, HIGH);
    distance = duration * 0.034 / 2;

    if (distance <= 20) {
        delay(2000);
        challengeSolved[3] = true;
        currentStage++;
        Serial.println("Challenge 4 solved");

        WiFiClient client;
        if (client.connect("12.34.56.78", 80)) {
            client.print("GET /api?missionCode=4 HTTP/1.1\r\n");
            client.print("Host: 12.34.56.78\r\n");
            client.print("Connection: close\r\n\r\n");
            client.stop();
        }
    }
}

#endif
