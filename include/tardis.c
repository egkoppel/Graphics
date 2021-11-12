float tardis[] = {
        -1.0f, -2.0f, -1.0f,  //0  bottom front left
         1.0f, -2.0f, -1.0f,  //1  bottom front right
         1.0f, -2.0f,  1.0f,  //2  bottom back  right
        -1.0f, -2.0f,  1.0f,  //3  bottom back  left
        -1.0f,  2.0f, -1.0f,  //4  top    front left
         1.0f,  2.0f, -1.0f,  //5  top    front right
         1.0f,  2.0f,  1.0f,  //6  top    back  right
        -1.0f,  2.0f,  1.0f,  //7  top    back  left
         0.0f,  3.0f,  0.0f   //8  cone top
};

unsigned int tardisindices[] = {
    0, 1, 2, //base
    1, 2, 3,
    0, 1, 4, //front
    4, 5, 1,
    2, 3, 6, //back
    6, 7, 3,
    0, 3, 4, //left
    4, 7, 3,
    1, 2, 5, //right
    5, 6, 2,
    4, 5, 8, //top front
    4, 3, 8, //top left
    6, 7, 8, //top back
    5, 6, 8  //top right
};