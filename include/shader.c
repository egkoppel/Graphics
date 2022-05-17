#ifdef _cplusplus
extern "C" {
#endif

static unsigned int compileshader(const char* source, unsigned int type) {
    unsigned int id = glCreateShader(type);
    glShaderSource(id, 1, &source, NULL);
    glCompileShader(id);
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int len;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
        char* message = (char*)malloc(len * sizeof(char));
        glGetShaderInfoLog(id, len, &len, message);
        printf("Oh Dear! The shader failed to compile!\n");
        printf("%s\n", message);
        glDeleteShader(id);
        return 0;
    }
    return id;
}

const char* parseshader(const char* filepath) {
    FILE* fp;
    fp = fopen(filepath, "rb");
    if (fp != NULL) {
        fseek(fp, 0, SEEK_END);
        int length = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        char* shadercode = (char*)malloc((length + 1) * sizeof(char));
        if (shadercode) {
            shadercode[length] = '\0';

            unsigned char store;
            for (int i = 0; i < length; i++) {
                fread(&store, 1, 1, fp);
                shadercode[i] = store;
            }

            fclose(fp);
            return(shadercode);
        }
        else {
            printf("const char* array shadercode could not be allocated memory, and was a NULL pointer.\n");
            return(NULL);
        }
    }
    else {
        printf("Shader file %s could not be found/opened.", filepath);
        return NULL;
    }
}

static unsigned int createshader(const char* VertexShader, const char* FragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vertexshader = compileshader(parseshader(VertexShader), GL_VERTEX_SHADER);
    unsigned int fragmentshader = compileshader(parseshader(FragmentShader), GL_FRAGMENT_SHADER);
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

//WARNING: Other versions of the following functions will need to be created for uniforms of different types, such as 1 float, matrices, etc.
void setuniform4f(unsigned int shader, const char *uniformname, float v0, float v1, float v2, float v3) {
    glUniform4f(getuniformlocation(shader, uniformname), v0, v1, v2, v3);
}

void setuniform1i(unsigned int shader, const char* uniformname, int i0) {
    glUniform1i(getuniformlocation(shader, uniformname), i0);
}

void setuniformmat4f(unsigned int shader, const char* uniformname, glm::mat4& matrix) {
    glUniformMatrix4fv(getuniformlocation(shader, uniformname), 1, GL_FALSE, &matrix[0][0]);
}

#ifdef _cplusplus
}
#endif