#include <iostream>
#include "Display.h"
#include <GL/glew.h>
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "transform.h"

int main(){
    Display display(800, 800, "First project");

    Vertex vertices[] = {
        Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0, 0)),
        Vertex(glm::vec3(0, 0.5, 0), glm::vec2(0.5, 1.0)),
        Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(1.0, 0))
    };
    
    Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]));
    Shader shader("./res/basicShader");
    Texture texture("./res/bricks.jpg");
    Transform transform;

    while (!display.isClosed()) {
        display.Clear(0.0f, 0.15f, 0.3f, 1.0f);
    
        shader.Bind();
        texture.Bind(0);
        shader.Update(transform);
        mesh.Draw();
    
        display.Update();
    }
    
    return 0;
}