#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Telegram.hpp"
#include <iostream>

namespace Project1 {
    class Telegram110 : public Messaging::Telegram {
        public:
            Telegram110() : Telegram(110) {
            };

            int ckd(){
                return get<int>(2);
            };

            void ckd(int ckd){
                set<int>(2, ckd);
            }
    };

}
namespace Project2 {
    class Telegram120 : public Messaging::Telegram {
        public:
            Telegram120() : Telegram(120, 12) {
            };
    };
}

namespace Project3 {
    class BadTelegram : public Messaging::Telegram {
        public:
            BadTelegram() : Telegram(100) {
            };

            int param(){
                return get<int>(64);
            }
    };
}

TEST_CASE( "Check ID of inherited telegram and base telegram") {
    auto t = Project1::Telegram110();
    auto kt = Messaging::Telegram(t.getDataVector());
    REQUIRE( t.getId() == 110 );
    REQUIRE( kt.getId() == 110 );
}

TEST_CASE( "Check value of setted parameter") {
    auto t = Project1::Telegram110();
    t.ckd(32);
    REQUIRE( t.ckd() == 32 );
}

TEST_CASE( "Size is not changed" ) {
    auto t = Project1::Telegram110();
    auto kt = Messaging::Telegram(t.getDataVector());
    REQUIRE( t.size() == 64 );
    REQUIRE( kt.size() == 64 );
}

TEST_CASE( "Telegram 110 header and footer check" ) {
    auto t = Project1::Telegram110();
    REQUIRE( t.getHeader() == Messaging::Telegram::Header(0xDDCCBBAA) );
    REQUIRE( t.getFooter() == Messaging::Telegram::Footer(0xAABBCCDD) );
}

TEST_CASE( "Telegram 120 header and footer check" ) {
    auto t = Project2::Telegram120();
    REQUIRE( t.getHeader() == Messaging::Telegram::Header(0xDDCCBBAA) );
    REQUIRE( t.getFooter() == Messaging::Telegram::Footer(0xAABBCCDD) );
}

TEST_CASE( "Cast to Telegram 120" ) {
    Messaging::TelegramBase::DataVector dv = {0xdd, 0xcc, 0xbb, 0xaa, 0x00, 0x78, 0x00, 0x00, 0xaa, 0xbb, 0xcc, 0xdd};
    auto mt = Messaging::Telegram(dv);
    REQUIRE( mt.getId() == 120 );
    if(mt.getId() == 120) {
        auto t = static_cast<Project2::Telegram120*>(&mt);
        REQUIRE( t->getHeader() == Messaging::Telegram::Header(0xDDCCBBAA) );
        REQUIRE( t->getFooter() == Messaging::Telegram::Footer(0xAABBCCDD) );
    }
}

TEST_CASE( "Returns ZERO if not in range" ) {
    auto t = Project3::BadTelegram();
    REQUIRE( t.param() == 0 );
}

