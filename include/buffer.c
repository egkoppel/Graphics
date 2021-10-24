//Perhaps tidy it up to reflect the fact that I seldom declare multiple buffers in a single line.

void floatbuffer(GLenum buffer_type, GLsizei size, unsigned int* buffer, float data[], unsigned int datasize) {
    glGenBuffers(size, buffer);
    for (int i = 0; i < size; ++i) {
        glBindBuffer(buffer_type, buffer[i]);
    }
    glBufferData(buffer_type, datasize, data, GL_STATIC_DRAW);
}

void unsignedintbuffer(GLenum buffer_type, GLsizei size, unsigned int* buffer, unsigned int data[], unsigned int datasize) {
    glGenBuffers(size, buffer);
    for (int i = 0; i < size; ++i) {
        glBindBuffer(buffer_type, buffer[i]);
    }
    glBufferData(buffer_type, datasize, data, GL_STATIC_DRAW);
}

void vertexarray(GLsizei size, unsigned int* buffer){
    glGenVertexArrays(size, buffer);
    for (int i = 0; i < size; ++i) {
        glBindVertexArray(buffer[i]);
    }
}

void unbindbuffer(GLenum buffer_type) {
    glBindBuffer(buffer_type, 0);
}

void unbindvao(void) {
    glBindVertexArray(0);
}

/*
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW); //Don't change the size!
    
    unsigned int buffer;
    makebuffer(GL_ARRAY_BUFFER, 1, &buffer, positions, sizeof(positions));

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);    
*/