//
// Created by chris on 2021-08-04.
//

#ifndef HAZELCHAIN_HTTP_H
#define HAZELCHAIN_HTTP_H

#include <string>
#include <utility>
#include <json.hpp>
#include <cpr/cpr.h>

using json = nlohmann::json;

namespace http {
    using namespace std;

    struct Response {
        Response(json headersIn, json bodyIn)
                : headers(std::move(headersIn)),
                  body(std::move(bodyIn)) {
        }

        json headers{};
        json body{};
    };

    Response get(const string &url) {
        cpr::Response rep = cpr::Get(cpr::Url{url});
        return {rep.header, json(rep.text)};
    }
}


#endif //HAZELCHAIN_HTTP_H
