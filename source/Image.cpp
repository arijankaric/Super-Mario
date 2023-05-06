#include "../include/Image.hpp"

namespace WrapperRAII
{

Image::Image(const char* imagePath)
{
    // Get the current working directory
    char currentDir[MAX_PATH];
    GetCurrentDirectoryA(MAX_PATH, currentDir);

    // Convert the relative path to a wide-character string
    wchar_t wideImagePath[MAX_PATH];
    swprintf(wideImagePath, MAX_PATH, L"%hs", imagePath);

    // Construct the full path to the image file
    wchar_t fullPath[MAX_PATH];
    swprintf(fullPath, MAX_PATH, L"%hs%s", currentDir, wideImagePath);

    wchar_t currentPath[MAX_PATH];
    swprintf(currentPath, MAX_PATH, L"%hs", currentDir);

    wcscat(currentPath, wideImagePath);
    // Load the image using the LoadImage function

    // printf("Image path: %s\n", imagePath);
    // std::wcout << "Wide Image path: " << wideImagePath << std::endl;
    // std::wcout << "Full Image path: " << fullPath << std::endl;
    // std::wcout << "Current dir: " << currentPath << std::endl;
    this->hBitmap_ = (HBITMAP)LoadImage(NULL, currentPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    if(this->hBitmap_ == 0) {
        std::cout << "Couldn't load image" << std::endl;
        std::wcout << "Curent dir: " << currentPath << std::endl;
        std::cout << "Image: " << this->hBitmap_ << std::endl;
    }


    if (this->hBitmap_ == NULL)
    {
        // Handle error loading image
    }
}

WrapperRAII::Image::~Image()
{
    DeleteObject(this->hBitmap_);
}

HBITMAP WrapperRAII::Image::getHBitmap()
{
    return this->hBitmap_;
}

}
