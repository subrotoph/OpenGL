//  Copyright © 2019 Subph. All rights reserved.
//

#pragma once

class Basic {
    
public:
    Basic() { }
    
    void runTriangle();
    void runTexture();
    void runPerspective();
    void runTestCamera();
    void runLighting();
    void runMultipleLight();
    
private:
    
};



#define CUBE_TEXTURE {               \
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,\
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,\
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,\
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,\
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,\
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,\
                                     \
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,\
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,\
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,\
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,\
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,\
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,\
                                     \
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,\
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,\
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,\
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,\
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,\
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,\
                                     \
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,\
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,\
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,\
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,\
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,\
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,\
                                     \
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,\
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,\
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,\
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,\
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,\
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,\
                                     \
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,\
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,\
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,\
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,\
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,\
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f \
}

#define CUBE_NORMAL {                        \
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,\
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,\
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,\
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,\
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,\
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,\
                                             \
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,\
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,\
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,\
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,\
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,\
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,\
                                             \
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,\
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,\
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,\
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,\
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,\
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,\
                                             \
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,\
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,\
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,\
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,\
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,\
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,\
                                             \
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,\
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,\
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,\
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,\
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,\
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,\
                                             \
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,\
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,\
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,\
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,\
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,\
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f \
}
