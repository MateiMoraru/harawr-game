#ifndef SETTINGS_H
#define SETTINGS_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
using namespace std;

class Settings
{
    public:
        Settings();
        
        bool get_vsync() const { return vsync; }
        bool get_fullscreen() const { return fullscreen; }
        bool get_fps() const { return fps; }
        int get_width() const { return width; }
        int get_height() const { return height; }

        void set_screen_size(int screen_width, int screen_height);

    private:
        ifstream settings_file;
        const string PATH_TO_FILE = "assets/data/settings.txt";
        const char* SEP = ": ";
        bool vsync, fullscreen;
        int width, height;
        int fps;
};

#endif