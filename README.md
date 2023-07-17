# coroutine
c++ coroutine demo

![](https://raw.githubusercontent.com/xmh0511/coroutine/master/Stack-frame-and-related-operations.jpg)

因为`swap_context`函数定义完全由汇编实现，所以没有如下步骤
> 1.`pushq   %rbp`保存旧的`rbp`这一步   
> 2.让新栈的栈底指针`rbp`设置为当前的`rsp`   
> 3.设置`rsp`指向新栈的栈顶   
>
因此`rsp`是指向保存返回地址的内存空间，`0(%rsp)`就是读取`call swap_context`保存的下一条指令的返回地址(即，return address)。

````cpp
	ctx.stack = (char*)malloc(1024*128);
	ctx.stack_size = 1024*128;
	 // .
	 // .
	 // .
	char* sp = ctx.stack + ctx.stack_size;
	ctx.regs[RegIndex::Rsp] = (char*)((unsigned long)sp & -16LL) - 8;//保奇偶性  pushq  ebp  地址为平台寄存器位数的偶数倍，内存对齐
````
`sp`指向分配的内存的空间的末尾地址`Addr`(高位地址，因为栈空间的增长方向是高地址->低地址), `& -16LL`的操作抹去了低4位的数值变成`0000`, 使得`Addr2`(即，`Addr & -16LL`的结果)的值16的整数倍。即是`8`的偶数倍，即`2n*8`, 再减去`8`的结果为`(2n-1)*8`(保存为rsp指向地址),因为后续的函数调用中`pushq %rbp`的操作会记录旧`rbp`并且让`rsp - 8`(向低地址方向变化)，因此`rsp`在操作后的实际指向位置就是`(2n - 2)*8`即`8`的偶数倍(以及16的整数倍)。
