#include <application.h>

int main(int, char**) {
	Application app;
	std::thread th_3{ &Application::process, &app };
	std::thread th_4{ &Application::run, &app };
	th_3.join();
    return 0;
}
