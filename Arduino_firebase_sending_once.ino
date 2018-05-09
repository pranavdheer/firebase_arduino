
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "nodemcu-b4848.firebaseio.com"
#define FIREBASE_AUTH "hofjAt5fa6CVZk5TzM465taGPaq84HgKr6NG2ICl"
#define WIFI_SSID "hotsp"
#define WIFI_PASSWORD "hottyspotty89"

int start=0,new_start=0;
int frequency=100; // frequency in hertz
int Time = 1; // Time for which you want to upload the data to the cloud 
int channel1=0,channel2=0,channel3=0;
String save_data=" ";
float delay_time=1000/frequency,flag=0,stamp_Second; // delay_time in milliseconds
long stamp;
String data_Send;
int iterator=0;
void setup() {
  
  Serial.begin(9600);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  start=millis();
  
}

int n = 0;

void loop()
{

  if ( millis()-start<=Time*1000)
  { 
   channel1=channel1+1;  // acquiring value of a 
   channel2=channel2+1;  // acquiring value of b
   channel3=channel3+1;  // acquiring value of c 
   iterator++;
    
   save_data=save_data+','+String(channel1);

  if (iterator==300)  //after 300 samples send data to cloud
  {
    Serial.println("ppp");
  stamp=millis()-start;  
  stamp_Second=float(stamp)/1000.00;
  data_Send= String(stamp_Second)+"=: "+String(save_data);
  String name = Firebase.pushString("testing_300_samples at a time", data_Send);
  
  //  // handle error
//  if (Firebase.failed()) {
//      Serial.print("pushing /logs failed:");
//      Serial.println(Firebase.error());  
//      return;}
      
  iterator=0;
  save_data=" ";
  }
  delay(10);
  }
  

 else if (flag==0)
 {Serial.println(iterator);
  if (iterator!=0) // for dealing with packets not multiple of 300
  {
   
  stamp=millis()-start;  
  stamp_Second=float(stamp)/1000.00;
  data_Send= String(stamp_Second)+"=: "+String(save_data);
  String name = Firebase.pushString("testing_300_samples at a time", data_Send);
  
//    if (Firebase.failed()) {
//      Serial.print("pushing /logs failed:"); // error handling
//      Serial.println(Firebase.error());  
//      return;
//      
//  }
Serial.println("PROCESS ENDED");

 }
  flag=1; 
 }

}


