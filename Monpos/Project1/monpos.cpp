#include <cassert>
#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#define MAX_NUM_MONITORS 10 //the regular windows desktop applet doesn't support more than 10 screens. So this is hardcoded.
#define FILE_NAME "monitor_map.txt"

LPRECT monitor_dimensions[10];


BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData)
{
    int* Count = (int*)dwData;

    // return if we're above to avoid writing into invalid memory
    if (*Count >= MAX_NUM_MONITORS) {
        return FALSE;
    }

    monitor_dimensions[*Count] = new RECT();
    CopyRect(monitor_dimensions[*Count], lprcMonitor);
    (*Count)++;
    return TRUE;
}

// Thank you stack overflow 
// https://stackoverflow.com/questions/7767036/how-do-i-get-the-number-of-displays-in-windows
int DetectMonitors()
{
    int Count = 0;
    if (EnumDisplayMonitors(NULL, NULL, MonitorEnumProc, (LPARAM)&Count))
        return Count;
    return -1;//signals an error
}

void write_file() {

    int i = 0;
    std::ofstream fout(FILE_NAME);

    
    fout << "# monpos generated monitor map" << std::endl;
   
    while (monitor_dimensions[i] != NULL) {
        fout << i << "," << monitor_dimensions[i]->left << "," << monitor_dimensions[i]->top << std::endl;
        i++;
    }
    fout.close();
}


int main() {
    int monitor_count;

    std::ifstream map_file;
    map_file.open(FILE_NAME);

    //if no file is found detect monitors and write a new file
    if (map_file.fail()) {
        monitor_count = DetectMonitors();
        if (monitor_count == -1) {
            std::cout << "Could not detect monitors" << std::endl;
            return 1;
        }
        write_file();
        return 0;
    }

    //read file line by line
    std::string line;
    while (std::getline(map_file, line))
    {
        if (line[0] == '#') {
            continue;
        }
        std::vector<int> vect;
        std::cout << line << std::endl;

        std::stringstream ss(line);

        for (int i; ss >> i;) {
            vect.push_back(i);
            if (ss.peek() == ',')
                ss.ignore();
        }

        //if vect doesn't contain 3 ints, skip
        //(basically "ignore empty lines")
        if (vect.size() != 3) {
            continue;
        }
        
        DEVMODEW mode{ {}, {}, {}, sizeof(DEVMODEW), 0 };

        mode.dmFields = DM_POSITION;
        mode.dmPosition.x = vect[1];
        mode.dmPosition.y = vect[2];

        DISPLAY_DEVICEW info{ sizeof(DISPLAY_DEVICEW) };

        //load current Display settings
        auto const result0 = EnumDisplayDevicesW(NULL, vect[0], &info, EDD_GET_DEVICE_INTERFACE_NAME);
        if (result0 == 0) {
            return 2;
        }

        //change current display
        auto const result1 = ChangeDisplaySettingsExW(info.DeviceName, &mode, NULL, CDS_GLOBAL | CDS_UPDATEREGISTRY, NULL);
        if (result1 != DISP_CHANGE_SUCCESSFUL) {
            return 3;
        }
    }
	
    return 0;
}

