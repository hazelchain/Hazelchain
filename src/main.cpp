
#include <sys/stat.h>
#include <json.hpp>
#include "Block.h"
#include "storage/logging/Logger.h"

#ifdef _WIN32
#define mkdir(a, b) mkdir(a) // discard 2nd argument on windows
#endif // _WIN32

using namespace std;
using json = nlohmann::json;

void sync(Logger &logger);

void setupDirectories(Logger &logger);

void generateDir(const char *name, Logger &logger);

int findNodes();

void loadSettings(Logger &logger);

vector<Block> chain;
json settings = {};

int main(int argc, char **argv) {
    Logger logger(
            util::concat(
                    util::currentTime("[%d-%m-%y  %H:%M:%S] "),
                    "-log.txt"
            ),
            std::cout
    );

    loadSettings(logger);
    if (!util::contains(argc, argv, "-nosync")) sync(logger);

    return 0;
}

void sync(Logger &logger) {
    log(logger, info)
            << "Generating directories if they don't exist"
            << '\n';

    setupDirectories(logger);

    log(logger, info)
            << "Indexing and checking blocks"
            << '\n';

    log(logger, info)
            << "Genesis block _hash: "
            << settings["genesis_hash"]
            << '\n';

    log(logger, info)
            << "syncing to other nodes"
            << '\n';

    log(logger, info)
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

void setupDirectories(Logger &logger) {
    generateDir("blocks", logger);
    generateDir("trees", logger);
}

void generateDir(const char *name, Logger &logger) {
    if (!util::exists(name)) {
        if (mkdir(name, 0) != 0) {
            log(logger, info)
                    << "Could not create folder \""
                    << name
                    << "\"";
        }
    } else {
        log(logger, info)
                << "Directory \""
                << name
                << "\" already exists";
    }
}

void loadSettings(Logger &logger) {
    log(logger, info) << "Checking for existing settings" << '\n';

    json recovered = util::loadJson("settings.json", {
            {"ip",           util::getIp()},
            {"server_port",  10541},
            {"test_port",    10542},
            {"api_port",     10543},
            {"genesis_hash", util::generateGenesisHash()},
            {"nodes",        {
                                     {"fallback", {"-1"}},
                                     {"found", nullptr}
                             }}
    });
    settings = recovered;

    ofstream o("settings.json");
    o << settings;
    o.close();
}
