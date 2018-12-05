#include "main.h"

#ifndef Digit_H
#define Digit_H


class Digit {
public:
    Digit() {}
    Digit(float x, float y,int number);
    glm::vec3 position;
    float rotation;
    int no;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
private:
    VAO *object[7];
};

#endif // Digit_H
