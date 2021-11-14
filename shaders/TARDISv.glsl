#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texcoord;
out vec2 v_texcoord;
uniform mat4 u_MVP;
void main(){
    gl_Position = u_MVP * position;
    v_texcoord = texcoord;
}