#include <Servo.h>

Servo myservo;
int pos = 0;

int Lled = 8; // led for low
int Mled = 9;  // led for meduim
int Hled = 10; // led for hig

int Lbutt = 5; // button for low
int Mbutt = 6; // butt for meduim
int Hbutt = 7; // button for heigh

int Hstep = 1;// for rythmn
int Mstep = 1;


//first button
int Lstate = LOW;      // the current state of the output pin
int Lreading;           // the current reading from the input pin
int Lprevious = LOW;    // the previous reading from the input pin

//secondbutton
int Mstate = LOW;      // the current state of the output pin
int Mreading;           // the current reading from the input pin
int Mprevious = LOW;    // the previous reading from the input pin.+

//third button
int Hstate = LOW;      // the current state of the output pin
int Hreading;           // the current reading from the input pin
int Hprevious = LOW;    // the previous reading from the input pin

// the follow variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long time = 0;         // the last time the output pin was toggled
long debounce = 200;   // the debounce time, increase if the output flickers
int delayTime = 0;

int servoState = 0 ;
unsigned long previousMillis = 0;        // will store last time LED was updated
long OnTime = 250;           // milliseconds of on-time
long OffTime = 750;          // milliseconds of off-time

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  myservo.attach(11);

  pinMode(Lled, OUTPUT);  // declare LED as output
  pinMode(Lbutt, INPUT_PULLUP);    // declare pushbutton as input
  
  pinMode(Mled, OUTPUT);  // declare LED as output
  pinMode(Mbutt, INPUT_PULLUP);    // declare pushbutton as input
  
  pinMode(Hled, OUTPUT);  // declare LED as output
  pinMode(Hbutt, INPUT_PULLUP);    // declare pushbutton as input

 }

void loop() {

  unsigned long currentMillis = millis();
 
     Serial.print(Hstep);
    Serial.println();
  Lreading = digitalRead(Lbutt);
  Mreading = digitalRead(Mbutt);
  Hreading = digitalRead(Hbutt);


// how inconsistanct rythmn is coded, wait an amount of time, and then moves onto the next step
/*
if(Hstate == HIGH){
  if(Hstep == 1){
    if(currentMillis - previousMillis >= 400){
      myservo.writeMicroseconds(1300);
      servoState =0;
      Hstep = 2;
       previousMillis = currentMillis;
}
  }
  else if(Hstep == 2){
      if(currentMillis - previousMillis >= 400){
        myservo.writeMicroseconds(1000);
        servoState =1;
        Hstep = 3;
         previousMillis = currentMillis;
}
  }
  else if(Hstep == 3){
     if(currentMillis - previousMillis >=400){
      myservo.writeMicroseconds(1300);
      servoState =0;
      Hstep =4;
       previousMillis = currentMillis;
}
  }
    else if (Hstep == 4){
       if(currentMillis - previousMillis >= 400){
       myservo.writeMicroseconds(1000);
       servoState =1;
       Hstep = 5;
        previousMillis = currentMillis;
}
       
  }   else if(Hstep == 5){
     if(currentMillis - previousMillis >= 100){
     myservo.writeMicroseconds(1300);
     servoState =0;
     Hstep= 6;
      previousMillis = currentMillis;
}
     
  }  else if(Hstep == 6){
     if(currentMillis - previousMillis >= 400){
      myservo.writeMicroseconds(1000);
      servoState =1;
      Hstep =1;
       previousMillis = currentMillis;
}
  } 

}

*/

// different rythmn

/*
if(Mstate == HIGH){
  if(Mstep == 1){
    if(currentMillis - previousMillis >= 100){
      myservo.writeMicroseconds(1300);
      servoState =0;
      Mstep = 2;
       previousMillis = currentMillis;
}
  }
  else if(Mstep == 2){
      if(currentMillis - previousMillis >= 1000){
        myservo.writeMicroseconds(1000);
        servoState =1;
        Mstep = 3;
         previousMillis = currentMillis;
}
  }
  else if(Mstep == 3){
     if(currentMillis - previousMillis >=100){
      myservo.writeMicroseconds(1300);
      servoState =0;
      Mstep =4;
       previousMillis = currentMillis;
}
  }

    else if(Mstep == 4){
     if(currentMillis - previousMillis >=100){
      myservo.writeMicroseconds(1000);
      servoState =0;
      Mstep =5;
       previousMillis = currentMillis;
}
  }

       else if(Mstep == 5){
     if(currentMillis - previousMillis >=1000){
      myservo.writeMicroseconds(1300);
      servoState =0;
      Mstep =1;
       previousMillis = currentMillis;
}
  }
    

}

*/

//checks to see if light is on, if it is it plays guitar
if(Lstate  == HIGH || Mstate == HIGH || Hstate == HIGH){

  if(currentMillis - previousMillis >= delayTime)
  {
    if( servoState == 1){
      myservo.writeMicroseconds(1300);
      servoState =0;
    }
    else{
        myservo.writeMicroseconds(1000);
        servoState =1;

    }
    previousMillis = currentMillis;  // Remember the time
  }
}


//changes delay time and light if button was pressed
  if (Lreading == HIGH && Lprevious == LOW && millis() - time > debounce) {
    if (Lstate == HIGH)
      Lstate = LOW;
    else
      Lstate = HIGH;
      Mstate = LOW;
     
      Hstate = LOW;
      delayTime = 1000;

    time = millis();    
  }

  if (Mreading == HIGH && Mprevious == LOW && millis() - time > debounce) {
    if (Mstate == HIGH)
      Mstate = LOW;
    else
      Mstate = HIGH;
      Lstate =LOW;
      Hstate= LOW;
      delayTime = 500;
      
    time = millis();    
  }

    if (Hreading == HIGH && Hprevious == LOW && millis() - time > debounce) {
    if (Hstate == HIGH)
      Hstate = LOW;
    else
      Hstate = HIGH;
      Lstate=LOW;
      Mstate= LOW;
      delayTime = 100;
    time = millis();    
  }

  
  digitalWrite(Lled, Lstate);
  Lprevious = Lreading;
  
  digitalWrite(Mled, Mstate);
  Mprevious = Mreading;
  
  digitalWrite(Hled, Hstate);
  Hprevious = Hreading;


}
