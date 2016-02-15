#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

#include "lodepng.h"

const float kPI = 3.14159265358979323846f;

struct Point { float r; float g; float b; float a; };

float Distance(const Point &kPoint1, const Point &kPoint2) {
    return sqrtf(powf(kPoint1.r - kPoint2.r, 2.0f) + powf(kPoint1.g - kPoint2.g, 2.0f) + powf(kPoint1.b - kPoint2.b, 2.0f));
}

float GaussianKernel(const float kDistance, const float kBandwidth) {
    return (1.0f / (sqrtf(2.0f * kPI) * kBandwidth)) * expf(-0.5f * powf(kDistance / kBandwidth, 2.0f));
}

void ShiftPoint(const Point &kPoint, const std::vector<Point> kPoints, const float kBandwidth, Point &shift) {
    shift.r = 0.0f;
    shift.g = 0.0f;
    shift.b = 0.0f;
    float scale = 0.0f;
    for (int i = 0; i < kPoints.size(); ++i) {
        float distance = Distance(kPoint, kPoints[i]);
        float weight = GaussianKernel(distance, kBandwidth);
        shift.r += weight * kPoints[i].r;
        shift.g += weight * kPoints[i].g;
        shift.b += weight * kPoints[i].b;
        scale += weight;
    }
    shift.r /= scale;
    shift.g /= scale;
    shift.b /= scale;
}

void MeanShift(const float kBandwidth, const float kEpsilon, const int kMaxIterations, std::vector<Point> &points) {
    float difference_distance = 0.0f;
    int iteration = 0;

    std::vector<bool> still_shifting(points.size(), true);

    do {
        difference_distance = 0.0f;
        for (int i = 0; i < points.size(); ++i) {
            if (!still_shifting[i]) {
                continue;
            }

            Point new_point = points[i];
            ShiftPoint(points[i], points, kBandwidth, new_point);
            float distance = Distance(points[i], new_point);

            if (distance > difference_distance) {
                difference_distance = distance;
            }

            if (distance < kEpsilon) {
                still_shifting[i] = false;
            }

            points[i] = new_point;
        }
        ++iteration;
    } while ((difference_distance > kEpsilon) && (iteration < kMaxIterations));
}

void ReadPNGFile(const char *file_name, int &width, int &height, std::vector<Point> &pixels) {
    std::vector<unsigned char> image;

    unsigned int w;
    unsigned int h;
    unsigned int error = lodepng::decode(image, w, h, file_name);
    if (error) {
        printf("Failed to read input file: %s", lodepng_error_text(error));
    }
    width = static_cast<int>(w);
    height = static_cast<int>(h);

    pixels.resize(static_cast<unsigned int>(height * width));
    int pixel = 0;
    for (int channel = 0; channel < image.size(); channel+=4) {
        Point p = {
                static_cast<float>(image[channel]),
                static_cast<float>(image[channel + 1]),
                static_cast<float>(image[channel + 2]),
                static_cast<float>(image[channel + 3])
        };
        pixels[pixel] = p;
        ++pixel;
    }
}

void WritePNGFile(const char *file_name, const int &width, const int &height, std::vector<Point> &pixels) {
    std::vector<unsigned char> image;

    for (int pixel = 0; pixel < pixels.size(); ++pixel) {
        image.push_back(static_cast<unsigned char>(pixels[pixel].r));
        image.push_back(static_cast<unsigned char>(pixels[pixel].g));
        image.push_back(static_cast<unsigned char>(pixels[pixel].b));
        image.push_back(static_cast<unsigned char>(pixels[pixel].a));
    }

    unsigned int error = lodepng::encode(file_name, image, static_cast<unsigned int>(width), static_cast<unsigned int>(height));
    if (error) {
        printf("Failed to save output file: %s", lodepng_error_text(error));
    }
}

int main() {
    const float kBandwidth = 10.0f;
    const float kEpsilon = 0.1f;
    const int kMaxIterations = 100;
    const std::string kInputFileName = "input.png";
    const std::string kOutputFileName = "output.png";
    int width = 0;
    int height = 0;
    std::vector<Point> points;

    ReadPNGFile(kInputFileName.c_str(), width, height, points);
    MeanShift(kBandwidth, kEpsilon, kMaxIterations, points);
    WritePNGFile(kOutputFileName.c_str(), width, height, points);

    return 0;
}

