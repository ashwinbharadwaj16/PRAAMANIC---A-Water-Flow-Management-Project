#define BLYNK_TEMPLATE_ID "TMPLqyr7etGR"
#define BLYNK_TEMPLATE_NAME "Flow Rate"
#define BLYNK_AUTH_TOKEN "gP5HK6LPbzGsFznuzqkj8gt-0V5gBlIs"


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>


// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial
 

long currentMillis = 0;
long previousMillis = 0;
int interval = 1000;
boolean ledState = LOW;
float calibrationFactor = 4.5;
volatile byte pulseCount;
byte pulse1Sec = 0;
float flowRate;
unsigned int flowMilliLitres;
unsigned long totalMilliLitres;

char auth[] = BLYNK_AUTH_TOKEN;
 
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Redmi Note 10 Pro";
char pass[] = "anmol@1234";
 
BlynkTimer timer;

const int relay1Pin = 5; // Pin to control relay for clockwise rotation
const int relay2Pin = 4; // Pin to control relay for anticlockwise rotation
bool isClockwise = true;


void IRAM_ATTR pulseCounter()
{
  pulseCount++;
}

void setup()
{
  Blynk.begin(auth, ssid, pass);
 Serial.begin(115200);

   
   
  pinMode(relay1Pin, OUTPUT);
  pinMode(relay2Pin, OUTPUT);
}

void loop()
{
  Blynk.run();
   

     

      
   
  
}
BLYNK_WRITE(V1)
{
  int hello=param.asInt();
  Serial.println(hello);
    if(hello>=25 && hello <35){
            Blynk.logEvent("water_over_flow");
             
            //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1111
          }
    else if(hello>=35){
      digitalWrite(relay1Pin, HIGH); // Turn on relay for clockwise rotation
      digitalWrite(relay2Pin, LOW);// Turn off relay for anticlockwise rotation
      delay(2000);
      digitalWrite(relay1Pin, HIGH); // Turn on relay for clockwise rotation
      digitalWrite(relay2Pin, HIGH);
      
    }
}

BLYNK_WRITE(V0) // Virtual pin for toggle button
{
  int buttonState = param.asInt();
  if (buttonState == 1)
  {
    if (isClockwise)
    {
      digitalWrite(relay1Pin, HIGH); // Turn on relay for clockwise rotation
      digitalWrite(relay2Pin, LOW);// Turn off relay for anticlockwise rotation
      delay(2000);
      digitalWrite(relay1Pin, HIGH); // Turn on relay for clockwise rotation
      digitalWrite(relay2Pin, HIGH);
    }
  } 
   else if(buttonState ==0)
    {
      digitalWrite(relay1Pin, LOW); // Turn off relay for clockwise rotation
      digitalWrite(relay2Pin, HIGH);
      delay(20000.);
      digitalWrite(relay1Pin, HIGH); // Turn on relay for clockwise rotation
      digitalWrite(relay2Pin, HIGH);// Turn on relay for anticlockwise rotation
    }
    //isClockwise = !isClockwise; // Toggle direction of motor rotation
  
}