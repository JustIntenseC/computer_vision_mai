#pragma once
#include <recogniser.h>
#include <memory>

class Application {
private:
	std::shared_ptr<Recogniser> recogniser;
public:
	Application(std::shared_ptr<Recogniser> rec) : recogniser(rec) {}

	int process();

	void run();

	std::string show(Table frame);
};
