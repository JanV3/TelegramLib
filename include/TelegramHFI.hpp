#ifndef TELEGRAMLIB_TELEGRAMHFI_H
#define TELEGRAMLIB_TELEGRAMHFI_H

#include <unordered_map>
#include <functional>

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
     * @param data
     */
    TelegramHFI(TelegramBase::Data&& data)
        : TelegramBase(std::forward<TelegramBase::Data>(data)){};

    /**
     * @brief Create telegram using data vector
     *
     * @param data
     */
    TelegramHFI(TelegramBase::Data& data)
        : TelegramBase(data)
    {};

    /**
     * @brief Create telegram using telegram id and size
     *
     * @param id ID of telegram
     * @param base_size Size of telegram
     */
    TelegramHFI(Id id, size_t base_size = 64)
        : TelegramBase(base_size)
    {
        setId(id);
        if (headerValue != 0) {
            set(header_position, headerValue);
        }
        if (footerValue != 0) {
            set(footer_position, footerValue, true);
        }
    };

    /**
     * @brief Returns telegram ID
     *
     * @return
     */
    Id getId() const
    {
        return get<Id>(id_position);
    }

    /**
     * @brief Set telegram ID
     *
     * @param id
     */
    void setId(Id id)
    {
        set(id_position, id);
    }

    /**
     * @brief Get telegram header field
     *
     * @return telegram header
     */
    Header getHeader()
    {
        return get<Header>(header_position);
    }

    /**
     * @brief Get telegram footer fiels
     *
     * @return telegram footer
     */
    Footer getFooter()
    {
        return get<Footer>(size() - footer_position);
    }

    /**
     * @brief Check telegram validity by checking header and footer values at
     * defined positions.
     *
     * @return True if telegram is valid
     */
    bool isValid()
    {
        return (getHeader() == headerValue) && (getFooter() == footerValue);
    }

private:
    size_t header_position = 0;
    size_t id_position = 4;
    size_t footer_position = 4;
    Header headerValue = 0xDDCCBBAA;
    Footer footerValue = 0xAABBCCDD;
};

class TelegramHFIFactory {
    using TelegramHFIPtr = std::unique_ptr<TelegramHFI>;
    using Builder = std::function<TelegramHFIPtr(void)>;
    std::unordered_map<TelegramHFI::Id, Builder> builders_;

public:
    virtual ~TelegramHFIFactory()
    {
    }

    TelegramHFIPtr create(TelegramHFI::Id id)
    {
        return builders_[id]();
    }

    TelegramHFIPtr create(TelegramBase::Data&& data)
    {
        auto hfi = TelegramHFI(std::forward<TelegramBase::Data>(data));
        auto t = builders_[hfi.getId()]();
        t->setData(std::move(hfi.getData()));
        return t;
    }

protected:
    void reg(TelegramHFI::Id id, Builder&& builder)
    {
        builders_[id] = builder;
    }
};
}
#endif /* ifndef TELEGRAMLIB_TELEGRAMHFI_H */
