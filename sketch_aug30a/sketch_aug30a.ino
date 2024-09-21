#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver servos = Adafruit_PWMServoDriver(0x40);

int pos0 = 102;
int pos180 = 512;

void setup() {
  servos.begin();
  servos.setPWMFreq(50);
}

void loop() {
  // Mueve el servo 5 del brazo derecho de 70 a 150 grados lentamente
  moveServo(5, 70, 170, 10);  // (n_servo, angulo_inicial, angulo_final, retraso_entre_pasos)
  delay(1000);
  
  // Mueve el servo 5 del brazo derecho de 150 a 70 grados lentamente
  moveServo(5, 170, 70, 10);  // (n_servo, angulo_inicial, angulo_final, retraso_entre_pasos)
  delay(1000);
//brazo izquierdo
  moveServo(7, 0, 90, 10);  // (n_servo, angulo_inicial, angulo_final, retraso_entre_pasos)
  delay(1000);
  

  moveServo(7, 90, 0, 10);  // (n_servo, angulo_inicial, angulo_final, retraso_entre_pasos)
  delay(1000);

//cabeza servo 6

  moveServo(6, 30, 150, 10);  // (n_servo, angulo_inicial, angulo_final, retraso_entre_pasos)
  delay(1000);
  

  moveServo(6, 150, 30, 10);  // (n_servo, angulo_inicial, angulo_final, retraso_entre_pasos)
  delay(1000);

//cuello 
  moveServo(8, 70, 150, 10);  // (n_servo, angulo_inicial, angulo_final, retraso_entre_pasos)
  delay(1000);
  

  moveServo(8, 150, 70, 10);  // (n_servo, angulo_inicial, angulo_final, retraso_entre_pasos)
  delay(1000);


}

void moveServo(uint8_t n_servo, int startAngle, int endAngle, int stepDelay) {
  if (startAngle < endAngle) {
    for (int angle = startAngle; angle <= endAngle; angle++) {
      setServo(n_servo, angle);
      delay(stepDelay);
    }
  } else {
    for (int angle = startAngle; angle >= endAngle; angle--) {
      setServo(n_servo, angle);
      delay(stepDelay);
    }
  }
}

void setServo(uint8_t n_servo, int angulo) {
  int duty;
  duty = map(angulo, 0, 180, pos0, pos180);
  servos.setPWM(n_servo, 0, duty);
}
