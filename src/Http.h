//
// Created by chris on 2021-08-04.
//

#ifndef HAZELCHAIN_HTTP_H
#define HAZELCHAIN_HTTP_H

#include <string>

namespace http {
    using namespace std;

    struct Response {
        string headers;
        string body;
    };

    Response get(const string &url) {
        using namespace curlpp;

    }
}


#endif //HAZELCHAIN_HTTP_H
