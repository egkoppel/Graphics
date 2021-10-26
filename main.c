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

    struct TextureQuad face;
    face.vshader = "../shaders/texturevertex.glsl";
    face.fshader = "../shaders/texturefragment.glsl";
    face.texturepath = "../textures/mii_face_512x512.png";
    face.slot = 1;
    face.donebefore = 0;
    face.texture_mag_filter = GL_NEAREST;
    face.texture_min_filter = GL_NEAREST;
    face.texture_wrap_s = GL_REPEAT;
    face.texture_wrap_t = GL_REPEAT;

    struct TextureQuad wall;
    wall.vshader = "../shaders/texturevertex.glsl";
    wall.fshader = "../shaders/texturefragment.glsl";
    wall.texturepath = "../textures/cobble_stone.png";
    wall.slot = 0;
    wall.donebefore = 0;
    wall.texture_mag_filter = GL_LINEAR;
    wall.texture_min_filter = GL_LINEAR;
    wall.texture_wrap_s = GL_REPEAT;
    wall.texture_wrap_t = GL_REPEAT;
    
    for (int i = 0; i < 16; i++) {
        face.positions[i] = positions[i];
        wall.positions[i] = positions[i];
    }
    for (int i = 0; i < 8; i++) {
        face.texcoords[i] = texcoords[i];
        wall.texcoords[i] = texcoords[i];
    }
    for (int i = 0; i < 6; i++) {
        face.indices[i] = indices[i];
        wall.indices[i] = indices[i];
    }

    struct TextureQuad stuff[] = { wall, face };

    while (!glfwWindowShouldClose(window)) {
        drawStructArray(stuff, (sizeof(stuff)/sizeof(stuff[0])));
        glfwSwapBuffers(window);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwPollEvents();
    }

    deleteshader(face.texshader);
    deletetexture(&face.texture);
    //deleteshadertexture(stuff, (sizeof(stuff) / sizeof(stuff[0])));
    glfwTerminate();
    return 0;
}