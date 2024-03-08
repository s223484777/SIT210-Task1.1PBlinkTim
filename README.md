# SIT210-Task1.1PBlinkTim
S306 SIT210 Task 1.1P, blink a student's name in morse code whenever a button is pressed.

## Description
The pin definitions are for the ESP8266 based D1 Mini board. These definitions may be removed or modified for other boards
The morse code timing follows <https://www.itu.int/dms_pubrec/itu-r/rec/m/R-REC-M.1677-1-200910-I!!PDF-E.pdf>.

Connect an LED to the `morseLED`, and a button (pulled down) to `buttonPin`. Whenever the button is pressed, the sketch will translate the string to morse code, and blink the morse code using the LED.

## How it Works
The morse code representation of a character is obtained by first converting the character to uppercase, followed by looking up the morse byte in either the letters or numbers lookup. If a character is not in either of them or a space, the morse byte defaults to a "?", or whichever byte is defined in the definitions section.

For example, the character "Q" has the morse code representation --.-, which becomes the symbol sequence 10010, which is padded to 8 bits for a byte and prefixed with 0b. From this, we get the morse byte for "Q" as "0b00010010".

The following snippet (which does most of the heavy lifting) reads the morse code byte bit by bit, blinking a dit for a 1, and blinking a dah for a 0. Before any symbols are output, the loop must reach the first 1, allowing the length of each character to vary from 0 to 7 symbols.

```cpp
byte morse = unknown; // The morse representation as a byte, defaults to unknown/?
bool inMorse = false; // Flag to keep track of when we've reached the start of the symbol sequence

// Iterate through every bit in the morse byte
for(int i = 7; i >= 0; i--){
  // If we're in the morse symbols, call dit() for a 1 or dah() for a 0
  if(inMorse){
    if((morse >> i) & 0b1){
      blink(dit_units);
    }else{
      blink(dah_units);
    }
	// Delay between each symbol
    delay(unit_time * symbol_space);
  }else{
    // If the symbol sequence hasn't started yet, but we see a 1, set the inMorse flag
    if((morse >> i) & 0b1){
      inMorse = true;
    }
  }
}
```

To blink an entire string, the `blinkMorseString()` simply iterates through the string character by character, calling `blinkMorseChar()` each time. Calls to `blinkMorseChar()` have a final delay of one letter space, and calls to `blinkMorseString()` have a final delay of 2 word spaces so there is a clear separation of strings.

## Usage
All that is required for this sketch is to call `blinkMorseString()` with whatever string you'd like to blink on the `morseLED` pin. As per the task sheet, this is called with my name whenever the button is pressed.

## International Morse Code
1. A dit is 1 unit
2. A dah is 3 units
3. The space between symbols in a single character is 1 unit
4. The space between characters is 3 units
5. The space between words is 7 units

||||
|-------------|-----------|-----------|
| a       . − | i     . . | r   . − . |
| b   − . . . | j . − − − | s   . . . |
| c   − . − . | k   − . − | t       − |
| d     − . . | l . − . . | u   . . − |
| e         . | m     − − | v . . . − |
| é . . - . . | n     - . | w   . - - |
| f   . . − . | o   − − − | x − . . − |
| g     − − . | p . − − . | y − . − − |
| h   . . . . | q − − . − | z − − . . |
 
|||
|-------------|-------------|
| 0 - - - - - | 5 . . . . . |
| 1 . - - - - | 6 - . . . . |
| 2 . . - - - | 7 - - . . . |
| 3 . . . - - | 8 - - - . . |
| 4 . . . . - | 9 - - - - . |

International Morse Code contains a number of other characters, however only the question mark has been included to represent anything that isn't understood.

|||||
|---|-------------|---|-------------|
| . | . - . - . - | / |   - . . - . |
| , | - - . . - - | ( |   - . - - . |
| : | - - - . . . | ) | - . - - . - |
| ? | . . - - . . | " | . - . . - . |
| ' | . - - - - . | = |   - . . . - |
| - | - . . . . - | + |   . - . - . |
| @ | . - - . - . | x |     - . . - |

|||
|-|-|
| Understood             |       . . . - . |
| Error                  | . . . . . . . . |
| Invitation to transmit |           - . - |
| Wait                   |       . - . . . |
| End of work            |     . . . - . - |
| Start of transmission  |       - . - . - |