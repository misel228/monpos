# monpos
A tool to pixel perfectly position monitors on a Windows desktop.

If you have a Windows machine with more than one row of monitors you might have noticed that the Windows monitor alignment tool doesn't snap them on the corners properly.

![Multi monitor Desktop misaligned](https://raw.githubusercontent.com/misel228/monpos/main/images/desktop.png "Multi monitor Desktop misaligned")

If you look closely you can see that the edges don't line up perfectly. Using the integrated monitor arrangement tool it's next to impossible to snap the screens together perfectly.
![Corner Zoom](https://raw.githubusercontent.com/misel228/monpos/main/images/desktop_zoom_mismatched_corners.png "Corner Zoom")


This tool aims to change this. The intended workflow is to 
1. roughly align the monitors with Windows native solution,
2. run this program once, to generate a monitor map file
3. use a text editor to change the alignment as wanted in the map file*
4. run the program again with the updated map file to finally set your monitors

*Monitors that are already in the correct position should be commented out. I encountered a but where the monitors were seemingly shuffled and I don't know why. But changing only the ones that needed correction solved that problem.

## map file content

```
# lines with # at the beginning are ignored
# list of monitors generated on 2020-06-05 00:08:03
# each line describes one found monitor
# 1st column - the number of the monitor
# 2nd column - left 
# 3rd column - top
0,0,0
1,-1920,-1196
2,0,-1200
3,1920,0
4,-1931,4
```
