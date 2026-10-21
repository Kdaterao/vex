#include <iostream>
#include <filesystem>
#include <string>
#include <libserial/SerialPort.h>

namespace fs = std::filesystem;

int main() {



    for (const auto& entry : fs::directory_iterator("/dev")) {

        std::string name = entry.path().filename().string();

        // Look for UART devices
        if (name.rfind("ttyS", 0) != 0 &&
            name.rfind("ttyAMA", 0) != 0) {
            continue;
        }

        std::string port = entry.path().string();
        

        //testing output script...
        try {
            LibSerial::SerialPort uart;

            uart.Open(port);
            uart.SetBaudRate(
                LibSerial::BaudRate::BAUD_115200
            );

            std::cout << "Testing " << port << "...\n";

            uart.Write("UART_TEST\n");

            std::string response;
            uart.ReadLine(response, '\n', 500);

            if (response == "UART_TEST") {
                std::cout << "Working UART: "
                          << port << "\n";
            }

            uart.Close();
        }
        catch (const std::exception& e) {
            std::cout << port << ": "
                      << e.what() << "\n";
        }
    }

    return 0;
}
