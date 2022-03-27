#include "VertexBuffer.h"
#include "Renderer.h"
#include<GL/glew.h>

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{

  GLCall(glGenBuffers(1, &m_RendererID));

  GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
  /*
    顶点数据文档说明了，就用GL_ARRAY_BUFFER， data占多少字节， GL_STATIC_DRAW 是数据是静态，还是动态，还是只改几次
  */
  GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
  GLCall(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::Bind() const
{
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::UnBind() const
{
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}


