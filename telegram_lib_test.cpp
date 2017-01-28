#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "TelegramOmnia.hpp"

namespace Omnia {

    class Telegram110 : public Telegram {
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

    class Telegram120 : public Telegram {
        public:
            Telegram120() : Telegram(120, 12) {
            };
    };
}

TEST_CASE( "Check ID of inherited telegram and base telegram") {
    auto t = Omnia::Telegram110();
    auto kt = Omnia::Telegram(t.getDataVector());
    REQUIRE( t.getId() == 110 );
    REQUIRE( kt.getId() == 110 );
}

TEST_CASE( "Check value of setted parameter") {
    auto t = Omnia::Telegram110();
    t.ckd(32);
    REQUIRE( t.ckd() == 32 );
}

TEST_CASE( "Size is not changed" ) {
    auto t = Omnia::Telegram110();
    auto kt = Omnia::Telegram(t.getDataVector());
    REQUIRE( t.size() == 64 );
    REQUIRE( kt.size() == 64 );
}

TEST_CASE( "Check header & footer (normal endianness)" ) {
    auto t = Omnia::Telegram110();
    REQUIRE( t.getHeader() == Omnia::Telegram::Header(0xDDCCBBAA) );
    REQUIRE( t.getFooter() == Omnia::Telegram::Footer(0xAABBCCDD) );
}

TEST_CASE( "Check header & footer (inverted endianness)" ) {
    auto t = Omnia::Telegram120();
    REQUIRE( t.getHeader() == Omnia::Telegram::Header(0xDDCCBBAA) );
    REQUIRE( t.getFooter() == Omnia::Telegram::Footer(0xAABBCCDD) );
}
