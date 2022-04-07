#version 330
layout(location=0)in vec3 pos;
layout(location=1)in vec4 color;
layout(location=2)in vec2 uvMap;

out vec4 clr;
out vec2 UV;

uniform mat4 P;
uniform mat4 V;
uniform mat4 M;


void main(){

    mat4 view=mat4(1.0);
    view[0][3]=V[0][3];
    view[1][3]=V[1][3];
    view[2][3]=V[2][3];
    view[3]=V[3];
    gl_Position=P*view*M*vec4(pos,1.0f);
    UV=uvMap;
}
