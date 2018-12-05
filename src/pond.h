#include "main.h"
#include "player.h"
#ifndef Pond_H
#define Pond_H


class Pond {
public:
    Pond() {}
    Pond(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    double r;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    bounding_box_t bounding_box();
    bool detect_collision(Player p);

private:
    VAO *object;
};

#endif // Pond_H
