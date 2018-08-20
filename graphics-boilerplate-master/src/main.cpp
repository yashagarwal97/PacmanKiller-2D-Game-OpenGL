#include "main.h"
#include "timer.h"
#include "ball.h"
#include "magnet.h"
#include "ground.h"
#include "pond.h"
#include "plank.h"
#include "porcupine.h"
#include "trampoline.h"
#include<stdlib.h>
#include <time.h>
#include<math.h>
#include<string.h>
using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Ball ball[1000];
Ground ground[10];
Pond pond[10];
Porcupine porcupine[10];
int num_por=0;
Plank plank[100];
Trampoline trampoline[10];
Magnet magnet[10];
int magnet_frame=0;
int plank_flag=0;
//int magnet_flag=0;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
int flag[100];



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
    ground[1].draw(VP);
    ground[2].draw(VP);
    ground[3].draw(VP);
    ground[0].draw(VP);
    trampoline[0].draw(VP);
    for(int i=0;i<num_por;i++)
    {
        if(porcupine[i].position.x>=-4.2)
    porcupine[i].draw(VP);
    }
    pond[0].draw(VP);
    for(int i=1;i<20;i++)
    {
       if(ball[i].position.x>=-3.5 && ball[i].position.x<=3.5)
       {
           ball[i].draw(VP);
       if(flag[i]==1)
       {
           plank[i].draw(VP);
       }
       }

    }

    if(magnet_frame>=800 && magnet_frame<=1100)
    {
        magnet[0].magnet_flag=1;
        magnet[0].draw(VP);
        magnet[1].draw(VP);
    }
    else if(magnet_frame>1100)
    {
        magnet[0].magnet_flag=0;
        magnet_frame=0;
    }

}

void move_left()
{
    float a=ball[1].position.x;
    float b=ball[1].position.y;
    float r=1.5-0.5;

    //for moving along the semicircle
    if(r*r>=a*a)
    {
    b=(-2-sqrt(r*r-a*a));
    //printf("%lf %lf\n",b,ball[1].position.y);
    if(a>=-0.98 && a<=0.98 && ball[1].position.y<=b)
    {
        ball[1].position.x-=0.02;
        a = ball[1].position.x;
        ball[1].position.y = (-2-sqrt(r*r-a*a));
    }
    else if(a>=-0.98 && a<=0.98 && ball[1].position.y>b && ball[1].position.y<=-1.5)
    {
        ball[1].position.x-=0.02;
    }

    else
        ball[1].set_position(a-0.05,ball[1].position.y);         //normally
        //}
    }

    else
        ball[1].set_position(a-0.05,ball[1].position.y);         //normally
}

void move_right()
{
    float a=ball[1].position.x;
    float b=ball[1].position.y;
    float r=1.5-0.5;

    //ball1.position+=1;
    if(r*r>=a*a)
    {
    b=(-2-sqrt(r*r-a*a));


    if(a>=-0.98 && a<=0.98 && ball[1].position.y<=b)
    {
        ball[1].position.x+=0.02;
        a = ball[1].position.x;
        ball[1].position.y = (-2-sqrt(r*r-a*a));
    }
    else if(a>=-0.98 && a<=0.98 && ball[1].position.y>b && ball[1].position.y<=-1.5)
    {
        ball[1].position.x+=0.02;
    }
        //}

    else
        ball[1].set_position(a+0.05,ball[1].position.y);         //normally
    }
    else
        ball[1].set_position(a+0.05,ball[1].position.y);
}


void tick_input(GLFWwindow *window) {
    int pan_left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int pan_right  = glfwGetKey(window, GLFW_KEY_RIGHT);
    int pan_up  = glfwGetKey(window, GLFW_KEY_UP);
    int left  = glfwGetKey(window, GLFW_KEY_A);
    int right = glfwGetKey(window, GLFW_KEY_D);
    int up = glfwGetKey(window, GLFW_KEY_SPACE);
    int pan_down = glfwGetKey(window, GLFW_KEY_DOWN);
    float r=1.5-0.5;
    if (left) {
        float a=ball[1].position.x;
        float b=ball[1].position.y;
        //for moving along the semicircle
        if(r*r>=a*a)
        {
        b=(-2-sqrt(r*r-a*a));
        //printf("%lf %lf\n",b,ball[1].position.y);
        if(a>=-0.98 && a<=0.98 && ball[1].position.y<=b)
        {
            ball[1].position.x-=0.02;
            a = ball[1].position.x;
            ball[1].position.y = (-2-sqrt(r*r-a*a));
        }
        else if(a>=-0.98 && a<=0.98 && ball[1].position.y>b && ball[1].position.y<=-1.5)
        {
            ball[1].position.x-=0.02;
        }

        else
            ball[1].set_position(a-0.05,ball[1].position.y);         //normally
            //}
        }

        else
            ball[1].set_position(a-0.05,ball[1].position.y);         //normally
        //ball1.rotation+=1;
        // Do something
    }
    else if(right) {
        float a=ball[1].position.x;
        float b=ball[1].position.y;
        //ball1.position+=1;
        if(r*r>=a*a)
        {
        b=(-2-sqrt(r*r-a*a));


        if(a>=-0.98 && a<=0.98 && ball[1].position.y<=b)
        {
            ball[1].position.x+=0.02;
            a = ball[1].position.x;
            ball[1].position.y = (-2-sqrt(r*r-a*a));
        }
        else if(a>=-0.98 && a<=0.98 && ball[1].position.y>b && ball[1].position.y<=-1.5)
        {
            ball[1].position.x+=0.02;
        }
            //}

        else
            ball[1].set_position(a+0.05,ball[1].position.y);         //normally
        }
        else
            ball[1].set_position(a+0.05,ball[1].position.y);
    }
    else if(up) {
        //float x=ball1.position.x;
        //float y=ball1.position.y;
        //ball1.set_position(x,y+0.1);
        if(ball[1].position.y <= -1.5)
            ball[1].speed2 = 0.2;
    }
    else if(pan_left) {
        if(screen_center_x>-1.3)
        screen_center_x-=0.1;
        reset_screen();
    }
    else if(pan_right) {
        if(screen_center_x<1.3)
        screen_center_x+=0.1;
        reset_screen();
    }
    else if(pan_up) {
        if(screen_center_y<1.3)
        screen_center_y+=0.1;
        reset_screen();
    }
    else if(pan_down) {
        if(screen_center_y>-1.3)
        screen_center_y-=0.1;
        reset_screen();
    }

}

void tick_elements() {
    ball[1].tick1(magnet[0].magnet_flag);
    float a,b,rad_pond=1.5,r;
    r=rad_pond-0.5;
    for(int i=0;i<num_por;i++)
    {
    porcupine[i].tick();
    a=porcupine[i].position.x;
    b=porcupine[i].position.y;
    //printf("%lf %lf\n",a,b);
    if(ball[1].position.x<=(a+1.25) && ball[1].position.x>=(a-0.25) && ball[1].position.y>=b && ball[1].position.y<=(b+0.43+0.5))
    {
        ball[1].lives--;    // add penalty on player
        if(ball[1].lives==0)
            quit(window);
        porcupine[i].position.x = -7.5;   //regenerate porcupine[i]
        porcupine[i].speed=0.01;
    }
    }

    a = ball[1].position.x;
    b = ball[1].position.y;
    //printf("%lf %lf\n",ball[1].position.x,ball[1].position.y);

    if(a<=(-rad_pond+0.5+0.06) && a>=(-rad_pond+0.5-0.06) && b==1.5)
    {
       // printf("If \n");
        ball[1].position.x= -1;
        ball[1].position.y= -2;
    }
    else if(a<=(rad_pond-0.5+0.06) && a>=(rad_pond-0.5-0.06) && b==1.5)
    {
       // printf("If \n");
        ball[1].position.x= 1;
        ball[1].position.y= -2;
    }

    //printf("%lf %lf\n",b,ball[1].position.y);
//    if(b>=ball[1].position.y-0.01 && b<=ball[1].position.y+0.01)
      if(a>=-0.98 && a<=0.98 && ball[1].position.y<=(-2-sqrt(r*r-a*a)))
    {
        //printf("YESHHH\n");
        if(!(ball[1].position.x>=-0.01 && ball[1].position.x<=0.01))
        {
        if(ball[1].position.x<0)
        {
         //   printf("YESHHH 1\n");
        ball[1].position.x+=0.01;
        a = ball[1].position.x;
        ball[1].position.y = (-2-sqrt(r*r-a*a));
        //printf("%lf %lf\n",ball[1].position.x,ball[1].position.y);
        }
        else if(ball[1].position.x>0)
        {
          //  printf("YESHHH 2\n");
        ball[1].position.x-=0.01;
        a = ball[1].position.x;
        ball[1].position.y = (-2-sqrt(r*r-a*a));
        }
        }
        else
        {
            ball[1].position.x=0;
            ball[1].position.y = -3;
        }

    }
    //else
      //  printf("NO\n");




    for(int i=2;i<20;i++)
    {
        ball[i].tick();
        if(flag[i]==1)
        {
        plank[i].tick();
        if (ball[1].speed2 < 0 && detect_collision(ball[1].bounding_box(), plank[i].bounding_box())) {
        ball[1].speed2 = -ball[1].speed2;
        ball[1].speed = -0.1;
        plank_flag=1;
        }
        }

        if (ball[1].speed2 < 0 && detect_collision(ball[1].bounding_box(), ball[i].bounding_box())) {
            ball[1].score+=50;
            if(plank_flag==1)
            {
                ball[1].speed=0;
                plank_flag=0;
            }
            if(ball[1].score%1000==0)
            {
                ball[1].level++;
                for(int ii=2;ii<20;ii++)
                {
                    if(ball[ii].speed<0.3)
                    {
                    ball[ii].speed+=0.05;
                    if(flag[ii]==1)
                    plank[ii].speed+=0.05;
                    }
                }
                printf("%lf\n",ball[2].speed);


            }
            ball[i].position.x = -5;
            if(flag[i]==1)
            plank[i].position.x = -5;
            ball[1].speed2 = 0.2;
        }
      //  ball[1].speed = 0;
        //ball[2].speed = 0;
        // ball1.speed = -ball1.speed;
       // ball2.speed = -ball2.speed;
    }
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    ball[1].speed = 0;
    ball[1].speed2 = 0;
    flag[2]=1;
    flag[5]=1;
    flag[10]=1;
    flag[13]=1;
    flag[18]=1;
    ground[0] = Ground(0, -2, COLOR_BROWN);
    ground[2] = Ground(0, -1.5, COLOR_BROWN);
    ground[3] = Ground(0, -1, COLOR_BROWN);
    ground[1] = Ground(0, -0.5, COLOR_GREEN);
    ball[1] = Ball(0, -1.5,0.5, COLOR_RED);
    pond[0] = Pond(0, -2, COLOR_BLUE);
    trampoline[0] = Trampoline(2, -1.35, COLOR_RED);
    magnet[0] = Magnet(-3.4, 2,0.6, COLOR_RED);
    magnet[1] = Magnet(-3.4, 2,0.3, COLOR_BACKGROUND);
    porcupine[num_por++] = Porcupine(-3, -2, COLOR_BLUE);

    for(int i=2;i<20;i++)
    {
    double i2,i1,i3,i4;
    float i5,i6;
    i1 = (rand() % 100 - 50)*0.08;
    i2 = (rand() % 100 )*0.04;

    i3 = (rand() % 4 + 1);
    i5 = (rand() % 30)*0.01 + 0.3;
    i6 = (rand() % 5 -2)*7.5;

    if(i3==1)
    {
        ball[i] = Ball(i1, i2,i5, COLOR_YELLOW);
        if(flag[i]==1)
        {
            plank[i] = Plank(i1, i2+i5,i5,i6, COLOR_BROWN);

        }
    }
    else if(i3==2)
    {
    ball[i] = Ball(i1, i2,i5, COLOR_VIOLET);
    if(flag[i]==1)
    {
        plank[i] = Plank(i1, i2+i5,i5,i6, COLOR_BROWN);

    }
    }
    else if(i3==3)
    {
        ball[i] = Ball(i1, i2,i5, COLOR_ORANGE);
        if(flag[i]==1)
        {
            plank[i] = Plank(i1, i2+i5,i5,i6, COLOR_BROWN);

        }
    }
    else if(i3==4)
    {
        ball[i] = Ball(i1, i2,i5, COLOR_DBLUE);
        if(flag[i]==1)
        {
            plank[i] = Plank(i1, i2+i5,i5,i6, COLOR_BROWN);

        }
    }
    i4 = (rand() % 50 + 1)*0.001;
    //i4 = 0.01;
    ball[i].speed = i4;
    if(flag[i]==1)
        plank[i].speed = i4;

    ball[i].speed2 = 0;
    //ball[1].speed = 0;
    }

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
    int width  = 600;
    int height = 600;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            magnet_frame++;
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);
            char s1[30],s2[30],s3[30];
            char output[300]="";
              sprintf(s1,"%d",ball[1].score);
              sprintf(s2,"%d",ball[1].lives);
              sprintf(s3,"%d",ball[1].level);
              strcat(output,"Score: ");
              strcat(output,s1);
              strcat(output,"   Lives: ");
              strcat(output,s2);
              strcat(output,"   Level: ");
              strcat(output,s3);
glfwSetWindowTitle(window,output);


            tick_elements();
            tick_input(window);

        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void zoom_screen(int x) {
    if(x==1 && screen_zoom<2)
        screen_zoom+=0.1;
    else if(x==-1 && screen_zoom>1)
        screen_zoom-=0.1;
    reset_screen();
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
