#define SYMBOL_DOWN_ARROW 0
#define SYMBOL_UP_ARROW 1
#define SYMBOL_RUN_ARROW 2
#define SYMBOL_ANGSTROM 3
#define SYMBOL_STEPS_UNTIS 4

byte angtrom[] = {
  B01110,
  B01110,
  B00000,
  B01110,
  B10001,
  B11111,
  B10001,
  B10001
};

byte run_arrow[] = {
  B01000,
  B01100,
  B01110,
  B01111,
  B01111,
  B01110,
  B01100,
  B01000
};

byte up_arrow[] = {
  B00100,
  B01110,
  B10101,
  B00100,
  B00100,
  B00100,
  B00100,
  B00100
};

byte down_arrow[] = {
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,
  B10101,
  B01110,
  B00100
};
