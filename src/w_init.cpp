#include <iostream>

#include "camera.h"
#include "w_init.h"
#include "config.h"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


const GLuint screenWidth = 800;
const GLuint screenHeight = 600;
bool         keys[1024];
bool         firstMouse = true;

GLfloat lastX = (GLfloat)screenWidth  / 2;
GLfloat lastY = (GLfloat)screenHeight / 2;
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

GLFWwindow* window;
Camera      camera(glm::vec3(0.0f, 600.0f, 300.0f));

void initWindow(const char* wndName, int screenWidth, int screenHeight, int major, int minor) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_SAMPLES, 16); // AA samples

    window = glfwCreateWindow(screenWidth, screenHeight, wndName, nullptr, nullptr); // Windowed

    if (!window) {
        std::cout << "ENGINE_CYTRINE_RUNTIME_ERR_GL: error in glfwCreateWindow context" << std::endl;
        return;
    }

    glfwMakeContextCurrent(window);

    // Set the required callback functions
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // load extensions
    if (!gladLoadGL()) {
        std::cout << "ENGINE_CYTRINE_RUNTIME_ERR_GL: Failed to initialize OpenGL context" << std::endl;
    }

    glViewport(0, 0, screenWidth, screenHeight); // Define the viewport dimensions
    glEnable(GL_DEPTH_TEST);                     // Setup some OpenGL options

    std::cout << "ENGINE_CYTRINE_INFO: Using OpenGL v" << glGetString(GL_VERSION) << std::endl;
}

int windowIsOpen() {
    if (!glfwWindowShouldClose(window))
        return 1;
    return 0;
}

void glSwapBuffers() {
    glfwSwapBuffers(window);
    #if VSYNC == 1
    glfwSwapInterval(1);
	#else
	glfwSwapInterval(0);
    #endif
    glfwPollEvents();
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    if (action == GLFW_PRESS)
        keys[key] = true;
    else if (action == GLFW_RELEASE)
        keys[key] = false;
}

void Do_Movement() {
    // Camera controls
    if (keys[GLFW_KEY_W])
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (keys[GLFW_KEY_S])
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (keys[GLFW_KEY_A])
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (keys[GLFW_KEY_D])
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        firstMouse = false;
        lastX = xpos;
        lastY = ypos;
    }

    GLfloat xoffset = xpos - lastX;
    GLfloat yoffset = lastY - ypos; // Reversed since y-coordinates go from bottom to left

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll(yoffset);
}

void getFrameTime() {
    static char title[256];
    GLfloat currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // Calculate FPS
    int fps = static_cast<int>(1.0f / deltaTime);

    // Update the window title
    snprintf(title, sizeof(title), "Cytrine (%d FPS)", fps);
    glfwSetWindowTitle(window, title);
}


void transformCamera(int shader_ID) {
    Do_Movement();

    // Create camera transformation
    glm::mat4 view;
    view = camera.GetViewMatrix();
    glm::mat4 projection;
    projection = glm::perspective(camera.Zoom, (float)screenWidth / (float)screenHeight, 0.1f, 10000.0f);

    // Get the uniform locations
    GLint modelLoc = glGetUniformLocation(shader_ID, "model");
    GLint viewLoc  = glGetUniformLocation(shader_ID, "view");
    GLint projLoc  = glGetUniformLocation(shader_ID, "projection");

    // Pass the matrices to the shader
    glm::mat4 model;
    glUniformMatrix4fv(viewLoc,  1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc,  1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
}

void getShaderUniforms(int shader_ID) {
    glUniform1i(glGetUniformLocation(shader_ID, "s_bspTexture"), 0);
    glUniform1i(glGetUniformLocation(shader_ID, "s_bspLightmap"), 1);

    #if DEBUG_MODE == 1
    std::cout << "[ENGINE_CYTRINE_DEBUG]*glGetUniformLocation s_bspTexture  " << glGetUniformLocation(shader_ID, "s_bspTexture")  << std::endl;
    std::cout << "[ENGINE_CYTRINE_DEBUG]*glGetUniformLocation s_bspLightmap " << glGetUniformLocation(shader_ID, "s_bspLightmap") << std::endl;
    std::cout << "[ENGINE_CYTRINE_DEBUG]*shader_ID: " << shader_ID << std::endl;
    #endif
}
