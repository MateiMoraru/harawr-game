#include "settings.h"

Settings::Settings()
{
    settings_file.open(PATH_TO_FILE);

    if (!settings_file)
    {
        cerr << "Failed to open settings file (" << PATH_TO_FILE << ")" << endl;
        return;
    }
    
    char line[128];
    string setting;

    while(settings_file.getline(line, 128))
    {
        setting = strtok(line, SEP);
        if(setting == "vsync")
        {
            setting = strtok(NULL, SEP);
            vsync = (setting == "true");
        }
        else if(setting == "fullscreen")
        {
            setting = strtok(NULL, SEP);
            fullscreen = (setting == "true");
        }
        else if(setting == "fps")
        {
            setting = strtok(NULL, SEP);
            fps = stoi(setting);
        }
        else if(setting == "width")
        {
            setting = strtok(NULL, SEP);
            width = stoi(setting);
        } 
        else if(setting == "height")
        {
            setting = strtok(NULL, SEP);
            height = stoi(setting);
        }
    }

    cout << "Settings: " << endl;

    cout << "\tvsync: " << vsync << endl
         << "\tfullscreen: " << fullscreen << endl
         << "\tFPS: " << fps << endl
         << "\twidth: " << width << endl
         << "\theight: " << height << endl;
}


void Settings::set_screen_size(int screen_width, int screen_height) { width = screen_width; height = screen_height;}

/*
#include "settings.h"
#include <sstream>

Settings::Settings()
{
    settings_file.open(PATH_TO_FILE);
    if (!settings_file)
    {
        cerr << "Failed to open settings file (" << PATH_TO_FILE << ")" << endl;
        return;
    }

    string line;
    while (getline(settings_file, line))
    {
        istringstream iss(line);
        string key, value;
        if (!(iss >> key >> value)) continue;
        
        cout << (key == "vsync") << " " << value << endl;

        if (key == "vsync")
        {
            cout << "A " << (value == "true") << endl;
            vsync = (value == "true");
        }
        else if (key == "fullscreen")
            fullscreen = (value == "true");
        else if (key == "fps")
            fps = std::stoi(value);
        else if (key == "width")
            width = std::stoi(value);
        else if (key == "height")
            height = std::stoi(value);
    }
    cout << endl;

    cout << "vsync: " << vsync << endl
         << "fullscreen: " << fullscreen << endl
         << "FPS: " << fps << endl
         << "width: " << width << endl
         << "height: " << height << endl;
} */