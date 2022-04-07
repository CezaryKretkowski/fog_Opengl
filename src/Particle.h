//
// Created by cezar on 03.04.2022.
//

#ifndef UNTITLED3_PARTICLE_H
#define UNTITLED3_PARTICLE_H
#include "Clouds.h"
#include "DirectionStrategy.h"
float F_RAND(float LO, float HI);

enum Mode {
    POINT = 0,
    LINE = 1,
    SQUARE = 2,
    CUBE = 3
};


class Particle : public Clouds{
    /* data */
    bool active;
    float life;
    int mode;
    glm::vec3 pos;
    glm::vec3 externals;
    glm::vec3 gravity;
    DirectionStrategy *strategy= NULL;

    glm::vec3 emitterPosition;
    glm::vec3 emitterDimensions;

    glm::vec3 calculatePosition();

public:

    float fade;
    float speed;
    glm::vec3 color;
    glm::vec3 direction;

    Particle(int mode = 0);

    virtual ~Particle();

    void activate();

    void live(float tt);

    bool isActive() { return active; }

    float getLive() { return life; }

    void setDirectionStrategy(DirectionStrategy *strategy) { this->strategy = strategy; }


    glm::vec3 getPos() { return pos; }

    glm::vec3 getGravity() { return gravity; }

    glm::vec3 getExternals() { return externals; }

    glm::vec3 getDimension() { return gravity; }

    glm::vec3 getEmitterPosition() { return gravity; }

    void setGravity(glm::vec3 gravity) { this->gravity = gravity; }

    void setDimension(glm::vec3 dimension) { this->emitterDimensions = dimension; }

    void setEmitterPosition(glm::vec3 emitterPos);

    void setMode(int mode) { this->mode = mode; }
    void setExternal(glm::vec3 external) { this->externals = external; }
};
#endif //UNTITLED3_PARTICLE_H
