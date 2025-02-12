#include <iostream>
#include "Display.h"
#include <GL/glew.h>
#include "Shader.h"

int main(){
    Display display(800, 800, "Waffen SS");

    Shader shader("/res/basicShader");

    while(!display.isClosed()){
        glClear(GL_COLOR_BUFFER_BIT);
        shader.Bind();


        display.Update();
    }
    return 0;
}