/*
    В данной задаче можно реализовать два разных вида поиска информации по BMP файлу,
    первое это самомтоятельно искать нужные данные перемещаеясь с помощью битов по файлу
    (пример  bmpFile.seekg(28, ios::beg);)
    и второй как использовалось в данной программе через готовую структуру с помощью библиотеки windows.h
    можно посмотреть в заголовоночном файле BMPReaderHeader.h
    */

#include "BMPReaderHeader.h"

int main(int argc, char* argv[])
{
    BMPReader bmpReader;
    bmpReader.openBMP(argv[1]);
    bmpReader.displayBMP();
    bmpReader.closeBMP();
}




