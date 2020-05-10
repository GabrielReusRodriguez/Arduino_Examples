//Includes
#include<LiquidCrystal.h>

#define LINEA_EN_BLANCO "                "
//Defino los pins
const int PIN_CARDIO = A0;
const int PIN_BUZZER = 8;
const int PIN_LED = 5;
const int PIN_RS = 2, PIN_EN = 3, PIN_D4 = 9, PIN_D5 = 10, PIN_D6= 11, PIN_D7 = 12; 

LiquidCrystal lcd(PIN_RS, PIN_EN, PIN_D4, PIN_D5, PIN_D6, PIN_D7);

//Defino las variables que voy a usar.
float Pulso;
float lastVoltaje = 0.0f;
float voltaje;
int pulsaciones = 0;
float timeUltimaPulsacion = 0.0f;
float tiempoPrimeraPulsacion = 0.0f;
float difTiempoEntrePulsaciones = 0.0f;
float tiempo =0.0f;
int iteraciones = 0;
boolean limpiaPantalla = false;


//Defino las constantes
const float vReferencia = 520.0f;
const float cota = 3.2f;
const int COTA_MINIMA_PULSACIONES = 4;
const float COTA_TIEMPO_SIN_PULSACIONES = 5000.0f;
const float COTA_TIEMPO_DESDE_PRIMERA_PULSACION = 5.000f;

byte heart[8] ={
  B00000,
  B01010,
  B11111,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000,
};



//Funciones
boolean detectaPulso(){
  return (voltaje > cota && lastVoltaje < cota);
}

//Inicializaciones
void setup() {
  
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(PIN_CARDIO, INPUT);
  pinMode(PIN_LED, OUTPUT);

  lcd.begin(16,2);

  lcd.print("Cardio-Gab v2.0");
  
  lcd.createChar(0,heart);
  
}


//Bucle
void loop() {
  // put your main code here, to run repeatedly:
  //lcd.setCursor(0,0);
  //lcd.print("Cardio-Gab v2.0");
  Pulso = analogRead(PIN_CARDIO);
  voltaje = Pulso * (5.0 / 1024.0);
  tiempo = millis();

  //Check si debemos limpiar la pantalla.
  if(limpiaPantalla){
      lcd.setCursor(0,0);
      lcd.print(LINEA_EN_BLANCO);
  }else{
    limpiaPantalla = true;
  }
 
  if (detectaPulso())
  {
    //Serial.println("Detectado");
    //Sumo la pulsacion.8
    timeUltimaPulsacion = millis();
    //Si tenemos las pulsaciones a 0, guardamos el timestamp como primera pulsacion
    if(pulsaciones == 0){
      tiempoPrimeraPulsacion = timeUltimaPulsacion;
    }
    
    pulsaciones++;
    
    lcd.setCursor(0,0);
    lcd.write(byte(0));
    //PITA!!
    
    tone(PIN_BUZZER,20000);
    digitalWrite(PIN_LED,HIGH);
    delay(100);
    noTone(PIN_BUZZER);
    digitalWrite(PIN_LED,LOW);    
    limpiaPantalla = false;

    if(pulsaciones >= COTA_MINIMA_PULSACIONES){
      difTiempoEntrePulsaciones = tiempo - timeUltimaPulsacion;
      float tiempoDetectado = tiempo  - tiempoPrimeraPulsacion; 
      if(difTiempoEntrePulsaciones <=  COTA_TIEMPO_SIN_PULSACIONES && tiempoDetectado >= COTA_TIEMPO_DESDE_PRIMERA_PULSACION){
        //Pintamos las pulsaciones por minuto en caso que no hayamos pasado mas de 4 segundos sin detectar una pulsacion y de que llevemos más de 
        int pulsaciones_por_minuto = (((float)pulsaciones) / (tiempoDetectado/1000.0f))*60;
        lcd.setCursor(0,1);
        lcd.print(pulsaciones_por_minuto);
      //lcd.print("p/m");
      }
    }
  }else{
    //No hemos detectado pulso, contamos los segundos desde la  último pulso detectado y si hace más de n segundos, reseteamos las pulsaciones/min.
      difTiempoEntrePulsaciones = tiempo - timeUltimaPulsacion;
      //Serial.println(difTiempoEntrePulsaciones);
      if((difTiempoEntrePulsaciones >=  COTA_TIEMPO_SIN_PULSACIONES)){
        pulsaciones = 0;
        lcd.clear();
        lcd.setCursor(0,1);
        lcd.print("--");
        //lcd.print("p/m");
    }
  }
/*
  if(pulsaciones >= COTA_MINIMA_PULSACIONES){
    float difTiempoEntrePulsaciones = tiempo - timeUltimaPulsacion;
    float tiempoDetectado = tiempo  - tiempoPrimeraPulsacion; 
    if(difTiempoEntrePulsaciones <=  COTA_TIEMPO_SIN_PULSACIONES && tiempoDetectado >= COTA_TIEMPO_DESDE_PRIMERA_PULSACION){
      //Pintamos las pulsaciones por minuto en caso que no hayamos pasado mas de 4 segundos sin detectar una pulsacion y de que llevemos más de 
      int pulsaciones_por_minuto = (((float)pulsaciones) / (tiempoDetectado/1000.0f))*60;
      lcd.setCursor(0,1);
      lcd.print(pulsaciones_por_minuto);
      //lcd.print("p/m");
    }else{
      pulsaciones = 0;
      lcd.clear();
      lcd.setCursor(0,1);
      lcd.print("--");
      //lcd.print("p/m");
    }
  */
    lcd.setCursor(4,1);
    lcd.print("p/m");

  
  lastVoltaje = voltaje;
  Serial.println(voltaje);
  delay(100);

  //lcd.clear();
}
//https://ruclip.com/video/m3nyM40S6hQ/sensor-de-pulso-card%C3%ADaco.html
