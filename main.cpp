#include <iostream>
#include <cstdlib>
#include <string>
#include <termios.h>
#include <unistd.h>

using namespace std;

string getPassword(){
    string password;
    char c;

    termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);

    newt = oldt;
    newt.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    while ((c = getchar()) != '\n')
    {
        password += c;
        cout << '*';
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    cout << '\n';

    return password;
}

int main(){
    string name, password;

    system("nmcli radio wifi on");
    system("PAGER=cat nmcli device wifi list");

    cout << "\n$$$ SSID: ";
    getline(cin, name);

    cout << "$$$ Password: ";
    password = getPassword();

    string command = "nmcli device wifi connect \"" + name +
                     "\" password \"" + password + "\"";

    system(command.c_str());

    return 0;
}
