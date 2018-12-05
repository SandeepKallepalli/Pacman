#include "magnet.h"
#include "main.h"

Magnet::Magnet(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    dir=rand()%2;
    if(dir==0)
        this->rotation = 0;
    else
        this->rotation = 180;
    this->timer=0;
    static GLfloat vertex_buffer_data1[180*9];
    float angle=90*M_PI/180;
    r=1;
    for(int vertin=0;vertin<180;vertin++)
     {
                vertex_buffer_data1[vertin*9]=0.0f;
                vertex_buffer_data1[vertin*9+1]=0.0f;
                vertex_buffer_data1[vertin*9+2]=0.0f;

                vertex_buffer_data1[vertin*9+3]=r*cos(angle);
                vertex_buffer_data1[vertin*9+4]=r*sin(angle);
                vertex_buffer_data1[vertin*9+5]=0;

                vertex_buffer_data1[vertin*9+6]=r*cos(angle+(M_PI/180.0));
                vertex_buffer_data1[vertin*9+7]=r*sin(angle+(M_PI/180.0));
                vertex_buffer_data1[vertin*9+8]=0;

                angle+=M_PI/180.0;
     };
    this->object1 = create3DObject(GL_TRIANGLES, 180*3, vertex_buffer_data1, COLOR_RED, GL_FILL);
    static GLfloat vertex_buffer_data2[1440*9];
    angle=90*M_PI/180;
    r=0.8;
    for(int vertin=0;vertin<1440;vertin++)
     {
                vertex_buffer_data2[vertin*9]=0.0f;
                vertex_buffer_data2[vertin*9+1]=0.0f;
                vertex_buffer_data2[vertin*9+2]=0.0f;

                vertex_buffer_data2[vertin*9+3]=r*cos(angle);
                vertex_buffer_data2[vertin*9+4]=r*sin(angle);
                vertex_buffer_data2[vertin*9+5]=0;

                vertex_buffer_data2[vertin*9+6]=r*cos(angle+(M_PI/180.0));
                vertex_buffer_data2[vertin*9+7]=r*sin(angle+(M_PI/180.0));
                vertex_buffer_data2[vertin*9+8]=0;

                angle+=M_PI/1440.0;
     };
    this->object2 = create3DObject(GL_TRIANGLES, 1440*3, vertex_buffer_data2, COLOR_BACKGROUND, GL_FILL);
    static const GLfloat vertex_buffer_data3[]={
        0,1,0,
        0.5,1,0,
        0.5,0.8,0,

        0,1,0,
        0.5,0.8,0,
        0,0.8,0,


        0,-1,0,
        0.5,-1,0,
        0.5,-0.8,0,

        0,-1,0,
        0.5,-0.8,0,
        0,-0.8,0,

    };
    this->object3 = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data3, COLOR_RED, GL_FILL);
}

void Magnet::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object3);
    draw3DObject(this->object1);

    draw3DObject(this->object2);

}

void Magnet::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

bounding_box_t Magnet::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.4, 0.4 };
    return bbox;
}

void Magnet::tick(){
    this->timer+=1;
}

bool Magnet::detect_collision(Player p)
{
    return (fabs(this->position.x - p.position.x) <= 2 && fabs(this->position.y - p.position.y) <= 1);
}
