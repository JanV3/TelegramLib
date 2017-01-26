#include <vector>

namespace Kyb {

    using namespace std;

    class TelegramBase {
        public:
        using DataUnit = unsigned char;
        using DataVector = std::vector<DataUnit>;

        TelegramBase(size_t size){
            dv.resize(size);
        }

        TelegramBase(DataVector& dv){
            this->dv = dv;
        }

        TelegramBase(DataVector::iterator first, DataVector::iterator second){
            dv.resize(std::distance(first, second));
            std::copy(first, second, dv.begin());
        }

        void setDataVector(DataVector::iterator first, DataVector::iterator second){
            dv.resize(std::distance(first, second));
            std::copy(first, second, dv.begin());
        }

        void setDataVector(DataVector& dv){
            this->dv = dv;
        }

        DataVector& getDataVector(){
            return dv;
        }

        void invertEndiannes(bool status){
            inv_endianness = status;
        }

        protected:
        template<typename T>
            T get(size_t position){
                if(position + sizeof(T) > dv.size())
                    return T();
                return static_cast<T>(*(dv.begin() + position));
            }

        template<typename T>
            void set(size_t position, T value){
                if(position + sizeof(T) > dv.size())
                    return;
                *(dv.begin() + position) = value;
            }

        private:
        DataVector dv;
        bool inv_endianness = false;
    };
}
