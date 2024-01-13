#define BLYNK_TEMPLATE_ID "TMPLqyr7etGR"
#define BLYNK_TEMPLATE_NAME "Flow Rate"
#define BLYNK_AUTH_TOKEN "gP5HK6LPbzGsFznuzqkj8gt-0V5gBlIs"


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>


// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial
#define LED_BUILTIN 
#define SENSOR  2

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

//char auth[] = BLYNK_AUTH_TOKEN;
 
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Redmi Note 10 Pro";
char pass[] = "anmol@1234";
 
BlynkTimer timer;


void IRAM_ATTR pulseCounter()
{
  pulseCount++;
}

void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
   
  pinMode(SENSOR, INPUT_PULLUP);

  pulseCount = 0;
  flowRate = 0.0;
  flowMilliLitres = 0;
  totalMilliLitres = 0;
  previousMillis = 0;

  attachInterrupt(digitalPinToInterrupt(SENSOR), pulseCounter, FALLING);
}

void loop()
{
  Blynk.run();
  currentMillis = millis();
  if (currentMillis - previousMillis > interval) {
    
    pulse1Sec = pulseCount;
    pulseCount = 0;

    
    flowRate = ((1000.0 / (millis() - previousMillis)) * pulse1Sec) / calibrationFactor;
    previousMillis = millis();


    

    
    // Print the flow rate for this second in litres / minute
    Serial.print("Flow rate: ");
    Serial.print(int(flowRate));  // Print the integer part of the variable
    Serial.println("L/min");
    int hello =int(flowRate);
           // Print tab space
     Blynk.virtualWrite(V1,hello);
         
    if(hello>=25 && hello <35){
            Blynk.logEvent("water_over_flow");
             
            //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1111
          }
     
  }
}