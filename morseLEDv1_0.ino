// ESP8266 D1 Mini Pin Definitions
#define D0   16
#define D1    5
#define D2    4
#define D3    0
#define D4    2
#define D5   14
#define D6   12
#define D7   13
#define D8   15
#define TX    1
#define RX    3
#define SCL   5
#define SDA   4
#define WAKE 16
#define SCLK 14
#define MISO 12
#define MOSI 13
#define CS   15

int morseLED = D1;
int buttonPin = D2;

void setup() {
  pinMode(morseLED, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  if(digitalRead(buttonPin)){
    blinkMorseString("Timothy");
  }
}