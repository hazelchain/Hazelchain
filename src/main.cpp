#include <json.hpp>
#include "storage/logging/Logger.h"
#include "constants.h"
#include "util/util.h"
#include "node/server.h"
#include "node/Packet.h"

#ifdef _WIN32
#define mkdir(a, b) mkdir(a) // discard 2nd argument on windows
#endif // _WIN32

void loadSettings();

void sync();

void setupDirectories();

void generateDir(const char *name);

int findNodes();

static node::Server server;

int main(int argc, char **argv) {
    loadSettings();
    if (!util::contains(argc, argv, "-nosync")) sync();

    return 0;
}

void loadSettings() {
    log(constants::logger, info)
            << "Checking for existing settings"
            << logger::endl;

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
    log(constants::logger, info)
            << "Generating directories if they don't exist"
            << logger::endl;

    setupDirectories();

    std::string gen = util::generateGenesisHash();
    log(constants::logger, info)
            << "Genesis block hash: "
            << gen
            << logger::endl;

    log(constants::logger, info)
            << "Syncing to other nodes"
            << logger::endl;

    log(constants::logger, info)
            << "Starting node server on port "
            << (std::int32_t) constants::settings["server_port"]
            << logger::endl;

    server = node::Server("server", constants::settings["server_port"]);
    server.run();

    log(constants::logger, info)
            << "Indexing and checking blocks"
            << logger::endl;

    //TODO: implement syncing database to other nodes;
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
                    << "\""
                    << logger::endl;
        }
    } else {
        log(constants::logger, info)
                << "Directory \""
                << name
                << "\" already exists"
                << logger::endl;
    }
}

int findNodes() {
    int count = 0;
    {
        std::vector<int> searched;
        do {
            size_t i = std::rand() % constants::settings["nodes"]["fallback"].size() + 1;
            if (std::find(searched.begin(), searched.end(), i) != searched.end()) continue;
            // add node if available

        } while (1 == 2); // temporary fix
    }

    if (!constants::settings["nodes"]["found"].is_null()) {
        for (auto i = constants::settings["nodes"]["found"].begin();
             i < constants::settings["nodes"]["found"].end();
             ++i) {
            // if connected add to
            // TODO: connect to all found nodes
        }
    }
    return count == 0 ? -1 : count;
}
