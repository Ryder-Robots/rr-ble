#ifndef RRINGRESS_HPP
#define RRINGRESS_HPP

#include <algorithm>
#include <rrevent.hpp>
#include <rrutil.hpp>

namespace rrobot {
class rringress {
   public:
    /**
     * @brief Deserializes a string input into an rrevent object.
     *
     * This function takes a serialized representation of an rrevent, provided as a String,
     * and converts it back into an rrevent instance.
     *
     * @param in The serialized string representation of an rrevent.
     * @return The deserialized rrevent object.
     */
    static rrevent deserialize(const String in);
};
}  // namespace rrobot

#endif
