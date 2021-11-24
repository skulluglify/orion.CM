#include<iostream>

#define LOG(x) std::cout << x << std::endl;

class Parent {

	private:

		const char* name = "udin";
		
	public:

		virtual void print(void) {

			LOG(name)
		}

		friend void printName(const Parent& parent);
};

class Children: public Parent {

	private:

		const char* name = "syafiq";
		
	public:

		void print(void) override {

			LOG(name)
		}

		friend void printName(const Children& children);
};

void printName(const Parent& parent) {

	LOG(parent.name)
}


void printName(const Children& children) {

	LOG(children.name)
}

int main(const int argc, const char** argv) noexcept {

	(void)argc;
	(void)argv;

	Parent parent;
	Children children;
	parent.print();
	children.print();
	printName(parent);
	printName(children);

	return 0;
}
