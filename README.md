# SIT210-Task1.1PBlinkTim
S306 SIT210 Task 1.1P, blink a student's name in morse code whenever a button is pressed.

## Description
The pin definitions in the main file (morseLEDv1_0.ino) are for the ESP8266 based D1 Mini board. These definitions may be removed or modified for other boards
The morse code timing follows <https://www.itu.int/dms_pubrec/itu-r/rec/m/R-REC-M.1677-1-200910-I!!PDF-E.pdf>.

Connect an LED to the `morseLED`, and a button (pulled down) to `buttonPin`. Whenever the button is pressed, the sketch will translate the string to morse code, and blink the morse code using the LED.

## How it Works
The morse code representation of a character is obtained by first converting the character to uppercase, followed by looking up the morse byte in either the letters or numbers lookup. If a character is not in either of them or a space, the morse byte defaults to a "?", or whichever byte is defined in the definitions section.


The following snippet (which does most of the heavy lifting) reads the morse code byte bit by bit, blinking a dit for a 1, and blinking a dah for a 0. Before any symbols are output, the loop must reach the first 1, allowing the length of each character to vary from 0 to 7 symbols.
```cpp
bool inMorse = false;
for(int i = 7; i >= 0; i--){
  if(inMorse){
    if((morse >> i) & 0b1){
      dit();
    }else{
      dah();
    }
    delay(unit_time * symbol_space);
  }else{
    if((morse >> i) & 0b1){
      inMorse = true;
    }
  }
}
```

To blink an entire string, the `blinkMorseString()` simply iterates through the string character by character, calling `blinkMorseChar()` each time. Calls to `blinkMorseChar()` have a final delay of one letter space, and calls to `blinkMorseString()` have a final delay of 2 word spaces so there is a clear separation of strings.

## Usage
All that is required for this sketch is to call `blinkMorseString()` with whatever string you'd like to blink on the `morseLED` pin. As per the task sheet, this is called with my name whenever the button is pressed.