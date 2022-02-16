#include <Servo.h>

int sensorValue = 0;
int position = 0;
int FEED_TIMES = 3;				//feed fish 3 times
long FISH_FEEDER = 12000;		//12 seconds between feeding
long endTime; 					//next feed				
long now;

Servo servo_3;

void setup()
{
  Serial.begin(9600);	//initialize serial

  servo_3.attach(3);   // servo on pin 3
  pinMode(A0, INPUT);  // photoresistor on pin A0
  
  pinMode(9, OUTPUT);  //red LED on pin 9
  pinMode(10, OUTPUT); //green LED on pin 10
  
  servo_3.write(position);

  now = millis(); 
  endTime = now + FISH_FEEDER;
 
  delay(10);
}

void loop()
{
  sensorValue = analogRead(A0); //read light sensor 
  Serial.println(sensorValue);
  
  if (sensorValue > 20) { 	//day
    Serial.println("Day");
    analogWrite(9, 0); 		//red light off
    analogWrite(10, 255); 	//green light on
    
    if (now < endTime) { 
      for (int i = 0; i < FEED_TIMES; i++) { 
        Serial.print("Feed ");
        Serial.println(i);
  		for (position = 1; position <= 180; position += 1) {
    		servo_3.write(position);
    		delay(10); // Wait for 10 millisecond(s)
  		}
 		delay(100);
  		for (position = 1; position >= 180; position -= 1) {
    		servo_3.write(position);
    		delay(10); // Wait for 10 millisecond(s)
  		}
        delay(100);
      } 
       position = 0;			//reset motor position
     servo_3.write(position);
   	   delay(100);  			// Wait for 20 millisecond(s)
      
      now = millis();
      Serial.print("Now: ");
      Serial.println(now);      
      
      Serial.print("Feed interval: ");
      Serial.println(FISH_FEEDER);
      delay(FISH_FEEDER);
    } 
    else {
      	now = millis();
        Serial.print("Now: ");
        Serial.println(now);
        endTime = now + FISH_FEEDER;
        Serial.print("New end time: ");
        Serial.println(endTime);
      
    }
  } else { 	//night
    Serial.println("Night");
    analogWrite(9, 255); 	//red light on
    analogWrite(10, 0); 	//green light off
    
    position = 0;			//reset motor position
    servo_3.write(position);
    delay(100);  			// Wait for 20 millisecond(s)
  }
}

