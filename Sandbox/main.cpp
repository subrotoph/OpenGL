//  Copyright © 2019 Subph. All rights reserved.
//

#include <iostream>

#include "basic/basic.h"
#include "system/system.h"

std::string NAME = "Sandbox";
GLuint WIDTH = 600;
GLuint HEIGHT = 600;

int main() {
    System &system = System::instance();
    
    system.settingWindow();
    system.createWindow(WIDTH, HEIGHT, NAME.c_str());
    
    system.initGlLibrary();
    system.settingOpenGL();
    system.settingInput();
    
    Basic basic = Basic();
    basic.runTexture();
    
    system.closeWindow();
    
    return EXIT_SUCCESS;
}
