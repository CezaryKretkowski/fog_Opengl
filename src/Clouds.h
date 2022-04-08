//
// Created by Lothar on 30.03.2022.
//

#ifndef UNTITLED3_CLOUDS_H
#define UNTITLED3_CLOUDS_H
#include "Common/RenderableObject.h"

class Clouds :public RenderableObject{
protected:
    GLuint colorBuffer;
    GLuint Pid;
    GLuint Vid;
    GLuint Mid;
    GLuint alphaid;
    GLuint particlePosID;
    float alhpa=1.0;
    float color[4] = {1.0f,1.0f,1.0f,1.0};


   void initBuffers()override{
       glGenVertexArrays(1,&vao);
       glBindVertexArray(vao);

       glGenBuffers(1,&vertexBuff);
       glBindBuffer(GL_ARRAY_BUFFER,vertexBuff);
       glBufferData(GL_ARRAY_BUFFER,vertices.size() * sizeof(glm::vec3), &vertices[0],GL_STATIC_DRAW);

       glGenBuffers(1,&colorBuffer);
       glBindBuffer(GL_ARRAY_BUFFER,colorBuffer);
       glBufferData(GL_ARRAY_BUFFER,sizeof (color),color,GL_STATIC_DRAW);

       glGenBuffers(1,&uvBuff);
       glBindBuffer(GL_ARRAY_BUFFER,uvBuff);
       glBufferData(GL_ARRAY_BUFFER,uvs.size() * sizeof(glm::vec2), &uvs[0],GL_STATIC_DRAW);



       glEnableVertexAttribArray(0);
       glBindBuffer(GL_ARRAY_BUFFER,vertexBuff);
       glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*) 0);

       glEnableVertexAttribArray(1);
       glBindBuffer(GL_ARRAY_BUFFER,colorBuffer);
       glVertexAttribPointer(1,4,GL_FLOAT,GL_FALSE,0,(void*) 0);


       glEnableVertexAttribArray(2);
       glBindBuffer(GL_ARRAY_BUFFER,uvBuff);
       glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,0,(void*)0);

       glBindVertexArray(0);


   }
public:
    Clouds(){}
    virtual ~Clouds(){}
    void setAlpha(float alpha){
       this->alhpa=alpha;
   }
    void initAtribiuts(GLuint shaderID){
        Pid=glGetUniformLocation( shaderID,"P");
        Vid=glGetUniformLocation( shaderID,"V");
        Mid=glGetUniformLocation( shaderID,"M");
        particlePosID=glGetUniformLocation(shaderID,"ParticlePos");
        alphaid=glGetUniformLocation( shaderID,"alpha");

   }

};
#endif //UNTITLED3_CLOUDS_H
