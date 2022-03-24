#pragma once
#include "VertexBuffer.h";

class VertexArray {
private:
  VertexArray();
  ~VertexArray();

public:
  void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout);
};
