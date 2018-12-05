#include "trampoline.h"
#include "main.h"

Trampoline::Trampoline(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    static GLfloat vertex_buffer_data[180*9];
    double angle=0.0;
    r=0.5;
    for(int vertin=0;vertin<180;vertin++)
     {
                vertex_buffer_data[vertin*9]=0.0f;
                vertex_buffer_data[vertin*9+1]=0.0f;
                vertex_buffer_data[vertin*9+2]=0.0f;

                vertex_buffer_data[vertin*9+3]=r*cos(angle);
                vertex_buffer_data[vertin*9+4]=r*sin(angle);
                vertex_buffer_data[vertin*9+5]=0;

                vertex_buffer_data[vertin*9+6]=r*cos(angle+(M_PI/180.0));
                vertex_buffer_data[vertin*9+7]=r*sin(angle+(M_PI/180.0));
                vertex_buffer_data[vertin*9+8]=0;

                angle-=M_PI/180.0;
     };
    this->object1 = create3DObject(GL_TRIANGLES, 180*3, vertex_buffer_data, color, GL_FILL);
    static const GLfloat vertex_buffer_data1[] = {
        -0.5, 0, 0,
        -0.6, 0, 0,
        -0.5, -1.0, 0,

        -0.6, -1, 0,
        -0.6, 0, 0,
        -0.5, -1.0, 0,

         0.5, 0, 0,
         0.6, 0, 0,
         0.5, -1.0, 0,

         0.6, -1, 0,
         0.6, 0, 0,
         0.5, -1.0, 0,
    };
    this->object2 = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data1, color, GL_FILL);
}

void Trampoline::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
}

void Trampoline::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}


bounding_box_t Trampoline::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.4, 0.4 };
    return bbox;
}

bool Trampoline::detect_collision( Player p) {
    return fabs(this->position.x - p.position.x)<=0.5 && this->position.y<p.position.y
            && fabs(p.position.y-this->position.y - p.r) <= -p.speedy ;
}
