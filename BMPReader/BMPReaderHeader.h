#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <windows.h>
#include <fstream>


using namespace std;



class BMPReader {

private:
    int height, width;
    RGBTRIPLE* pixelBMP;

public:
    BMPReader() : width(0), height(0), pixelBMP(nullptr) {}

    void openBMP(const string& file) {

        ifstream bmpFile(file, ios::binary);

        // Чтение заголовка BMP
        BITMAPFILEHEADER fileHeader;
        bmpFile.read((char*)(&fileHeader), sizeof(fileHeader));

        BITMAPINFOHEADER infoHeader;
        bmpFile.read((char*)(&infoHeader), sizeof(infoHeader));


        //Проверка на битность(так же проверка на то что файл формата BMP
        if (fileHeader.bfType != 0x4D42 || (infoHeader.biBitCount != 24 && infoHeader.biBitCount != 32)) {
            cout << "Unsupported BMP format" << endl;

        }

        width = infoHeader.biWidth;
        height = infoHeader.biHeight;


        //Получаем количество пикселей
        pixelBMP = new RGBTRIPLE[width * height];

        // Чтение данных пикселей
        bmpFile.seekg(fileHeader.bfOffBits, std::ios::beg);
        for (int y = height - 1; y >= 0; --y) { // BMP хранит строки в обратном порядке
            for (int x = 0; x < width; ++x) {
                bmpFile.read((char*)(&pixelBMP[y * width + x]), sizeof(RGBTRIPLE));
            }
            // Пропуск заполнителей
            if (width % 4 != 0) {
                bmpFile.ignore(4 - (width * sizeof(RGBTRIPLE)) % 4);
            }
        }

        bmpFile.close();

    }

    void displayBMP() {

        if (!pixelBMP) {
            cout << "No image data to display" << std::endl;

        }


        for (int y = 0; y< height; ++y) {

            for (int x = 0; x < width; ++x) {
                RGBTRIPLE pixel = pixelBMP[y * width + x];
                if (pixel.rgbtRed == 0 && pixel.rgbtGreen == 0 && pixel.rgbtBlue == 0) {
                    cout << '+'; // Черный цвет
                }
                else if (pixel.rgbtRed == 255 && pixel.rgbtGreen == 255 && pixel.rgbtBlue == 255) {
                    cout << ' '; // Белый цвет
                }
                else {
                    cout << '?'; // Неизвестный цвет
                }
            }
            cout << endl;
        }
    }


    void closeBMP() {
        delete[] pixelBMP;
        pixelBMP = nullptr;
    }

};