/*
	Under the bed nightlight
 
 	Lights up a led strip under the bed when it detects movement while its dark.
 
 	The circuit:
 	* PIR for movement. The ammout of sensors depends on the bed. 
 	* LDR for light sensor
 * Transistor to drve the LED strip
 
 	Created 25-08-2014
 	By VeryEvilBetty
 
 */
#define ldr_pin 3
#define led_pin 4

const int numberOfPirs = 1;              // Number of pir sensors
const int pir_pins[numberOfPirs] = { 2 };  // Pins of the pir sensors Example = {pin,pin,pin}

const int led_time = 20; // Time to have the leds on (no an exact timing) (x .5 Sec)
const int on_delay = 5; // Delay to turn the leds on (in mSec)
const int off_delay = 1; // Delay to turn the leds off (in mSec)

const int light_ref = 320; // Value to make the differene between dark and light

const int led_max = 180;  // Ledstrip max pwm value
const int led_min = 0;    // Ledstrip min pwm value (0 recommended, else it wont turn off)

boolean lightDetect = false;   // Booelan thats true when the light is on;
boolean led = false;     // Boolean thats true when the led strip is on;
int timer = 0;           // Integer for the timer;

void setup(){
  analogReference(0); 
  pinMode(ldr_pin,INPUT);
  // Set pinmode for all pir sensors
  for (int i=0; i < numberOfPirs; i++){
    pinMode(pir_pins[i],INPUT);
  }
  pinMode(led_pin,OUTPUT);
}

void loop()
{
  // Read all pir sensors
  boolean pir = false;    
  for (int i=0; i < numberOfPirs; i++){
    if (digitalRead(pir_pins[i]) == 1){
      pir = true;    
    }
  }

  if (led == false)
  {
    // Read ldr value
    int ldr = analogRead(ldr_pin);
    // The beauty of the attiny ADCs is that they are upside-down.
    if (light_ref > ldr)
    {
      if (pir == true) 
      {
        ledOn();
        timer = 0;
      }
    }
  } 
  else 
  {
    timer++;
    // if the timer is equal to the set time turn the leds off.
    if (timer == led_time)
    {
      ledOff(); 
    }
  }
  delay(500);
}


// function to turn the leds on
void ledOn(){
  if (led == false){
    for(int i=led_min;i<=led_max; i++){
      analogWrite(led_pin,i);
      delay(on_delay);
    }    
    led = true;
  }
}

// function to turn the leds off
void ledOff(){
  if (led == true){
    for(int i=led_max;i>=led_min; i--){
      analogWrite(led_pin,i);
      delay(off_delay);      
    }    
    led = false;
  }
}



