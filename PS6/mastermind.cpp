#include <Arduino.h>
#include "mastermind.h"
#include "lcd_wrapper.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
char* generate_code(bool repeat, int length)
{
    lcd.begin();
    if (length < 1 || (!repeat && length > 10)) {
        return NULL;
    }
    randomSeed(analogRead(A2));
    char* shifr = (char*)calloc(length + 1, sizeof(char));
    if (shifr == NULL) {
        return NULL;
    }
    if(repeat==false){
      bool dig[10] = {false};

      for (int i = 0; i < length; i++) {
          int digit = random(10);
          while (!repeat && dig[digit]) {
              digit = random(9);
          }
          shifr[i] = '0' + digit;
          dig[digit] = true;
      }
      shifr[length] = '\0';
      lcd.clear();
    }
    else{
      for (int i = 0; i < length; i++) {
          int digit = random(10);
          while (!repeat) {
              digit = random(10);
          }
          shifr[i] = '0' + digit;
      }
      shifr[length] = '\0';
    }
    return shifr;
}
void get_score(const char* secret, const char* guess, int* peg_a, int* peg_b){
  int correct_pos_count = 0; // кількість правильних цифр на правильних позиціях
  int correct_only_count = 0; // кількість правильних цифр, які не знаходяться на правильних позиціях

  bool secret_digits_used[4] = {false}; // для відстеження використаних цифр з секретного числа
  bool guess_digits_used[4] = {false}; // для відстеження використаних цифр з варіанту гравця

  // Перевірка правильних цифр на правильних позиціях
  for(int i = 0; i < 4; i++) {
      if(secret[i] == guess[i]) {
          correct_pos_count++;
          secret_digits_used[i] = true;
          guess_digits_used[i] = true;
      }
  }
  // Перевірка правильних цифр, які не на правильних позиціях
  for(int i = 0; i < 4; ++i) {
      if (!secret_digits_used[i]) {
          for(int j = 0; j < 4; ++j) {
              if (!guess_digits_used[j] && guess[j] == secret[i]) {
                  correct_only_count++;
                  secret_digits_used[i] = true;
                  guess_digits_used[j] = true;
                  break;
              }
          }
      }
  }
  // Збереження кількостей правильних цифр у відповідних змінних
  *peg_a = correct_pos_count;
  *peg_b = correct_only_count;
}
void turn_off_leds(){
  for (int i = 1; i <= 4; ++i) {
        digitalWrite(LED_BLUE_1 + (i - 1) * 2, LOW);
        digitalWrite(LED_RED_1 + (i - 1) * 2, LOW);
    }
}
void render_leds(const int peg_a, const int peg_b){
  turn_off_leds();
  // Ввімкнення світлодіодів згідно з кількістю вгаданих цифр у правильній та неправильній позиціях
  for (int i = 0; i < peg_a; i++) {
    digitalWrite(LED_RED_1 + i*2, HIGH); // Увімкнення ЧЕРВОНОГГО світла для вгаданих цифр у правильній позиції
  }
  for (int i = peg_a; i < peg_b+peg_a; i++) {
    digitalWrite(LED_BLUE_1 + i*2, HIGH); // Увімкнення СИНЬОГО світла для вгаданих цифр у правильній позиції
  }
  delay(2000); 
}
void render_history(char* secret, char** history, const int entry_nr){
  lcd.clear();
  char* guess=history[entry_nr];
  int a=1;
  int b=0;
  get_score(secret, guess, &a, &b);
  lcd.clear();
  lcd.print("History ");
  lcd.print(entry_nr);
  lcd.print(": ");
  lcd.print(guess);
  lcd.setCursor(0,1);
  lcd.print("A:");
  lcd.print(a);
  lcd.print(" B:");
  lcd.print(b);
  delay(2000);
  lcd.clear();
}

void play_game(char* secret)
{
    turn_off_leds();
    char guess[4];
    char **history =(char**)calloc(10, sizeof(char *));
    for (int y = 0; y < 10; y++)
    {
      history[y] = calloc(5, sizeof(char));
    }
    int peg_a=0;
    int peg_b=0; // Зберігає кількість відповідних цифр на правильних і неправильних позиціях
    // Вивід привітання
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Welcome to");
    lcd.setCursor(0, 1);
    lcd.print("Mastermind Game!");
    delay(2000);
    // Генерація та відображення таємного коду
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Secret code:");
    lcd.setCursor(0, 1);
    lcd.print(secret);
    delay(1000);
    // Основний цикл гри
    for (int attempt = 1; attempt <= 10; ++attempt) { // Максимально 10 спроб
        // Очищення та вивід повідомлення для вводу
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Attempt ");
        lcd.print(attempt);
        lcd.setCursor(0, 1);
        lcd.print("Enter guess:");
        // Отримання введення гравця
        int idx=attempt;
        guess[0] = '0'; // Встановлюємо початкове значення на '0'
        lcd.setCursor(12, 1); // Переміщаємо курсор на початок першого рядка
        lcd.print(guess[0]);
        guess[1] = '0'; // Встановлюємо початкове значення на '0'
        lcd.setCursor(13, 1); // Переміщаємо курсор на початок першого рядка
        lcd.print(guess[1]);
        guess[2] = '0'; // Встановлюємо початкове значення на '0'
        lcd.setCursor(14, 1); // Переміщаємо курсор на початок першого рядка
        lcd.print(guess[2]);
        guess[3] = '0'; // Встановлюємо початкове значення на '0'
        lcd.setCursor(15, 1); // Переміщаємо курсор на початок першого рядка
        lcd.print(guess[3]);
        while(digitalRead(BTN_ENTER_PIN)==LOW){
          if (digitalRead(BTN_1_PIN) == HIGH){
              int currentValue = guess[0] - '0'; // Перетворюємо символ на число
              currentValue = (currentValue + 1) % 10; // Збільшуємо значення на 1, якщо менше 9
              guess[0] = currentValue + '0'; // Перетворюємо число на символ
              lcd.setCursor(12, 1); // Переміщаємо курсор на початок першого рядка
              lcd.print(guess[0]); // Виводимо значення першого елементу масиву
              delay(200);
              if (digitalRead(BTN_2_PIN) == HIGH) {
              idx--;
              if(idx<=0){
                  lcd.clear();
                  lcd.print("this Attempt: ");
                  lcd.print("0");
                  lcd.setCursor(0, 1);
                  lcd.print("try again");
                  delay(1000); // Wait for 350 milliseconds
                  idx=attempt-1;
                  lcd.clear();
                  lcd.setCursor(0, 0);
                  lcd.print("Attempt ");
                  lcd.print(attempt);
                  lcd.setCursor(0, 1);
                  lcd.print("Enter guess:");
                  guess[0] = '0'; // Встановлюємо початкове значення на '0'
                  lcd.setCursor(12, 1); // Переміщаємо курсор на початок першого рядка
                  lcd.print(guess[0]);
                  guess[1] = '0'; // Встановлюємо початкове значення на '0'
                  lcd.setCursor(13, 1); // Переміщаємо курсор на початок першого рядка
                  lcd.print(guess[1]);
                  guess[2] = '0'; // Встановлюємо початкове значення на '0'
                  lcd.setCursor(14, 1); // Переміщаємо курсор на початок першого рядка
                  lcd.print(guess[2]);
                  guess[3] = '0'; // Встановлюємо початкове значення на '0'
                  lcd.setCursor(15, 1); // Переміщаємо курсор на початок першого рядка
                  lcd.print(guess[3]);
              }else{
                  render_history(secret, history, idx);
                  delay(350); // Wait for 350 milliseconds
                  lcd.clear();
                  lcd.setCursor(0, 0);
                  lcd.print("Attempt ");
                  lcd.print(attempt);
                  lcd.setCursor(0, 1);
                  lcd.print("Enter guess:");
                  guess[0] = '0'; // Встановлюємо початкове значення на '0'
                  lcd.setCursor(12, 1); // Переміщаємо курсор на початок першого рядка
                  lcd.print(guess[0]);
                  guess[1] = '0'; // Встановлюємо початкове значення на '0'
                  lcd.setCursor(13, 1); // Переміщаємо курсор на початок першого рядка
                  lcd.print(guess[1]);
                  guess[2] = '0'; // Встановлюємо початкове значення на '0'
                  lcd.setCursor(14, 1); // Переміщаємо курсор на початок першого рядка
                  lcd.print(guess[2]);
                  guess[3] = '0'; // Встановлюємо початкове значення на '0'
                  lcd.setCursor(15, 1); // Переміщаємо курсор на початок першого рядка
                  lcd.print(guess[3]);
              }
            }
            if(digitalRead(BTN_3_PIN) == HIGH){
              idx++;
              if(idx<attempt){
                render_history(secret, history, idx);
                delay(350);
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Attempt ");
                lcd.print(attempt);
                lcd.setCursor(0, 1);
                lcd.print("Enter guess:");
                guess[0] = '0'; // Встановлюємо початкове значення на '0'
                lcd.setCursor(12, 1); // Переміщаємо курсор на початок першого рядка
                lcd.print(guess[0]);
                guess[1] = '0'; // Встановлюємо початкове значення на '0'
                lcd.setCursor(13, 1); // Переміщаємо курсор на початок першого рядка
                lcd.print(guess[1]);
                guess[2] = '0'; // Встановлюємо початкове значення на '0'
                lcd.setCursor(14, 1); // Переміщаємо курсор на початок першого рядка
                lcd.print(guess[2]);
                guess[3] = '0'; // Встановлюємо початкове значення на '0'
                lcd.setCursor(15, 1); // Переміщаємо курсор на початок першого рядка
                lcd.print(guess[3]);
              }else{
                idx=attempt;
                lcd.clear();
                lcd.print("No Attempt");
                lcd.setCursor(0,1);
                lcd.print("try again)");
                delay(900);
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Attempt ");
                lcd.print(attempt);
                lcd.setCursor(0, 1);
                lcd.print("Enter guess:");
                guess[0] = '0'; // Встановлюємо початкове значення на '0'
                lcd.setCursor(12, 1); // Переміщаємо курсор на початок першого рядка
                lcd.print(guess[0]);
                guess[1] = '0'; // Встановлюємо початкове значення на '0'
                lcd.setCursor(13, 1); // Переміщаємо курсор на початок першого рядка
                lcd.print(guess[1]);
                guess[2] = '0'; // Встановлюємо початкове значення на '0'
                lcd.setCursor(14, 1); // Переміщаємо курсор на початок першого рядка
                lcd.print(guess[2]);
                guess[3] = '0'; // Встановлюємо початкове значення на '0'
                lcd.setCursor(15, 1); // Переміщаємо курсор на початок першого рядка
                lcd.print(guess[3]);
              }
            }
              //////////////////////////////IF 1
          } 
          if (digitalRead(BTN_2_PIN) == HIGH) {
            int currentValue = guess[1] - '0'; // Перетворюємо символ на число
            currentValue = (currentValue + 1) % 10; // Збільшуємо значення на 1, якщо менше 9
            guess[1] = currentValue + '0'; // Перетворюємо число на символ
            lcd.setCursor(13, 1); // Переміщаємо курсор на початок першого рядка
            lcd.print(guess[1]); // Виводимо значення першого елементу масиву
            delay(200);
          } 
          if (digitalRead(BTN_3_PIN) == HIGH) {
            int currentValue = guess[2] - '0'; // Перетворюємо символ на число
            currentValue = (currentValue + 1) % 10; // Збільшуємо значення на 1, якщо менше 9
            guess[2] = currentValue + '0'; // Перетворюємо число на символ
            lcd.setCursor(14, 1); // Переміщаємо курсор на початок першого рядка
            lcd.print(guess[2]); // Виводимо значення першого елементу масиву
            delay(200);
          } 
          if (digitalRead(BTN_4_PIN) == HIGH) {
            int currentValue = guess[3] - '0'; // Перетворюємо символ на число
            currentValue = (currentValue + 1) % 10; // Збільшуємо значення на 1, якщо менше 9
            guess[3] = currentValue + '0'; // Перетворюємо число на символ
            lcd.setCursor(15, 1); // Переміщаємо курсор на початок першого рядка
            lcd.print(guess[3]); // Виводимо значення першого елементу масиву
            delay(200);
          }
        /////////////////////////////WHILE
        }
        //перевірки
        guess[4]='\0';//для того щоб записало число з /0 до хісторі
        memcpy(history[attempt], guess, 5 * sizeof(guess[0]));//копіювання до хісторі
        lcd.clear();
        get_score(secret, guess, &peg_a, &peg_b);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("A: ");
        lcd.print(peg_a);
        lcd.setCursor(0,1);
        lcd.print("B: ");
        lcd.print(peg_b);
        render_leds(peg_a,peg_b);
        delay(2000);
        lcd.clear();
        turn_off_leds();
        // Перевірка чи вгадано таємний код
        if (peg_a == 4) {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Congratulations!");
            lcd.setCursor(0, 1);
            lcd.print("You won!");
            lcd.setCursor(0, 2);
            lcd.print("the code!");
            for (int i = 0; i < 30; i++) { // Повторюємо процес 10 разів
            int random_led = random(4); // Випадково вибираємо світлодіод для увімкнення
            switch(random_led) {
              case 0:
                digitalWrite(LED_RED_1, LOW); // Увімкнення червоного
                break;
              case 1:
                digitalWrite(LED_BLUE_1, LOW); // Увімкнення синього
                break;
              case 2:
                digitalWrite(LED_RED_4, LOW); // Увімкнення зеленого
                break;
              case 3:
                digitalWrite(LED_RED_2, LOW); // Увімкнення червоного (для другого світлодіоду)
                break;
              // додайте кейси для інших світлодіодів, якщо необхідно
            }
            delay(100); // Затримка для створення ефекту блимання
            turn_off_leds(); // Вимикаємо всі світлодіоди
          }
          delay(2000);
          break; // Вихід з циклу, якщо код вгадано
        }
        if(attempt>=9&&peg_a!=4){
          lcd.clear();
          lcd.print("LOSE lose(");
          lcd.setCursor(0,1);
          lcd.print("secret code:");
          lcd.print(secret);
          for (int i = 0; i < 10; i++) { // Повторюємо процес 10 разів
              int random_led = random(4); // Випадково вибираємо світлодіод для увімкнення
              switch(random_led) {
                case 0:
                  digitalWrite(LED_RED_1, LOW); // Увімкнення червоного
                  break;
                case 1:
                  digitalWrite(LED_BLUE_1, LOW); // Увімкнення синього
                  break;
                case 2:
                  digitalWrite(LED_RED_4, LOW); // Увімкнення зеленого
                  break;
                case 3:
                  digitalWrite(LED_RED_2, LOW); // Увімкнення червоного (для другого світлодіоду)
                  break;
                // додайте кейси для інших світлодіодів, якщо необхідно
              }
              delay(100); // Затримка для створення ефекту блимання
              turn_off_leds(); // Вимикаємо всі світлодіоди
          }
          delay(2000);
          break;
        }
    }
  for (int pam = 0; pam < 10; pam++)
  {
    free(history[pam]);
  }
  free(history);
}