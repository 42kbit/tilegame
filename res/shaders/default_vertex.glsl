#version 450 core

layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec2 a_TexCoords;

out vec2 v_TexCoords;

layout (std140) uniform ub_ProjView{
	mat4 proj;
	mat4 view;
} pv;
uniform mat4 u_Model;

void main(){
	v_TexCoords = a_TexCoords;
	gl_Position = pv.proj * pv.view * u_Model * vec4(a_Position, 0, 1);
}
