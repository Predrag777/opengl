#include <iostream>
#include "Display.h"
#include <GL/glew.h>
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "transform.h"
#include "Camera.h"

#define WIDTH 800
#define HEIGHT 600

int main(){
    Display display(800, 800, "First project");

    Vertex vertices[] = {
        Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0, 0)),
        Vertex(glm::vec3(0, 0.5, 0), glm::vec2(0.5, 1.0)),
        Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(1.0, 0))
    };
    
    Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]));
    Camera camera(glm::vec3(0,0,-3), 70.0f, (float) WIDTH/(float) HEIGHT, 0.01f, 1000.0f);
    Shader shader("./res/basicShader");
    Texture texture("./res/bricks.jpg");
    Transform transform;

    float counter=0.0f;

    while (!display.isClosed()) {
        display.Clear(0.0f, 0.15f, 0.3f, 1.0f);
    
        transform.GetPos()->x = sinf(counter);


        shader.Bind();
        texture.Bind(0);
        shader.Update(transform, camera);
        mesh.Draw();
    
        display.Update();
        counter+=0.00001f;
    }
    
    return 0;
}