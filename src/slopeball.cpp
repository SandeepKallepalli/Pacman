#include "slopeball.h"
#include "main.h"

Slopeball::Slopeball(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = -0.00f;
    status=true;
    static GLfloat vertex_buffer_data[360*9];
    float angle=0;
    r=0.2;
    for(int vertin=0;vertin<360;vertin++)
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

                angle+=M_PI/180.0;
     };
    this->object = create3DObject(GL_TRIANGLES, 360*3, vertex_buffer_data, color, GL_FILL);
    this->slope=rand()%2;
    //if slope is 0 we will have slope touching left if it is 1 then roght side otherwise slope is not there
    if(this->slope==1)
    {
        static const GLfloat vertex_buffer_data1[]={
            r*sqrt(2)       ,      0          , 0,
            r*sqrt(2) + 0.05,      0          , 0,
                    0             ,  r*sqrt(2), 0,


                    0             ,r*sqrt(2) + 0.05, 0,
            r * sqrt(2) + 0.05,          0           , 0,
                    0             ,  r*sqrt(2)     , 0,
        };
        this->inclinedplane = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data1, COLOR_BROWN, GL_FILL);
    }
    else if(this->slope==0)
    {
        static const GLfloat vertex_buffer_data1[]={
            -r*sqrt(2)       ,      0          , 0,
            -r*sqrt(2) - 0.05,      0          , 0,
                    0             ,  r*sqrt(2), 0,


                    0             ,r*sqrt(2) + 0.05, 0,
            -r * sqrt(2) - 0.05,          0           , 0,
                    0             ,  r*sqrt(2)     , 0,
        };
        this->inclinedplane = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data1, COLOR_BROWN, GL_FILL);
    }
}

void Slopeball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->inclinedplane);
}

void Slopeball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Slopeball::tick() {
    this->position.x -= speed;
    if(this->position.x>(3.9+screen_center_x)/screen_zoom)
    {
        this->position.x=(-4.5+screen_center_x)/screen_zoom;
        this->position.y=rand()%5;
        this->speed= -double(rand()%5)/100.0;
        while(!this->speed)
        {
            this->speed= -double(rand()%5)/100.0;
        }
    }
    // this->position.y -= speed;
}

bounding_box_t Slopeball::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.4, 0.4 };
    return bbox;
}
