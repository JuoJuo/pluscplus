vertex array buffer 

index array buffer 因为所有的东西都是三角形组成的，如果我们要画矩形就必须要两个三角形。
如果只使用vertex array buffer，那就得6个点的位置数据，也就是12个float。主要是有冗余的数据位置
，所以我们加入index array buffer，指定从哪个索引点，画到哪个。注意，也是三个一组
。


特别的对于vertext array的绑定，实际上需要三行代码(使用vao后就不用每次设置这三行了，直接bindVertexArray就行了)
glBindBuffer
glEnableVertexAttribArray
glVertexAttribPointer

index array buffer就一行代码glBindBuffer就完了


默认使用的是兼容性opengl 配置文件GLFW_OPENGL_COMPAT_PROFILE，内部会自己给创建一个vertex array object
如果使用GLFW_OPENGL_CORE_PROFILE，就得手动创建绑定一个。
至于为什么，好像是

GL_ARRAY_BUFFER就是我们glGenVertexArrays生成的那个

glBindBuffer(GL_ARRAY_BUFFER, bufferID)
glEnableVertexAttribArray(0)

这句才实际绑定了这个buffer跟GL_ARRAY_BUFFER，所谓绑定好像是说GL_ARRAY_BUFFER[0（第一个参数）]就对应这个buffer，
别的可能是1 2 3 4
glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0)



- VertexBuffer就是自己生成一个vertexbuffer 并且绑定， 然后设置buffer数据的
- IndexBuffer就是自己生成一个IndexBuffer 并且绑定， 然后设置索引数据，跟索引（顶点）个数的。
- layout就是记录创建的vertexbuffer的数据布局的。
（在va的第几个索引，元素一组有几个。元素类型。是否需要GPU帮把数据转到0-1之间，占过少个字节，以及每个vertex之间偏移量）
