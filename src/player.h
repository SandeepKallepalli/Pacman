#include "main.h"
#include "ball.h"
#include "slopeball.h"

#ifndef Player_H
#define Player_H


class Player {
public:
    Player() {}
    Player(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(GLFWwindow *window);
    void tick_water();
    double score;
    int level;
    int lives;
    double r;
    double speedx;
    double speedy;
    double accerlation;
    bool detect_collision(Ball b);
    bool detect_collision_reflection(Slopeball b);
    bounding_box_t bounding_box();
private:
    VAO* object[6];
};

#endif // Player_H

