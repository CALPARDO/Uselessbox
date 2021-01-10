
/*Useless Box Arduino Code by Derin Durak
  https://www.calpardo.com */
  
// Libraries
#include <Servo.h>
#include "pitches.h"

// Servo
Servo armservo;  // create servo object to control a servo

// Constants
const int servopin = 9; // define servo pin
const int switchpin = 6; // define switch pin
const int buzzerpin = 4; // define buzzer pin
const int ledpin = 13; // define led pin
const int moves = 7; // possible moves

// Variables
int pos = 0;
int min_pos = 2; // starting position
int med_pos = 70; // medium position
int max_pos = 125; // switched position
int switch_val = 0; // if switched turned or not
int selectedMove = 0; // move selection

int elephanttempo = 172;
int elephantwholenote = (60000 * 4) / elephanttempo;
int elephantdivider = 0, elephantnoteDuration = 0;

int ussrmelody[] = { // ussr melody
  NOTE_G4, NOTE_C5, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_E4, NOTE_E4, 
  NOTE_A4, NOTE_G4, NOTE_F4, NOTE_G4, NOTE_C4, NOTE_C4, 
  NOTE_D4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5, NOTE_D5, 
  NOTE_E5, NOTE_D5, NOTE_C5, NOTE_D5, NOTE_B4, NOTE_G4, 
  NOTE_C5, NOTE_B4, NOTE_A4, NOTE_B4, NOTE_E4, NOTE_E4, 
  NOTE_A4, NOTE_G4, NOTE_F4, NOTE_G4, NOTE_C4, NOTE_C4, 
  NOTE_C5, NOTE_B4, NOTE_A4, NOTE_G4, NOTE_B4, NOTE_C5, NOTE_D5, 
  NOTE_E5, NOTE_D5, NOTE_C5, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_G4, NOTE_G4, NOTE_B4, NOTE_C5, NOTE_D5,
  NOTE_C5, NOTE_B4, NOTE_A4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_E4, NOTE_E4, NOTE_G4, NOTE_A4, NOTE_B4,
  NOTE_C5, NOTE_A4, NOTE_B4, NOTE_C5, NOTE_A4, NOTE_B4, NOTE_C5, NOTE_A4, NOTE_C5, NOTE_F5,
  NOTE_F5, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_C5, NOTE_C5,
  NOTE_D5, NOTE_C5, NOTE_B4, NOTE_A4, NOTE_B4, NOTE_C5, NOTE_A4, NOTE_A4,
  NOTE_C5, NOTE_B4, NOTE_A4, NOTE_G4, NOTE_C4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5
};

int elephantmelody[] = {
  
  NOTE_C4,-8, NOTE_E4,16, NOTE_G4,8, NOTE_C5,8, NOTE_E5,8, NOTE_D5,8, NOTE_C5,8, NOTE_A4,8,
  NOTE_FS4,8, NOTE_G4,8, REST,4, REST,2,
  NOTE_C4,-8, NOTE_E4,16, NOTE_G4,8, NOTE_C5,8, NOTE_E5,8, NOTE_D5,8, NOTE_C5,8, NOTE_A4,8,
  NOTE_G4,-2, NOTE_A4,8, NOTE_DS4,1,
  
  NOTE_A4,8,
  NOTE_E4,8, NOTE_C4,8, REST,4, REST,2,
  NOTE_C4,-8, NOTE_E4,16, NOTE_G4,8, NOTE_C5,8, NOTE_E5,8, NOTE_D5,8, NOTE_C5,8, NOTE_A4,8,
  NOTE_FS4,8, NOTE_G4,8, REST,4, REST,4, REST,8, NOTE_G4,8,
  NOTE_D5,4, NOTE_D5,4, NOTE_B4,8, NOTE_G4,8, REST,8, NOTE_G4,8,
   
  NOTE_C5,4, NOTE_C5,4, NOTE_AS4,16, NOTE_C5,16, NOTE_AS4,16, NOTE_G4,16, NOTE_F4,8, NOTE_DS4,8,
  NOTE_FS4,4, NOTE_FS4,4, NOTE_F4,16, NOTE_G4,16, NOTE_F4,16, NOTE_DS4,16, NOTE_C4,8, NOTE_G4,8,
  NOTE_AS4,8, NOTE_C5,8, REST,4, REST,2,
};
int elephantnotes = sizeof(elephantmelody) / sizeof(elephantmelody[0]) / 2;

int ussrnoteDurations[] = { // ussr melody note durations
  8, 4, 6, 16, 4, 8, 8, 
  4, 6, 16, 4, 8, 8, 
  4, 8, 8, 4, 8, 8, 4, 8, 8, 2,
  4, 6, 16, 4, 8, 8, 
  4, 6, 16, 4, 8, 8, 
  4, 6, 16, 4, 6, 16, 
  4, 6, 16, 8, 8, 8, 8, 
  2, 8, 8, 8, 8, 3, 8, 8, 8, 8, 8,
  2, 8, 8, 8, 8, 3, 8, 8, 8, 8, 8,
  4, 6, 16, 4, 6, 16, 4, 8, 8, 2,
  2, 8, 8, 8, 8, 3, 8, 2,
  2, 8, 8, 8, 8, 3, 8, 2,
  4, 6, 16, 4, 4, 2, 4, 4, 1
};

// setup
void setup() {
  armservo.attach(servopin);  // attaches the servo on pin 9 to the servo object
  armservo.write(min_pos);
  pinMode(buzzerpin,OUTPUT);
  pinMode(switchpin, INPUT);
  pinMode(ledpin, OUTPUT);
  Serial.begin(9600);
}

// loop
void loop() {
  switch_val = digitalRead(switchpin); // read switchpin and write to switch_val
  Serial.println(switch_val); // print switch_val to serial monitor

  // main statement
  if (switch_val == HIGH) {
    
    selectedMove = random(1,moves+4); // randomly select a move number

    // move cases
    if (selectedMove == 1) { 
    classic(); 
    }   
    else if (selectedMove == 2) { 
    slow(); 
    }
    else if (selectedMove == 3) { 
    fast(); 
    }
    /*else if (selectedMove == 4) { 
    withussr(); 
    }*/
    else if (selectedMove == 5) { 
    fake(); 
    }
    else if (selectedMove == 6) { 
    withledandbuzzer(); 
    }
    else if (selectedMove == 7) { 
    elephant(); 
    } 
    if (selectedMove == 8) { 
    classic(); 
    }   
    else if (selectedMove == 9) { 
    slow(); 
    }
    else if (selectedMove == 10) { 
    fast(); 
    }   
  } else {
    armservo.write(min_pos);
    }
}

// functions
void ussr() {
  for (int thisNote = 0; thisNote < sizeof(ussrmelody) / 2; thisNote++) {
    int noteDuration = 2000 / ussrnoteDurations[thisNote];
    tone(buzzerpin, ussrmelody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(buzzerpin);
  }
}

void classic() {
    for (pos = min_pos; pos <= max_pos; pos += 4) { // goes from 0 degrees to 180 degrees
      armservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    delay(100);
    for (pos = max_pos; pos <= min_pos; pos -= 4) { // goes from 0 degrees to 180 degrees
      armservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
   delay(50);  
  }

void slow() {
    for (pos = min_pos; pos <= max_pos; pos += 2) { // goes from 0 degrees to 180 degrees
      armservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    delay(100);
    for (pos = max_pos; pos <= min_pos; pos -= 2) { // goes from 0 degrees to 180 degrees
      armservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
   delay(50);  
  }

void fast() {
    for (pos = min_pos; pos <= max_pos; pos += 10) { // goes from 0 degrees to 180 degrees
      armservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    delay(100);
    for (pos = max_pos; pos <= min_pos; pos -= 10) { // goes from 0 degrees to 180 degrees
      armservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
   delay(50);  
  }

void withussr() {    
    for (pos = min_pos; pos <= max_pos; pos += 4) { // goes from 0 degrees to 180 degrees
      armservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    ussr();
    delay(100);
    for (pos = max_pos; pos <= min_pos; pos -= 4) { // goes from 0 degrees to 180 degrees
      armservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
   delay(50);  
  }

void withledandbuzzer() {    
    for (pos = min_pos; pos <= med_pos; pos += 8) { // goes from 0 degrees to 180 degrees
      armservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    digitalWrite(ledpin, HIGH);
    delay(1000);
    for (pos = med_pos; pos <= max_pos; pos += 1) { // goes from 0 degrees to 180 degrees
      digitalWrite(ledpin, HIGH);
      digitalWrite(buzzerpin, HIGH);
      armservo.write(pos); // tell servo to go to position in variable 'pos'
      delay(15);   // waits 15ms for the servo to reach the position
      digitalWrite(ledpin, LOW);
      digitalWrite(buzzerpin,LOW);
    }
    for (pos = max_pos; pos <= min_pos; pos -= 15) { // goes from 0 degrees to 180 degrees
      armservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
   delay(50);  
  }

void fake() {
    for (pos = min_pos; pos <= med_pos; pos += 2) { // goes from 0 degrees to 180 degrees
      armservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    delay(1000);
    for (pos = med_pos; pos <= min_pos; pos -= 10) { // goes from 0 degrees to 180 degrees
      armservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    delay(3000);
    for (pos = min_pos; pos <= max_pos; pos += 15) { // goes from 0 degrees to 180 degrees
      armservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    delay(100);
    for (pos = max_pos; pos <= min_pos; pos -= 15) { // goes from 0 degrees to 180 degrees
      armservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
   delay(50);  
  }

void elephant(){
    for (int elephantthisNote = 0; elephantthisNote < elephantnotes * 2; elephantthisNote = elephantthisNote + 2) {

    // calculates the duration of each note
    elephantdivider = elephantmelody[elephantthisNote + 1];
    if (elephantdivider > 0) {
      // regular note, just proceed
      elephantnoteDuration = (elephantwholenote) / elephantdivider;
    } else if (elephantdivider < 0) {
      // dotted notes are represented with negative durations!!
      elephantnoteDuration = (elephantwholenote) / abs(elephantdivider);
      elephantnoteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(buzzerpin, elephantmelody[elephantthisNote], elephantnoteDuration * 0.9);

    // Wait for the specief duration before playing the next note.
    delay(elephantnoteDuration);

    // stop the waveform generation before the next note.
    noTone(buzzerpin);
  }
}

  
