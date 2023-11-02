#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "../aux/glad.h"

#include "Quake3Bsp.h"
#include "Shader.h"
#include "w_init.h"

int main(int argc, char* argv[]) {
    initWindow("CoreBSP", 800, 600, 3, 3);

    CQuake3BSP bsp;
    Shader     shader("shaders/simple.vs", "shaders/simple.fs");

    if (!bsp.LoadBSP(argv[1])) {
        return 1;
    }

    bsp.BuildVBO();
    bsp.GenerateTexture();
    bsp.GenerateLightmap();

    shader.Use();
    getShaderUniforms(shader.id());

    // Game loop
    while (windowIsOpen()) {
        getFrameTime();

        glClearColor(0.0f, 0.0f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        transformCamera(shader.id());

        bsp.renderFaces();

        glSwapBuffers();
    }
    glfwTerminate();
    return 0;
}
