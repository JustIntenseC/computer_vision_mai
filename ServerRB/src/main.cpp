#include <server.h>

int main(int, char**) {
	MainServer srv;
	std::thread th_1{ &MainServer::ServerLow, &srv };
	std::thread th_2{ &MainServer::ShowLines, &srv };
	th_2.join();
	return 0;
}
