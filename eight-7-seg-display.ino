const int clock_pin = SCL;
// This is for the data pin
const int data_latch_pin = 13;
const int data_input_pin = 12;
unsigned int counter = 0;
unsigned int digit_base = 16;

// the MAX7219 address map (datasheet table 2)
#define MAX7219_DECODE_REG      (0x09)
#define MAX7219_DIGIT_REG(pos)  ((pos) + 1)
#define MAX7219_INTENSITY_REG   (0x0A)
#define MAX7219_SCANLIMIT_REG   (0x0B)
#define MAX7219_SHUTDOWN_REG    (0X0C)
#define MAX7219_DISPLAYTEST_REG (0x0F)
// For keeping the display on/off
#define MAX7219_ON  (0x1)
#define MAX7219_OFF             (0x0)
#define NUM_OF_DIGITS (8)

// This is for counting
const byte digit_pattern[10] =
{
  B01111110,  // 0
  B00110000,  // 1
  B01101101,  // 2
  B01111001,  // 3
  B00110011,  // 4
  B01011011,  // 5
  B01011111,  // 6
  B01110000,  // 7
  B01111111,  // 8
  B01111011,  // 9
};

// update the register value of MAX7219
void set_register(byte address, byte value)  
{
  digitalWrite(data_latch_pin, LOW);
  shiftOut(data_input_pin, clock_pin, MSBFIRST, address);
  shiftOut(data_input_pin, clock_pin, MSBFIRST, value);
  digitalWrite(data_latch_pin, HIGH);
}


// The chip used is common, a MAX 7219.
// It addresses eight 7-segment displays

void setup() {
  // put your setup code here, to run once:
  // Brightest setting
  
  // This is for output
  pinMode(clock_pin, OUTPUT);
  pinMode(data_latch_pin, OUTPUT);    
  pinMode(data_input_pin, OUTPUT);
  // This is for disabling testing
  set_register(MAX7219_DISPLAYTEST_REG, MAX7219_OFF);
  // set medium intensity. datasheet table 7
  set_register(MAX7219_INTENSITY_REG, 0x8);
  // turn off display. datasheet table 3
  set_register(MAX7219_SHUTDOWN_REG, MAX7219_OFF);
  // drive 8 digits. datasheet table 8
  set_register(MAX7219_SCANLIMIT_REG, 7);
  // no decode mode for all positions. datasheet table 4
  set_register(MAX7219_DECODE_REG, B00000000);


}

void loop() {
  unsigned int counter = 0;
  // we use i for the certain 7 segment we'd like to display values on
  int i;
  //This is what gets sent to the board, sends the value as binary
  byte value;


  
  // this will iterate through count on the 7 seg display
    while(true)
    {
    //algorithm
    // 1.) Turn off the display
    // 2.) Send data to the display
    // 3.) Turn on the display
    // 4.) iterate

    if(i == 8) // Turn off display
    {set_register(MAX7219_SHUTDOWN_REG, MAX7219_OFF);
    i = 0;
    }

    //using a switch statement for changing values of the 7 seg
    switch (counter) 
    { 
       case 1: value = digit_pattern[counter];
               break; 
       case 11: counter = 0;
                break; 
       default: counter = 0;
                break;   
    } 

    //Set the display values
    if(i == 8)
    set_register(MAX7219_DIGIT_REG(i), value);
    
    

    i++;
    counter++;
    }

    delay(20);

    
}
