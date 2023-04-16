#include "../tests/include/gtest/gtest.h"
#include "../include/Mario.hpp"

// Test fixture for Mario class
class MarioTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Set up any necessary objects or states before running the tests
        mario = new Mario(0, 0);
    }

    void TearDown() override {
        // Clean up any objects or states after running the tests
        delete mario;
    }

    Mario* mario;
};

// Test case for Mario class
TEST_F(MarioTest, TestSetWalkLeft) {
    // Call the setWalkLeft() method
    mario->setWalkLeft();

    // Assert that the hbm_ and hbmMask_ handles are updated correctly
    ASSERT_EQ(mario->hbm_, mario->getHbmSuperMarioWalkLeft());
    ASSERT_EQ(mario->hbmMask_, mario->getHbmSuperMarioWalkLeftMask());
}

// Test case for Mario class
TEST_F(MarioTest, TestSetWalkRight) {
    // Call the setWalkRight() method
    mario->setWalkRight();

    // Assert that the hbm_ and hbmMask_ handles are updated correctly
    ASSERT_EQ(mario->hbm_, mario->getHbmSuperMarioWalkRight());
    ASSERT_EQ(mario->hbmMask_, mario->getHbmSuperMarioWalkRightMask());
}

// Test case for Mario class
TEST_F(MarioTest, TestSetYState) {
    // Call the setYState() method with stateY::Up
    mario->setYState(Object::stateY::Up);

    // Assert that the Y, X, and maxCycles_ members are updated correctly
    ASSERT_EQ(mario->Y_, 3);
    ASSERT_EQ(mario->X_, 0);
    ASSERT_EQ(mario->maxCycles_, 1);

    // Call the setYState() method with stateY::Neutral
    mario->setYState(Object::stateY::Neutral);

    // Assert that the Y, X, and maxCycles_ members are updated correctly
    ASSERT_EQ(mario->Y_, 0);
    ASSERT_EQ(mario->X_, 0);
    ASSERT_EQ(mario->maxCycles_, 1);
}

// Test case for Mario class
TEST_F(MarioTest, TestSetXState) {
    // Call the setXState() method with stateX::Left
    mario->setXState(Object::stateX::Left);

    // Assert that the Y, maxCycles_, dx_, hbm_, and hbmMask_ members are updated correctly
    ASSERT_EQ(mario->Y_, 1);
    ASSERT_EQ(mario->maxCycles_, 2);
    ASSERT_EQ(mario->dx_, -5);
    ASSERT_EQ(mario->hbm_, mario->getHbmSuperMarioWalkLeft());
    ASSERT_EQ(mario->hbmMask_, mario->getHbmSuperMarioWalkLeftMask());

    // Call the setXState() method with stateX::Right
    mario->setXState(Object::stateX::Right);

    // Assert that the Y, maxCycles_, dx_, hbm_, and hbmMask_ members are updated correctly
    ASSERT_EQ(mario->Y_, 1);
    ASSERT_EQ(mario->maxCycles_, 2);
    ASSERT_EQ(mario->dx_, 5);
    ASSERT_EQ(mario->hbm_, mario->getHbmSuperMarioWalkRight());
    ASSERT_EQ(mario->hbmMask_, mario->getHbmSuperMarioWalkRightMask());
}

// Test case for Mario class
TEST_F(MarioTest, TestJump) {
    // Call the jump() method
    mario->setYState(Object::stateY::Up);

    // Assert that the dy_ member is updated correctly
    ASSERT_EQ(mario->dy_, -16);
}
