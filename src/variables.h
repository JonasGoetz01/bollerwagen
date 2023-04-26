//Buzzer
#define BUZZER_PIN  15

//Bildschirm
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define DISPLAY_ADDRESS 0x78

//Motor
#define RPWM 12
#define LPWM 23
#define REN 13
#define LEN 13

// Temp sensor
#define TEMP 34

// Current Sensor
#define CURRENTSENSOR_PIN 32 
#define CURRENTSENSOR_PIN2 35
#define CURRENTSENSOR_VCC 5.0
#define CURRENTSENSOR_MODEL 0 //ACS758LCB-050B
#define CURRENTSENSOR_CUTOFFLIMIT 1.00 // 1A = 1%

//Timers
#define SENSORCHECKINTERVAL 4000

struct Variables
{
  bool motorEnabled = false;
};