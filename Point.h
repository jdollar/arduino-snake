#ifndef _POINT_H_INCLUDED_
#define _POINT_H_INCLUDED_

#include <Arduino.h>

class Point {
  private:
    int8_t x;
    int8_t y;
  public:
    Point();
    Point(int8_t xValue, int8_t yValue);
    ~Point();
    int8_t getX();
    int8_t getY();
    void setX(int8_t xValue);
    void setY(int8_t yValue);
    bool equals(Point otherPoint);
};

#endif
