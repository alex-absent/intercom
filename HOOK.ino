#include <MsTimer2.h>

#define MEASURE_PERIOD 50  // время периода измерения
#define PIN_RELAY 5

int timeCount, aver;  // счетчик времени
long temp;
long  sumU1; // переменные для суммирования кодов АЦП
long  avarageU1; // сумма кодов АЦП (среднее значение * 500)
boolean flagReady;  // признак готовности данных измерения
boolean answer = false;  // признак готовности данных измерения

void setup() {
  Serial.begin(9600); // инициализируем порт, скорость 9600
  MsTimer2::set(1, timerInterupt); // прерывания по таймеру, период 1 мс
  MsTimer2::start();              // разрешение прерывания
  pinMode(PIN_RELAY, OUTPUT); // Объявляем пин реле как выход
  digitalWrite(PIN_RELAY, HIGH); // Выключаем реле - посылаем высокий сигнал
}

void loop() {

if (answer == false) {
  if ( flagReady == true ) {
    flagReady= false;
    Serial.print("U1-initial = ");
    aver = (float)avarageU1 / 500. * 5. / 1024. * 9400;
    Serial.println (aver);
    }

    if (aver >= 180) {Serial.println ("bla bla");}
    else {
      answer = true;
      delay (500);
      }  
      
      }
    

//////////////////////////////////////
  if (answer == true) {
    if ( flagReady == true ) {
    flagReady= false;
    Serial.print("U1 - wait = ");
    aver = (float)avarageU1 / 500. * 5. / 1024. * 9400;
    Serial.println (aver);
    }

    if (aver >= 181) {
      Serial.println ("relay");
      digitalWrite(PIN_RELAY, LOW); // Включаем реле - посылаем низкий уровень сигнала
      delay(100000);
      digitalWrite(PIN_RELAY, HIGH);
    }
    }
    
}

// обработка прерывания 1 мс
void  timerInterupt() {

  timeCount++;  // +1 счетчик выборок усреднения
  sumU1+= analogRead(A0);  // суммирование кодов АЦП

  // проверка числа выборок усреднения
  if ( timeCount >= MEASURE_PERIOD ) {
    timeCount= 0;
    avarageU1= sumU1; // перегрузка среднего значения
    sumU1= 0;
    flagReady= true;  // признак результат измерений готов
    }
}   
