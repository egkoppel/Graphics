static unsigned int compileshader(const char* source, unsigned int type) {
    unsigned int id = glCreateShader(type);
    glShaderSource(id, 1, &source, NULL);
    glCompileShader(id);
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int len;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
        char* message = malloc(len * sizeof(char));
        glGetShaderInfoLog(id, len, &len, message);
        printf("Oh Dear! The shader failed to compile!\n");
        printf("%s\n", message);
        glDeleteShader(id);
        return 0;
    }
    return id;
}

static unsigned int createshader(const char* VertexShader, const char* FragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vertexshader = compileshader(VertexShader, GL_VERTEX_SHADER);
    unsigned int fragmentshader = compileshader(FragmentShader, GL_FRAGMENT_SHADER);
    glAttachShader(program, vertexshader);
    glAttachShader(program, fragmentshader);
    glLinkProgram(program);
    glValidateProgram(program);
    glDeleteShader(vertexshader);
    glDeleteShader(fragmentshader);
    return(program);
}

void bindshader(unsigned int shader) {
    glUseProgram(shader);
}

void unbindshader(void) {
    glUseProgram(0);
}

void deleteshader(unsigned int program) {
    glDeleteProgram(program);
}

GLint getuniformlocation(GLuint program, const char *uniformname) {
    GLint location = glGetUniformLocation(program, uniformname);
    if (location == -1) {
        printf("WARNING: Uniform \"%s\" does not exist!\n", (char*)uniformname);
    }
    return location;
}

//WARNING: Other versions of the following function will need to be created for uniforms of different types, such as 1 float, matrices, etc.
void setuniform4f(unsigned int shader, const char *uniformname, float v0, float v1, float v2, float v3) {
    glUniform4f(getuniformlocation(shader, uniformname), v0, v1, v2, v3);
}

void setuniform1i(unsigned int shader, const char* uniformname, int i0) {
    glUniform1i(getuniformlocation(shader, uniformname), i0);
}
