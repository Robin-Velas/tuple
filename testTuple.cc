#include <gtest/gtest.h>

#include "Tuple.h"

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(Tuple, easy) {
    t::Tuple<int> tu(42);
    ASSERT_EQ(42,tu.get<0>());
}

TEST(tuple, draft) {
    int val0 = 42;
    double val1 = 3.14;
    std::string val2 = "The cake is ";
    t::Tuple<int, double, std::string> t(val0, val1, val2);
    EXPECT_EQ(val0, t.get<0>());
    EXPECT_EQ(val1, t.get<1>());
    EXPECT_EQ(val2, t.get<2>());

    int val3 = -42;
    double val4 = -3.14;
    std::string val5 = "a lie";
    t::Tuple<int, double, std::string> t2(val3, val4, val5);
    EXPECT_EQ(val3, t2.get<0>());
    EXPECT_EQ(val4, t2.get<1>());
    EXPECT_EQ(val5, t2.get<2>());

    t += t2;
    EXPECT_EQ(0, t.get<0>());
    EXPECT_EQ(0, t.get<1>());
    EXPECT_EQ("The cake is a lie", t.get<2>());

    t::Tuple<int> a_1(12);
    t::Tuple<int> a_2(12);
    t::Tuple<int, int> a(12, 11);
    t::Tuple<int, int> b(10, 11);
    t::Tuple<int, int> c(12, 10);
    EXPECT_TRUE(a_1 == a_2);
    EXPECT_FALSE(a == b);
    EXPECT_FALSE(a == c);

    auto t3 = t::makeTuple(10, 10.0f, "test");
    EXPECT_EQ(10, t3.get<0>());
    EXPECT_EQ(10.0f, t3.get<1>());
    EXPECT_EQ("test", t3.get<2>());

    // dont' work...
    /*
    t::Tuple<int, double> one(12, 5.8);
    t::Tuple<int, double> two(6, 0.1);
    auto t_sum = one + two;
    std::cout
            << t_sum.get<0>() << ", "
            << t_sum.get<1>() << std::endl;
    */
}

TEST(eq, simple_eq){
    t::Tuple<int, double, std::string> t1(12, 1.2, "hello");
    t::Tuple<int, double, std::string> t2(12, 1.2, "hello");
    EXPECT_TRUE(t1 == t2);
}

TEST(eq, simple_not_eq){
    t::Tuple<int, double, std::string> t1(12, 1.25, "hello");
    t::Tuple<int, double, std::string> t2(12, 1.2, "hello");
    EXPECT_FALSE(t1 == t2);
}

TEST(eq, double_int_eq){
    t::Tuple<int, double, std::string> t1(12, 1.0, "hello");
    t::Tuple<int, int, std::string> t2(12, 1, "hello");
    EXPECT_TRUE(t1 == t2);
}


TEST(neq, simple_neq){
    t::Tuple<int, double, std::string> t1(125, 1.25, "hello5");
    t::Tuple<int, double, std::string> t2(12, 1.2, "hello");
    EXPECT_TRUE(t1 != t2);
}

TEST(neq, simple_not_neq){
    t::Tuple<int, double, std::string> t1(12, 1.2, "hello");
    t::Tuple<int, double, std::string> t2(12, 1.2, "hello");
    EXPECT_FALSE(t1 != t2);
}

TEST(neq, double_int_neq){
    /*
    t::Tuple<int, double, std::string> t1(12, 1.5, "hello");
    t::Tuple<int, int, std::string> t2(12, 1, "hello");
     */
    std::tuple<int, double, std::string> t1(12, 1.5, "hello");
    std::tuple<int, int, std::string> t2(12, 1, "hello");

    EXPECT_TRUE(t1 != t2);
}


TEST(lt, simple_lt){
    t::Tuple<int, double, std::string> t1(12, 1.2, "hello");
    t::Tuple<int, double, std::string> t2(120, 1.21, "hello56");
    EXPECT_TRUE(t1 < t2);
}

TEST(lt, simple_not_lt){
    t::Tuple<int, double, std::string> t1(12, 1.25, "hello");
    t::Tuple<int, double, std::string> t2(1, 1.0, "hell");
    EXPECT_FALSE(t1 < t2);
}

TEST(lt, simple_partialy_lt){
    t::Tuple<int, double, std::string> t1(0, 1.25, "hello");
    t::Tuple<int, double, std::string> t2(1, 1.0, "hell");
    EXPECT_FALSE(t1 < t2);
}

TEST(lt, double_int_gt){
    t::Tuple<int, double, std::string> t1(12, 1.99, "hello");
    t::Tuple<int, int, std::string> t2(13, 2, "hello563");
    EXPECT_TRUE(t1 < t2);
}


TEST(gt, simple_gt){
    t::Tuple<int, double, std::string> t1(12, 1.2, "hello");
    t::Tuple<int, double, std::string> t2(120, 1.21, "hello56");
    EXPECT_TRUE(t2 > t1);
}

TEST(gt, simple_not_gt){
    t::Tuple<int, double, std::string> t1(12, 1.25, "hello");
    t::Tuple<int, double, std::string> t2(1, 1.0, "hell");
    EXPECT_FALSE(t2 > t1);
}

TEST(gt, simple_partialy_gt){
    t::Tuple<int, double, std::string> t1(0, 1.25, "hello");
    t::Tuple<int, double, std::string> t2(1, 1.0, "hell");
    EXPECT_FALSE(t2 > t1);
}

TEST(gt, double_int_gt){
    t::Tuple<int, double, std::string> t1(12, 1.99, "hello");
    t::Tuple<int, int, std::string> t2(13, 2, "hello563");
    EXPECT_FALSE(t1 > t2);
}


TEST(let, simple_let){
    t::Tuple<int, double, std::string> t1(12, 1.2, "hello");
    t::Tuple<int, double, std::string> t2(120, 1.21, "hello56");
    EXPECT_TRUE(t1 <= t2);
}

TEST(let, simple_not_let){
    t::Tuple<int, double, std::string> t1(12, 1.25, "hello");
    t::Tuple<int, double, std::string> t2(1, 1.0, "hell");
    EXPECT_FALSE(t1 <= t2);
}

TEST(let, simple_partialy_let){
    t::Tuple<int, double, std::string> t1(0, 1.25, "hello");
    t::Tuple<int, double, std::string> t2(1, 1.0, "hell");
    EXPECT_FALSE(t1 <= t2);
}

TEST(let, double_int_let){
    t::Tuple<int, double, std::string> t1(12, 1.99, "hello");
    t::Tuple<int, int, std::string> t2(13, 2, "hello563");
    EXPECT_TRUE(t1 <= t2);
}

TEST(incr_plus, simple) {
    t::Tuple<int, int> t1(12, 1);
    t::Tuple<int, int> t2(13, 2);
    t1 += t2;
    EXPECT_EQ(25, t1.get<0>());
    EXPECT_EQ(3, t1.get<1>());
}

TEST(incr_plus, simple2) {
    t::Tuple<double, std::string> t1(12.9, "heal");
    t::Tuple<double, std::string> t2(11.1, " you");
    t1 += t2;
    EXPECT_EQ(24.0, t1.get<0>());
    EXPECT_EQ("heal you", t1.get<1>());
}


TEST(incr_minus, simple) {
    t::Tuple<int, int> t1(16, 1);
    t::Tuple<int, int> t2(13, 2);
    t1 -= t2;
    EXPECT_EQ(3, t1.get<0>());
    EXPECT_EQ(-1, t1.get<1>());
}


TEST(incr_multiply, simple) {
    t::Tuple<int, int> t1(6, 3);
    t::Tuple<int, int> t2(3, 2);
    t1 *= t2;
    EXPECT_EQ(18, t1.get<0>());
    EXPECT_EQ(6, t1.get<1>());
}

TEST(incr_divide, simple) {
    t::Tuple<int, int> t1(6, 4);
    t::Tuple<int, int> t2(3, 2);
    t1 /= t2;
    EXPECT_EQ(2, t1.get<0>());
    EXPECT_EQ(2, t1.get<1>());
}

TEST(incr_divide, simple_but_not_working) {
    t::Tuple<int, int> t1(6, 3);
    t::Tuple<int, int> t2(3, 2);
    t1 /= t2;
    EXPECT_EQ(2, t1.get<0>());
    EXPECT_EQ(1, t1.get<1>());
}

