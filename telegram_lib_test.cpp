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
}

TEST_CASE( "Check ID of inherited telegram and base telegram") {
    auto t = Omnia::Telegram110();
    auto kt = Omnia::Telegram(t.getDataVector());
    REQUIRE( t.getId<short>() == 110 );
    REQUIRE( kt.getId<short>() == 110 );
}

TEST_CASE( "Check value of setted parameter") {
    auto t = Omnia::Telegram110();
    t.ckd(32);
    REQUIRE( t.ckd() == 32 );
}
