#include <json.hpp>
#include <thread>
#include "storage/logging/Logger.h"
#include "constants.h"
#include "util/util.h"
#include "node/Server.h"
#include "node/Node.h"

#ifdef _WIN32
#define mkdir(a, b) mkdir(a) // discard 2nd argument on windows
#endif // _WIN32

void loadSettings();

void sync();

void setupDirectories();

void generateDir(const char *name);

int findNodes();

static Server server;

int main(int argc, char **argv) {
    loadSettings();
    sync();

    return 0;
}

void loadSettings() {
    log(constants::logger, info)
            << "Checking for existing settings"
            << std::endl;

    json target = {
            {"ip", util::getIp()},
            {"server_port", 10541},
            {"test_port", 10542},
            {"nodes", {
                    {"fallback", {
                            {
                                    {"ip", "-1"},
                                    {"server_port", 10541},
                                    {"test_port", 10542},
                            }
                    }},
                    {"found", nullptr}
            }}
    };

    json recovered = util::loadJson("settings.json", target);
    if (recovered["nodes"]["fallback"] != target["nodes"]["fallback"])
        recovered["nodes"]["fallback"] = target["nodes"]["fallback"];
    constants::settings = recovered;

    std::ofstream o("settings.json");
    o << constants::settings;
    o.close();
}

void sync() {
    setupDirectories();

    log(constants::logger, info) << "Syncing to other nodes" << std::endl;

    log(constants::logger, info) << "Indexing and checking blocks" << std::endl;

    Node::instance()->initialize();
    Node::sendTo({"10.0.0.139", 10541}, "yeet");
    std::tuple<std::vector<char>, std::tuple<std::string, int>> p = Node::recvFrom(512);

    for (auto i: std::get<0>(p)) {
        std::cout << i << " " << std::endl;
    }
    std::cout << std::endl;

    std::cout << std::get<0>(std::get<1>(p)) << std::endl;
    std::cout << std::get<1>(std::get<1>(p)) << std::endl;
    std::cout << "test" << std::endl;

    //TODO: implement syncing database to other nodes;
}

void setupDirectories() {
    log(constants::logger, info)
            << "Generating directories if they don't exist"
            << std::endl;
    generateDir("blocks");
    generateDir("trees");
}

void generateDir(const char *name) {
    if (!util::exists(name)) {
        if (mkdir(name, 0) != 0) {
            log(constants::logger, info)
                    << "Could not create folder \""
                    << name
                    << "\""
                    << std::endl;
        }
    } else {
        log(constants::logger, info)
                << "Directory \""
                << name
                << "\" already exists"
                << std::endl;
    }
}
