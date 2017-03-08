#include <gtest/gtest.h>

#include <string>
#include <iostream>

#include <cpr/cpr.h>

#include "server.h"

using namespace cpr;

static Server *server = new Server();
auto base = server->GetBaseUrl();

TEST(AlternatingTests, StatusTest) {
    auto url = Url{base + "/inforeader.html"};
    Session session;
    session.SetUrl(url);

    {
        session.SetInfoParser(InfoReader([](CURL* curl){
            //std::cout << "try to parse" << std::endl;
            //TODO Implement a test?
        }));
        auto response =  session.Get();
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
