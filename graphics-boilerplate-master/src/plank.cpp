#include "plank.h"
#include "main.h"

Plank::Plank(float x, float y,float r,float rot, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 15;
    speed = 0.1;
    speed2 = 0;
    // r = radius of ball under the plank
   GLfloat vertex_buffer_data[] = {
        -1.5*r, 0.5*r, 0, // vertex 1
        -1.5*r,  0, 0, // vertex 2
        1.5*r,  0.5*r, 0, // vertex 3

        1.5*r,  0.5*r, 0, // vertex 3
        -1.5*r, 0, 0, // vertex 4
        1.5*r, 0, 0 // vertex 1
    };
/*
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
*/

    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);
}

void Plank::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Plank::tick() {
    this->position.x += speed;
    this->position.y += speed2;
    if(this->position.x >= 7.5) //4.5
        this->position.x = -10; //-5

    if(this->position.y >= 3.5 || this->position.y <= -3.5 )
        speed2 = -speed2;
}

bounding_box_t Plank::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.4, 0.4 };
    return bbox;
}
