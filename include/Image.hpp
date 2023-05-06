#pragma once
#define _UNICODE
#define UNICODE
#include <windows.h>
#include <iostream>
#include <stdio.h>

namespace WrapperRAII
{

class Image
{
private:
    HBITMAP hBitmap_;
public:
    Image(const char* imagePath);
    ~Image();
    HBITMAP getHBitmap();
};

}
