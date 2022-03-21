#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

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

  glfwTerminate();
  return 0;
}
