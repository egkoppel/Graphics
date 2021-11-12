#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_IMPLEMENTATION

#include <std_image.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

#include <glm/glm.hpp> //FORGIVE ME FATHER FOR I HAVE SINNED
#include <glm/gtc/matrix_transform.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>

#include "startup.c"
#include "buffer.c"
#include "shader.c"
#include "texture.c"
#include "draw.c"

//#include "testclearcolor.c"
#include "test.c"

int main(void) {

//#include "tardis.c"

    int width =  800;
    int height = 500;

    GLFWwindow* window = startup(width, height, "Graphics with OpenGL and GLFW", NULL, NULL, 1, 0.0f, 0.3f, 0.2f, 0.0f);
    if (window == NULL) {
        printf("Window Startup Error\n");
        return -1;
    }

    float positions[] = {
         //positions       //tex coord   //vertex colours
        -150.0f, -150.0f,  0.0f, 0.0f,   1.0f, 0.0f, 0.0f,  //0 - Bottom-Left 
         150.0f, -150.0f,  1.0f, 0.0f,   0.0f, 1.0f, 0.0f,  //1 - Bottom-Right
         150.0f,  150.0f,  1.0f, 1.0f,   0.0f, 0.0f, 1.0f,  //2 - Top----Right
        -150.0f,  150.0f,  0.0f, 1.0f,   1.0f, 1.0f, 0.0f   //3 - Top----Left
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    glm::mat4 proj = glm::ortho(0.0f, (float)width, 0.0f, (float)height, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(200, 200, 0));
    glm::mat4 mvp = proj * view * model;

    struct TextureQuad face;
    face.vshader = "../shaders/projtexturevertex.glsl";
    face.fshader = "../shaders/colourtexturefragment.glsl";
    face.texturepath = "../textures/mii_face_512x512.png";
    face.slot = 1;
    face.donebefore = 0;
    face.texture_mag_filter = GL_NEAREST;
    face.texture_min_filter = GL_NEAREST;
    face.texture_wrap_s = GL_REPEAT;
    face.texture_wrap_t = GL_REPEAT;

    struct TextureQuad wall;
    wall.vshader = "../shaders/projtexturevertex.glsl";
    wall.fshader = "../shaders/colourtexturefragment.glsl";
    wall.texturepath = "../textures/cobble_stone.png";
    wall.slot = 0;
    wall.donebefore = 0;
    wall.texture_mag_filter = GL_LINEAR;
    wall.texture_min_filter = GL_LINEAR;
    wall.texture_wrap_s = GL_REPEAT;
    wall.texture_wrap_t = GL_REPEAT;
    
    for (int i = 0; i < 28; i++) {
        face.positions[i] = positions[i];
        wall.positions[i] = positions[i];
    }
    for (int i = 0; i < 6; i++) {
        face.indices[i] = indices[i];
        wall.indices[i] = indices[i];
    }

    struct TextureQuad stuff[] = {wall, face};

    ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init(window, true);
    ImGui::StyleColorsDark();

    /*
    //ImGui::StyleColorsClassic();
    float f;
    glm::vec3 translation(200, 200, 0);
    glm::vec3 translation2(600, 200, 0);
    */
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        onupdate(0.0f);
        onrender();

        ImGui_ImplGlfwGL3_NewFrame();

        onimguirender();

        drawStructArray(stuff, (sizeof(stuff)/sizeof(stuff[0])), mvp);
        /*
        ImGui::SliderFloat3("Translation", &translation.x, 0.0f, (float)width);            // Edit 1 float using a slider from 0.0f to 1.0f
        model = glm::translate(glm::mat4(1.0f), translation);
        mvp = proj * view * model;
        drawStruct(&wall, mvp);

        
        ImGui::SliderFloat3("Translation2", &translation2.x, 0.0f, (float)width);            // Edit 1 float using a slider from 0.0f to 1.0f
        model = glm::translate(glm::mat4(1.0f), translation2);
        mvp = proj * view * model;
        drawStruct(&face, mvp);
        */

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

        ImGui::Render();
        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    //deleteshadertexture(stuff, (sizeof(stuff) / sizeof(stuff[0])));
    glfwTerminate();
    return 0;
}
