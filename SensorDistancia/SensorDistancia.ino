#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#define WHITE_LINE "                    "

long tiempo;
int disparador = 4;   // triger
int entrada = 2;      // echo
float distancia;

LiquidCrystal_I2C lcd(0x3F,20,4);  //

void setup() {
  // put your setup code here, to run once:
  pinMode(disparador, OUTPUT);
  pinMode(entrada, INPUT);
  
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();
  lcd.print("Distance detect v1.0");
}

void loop() {
  // put your main code here, to run repeatedly:
// lanzamos un pequeño pulso para activar el sensor
  digitalWrite(disparador, HIGH);
  delayMicroseconds(10);
  digitalWrite(disparador, LOW);
  
  // medimos el pulso de respuesta
  tiempo = (pulseIn(entrada, HIGH)/2); // dividido por 2 por que es el 
                                       // tiempo que el sonido tarda
                                       // en ir y en volver
  // ahora calcularemos la distancia en cm
  // sabiendo que el espacio es igual a la velocidad por el tiempo
  // y que la velocidad del sonido es de 343m/s y que el tiempo lo 
  // tenemos en millonesimas de segundo
  distancia = float(tiempo * 0.0343);
  
  // y lo mostramos por el puerto serie una vez por segundo
  Serial.println(distancia);
  lcd.print(WHITE_LINE);
  lcd.setCursor(0, 1);
  lcd.print(distancia);
  lcd.print(" cm");
  
  delay(1000);
}
