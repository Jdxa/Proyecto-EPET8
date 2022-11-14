#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <DHT.h>
LiquidCrystal_I2C lcd(0x27,16,2);

int temp;
int humedad;

int SENSOR= 2;

DHT dht(SENSOR, DHT11);


void setup() {
  dht.begin();
  lcd.init();
  lcd.backlight();
  
 
  
}

void loop() {
  humedad = dht.readHumidity();
  temp = dht.readTemperature();

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temperatura:");
  lcd.print(temp);
  lcd.print("*C");
  lcd.setCursor(0,1);
  lcd.print("Humedad: ");
  lcd.print(humedad);
  lcd.print("%");

  delay(5000);


}

  
  
  
  
