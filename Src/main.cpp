#include "..\Core\Src\corestd.h"
#include "..\Core\Src\Queue.h"
#include "..\Core\Src\ThreadPool.h"

#include <string>
#include <iostream>

using std::cout;
using std::endl;

struct String
{
	std::string str;
};

void a(void* arg)
{
	cout << "wololo";
}

void b(void* arg)
{
	cout << "sdsdsdsds";
}

void c(void* arg)
{
	String* str = (String*)arg;
	cout << str->str;
}

int32 main(int32 argc, char *argv[], char *envp[])
{
	String str;
	str.str = "wwewewewewewewewewewe323223232232";
	
	ThreadPool pool;

	pool.push(&a);
	pool.push(&b);
	pool.push(&c,&str);


	getchar();

	return 0;
}