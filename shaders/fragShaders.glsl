#version 330
in vec4 clr;
in vec2 UV;

out vec4 color;

uniform sampler2D text;
uniform float alpha;

void main(){
	vec4 buff=texture(text, UV);
	if(buff.a<0.1)
        discard;
	color=vec4(buff.r*0.8,buff.g*0.8,buff.b*0.8,buff.a*alpha);
}
