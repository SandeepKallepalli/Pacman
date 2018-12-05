#include "porcupine.h"
#include "main.h"

Porcupine::Porcupine(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed=0;
    static const GLfloat vertex_buffer_data[] = {
        0,0,0,
        0.2*0.7,0,0,
        0.1*0.7,0.1*0.7,0,

        0.2*0.7,0,0,
        0.4*0.7,0,0,
        0.3*0.7,0.1*0.7,0,

        0.4*0.7,0,0,
        0.6*0.7,0,0,
        0.5*0.7,0.1*0.7,0,

        -0,0,0,
        -0.2*0.7,0,0,
        -0.1*0.7,0.1*0.7,0,

        -0.2*0.7,0,0,
        -0.4*0.7,0,0,
        -0.3*0.7,0.1*0.7,0,

        -0.4*0.7,0,0,
        -0.6*0.7,0,0,
        -0.5*0.7,0.1*0.7,0,
    };

    this->object = create3DObject(GL_TRIANGLES, 18, vertex_buffer_data, color, GL_FILL);
}

void Porcupine::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Porcupine::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Porcupine::tick(Player p) {
    if(this->position.x > p.position.x)
        this->speed=0.005;
    else if(this->position.x < p.position.x)
        this->speed=-0.005;

    this->position.x -= speed;
    if(this->position.x > 3.9)
        this->position.x=-4;
    if(this->position.x < -3.9)
        this->position.x=4;
}

bounding_box_t Porcupine::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.18, 0.02 };
    return bbox;
}

bool Porcupine::detect_collision( Player p) {
    return fabs(this->position.x - p.position.x)<=0.62 && p.position.y<= -0.27 && fabs(p.position.x)>=1;
}
