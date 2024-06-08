#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <stdio.h>
#include <stdlib.h>

#include "window.h"

int render(Node *vertexArr)
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


  Point **vertex = getVertexPos(vertexArr);

  unsigned int VBO;
  glGenBuffers(1, &VBO); 
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  glBufferData(GL_ARRAY_BUFFER, NUM_NODES, vertex, GL_STATIC_DRAW);

  const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);

  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  int  success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

  if(!success)
  {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    printf("error while compiling vertex shader %s\n", infoLog);
  }

  const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

  if(!success)
  {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    printf("error while compiling fragment shader %s\n", infoLog);
  }

  unsigned int shaderProgram;
  shaderProgram = glCreateProgram();

  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

  if(!success)
  {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    printf("error while linking program %s\n", infoLog);
  }
  
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  
  glUseProgram(shaderProgram);

  while (!glfwWindowShouldClose(window))
  {
    // input
    // not doint it fow now

    // render
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // draw one dot
    glPointSize(1.0f);
    glBegin(GL_POINTS);

    glVertex2f((vertexArr + 0)->point.x, (vertexArr + 0)->point.y);
    glEnd();

    // swap buffers and poll IO events
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}

Point **getVertexPos(Node *vertexArr)
{
  Point **vertexPos;
  *vertexPos = malloc(sizeof(Point) * NUM_NODES);

  for (int i = 0; i < NUM_NODES; i++)
  {
    printf("Vertex %d\n", i);
    printf("%.2f, %.2f\n%.2f, %.2f\n", (vertexArr + i)->point.x, (vertexArr + i)->point.y, (vertexArr + i)->point.x, (vertexArr + i)->point.y);
    Point *p = malloc(sizeof(Point));
    p->x = (vertexArr + i)->point.x;
    p->y = (vertexArr + i)->point.y;
    vertexPos[i] = p;
  };
  return vertexPos;
}

