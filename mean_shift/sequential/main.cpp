#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

#include "png.h"

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
    FILE *fp = fopen(file_name, "rb");
    if (!fp) {
        printf("Failed to open input file!");
    }

    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png) {
        printf("Failed to create PNG read struct!");
    }

    png_infop info = png_create_info_struct(png);
    if (!png) {
        printf("Failed to create PNG info struct!");
    }

    if (setjmp(png_jmpbuf(png))) {
        printf("Failed to set jmp!");
    }

    png_init_io(png, fp);

    png_read_info(png, info);

    width = png_get_image_width(png, info);
    height = png_get_image_height(png, info);
    png_byte color_type = png_get_color_type(png, info);
    png_byte bit_depth = png_get_bit_depth(png, info);

    // Read any color_type into 8bit depth, RGBA format.
    // See http://www.libpng.org/pub/png/libpng-manual.txt

    if(bit_depth == 16)
        png_set_strip_16(png);

    if(color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_palette_to_rgb(png);

    // PNG_COLOR_TYPE_GRAY_ALPHA is always 8 or 16bit depth.
    if(color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
        png_set_expand_gray_1_2_4_to_8(png);

    if(png_get_valid(png, info, PNG_INFO_tRNS))
        png_set_tRNS_to_alpha(png);

    // These color_type don't have an alpha channel then fill it with 0xff.
    if(color_type == PNG_COLOR_TYPE_RGB ||
       color_type == PNG_COLOR_TYPE_GRAY ||
       color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_filler(png, 0xFF, PNG_FILLER_AFTER);

    if(color_type == PNG_COLOR_TYPE_GRAY ||
       color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
        png_set_gray_to_rgb(png);

    png_read_update_info(png, info);

    int row_bytes = png_get_rowbytes(png, info);
    png_bytep* row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * height);
    for (int y = 0; y < height; ++y) {
        row_pointers[y] = (png_byte*)malloc(sizeof(png_byte) * row_bytes);
    }

    png_read_image(png, row_pointers);

    pixels.resize(static_cast<unsigned int>(height * width));
    int i = 0;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < row_bytes; x+=4) {
            Point p = {
                    static_cast<float>(row_pointers[y][x]),
                    static_cast<float>(row_pointers[y][x + 1]),
                    static_cast<float>(row_pointers[y][x + 2]),
                    static_cast<float>(row_pointers[y][x + 3])
            };
            pixels[i] = p;
            ++i;
        }
        free(row_pointers[y]);
    }
    free(row_pointers);

    fclose(fp);
}

void WritePNGFile(const char *file_name, const int &width, const int &height, std::vector<Point> &pixels) {
    FILE *fp = fopen(file_name, "wb");
    if (!fp) {
        printf("Failed to open input file!");
    }

    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png) {
        printf("Failed to create PNG read struct!");
    }

    png_infop info = png_create_info_struct(png);
    if (!png) {
        printf("Failed to create PNG info struct!");
    }

    if (setjmp(png_jmpbuf(png))) {
        printf("Failed to set jmp!");
    }

    png_init_io(png, fp);

    png_set_IHDR(png, info, width, height, 8, PNG_COLOR_TYPE_RGBA, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
    png_write_info(png, info);

    int row_bytes = width * 4;
    png_bytep* row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * height);
    int i = 0;
    for (int y = 0; y < height; ++y) {
        row_pointers[y] = (png_byte*)malloc(sizeof(png_byte) * row_bytes);
        for (int x = 0; x < row_bytes; x+=4) {
            row_pointers[y][x] = static_cast<uint8_t>(pixels[i].r);
            row_pointers[y][x + 1] = static_cast<uint8_t>(pixels[i].g);
            row_pointers[y][x + 2] = static_cast<uint8_t>(pixels[i].b);
            row_pointers[y][x + 3] = static_cast<uint8_t>(pixels[i].a);
            ++i;
        }
    }

    png_write_image(png, row_pointers);
    png_write_end(png, NULL);

    for (int y = 0; y < height; ++y) {
        free(row_pointers[y]);
    }
    free(row_pointers);

    fclose(fp);
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

