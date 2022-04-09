/*                                                                             |
 * Lista pin utilizzati sull'Arduino uno:                                      |
 * DISPLAY 16,2 con interfaccia classica (non I2C):                            |
 * pin 12 --> rs                                                               |
 * pin 11 --> en                                                               |
 * pin 5  --> d4                                                               |
 * pin 4  --> d5                                                               |
 * pin 3  --> d6                                                               |
 * pin 2  --> d7                                                               |
--------------------------------------------------------------------------------
 * SENSORE TEMPERATURA/UMIDITà DHT11                                           |
 * pin 7  --> out                                                              |
--------------------------------------------------------------------------------
 * USCITA UMIDIFICATORE AD ULTRASUONI:                                         |
 * pin 10                                                                      |
--------------------------------------------------------------------------------
 * USCITA PER SEGNALAZIONE LED (TEMPERATURA)                                   |
 * pin 8  --> led rosso, elemento riscaldante acceso                           |
 * pin 9  --> led verde, elemento riscaldante spento                           |
--------------------------------------------------------------------------------
 * USCITA PER ACCENSIONE/SPEGNIMENTO ELEMENTO RISCALDANTE                      |
 * pin 6                                                                       |
*/

#include <LiquidCrystal.h>
#include <DHT.h>

DHT dht(7, DHT11);
const int rs= 12, en = 11, d4= 5, d5= 4, d6= 3, d7=2;
LiquidCrystal lcd (rs, en, d4, d5, d6, d7); 

boolean sentinel = 0;

void setup() 
{
  Serial.begin(9600);
  
  pinMode(6,OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  dht.begin();
  lcd.begin (16, 2);
  lcd.print("Camera di");
  lcd.setCursor (0,1);
  lcd.print("lievitazione");
  delay (3000);
  lcd.clear();
}

void loop()
{
  delay(1000);
  int t = dht.readTemperature();
  int h = dht.readHumidity();
  

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temp.:" + String(t) + char(0xDF) + "C");
  lcd.setCursor(0,1);
  lcd.print("Umidita':" + String(h) + "%");


//condizioni per attivare e disattivare l'elemento riscaldante
  if(t <= 28)
  {
    digitalWrite(6,HIGH);
    digitalWrite(8,HIGH);
    digitalWrite(9,LOW);
  }
  else if (t >= 30)
  {
    digitalWrite(6, LOW);
    digitalWrite(8,LOW);
    digitalWrite(9,HIGH);
  }


//condizioni per accendere o spegnere l'umidificatore

 if(sentinel == 0)
 {
   if (h <80)
   {
      digitalWrite(10, HIGH);
      delay(100);
      digitalWrite(10, LOW);
      sentinel = 1;
   }
 }
   if (sentinel == 1 && h >=80)
    {
      digitalWrite(10, HIGH);
      delay(100);
      digitalWrite(10, LOW);
      sentinel = 0;
    }

  
}
