#include "main.h"
#include "player.h"

#ifndef Magnet_H
#define Magnet_H


class Magnet {
public:
    Magnet() {}
    Magnet(float x, float y);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    double r;
    int timer;
    void tick();
    bool status;
    bounding_box_t bounding_box();
    int dir;
    bool detect_collision(Player p);
private:
    VAO *object1;//edges
    VAO *object2;//bars
    VAO *object3;//semi circle
};

#endif // Magnet_H
