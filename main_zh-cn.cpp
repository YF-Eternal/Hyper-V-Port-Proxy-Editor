#include <stdio.h>
#include <stdlib.h> 
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <windows.h>
#include <conio.h>
#include <string>
#include <sstream>
#include <limits>

using namespace std;


// ִ��������ؽ��
string executeCommand(const char* cmd) {
    char buffer[128];
    string result = "";
    FILE* pipe = _popen(cmd, "r");

    if (!pipe) {
        HANDLE handle;
        handle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(handle, 0x0C);
        cout << "�޷�ִ������!\n";
        return "";
    }

    while (!feof(pipe)) {
        if (fgets(buffer, 128, pipe) != NULL)
            result += buffer;
    }

    _pclose(pipe);
    return result;
}

// ��ʾ���ж˿�ӳ��
void showPortMappings() {
    HANDLE handle;
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, 0x0F);
    string result = executeCommand("netsh interface portproxy show all");
    cout << result << endl;
    SetConsoleTextAttribute(handle, 0x0B);
    printf("\n����������������˵�...");
    int ch = _getch();
}

// ��Ӷ˿�ӳ��
void addPortMapping(const string& listenAddress, const string& listenPort, const string& connectAddress, const string& connectPort) {
    char command[200];
    snprintf(command, sizeof(command), "netsh interface portproxy add v4tov4 listenport=%s listenaddress=%s connectport=%s connectaddress=%s",
        listenPort.c_str(),
        listenAddress.c_str(),
        connectPort.c_str(),
        connectAddress.c_str());

    executeCommand(command);
    HANDLE handle;
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, 0x0A);
    cout << "\n�˿�ӳ������ӣ�" << listenAddress << ":" << listenPort << " -> " << connectAddress << ":" << connectPort << endl;
    SetConsoleTextAttribute(handle, 0x0B);
    printf("\n����������������˵�...");
    int ch = _getch();
}

// ɾ���˿�ӳ��
void removePortMapping(const string& listenAddress, const string& listenPort) {
    char command[200];
    snprintf(command, sizeof(command), "netsh interface portproxy delete v4tov4 listenport=%s listenaddress=%s", listenPort.c_str(), listenAddress.c_str());
    executeCommand(command);
    HANDLE handle;
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, 0x0A);
    cout << "\n�˿�ӳ����ɾ����" << listenAddress << ":" << listenPort << endl;
    SetConsoleTextAttribute(handle, 0x0B);
    printf("\n����������������˵�...");
    int ch = _getch();
}

int main() {
    string listenAddress, listenPort, connectAddress, connectPort;
    int choice;

    system("title Hyper-V Port Proxy Editor");
    do {
        system("cls");
        HANDLE handle;
        handle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(handle, 0x0C);
        cout << "|  |                  |    |  |~~\\        |   |~~\\               |~~   |' |        \n";
        cout << "|--|\\  /|~~\\/~/|/~\\--- \\  /   |__//~\\|/~\\~|~  |__/|/~\\/~\\\\/\\  /  |--/~~||~|~/~\\|/~\\\n";
        cout << "|  | \\/ |__/\\/_|        \\/    |   \\_/|    |   |   |   \\_//\\ \\/   |__\\__|| | \\_/|   \n";
        cout << "    _/  |                                                  _/                      \n";
        SetConsoleTextAttribute(handle, 0x1F);
        cout << "  V1.0  \n";
        SetConsoleTextAttribute(handle, 0x0E);
        cout << "------------------------------------------------------\n";
        cout << "1. ��ʾ���ж˿�ӳ��\n";
        cout << "2. ��Ӷ˿�ӳ��\n";
        cout << "3. ɾ���˿�ӳ��\n\n";
        cout << "0. �˳�\n";
        cout << "------------------------------------------------------\n";
        SetConsoleTextAttribute(handle, 0x0F);
        cout << "������(1, 2, 3, 0): ";
        cin >> choice;

        switch (choice) {
        case 1:
            showPortMappings();
            break;
        case 2: {
            cout << "\n������������ַ�������˿ڡ��������ַ��������˿ڣ��Կո�ָ�\n";
            SetConsoleTextAttribute(handle, 0x09);
            cout << ">";

            cin.ignore(INT_MAX, '\n'); // ���֮ǰ�Ļ��з�

            // ��ȡ����
            string inputLine;
            getline(cin, inputLine);

            // ʹ�� stringstream ����ֵ
            istringstream iss(inputLine);

            // ����Ƿ���ȡ�ɹ�������ȷ�����������ַ�δ����ȡ
            if (!(iss >> listenAddress >> listenPort >> connectAddress >> connectPort) || iss.rdbuf()->in_avail() != 0) {
                SetConsoleTextAttribute(handle, 0x0C);
                cout << "\n������Ч����ʹ�ÿո�ָ�������ַ�������˿ڡ��������ַ��������˿�\n";
                SetConsoleTextAttribute(handle, 0x0B);
                printf("\n����������������˵�...");
                int ch = _getch();

                break;  // �˳���ǰ case
            }
            else {
                addPortMapping(listenAddress, listenPort, connectAddress, connectPort);
                break;
            }
        }
        case 3: {
            cout << "\n������Ҫɾ����������ַ�������˿�, �Կո�ָ�\n";
            SetConsoleTextAttribute(handle, 0x09);
            cout << ">";

            cin.ignore(INT_MAX, '\n'); // ���֮ǰ�Ļ��з�

            // ��ȡ����
            string inputLine;
            getline(cin, inputLine);

            // ʹ�� stringstream ����ֵ
            istringstream iss(inputLine);

            // ����Ƿ���ȡ�ɹ�������ȷ�����������ַ�δ����ȡ
            if (!(iss >> listenAddress >> listenPort) || iss.rdbuf()->in_avail() != 0) {
                SetConsoleTextAttribute(handle, 0x0C);
                cout << "\n������Ч����ʹ�ÿո�ָ�������ַ�������˿�\n";
                SetConsoleTextAttribute(handle, 0x0B);
                printf("\n����������������˵�...");
                int ch = _getch();

                break;  // �˳���ǰ case
            }
            else {
                removePortMapping(listenAddress, listenPort);
                break;
            }
        }
        case 0:
            break;
        default:
            SetConsoleTextAttribute(handle, 0x0C);
            cout << "\n��Ч��ѡ��!\n";
            SetConsoleTextAttribute(handle, 0x0B);
            printf("\n����������������˵�...");
            int ch = _getch();
        }
    } while (choice != 0);

    return 0;
}