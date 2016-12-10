//#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include "Snake.h"
#include "Point.h"

#define MAX_DEVICES 4
#define CLK_PIN 13
#define DATA_PIN 11
#define CS_PIN 10

#define DEFAULT_ZONE 0
#define DISPLAY_TEXT "Hello World"

#define MAX_Y 31
#define MAX_X 7

#define LEFT_PIN 2
#define DOWN_PIN 3
#define UP_PIN 4
#define RIGHT_PIN 5

#define LOOP_COUNT_TRIGGER 70 //uint8_t size

Point generateRandomLocation() {
  return Point((uint8_t) random(0, MAX_X), (uint8_t) random(0, MAX_Y));
}

// Hardware SPI connection
//MD_Parola P = MD_Parola(CS_PIN, MAX_DEVICES);
MD_MAX72XX mdMax = MD_MAX72XX(CS_PIN, MAX_DEVICES);
Snake snake = Snake();
Point foodLocation = generateRandomLocation();

int x = 0;
int y = 0;
int val = 0;

uint8_t loopCounter = 0;

void setup(void)
{
  Serial.begin(9600);
  mdMax.begin();
  pinMode(LEFT_PIN, INPUT);
  pinMode(DOWN_PIN, INPUT);
  pinMode(UP_PIN, INPUT);
  pinMode(RIGHT_PIN, INPUT);

  mdMax.setPoint(foodLocation.getX(), foodLocation.getY(), true);
}

void updateDirection() {
  if (digitalRead(RIGHT_PIN) == HIGH) {
    snake.update(1, 0);
  } else if (digitalRead(LEFT_PIN) == HIGH) {
    snake.update(-1, 0);
  } else if (digitalRead(UP_PIN) == HIGH) {
    snake.update(0, 1);
  } else if (digitalRead(DOWN_PIN) == HIGH) {
    snake.update(0, -1);
  }
}

void moveSnake() {
  uint8_t snakeBodyCount = snake.getBodyCount();
  Serial.print(snakeBodyCount);
  mdMax.setPoint(snake.getBody()[snakeBodyCount-1].getX(), snake.getBody()[snakeBodyCount-1].getY(), false);
  snake.move();
  mdMax.setPoint(snake.getLocation().getX(), snake.getLocation().getY(), true);
}

bool isSnakeOnFood() {
  Point snakeLocation = snake.getLocation();
  return snakeLocation.equals(foodLocation);
}

bool isLocationInsideSnake(Point location) {
  bool locationInsideSnake = false;

  Point * snakeBody = snake.getBody();
  uint8_t snakeBodyCount = snake.getBodyCount();

  for (uint8_t i = 0; i < snakeBodyCount; i++) {
    if (snakeBody[i].equals(location)) {
      locationInsideSnake = true;
      break;
    }
  }

  return locationInsideSnake;
}

bool isSnakeInsideField() {
  Point snakeLocation = snake.getLocation();
  bool isInXBounds = snakeLocation.getX() < MAX_X && snakeLocation.getX() >= 0;
  bool isInYBounds = snakeLocation.getY() < MAX_Y && snakeLocation.getY() >= 0;
  return isInXBounds && isInYBounds;
}

void createNewFood() {
  Point possibleFoodLocation = generateRandomLocation();
  while(isLocationInsideSnake(possibleFoodLocation)) {
    Point possibleFoodLocation = generateRandomLocation();
  }

  foodLocation = possibleFoodLocation;
  mdMax.setPoint(foodLocation.getX(), foodLocation.getY(), true);
}

bool isSnakeEatingItself() {
  Point snakeLocation = snake.getLocation();
  Point * snakeBody = snake.getBody();
  uint8_t snakeBodyCount = snake.getBodyCount();

  bool isSnakeEatingItself = false;

  for (uint8_t i = 1; i < snakeBodyCount; i++) {
    if (snakeBody[i].equals(snakeLocation)) {
      isSnakeEatingItself = true;
      break;
    }
  }

  return isSnakeEatingItself;
}

void loop(void)
{
  updateDirection();

  if (loopCounter >= LOOP_COUNT_TRIGGER) {
    moveSnake();

    if (isSnakeOnFood()) {
      snake.eat();
      createNewFood();
    }

    loopCounter = 0;
  } else {
    loopCounter++;
  }

  if (!isSnakeInsideField() || isSnakeEatingItself()) {
    mdMax.setPoint(0, 0, true);
  }

  // Point * snakeBody = snake.getBody();
  // uint8_t snakeBodyCount = snake.getBodyCount();

  delay(10);
}
