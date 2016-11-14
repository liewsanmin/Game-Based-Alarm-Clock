//  Simon Alarm Clock is an alarm clock that is set from your web browsers and in order to turn it off you must complete a game of Simon.
//  In order to ensure the user wakes up the game of Simon is controlled by a Photon seperate from the Photon controlling the speaker for the alarm.
//  This is accomplished using Particle.publish() and Particle.subscribe()

/*
        Simon Variables
*/
//arrays to store the generated pattern and the users attempted pattern
int genPattern[3];
int inputPattern[3];

//Declare the pins used for the buttons for the game of Simon
int buttonZeroPin = D1, buttonOnePin = D2, buttonTwoPin = D3, buttonThreePin = D4;

//int ledZeroPin = D5, ledOnePin = D6, ledTwoPin = D7;

//Declare the pins for the LEDS used in the game of Simon
int ledPins[3] = { D5, D6, D7 };

bool buttonNow0 = FALSE;
bool buttonNow1 = FALSE;
bool buttonNow2 = FALSE;
bool buttonNow3 = FALSE;

bool buttonLast0 = FALSE;
bool buttonLast1 = FALSE;
bool buttonLast2 = FALSE;
bool buttonLast3 = FALSE;

/*
        Alarm Variables
*/
//alarmHour is the hour the alarm is set for
//alarmMinute is the minute the alarm is set for
//alarmMode is whether or not the alarm is turned on
int alarmHour = 0;
int alarmMinute = 0;
int alarmMode = 0;


int inputNum = 0;

//char testFlag = 1;
char checkInputs = 0;
int alarmTrigger = 0;
//int showPattern = 0;

/*
        Setup portion of the code
*/

void setup() {
    //Initialize Serial communication for debugging
    Serial.begin(9600);
    //Sync the time and set the timezone
    Spark.syncTime();
    Time.zone(-6);
    
    //Generate a pattern for the alarm
    //seed random()
    randomSeed(Time.now());
    /*
    for(int i = 0; i < 3; i++){
        genPattern[i] = random(3);
        Serial.println(genPattern[i]);
    }
    */
    
    //Declare the pins used for input
    pinMode(buttonZeroPin, INPUT_PULLDOWN);
    pinMode(buttonOnePin, INPUT_PULLDOWN);
    pinMode(buttonTwoPin, INPUT_PULLDOWN);
    pinMode(buttonThreePin, INPUT_PULLDOWN);
    
    pinMode(ledPins[0], OUTPUT);
    pinMode(ledPins[1], OUTPUT);
    pinMode(ledPins[2], OUTPUT);
    
    //Initialize cloud variables for the alarm hour and minute
    Particle.variable("alarmHour", &alarmHour, INT);
    Particle.variable("alarmMinute", &alarmMinute, INT);
    Particle.variable("alarmEnable", &alarmMode, INT);
    
    //Initialize the cloud function to set the alarm time and another to set the mode
    Particle.function("setModeKey", setAlarmMode);
    Particle.function("setAlarmKey", setAlarm);
    
}

/*
        Loop portion of the code
*/

void loop() {
    
    //buttonNow3 = digitalRead(buttonThreePin);
    
    /*
    if(buttonNow3 == HIGH && buttonLast3 == LOW){
                Serial.println("Button Three");
                buttonLast3 = HIGH;
                
                for(int i = 0; i < 3; i++){
                    genPattern[i] = random(3);
                    Serial.println(genPattern[i]);
                }
                    
                for(int i = 0; i < 3; i++){
                    
                    switch(genPattern[i])
                    {
                        case 0:
                            digitalWrite(ledPins[0], HIGH);
                            delay(250);
                            digitalWrite(ledPins[0], LOW);
                            delay(100);
                            break;
                        case 1:
                            digitalWrite(ledPins[1], HIGH);
                            delay(250);
                            digitalWrite(ledPins[1], LOW);
                            delay(100);
                            break;
                        case 2:
                            digitalWrite(ledPins[2], HIGH);
                            delay(250);
                            digitalWrite(ledPins[2], LOW);
                            delay(100);
                            break;
                    }
                }
            }else if(buttonNow3 == LOW){
                buttonLast3 = LOW;
            }
   */
   
   //Checks if the alarm is turned on
    if(alarmMode){
        //checks if it is time for the alarm to go off
        if(alarmHour == Time.hour() && alarmMinute == Time.minute()){
            //only publish the alarm event once
            if(alarmTrigger == 0){
                Particle.publish("EE1301_Alarm", "", 5);
                //delay(1000);
                alarmTrigger = 1;;
                Serial.println("Alarm is going off");
            }
            //Serial.println("Alarm is going off");
            //read button 3 status
        }
        
        if(alarmTrigger == 1){
            buttonNow3 = digitalRead(buttonThreePin);
            
            if(buttonNow3 == HIGH && buttonLast3 == LOW){
                Serial.println("Button Three");
                buttonLast3 = HIGH;
                //generate a new patter
                for(int i = 0; i < 3; i++){
                    genPattern[i] = random(3);
                    Serial.println(genPattern[i]);
                }
                 //display the pattern once for the user to see   
                for(int i = 0; i < 3; i++){
                    switch(genPattern[i])
                    {
                        case 0:
                            digitalWrite(ledPins[0], HIGH);
                            delay(250);
                            digitalWrite(ledPins[0], LOW);
                            delay(100);
                        break;
                        case 1:
                            digitalWrite(ledPins[1], HIGH);
                            delay(250);
                            digitalWrite(ledPins[1], LOW);
                            delay(100);
                        break;
                        case 2:
                            digitalWrite(ledPins[2], HIGH);
                            delay(250);
                            digitalWrite(ledPins[2], LOW);
                            delay(100);
                        break;
                        default:
                        break;
                    }
                }
            }else if(buttonNow3 == LOW){
                buttonLast3 = LOW;
            }
            
            //read the Simon button status    
            buttonNow0 = digitalRead(buttonZeroPin);
            buttonNow1 = digitalRead(buttonOnePin);
            buttonNow2 = digitalRead(buttonTwoPin);
                
            if(buttonNow0 == HIGH && buttonLast0 == LOW){
                Serial.println("Button Zero");
                buttonLast0 = HIGH;
                //record button0 input
                inputPattern[inputNum] = 0;
                //increase inputNum count
                inputNum++;
                //light up the LED for button0
                digitalWrite(ledPins[0], HIGH);
                delay(100);
                digitalWrite(ledPins[0], LOW);
                delay(25);
            }else if(buttonNow0 == LOW){
                buttonLast0 = LOW;
            }
                
            if(buttonNow1 == HIGH && buttonLast1 == LOW){
                Serial.println("Button One");
                buttonLast1 = HIGH;
                //record button1 input
                inputPattern[inputNum] = 1;
                //increase inputNum count
                inputNum++;
                //light up the LED for button1
                digitalWrite(ledPins[1], HIGH);
                delay(100);
                digitalWrite(ledPins[1], LOW);
                delay(25);
            }else if(buttonNow1 == LOW){
                buttonLast1 = LOW;
            }
            
            if(buttonNow2 == HIGH && buttonLast2 == LOW){
                Serial.println("Button Two");
                buttonLast2 = HIGH;
                //record button2 input
                inputPattern[inputNum] = 2;
                //increase inputNum count
                inputNum++;
                //light up the LED for button2
                digitalWrite(ledPins[2], HIGH);
                delay(100);
                digitalWrite(ledPins[2], LOW);
                delay(25);
            }else if(buttonNow2 == LOW){
                buttonLast2 = LOW;
            }
            
            //when the users finishes a pattern check if it is right
            if(inputNum >= 3){
                //reset inputNum count
                inputNum = 0;
                //print the inputPattern
                for(int i = 0; i < 3; i++){
                    Serial.println(inputPattern[i]);
                }
                //check the inputPattern to the genPattern
                for(int j = 0; j < 3; j++){
                    if(inputPattern[j] == genPattern[j]){
                        //increase checkInputs for each correct input
                        checkInputs++;
                    }else{
                        break;
                    }
                }
                //if the inputPattern is correct
                if(checkInputs == 3){
                    Particle.publish("EE1301_Alarm_Pattern_Correct");
                    //publish an event to turn off the alarm
                    Serial.println("Patterns Match");
                    //disable the alarm
                    alarmMode = 0;
                    alarmTrigger = 0;
                }else{
                    //publish an event saying the input was wrong
                    Serial.println("Patterns Do Not Match");
                    //Particle.publish("EE1301_Alarm_Pattern_Incorrect");
                }
                //reset checkInputs
                checkInputs = 0;
            }
        }
    }
    delay(100);
}

//Cloud function to turn the alarm on or off
int setAlarmMode(String mode){
    if(mode == "1"){
        alarmMode = 1;
    }else{
        alarmMode = 0;
    }
};


//Cloud function to set the alarm time and to enable or disable it
int setAlarm(String alarmInfo){    //string of hour minute mode
    //intialize char arrays to seperate the alarmInfo into 
    char hour[2];
    char minute[2];
    
    //initialize a char array for the alarmInfo
    char inputStr[5];
    alarmInfo.toCharArray(inputStr, 5);
    
    //set the hour for the alarm
    hour[0] = inputStr[0];
    hour[1] = inputStr[1];
    alarmHour = atoi(hour);
    //set the minute for the alarm
    minute[0] = inputStr[2];
    minute[1] = inputStr[3];
    alarmMinute = atoi(minute);
};
