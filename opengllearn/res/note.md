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


- 纹理 
  - 就是，在一个缓冲区中，有rgba或者别的格式的一堆颜色定义（一般是从一张图片读取），
  - 然后会给vetextbuffer添加纹理的一些值（目前不知道是干什么的）
  - vertex shader就可以获取到，fragmentshader就可以利用一些函数，做颜色像素取样。最终呈现画面
  - 搬砖方面，发现shader里的layout(location = 1) in vec2 textCoord;好像是在glVertexAttribPointer第一个参数是几，就是对应的哪些数据



- 混合 opengl默认是不处理透明的。也就是不混合颜色的。  定义：就是如何决定input的颜色跟已经存在的颜色重叠后的结果

  - eg: output: (1,1,1,0.5) --output就认为是重叠的时候，放上面的颜色吧
        destination: (1,0,1,1)

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)
        解释： 每个src通道 * src的透明通道 + 对应的每个目的通道 * 1 - src的透明通道

        R = 1 * 0.5 + 1 * (1-0.5) = 1
        G = 1 * 0.5 + 0 * (1-0.5) = 0.5
        B = 1 * 0.5 + 1 * (1-0.5) = 1
        A = 0.5 * 0.5 + 1 * (1-0.5) = 0.75

