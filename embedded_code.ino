
#include <dht.h>


#include "DHT.h"
#define dht_apin A1 // Analog Pin sensor is connected 
 
dht DHT;


 const int soil_sensor = A0;  // Analog input pin that the soil moisture sensor is attached to
int sensorValue = 0; //store sensor input value


void setup(){
 
  Serial.begin(9600);
  delay(500);//Delay to let system boot

  Serial.println("DHT11 Humidity & temperature Sensor\n\n");
  delay(1000);//Wait before accessing Sensor


  // initialize serial communications at 9600 bps:
  Serial.begin(9600); 

  
}//end "setup()"
 
void loop(){
  //Start of Program 
 
    DHT.read11(dht_apin);
    
    Serial.print("Current humidity = ");
    Serial.print(DHT.humidity);
    Serial.print("%  ");
    Serial.print("temperature = ");
    Serial.print(DHT.temperature); 
    Serial.println("C  ");
    
    delay(5000);//Wait 5 seconds before accessing sensor again.
 
  //Fastest should be once every two seconds.


 // read the sensor:
  sensorValue = analogRead(soil_sensor);            
  
  // print the sensor results to the serial monitor:
  Serial.print("Moisture Value = " );                       
  Serial.println(sensorValue);      

  // delay of one second
  delay(1000);

  
}// end loop() 

