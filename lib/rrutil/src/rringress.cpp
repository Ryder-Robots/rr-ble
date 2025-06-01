#include <rringress.hpp>

using namespace rrobot;

rrevent deserialize(const String in) {
    String result[RR_MX_E_SZ];
    const int mcount = split_string(in, _DELIMETER, result, RR_MX_E_SZ);

    if (mcount < 3) {
        return rrevent(MSP_NONE, 0);
    } else {
        if (mcount > 3) {
            String data[RLEN(result) - 3];
            for (int i = 3; i < RLEN(result); i++) {
                data[i - 3] = result[i];
            }
            return rrevent(static_cast<int>(result[0].toInt()), static_cast<size_t>(result[1].toInt()), data);
        } else {
            return rrevent(static_cast<int>(result[0].toInt()), static_cast<size_t>(result[1].toInt()));
        }
    }
}