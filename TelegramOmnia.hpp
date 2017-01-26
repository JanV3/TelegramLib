#include <vector>

#include "TelegramBase.hpp"

namespace Omnia {

    using namespace std;

    class Telegram : public Kyb::TelegramBase {
        public:
            Telegram() : TelegramBase(64) {
            };

            Telegram(Kyb::TelegramBase::DataVector& dv) : TelegramBase(dv) {
            };

            Telegram(short id) : TelegramBase(64) {
                setId<short>(id);
            };

            Telegram(size_t id_position, short id) : TelegramBase(64) {
                this->id_position = id_position;
                setId<short>(id);
            };

            void setIdPosition(size_t id_position){
                this->id_position = id_position;
            }

            size_t getIdPosition(){
                return id_position;
            }

            template<typename T>
                T getId(){
                    return get<T>(id_position);
                }

            template<typename T>
                void setId(T id){
                    return set<T>(id_position, id);
                }

        private:
            size_t id_position = 0;
    };
}
