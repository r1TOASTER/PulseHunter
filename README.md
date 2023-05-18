# PulseHunter

PulseHunter is a network tool for examining ports.
## Compiling

To compile PulseHunter, you will need a C++ compiler and the **iphlpapi** and **ws2_32** libraries.

Here is an example of how to compile PulseHunter in Visual Studio Code using the C++ extension:

1. Create a bin folder in the root directory of the project.
2. Open the project in Visual Studio Code.
3. Open the terminal by pressing ```Ctrl + Shift + ~```.
4. Run the following command to generate the executable file:
```
g++ -fdiagnostics-color=always -g -Wall -pedantic -Werror ${workspaceFolder}\\src\\*.cpp -o ${workspaceFolder}\\bin\\PulseHunter.exe -liphlpapi -lws2_32
```
This command will generate an executable file named PulseHunter.exe in the bin folder.
## Usage

To use PulseHunter, simply run the executable file and follow the prompts. The program currently allows you to check the open ports running on your pc (UDP and TCP).

Future updates to the program will include:

- [x] User interface
- [x] Scanning ports by their status
- [x] Scanning IP addresses that are open for the ports (host/source)

## License

+ Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, and distribute copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

+ The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

+ Any person who uses, copies, modifies, or distributes the Software must give appropriate credit, provide a link to the original source code, and indicate if changes were made. The Software is provided “as is”, without warranty of any kind, express or implied, including but not limited to the warranties of merchantability, fitness for a particular purpose and noninfringement. In no event shall the authors or copyright holders be liable for any claim, damages, or other liability, whether in an action of contract, tort, or otherwise, arising from, out of or in connection with the software or the use or other dealings in the software.
