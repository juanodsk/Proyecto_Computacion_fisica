#include <DHT.h>
#include <DHT_U.h>
#include <Servo.h>
#include <SoftwareSerial.h>


const int ledPin = 13;
const int ldrPin = A0;
const int ledHab = 12;
const int soundSensorPin = 2; // Cambiado de LED a soundSensorLED
const int soundSensorLED = 12; // Cambiado de LED a soundSensorLED


Servo myServo;
SoftwareSerial miBT(10, 11);
char dato;


int analogPin = 0;
int valorLDR = 0;
int umbralNumber = 900;
int LED = 13;


void setup() {
  Serial.begin(9600);
  Serial.println("listo");
  miBT.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  myServo.attach(5);
  pinMode(ledPin, OUTPUT);
  pinMode(ldrPin, INPUT);
  pinMode(ledHab, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(soundSensorPin, INPUT);
  pinMode(soundSensorLED, OUTPUT);


  onOffLeds();
}


void loop() {
  if (miBT.available()) {
    dato = miBT.read();
    Serial.print("Dato recibido: ");
    Serial.println(dato);


    onOffLeds();


    if (dato == 'a')
      abrirPuerta();
    else if (dato == 'c')
      cerrarPuerta();
    else if (dato == 'b')
      encenderLedHab();
    else if (dato == 'd')
      apagarLedHab();
  }


  int ldrStatus = analogRead(ldrPin);
  if (ldrStatus > 300) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }


  valorLDR = analogRead(analogPin);
  if (valorLDR >= umbralNumber) {
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(LED, LOW);
  }


  int statusSensor = digitalRead(soundSensorPin);
  if (statusSensor == 1) {
    digitalWrite(soundSensorLED, HIGH);
  } else {
    digitalWrite(soundSensorLED, LOW);
  }
}


void onOffLeds() {
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  delay(100);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  delay(100);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  delay(100);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
}


void cerrarPuerta() {
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  int angulo = 0;
  do {
    angulo = angulo + 1;
    myServo.write(angulo);
    delay(50);
  } while (angulo < 90);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
}


void abrirPuerta() {
  digitalWrite(3, HIGH);
  digitalWrite(4, LOW);
  int angulo = 90;
  do {
    angulo = angulo - 1;
    myServo.write(angulo);
    delay(50);
  } while (angulo > 0);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
}


void encenderLedHab() {
  digitalWrite(12, HIGH);
}


void apagarLedHab() {
  digitalWrite(12, LOW);
}

