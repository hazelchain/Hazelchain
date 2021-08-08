
#include <sys/stat.h>
#include <json.hpp>
#include "Block.h"
#include "storage/logging/Logger.h"
#include "util/util.h"

#ifdef _WIN32
#define mkdir(a, b) mkdir(a) // discard 2nd argument on windows
#endif // _WIN32

using namespace std;
using json = nlohmann::json;

void sync();

void setupDirectories();

void generateDir(const char *name);

int findNodes();

void loadSettings();

vector<Block> chain;
json settings;
static Logger *logger;

int main(int argc, char **argv) {
    loadSettings();
    logger = new Logger(util::concat(
            util::currentTime("[%d-%m-%y  %H:%M:%S] "), "-log.txt"));
    if (util::contains(argc, argv, "-nolog")) logger->bLog = false;
    if (util::contains(argc, argv, "-noshow")) logger->bShow = false;
    if (!util::contains(argc, argv, "-nosync")) sync();

    return 0;
}

/**
 * Synchronises this node and it's data to other nodes and their data
 */
void sync() {
    logger->log("Generating directories if they don't exist");
    setupDirectories();
    logger->log("Indexing and checking blocks");
    logger->log({"Genesis block hash: ", settings["genesis_hash"]});
    logger->log("syncing to other nodes");
    logger->log({"connected to ", util::to_string<int>(findNodes()), " other nodes"});


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

/**
 * Generates a directory based on the name given if the stated directory does not exist.
 * @param name The name of the directory
 */
void generateDir(const char *name) {
    if (!util::exists(name)) {
        if (mkdir(name, 0) != 0) {
            logger->log({"Could not create folder \"", name, "\""});
        }
    } else {
        logger->log({"Directory \"", name, "\" already exists"});
    }
}

void loadSettings() {
    ifstream ifs("settings.json");
    if (ifs.good()) {
        settings = json::parse(ifs);
        return;
    }
    settings = {
            {"ip",           util::getIp()},
            {"server_port",  10541},
            {"test_port",    10542},
            {"api_port",     10543},
            {"genesis_hash", util::generateGenesisHash()},
            {"nodes",        -1}
    };
    ofstream o("settings.json");
    o << settings;
    o.close();
}
