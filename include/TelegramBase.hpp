
/**
\mainpage The Telegram Library

This is a simple library that create telegram(data vector) of any size. Library automatically ensures that encoded message have big endianness.
*/

#ifndef MESSAGING_TELEGRAM_BASE_H
#define MESSAGING_TELEGRAM_BASE_H

#include <vector>
#include <string>
#include <iomanip>
#include <sstream>

namespace Messaging {

    using namespace std;

    /**
     * @brief Convert input range to hexadecimal string.
     *
     * @tparam T
     * @param first from iterator
     * @param second to iterator
     *
     * @return string with hexadecimal representation of input range
     */
    template<typename T>
        string toHex(T first, T second){
            stringstream ss;
            for(; first != second; ++first){
                ss << setw(2) << setfill('0') << hex << static_cast<unsigned int>(*first) << " ";
            }
            return ss.str();
        }

    /**
     * @brief Function to runtime check of system endianness
     *
     * @return True if system is little endian
     * @return False if system is big endian
     */
    bool isLittleEndian()
    {
        short int number = 0x1;
        char *numPtr = (char*)&number;
        return (numPtr[0] == 1);
    }

    /**
     * @brief Swap bytes of input type
     *
     * @tparam T type of input parameter
     * @param input value
     *
     * @return output value with swapped bytes
     */
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

    /**
     * @brief Base of telegram. This class represents vector of data with getters and setters and also handles endianness of system.
     */
    class TelegramBase {
        public:
            using DataUnit = unsigned char;
            using DataVector = std::vector<DataUnit>;

            /**
             * @brief Create telegram with specific size
             *
             * @param size of telegram
             */
            TelegramBase(size_t size){
                dv.resize(size);
                little_endian = isLittleEndian();
            }

            /**
             * @brief Create telegram from DataVector (received data from socket, file, serial port, etc.). Input data are copyied.
             *
             * @param dv input data vector
             */
            TelegramBase(DataVector& dv){
                this->dv = dv;
                little_endian = isLittleEndian();
            }

            /**
             * @brief Create telegram by range given iterators
             *
             * @param first     from range
             * @param second    to range
             */
            TelegramBase(DataVector::iterator first, DataVector::iterator second){
                dv.resize(std::distance(first, second));
                std::copy(first, second, dv.begin());
                little_endian = isLittleEndian();
            }

            /**
             * @brief Method to set range of data given by iterators.
             *
             * @param first     from range
             * @param second    to range
             */
            void setDataVector(DataVector::iterator first, DataVector::iterator second){
                dv.resize(std::distance(first, second));
                std::copy(first, second, dv.begin());
            }

            /**
             * @brief Method for setting data vector (e.g. received data from socket, file, serial port, etc.). Input data are copyied.
             *
             * @param dv input data vector
             */
            void setDataVector(DataVector& dv){
                this->dv = dv;
            }

            /**
             * @brief Returns reference to underlying data vector
             *
             * @return DataVector&
             */
            DataVector& getDataVector(){
                return dv;
            }

            /**
             * @return Size of underlying data vector
             */
            size_t size(){
                return dv.size();
            }

            /**
             * @return Hexadecimal formatted string
             */
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
