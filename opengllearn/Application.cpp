#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

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


  float positions[6] = {
    -0.5f, -0.5f,
     0.0f, 0.5f,
     0.5f, -0.5f
  };
  unsigned int bufferID;

  /*
    生成几个缓冲区，给一个引用用于返回缓冲区ID
  */
  glGenBuffers(1, &bufferID);

  glBindBuffer(GL_ARRAY_BUFFER, bufferID);

  /* GL_STATIC_DRAW The data store contents will be modified once and used many times. */ 
  glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(6), positions, GL_STATIC_DRAW);

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


  /*
    330 gl shader language 330版本

    core不允许使用过期函数

    layout(location=0)是glVertexAttribPointer第一个参数。表示从第几个点开始接收

    gl_Position是固定的变量名字，接收vec4类型.

    我们注意到此处我们是vec2，赋值的时候还得调用具体的函数转换，所以就直接定义为vec4了
  */

  std::string vertexShader =
    "#version 330 core\n"
    "\n"
    "layout(location = 0) in vec4 position;\n"
    "\n"
    "void main()\n"
    "{\n"
    " gl_Position = position;\n"
    "}\n";


  /*

    color rgba  0-255 映射为  0-1
  */
  std::string fragmentShader =
    "#version 330 core\n"
    "\n"
    "layout(location = 0) out vec4 color;\n"
    "\n"
    "void main()\n"
    "{\n"
    " color = vec4(1.0, 0.0, 0.0, 1.0);\n"
    "}\n";

  unsigned int id_program = CreateShader(vertexShader, fragmentShader);
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
    glDrawArrays(GL_TRIANGLES, 0, 3);


    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
  }
  glDeleteProgram(id_program);
  glfwTerminate();
  return 0;
}
