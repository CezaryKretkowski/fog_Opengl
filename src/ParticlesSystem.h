//
// Created by cezar on 30.03.2022.
//

#ifndef UNTITLED3_PARTICLESSYSTEM_H
#define UNTITLED3_PARTICLESSYSTEM_H

#include "dependeces/Common/Initialize.h"
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>
#include <algorithm>
#include "resource/squere.h"
#include "Particle.h"
#include "DirectionStrategy.h"
struct Node{
    int id;
    float distance;
};
bool operator <(const  Node & v,const  Node & w){
    return v.distance>w.distance;
}
class FogEffect : public DirectionStrategy {
    ~FogEffect(){}
    glm::vec3 calculateDirection() override {
        float fi = 3.14f / 4; // 45 stopni w górę
        float psi = F_RAND(0.0f, 1.0f) * (3.14f * 2); // 0-360 stopni wokół osi Y
        float rr = F_RAND(0.0f, 1.0f) * 12 + 16;
        glm::vec3 direction(rr * cos(fi) * cos(psi), rr * sin(fi), rr * cos(fi) * sin(psi));
        return direction;
    }
};

class ParticlesSystem {
    GLuint core0;
    GLuint core1;
    int MAX_PART = 1000;
    Particle particles[1000];
    float ACTIVATE_TIME = 0.00001f;
    float act_time = 0.0f;
    float lastTime;
    RenderableObject cube;
    std::vector<Node>particlesList;
    std::vector<glm::vec3> zero;
    GLuint MatrixID;
    GLuint ViewMatrixID;
    GLuint ModelMatrixID;
    GLuint LightID;

    void sortParticles(){
        particlesList.clear();
        for(int i=0;i<MAX_PART;i++){
            Node p;
            vec3 w1=particles[i].getPos();
            vec3 w2=getPosition();
            p.id=i;
            p.distance= abs(glm::length2(w1-w2));
            particlesList.push_back(p);
        }
        std::sort(particlesList.begin(),particlesList.end());

    }
public:
    void setUp(GLFWwindow *window) {
        glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
        glEnable(GL_DEPTH_TEST);
       glDepthFunc(GL_LESS);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        core0 = LoadShaders("shaders/verShader.glsl", "shaders/fragShaders.glsl");
        core1 = LoadShaders("shaders/StandardShading.vertexshader", "shaders/StandardShading.fragmentshader");
        MatrixID = glGetUniformLocation(core1, "MVP");
        ViewMatrixID = glGetUniformLocation(core1, "V");
        ModelMatrixID = glGetUniformLocation(core1, "M");
        LightID = glGetUniformLocation(core1, "LightPosition_worldspace");

        glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        cube.intFromFile("resource/cube.obj",core1,"resource/uvmap.png","myTextureSampler");

        computeMatricesFromInputs(window);
        GLuint out[] = {NULL, NULL};
        FogEffect *startegy = new FogEffect();
        LoadTexture(core0, "resource/ParticleCloudWhite.png", "text", out);
        sortParticles();

        for (int  i=0; i<MAX_PART; i++) {
            particles[i].initFromArrary(vert, zero, uv);
            particles[i].setMode(CUBE);
            particles[i].setEmitterPosition(glm::vec3(-1.0f,0.0f,0.0f));
            particles[i].setDimension(glm::vec3(3.0f, 3.0f, 3.0f));
            particles[i].initAtribiuts(core0);
            particles[i].speed = 500;
            particles[i].setTexture(out[0], out[1]);
            particles[i].setDirectionStrategy(startegy);

        }
    }

    void update(GLFWwindow *window) {
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        computeMatricesFromInputs(window);
        glUseProgram(0);
        glUseProgram(core1);

        glm::vec3 lightPos1 = glm::vec3(-4, 4, -4);
        glUniform3f(LightID, lightPos1.x, lightPos1.y, lightPos1.z);
        cube.setProjectionMatrix(getProjectionMatrix());
        cube.setViewMatrix(getViewMatrix());
        cube.draw(MatrixID,ViewMatrixID,ModelMatrixID);
        glUseProgram(0);
        glUseProgram(core0);


        int i = 0;
        float nowTime = glfwGetTime();
        float times = (nowTime - lastTime);
        act_time += times;

        while (i < MAX_PART) {//(int i = 0; i < MAX_PART; i++) {

            if (particles[i].isActive()) {
                particles[i].live(times);
            } else {
                if (act_time >= ACTIVATE_TIME) {
                    act_time = 0.0f;
                    particles[i].activate();
                }
            }
            i++;
        }

        sortParticles();
        for (std::vector<Node>::iterator i = particlesList.begin() ; i<particlesList.end(); i++) {

            particles[i->id].setAlpha(particles[i->id].getLive());
            particles[i->id].setModelMatrix(glm::mat4(1));
            particles[i->id].translate(particles[i->id].getPos());
            particles[i->id].setViewMatrix(getViewMatrix());
            //printf("%f  %f  %f\n",particles[i].getPos()[0],particles[i->id].getPos()[1],particles[i->id].getPos()[2]);
            particles[i->id].setProjectionMatrix(getProjectionMatrix());
            particles[i->id].draw();

        }

        lastTime = nowTime;
    }

    void clean(GLFWwindow *window) {
        glDeleteProgram(core1);
        glDeleteProgram(core0);

    }
};

#endif //UNTITLED3_PARTICLESSYSTEM_H
