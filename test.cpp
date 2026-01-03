#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <random>
#include "NCint.hpp" // 你的 NCint 类

// 生成随机大整数字符串，长度 len，首位不能为0
std::string random_bigint_str(int len, bool allow_negative = true) {
    static std::mt19937_64 rng(std::random_device{}());
    static std::uniform_int_distribution<int> digit_dist(0, 9);
    static std::uniform_int_distribution<int> sign_dist(0, 1);

    std::string s;
    if (allow_negative && sign_dist(rng) == 1) s += '-';
    s += char('1' + digit_dist(rng) % 9); // 首位 1~9
    for (int i = 1; i < len; ++i) {
        s += char('0' + digit_dist(rng));
    }
    return s;
}

int main() {
    const int NUM_TESTS = 5;      // 测试组数
    const int MIN_LEN = 500;      // 最小位数
    const int MAX_LEN = 1000;     // 最大位数

    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> len_dist(MIN_LEN, MAX_LEN);

    for (int t = 1; t <= NUM_TESTS; ++t) {
        int len_a = len_dist(rng);
        int len_b = len_dist(rng);

        NCint<> a(random_bigint_str(len_a));
        NCint<> b(random_bigint_str(len_b));

        std::cout << "Test " << t << ": a length=" << len_a << ", b length=" << len_b << "\n";

        auto start_div = std::chrono::high_resolution_clock::now();
        NCint<> quotient = a / b;
        auto end_div = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> div_time = end_div - start_div;

        auto start_mod = std::chrono::high_resolution_clock::now();
        NCint<> remainder = a % b;
        auto end_mod = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> mod_time = end_mod - start_mod;

        std::cout << "  Division time: " << div_time.count() << " seconds\n";
        std::cout << "  Modulo time:   " << mod_time.count() << " seconds\n";

        // 仅显示前50位以验证结果
        std::string q_str = std::string(quotient);
        std::string r_str = std::string(remainder);
        std::cout << "  Quotient first 50 digits: " << q_str.substr(0, std::min(50, (int)q_str.size())) << "\n";
        std::cout << "  Remainder first 50 digits: " << r_str.substr(0, std::min(50, (int)r_str.size())) << "\n";
        std::cout << "----------------------------------------\n";
    }

    return 0;
}
