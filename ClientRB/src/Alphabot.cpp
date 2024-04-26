#include <alphabot.h>

void AlphaBot::forward() {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    digitalWrite(ENA, HIGH);
    digitalWrite(ENB, HIGH);
}

void AlphaBot::stop() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    digitalWrite(ENA, LOW);
    digitalWrite(ENB, LOW);
}

void AlphaBot::left() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    digitalWrite(ENA, HIGH);
    digitalWrite(ENB, HIGH);
}

void AlphaBot::right() {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    digitalWrite(ENA, HIGH);
    digitalWrite(ENB, HIGH);
}
