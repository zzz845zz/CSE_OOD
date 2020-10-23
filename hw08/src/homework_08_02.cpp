#include <iostream>

class Strategy {
public:
	virtual ~Strategy() {}
	virtual int doOperation(int num1, int num2) = 0;
};

class OperationAdd: public Strategy {
public:
	int doOperation(int num1, int num2) override {
		return num1 + num2;
	}
};

class OperationMultiply: public Strategy {
public:
	int doOperation(int num1, int num2) override {
		return num1 * num2;
	}
};

class OperationSubstract: public Strategy {
public:
	int doOperation(int num1, int num2) override {
		return num1 - num2;
	}
};

class Context {
	private:
		Strategy* strategy;
	public:
		Context(Strategy* str) {
			if(strategy) {
				delete strategy;
			}
			this->strategy = str;
		}
		~Context() {
			delete this->strategy;
		}

		void setStrategy(Strategy* str) {
			delete this->strategy;
			this->strategy = str;
		}

		int executeStrategy(int num1, int num2) const {
			return strategy->doOperation(num1, num2);
		}
};

int main(){
	Context* context = new Context(new OperationAdd);
	std::cout << "10 + 5 = " << context->executeStrategy(10, 5) << std::endl;
	context->setStrategy(new OperationSubstract);
	std::cout << "10 - 5 = " << context->executeStrategy(10, 5) << std::endl;
	context->setStrategy(new OperationMultiply);
	std::cout << "10 * 5 = " << context->executeStrategy(10, 5) << std::endl;

	delete context;
}