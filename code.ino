#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define trig 12
#define echo 14
long duration;
float distance;
int X;
int Y;
float TIME = 0,tr = 0;
float FREQUENCY = 0;
float WATER = 0;
float TOTAL = 0,VOL = 7.75;
float LS = 0;
const int input = A0;
char auth[] = "BSaYkSFfKzBdlWAGQjTPawPsdkE0UudH";
char ssid[] = ""; //your-network-ssid
char pass[] = ""; //your-network-password
void setup()
{
pinMode(trig,OUTPUT);
pinMode(echo, INPUT);
pinMode(input,INPUT);
Serial.begin(115200);
Blynk.begin(auth, ssid, pass);
Serial.println("Connected");
}
void loop()
{
Blynk.run();
X = pulseIn(input, HIGH);
Y = pulseIn(input, LOW);
TIME = X + Y;
FREQUENCY = 1000000/TIME;
Team 8
WATER = FREQUENCY/7.5;
LS = WATER/60;
tr = ((VOL-TOTAL)*60)/LS;
if(FREQUENCY >= 0)
{
if(isinf(FREQUENCY))
{
Serial.print("Flow Rate");
Serial.println(LS);
Serial.print("TOTAL:");
Serial.print( TOTAL);
Serial.println("L");
}
else
{
TOTAL = TOTAL + LS;
Serial.print("Flow Rate");
Serial.println(LS);
Serial.println(FREQUENCY);
Serial.print("TOTAL:");
Serial.print( TOTAL);
Serial.println("L");
}
}
digitalWrite(trig , LOW);
delayMicroseconds(2);
digitalWrite(trig,HIGH);
delayMicroseconds(10);
digitalWrite(trig , LOW);
duration = pulseIn(echo, HIGH);
distance = (duration*0.0343)/2;
Serial.println(distance);
Blynk.virtualWrite(V0, distance);
Blynk.virtualWrite(V1, 29.64-distance);
Blynk.virtualWrite(V2, LS);
Blynk.virtualWrite(V3, TOTAL);
Blynk.virtualWrite(V4, tr);
delay(500);
}
