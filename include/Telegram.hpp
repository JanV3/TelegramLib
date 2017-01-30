#ifndef MESSAGING_TELEGRAM_H
#define MESSAGING_TELEGRAM_H

#include "TelegramBase.hpp"

namespace Messaging {

    using namespace std;

    /**
     * @brief Class that represents telegram with specified ID, header and footer
     */
    class Telegram : public TelegramBase {
        public:
            using Header = unsigned int;
            using Footer = unsigned int;

            /**
             * @brief Create telegram using data vector
             *
             * @param dv
             */
            Telegram(TelegramBase::DataVector& dv) : TelegramBase(dv) {
            };

            /**
             * @brief Create telegram using telegram id and size
             *
             * @param id ID of telegram
             * @param base_size Size of telegram (default value 64)
             */
            Telegram(short id, size_t base_size = 64) : TelegramBase(base_size) {
                set(id_position, id);
                init();
            };

            /**
             * @brief Returns telegram ID
             *
             * @return
             */
            short getId(){
                return get<short>(id_position);
            }

            /**
             * @brief Set telegram ID
             *
             * @param id
             */
            void setId(short id){
                set(id_position, id);
            }

            /**
             * @brief Get telegram header field
             *
             * @return telegram header
             */
            unsigned int getHeader(){
                return get<Header>(header_position);
            }

            /**
             * @brief Get telegram footer fiels
             *
             * @return telegram footer
             */
            unsigned int getFooter(){
                return get<Footer>(size() - footer_position);
            }

        private:
            void init(){
                if(headerValue != 0){
                    set(header_position, headerValue);
                }
                if (footerValue != 0) {
                    set(footer_position, footerValue, true);
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
#endif /* ifndef MESSAGING_TELEGRAM_H */
