#include "Display.h"
#include <iostream>
#include <GL/glew.h>

Display::Display(int width, int height, const std::string& title) {//Konstruktor
    SDL_Init(SDL_INIT_EVERYTHING);              //Init video, sound, keys input, window control...

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);  // RGB 24 bits and 8bit for alpha => transparency

    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32); //Create buffer for 32 bit 
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // Use doublebuffer for enabling smoot rendering

    m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL); //Create window on the center of the screen
    if (!m_window) {// If window is not created
        std::cerr << "Failed to create SDL window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }

    m_glContext = SDL_GL_CreateContext(m_window);// Kontekst je skup metoda renderovanja
    if (!m_glContext) {
        std::cerr << "Failed to create OpenGL context: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        return;
    }

    GLenum status = glewInit(); // Inicijalizacija glew zato sto moderni opengl zahteva glew ekstenziju
    if (status != GLEW_OK) {
        std::cerr << "GLEW failed to initialize!" << std::endl;
    }

    m_isClosed = false; 
}

Display::~Display() { // Destruktor. Without destructor, it woiuld lead to memory leak and bad performance.
    SDL_GL_DeleteContext(m_glContext);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

bool Display::isClosed() { 
    return m_isClosed;
}

void Display::Clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Display::Update() {// Update is related to changing between two  buffer to avoid flickering. First buffer is the front image, second buffer contain nex image.
    SDL_GL_SwapWindow(m_window);

    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            m_isClosed = true; 
        }
    }
}
