#include "porcupine.h"
#include "main.h"

Porcupine::Porcupine(float x,float y,color_t color) {
    this->position = glm::vec3(x, y, 0);
    speed = 0.01;
    static const GLfloat vertex_buffer_data[] = {
        0, 0.43, 0, // vertex 1
        -0.25, 0, 0, // vertex 2
        0.25, 0, 0, // vertex 3

        0.25, 0, 0, // vertex 3
        0.75, 0, 0, // vertex 4
        0.5, 0.43, 0, // vertex 1

        1, 0.43, 0, // vertex 1
        1.25, 0, 0, // vertex 2
        0.75, 0, 0, // vertex 3

    };

    this->object = create3DObject(GL_TRIANGLES, 9, vertex_buffer_data, color, GL_FILL);
}

void Porcupine::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Porcupine::tick() {
    this->position.x += speed;
    if(this->position.x >= -2.25)
        speed=-speed;
    if(this->position.x <= -5.5 && speed<0)
        speed=-speed;
}
