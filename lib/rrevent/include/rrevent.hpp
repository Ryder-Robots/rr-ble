#ifndef RREVENT_HPP
#define RREVENT_HPP

#include <rrblemappings.hpp>
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
    rrevent(const int cmd, const size_t sz, const String data[]) : _cmd(cmd), _sz(sz) {
        for (size_t i = 0; i < sz; i++) {
            _data[i] = String(data[i].c_str());
        }
    }

    rrevent(const int cmd = MSP_NONE, const size_t sz = 0) : _cmd(cmd), _sz(sz) {}

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
     * @return Pointer to the array of String objects..
     */
    String get_data(int i) { return _data[i]; }

   private:
    const int _cmd;
    const size_t _sz = 0;
    String _data[RR_MX_E_SZ];
};
}  // namespace rrobot

#endif
