#include "../tests/include/gtest/gtest.h"
#include "../include/Object.hpp"

class ObjectTest : public testing::Test {
protected:
    void SetUp() override {
        objects = std::make_shared<std::vector<std::shared_ptr<Object>>>();
        // Add some objects to the objects vector
//        objects->push_back(std::make_shared<Object>());
//        objects->push_back(std::make_shared<Object>());
    }

    void TearDown() override {
        objects->clear();
    }

    std::shared_ptr<std::vector<std::shared_ptr<Object>>> objects;
};

TEST_F(ObjectTest, ProjectXTest) {
//    std::shared_ptr<Object> testObject = std::make_shared<Object>();
//    testObject->dx_ = 10;
//
//    testObject->projectX();
//
//    EXPECT_EQ(10, testObject->dx_);
}
