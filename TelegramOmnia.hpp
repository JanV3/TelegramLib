#include <vector>

#include "TelegramBase.hpp"

namespace Omnia {

    using namespace std;

    class Telegram : public Kyb::TelegramBase {
        public:
            using Header = unsigned int;
            using Footer = unsigned int;

            Telegram(Kyb::TelegramBase::DataVector& dv) : TelegramBase(dv) {
            };

            Telegram(short id) : TelegramBase(64) {
                set(id_position, id);
                header = 0xDDCCBBAA;
                set(header_position, header);
                footer = 0xAABBCCDD;
                set(footer_position, footer);
            };

            short getId(){
                return get<short>(id_position);
            }

            void setId(short id){
                set(id_position, id);
            }

            unsigned int getHeader(){
                return get<Header>(header_position);
            }

            unsigned int getFooter(){
                return get<Footer>(footer_position);
            }

        private:
            size_t header_position = 0;
            size_t id_position = 4;
            size_t footer_position = 60;
            Header header;
            Footer footer;
    };
}
