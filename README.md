# coroutine
c++ coroutine demo

![](https://raw.githubusercontent.com/xmh0511/coroutine/master/Stack-frame-and-related-operations.jpg)

因为`swap_context`函数定义完全由汇编实现，所以没有`pushq   %rbp`保存旧的`rbp`这一步，因此`rsp`是指向保存返回地址的内存空间，`0(%rsp)`就是读取`call swap_context`保存的下一条指令的返回地址。
