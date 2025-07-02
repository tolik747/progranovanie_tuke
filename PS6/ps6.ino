#include <LiquidCrystal_I2C.h>
#include "lcd_wrapper.h"
#include "mastermind.h"
#include<assert.h>


void setup() {
  randomSeed(digitalRead(A1));
  pinMode(BTN_1_PIN, INPUT_PULLUP);
  pinMode(BTN_2_PIN, INPUT_PULLUP);
  pinMode(BTN_3_PIN, INPUT_PULLUP);
  pinMode(BTN_4_PIN, INPUT_PULLUP);
  pinMode(BTN_ENTER_PIN, INPUT_PULLUP);
  pinMode(LED_BLUE_1, OUTPUT);
  pinMode(LED_RED_1, OUTPUT);
  pinMode(LED_BLUE_2, OUTPUT);
  pinMode(LED_RED_2, OUTPUT);
  pinMode(LED_BLUE_3, OUTPUT);
  pinMode(LED_RED_3, OUTPUT);
  pinMode(LED_BLUE_4, OUTPUT);
  pinMode(LED_RED_4, OUTPUT);
}

void loop() {
  char* code = generate_code(false, 4);
    play_game(code);
    free(code);
}


