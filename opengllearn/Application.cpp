#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>

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

  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
  if (!window)
  {
    glfwTerminate();
    return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);

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


  unsigned int bufferID;

  /*
    生成几个缓冲区，给一个引用用于返回缓冲区ID
  */
  glGenBuffers(1, &bufferID);

  glBindBuffer(GL_ARRAY_BUFFER, bufferID);

  /* GL_STATIC_DRAW The data store contents will be modified once and used many times. */ 
  glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), positions, GL_STATIC_DRAW);

  /* 要让指定的顶点属性生效，的手动调用enable。并传入从第几个索引开始enable */
  glEnableVertexAttribArray(0);
  /*
  从第几个索引开始，
  几个元素表示位置属性，
  数据类型是什么，
  是否让opengl把点映射到0-1之内，
  以及每个vertex的长度。（不一定vertex只有位置，还有纹理法线之类的）只不过demo中只有位置，刚起步嘛，简单点。
  第几个字节的位置开始就是纹理法线之类的数据。这里没有纹理法线数据，就写0.
  */
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);


  unsigned int ibo;
  glGenBuffers(1, &ibo);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

  /*
    跟vertex缓冲区差不多。都是要指定数据占的大小。数据的指针，以及偏移量或者静态绘制还是动态绘制
    索引缓冲区就得传GL_ELEMENT_ARRAY_BUFFER， indictes里所有数据占的空间，indictes指针， indictes里偏移量
  */
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indictes, GL_STATIC_DRAW);


  ShaderProgramSource source = ParseShader("res/basic.shader");

  unsigned int id_program = CreateShader(source.VertexSource, source.FragmentSource);
  glUseProgram(id_program);
  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window))
  {
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT);

    /*
      缓冲区bind了，数据指定了，发出画的指令了，因为要求是一维数组（高性能），所以得指定从第几个索引开始画
      以及有几个点
    */
    // glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
  }
  glDeleteProgram(id_program);
  glfwTerminate();
  return 0;
}
