//
// Created by chris on 2021-08-12.
//

#ifndef HAZELCHAIN_CONSTANTS_H
#define HAZELCHAIN_CONSTANTS_H

#include <iostream>
#include "util/util.h"
#include "util/strutil.h"

using json = nlohmann::json;

/* ****************** BAD PRACTICE, PLEASE DON'T DO THIS!! ****************** */
namespace constants {
    inline static Logger logger(
            util::concat(
                    util::currentTime("[%d-%m-%y  %H:%M:%S] "),
                    "-log.txt"
            ),
            std::cout
    );

    inline static json settings = {};
}

#endif //HAZELCHAIN_CONSTANTS_H
