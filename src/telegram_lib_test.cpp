#define CATCH_CONFIG_MAIN
#include "include/TelegramHFI.hpp"
#include "vendor/catch.hpp"
#include <iostream>

using namespace TelegramLib;

namespace Project1 {
class Telegram110 : public TelegramHFI {
public:
    Telegram110() : TelegramHFI(TelegramHFI::Id(110)){};

    int ckd() { return get<int>(2); }

    void ckd(int ckd) { set<int>(2, ckd); }
};
}

namespace Project2 {
class Telegram120 : public TelegramHFI {
public:
    Telegram120() : TelegramHFI(TelegramHFI::Id(120), 12){};
};
}

namespace Project3 {
class BadTelegram : public TelegramHFI {
public:
    BadTelegram() : TelegramHFI(TelegramHFI::Id(100)){};

    int param() { return get<int>(64); }
};
}

TEST_CASE("Check ID of inherited telegram and base telegram")
{
    auto t = Project1::Telegram110();
    auto kt = TelegramHFI(t.getDataVector());
    REQUIRE(t.getId() == 110);
    REQUIRE(kt.getId() == 110);
}

TEST_CASE("Check value of setted parameter")
{
    auto t = Project1::Telegram110();
    t.ckd(32);
    REQUIRE(t.ckd() == 32);
}

TEST_CASE("Size is not changed")
{
    auto t = Project1::Telegram110();
    auto kt = TelegramHFI(t.getDataVector());
    REQUIRE(t.size() == 64);
    REQUIRE(kt.size() == 64);
}

TEST_CASE("Telegram 110 header and footer check")
{
    auto t = Project1::Telegram110();
    REQUIRE(t.isValid());
}

TEST_CASE("Telegram 120 header and footer check")
{
    auto t = Project2::Telegram120();
    REQUIRE(t.isValid());
}

TEST_CASE("Cast to Telegram 120")
{
    TelegramBase::DataVector dv = {0xdd, 0xcc, 0xbb, 0xaa, 0x00, 0x78,
                                   0x00, 0x00, 0xaa, 0xbb, 0xcc, 0xdd};
    auto mt = TelegramHFI(dv);
    REQUIRE(mt.getId() == 120);
    if (mt.getId() == 120) {
        auto t = static_cast<Project2::Telegram120 *>(&mt);
        REQUIRE(t->isValid());
    }
}

TEST_CASE("Returns ZERO if not in range")
{
    auto t = Project3::BadTelegram();
    REQUIRE(t.param() == 0);
}
