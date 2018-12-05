#include "main.h"
#include "player.h"

#ifndef Porcupine_H
#define Porcupine_H


class Porcupine {
public:
    Porcupine() {}
    Porcupine(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(Player p);
    double speed;
    bool detect_collision(Player p);
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // Porcupine_H
