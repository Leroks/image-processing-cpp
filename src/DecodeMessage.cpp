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


std::string DecodeMessage::decodeFromImage(const ImageMatrix& image, const std::vector<std::pair<int, int>>& edgePixels) {
    std::string binaryString;
    for (const auto& pixel : edgePixels) {
        int pixelValue = image.get_data(pixel.first, pixel.second);
        binaryString += std::bitset<8>(pixelValue).to_string().substr(0, 1);
    }

    std::string asciiString;
    for (int i = 0; i < binaryString.length(); i += 7) {
        std::string segment = binaryString.substr(i, 7);
        if (segment.length() < 7) {
            segment = std::string(7 - segment.length(), '0') + segment;
        }
        int asciiValue = std::bitset<7>(segment).to_ulong();
        if (asciiValue <= 32) {
            asciiValue += 33;
        } else if (asciiValue == 127) {
            asciiValue = 126;
        }
        asciiString += static_cast<char>(asciiValue);
    }

    return asciiString;
}

