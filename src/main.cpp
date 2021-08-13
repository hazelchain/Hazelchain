#include <json.hpp>
#include "storage/logging/Logger.h"
#include "constants.h"

#ifdef _WIN32
#define mkdir(a, b) mkdir(a) // discard 2nd argument on windows
#endif // _WIN32

void loadSettings();

void sync();

void setupDirectories();

void generateDir(const char *name);

int findNodes();


int main(int argc, char **argv) {
    loadSettings();
    if (!util::contains(argc, argv, "-nosync")) sync();

    return 0;
}

void loadSettings() {
    log(constants::logger, info) << "Checking for existing settings" << '\n';

    json target = {
            {"ip",           util::getIp()},
            {"server_port",  10541},
            {"test_port",    10542},
            {"api_port",     10543},
            {"genesis_hash", util::generateGenesisHash()},
            {"nodes",        {
                                     {"fallback", {"-1"}},
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
    log(constants::logger, info)
            << "Generating directories if they don't exist"
            << '\n';

    setupDirectories();

    log(constants::logger, info)
            << "Indexing and checking blocks"
            << '\n';

    log(constants::logger, info)
            << "Genesis block _hash: "
            << constants::settings["genesis_hash"]
            << '\n';

    log(constants::logger, info)
            << "syncing to other nodes"
            << '\n';

    log(constants::logger, info)
            << "connected to "
            << util::to_string<int>(findNodes())
            << " other nodes"
            << '\n';

    //TODO: implement syncing database to other nodes;
}

int findNodes() {
    // TODO: implement finding nodes;
    return -1;
}

void setupDirectories() {
    generateDir("blocks");
    generateDir("trees");
}

void generateDir(const char *name) {
    if (!util::exists(name)) {
        if (mkdir(name, 0) != 0) {
            log(constants::logger, info)
                    << "Could not create folder \""
                    << name
                    << "\"";
        }
    } else {
        log(constants::logger, info)
                << "Directory \""
                << name
                << "\" already exists";
    }
}
