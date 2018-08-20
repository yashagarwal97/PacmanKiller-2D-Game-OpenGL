#include "ball.h"
#include "main.h"

Ball::Ball(float x, float y,float r, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->score=0;
    this->lives=3;
    this->level=1;
    speed = 0.25;
    speed2 = 0;
    /*
    static const GLfloat vertex_buffer_data[] = {
        -0.2, -0.2, 0, // vertex 1
        0.2,  -0.2, 0, // vertex 2
        0.2,  0.2, 0, // vertex 3

        0.2,  0.2, 0, // vertex 3
        -0.2, 0.2, 0, // vertex 4
        -0.2, -0.2, 0 // vertex 1
    };
    */
    static GLfloat vertex_buffer_data[9000000];
       int n=10000,top=0;
       for(int i=0;i<n;i++)
       {
           vertex_buffer_data[top++]=r*cos((2*3.1416/n)*i);
           vertex_buffer_data[top++]=r*sin((2*3.1416/n)*i);
           vertex_buffer_data[top++]=0;

           vertex_buffer_data[top++]=r*cos((2*3.1416/n)*(i+1));
           vertex_buffer_data[top++]=r*sin((2*3.1416/n)*(i+1));
           vertex_buffer_data[top++]=0;

           vertex_buffer_data[top++]=0;
           vertex_buffer_data[top++]=0;
           vertex_buffer_data[top++]=0;

       }


    this->object = create3DObject(GL_TRIANGLES, 3*n, vertex_buffer_data, color, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball::tick() {
    this->position.x += speed;
    this->position.y += speed2;
    if(this->position.x >= 7.5)
        this->position.x = -10;

    if(this->position.y >= 3.5 || this->position.y <= -3.5 )
        speed2 = -speed2;
}

// jump function
int Ball::tick1(int f) {
    this->position.x += speed;
    this->position.y += speed2;
    //printf("%lf %lf\n",this->position.x,this->position.y);
    /*if(this->position.x>=(a+1.25) && this->position.x<=(a-0.25)+ && this->position.y>=b && this->position.y<=(b+0.43))
    {
        // give a penalty to the player
        // regenerate the porcupine

    }*/

    if(f==1)    //magnet flag
    {
         speed -= 0.0001;
    }
    else
    {
        speed=0;
    }

    if(speed2<=0 && this->position.y <= -0.85 && this->position.x>=1.5 && this->position.x<=2.5)
    {
        speed2 = 0.4;
    }
    if(this->position.x >= 3.5)
        this->position.x = 3.5;
    else if(this->position.x <= -3.5 )
        this->position.x = -3.5;

    //float r=1.5-0.5;
   // float a = this->position.x;
    //float b=(-2-sqrt(r*r-a*a));
    if(this->position.y > 3.5){
        speed2 = 0;
        this->position.y= 3.5;
    }

    //    if(a<=(-rad_pond+0.5+0.06) && a>=(-rad_pond+0.5-0.06) && b==-1.5)
    if(this->position.y <= -1.5)
    {
        if(this->position.x<=-0.99 && this->position.x>=-1.01)
        {
        speed2 = 0;
        }
        else if(this->position.x>=0.99 && this->position.x<=1.01)
        {
        speed2 = 0;
        }
        else if(this->position.x<(-1.01) || this->position.x>1.01)
        {
            speed2 = 0;
            this->position.y= -1.5;
        }
        else    //middle of pond
        {
         speed2=-0.01;

         if(this->position.x>=-0.02 && this->position.x<=0.02 && this->position.y<=-3)
         {
             speed2=0;
             this->position.y=-3;
             this->position.x=0;
         }
        }

    }

    else
    {
        speed2 -= 0.01; //gravity

    }

//printf("%lf %lf\n",this->position.y,speed2);

}

bounding_box_t Ball::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.4, 0.4 };
    return bbox;
}
