#include "pond.h"
#include "main.h"

Pond::Pond(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    static GLfloat vertex_buffer_data[360*9];
    double angle=0.0;
    r=1.0;
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

                angle-=M_PI/180.0;
     };
    this->object = create3DObject(GL_TRIANGLES, 180*3, vertex_buffer_data, color, GL_FILL);
}

void Pond::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Pond::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

bounding_box_t Pond::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.4, 0.4 };
    return bbox;
}

bool Pond::detect_collision(Player p)
{
    //if player is about to fall in the pond this func will detect and does the trajectory accordingly.
    if(fabs(this->position.x-p.position.x)<=this->r && (fabs(this->position.y-p.position.y+0.2)<=0.01 || p.position.y-0.2 < this->position.y))//dist btw x's should be less than 1 and btw y's should be less than 0.014
    {
        if(fabs(sqrt(pow(this->position.x-p.position.x , 2)+pow(this->position.y - p.position.y , 2 ))-(this->r-p.r)) > 0.01)
        {
            //printf("entered pond");
            return true;
        }
        else
            return false;
    }
}
