#include "magnet.h"
#include "main.h"

Magnet::Magnet(float x,float y,float r,color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->magnet_flag=0;
/*
    static const GLfloat vertex_buffer_data[] = {
        -4, -1.5, 0, // vertex 1
        -4, -2, 0, // vertex 2
        4, -2, 0, // vertex 3

        4, -2, 0, // vertex 3
        4, -1.5, 0, // vertex 4
        -4, -1.5, 0 // vertex 1
    };
*/
    static GLfloat vertex_buffer_data[9000000];
       int n=10000,top=0;
       for(int i=0;i<n;i++)
       {
           vertex_buffer_data[top++]=r*cos(4.7124/3+(3.1416/n)*i);
           vertex_buffer_data[top++]=r*sin(4.7124/3+(3.1416/n)*i);
           vertex_buffer_data[top++]=0;

           vertex_buffer_data[top++]=r*cos(4.7124/3+(3.1416/n)*(i+1));
           vertex_buffer_data[top++]=r*sin(4.7124/3+(3.1416/n)*(i+1));
           vertex_buffer_data[top++]=0;

           vertex_buffer_data[top++]=0;
           vertex_buffer_data[top++]=0;
           vertex_buffer_data[top++]=0;

       }


    this->object = create3DObject(GL_TRIANGLES, 3*n, vertex_buffer_data, color, GL_FILL);
}

void Magnet::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}
