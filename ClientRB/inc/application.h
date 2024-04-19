#pragma once
#include <recogniser.h>
#include <thread>
#include <memory>

class Application {
private:
	std::shared_ptr<Recogniser> recogniser;
public:
	Application() : recogniser() {
		std::shared_ptr<Recogniser> Rec = std::make_shared<FooRecogniser>(6, 6);
		recogniser = Rec;
	}

	int process();

	void run();

	std::string show(Table frame);
};
