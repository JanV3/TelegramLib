#define CATCH_CONFIG_MAIN
#include "include/TelegramHFI.hpp"
#include "vendor/catch.hpp"
#include <iostream>
#include <memory>
#include <unordered_map>

using namespace TelegramLib;

namespace Project {
class Telegram120 : public TelegramHFI {
public:
    Telegram120()
        : TelegramHFI(120){};

    int ckd()
    {
        return get<int>(8);
    }

    void ckd(int value)
    {
        set(8, value);
    }
};

class Telegram121 : public TelegramHFI {
public:
    Telegram121()
        : TelegramHFI(121){};
};

class Telegram122 : public TelegramHFI {
public:
    Telegram122()
        : TelegramHFI(122, 12){};
};

class TelegramFactory : public TelegramHFIFactory {
public:
    TelegramFactory()
    {
        reg(120, [](){ return std::make_unique<Telegram120>(); });
        reg(121, [](){ return std::make_unique<Telegram121>(); });
        reg(122, [](){ return std::make_unique<Telegram122>(); });
    }
};
}


TEST_CASE("Check ID of inherited telegram and base telegram")
{
    Project::TelegramFactory tf;
    auto t = tf.create(120);
    auto kt = TelegramHFI(t->getData());
    REQUIRE(t->getId() == 120);
    REQUIRE(kt.getId() == 120);
}

TEST_CASE("Check value of setted parameter")
{
    auto t = Project::Telegram120();
    t.ckd(32);
    REQUIRE(t.ckd() == 32);
}

TEST_CASE("Size is not changed")
{
    auto t = Project::Telegram121();
    auto kt = TelegramHFI(t.getData());
    REQUIRE(t.size() == 64);
    REQUIRE(kt.size() == 64);
}

TEST_CASE("Telegram 110 header and footer check")
{
    auto t = Project::Telegram122();
    REQUIRE(t.isValid());
}

TEST_CASE("Cast to Telegram 120")
{
    TelegramBase::Data data = {0xdd, 0xcc, 0xbb, 0xaa, 0x00, 0x78, 0x00, 0x00, 0xaa, 0xbb, 0xcc, 0xdd};
    auto mt = TelegramHFI(data);
    REQUIRE(mt.getId() == 120);
    if (mt.getId() == 120) {
        auto t = static_cast<Project::Telegram122*>(&mt);
        REQUIRE(t->isValid());
    }
}

// TODO: make polymorphic switch, probably visitor pattern...
//TEST_CASE("Create telegram by data")
//{
    //auto process = [](Project::Telegram120 const * const telegram){ return telegram->getId(); };
    //Project::TelegramFactory tf;
    //TelegramBase::Data data = {0xdd, 0xcc, 0xbb, 0xaa, 0x00, 0x78, 0x00, 0x00, 0xaa, 0xbb, 0xcc, 0xdd};
    //auto mt = tf.create(std::move(data));
    //REQUIRE(process(mt) == 120);
    //if (mt->getId() == 120) {
        //auto t = static_cast<Project::Telegram120*>(mt.get());
        //REQUIRE(t->isValid());
    //}
//}
