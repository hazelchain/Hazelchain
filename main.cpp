
#include <iostream>
#include <dirent.h>
#include <sys/stat.h>
#include "lib/json/json.hpp"
#include "Block.h"
#include "storage/tree/TransactionTree.h"

using namespace std;
using json = nlohmann::json;

void setupDirectories();
void generateDir(const char *name);


vector<Block> chain;

int main() {
    sync();

    return 0;
}

void sync() {
    setupDirectories();


    //TODO: implement syncing database to other nodes;
}

void setupDirectories() {
    generateDir("blocks");
    generateDir("trees");
}

void generateDir(const char *name) {
    if (!util::exists(name) && mkdir(name, 0)) {
        cout << "ERROR: could not create folder \"" << name << '\"' << endl;
    }
}
