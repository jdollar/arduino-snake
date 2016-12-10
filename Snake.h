#ifndef _SNAKE_H_INCLUDED_
#define _SNAKE_H_INCLUDED_

#include "Point.h"
#include "Arduino.h"

class Snake {
  private:
    Point location;
    Point speed;
    Point * body;
    uint8_t bodyCount;
  public:
    Snake();
    ~Snake();
    void update(int8_t xSpeed, int8_t ySpeed);
    void move();
    void eat();
    void increase(Point** array);
    Point getLocation();
    Point * getBody();
    uint8_t getBodyCount();
};

#endif
