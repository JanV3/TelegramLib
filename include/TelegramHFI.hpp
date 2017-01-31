#ifndef TELEGRAMLIB_TELEGRAMHFI_H
#define TELEGRAMLIB_TELEGRAMHFI_H

#include "TelegramBase.hpp"

namespace TelegramLib {

    using namespace std;

    /**
     * @brief Class that represents telegram with specified ID, header and footer
     */
    class TelegramHFI : public TelegramBase {
        public:

            /**
             * @brief Data type of telegram Header field
             */
            using Header = unsigned int;

            /**
             * @brief Data type of telegram Footer field
             */
            using Footer = unsigned int;

            /**
             * @brief Data type of telegram ID field
             */
            using Id = short;

            /**
             * @brief Create telegram using data vector
             *
             * @param dv
             */
            TelegramHFI(TelegramBase::DataVector& dv) : TelegramBase(dv) {};

            /**
             * @brief Create telegram using telegram id and size
             *
             * @param id ID of telegram
             * @param base_size Size of telegram
             */
            TelegramHFI(Id id, size_t base_size = 64) : TelegramBase(base_size) {
                setId(id);
                setHF();
            };

            /**
             * @brief Returns telegram ID
             *
             * @return
             */
            Id getId(){
                return get<Id>(id_position);
            }

            /**
             * @brief Set telegram ID
             *
             * @param id
             */
            void setId(Id id){
                set(id_position, id);
            }

            /**
             * @brief Get telegram header field
             *
             * @return telegram header
             */
            Header getHeader(){
                return get<Header>(header_position);
            }

            /**
             * @brief Get telegram footer fiels
             *
             * @return telegram footer
             */
            Footer getFooter(){
                return get<Footer>(size() - footer_position);
            }

            /**
             * @brief Check telegram validity by checking header and footer values at defined positions.
             *
             * @return True if telegram is valid
             */
            bool isValid(){
                return ( getHeader() == headerValue ) && ( getFooter() == footerValue );
            }

        private:
            void setHF(){
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
#endif /* ifndef TELEGRAMLIB_TELEGRAMHFI_H */
