#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <stdio.h>
#include <stdlib.h>

#include "window.h"

int render(Vertex *vertexArr)
{
  GLFWwindow* window;

  if (!glfwInit())
    return -1;
  
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  uint width = 640;
  uint height = 480;

  window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
  if (!window)
  {
    glfwTerminate();
    return -1;
  }


  glfwMakeContextCurrent(window);

  if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
  {
    printf("Failed to initialize GLAD\n");
    return -1;
  }

  glViewport(0, 0, width, height);

  while (!glfwWindowShouldClose(window))
  {
    // input
    // not doint it fow now

    // render
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
