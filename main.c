#define STB_IMAGE_IMPLEMENTATION
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
#include "shaders/shaderstore.txt"

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
    rect.vshader = texturevertex;
    rect.fshader = texturefragment;
    rect.texturepath = "../textures/mii_face_512x512.png";
    rect.slot = 0;
    rect.donebefore = 0;
    
    for (int i = 0; i < 16; i++) {
        rect.positions[i] = positions[i];
    }
    for (int i = 0; i < 8; i++) {
        rect.texcoords[i] = texcoords[i];
    }
    for (int i = 0; i < 6; i++) {
        rect.indices[i] = indices[i];
    }

    while (!glfwWindowShouldClose(window)) {
        //Render here
        drawStruct(rect);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //deleteshader(rect.texshader);
    deletetexture(&rect.texture);
    glfwTerminate();
    return 0;
}