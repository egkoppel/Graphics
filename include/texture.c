#ifdef _cplusplus
extern "C" {
#endif

void maketexture(const char* imagefile, GLuint *texture, GLint texture_mag_filter, GLint texture_min_filter, GLint texture_wrap_s, GLint texture_wrap_t) {
	int width, height, bpp;
	stbi_set_flip_vertically_on_load(1);
	unsigned char* localbuffer = stbi_load(imagefile, &width, &height, &bpp, 4);
	if(!localbuffer){
		printf("Image file %s could not be found/opened", imagefile);
	}
	glGenTextures(1, texture);
	glBindTexture(GL_TEXTURE_2D, *texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texture_mag_filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texture_min_filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texture_wrap_s);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texture_wrap_t);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localbuffer);
	glBindTexture(GL_TEXTURE_2D, 0);
	glGenerateMipmap(GL_TEXTURE_2D);
	
	if (localbuffer) {
		stbi_image_free(localbuffer);
	}
}

void bindtexture(unsigned int slot, unsigned int texture) {
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, texture);
}

void unbindtexture(void) {
	glBindTexture(GL_TEXTURE_2D, 0);
}

void deletetexture(const GLuint* texture) {
	glDeleteTextures(1, texture);
}

#ifdef _cplusplus
}
#endif