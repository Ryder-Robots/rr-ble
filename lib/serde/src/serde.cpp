#include <serde.hpp>

using namespace rrobot;

rrevent serde::deserialize(const String in) {
    String result[RR_MX_E_SZ];
    const int mcount = split_string(in, _DELIMETER, result, RR_MX_E_SZ);

    for (int i = 0; i < 3; i++) {
        int v = result[i].toInt();
        if (String(v) != result[i]) {
            return rrevent(MSP_NONE);
        }
    }

    const int sz = std::min(static_cast<int>(result[1].toInt()), mcount);
    if (mcount < 3) {
        return rrevent(MSP_NONE);
    } else if (sz > 3) {
        String data[RR_MX_E_SZ];
        for (int i = 3; i < mcount; i++) {
            data[i - 3] = String(result[i].c_str());
        }
        return rrevent(static_cast<int>(result[0].toInt()), (sz - 3), data);
    }
    return rrevent(static_cast<int>(result[0].toInt()));
}


const String serde::serialize(rrevent out) {
    String dataj = "";
    for (size_t i = 0; i < out.get_sz(); i++) {
        dataj += out.get_data(i) + _DELIMETER;
    }

    const uint8_t* data_ptr = reinterpret_cast<uint8_t*>(const_cast<char*>(dataj.c_str()));
    String joined = String(out.get_cmd()) + _DELIMETER + String(dataj.length()) + _DELIMETER +
                    cal_crc(data_ptr, dataj.length()) + _DELIMETER + dataj + _TERM_CHAR;

    return joined;
}

String serde::cal_crc(const uint8_t* data, size_t length) {
    uint16_t crc = 0xFFFF;
    for (size_t i = 0; i < length; i++) {
        crc ^= data[i];
        for (uint8_t j = 0; j < 8; j++) {
            if (crc & 0x0001) {
                crc = (crc >> 1) ^ 0xA001;
            } else {
                crc = crc >> 1;
            }
        }
    }
    return String(crc);
}
