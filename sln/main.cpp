#include "tqueue.h"

int main()
{
	TStack<int> a;
	TStack<int> b(3);
	TStack<int> b1(b);
	TStack<int> c = b;
	if (c == b)
	{
		if (b1 == b)
		{
			std::cout << "ok\n";
		}
	}
	TStack<int> s(3);
	s.Push(1);
	s.Push(2);
	TStack<int> s2(s);
	std::cout << (s == s2);
	s.Pop();
	int val = s2.Pop();
	std::cout << val;
	int val2 = s2.Pop();
	std::cout << val2;
	b.Push(3);
	b.Push(3);
	b.Push(3);
	b.Pop();
	int** data = new int*[5];
	data[0] = new int (3);
	data[1] = new int (2);
	for (int i = 2; i < 5; i++)
	{
		data[i] = nullptr;
	}
	TStack<int> d(data, 5);

	TStack<int> s5(2);
	s5.Push(1);
	s5.Push(2);
	s5.Resize(4);
	s5.Push(3);
	std::cout << s5 << '\n';
	TQueue<int> qa;
	TQueue<int> qb(3);
	TQueue<int> qb1(qb);
	TQueue<int> qc = qb;
	if (qc == qb)
	{
		if (qb1 == qb)
		{
			std::cout << "ok\n";
		}
	}
	qb.AddToTail(2);
	qb.AddToTail(3);
	qb.AddToTail(4);
	qb.RemoveFromHead();
	qb.AddToTail(5);
	std::cout << qb << '\n';
	return 0;
}