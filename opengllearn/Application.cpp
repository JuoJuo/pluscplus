#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include "Renderer.h"
#include "VertexBufferLayout.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"

int main(void)
{
  GLFWwindow* window;

  /* Initialize the library */
  if (!glfwInit())
    return -1;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
  if (!window)
  {
    glfwTerminate();
    return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);

  /*
     开启垂直同步，就是怕在不断的循环里，闪得太快
  */
  glfwSwapInterval(1);

  GLenum err = glewInit();
  if (GLEW_OK != err)
  {
    /* Problem: glewInit failed, something is seriously wrong. */
    fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
  }
  std::cout << glGetString(GL_VERSION);

  float positions[] = {
    -0.5f, -0.5f, 0.0f, 0.0f,
     0.5f, -0.5f, 1.0f, 0.0f,
     0.5f, 0.5f, 1.0f, 1.0f,
    -0.5f, 0.5f, 0.0f, 1.0f
  };

  unsigned int indictes[] = {
    0, 1, 2,
    2, 3, 0
  };

  GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
  GLCall(glEnable(GL_BLEND));

  VertexArray va;
  VertexBuffer vb(positions, 16 * sizeof(float));

  VertexBufferLayout layout;
  /*
    vb 顶点数据是 位置占几个元素，是float还是别的。
  */
  layout.Push<float>(2);
  layout.Push<float>(2);
  va.AddBuffer(vb, layout);

  IndexBuffer ib(indictes, 6);

  Shader shader("res/basic.shader");
  shader.Bind();
  shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);

  va.Unbind();
  vb.UnBind();
  ib.UnBind();
  shader.Unbind();

  Renderer renderer;

  float r = 0.0f;
  float increament = 0.05f;

  while (!glfwWindowShouldClose(window))
  {
    renderer.Clear();

    shader.Bind();
    shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);

    Texture texture("res/ChernoLogo.png");
    /*
     Bind的时候，插槽是几， shader.SetUniform1i("u_Texture", 0);就是几
    */
    texture.Bind();
    shader.SetUniform1i("u_Texture", 0);

    renderer.Draw(va, ib, shader);

    if (r > 1.0f)
      increament = -0.05f;
    else if (r < 0.0f)
      increament = 0.05f;

    r += increament;
    /* Swap front and back buffers */
    GLCall(glfwSwapBuffers(window));

    /* Poll for and process events */
    GLCall(glfwPollEvents());
  }

  glfwTerminate();
  return 0;
}

