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
    mat4 model=mat4(1.0);

    view[3]=V[3];
    model[3]=P[3];


    mat3 invViewRot = inverse(mat3(V));
    vec3 worldPos        = invViewRot * pos;



    gl_Position=P*V*M*vec4(worldPos,1.0f);
    UV=uvMap;
}
