#include <Wire.h>
#include "RTClib.h"
#include  <LiquidCrystal_I2C.h>

 
// RTC_DS1307 rtc;
RTC_DS3231 rtc;
LiquidCrystal_I2C lcd(0x3F, 20,4);
//LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3,);
//0x3F
//0x57
//0x68

String daysOfTheWeek[7] = { "Domingo", "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado" };
String monthsNames[12] = { "Enero", "Febrero", "Marzo", "Abril", "Mayo",  "Junio", "Julio","Agosto","Septiembre","Octubre","Noviembre","Diciembre" };

void initLcd(){
  
  lcd.init();
  lcd.backlight();
  // Indicar a la libreria que tenemos conectada una pantalla de 16x2
 // lcd.begin(20, 4);
  // Mover el cursor a la primera posición de la pantalla (0, 0)
 // lcd.clear();
  // Imprimir "Hola Mundo" en la primera linea
  lcd.print(" GEEKFACTORY.MX ");
  // Esperar un segundo
  delay(1000);
}

void initClock(){
 
   if (!rtc.begin()) {
      Serial.println(F("Couldn't find RTC"));
      while (1);
   }
 
   // Si se ha perdido la corriente, fijar fecha y hora
   if (rtc.lostPower()) {
      // Fijar a fecha y hora de compilacion
      rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
      
      // Fijar a fecha y hora específica. En el ejemplo, 21 de Enero de 2016 a las 03:00:00
      // rtc.adjust(DateTime(2016, 1, 21, 3, 0, 0));
   } 
}

void initSerial(){
   Serial.begin(9600);
}
  
void setup() {
  
    initSerial();
    initLcd();
    initClock();
    delay(1000); 
}
 
void printDate2Serial(DateTime date)
{
   Serial.print(date.year(), DEC);
   Serial.print('/');
   Serial.print(date.month(), DEC);
   Serial.print('/');
   Serial.print(date.day(), DEC);
   Serial.print(" (");
   Serial.print(daysOfTheWeek[date.dayOfTheWeek()]);
   Serial.print(") ");
   Serial.print(date.hour(), DEC);
   Serial.print(':');
   Serial.print(date.minute(), DEC);
   Serial.print(':');
   Serial.print(date.second(), DEC);
   Serial.println();
}

void printNumeroDecimal2Lcd(int numero){
  
  if(numero < 10){
    lcd.print(0,DEC);  
  }
  lcd.print(numero,DEC);
}

void printDate2Lcd(DateTime date)
{
   lcd.home();
   printNumeroDecimal2Lcd(date.day());
   lcd.print('/');
   printNumeroDecimal2Lcd(date.month());
   lcd.print('/');
   printNumeroDecimal2Lcd(date.year());
   lcd.print(" (");
   lcd.print(daysOfTheWeek[date.dayOfTheWeek()]);
   lcd.print(") ");
   
   lcd.setCursor(0,1);
   printNumeroDecimal2Lcd(date.hour());
   lcd.print(':');
   printNumeroDecimal2Lcd(date.minute());
   lcd.print(':');
   printNumeroDecimal2Lcd(date.second());
}

 
void loop() {
   // Obtener fecha actual y mostrar por Serial
   DateTime now = rtc.now();
   printDate2Serial(now);
   printDate2Lcd(now);
  //lcd.print(" GEEKFACTORY.MX ");
   delay(1000);
}
