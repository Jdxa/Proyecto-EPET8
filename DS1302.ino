//SE AGREGA LIBRERÍAS DE LCD
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2); 
//SE AGREGA LIBRERÍAS PARA RTC
#include <ThreeWire.h>  
#include <RtcDS1302.h>
//SE CREA Y CONFIGURA OBJETO PARA MANEJAR RTC
ThreeWire myWire(4,5,2); //PINES IO, SCLK, CE -> DE RTC DS1302
RtcDS1302<ThreeWire> Rtc(myWire);

void setup () {   
  // SE INICAR MONITOR SERIE E IMPRIME FECHA Y HORA
    Serial.begin(57600);
    Serial.print("CONFIGURACIÓN INICIAL ");
    Serial.print(__DATE__);
    Serial.println(__TIME__);
    lcd.begin(16,2); //SE INICIARLIZA LCD
    Rtc.Begin();// SE INICIALIZA RTC
    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);//SE CONFIGURA FECHA Y HORA ACTUAL
    printDateTime(compiled); //SE IMPRIME FECHA Y HORA
    Serial.println();
}

void loop () {
  //SE OBTENIE FECHA Y HORA ACTUAL Y SE ACTUALIZA
    RtcDateTime now = Rtc.GetDateTime();
    printDateTime(now);
    Serial.println();
    if (!now.IsValid()){
        Serial.println("ERROR EN FECHA Y HORA");
    }
    delay(1000);
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
    lcd.print("DATE  ");
    lcd.print(dt.Month());
    lcd.print("/");
    lcd.print(dt.Day());
    lcd.print("/");
    lcd.print(dt.Year());
    lcd.setCursor(0,14);
    lcd.print(" ");
    lcd.setCursor(0,1);
    lcd.print("TIME  ");
    lcd.print(dt.Hour());
    lcd.print(":");
    lcd.print(dt.Minute());
    lcd.print(":");
    lcd.print(dt.Second());
    Serial.print(datestring);//SE IMPRIME EN MONITOR SERIE
}
