void draw(unsigned int shader, unsigned int vao, unsigned int ibo, GLenum mode, GLsizei count, GLenum type, const void *indices){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    bindshader(shader);
    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glDrawElements(mode, count, type, indices);
    //Since everything gets bound at the start again, there's little point unbinding stuff
}

struct Quad {
    float positions[16];
    float texcoords[8];
    unsigned int indices[6];
    unsigned int buffer;
    unsigned int texb;
    unsigned int ibo;
    unsigned int vao;
    const char* vshader;
    const char* fshader;
    unsigned int slot;
    unsigned int texture;
    unsigned int texshader;
    const char* texturepath;
    GLint texture_min_filter;
    GLint texture_mag_filter;
    GLint texture_wrap_s;
    GLint texture_wrap_t;
    unsigned short int donebefore;
};

void drawStruct(struct Quad* item) {
    if (item->donebefore == 0) {
        floatbuffer(GL_ARRAY_BUFFER, 1, &item->buffer, item->positions, sizeof(item->positions));
        unsignedintbuffer(GL_ELEMENT_ARRAY_BUFFER, 1, &item->ibo, item->indices, sizeof(item->indices));
        floatbuffer(GL_ARRAY_BUFFER, 1, &item->texb, item->texcoords, sizeof(item->texcoords));

        vertexarray(1, &item->vao);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, item->buffer);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (const void*)0);
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, item->texb);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (const void*)0);

        item->texshader = createshader(item->vshader, item->fshader);
        bindshader(item->texshader);

        maketexture(item->texturepath, &item->texture, item->texture_mag_filter, item->texture_min_filter, item->texture_wrap_s, item->texture_wrap_t);

        bindtexture(item->slot, item->texture);
        setuniform1i(item->texshader, "u_texture", item->slot);

        item->donebefore++;
    }
    
    bindshader(item->texshader);
    glBindVertexArray(item->vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, item->ibo);
    glDrawElements(GL_TRIANGLES, ( sizeof(item->indices) / sizeof(item->indices[0]) ), GL_UNSIGNED_INT, NULL);
}

void drawStructArray(struct Quad items[], unsigned int length) {
    for (int i = 0; i < length; i++) {
        drawStruct(&items[i]);
    }
}

void deleteshadertexture(struct Quad items[], unsigned int length) {
    for (int i = 0; i < length; i++) {
        deleteshader(&items[i].texshader);
        deletetexture(&items[i].texture);
    }
}