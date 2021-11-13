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

#include "controls.cpp"
//#include "testclearcolor.c"
#include "test.c"

int main(void) {

    #include "tardis.c"
 
    int width =  800;
    int height = 500;

    GLFWwindow* window = startup(width, height, "Graphics with OpenGL and GLFW", NULL, NULL, 1, 0.0f, 0.3f, 0.2f, 0.0f);
    if (window == NULL) {
        printf("Window Startup Error\n");
        return -1;
    }

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    // Hide the mouse and enable unlimited mouvement
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Set the mouse at the center of the screen
    glfwPollEvents();
    glfwSetCursorPos(window, width / 2, height / 2);
    
    float positions1[] = {
         //positions          //tex coord   //vertex colours
         1.0f,  1.0f, 10.0f,  0.0f, 0.0f,   1.0f, 0.0f, 0.0f,  //0 - Bottom-Left 
         2.0f,  1.0f, 10.0f,  1.0f, 0.0f,   0.0f, 1.0f, 0.0f,  //1 - Bottom-Right
         2.0f,  2.0f, 10.0f,  1.0f, 1.0f,   0.0f, 0.0f, 1.0f,  //2 - Top----Right
         1.0f,  2.0f, 10.0f,  0.0f, 1.0f,   1.0f, 1.0f, 0.0f   //3 - Top----Left
    };

    float positions2[] = {
        //positions          //tex coord   //vertex colours
       -1.0f, -1.0f, 10.0f,  0.0f, 0.0f,   1.0f, 0.0f, 0.0f,  //0 - Bottom-Left 
        1.0f, -1.0f, 10.0f,  1.0f, 0.0f,   0.0f, 1.0f, 0.0f,  //1 - Bottom-Right
        1.0f,  1.0f, 10.0f,  1.0f, 1.0f,   0.0f, 0.0f, 1.0f,  //2 - Top----Right
       -1.0f,  1.0f, 10.0f,  0.0f, 1.0f,   1.0f, 1.0f, 0.0f   //3 - Top----Left
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    float aspect = (float)width / (float)height;
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), aspect, 0.0f, 125.0f);
    glm::mat4 view = glm::lookAt(
        glm::vec3(-5, 2, -5), // Camera is at (0,2,10), in World Space
        glm::vec3(0, 0, 0), // and looks at the origin
        glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
    );
    glm::mat4 model = glm::mat4(1.0f);
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
    
    for (int i = 0; i < 32; i++) {
        face.positions[i] = positions1[i];
        wall.positions[i] = positions2[i];
    }
    for (int i = 0; i < 6; i++) {
        face.indices[i] = indices[i];
        wall.indices[i] = indices[i];
    }

    struct TextureQuad stuff[] = {face, wall};

    struct VertexColourModel tardis;
    tardis.vshader = "../shaders/projcolourvertex.glsl";
    tardis.fshader = "../shaders/projcolourfragment.glsl";
    tardis.donebefore = 0;

    struct BasicColourModel tardisblue;
    tardisblue.vshader = "../shaders/projvertex.glsl";
    tardisblue.fshader = "../shaders/bluefragment.glsl";
    tardisblue.donebefore = 0;

    for (int i = 0; i < 54; i++) {
        tardis.positions[i] = tardispositions1[i];
    }
    for (int i = 0; i < 27; i++) {
        tardisblue.positions[i] = tardispositions0[i];
    }
    for (int i = 0; i < 42; i++) {
        tardis.indices[i] = tardisindices[i];
        tardisblue.indices[i] = tardisindices[i];
    }

    ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init(window, true);
    ImGui::StyleColorsDark();

    /*
    //ImGui::StyleColorsClassic();
    float f;
    glm::vec3 translation(200, 200, 0);
    glm::vec3 translation2(600, 200, 0);
    */
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    //glEnable(GL_CULL_FACE);
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        onupdate(0.0f);
        onrender();

        //ImGui_ImplGlfwGL3_NewFrame();

        //onimguirender();
        computeMatricesFromInputs(window, width, height);
        glm::mat4 proj = getProjectionMatrix();
        glm::mat4 view = getViewMatrix();
        glm::mat4 model = glm::mat4(1.0);
        mvp = proj * view * model;
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
        drawBasicColourModel(&tardisblue , mvp);
        drawVertexColourModel(&tardis, mvp);
        //ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

        //ImGui::Render();
        //ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    //deleteshadertexture(stuff, (sizeof(stuff) / sizeof(stuff[0])));
    glfwTerminate();
    return 0;
}
