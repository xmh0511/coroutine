#include <iostream>
#include <cstring>
enum RegIndex{
	Ret = 0,  //ret address
	Rdi = 1,  //param1
	Rsi = 2,  //param2
	Rcx = 3,  //params3
	Rdx = 4,  //params4
	R8 = 5,   //params5
	R9 = 6,    //params6
	Rbx = 7,
	Rbp = 8,  //stack base ptr
	Rsp = 9,  //stack ptr
	R12 = 10,
	R13 = 11,
	R14 = 12,
	R15 = 13
};
struct context{
	void* regs[14];
	char* stack;
	std::size_t stack_size;
};

void swap_context(context* ctx0,context* ctx1) asm("swap_context");

void swap_ctx(context* ctx0,context* ctx1){
	swap_context(ctx0,ctx1);
}
context current;
void CoroutinFunc(context* ctx0,void*){
	//std::cout<<(unsigned long)&ctx0<<std::endl;
	std::cout<<"in CoroutinFunc"<<std::endl;
	swap_ctx(ctx0,&current);
}

void call(){
}

int main(){
	int  src = 1024;
	context ctx;
	memset(&ctx,0,sizeof(context));
	ctx.stack = (char*)malloc(1024*128);
	ctx.stack_size = 1024*128;
	memset(ctx.stack,0,ctx.stack_size);
	ctx.regs[RegIndex::Ret] = (void*)&CoroutinFunc;
	char* sp = ctx.stack + ctx.stack_size;
	ctx.regs[RegIndex::Rbp] = 0;
	ctx.regs[RegIndex::Rsp] = (char*)((unsigned long)sp & -16LL) - 8;//保奇偶性  pushq  ebp  地址为平台寄存器位数的偶数倍
	ctx.regs[RegIndex::Rdi] = (void*)&ctx;
	ctx.regs[RegIndex::Rsi] = (void*)0;
	memset(&current,0,sizeof(context));
	swap_ctx(&current,&ctx);
	std::cout<<"end "<<src<<std::endl;
}
