#ifndef CPR_STATUS_H
#define CPR_STATUS_H

#include <chrono>
#include <cstdint>
#include <functional>
#include <iostream>
#include <curl/curl.h>

namespace cpr {
    typedef int (*StatusCallback)(void *clientp, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal, curl_off_t ulnow);

    class Progress {
    public:
        Progress(const StatusCallback& callback) : function(callback), data(nullptr) {}


        Progress(const StatusCallback& callback, void* data) : function(callback), data(data) {}

        const StatusCallback& function;
        void* data;
    };

} // namespace cpr
#endif //CPR_STATUS_H
