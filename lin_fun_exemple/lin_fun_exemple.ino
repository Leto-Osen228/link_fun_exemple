/*
   Пример создания функций,
   имена переменных в которых могут отличаться от имен в остальном коде.
   Необходимо это потому, что разные разработчики могут использовать разные имена переменных.
   Такой подход решает эту проблему

   Разработано: Александром Алексеевичем Петровым
   Специально для команды Х
   07.03.2022
*/

#define BTN1 4
#define BTN2 5

// структура в формате которой будут храниться все данные
struct data {
  uint8_t counter;
  bool outFlag;
  bool flag;
};

// создаём объекты такой структуры
data data1;
data data2;

void setup() {
  Serial.begin(115200);
  pinMode(BTN1, INPUT_PULLUP);
  pinMode(BTN2, INPUT_PULLUP);
}

void loop() {
  // функция опроса
  // приведён пример передачи адреса в функцию
  readBTN(BTN1, &data1.counter, &data1.outFlag, &data1.flag);

  // функция отправки данных
  // создавать ссылку на текс как правило не нужно
  // Иногда может потребоваться преобразование типа: (const char*)"текс"
  printData("counter 1 : ", &data1.counter, &data1.outFlag);

  readBTN(BTN2, &data2.counter, &data2.outFlag, &data2.flag);
  printData("counter 2 : ", &data2.counter, &data2.outFlag);

  // дополнительных задач нет,поэтому задержку можно допустить
  // Никогда так не делайте!
  delay(50);
}

// функция читает значение кнопки и при начатие прибавляет 1 к счётчику
// она принимает: номер пина и адреса: счётчика, флага обновления данных, флаг для кнопки
void readBTN(uint8_t pin, uint8_t *counter, bool *outFlag, bool *flag) {
  // вызывать раз в 50мс
  bool btn = !digitalRead(pin);
  // если кнопка стала нажата
  if (btn == 1 && *flag == 0) {
    *flag = 1;      // присваеваем флагу кнопки значение 1
    *counter += 1;  // прибавляем 1 к счётчику
    *outFlag = 1;
  } 
  //если кнопку отпустили
  else if (btn == 0 && *flag == 1) {
    *flag = 0;
  }
}

// функция по флагу отправляет данные в порт
// принемает строку с текстом, ссылку на данные и ссылку на флаг
void printData(const char* text, uint8_t *data, bool *outFlag) {
  // вызывать раз в 50мс
  //если outFlag поднят
  if (*outFlag == 1) {
    Serial.write(text);
    Serial.println(*data);
    *outFlag = 0;
  }
}
