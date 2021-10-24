#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texcoord;
out vec2 v_texcoord;
void main(){
    gl_Position = position;
    v_texcoord = texcoord;
}