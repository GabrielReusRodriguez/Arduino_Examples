//Incluimos la libreria
#include <DHT.h>
//#include <LiquidCrystal.h>

//Defino el pin digital donde se conecta el sensor
#define DHTPIN 3

#define DHTTYPE DHT22


//const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 
  // Comenzamos el sensor DHT
  dht.begin();
/*
    // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Temperature");
  lcd.setCursor(0, 1);
  lcd.print("v1.0 :)");*/


  
}

void loop() {
  // put your main code here, to run repeatedly:
    // Esperamos 5 segundos entre medidas
  delay(5000);
 
  // Leemos la humedad relativa
  float h = dht.readHumidity();
  // Leemos la temperatura en grados centígrados (por defecto)
  float t = dht.readTemperature();
  // Leemos la temperatura en grados Fahrenheit
  float f = dht.readTemperature(true);
 
  // Comprobamos si ha habido algún error en la lectura
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Error obteniendo los datos del sensor DHT11");
    return;
  }
 
  // Calcular el índice de calor en Fahrenheit
  float hif = dht.computeHeatIndex(f, h);
  // Calcular el índice de calor en grados centígrados
  float hic = dht.computeHeatIndex(t, h, false);

 //lcd.print("hello, world!");
 /*
  lcd.setCursor(0, 0);
  lcd.print("T: ");
  lcd.print(t);
  lcd.print(" - ");
  lcd.print(hic);
  lcd.print(" *C");

  lcd.setCursor(0, 1);
  lcd.print("H: ");
  lcd.print(h);
  lcd.print(" %");
*/
  
  //Serial.print(f);
  //Serial.print(" *F\t");
  //lcd.print("Calor: ");
  //lcd.print(hic);
  //lcd.print(" *C ");
  //Serial.print(hif);
  //Serial.print(" *F");
  //Serial.print("\n");

  Serial.print("Humedad: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Índice de calor: ");
  Serial.print(hic);
  Serial.print(" *C ");
  Serial.print(hif);
  Serial.print(" *F");
  Serial.print("\n");
 
}
