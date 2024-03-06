// Definitions
#define unit_time           125 // Unit time in ms
#define unknown      0b01110011 // Question mark for any unknown chars

// Following: https://www.itu.int/dms_pubrec/itu-r/rec/m/R-REC-M.1677-1-200910-I!!PDF-E.pdf
#define dit_units             1 // Units per dit
#define dah_units             3 // Units per dah
#define symbol_space          1 // Units between each dit/dah within a letter
#define letter_space          3 // Units between each letter
#define word_space            7 // Units between each word

// Define the morse representation for letters
byte lookup_morse_letters[] = {
  0b00000110,
  0b00010111,
  0b00010101,
  0b00001011,
  0b00000011,
  0b00011101,
  0b00001001,
  0b00011111,
  0b00000111,
  0b00011000,
  0b00001010,
  0b00001101,
  0b00000100,
  0b00000101,
  0b00001000,
  0b00011001,
  0b00010010,
  0b00001101,
  0b00001111,
  0b00000010,
  0b00001110,
  0b00011110,
  0b00001100,
  0b00010110,
  0b00010100,
  0b00010011
};

// Define the morse representation for numbers
byte lookup_morse_numbers[] = {
  0b00100000,
  0b00110000,
  0b00111000,
  0b00111100,
  0b00111110,
  0b00111111,
  0b00101111,
  0b00100111,
  0b00100011,
  0b00100001
};

// Blink a short dit (dot)
void dit(){
  digitalWrite(morseLED, HIGH);
  delay(unit_time * dit_units);
  digitalWrite(morseLED, LOW);
}

// Blink a long dah (dash)
void dah(){
  digitalWrite(morseLED, HIGH);
  delay(unit_time * dah_units);
  digitalWrite(morseLED, LOW);
}

// Blink the morse code for a given character (letters and numbers only).
void blinkMorseChar(char c){
  // Find the morse representaion for the char, or use "?" if unknown
  c = toupper(c);
  byte morse = unknown;
  if(c > 47 && c < 58){        // Numbers
    morse = lookup_morse_numbers[c-48];
  }else if(c > 64 && c < 91){  // Letters
    morse = lookup_morse_letters[c-65];
  }else if(c == 32){           // Word space delay
    delay(unit_time * (word_space - letter_space));
    return;
  }

  // Start blinking after the first high bit
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

  // Delay between letter (offset for the symbol_space)
  delay(unit_time * (letter_space - symbol_space));
}

// Blink the morse code for a given string.
void blinkMorseString(char str[]){
  for(int i = 0; i < strlen(str); i++){
    blinkMorseChar(str[i]);
  }

  // Ensure consecutive strings are seperated
  delay(unit_time * (word_space - letter_space) * 2);
}