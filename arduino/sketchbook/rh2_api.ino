// Define the number of leds.
const int NB_LEDS = 5;
const int START_BYTE = '~'; // 126

unsigned long startTrigger[NB_LEDS];
int totalTime[NB_LEDS];
int onTime[NB_LEDS];
int offTime[NB_LEDS];

unsigned long currentTime;
int led;
int i;

unsigned long currentStatus, periodTime, currentPeriod, periodStartTime;

int leds[] = {11, 10, 9, 6, 5, 3};

void setup(){
  for(i = 0; i < NB_LEDS; i++){
    pinMode(leds[i], OUTPUT);
    totalTime[i] = 0;
    onTime[i] = 0;
    offTime[i] = 0;
  }
  
  Serial.begin(9600);
}

void loop(){
  // Read the serial port and configure the event
  
  if(Serial.available() >= 5) {
    if(Serial.read() == START_BYTE){ // Flush the Serial until we find a start byte.
      led = ((int) Serial.read());
      if(led < 0 || led > 6){
        Serial.flush();
        return; 
      }
      totalTime[led] = Serial.read();
      onTime[led] = Serial.read();
      offTime[led] = Serial.read();
      startTrigger[led] = millis();
      if(totalTime[led] > 0) {
        digitalWrite(leds[led], HIGH);
      } else {
        digitalWrite(leds[led], LOW);
        startTrigger[led] = 0;
      }
      
      
      Serial.print(millis());
      Serial.print(' ');
      Serial.print(led);
      Serial.print(' ');
      Serial.print(totalTime[led]);
      Serial.print(' ');
      Serial.print(onTime[led]);
      Serial.print(' ');
      Serial.print(offTime[led]);
      Serial.print(' ');
      Serial.println(startTrigger[led]);
    }
  }
  
  // For each led, activate/deactivate the led
  for(led = 0; led < NB_LEDS; led++){
    currentTime = millis();
    // If totalTime is expired : turn off the led
    if(currentTime > startTrigger[led] + totalTime[led]*100) {
      digitalWrite(leds[led], LOW);
    } else {
      // Time lapsed since the animation start
      // currentStatus = currentTime - startTrigger[led];
      
      // Time of on animation period
      periodTime = onTime[led]*10 + offTime[led]*10;
      
      // In which period are we ? 1, 2 ,3 ...
      currentPeriod = (currentTime - startTrigger[led]) / periodTime;
      
      // When did the period starts ?
      periodStartTime = startTrigger[led] + currentPeriod * periodTime;
      
      // Are we in the On part or the Off part ?
      if ((currentTime - periodStartTime) > onTime[led]*10) 
        digitalWrite(leds[led], LOW);
      else 
        digitalWrite(leds[led], HIGH);
    }
  }
  delay(10);
}
