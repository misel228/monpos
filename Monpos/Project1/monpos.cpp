#include <cassert>
#include <Windows.h>
#include <iostream>
#include <fstream>

#define MAX_NUM_MONITORS 10 //the regular windows desktop applet doesn't support more than 10 screens. So this is hardcoded.

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

int DetectMonitors()
{
    int Count = 0;
    if (EnumDisplayMonitors(NULL, NULL, MonitorEnumProc, (LPARAM)&Count))
        return Count;
    return -1;//signals an error
}

void write_file() {

    int i = 0;
    std::ofstream fout("afile.txt");
    while (monitor_dimensions[i] != NULL) {
        fout << i << "," << monitor_dimensions[i]->left << "," << monitor_dimensions[i]->right << "," << monitor_dimensions[i]->top << "," << monitor_dimensions[i]->bottom << std::endl;
        i++;
    }
    fout.close();
}


int main() {
    int monitor_count;

    monitor_count = DetectMonitors();
    if (monitor_count == -1) {
        std::cout << "Could not detect monitors" << std::endl;
        return -1;
    }

	
    write_file();
	return 0;
}

