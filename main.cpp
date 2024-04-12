#include <server.h>
#include <application.h>

int main(int, char**) {
	MainServer srv;
	std::shared_ptr<Recogniser> Rec = std::make_shared<FooRecogniser>(6, 6);
	Application app(Rec);
	std::thread th_1{ &MainServer::ServerLow, &srv };
	std::thread th_2{ &MainServer::ShowLines, &srv };
	std::thread th_3{ &Application::process, &app };
	std::thread th_4{ &Application::run, &app };
	th_3.join();
    return 0;
}
