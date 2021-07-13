
#include <iostream>
#include <sys/stat.h>
#include "libs/json/json.hpp"
#include "Block.h"
#include "util.h"

using namespace std;
using json = nlohmann::json;


void setupDirectories();
void generateDir(const char *name);
int findNodes();
void loadSettings();

vector<Block> chain;
json settings;

int main(int argc, char **argv) {
    loadSettings();
    if (!util::contains(argc, argv, "-nosync")) sync();

    return 0;
}

/**
 * Synchronises this node and it's data to other nodes and their data
 */
void sync() {
    cout << "SYNC-> Generating directories if they don't exist" << endl;
    setupDirectories();
    cout << "SYNC-> Indexing and checking blocks" << endl;
    string genesis = util::generateGenesisHash();
    cout << "SYNC-> Genesis block hash: " << genesis << endl;
    cout << "SYNC-> syncing to other nodes" << endl;
    cout << "SYNC-> connected to " << findNodes() << " nodes" << endl;


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
            cout << "ERROR-> could not create folder \"" << name << '\"' << endl;
        }
    } else {
        cout << "NOTICE-> directory \"" << name << "\" already exists" << endl;
    }
}

void loadSettings() {
    settings["ip"] = util::getIp();
}
