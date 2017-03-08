#include <gtest/gtest.h>

#include <string>
#include <iostream>

#include <cpr/cpr.h>

#include "server.h"

using namespace cpr;

static Server *server = new Server();
auto base = server->GetBaseUrl();

TEST(AlternatingTests, StatusTest) {
    auto url = Url{base + "/progress_request.html"};
    Session session;
    session.SetUrl(url);

    {
        session.SetProgress(cpr::Progress([](void* ptr, curl_off_t cur, curl_off_t max, curl_off_t x, curl_off_t y){
            std::cout << "X: " << ptr << " - " << cur << " - " << max << " - " << x << " - " << y << std::endl;
            return 0;
        }));

        auto response =  session.Get();
        EXPECT_EQ(1024*1024, response.text.length());
        EXPECT_EQ(url, response.url);
        EXPECT_EQ(200, response.status_code);
        EXPECT_EQ(ErrorCode::OK, response.error.code);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::AddGlobalTestEnvironment(server);
    return RUN_ALL_TESTS();
}
