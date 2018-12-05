#include "digit.h"

Digit::Digit(float x, float y,int number) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->no=number;
    color_t color=COLOR_WHITE;
    static const GLfloat vertex_buffer_data1[] = {
        -0.2, 0, 0, // vertex 1
        0.2,  0, 0, // vertex 2
    };
    static const GLfloat vertex_buffer_data2[] = {
        0.2,  0, 0,
        0.2,-0.2,0,
    };
    static const GLfloat vertex_buffer_data3[] = {
        0.2,-0.2,0,
        -0.2,-0.2,0,
    };
    static const GLfloat vertex_buffer_data4[] = {
        -0.2,-0.2,0,
        -0.2, 0, 0,
    };
    static const GLfloat vertex_buffer_data5[] = {
        0.2,  0, 0,
        0.2,0.2,0,
    };
    static const GLfloat vertex_buffer_data6[] = {
        0.2,0.2,0,
        -0.2,0.2,0,
    };
    static const GLfloat vertex_buffer_data7[] = {
        -0.2,0.2,0,
        -0.2, 0, 0,
    };


    if((this->no!=1&&this->no!=7&&this->no!=0))
        color=COLOR_WHITE;
    else
        color=COLOR_BACKGROUND;
    this->object[0] = create3DObject(GL_LINES, 2, vertex_buffer_data1, color, GL_FILL);


    if(this->no!=2)
        color=COLOR_WHITE;
    else
        color=COLOR_BACKGROUND;
    this->object[1] = create3DObject(GL_LINES, 2, vertex_buffer_data2, color, GL_FILL);


    if(this->no==0||this->no==2||this->no==3||this->no==5||this->no==6||this->no==8)
        color=COLOR_WHITE;
    else
        color=COLOR_BACKGROUND;
    this->object[2] = create3DObject(GL_LINES, 2, vertex_buffer_data3, color, GL_FILL);




    if(this->no==2||this->no==6||this->no==8||this->no==0)
        color=COLOR_WHITE;
    else
        color=COLOR_BACKGROUND;
    this->object[3] = create3DObject(GL_LINES, 2, vertex_buffer_data4, color, GL_FILL);




    if((this->no!=5&&this->no!=6))
        color=COLOR_WHITE;
    else
        color=COLOR_BACKGROUND;
    this->object[4] = create3DObject(GL_LINES, 2, vertex_buffer_data5, color, GL_FILL);





    if((this->no!=1&&this->no!=4))
        color=COLOR_WHITE;
    else
        color=COLOR_BACKGROUND;
    this->object[5] = create3DObject(GL_LINES, 2, vertex_buffer_data6, color, GL_FILL);



    if(this->no==4||this->no==9||this->no==5||this->no==6||this->no==8||this->no==0)
        color=COLOR_WHITE;
    else
        color=COLOR_BACKGROUND;
    this->object[6] = create3DObject(GL_LINES, 2, vertex_buffer_data7, color, GL_FILL);

}

void Digit::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    //this->no=9;
    /*
    if((this->no!=1&&this->no!=7&&this->no!=0))
        draw3DObject(this->object[0]);
    if(this->no!=2)
        draw3DObject(this->object[1]);
    if(this->no==0||this->no==2||this->no==3||this->no==5||this->no==6||this->no==8)
        draw3DObject(this->object[2]);
    if(this->no==2||this->no==6||this->no==8||this->no==0)
        draw3DObject(this->object[3]);
    if((this->no!=5&&this->no!=6))
        draw3DObject(this->object[4]);
    if((this->no!=1&&this->no!=4))
        draw3DObject(this->object[5]);
    if(this->no==4||this->no==9||this->no==5||this->no==6||this->no==8||this->no==0)
        draw3DObject(this->object[6]);*/
    for(int i=0;i<7;i++)
        draw3DObject(this->object[i]);
}
