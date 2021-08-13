//
// Created by chris on 2021-08-04.
//

#ifndef HAZELCHAIN_HTTP_H
#define HAZELCHAIN_HTTP_H

#include <string>
#include <iostream>
#include <sstream>
#include <string>
//#include <cpprest/http_client.h>
//#include <cpprest/filestream.h>


using namespace std;
//using namespace web;
//using namespace web::json;
//using namespace web::http;
//using namespace web::http::client;
//using namespace utility;
//using namespace utility::conversions;

namespace util::requests {
    struct Response {
        string url;
        string headers;
        string response;
        long code;

        Response() {
            url = "-1";
            headers = "-1";
            response = "-1";
            code = -1;
        }

        Response(string url,
                 string headers,
                 string response,
                 int code)
                : url(std::move(url)),
                  headers(std::move(headers)),
                  response(std::move(response)),
                  code(code) {
        }
    };

    inline Response GET(const string &url) {
        //        wstring wUrl;
        //        for (size_t i = 0; i < url.length(); ++i) {
        //            wUrl += wchar_t(url[i]);
        //        }
        //
        //        http_client client(wUrl);
        //
        //        client.request(methods::GET).then([](res) {
        //            res.status_code();
        //        });

        return {
                "unimplemented",
                "unimplemented",
                "unimplemented",
                -1
        };
    }
}


#endif //HAZELCHAIN_HTTP_H
