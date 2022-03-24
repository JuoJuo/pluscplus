#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

struct ShaderProgramSource {
  std::string VertexSource;
  std::string FragmentSource;
};

static ShaderProgramSource ParseShader(const std::string& filepath) {
  std::ifstream stream(filepath);
  enum class ShaderType
  {
    NONE = -1, VERTEX = 0, FRAGMENT = 1,
  };
  std::string line;
  std::stringstream ss[2];

  ShaderType type = ShaderType::NONE;

  while (getline(stream, line)) {
    if (line.find("#shader") != std::string::npos) {
      if (line.find("vertex") != std::string::npos) {
        type = ShaderType::VERTEX;
      }

      else if (line.find("fragment") != std::string::npos) {
        type = ShaderType::FRAGMENT;
      }
    }
    else {
      ss[(int)type] << line << '\n';
    }
  }

  return { ss[0].str(), ss[1].str() };
}
/*
  vertex shader 有多少个vertex就调用多少次。
  fragment shader 目前可以理解为有多少个px就调用多少次。

*/
static unsigned int CompileShader(unsigned int type, const std::string& souce) {
  unsigned int programID = glCreateShader(type);
  const char* src = souce.c_str();
  glShaderSource(programID, 1, &src, nullptr);
  glCompileShader(programID);


  int result;

  glGetShaderiv(programID, GL_COMPILE_STATUS, &result);
  if (result == GL_FALSE) {
    int length;
    glGetShaderiv(programID, GL_INFO_LOG_LENGTH, &length);

    char* message = (char*)_alloca(length * sizeof(char));

    glGetShaderInfoLog(programID, length, &length, message);

    std::cout << "Failed to compile " << (type == GL_VERTEX_ARRAY ? "vertex" : "fragment") << " shader" << std::endl;
    std::cout << message << std::endl;

    glDeleteShader(programID);

    return 0;
  }

  return programID;
}

static int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
  unsigned int program = glCreateProgram();
  unsigned int vsid = CompileShader(GL_VERTEX_SHADER, vertexShader);
  unsigned int fsid = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

  glAttachShader(program, vsid);
  glAttachShader(program, fsid);
  glLinkProgram(program);
  glValidateProgram(program);

  glDeleteShader(vsid);
  glDeleteShader(fsid);

  return program;
}

/*

 opengl是个状态机，简单讲，工作模式就是，我指定一个buffer，指定一个shader，然后告诉你画某个图形。就会绘制了

*/
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

  float positions[8] = {
    -0.5f, -0.5f,
     0.5f, -0.5f,
     0.5f, 0.5f,
    -0.5f, 0.5f
  };

  unsigned int indictes[] = {
    0, 1, 2,
    2, 3, 0
  };

  unsigned int vao;
  GLCall(glGenVertexArrays(1, &vao));
  GLCall(glBindVertexArray(vao));

  VertexBuffer vb(positions, 8 * sizeof(float));

  GLCall(glEnableVertexAttribArray(0));

  GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));

  IndexBuffer ib(indictes, 6);

  ShaderProgramSource source = ParseShader("res/basic.shader");

  unsigned int id_program = CreateShader(source.VertexSource, source.FragmentSource);
  GLCall(glUseProgram(id_program));

  GLCall(int location = glGetUniformLocation(id_program, "u_Color"));
  ASSERT(location != -1);
  GLCall(glUniform4f(location, 0.2f, 0.3f, 0.8f, 1.0f));

  GLCall(glUseProgram(0));
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

  float r = 0.0f;
  float increament = 0.05f;

  while (!glfwWindowShouldClose(window))
  {
    /* Render here */
    GLCall(glClear(GL_COLOR_BUFFER_BIT));

    GLCall(glUseProgram(id_program));
    GLCall(glUniform4f(location, r, 0.3f, 0.8f, 1.0f));

    GLCall(glBindVertexArray(vao));
    ib.Bind();

    GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

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
  GLCall(glDeleteProgram(id_program));
  GLCall(glfwTerminate());
  return 0;
}

