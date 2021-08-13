//
// Created by chris on 2021-08-12.
//

#ifndef HAZELCHAIN_CONSTANTS_H
#define HAZELCHAIN_CONSTANTS_H

namespace constants {
    using json = nlohmann::json;

    Logger logger(
            util::concat(
                    util::currentTime("[%d-%m-%y  %H:%M:%S] "),
                    "-log.txt"
            ),
            std::cout
    );

    json settings = {};
}

#endif //HAZELCHAIN_CONSTANTS_H
