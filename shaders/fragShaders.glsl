#version 330
in vec4 clr;
in vec2 UV;

out vec4 color;

uniform sampler2D text;
uniform float alpha;

void main(){
	vec4 buff=texture(text, UV);
	color=vec4(buff.r,buff.g,buff.b,buff.a*alpha);
}
