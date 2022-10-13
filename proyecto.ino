//SE AGREGA LIBRERÍAS DE LCD
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
int sensor = 2;
int temp, humedad; 
#include <DHT.h>
LiquidCrystal_I2C lcd(0x27,16,2);
DHT dht (sensor, DHT11); 
#include <ThreeWire.h>  
#include <RtcDS1302.h>
//SE CREA Y CONFIGURA OBJETO PARA MANEJAR RTC
ThreeWire myWire(4,5,3); //PINES IO, SCLK, CE -> DE RTC DS1302
RtcDS1302<ThreeWire> Rtc(myWire);

void setup () {
    Rtc.Begin();// SE INICIALIZA RTC
    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);//SE CONFIGURA FECHA Y HORA ACTUAL
    printDateTime(compiled); //SE IMPRIME FECHA Y HORA
    Serial.println();
    dht.begin();

  // SE INICAR MONITOR SERIE E IMPRIME FECHA Y HORA
  
   
    Serial.begin(57600);
    Serial.print("CONFIGURACIÓN INICIAL ");
    Serial.print(__DATE__);
    Serial.println(__TIME__);
    
    lcd.init();
    lcd.backlight();
    lcd.clear();
    
 
}

void loop () {
  //DHT PARTE
    humedad = dht.readHumidity();
    temp = dht.readTemperature();
    Serial.print("Temperatura: "); 
    Serial.print(temp);
    Serial.print("ºC Humedad: "); 
    Serial.print(humedad); 
    Serial.println("%");
    delay (500);
    if (humedad >= 35)
    {
      Serial.println("Esta empezando estar humedo");    
    }
    delay(500);
    if (temp >= 23){
      Serial.println("Hace calorsito");
    }
    delay (500);

  //RTC PARTE
    RtcDateTime now = Rtc.GetDateTime();
    printDateTime(now);
    Serial.println();
    if (!now.IsValid()){
        Serial.println("ERROR EN FECHA Y HORA");
    }
    delay(2000); 
}

#define countof(a) (sizeof(a) / sizeof(a[0]))

//FUNCION PARA IMPRIMIR FECHA Y HORA CON FORMATO ADECUADO
void printDateTime(const RtcDateTime& dt){
    char datestring[20];
    snprintf_P(datestring, 
            countof(datestring),
            PSTR("%02u/%02u/%04u %02u:%02u:%02u"),//SE CONFURA FORMATO DE FECHA Y HORA
            dt.Month(),
            dt.Day(),
            dt.Year(),
            dt.Hour(),
            dt.Minute(),
            dt.Second() );
    //SE IMPRIME LA FECHA Y HORA EN LCD
    lcd.setCursor(0,0);
    lcd.print("DIA  ");
    lcd.print(dt.Month());
    lcd.print("/");
    lcd.print(dt.Day());
    lcd.print("/");
    lcd.print(dt.Year());
    lcd.setCursor(0,14);
    lcd.print(".");
    lcd.setCursor(15,0);
    lcd.print(" ");
    lcd.setCursor(0,1);
    lcd.print("HORA  ");
    lcd.print(dt.Hour());
    lcd.print(":");
    lcd.print(dt.Minute());
    lcd.print(":");
    lcd.print(dt.Second());
    lcd.setCursor(13,1);
    lcd.print("   ");
    Serial.print(datestring);//SE IMPRIME EN MONITOR SERIE
    delay (3000);
    lcd.clear();
    lcd.setCursor(0, 0); //Posicion: columna cero fila cero
    lcd.print("Temperatura:");
    lcd.print(temp);
    lcd.print(" C");
    lcd.setCursor(0,1);
    lcd.print("Humedad: ");
    lcd.setCursor(12,1);
    lcd.print(humedad);
    lcd.print(" %");
 
    
    
}
