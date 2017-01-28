#ifndef MESSAGING_TELEGRAM_BASE_H
#define MESSAGING_TELEGRAM_BASE_H

#include <vector>
#include <string>
#include <iomanip>
#include <sstream>

namespace Messaging {

    using namespace std;

    template<typename T>
        string toHex(T first, T second){
            stringstream ss;
            for(; first != second; ++first){
                ss << setw(2) << setfill('0') << hex << static_cast<unsigned int>(*first) << " ";
            }
            return ss.str();
        }

    bool isLittleEndian()
    {
        short int number = 0x1;
        char *numPtr = (char*)&number;
        return (numPtr[0] == 1);
    }

    template<typename T>
        T swapBytes(const T input){
            T output;
            size_t type_size = sizeof(T);

            if(type_size % 2 != 0)
                return input;

            char *valueToConvert = ( char* ) & input;
            char *returnValue = ( char* ) & output;

            for(int i = 0; i < type_size; i++){
                returnValue[i] = valueToConvert[type_size - 1 - i];
            }

            return output;
        };

    class TelegramBase {
        public:
            using DataUnit = unsigned char;
            using DataVector = std::vector<DataUnit>;

            TelegramBase(size_t size){
                dv.resize(size);
                little_endian = isLittleEndian();
            }

            TelegramBase(DataVector& dv){
                this->dv = dv;
                little_endian = isLittleEndian();
            }

            TelegramBase(DataVector::iterator first, DataVector::iterator second){
                dv.resize(std::distance(first, second));
                std::copy(first, second, dv.begin());
                little_endian = isLittleEndian();
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

            size_t size(){
                return dv.size();
            }

            string print(){
                return toHex(dv.begin(), dv.end());
            }

        protected:
            template<typename T>
                T get(size_t position){
                    if(position + sizeof(T) > dv.size())
                        return T();
                    if(little_endian){
                        return swapBytes(*reinterpret_cast<T*>(dv.data() + position));
                    } else {
                        return *reinterpret_cast<T*>(dv.data() + position);
                    }
                }

            template<typename T>
                void set(size_t offset, T value, bool from_end = false){
                    size_t position = offset;
                    if(from_end)
                        position = dv.size() - offset;
                    if(position + sizeof(T) > dv.size())
                        return;
                    if(little_endian){
                        *reinterpret_cast<T*>(dv.data() + position) = swapBytes(value);
                    } else {
                        *reinterpret_cast<T*>(dv.data() + position) = value;
                    }
                }


        private:
            DataVector dv;
            bool little_endian = false;
    };
}
#endif /* ifndef MESSAGING_TELEGRAM_BASE_H */
