#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <stdio.h>
#include <stdlib.h>

#include "window.h"

Point **getVertexPos(Node *vertexArr)
{
  Point **vertexPos = malloc(sizeof(Point*) * NUM_NODES);  // Correct memory allocation for the array of pointers

  for (int i = 0; i < NUM_NODES; i++)
  {
    vertexPos[i] = malloc(sizeof(Point));  // Allocate memory for each Point
    vertexPos[i]->x = vertexArr[i].point.x;
    vertexPos[i]->y = vertexArr[i].point.y;
  }

  for (int i = 0; i < NUM_NODES; i++)
  {
    printf("VertexPos %d\n", i);
    printf("%.2f %.2f\n", vertexPos[i]->x, vertexPos[i]->y);
  }

  return vertexPos;
}

Edge **getEdges(Node *vertexArr)
{
  Edge **edges = malloc(sizeof(Edge*) * NUM_EDGES); 

  for (int i = 0; i < NUM_EDGES; i++)
  {
    edges[i] = malloc(sizeof(Edge));  // Allocate memory for each Edge
    edges[i]->from->point.x= vertexArr[i].point.x;
    edges[i]->from->point.y= vertexArr[i].point.y;
  }

  for (int i = 0; i < NUM_EDGES; i++)
  {
    printf("Edge %d\n", i);
    printf("from: %.2f %.2f\n", edges[i]->from->point.x, edges[i]->to->point.x);
    printf("to: %.2f %.2f\n", edges[i]->from->point.y, edges[i]->to->point.y);
  }

  return edges;
}


int render(Node *vertexArr, Edge *edgeArr)
{
  GLFWwindow* window;

  if (!glfwInit())
    return -1;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  uint width = 640;
  uint height = 480;

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

  // get all vertex positions on R²
  Point **vertex = getVertexPos(vertexArr);

  glViewport(0, 0, width, height);

  // creating a VAO to input on VBO 
  unsigned int VAO[2], VBO[2];
  glGenVertexArrays(1, &VAO[0]); 
  glGenBuffers(1, &VBO[0]); 

  glBindVertexArray(VAO[0]);
  glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);


  float vertexData[NUM_NODES][2];  

  for (int i = 0; i < NUM_NODES; i++) {
    vertexData[i][0] = vertex[i]->x;
    vertexData[i][1] = vertex[i]->y;
  }

  glBufferData(GL_ARRAY_BUFFER, sizeof(Point) * NUM_NODES, vertexData, GL_STATIC_DRAW);

  const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);\n"
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
    "   FragColor = vec4(0.0f, 0.5f, 0.2f, 1.0f);\n"
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
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

  if(!success)
  {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    printf("error while linking program %s\n", infoLog);
  }



  // the probably most important part
  // first param: location of the vertex attribute (like location = 0 in the vertex shader)
  // second param: size of the vertex attribute (vec2 has size 2 or our Point struct)
  // third param: type of the data
  // fourth param: if the data should be normalized
  // fifth param: stride (space between consecutive vertex attributes)
  // sixth param: offset of the first component of the first vertex attribute
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  float dotSize = 20.0f;

  // ----------------------------------------------------------
  // drawing the edges

  float edgeData[NUM_EDGES][4];
  
  for (int i = 0; i < NUM_EDGES; i++) {
    edgeData[i][0] = edgeArr[i].from->point.x;
    edgeData[i][1] = edgeArr[i].from->point.y;
    edgeData[i][2] = edgeArr[i].to->point.x;
    edgeData[i][3] = edgeArr[i].to->point.y;
    printf("Edge %d\n", i);
    printf("from: %.2f %.2f\n", edgeData[i][0], edgeData[i][1]);
    printf("to: %.2f %.2f\n", edgeData[i][2], edgeData[i][3]);
  }
  
  glGenVertexArrays(1, &VAO[1]);
  glGenBuffers(1, &VBO[1]);
  glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);

  glBufferData(GL_ARRAY_BUFFER, sizeof(edgeData), edgeData, GL_STATIC_DRAW);

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(1);

  // ----------------------------------------------------------
  // deleting compiled shaders
  glDeleteShader(vertexShader);
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
    glBindVertexArray(VAO[0]);
    glDrawArrays(GL_POINTS, 0, NUM_NODES);

    // draw edges 
    glBindVertexArray(VAO[1]);
    glDrawArrays(GL_LINE_LOOP, 1, NUM_EDGES);

    // swap buffers and poll IO events
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
