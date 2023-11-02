#include "../aux/GLFW/glfw3.h"

void initWindow(const char *wndName, int screenWidth, int screenHeight, int major, int minor);
void createWindow();

int windowIsOpen();
void glSwapBuffers();

void Do_Movement();
void getFrameTime();

void getShaderUniforms(int shader_ID);
void transformCamera(int shader_ID);

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
