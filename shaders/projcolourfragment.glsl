#version 330 core
in vec3 v_vertexcolor;
out vec4 color;
void main(){
    color = vec4(v_vertexcolor, 1.0);
}