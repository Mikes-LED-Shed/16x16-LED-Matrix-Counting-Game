
#include <FastLED.h>
#define NUM_LEDS 256  //16 x 16 Matrix
CRGB leds[NUM_LEDS];

int Number0[] = {13, 12, 11, 17, 21, 46, 42, 49, 53, 78, 74, 81, 85, 109, 108, 107};
int Number1[] = {12, 19, 44, 51, 76, 83, 108};
int Number2[] = {13, 12, 11, 17, 21, 43, 51, 77, 81, 110, 109, 108, 107, 106};
int Number3[] = {13, 12, 11, 17, 21, 42, 50, 51, 52, 74, 85, 81, 109, 108, 107};
int Number4[] = {17, 46, 42, 49, 53, 78, 77, 76, 75, 74, 85, 106};
int Number5[] = {14, 13, 12, 11, 10, 17, 46, 50, 51, 52, 74, 85, 106, 113, 114, 115, 116};
int Number6[] = {13, 12, 11, 10, 17, 46, 50, 51, 52, 78, 74, 81, 85, 110, 106, 114, 115, 116};
int Number7[] = {13, 12, 11, 10, 21, 42, 53, 74, 85, 106};
int Number8[] = {13, 12, 11, 10, 17, 22, 46, 41, 50, 51, 52, 53, 78, 73, 81, 86, 109, 108, 107, 106};
int Number9[] = {13, 12, 11, 17, 21, 46, 42, 50, 51, 52, 53, 75, 83, 109, 113};
int Number10[] = {9, 22, 41, 54, 73, 86, 105, 5, 4, 3, 25, 29, 38, 34, 57, 61, 70, 66, 89, 93, 101, 100, 99};
int Number11[] = {9, 22, 41, 54, 73, 86, 105, 6, 25, 38, 57, 70, 89, 102};
int Number12[] = {9, 22, 41, 54, 73, 86, 105, 25, 5, 4, 3, 2, 29, 35, 59, 69, 89, 102, 101, 100, 99, 98};
int Number13[] = {9, 22, 41, 54, 73, 86, 105, 5, 4, 3, 25, 29, 34, 58, 59, 60, 61, 66, 93, 101, 100, 99};
int Number14[] = {9, 22, 41, 54, 73, 86, 105, 6, 25, 38, 57, 70, 69, 68, 67, 35, 60, 92, 99};
int Number15[] = {9, 22, 41, 54, 73, 86, 1056, 5, 4, 3, 25, 38, 58, 59, 60, 67, 92, 102, 101, 100, 99};
int Number16[] = {9, 22, 41, 54, 73, 86, 105, 5, 4, 3, 2, 25, 38, 58, 59, 60, 70, 66, 89, 93, 102, 98, 122, 123, 124};
int Number17[] = {9, 22, 41, 54, 73, 86, 105, 6, 5, 4, 3, 2, 29, 34, 61, 66, 93, 98};
int Number18[] = {9, 22, 41, 54, 73, 86, 105, 5, 4, 3, 25, 29, 38, 34, 58, 59, 60, 70, 66, 89, 93, 101, 100, 99};
int Number19[] = {9, 22, 41, 54, 73, 86, 105, 5, 4, 3, 25, 29, 37, 34, 58, 59, 60, 61, 67, 91, 101, 121};
int Number20[] = {12, 11, 10, 18, 22, 42, 52, 76, 82, 109, 108, 107, 106, 105, 5, 4, 3, 25, 29, 38, 34, 57, 61, 70, 66, 89, 93, 101, 100, 99};

int buttonState = 0;
int GameStep = 0;
int TheRandomNumber = 0;
boolean DuplicateFound;
int MyArray[20];


void TheGameStepZero()
{
  FastLED.clear();
  for (int i = 0; i < 20; i++)
  {
    leds[random16(NUM_LEDS)] = CHSV(random8(), 255, 255); //CRGB::Red;
  }
}


void  ShowScore(int NumToShow[], int ArrayLen)
{

  FastLED.clear();
  for (int i = 0; i < ArrayLen; i++)
  {
    leds[NumToShow[i]] = CRGB::Blue;
  }
}

void ShowTheLEDData()
{

  FastLED.show();
}


void setup()
{

  FastLED.addLeds<WS2812, 7, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(100);

  pinMode(2, INPUT);
  Serial.begin(9600);

}

void loop()
{
  // Old Button
  buttonState = digitalRead(2);

  if (buttonState == HIGH) {

    if (GameStep == 0) {
      GameStep = 1;
    }

    if (GameStep == 99) {
      GameStep = 2;
    }

    if (GameStep == 98) {
      GameStep = 0;
    }
  }

  // Game Start
  if (GameStep == 0) {
    TheGameStepZero();

  }

  // Game Step 1
  if (GameStep == 1) {
    FastLED.clear();

    randomSeed(analogRead(0));
    TheRandomNumber = random8(20);
    if (TheRandomNumber == 0) {
      TheRandomNumber = 1;
    }
    Serial.print("Rnd = ");
    Serial.println(TheRandomNumber);

    for (int counter1 = 0; counter1 < TheRandomNumber; counter1++) {
      DuplicateFound = true;
      while (DuplicateFound == true) {
        MyArray[counter1] = random(1, 255);
        DuplicateFound = false;
        for (int counter2 = 0; counter2 < counter1; counter2++) {
          if (MyArray[counter1] == MyArray[counter2]) {
            DuplicateFound = true;
          }
        }
      }
    }


    for (int i = 0; i < TheRandomNumber; i++)
    {
      leds[MyArray[i]] = CHSV(random8(), 255, 255); //CRGB::Red;
    }
    GameStep = 99;
  }


  // Game Step 2
  if (GameStep == 2) {
    if (TheRandomNumber == 1)  {
      ShowScore(Number1, sizeof(Number1) / sizeof(Number1[0]));
    }
    if (TheRandomNumber == 2)  {
      ShowScore(Number2, sizeof(Number2) / sizeof(Number2[0]));
    }
    if (TheRandomNumber == 3)  {
      ShowScore(Number3, sizeof(Number3) / sizeof(Number3[0]));
    }
    if (TheRandomNumber == 4)  {
      ShowScore(Number4, sizeof(Number4) / sizeof(Number4[0]));
    }
    if (TheRandomNumber == 5)  {
      ShowScore(Number5, sizeof(Number5) / sizeof(Number5[0]));
    }
    if (TheRandomNumber == 6)  {
      ShowScore(Number6, sizeof(Number6) / sizeof(Number6[0]));
    }
    if (TheRandomNumber == 7)  {
      ShowScore(Number7, sizeof(Number7) / sizeof(Number7[0]));
    }
    if (TheRandomNumber == 8)  {
      ShowScore(Number8, sizeof(Number8) / sizeof(Number8[0]));
    }
    if (TheRandomNumber == 9)  {
      ShowScore(Number9, sizeof(Number9) / sizeof(Number9[0]));
    }

    if (TheRandomNumber == 10)  {
      ShowScore(Number10, sizeof(Number10) / sizeof(Number10[0]));
    }

    if (TheRandomNumber == 11)  {
      ShowScore(Number11, sizeof(Number11) / sizeof(Number1[0]));
    }

    if (TheRandomNumber == 12)  {
      ShowScore(Number12, sizeof(Number12) / sizeof(Number12[0]));
    }

    if (TheRandomNumber == 13)  {
      ShowScore(Number13, sizeof(Number13) / sizeof(Number13[0]));
    }

    if (TheRandomNumber == 14)  {
      ShowScore(Number14, sizeof(Number14) / sizeof(Number14[0]));
    }

    if (TheRandomNumber == 15)  {
      ShowScore(Number15, sizeof(Number15) / sizeof(Number15[0]));
    }

    if (TheRandomNumber == 16)  {
      ShowScore(Number16, sizeof(Number16) / sizeof(Number16[0]));
    }

    if (TheRandomNumber == 17)  {
      ShowScore(Number17, sizeof(Number17) / sizeof(Number17[0]));
    }

    if (TheRandomNumber == 18)  {
      ShowScore(Number18, sizeof(Number18) / sizeof(Number18[0]));
    }

    if (TheRandomNumber == 19)  {
      ShowScore(Number19, sizeof(Number19) / sizeof(Number19[0]));
    }

    if (TheRandomNumber == 20)  {
      ShowScore(Number20, sizeof(Number20) / sizeof(Number20[0]));
    }

    GameStep = 98;
  }

  ShowTheLEDData();
  delay(200);


  
}
