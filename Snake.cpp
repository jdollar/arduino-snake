#include "Snake.h"

Snake::Snake() : location(0,0), speed(0,1){
  body = (Point *) malloc(1 * sizeof(Point));
  body[0] = location;
  bodyCount = (uint8_t) 1;
}

Snake::~Snake() {
}

void Snake::update(int8_t xSpeed, int8_t ySpeed) {
  speed.setX(xSpeed);
  speed.setY(ySpeed);
}

void Snake::move() {
  int8_t newX = location.getX() + speed.getX();
  int8_t newY = location.getY() + speed.getY();

  location.setX(newX);
  location.setY(newY);

  Point newLocation(newX, newY);

  Point prevPosition;
  for (uint8_t i = 0; i < bodyCount; i++) {
    prevPosition = body[i];
    body[i] = newLocation;
    newLocation = prevPosition;
  }
}

void Snake::eat() {
  body = (Point *) realloc(body, ++bodyCount * sizeof(Point));
}

Point Snake::getLocation() {
  return location;
}

Point* Snake::getBody() {
  return body;
}

uint8_t Snake::getBodyCount() {
  return bodyCount;
}
