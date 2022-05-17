#ifdef _cplusplus
extern "C" {
#endif

GLFWwindow* startup(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share, int swapinterval, float red, float green, float blue, float alpha) {

    GLFWwindow* window;

    //Initialize the library
    if (!glfwInit()) {
        return NULL;
    }
    printf("GLWF init\n");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);


    //Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(width, height, title, monitor, share);
    if (window == NULL) {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return NULL;
    }

    //Make the window's context current
    glfwMakeContextCurrent(window);
    glfwSwapInterval(swapinterval);

    if (glewInit() != GLEW_OK) {
        printf("Oh dear! It seems that for some reason, GLEW didn't initialise correctly.\n");
        glfwTerminate();
        return NULL;
    }

    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    glClearColor(red, green, blue, alpha);

    return window;
}

#ifdef _cplusplus
}
#endif