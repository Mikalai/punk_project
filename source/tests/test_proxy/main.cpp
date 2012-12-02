#include "../../punk_engine.h"

class A
{
public:
	A()
	{
		std::cout << typeid(*this).name() << " created" << std::endl;
	}

	virtual ~A()
	{
		std::cout << typeid(*this).name() << " deleted" << std::endl;
	}

	virtual void print()
	{
		std::cout << "Hello A" << std::endl;
	}
};

class B
{
public:

	B()
	{
		std::cout << typeid(*this).name() << " created" << std::endl;
	}

	virtual ~B()
	{
		std::cout << typeid(*this).name() << " deleted" << std::endl;
	}

	virtual void print()
	{
		std::cout << "Hello B" << std::endl;
	}
};

class C : public A, public B
{
public:
	
	C()
	{
		std::cout << typeid(*this).name() << " created" << std::endl;
	}

	virtual void print()
	{
		//std::cout << "\t"; A::print();
		//std::cout << "\t"; B::print();
		std::cout << "Hello C" << std::endl;
	}

	virtual ~C()
	{
		std::cout << typeid(*this).name() << " deleted" << std::endl;
	}
};

class D : public A
{
public:

	void print()
	{
		std::cout << "Hello world" << std::endl;
	}
};

void Test1()
{
	A a;
	B b;

	a.print();
	b.print();

	std::cout << std::endl;
}

void Test2()
{
	System::Proxy<A> a(new C);
	a->print();

	System::Proxy<B> b(new B);
	b->print();
	
	std::cout << a.GetCount() << std::endl;
}

void Test3()
{
	std::vector<System::Proxy<A>> objects;

	for (int i = 0; i < 10; ++i)
	{
		if (i % 2)
			objects.push_back(System::Proxy<A>(new A));
		else
			objects.push_back(System::Proxy<A>(new C));
	}

	for (int i = 0; i < 10; ++i)
	{
		objects[i]->print();
	}
}

void Test4()
{
	System::Proxy<A> t1(new C);
	System::Proxy<B> t2(new B);
	System::Proxy<D> t3(new D);

	t1->print();
	t2->print();

	t2 = t3;

	t2->print();
}

int main()
{
	Test4();
	return 0;
}