void draw(unsigned int shader, unsigned int vao, unsigned int ibo, GLenum mode, GLsizei count, GLenum type, const void *indices){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    bindshader(shader);
    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glDrawElements(mode, count, type, indices);
    //Since everything gets bound at the start again, there's little point unbinding stuff
}

struct TextureQuad {
    float positions[28];
    unsigned int indices[6];
    unsigned int buffer;
    unsigned int ibo;
    unsigned int vao;
    const char* vshader;
    const char* fshader;
    unsigned int slot;
    unsigned int texshader;
    const char* texturepath;
    GLint texture_min_filter;
    GLint texture_mag_filter;
    GLint texture_wrap_s;
    GLint texture_wrap_t;
    GLuint texture;
    //unsigned int texture;
    unsigned short int donebefore;
};

void drawStruct(struct TextureQuad* item, glm::mat4 proj) {
    if (item->donebefore == 0) {
        floatbuffer(GL_ARRAY_BUFFER, 1, &item->buffer, item->positions, sizeof(item->positions));
        unsignedintbuffer(GL_ELEMENT_ARRAY_BUFFER, 1, &item->ibo, item->indices, sizeof(item->indices));
        vertexarray(1, &item->vao);
        glBindBuffer(GL_ARRAY_BUFFER, item->buffer);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (const void*)(sizeof(float) * 0));
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (const void*)(sizeof(float) * 2));
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (const void*)(sizeof(float) * 4));

        item->texshader = createshader(item->vshader, item->fshader);
        bindshader(item->texshader);

        maketexture(item->texturepath, &item->texture, item->texture_mag_filter, item->texture_min_filter, item->texture_wrap_s, item->texture_wrap_t);

        item->donebefore++;
    }
    
    bindshader(item->texshader);
    bindtexture(item->slot, item->texture);
    setuniform1i(item->texshader, "u_texture", item->slot);
    setuniformmat4f(item->texshader, "u_MVP", proj);
    glBindVertexArray(item->vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, item->ibo);
    glDrawElements(GL_TRIANGLES, ( sizeof(item->indices) / sizeof(item->indices[0]) ), GL_UNSIGNED_INT, NULL);
}

void drawStructArray(struct TextureQuad items[], unsigned int length, glm::mat4 proj) {
    for (unsigned int i = 0; i < length; i++) {
        drawStruct(&items[i], proj);
    }
}

void deleteshadertexture(struct TextureQuad items[], unsigned int length) {
    for (unsigned int i = 0; i < length; i++) {
        deleteshader(items[i].texshader);
        deletetexture(&items[i].texture);
    }
}