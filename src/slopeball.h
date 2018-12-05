#include "main.h"

#ifndef Slopeball_H
#define Slopeball_H


class Slopeball {
public:
    Slopeball() {}
    Slopeball(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    double r;
    int slope;
    bool status;
    bounding_box_t bounding_box();
private:
    VAO *object;
    VAO *inclinedplane;
};

#endif // Slopeball_H
