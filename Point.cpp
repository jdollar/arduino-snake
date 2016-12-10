#include "Point.h"
#include "Arduino.h"

Point::Point() {

}

Point::Point(int8_t xValue, int8_t yValue) {
  x = xValue;
  y = yValue;
}

Point::~Point() {

}

int8_t Point::getX() {
  return x;
}

int8_t Point::getY() {
  return y;
}

void Point::setX(int8_t xValue) {
  x = xValue;
}

void Point::setY(int8_t yValue) {
  y = yValue;
}

bool Point::equals(Point otherPoint) {
  return x == otherPoint.getX() && y == otherPoint.getY();
}
