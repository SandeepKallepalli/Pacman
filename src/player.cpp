#include "player.h"
#include "main.h"

Player::Player(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    double score;
    this->level=1;
    this->lives=3;
    speedx = 0.0;
    speedy = 0.0;
    accerlation=0.0;
    static GLfloat vertex_buffer_data[6][60*9];
    float angle=0;
    double r=0.2f;
    for(int i=0;i<6;i++)
    {

    for(int vertin=0;vertin<60;vertin++)
     {
                vertex_buffer_data[i][vertin*9]=0.0f;
                vertex_buffer_data[i][vertin*9+1]=0.0f;
                vertex_buffer_data[i][vertin*9+2]=0.0f;

                vertex_buffer_data[i][vertin*9+3]=r*cos(angle);
                vertex_buffer_data[i][vertin*9+4]=r*sin(angle);
                vertex_buffer_data[i][vertin*9+5]=r;

                vertex_buffer_data[i][vertin*9+6]=r*cos(angle+(M_PI/180.0));
                vertex_buffer_data[i][vertin*9+7]=r*sin(angle+(M_PI/180.0));
                vertex_buffer_data[i][vertin*9+8]=r;

                angle+=M_PI/180.0;
     };
        if(i==0)
            this->object[i] = create3DObject(GL_TRIANGLES, 60*3, vertex_buffer_data[i], COLOR_BLUE, GL_FILL);
        if(i==1)
            this->object[i] = create3DObject(GL_TRIANGLES, 60*3, vertex_buffer_data[i], COLOR_RED, GL_FILL);
        if(i==2)
            this->object[i] = create3DObject(GL_TRIANGLES, 60*3, vertex_buffer_data[i], COLOR_GREEN, GL_FILL);
        if(i==3)
            this->object[i] = create3DObject(GL_TRIANGLES, 60*3, vertex_buffer_data[i], COLOR_VIOLET, GL_FILL);
        if(i==4)
            this->object[i] = create3DObject(GL_TRIANGLES, 60*3, vertex_buffer_data[i], COLOR_YELLOW, GL_FILL);
        if(i==5)
            this->object[i] = create3DObject(GL_TRIANGLES, 60*3, vertex_buffer_data[i], COLOR_ORANGE, GL_FILL);
    }
}

void Player::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    for(int i=0;i<6;i++)
        draw3DObject(this->object[i]);
}

void Player::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Player::tick(GLFWwindow *window) {
    //printf("score is %lf\n",this->score);
    if(this->speedy>0)
    {
        this->accerlation=0.005;
    }
    while(this->rotation>=360.0)
        this->rotation-=360.0;
    this->position.x += speedx;
    this->position.y += speedy;
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    if(this->position.x>(3.9+screen_center_x)/screen_zoom && (right||this->speedx>0))
        this->position.x=(-4+screen_center_x)/screen_zoom;
    if(this->position.x<(-3.9+screen_center_x)/screen_zoom && (left||this->speedx<0))
        this->position.x=(4+screen_center_x)/screen_zoom;
    if(this->position.y<=-0.4)
    {
        this->accerlation=0;
        this->speedy=0;
        this->speedx=0;
        this->position.y=-0.4;
    }
    this->speedy-=this->accerlation;
    // this->position.y -= speed;
}
void Player::tick_water() {
    printf("score is %lf\n",this->score);
    if(this->speedy>0)
    {
        this->accerlation=0.001;
    }
    this->position.x += speedx;
    this->position.y += speedy;
    double yappr=-0.6-sqrt(0.64-pow(this->position.x,2));
    if(this->position.y>yappr)
    {
        //printf("accrelation applied\n");
        this->accerlation=0.001;
    }
    //printf("p position is %lf %lf\n",this->position.x,this->position.y);
    if(this->position.y<=yappr)
    {
        this->accerlation=0;
        this->speedy=0;
        this->speedx=0;
        this->position.y=yappr;
        //printf("should slide\n");
        if(this->position.x<0)
        {
            this->position.x+=0.009;
            this->rotation-=9;
        }
        else if(this->position.x>0)
        {
            this->position.x-=0.009;
            this->rotation+=9;
        }
        if(fabs(this->position.x)<=0.009)
        {
            this->position.x=0;
        }
    }
    this->speedy-=this->accerlation;
    // this->position.y -= speed;
}

bounding_box_t Player::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.4, 0.4 };
    return bbox;
}

bool Player::detect_collision( Ball b) {

//    return (abs(this->position.x - b.position.x)<0.00000000000000000000000001)
//            && ((this->position.y ) > (b.position.y ))
//            && ((this->position.y - this->r - b.position.y - b.r) < 0.000000000000000000001*b.r);
        return sqrt(pow((this->position.x - b.position.x),2) + pow((this->position.y-b.position.y - this->r + b.r),2))<=0.3
                && this->position.y > b.position.y  && this->speedy<=0;

}
bool Player::detect_collision_reflection( Slopeball b) {

    if(b.slope==0||b.slope==1)
    {
        //printf("slope ball\n");
        if(b.slope==0)
        {
            //left inclination slope and reflection happens only if there is a speedy in -ve direction
            //speedy becomes speed but in the left direction
            if((sqrt(pow((this->position.x - b.position.x),2) + pow((this->position.y-b.position.y ),2)) - b.r -this->r)<=0.3
                    && this->position.x < b.position.x  && this->position.y > b.position.y && this->speedy<=0)
            {
                this->speedx=-0.1;
                //this->speedy=0.000001;
                return true;
            }
        }
        else
        {
            //right inclination slope and reflection happens only if there is a speedy in -ve direction
            //speedy becomes speed but in the right direction
            if(sqrt(pow((this->position.x - b.position.x),2) + pow((this->position.y-b.position.y - this->r + b.r),2))<=0.3
                    && this->position.x > b.position.x && this->position.y > b.position.y  && this->speedy<=0)
            {
                this->speedx=0.1;
                //this->speedy=0.000001;
                return true;
            }
        }
    }

}
