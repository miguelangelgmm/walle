#include <Servo.h>

// Crea un objeto Servo para controlar el servo
Servo myServo;

void setup() {
  // Asigna el pin al servo
  myServo.attach(8);

  // Mueve el servo a 90 grados
  myServo.write(90);

  // Espera 10 segundos (10000 milisegundos)
  delay(10000);

  // Mueve el servo a 180 grados
  //myServo.write(180);
}

void loop() {
  // No es necesario colocar nada en loop() para este ejemplo
}
