    float tardispositions1[] = {
        //vertices              //vertex colours
        -1.0f, -2.0f, -1.0f,    0.583f,  0.771f,  0.014f, //0  bottom front left   
         1.0f, -2.0f, -1.0f,    0.609f,  0.115f,  0.436f, //1  bottom front right  
         1.0f, -2.0f,  1.0f,    0.327f,  0.483f,  0.844f, //2  bottom back  right  
        -1.0f, -2.0f,  1.0f,    0.822f,  0.569f,  0.201f, //3  bottom back  left   
        -1.0f,  1.0f, -1.0f,    0.435f,  0.602f,  0.223f, //4  top    front left   
         1.0f,  1.0f, -1.0f,    0.310f,  0.747f,  0.185f, //5  top    front right  
         1.0f,  1.0f,  1.0f,    0.597f,  0.770f,  0.761f, //6  top    back  right  
        -1.0f,  1.0f,  1.0f,    0.559f,  0.436f,  0.730f, //7  top    back  left   
         0.0f,  2.0f,  0.0f,    0.359f,  0.583f,  0.152f  //8  cone top            
    };

    float tardispositions0[] = {
        //vertices             
         4.0f, -2.0f, -1.0f,   //0  bottom front left   
         6.0f, -2.0f, -1.0f,   //1  bottom front right  
         6.0f, -2.0f,  1.0f,   //2  bottom back  right  
         4.0f, -2.0f,  1.0f,   //3  bottom back  left   
         4.0f,  1.0f, -1.0f,   //4  top    front left   
         6.0f,  1.0f, -1.0f,   //5  top    front right  
         6.0f,  1.0f,  1.0f,   //6  top    back  right  
         4.0f,  1.0f,  1.0f,   //7  top    back  left   
         5.0f,  2.0f,  0.0f    //8  cone top            
    };

    unsigned int tardisindices[] = {
        0, 1, 2, //base
        2, 3, 0,
        1, 0, 4, //front
        4, 5, 1,
        3, 2, 6, //back
        6, 7, 3,
        0, 3, 4, //left
        7, 4, 3,
        2, 1, 5, //right
        5, 6, 2,
        5, 4, 8, //top front
        4, 7, 8, //top left
        7, 6, 8, //top back
        6, 5, 8  //top right
    };