#version 330
layout(location=0)in vec3 pos;
layout(location=1)in vec4 color;
layout(location=2)in vec2 uvMap;

out vec4 clr;
out vec2 UV;


uniform mat4 P;
uniform mat4 V;
uniform mat4 M;
uniform vec3 ParticlePos;

void main(){
    vec3 right=vec3(V[0][0],V[1][0],V[2][0]);
    vec3 up=vec3(V[0][1],V[1][1],V[2][1]);

    vec3 worldPos = ParticlePos
    +right*pos.x
    +up*pos.y;



    gl_Position=P*V*vec4(worldPos,1.0f);
    UV=uvMap;
}
