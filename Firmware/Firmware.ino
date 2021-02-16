
// Include Libraries
#include "Arduino.h"
#include "LiquidCrystal.h"
#include "RFID.h"
#include "Servo.h"
#include "dht.h"
// Pin Definitions
#define LCD_PIN_RS	9
#define LCD_PIN_E	8
#define LCD_PIN_DB4	3
#define LCD_PIN_DB5	4
#define LCD_PIN_DB6	6
#define LCD_PIN_DB7	7
#define LEDR_PIN_VIN	5
#define PIR_PIN_SIG	A5
#define RFID_PIN_RST	5
#define RFID_PIN_SDA	A4
#define SERVO9G_PIN_SIG	A0
#define SND_DETECTOR_PIN_AUDIO	A3
#define BUZZER	A1
#define DHT_SENSOR_PIN 2
#define ledPin 10
dht DHT;

// Global variables and defines
const int servo9gRestPosition   = 5;  //Starting position
const int servo9gTargetPosition = 150; //Position when event is detected
// object initialization
LiquidCrystal lcd(LCD_PIN_RS,LCD_PIN_E,LCD_PIN_DB4,LCD_PIN_DB5,LCD_PIN_DB6,LCD_PIN_DB7);
//LED ledR(LEDR_PIN_VIN);
RFID rfid(RFID_PIN_SDA,RFID_PIN_RST);
Servo servo9g;

int pirVal;

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");
    lcd.begin(16, 2);
    SPI.begin();    
    rfid.init();
    pinMode(ledPin,OUTPUT);
    //pinMode(PIR_PIN_SIG,INPUT);
    pinMode(BUZZER,OUTPUT);
    digitalWrite(ledPin,LOW);
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop()
{
    cb_rfid();
        //cb_temp();
    cb_motion();
    //cb_temp();   
    cb_sound();
    //delay(500);
    
}

void cb_rfid(){
  char cb_key[]="5a8374822f";
    // RFID Card Reader - RC522 - Test Code
    //Read RFID tag if present
    String rfidtag = rfid.readTag();
    //print the tag to serial monitor if one was discovered
    //lcd.print("Rfid!");
    rfid.printTag(rfidtag);
    if(rfidtag != "None"){
    if(rfidtag == cb_key){
    //ledR.off();
    servo9g.attach(SERVO9G_PIN_SIG);        
    servo9g.write(servo9gTargetPosition);
    Display("Auth Success!",1500,0);
    servo9g.write(servo9gRestPosition);    
    //delay(500);                         
    //servo9g.detach();  
            cb_temp();


      }
    else{  
    //lcd.print(rfidtag);
    //ledR.on();
     Display("Auth Failed!",1500,0);
     Buzzer(2);
    //ledR.off();

    }

    }

  }
void cb_motion(){
 //pinMode(PIR_PIN_SIG,INPUT);
  pirVal = digitalRead(PIR_PIN_SIG);
  delay(20);
  digitalWrite(ledPin,pirVal);  
  //Serial.print(F("Val: ")); Serial.println(pirVal);
  cb_temp();
  
  }
void cb_temp(){
   
  int readData=DHT.read11(DHT_SENSOR_PIN);
  float temperature=DHT.temperature;
    float humidity=DHT.humidity;
    delay(200);
    Display("T:"+String(temperature)+",H:"+String(humidity),1500,1);
  
  }
void cb_sound(){
    int threshold = 540; //Set minimum threshold for LED lit 
    int value = digitalRead(SND_DETECTOR_PIN_AUDIO);//read the value of A0 
    //Serial.println(value);//print the value 
    if(value == 1) //if the value is greater than 524 
    { //digitalWrite(ledPin,HIGH);//turn on the led
    Buzzer(3); 
    delay(200);//delay 200ms 
    } 
  }
void servo(){
  
  }
 
void Display(String msg,int d,int c){
  lcd.setCursor(0,c);
  lcd.print(msg);
    lcd.display();
    delay(d);
    //lcd.noDisplay();
  
  }
void Buzzer(int d){
  unsigned char i;
  while(d>0){
    for(i=0;i<80;i++)
   {
    digitalWrite(BUZZER,HIGH);
    delay(1);//wait for 1ms
    digitalWrite(BUZZER,LOW);
    delay(1);//wait for 1ms
    }
    //output another frequency
     for(i=0;i<100;i++)
      {
        digitalWrite(BUZZER,HIGH);
        delay(2);//wait for 2ms
        digitalWrite(BUZZER,LOW);
        delay(2);//wait for 2ms
      }
    d--;
    }
  
  
  }
