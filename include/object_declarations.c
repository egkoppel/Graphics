#include "shader_config.h"

#ifdef _cplusplus
extern "C" {
#endif

float positions1[] = {
    //positions          //tex coord   //vertex colours
    1.0f,  1.0f, 10.0f,  0.0f, 0.0f,   1.0f, 0.0f, 0.0f,  //0 - Bottom-Left 
    2.0f,  1.0f, 10.0f,  1.0f, 0.0f,   0.0f, 1.0f, 0.0f,  //1 - Bottom-Right
    2.0f,  2.0f, 10.0f,  1.0f, 1.0f,   0.0f, 0.0f, 1.0f,  //2 - Top----Right
    1.0f,  2.0f, 10.0f,  0.0f, 1.0f,   1.0f, 1.0f, 0.0f   //3 - Top----Left
};

float positions2[] = {
    //positions          //tex coord   //vertex colours
   -1.0f,  0.0f, 10.0f,  0.0f, 0.0f,   1.0f, 0.0f, 0.0f,  //0 - Bottom-Left 
    1.0f,  0.0f, 10.0f,  1.0f, 0.0f,   0.0f, 1.0f, 0.0f,  //1 - Bottom-Right
    1.0f,  2.0f, 10.0f,  1.0f, 1.0f,   0.0f, 0.0f, 1.0f,  //2 - Top----Right
   -1.0f,  2.0f, 10.0f,  0.0f, 1.0f,   1.0f, 1.0f, 0.0f   //3 - Top----Left
};

float floorpositions[] = {
    //positions          //tex coord   //vertex colours
  -10.0f,  0.0f, -10.0f,  0.0f, 0.0f,   0.5f, 0.5f, 0.5f,  //0 - Bottom-Left 
   10.0f,  0.0f, -10.0f,  1.0f, 0.0f,   0.5f, 0.5f, 0.5f,  //1 - Bottom-Right
   10.0f,  0.0f,  10.0f,  1.0f, 1.0f,   0.5f, 0.5f, 0.5f,  //2 - Top----Right
  -10.0f,  0.0f,  10.0f,  0.0f, 1.0f,   0.5f, 0.5f, 0.5f   //3 - Top----Left
};

float manpositions[] = {
    //positions          //tex coord    //vertex colours
    0.0f,  0.0f, -5.0f,  0.25f, 0.0f,   1.0f, 1.0f, 1.0f,  //0 - Bottom-Left 
    1.0f,  0.0f, -5.0f,  0.75f, 0.0f,   1.0f, 1.0f, 1.0f,  //1 - Bottom-Right
    1.0f,  2.0f, -5.0f,  0.75f, 1.0f,   1.0f, 1.0f, 1.0f,  //2 - Top----Right
    0.0f,  2.0f, -5.0f,  0.25f, 1.0f,   1.0f, 1.0f, 1.0f   //3 - Top----Left
};


unsigned int indices[] = {
    1, 0, 2,
    3, 2, 0
};

struct TextureQuad face;
face.vshader = PROJECTION_TEXTURE_VERTEX_SHADER_PATH;
face.fshader = COLOUR_TEXUTURE_FRAG_SHADER;
face.texturepath = TEXTURE_MII_FACE;
face.slot = 1;
face.donebefore = 0;
face.texture_mag_filter = GL_NEAREST;
face.texture_min_filter = GL_NEAREST;
face.texture_wrap_s = GL_REPEAT;
face.texture_wrap_t = GL_REPEAT;

struct TextureQuad wall;
wall.vshader = PROJECTION_TEXTURE_VERTEX_SHADER_PATH;
wall.fshader = COLOUR_TEXUTURE_FRAG_SHADER;
wall.texturepath = TEXTURE_COBBLESTONE;
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


struct VertexColourModel tardis;
tardis.vshader = PROJECTION_COLOUR_VERTEX;
tardis.fshader = PROJECTION_COLOUR_FRAGMENT;
tardis.donebefore = 0;

struct BasicColourModel tardisblue;
tardisblue.vshader = PROJECTION_VERTEX;
tardisblue.fshader = BLUE_FRAG;
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

struct TextureModel TARDIS;
TARDIS.vshader = TARDIS_VERTEX_SHADER;
TARDIS.fshader = TEXTURE_FRAG_SHADER;
TARDIS.texturepath = TEXTURE_TARDIS;
TARDIS.slot = 2;
TARDIS.donebefore = 0;
TARDIS.texture_mag_filter = GL_NEAREST;
TARDIS.texture_min_filter = GL_NEAREST;
TARDIS.texture_wrap_s = GL_REPEAT;
TARDIS.texture_wrap_t = GL_REPEAT;

for (int i = 0; i < 210; i++) {
    TARDIS.positions[i] = tardispositions2[i];

}

struct TextureQuad floor;
floor.vshader = PROJECTION_TEXTURE_VERTEX_SHADER_PATH;
floor.fshader = COLOUR_TEXUTURE_FRAG_SHADER;
floor.texturepath = TEXTURE_COBBLESTONE;
floor.slot = 2;
floor.donebefore = 0;
floor.texture_mag_filter = GL_LINEAR;
floor.texture_min_filter = GL_LINEAR;
floor.texture_wrap_s = GL_MIRRORED_REPEAT;
floor.texture_wrap_t = GL_MIRRORED_REPEAT;

for (int i = 0; i < 32; i++) {
    floor.positions[i] = floorpositions[i];
}

for (int i = 0; i < 6; i++) {
    floor.indices[i] = indices[i];
}

struct TextureQuad man;
man.vshader = PROJECTION_TEXTURE_VERTEX_SHADER_PATH;
man.fshader = COLOUR_TEXUTURE_FRAG_SHADER;
man.texturepath = TEXTURE_MAN;
man.slot = 2;
man.donebefore = 0;
man.texture_mag_filter = GL_LINEAR;
man.texture_min_filter = GL_LINEAR;
man.texture_wrap_s = GL_REPEAT;
man.texture_wrap_t = GL_REPEAT;

for (int i = 0; i < 32; i++) {
    man.positions[i] = manpositions[i];
}

for (int i = 0; i < 6; i++) {
    man.indices[i] = indices[i];
}


struct TextureQuad stuff[] = { face, wall, floor, man };

#ifdef _cplusplus
}
#endif