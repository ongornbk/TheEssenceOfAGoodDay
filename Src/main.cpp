#include "..\Core\Src\corestd.h"
#include "..\Core\Src\Queue.h"
#include "..\Core\Src\Thread.h"

#include <iostream>

using std::cout;
using std::endl;

void b(void* arg)
{
	Queue<int32>* queue = (Queue<int32>*)(arg);
	for (Queue<int32>::QueueElement* i = queue->head(); i != nullptr; i = i->next)
	{
		cout << i->data << endl;
		getchar();
	}
}

void a(Queue<int32> & queue)
{
	if (queue.empty())
	cout << "Queue : front = nullptr and size = 0" << endl;
	else
	cout << "Queue : front = " << queue.front() << " and size = " << queue.size() << endl;
}

int32 main(int32 argc, char *argv[], char *envp[])
{

	
		Queue<int32> queue;
		queue.push(5);
		queue.push(3);
		queue.push(7);
		queue.push(3);
		queue.push(11);

		Thread t(b, NULL, &queue);

		cout << "wooldsd";

		t.join();

		cout << "dfdf";
	
	getchar();
	getchar();

	return 0;
}