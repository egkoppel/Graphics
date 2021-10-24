#define STB_IMAGE_IMPLEMENTATION
#include <std_image.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/startup.c"
#include "include/buffer.c"
#include "include/shader.c"
#include "include/texture.c"
#include "include/draw.c"
#include "include/shaderstore.txt"

int main(void) {

    GLFWwindow* window = startup(600, 600, "Graphics with OpenGL and GLFW", NULL, NULL, 1);
    if (window == NULL) {
        printf("Startup Error\n");
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

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    
    struct Quad rect;
    rect.vshader = texturevertex;
    rect.fshader = texturefragment;
    rect.texturepath = "../textures/mii_face_512x512.png";
    rect.slot = 0;
    rect.donebefore = 0;

    memcpy(positions, rect.positions, sizeof(positions));
    memcpy(texcoords, rect.texcoords, sizeof(texcoords));
    memcpy(indices, rect.indices, sizeof(indices));

    glClearColor(0.0f, 0.3f, 0.2f, 0.0f);
    //Loop until the user closes the window
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