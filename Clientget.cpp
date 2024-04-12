#include <clientget.h>

int ClientGet::GetCommand() {
    httplib::Client cli("http://127.0.0.1:8080");
    auto res = cli.Post("/command");
    if (res && res->status == 200) {
        if (res->body == "Start") {
            return 1;
        }
        else if (res->body == "Right") {
            return 2;
        }
        else if (res->body == "Left") {
            return 3;
        }
        else if (res->body == "Stop") {
            return 4;
        }
        return 0;
    }
    else {
        std::cerr << "Request failed, error code: " << (res ? res->status : -1) << std::endl;
        return 0;
    }
}
