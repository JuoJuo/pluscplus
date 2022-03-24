vertex array buffer 

index array buffer 因为所有的东西都是三角形组成的，如果我们要画矩形就必须要两个三角形。
如果只使用vertex array buffer，那就得6个点的位置数据，也就是12个float。主要是有冗余的数据位置
，所以我们加入index array buffer，指定从哪个索引点，画到哪个。注意，也是三个一组
。


特别的对于vertext array的绑定，实际上需要三行代码
glBindBuffer
glEnableVertexAttribArray
glVertexAttribPointer

index array buffer就一行代码glBindBuffer就完了
