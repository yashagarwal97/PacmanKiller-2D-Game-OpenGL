#include "trampoline.h"
#include "main.h"

Trampoline::Trampoline(float x,float y,color_t color) {
    this->position = glm::vec3(x, y, 0);

    static const GLfloat g_vertex_buffer_data[] = {
        -0.65, 0, 0, // vertex 1
        -0.5, 0, 0, // vertex 2
        -0.5, -0.65, 0, // vertex 3

        -0.65, 0, 0, // vertex 3
        -0.5, -0.65, 0, // vertex 4
        -0.65, -0.65, 0, // vertex 1

        0.65, -0.65, 0, // vertex 1
        0.5, 0, 0, // vertex 2
        0.5, -0.65, 0, // vertex 3

        0.5, 0, 0, // vertex 3
        0.65, 0, 0, // vertex 4
        0.65, -0.65, 0 // vertex 1
    };

    static GLfloat vertex_buffer_data[9000000];
       int n=10000,top=0;
       for(int i=0;i<n;i++)
       {
           vertex_buffer_data[top++]=0.5*cos(3.1416+(3.1416/n)*i);
           vertex_buffer_data[top++]=0.5*sin(3.1416+(3.1416/n)*i);
           vertex_buffer_data[top++]=0;

           vertex_buffer_data[top++]=0.5*cos(3.1416+(3.1416/n)*(i+1));
           vertex_buffer_data[top++]=0.5*sin(3.1416+(3.1416/n)*(i+1));
           vertex_buffer_data[top++]=0;

           vertex_buffer_data[top++]=0;
           vertex_buffer_data[top++]=0;
           vertex_buffer_data[top++]=0;

       }

    this->object = create3DObject(GL_TRIANGLES, 12, g_vertex_buffer_data, color, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 3*n, vertex_buffer_data, color, GL_FILL);
}

void Trampoline::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object2);

}
