#include <rringress.hpp>

using namespace rrobot;

rrevent rringress::deserialize(const String in) {
    String result[RR_MX_E_SZ];
    const int mcount = split_string(in, _DELIMETER, result, RR_MX_E_SZ);

    for (int i = 0; i < 3; i++) {
        int v = result[i].toInt();
        if (String(v) != result[i]) {
            return rrevent(MSP_NONE, 0);
        }
    }

    const int sz = std::min(static_cast<int>(result[1].toInt()), mcount);
    if (mcount < 3) {
        return rrevent(MSP_NONE, 0);
    } else if (sz > 3) {
        String data[RR_MX_E_SZ];
        for (int i = 3; i < mcount; i++) {
            data[i - 3] = String(result[i].c_str());
        }
        rrevent e =  rrevent(static_cast<int>(result[0].toInt()), (sz - 3), data);
        return e;
    }
    return rrevent(static_cast<int>(result[0].toInt()), sz);
}
