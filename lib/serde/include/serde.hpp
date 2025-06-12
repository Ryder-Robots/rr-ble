#ifndef SERDE_HPP
#define SERDE_HPP

#include <algorithm>
#include <rrevent.hpp>
#include <rrblemappings.hpp>

namespace rrobot {

class serde {
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

    /**
     * @brief Serializes an rrevent object into a string.
     *
     * This function takes an rrevent instance and converts it into a serialized string
     * representation, suitable for storage or transmission.
     *
     * @param out The rrevent object to serialize.
     * @return The serialized string representation of the rrevent.
     */
    static const String serialize(rrevent out);

    /**
     * @brief Calculates the CRC (Cyclic Redundancy Check) for a given data buffer.
     *
     * This function computes the CRC value for the provided data array of specified length.
     * The CRC is commonly used to detect accidental changes to raw data.
     *
     * @param data Pointer to the input data buffer.
     * @param length The number of bytes in the data buffer.
     * @return The calculated CRC value as a String.
     */
    static String cal_crc(const uint8_t* data, size_t length);
};
}  // namespace rrobot

#endif
