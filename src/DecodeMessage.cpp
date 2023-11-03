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
    for (int index = 0; index < msg.size(); index += 7) {
        std::string substring = msg.substr(index, 7);
        int asciiValue = std::stoi(substring, nullptr, 2);
        if (asciiValue <= 32) {
            asciiValue += 33;
        } else if (asciiValue >= 127) {
            asciiValue = 126;
        }
        char character = static_cast<char>(asciiValue);
        finalMsg += character;
    }
    return finalMsg;
}


