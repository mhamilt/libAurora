//
//  main.cpp
//  png_dump
//
//  Created by admin on 25/07/2026.
//

#include <fstream>
#include <iostream>
#include <map>
#include "../src/stickers.h"

struct PngData
{
    const unsigned char* data;
    std::size_t size;
};


int main()
{


    std::map<std::string, PngData> png_files =
    {
        { "ap_logo_png",     { ap_logo_png,     sizeof(ap_logo_png) } },
        { "ssg_logo_png",    { ssg_logo_png,    sizeof(ssg_logo_png) } },
        { "sti_logo_png",    { sti_logo_png,    sizeof(sti_logo_png) } },
        { "tha_logo_png",    { tha_logo_png,    sizeof(tha_logo_png) } },
        { "xfn_logo_png",    { xfn_logo_png,    sizeof(xfn_logo_png) } },
        { "conv_logo_png",   { conv_logo_png,   sizeof(conv_logo_png) } },
        { "kirk_logo_png",   { kirk_logo_png,   sizeof(kirk_logo_png) } },
        { "Aurora_logo_png", { Aurora_logo_png, sizeof(Aurora_logo_png) } },
    };

    for (const auto& [name, png] : png_files)
    {
        std::cout << "/Users/admin/Desktop/logos/" + name + ".png" << '\n';
        std::ofstream out("/Users/admin/Desktop/logos/" + name + ".png", std::ios::binary);
        out.write(reinterpret_cast<const char*>(png.data), png.size);
    }

    return 0;
}
