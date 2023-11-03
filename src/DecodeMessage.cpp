// DecodeMessage.cpp

#include "DecodeMessage.h"
#include <iostream>
#include <bitset>

// Default constructor
DecodeMessage::DecodeMessage() {
    // Nothing specific to initialize here
}

// Destructor
DecodeMessage::~DecodeMessage() {
    // Nothing specific to clean up
}


int getLeastSignificantBit(int pixel) {
    return pixel & 1;
}

std::string DecodeMessage::decodeFromImage(const ImageMatrix& image, const std::vector<std::pair<int, int>>& edgePixels) {
    if (edgePixels.empty()) {
        return "";
    }

    std::string msg;

    for (const auto& pixel : edgePixels) {
        int lsb = getLeastSignificantBit(image.get_data()[pixel.first][pixel.second]);
        msg += std::to_string(lsb);
    }

    if (msg.size() % 7 != 0) {
        msg = std::string(7 - (msg.size() % 7), '0') + msg;
    }

    std::string finalMsg;
    for (int i = 0; i < msg.size(); i += 7) {
        std::string tmp = msg.substr(i, 7);
        int number = std::stoi(tmp, nullptr, 2);
        if (number <= 32) {
            number += 33;
        } else if (number >= 127) {
            number = 126;
        }
        char c = static_cast<char>(number);
        finalMsg += c;
    }
    return finalMsg;
}


