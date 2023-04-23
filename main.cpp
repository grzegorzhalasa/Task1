#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
using namespace std;
#define MAX_COLORS 1000
#define MAX_COLOR_NAME_LENGTH 100
#define HEX_LENGTH 8

struct Color {
    int red;
    int green;
    int blue;
    int alpha;

};

struct Color colors[MAX_COLORS];
int numColors = 0;

char hex[MAX_COLORS][HEX_LENGTH];

void parseColor(char* colorString, struct Color* color);
void parseHex(char* hexString, struct Color* color);
void mixColors();
void lowestColor();
void highestColor();
void mixSaturateColor();
void printColor(struct Color color);

int main(int argc, char* argv[]) {
    FILE* fp;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    int i;

    fp = fopen("colors.txt", "r");
    if (fp == NULL) {
        printf("Could not open colors.txt\n");
        return 1;
    }

    while ((read = getline(&line, &len, fp)) != -1) {
        line[strcspn(line, "\r\n")] = '\0'; // remove newline characters
        if (read > 0 && read <= MAX_COLOR_NAME_LENGTH) {
            struct Color color;
            if (line[0] == '#') {
                parseHex(line, &color);
            } else {
                parseColor(line, &color);
            }
            colors[numColors] = color;
            numColors++;
        }
    }

    fclose(fp);
    if (line) {
        free(line);
    }

    // parse command line arguments
    char* mode = "mix";
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--mode") == 0 || strcmp(argv[i], "-m") == 0) {
            i++;
            if (i < argc) {
                mode = argv[i];
            }
        }
    }

    if (strcmp(mode, "mix") == 0) {
        mixColors();
    } else if (strcmp(mode, "lowest") == 0) {
        lowestColor();
    } else if (strcmp(mode, "highest") == 0) {
        highestColor();
    } else if (strcmp(mode, "mix-saturate") == 0) {
        mixSaturateColor();
    } else {
        printf("Invalid mode specified.\n");
        return 1;
    }

    return 0;
}

void parseColor(char* colorString, struct Color* color) {
    int red, green, blue, alpha;
    sscanf(colorString, "%d,%d,%d,%d", &red, &green, &blue, &alpha);
    color->red = red;
    color->green = green;
    color->blue = blue;
    color->alpha = alpha;
}

void parseHex(char* hexString, struct Color* color) {
    int red, green, blue, alpha;
    sscanf(hexString, "#%02x%02x%02x%02x", &red, &green, &blue, &alpha);
    color->red = red;
    color->green = green;
    color->blue = blue;
    color->alpha = alpha;
    snprintf(hex[numColors], HEX_LENGTH, "#%02x%02x%02x%02x", red, green, blue, alpha);
}

void mixColors() {
    if (numColors == 0) {
        printf("No colors specified.\n");
        return;
            int i;
    struct Color color;
    double red = 0.0, green = 0.0, blue = 0.0, alpha = 0.0;
    for (i = 0; i < numColors; i++) {
        red += (double) colors[i].red;
        green += (double) colors[i].green;
        blue += (double) colors[i].blue;
        alpha += (double) colors[i].alpha;
    }
    color.red = (int) round(red / (double) numColors);
    color.green = (int) round(green / (double) numColors);
    color.blue = (int) round(blue / (double) numColors);
    color.alpha = (int) round(alpha / (double) numColors);

    printColor(color);
}
}

