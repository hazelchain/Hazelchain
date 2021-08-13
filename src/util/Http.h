//
// Created by chris on 2021-08-04.
//

#ifndef HAZELCHAIN_HTTP_H
#define HAZELCHAIN_HTTP_H

#include <string>
#include <iostream>
#include <sstream>
#include <string>

namespace util::requests {
    struct Response {
        std::string url;
        std::string headers;
        std::string response;
        long code;

        Response() {
            url = "-1";
            headers = "-1";
            response = "-1";
            code = -1;
        }

        Response(std::string url,
                 std::string headers,
                 std::string response,
                 int code)
                : url(std::move(url)),
                  headers(std::move(headers)),
                  response(std::move(response)),
                  code(code) {
        }
    };

    inline Response GET(const std::string &url) {
        return {
                "unimplemented",
                "unimplemented",
                "unimplemented",
                -1
        };
    }
}


#endif //HAZELCHAIN_HTTP_H
