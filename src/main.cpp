#include "main.h"
#include "timer.h"
#include "ball.h"
#include "slopeball.h"
#include "player.h"
#include "ground.h"
#include "pond.h"
#include "trampoline.h"
#include "porcupine.h"
#include "magnet.h"
#include "digit.h"

using namespace std;
GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/
int n=30;
Ball ball[30];
Slopeball slopeball[10];
Ground soil1,soil2,grass;
Player player;
Pond pond;
Trampoline trampoline;
Porcupine porcupine;
Magnet magnet;
Digit digit[4];
float screen_zoom = 1.0, screen_center_x = 0, screen_center_y = 0.8;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    // glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    // glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    // glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    // Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    if(player.level==3 && magnet.timer<1000)
        magnet.draw(VP);
    player.draw(VP);
    for(int i=0;i<n;i++)
    {
        if(ball[i].status)
            ball[i].draw(VP);
    }
    for(int i=0;i<10;i++)
    {
        if(slopeball[i].status)
            slopeball[i].draw(VP);
    }
    grass.draw(VP);
    soil1.draw(VP);
    soil2.draw(VP);
    pond.draw(VP);
    if(player.level>=2)
    {
        trampoline.draw(VP);
        porcupine.draw(VP);
    }
    digit[0]=Digit(3+screen_center_x,5+screen_center_y-0.8,(int)player.score % 10);
    digit[1]=Digit(2.5+screen_center_x,5+screen_center_y-0.8,((int)player.score /10) % 10);
    digit[2]=Digit(0+screen_center_x,5+screen_center_y-0.8,player.lives);
    digit[3]=Digit(1.5+screen_center_x,5+screen_center_y-0.8,player.level);
    for(int i=0;i<4;i++)
        digit[i].draw(VP);
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    if (left) {
        // Do something
        player.position.x-=0.03;
        player.rotation+=10;
    }
    if(right) {
        // Do something
        player.position.x+=0.03;
        player.rotation-=10;
    }
    if(up && fabs(player.position.x)>=1)
    {
        if(player.position.y<= -0.4)
            player.speedy=0.15;
        if(player.speedy!=0)
        {
            player.accerlation=0.005;
        }
    }

}
void tick_input_water(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    if (left) {
        // Do something
        player.position.x-=0.03;
        player.rotation+=10;
    }
    if(right) {
        // Do something
        player.position.x+=0.03;
        player.rotation-=10;
    }
    if(up)
    {
        if(/*player.position.y<= -1.399 && */player.speedy==0)
            player.speedy=0.15;
        if(player.speedy!=0)
        {
            player.accerlation=0.006;
        }
    }

}

void tick_elements() {
    if(player.score>25)
        player.level=3;
    else if(player.score>12)
        player.level=2;

    for(int i=0;i<10;i++)
    {
        slopeball[i].tick();
    }
    for(int i=0;i<n;i++)
    {
        ball[i].tick();
    }
    magnet.tick();
    for(int i=0;i<10;i++)
        if (slopeball[i].status && player.detect_collision_reflection(slopeball[i]))
        {
            slopeball[i].status=false;//ball is destroyed
            //player.speedy=0.15;
            double temp=player.score;
            player.score+= (0.3-slopeball[i].r)*10.0 ;
            if(player.score>35 && temp<=35)
            {
                player.level=4;
                magnet.timer=0;
            }
            if(player.score>45 && temp<=45)
            {
                player.level=5;
                magnet.timer=0;
            }
            //printf("score is %lf\n",player.score);
            //PlaySound("starwars.wav", NULL, SND_ASYNC|SND_FILENAME);
            //printf("collision happened\n");

        }

    for(int i=0;i<n;i++)
        if (ball[i].status /*&& (ball[i].slope==2) */&& player.detect_collision(ball[i]))
        {
            ball[i].status=false;//ball is destroyed
            player.speedy=0.15;
            double temp=player.score;
            player.score+= (0.3-ball[i].r)*10.0 ;
            if(player.score>35 && temp<=35)
            {
                player.level=4;
                magnet.timer=0;
            }
            if(player.score>45 && temp<=45)
            {
                player.level=5;
                magnet.timer=0;
            }
            //printf("ball radius is %lf\n",player.score);
            //PlaySound("starwars.wav", NULL, SND_ASYNC|SND_FILENAME);
            //printf("collision happened\n");

        }
    if(player.level>=2)
    {
        porcupine.tick(player);
        if(trampoline.detect_collision(player))
        {
            player.speedy=0.2;
            player.accerlation=0.005;
        }

        if(porcupine.detect_collision(player))
        {
            player.set_position(-1.5,-0.4);
            player.speedx=0;
            player.lives-=1;
            if(!player.lives)
                quit(window);
            porcupine.set_position(-3,-0.6);
        //player.speedy=0.1;
        }
    }
    if(player.level>=3&&magnet.timer<1000&&magnet.detect_collision(player))
    {
        if(magnet.dir==0)//magnet in the left side
            player.speedx=-0.1;
        else
            player.speedx=0.1;
    }
    if(!pond.detect_collision(player))
    {
        player.tick(window);
        tick_input(window);
    }
    else
    {
        player.tick_water();
        tick_input_water(window);
    }
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    for(int i=0;i<n;i++)
    {
        ball[i]       = Ball(-4.2, rand()%5 , COLOR_YELLOW);
        ball[i].speed = -double(rand()%5)/100.0;
        while(!ball[i].speed)
            ball[i].speed = -double(rand()%5)/100.0;
    }
    for(int i=0;i<10;i++)
    {
        slopeball[i]       = Slopeball(-4.2, rand()%5 , COLOR_YELLOW);
        slopeball[i].speed = -double(rand()%5)/100.0;
        while(!slopeball[i].speed)
            slopeball[i].speed = -double(rand()%5)/100.0;
    }
    grass=Ground(0.0,-1.1,COLOR_GREEN);
    soil1=Ground(0.0,-1.8,COLOR_BROWN);
    soil2=Ground(0.0,-2.8,COLOR_BROWN);
    player=Player(-1.5,-0.4,COLOR_RED);
    player.score=0.0;
    pond=Pond(0,-0.6,COLOR_POND);
    trampoline=Trampoline(2,0.4,COLOR_RED);
    porcupine=Porcupine(-3,-0.6,COLOR_POND);
    magnet=Magnet(-2,3);
    if(magnet.dir)
        magnet.set_position(2,3);

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 700;
    int height = 700;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            reshapeWindow (window, width, height);
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            //tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}


void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
