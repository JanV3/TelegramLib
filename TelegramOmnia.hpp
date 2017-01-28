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

            Telegram(short id, size_t base_size = 64) : TelegramBase(base_size) {
                set(id_position, id);
                init();
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
            void init(){
                if(headerValue != 0){
                    set(header_position, headerValue);
                }
                if (footerValue != 0) {
                    set(size() - footer_position, footerValue);
                }
            }

        private:
            size_t header_position = 0;
            size_t id_position = 4;
            size_t footer_position = 4;
            Header headerValue = 0xDDCCBBAA;
            Footer footerValue = 0xAABBCCDD;
    };
}
