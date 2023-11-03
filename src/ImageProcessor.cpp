#include "ImageProcessor.h"

ImageProcessor::ImageProcessor() {

}

ImageProcessor::~ImageProcessor() {


}


std::string ImageProcessor::decodeHiddenMessage(const ImageMatrix &img) {
    ImageSharpening sharpen;
    EdgeDetector edgeDetector;
    DecodeMessage decoder;

    ImageMatrix sharpenedImage = sharpen.sharpen(img, 2.0);
    std::vector<std::pair<int, int>> edgePixels = edgeDetector.detectEdges(sharpenedImage);

    return decoder.decodeFromImage(sharpenedImage, edgePixels);

}

ImageMatrix ImageProcessor::encodeHiddenMessage(const ImageMatrix &img, const std::string &message) {
    ImageSharpening sharpen;
    EdgeDetector edgeDetector;
    EncodeMessage encoder;

    ImageMatrix sharpenedImage = sharpen.sharpen(img, 2.0);
    std::vector<std::pair<int, int>> edgePixels = edgeDetector.detectEdges(img);

    return encoder.encodeMessageToImage(img, message, edgePixels);

}
