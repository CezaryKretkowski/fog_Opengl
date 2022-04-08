#include "Particle.h"
#include <math.h>
#include <cstdlib>
#include <ctime>
float F_RAND(float LO,float HI){
    if(LO>HI) {
        float tmp = HI;
        HI=LO;
        LO=tmp;
    }
    //srand (static_cast <unsigned> (time(0)));
    float out=LO + static_cast <float> (std::rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
    return out;
}
void Particle::setEmitterPosition(glm::vec3 emitterPos) {
    this->emitterPosition =emitterPos;
}

Particle::Particle(int mode) {
    emitterPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    emitterDimensions = glm::vec3(0.0f, 0.0f, 0.0f);
    color = glm::vec4(1.0f, 0.0f, 1.0f,1.0f);
    active = false;
    speed=50.0f;
    externals=glm::vec3(0.0f, 0.0f, 0.0f);
    gravity = glm::vec3(0.0f, -10.0f, 0.0f);
}

void Particle::activate() {

    active = true;
    life = 1.0f;
    if(strategy!=NULL)
        direction =strategy->calculateDirection();
    else
        direction=gravity;
    fade = 0.0005f + F_RAND(0.0f,1.0f) * 0.4f;
    pos = calculatePosition();
}

void Particle::live(float tt) {
    pos += direction * (tt/speed);
    direction += gravity*(tt/speed);
    direction += externals*(tt/speed);
    life -= fade * tt/fadeTime;
    if (life <= 0.0f) {

        activate();

    }
}

glm::vec3 Particle::calculatePosition() {
    glm::vec3 out = emitterPosition;

    if(mode==POINT)
        out=emitterPosition;
    if(mode==LINE)
        out=glm::vec3 (F_RAND(emitterPosition[0],emitterDimensions[0]),emitterPosition[1],emitterPosition[2]);
    if(mode==SQUARE)
        out=glm::vec3 (F_RAND(emitterPosition[0],emitterDimensions[0]),emitterPosition[1],F_RAND(emitterPosition[2],emitterDimensions[2]));
    if(mode==CUBE)
        out=glm::vec3 (F_RAND(emitterPosition[0],emitterDimensions[0]),F_RAND(emitterPosition[1],emitterDimensions[1]),
                       F_RAND(emitterPosition[2],emitterDimensions[2]));
    return out;
}

Particle::~Particle() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vertexBuff);
    glDeleteBuffers(1, &uvBuff);
    glDeleteBuffers(1, &normalBuff);
    glDeleteBuffers(1,&colorBuffer);

}
void Particle::draw(){
    glBindVertexArray(vao);
    glUniform1i(textureID,0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glUniformMatrix4fv(Pid,1,GL_FALSE,&projectionMatrix[0][0]);
    glUniformMatrix4fv(Vid,1,GL_FALSE,&viewMatrix[0][0]);
    glUniformMatrix4fv(Mid,1,GL_FALSE,&modelMatrix[0][0]);
    glUniform1f(alphaid,alhpa);
    glUniform3f(particlePosID,pos.x,pos.y,pos.z);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}

