#include "main.h"
#include "player.h"

#ifndef Trampoline_H
#define Trampoline_H


class Trampoline {
public:
    Trampoline() {}
    Trampoline(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    double r;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    bool detect_collision(Player p);
    bounding_box_t bounding_box();
private:
    VAO* object1;
    VAO* object2;
};

#endif // Trampoline_H

