#define STB_IMAGE_IMPLEMENTATION
#define _CRT_SECURE_NO_WARNINGS
#include <std_image.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include "include/startup.c"
#include "include/buffer.c"
#include "include/shader.c"
#include "include/texture.c"
#include "include/draw.c"

int main(void) {

    GLFWwindow* window = startup(600, 600, "Graphics with OpenGL and GLFW", NULL, NULL, 1, 0.0f, 0.3f, 0.2f, 0.0f);
    if (window == NULL) {
        printf("Window Startup Error\n");
        return -1;
    }
    
    float positions[] = {
        -1.0f, -1.0f, 0.0f, 0.0f, //0 
         1.0f, -1.0f, 1.0f, 0.0f, //1
         1.0f,  1.0f, 1.0f, 1.0f, //2
        -1.0f,  1.0f, 0.0f, 1.0f  //3
    };

    float texcoords[] = {
         0.0f,  0.0f, //0 
         1.0f,  0.0f, //1
         1.0f,  1.0f, //2
         0.0f,  1.0f  //3
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    struct Quad rect;
    rect.vshader = "../shaders/texturevertex.glsl";
    rect.fshader = "../shaders/texturefragment.glsl";
    rect.texturepath = "../textures/mii_face_512x512.png";
    rect.slot = 0;
    rect.donebefore = 0;

    struct Quad wall;
    wall.vshader = "../shaders/texturevertex.glsl";
    wall.fshader = "../shaders/texturefragment.glsl";
    wall.texturepath = "../textures/cobble_stone.png";
    wall.slot = 1;
    wall.donebefore = 0;
    
    for (int i = 0; i < 16; i++) {
        rect.positions[i] = positions[i];
        wall.positions[i] = positions[i];
    }
    for (int i = 0; i < 8; i++) {
        rect.texcoords[i] = texcoords[i];
        wall.texcoords[i] = texcoords[i];
    }
    for (int i = 0; i < 6; i++) {
        rect.indices[i] = indices[i];
        wall.indices[i] = indices[i];
    }

    struct Quad stuff[] = { wall, rect};

    while (!glfwWindowShouldClose(window)) {
        drawStructArray(stuff, (sizeof(stuff)/sizeof(stuff[0])));
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    deleteshader(rect.texshader);
    deletetexture(&rect.texture);
    glfwTerminate();
    return 0;
}