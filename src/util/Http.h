//
// Created by chris on 2021-08-04.
//

#ifndef HAZELCHAIN_HTTP_H
#define HAZELCHAIN_HTTP_H

#include <string>
#include <utility>
#include <json.hpp>
#include <curl/curl.h>

using namespace std;

namespace requests {
    using json = nlohmann::json;

//    size_t writeFunction(void *ptr, size_t size, size_t nmemb,
//                         string *data) {
//        data->append((char *) ptr, size * nmemb);
//        return size * nmemb;
//    }

    struct Response {
        string url;
        string headers;
        string response;
        int code;
        double elapsed;

        Response() {
            url = "-1";
            headers = "-1";
            response = "-1";
            code = -1;
            elapsed = -1;
        }

        Response(string url,
                 string headers,
                 string response,
                 int code,
                 double elapsed)
                : url(std::move(url)),
                  headers(std::move(headers)),
                  response(std::move(response)),
                  code(code),
                  elapsed(elapsed) {
        }
    };

    Response get(const string &url) {
        auto curl = curl_easy_init();
        if (curl) {
            Response out;
            out.url = url;

            curl_easy_setopt(curl, CURLOPT_URL, &url);
            curl_easy_setopt(curl, CURLOPT_USERAGENT, "curl/7.42.0");

//            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &out.response);
            curl_easy_setopt(curl, CURLOPT_HEADERDATA, &out.headers);

            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &out.code);
            curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &out.elapsed);
            curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &url);

            curl_easy_perform(curl);
            curl_easy_cleanup(curl);
            curl = nullptr;
            return out;
        }
        return {"-1", "-1", "-1", -1, -1};
    }
}


#endif //HAZELCHAIN_HTTP_H
