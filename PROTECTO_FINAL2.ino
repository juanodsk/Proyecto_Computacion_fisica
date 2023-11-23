#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

//Crear el objeto lcd  dirección  0x3F y 16 columnas x 2 filas
LiquidCrystal_I2C lcd(0x27,16,2);  //
#include "DHT.h" 
#define DHTPIN 5 
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Inicializar el LCD
  lcd.init();
  Serial.begin(9600); 
  dht.begin();
  //Encender la luz de fondo.
  lcd.backlight();
  
  // Escribimos el Mensaje en el LCD.
  float temperatura = dht.readTemperature();
  lcd.print("Temp. =");
  lcd.print(temperatura);
   lcd.print(" C");

}

void loop() {
   // Ubicamos el cursor en la primera posición(columna:0) de la segunda línea(fila:1)
  int humedad = dht.readHumidity();
   lcd.setCursor(0,1); // Siguiente renglón.
lcd.print("Humedad = ");
lcd.print(humedad);
lcd.print("%");

delay(200);
  delay(100);
}