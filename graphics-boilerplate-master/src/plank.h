#include "main.h"

#ifndef PLANK_H
#define PLANK_H


class Plank {
public:
    Plank() {}
    Plank(float x, float y,float r, float rot, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    void tick1(int f);
    double speed;
    double speed2;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // PLANK_H
