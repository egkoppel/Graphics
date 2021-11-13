#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 vertexcolor;
out vec3 v_vertexcolor;
uniform mat4 u_MVP;
void main(){
    gl_Position = u_MVP * vec4(position, 1);
    v_vertexcolor = vertexcolor;
}