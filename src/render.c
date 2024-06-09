#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <stdio.h>
#include <stdlib.h>

#include "render.h"

Point **getVertexPos(Node *vertexArr)
{
  Point **vertexPos = malloc(sizeof(Point*) * NUM_NODES);  // Correct memory allocation for the array of pointers

  for (int i = 0; i < NUM_NODES; i++)
  {
    vertexPos[i] = malloc(sizeof(Point));  // Allocate memory for each Point
    vertexPos[i]->x = vertexArr[i].point.x;
    vertexPos[i]->y = vertexArr[i].point.y;
    if(vertexArr[i].point.color == 0)
      vertexPos[i]->color = 1.0f;
    else
      vertexPos[i]->color = 0.0f ;
  }

  for (int i = 0; i < NUM_NODES; i++)
  {
    printf("VertexPos %d\n", i);
    printf("%.2f %.2f\n", vertexPos[i]->x, vertexPos[i]->y);
  }

  return vertexPos;
}

int render(Node *vertexArr, int edgeIndex[NUM_EDGES][2])
{
  GLFWwindow* window;
  float dotSize = 20.0f;
  uint width = 640;
  uint height = 480;
  // get all vertex positions on R²
  Point **vertex = getVertexPos(vertexArr);
  float vertexData[NUM_NODES][3];  

  if (!glfwInit())
    return -1;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(width, height, "bígrafo", NULL, NULL);

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

  // getting the vertex and edge data
  for (int i = 0; i < NUM_NODES; i++) {
    vertexData[i][0] = vertex[i]->x;
    vertexData[i][1] = vertex[i]->y;
    vertexData[i][2] = 0.0f;
  }


  const char *vertexShaderSource = "#version 330 core\n"
    "layout(location = 0) in vec3 aPos;\n"
    "out vec4 LineColor;\n"  

    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos, 1.0);\n"
    "   if (aPos.z == 0.0)\n"
    "     LineColor = vec4(0.0, aPos.z, 1.0, 1.0);\n"  
    "   else\n"
    "     LineColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
    "}\0";

  unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vs, 1, &vertexShaderSource, NULL);
  glCompileShader(vs);

  int  success;
  char infoLog[512];
  glGetShaderiv(vs, GL_COMPILE_STATUS, &success);

  if(!success)
  {
    glGetShaderInfoLog(vs, 512, NULL, infoLog);
    printf("error while compiling vertex shader %s\n", infoLog);
  }

  const char *fragmentShaderSource = "#version 330 core\n"
    "in vec4 LineColor;\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "  FragColor = LineColor;\n"
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

  unsigned int shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vs);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

  if(!success)
  {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    printf("error while linking program %s\n", infoLog);
  }

  // creating a VAO to input on VBO 
  unsigned int VAO, VBO;

  // ----------------------------------------------------------
  // drawing the vertex 
  glGenVertexArrays(1, &VAO); 
  glGenBuffers(1, &VBO); 

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Point) * NUM_NODES, vertexData, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);


  // ----------------------------------------------------------
  // drawing the edges

  unsigned int EBO;
  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * 2 * NUM_EDGES, edgeIndex, GL_STATIC_DRAW);
  

  // ----------------------------------------------------------
  // deleting compiled shaders
  glDeleteShader(vs);
  glDeleteShader(fragmentShader);

  // render loop
  while (!glfwWindowShouldClose(window))
  {
    // input
    // not doint it fow now

    // render
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);

    // draw dots
    glPointSize(dotSize);
    glBindVertexArray(VAO);
    glDrawArrays(GL_POINTS, 0, NUM_NODES);

    // draw edges 
    glLineWidth(2.5f);
    glBindVertexArray(EBO);
    glDrawElements(GL_LINES, NUM_EDGES,GL_UNSIGNED_INT, 0);

    // swap buffers and poll IO events
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // delete all
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteProgram(shaderProgram);
  glfwTerminate();
  return 0;
}