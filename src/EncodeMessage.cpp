#include "EncodeMessage.h"
#include <cmath>
#include <bitset>



// Default Constructor
EncodeMessage::EncodeMessage() {

}

// Destructor
EncodeMessage::~EncodeMessage() {
    
}

// Function to encode a message into an image matrix
ImageMatrix EncodeMessage::encodeMessageToImage(const ImageMatrix &img, const std::string &message, const std::vector<std::pair<int, int>>& positions) {
    if (message.empty()) {
        return img;
    }

    // Transform the characters of the message
    std::string transformedMessage;
    for (int i = 0; i < message.length(); i++) {
        if (i % 2 == 0) {
            transformedMessage += static_cast<char>(message[i] + (i + 1));
        } else {
            transformedMessage += message[i];
        }
    }

    // Apply right circular shifting
    int shift = std::floor(transformedMessage.length() / 2.0);
    transformedMessage = transformedMessage.substr(shift) + transformedMessage.substr(0, shift);

    // Convert the transformed message into binary
    std::string binaryMessage;
    for (char c : transformedMessage) {
        binaryMessage += std::bitset<8>(c).to_string().substr(1, 7);
    }

    if (positions.size() < binaryMessage.length()) {
        return img;
    }

    // Embed the binary message into the image
    ImageMatrix encodedImage = img;
    for (int i = 0; i < binaryMessage.length(); i++) {
        int pixelValue = encodedImage.get_data(positions[i].first, positions[i].second);
        int binaryValue = binaryMessage[i] - '0';
        pixelValue = (pixelValue & ~1) | binaryValue;
        encodedImage.set_data(positions[i].first, positions[i].second, pixelValue);
    }

    return encodedImage;

}
