#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y,float r, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    int tick1(int f);
    double speed;
    double speed2;
    int score;
    int lives;
    int level;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // BALL_H
