# monpos
A tool to pixel perfectly position monitors on a Windows desktop.

If you have a Windows machine with more than one row of monitors you might have noticed that the Windows monitor alignment tool doesn't snap them on the corners properly.

-- insert screenshot here --

This tool aims to change this. The intended workflow is to 
1. roughly align the monitors with Windows native solution,
2. run this program once, to generate a monitor map file
3. use a text editor to change the alignment as wanted in the map file
4. run the program again with the updated map file to finally set your monitors

## map file content

```
# lines with # at the beginning are ignored
# list of monitors generated on 2020-06-05 00:08:03
# each line describes one found monitor
# first column is the number of the monitor
# second column pos x on the desktop
# second column pos y on the desktop
1,1920,1200
2,1920,1200
3,1920,1200
4,1920,1200
5,1920,1200
```
