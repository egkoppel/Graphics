void maketexture(const char* imagefile, unsigned int *texture) {
	int width, height, bpp;
	stbi_set_flip_vertically_on_load(1);
	unsigned char* localbuffer = stbi_load(imagefile, &width, &height, &bpp, 4);
	if(!localbuffer){
		printf("Image file %s could not be found/opened", imagefile);
		return NULL;
	}
	glGenTextures(1, texture);
	glBindTexture(GL_TEXTURE_2D, *texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localbuffer);
	glBindTexture(GL_TEXTURE_2D, 0);
	//glGenerateMipmap(GL_TEXTURE_2D);
	
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

void deletetexture(GLint* texture) {
	glDeleteTextures(1, texture);
}