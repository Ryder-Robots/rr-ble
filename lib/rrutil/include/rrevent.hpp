#ifndef RREVENT_HPP
#define RREVENT_HPP

#include <rrutil.hpp>

namespace rrobot {

class rrevent {
   public:
    /**
     * @brief Constructs an rrevent object with the specified command, size, and data.
     *
     * @param cmd The command identifier for the event.
     * @param sz Byte size associated with the event.
     * @param data An array of String objects containing event data.
     * @param mcount The number of elements in the data array to copy.
     */
    rrevent(const int cmd, const size_t sz, String data[], size_t mcount) : _cmd(cmd), _sz(sz) {
        for (size_t i = 0; i < mcount; ++i) {
            _data[i] = data[i];
        }
    }

    /**
     * @brief Destructor for the rrevent class.
     *
     * Defaulted destructor. Cleans up resources used by the rrevent object.
     */
    ~rrevent() = default;

    /**
     * @brief Retrieves the command identifier associated with the event.
     *
     * @return The command identifier as an integer.
     */
    int get_cmd() { return _cmd; }

    /**
     * @brief Retrieves the byte size associated with the event.
     *
     * @return The size in bytes as a size_t.
     */
    size_t get_sz() { return _sz; }

    /**
     * @brief Retrieves a pointer to the array of String objects containing event data.
     *
     * @return Pointer to the array of String objects.
     */
    String* get_data() { return _data; }

   private:
    const int _cmd;
    const size_t _sz;
    String _data[];
};
}  // namespace rrobot

#endif
