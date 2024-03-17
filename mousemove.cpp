#include "mousemove.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include <vector>
#include <algorithm>



void Wait(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

void seedRandomGenerator() {
    srand(static_cast<unsigned int>(time(nullptr)));
}

POINT getRandomPointInRange(int minX, int minY, int maxX, int maxY) {
    POINT result;
    result.x = rand() % (maxX - minX + 1) + minX;
    result.y = rand() % (maxY - minY + 1) + minY;
    return result;
}

POINT interpolatePoints(POINT start, POINT end, double t) {
    POINT result;
    result.x = start.x + static_cast<int>((end.x - start.x) * t);
    result.y = start.y + static_cast<int>((end.y - start.y) * t);
    return result;
}

POINT calculateQuadraticBezierPointWithNoiseAndSmoothing(POINT p0, POINT p1, POINT p2, double t, double noiseFactor, double smoothingFactor) {
    POINT result;
    
    // Generate random noise for control points
    double noiseX = (rand() % 100 - 50) / 100.0 * noiseFactor;
    double noiseY = (rand() % 100 - 50) / 100.0 * noiseFactor;

    // Update control points with noise and smoothing
    static POINT controlPoint1 = p1;
    static POINT controlPoint2 = p1;
    controlPoint1.x = p1.x + (controlPoint1.x - p1.x) * smoothingFactor + noiseX;
    controlPoint1.y = p1.y + (controlPoint1.y - p1.y) * smoothingFactor + noiseY;
    controlPoint2.x = p1.x + (controlPoint2.x - p1.x) * smoothingFactor + noiseX;
    controlPoint2.y = p1.y + (controlPoint2.y - p1.y) * smoothingFactor + noiseY;

    double u = 1.0 - t;
    result.x = static_cast<int>(u * u * p0.x + 2 * u * t * controlPoint1.x + t * t * p2.x);
    result.y = static_cast<int>(u * u * p0.y + 2 * u * t * controlPoint1.y + t * t * p2.y);

    return result;
}



void moveMouseRandomCurved(int startX, int startY, int endX, int endY, int durationMs) {
    seedRandomGenerator();

    SetCursorPos(startX, startY);

    int dx = endX - startX;
    int dy = endY - startY;
    double distance = std::sqrt(dx * dx + dy * dy);

    auto startTime = std::chrono::steady_clock::now();

    bool useBezierCurve = rand() % 2 == 0; // Randomly choose between using Bezier curve or interpolation

    POINT currentPoint;

    if (useBezierCurve) {
        for (double t = 0.0; t <= 1.0; t += 0.01) {
            currentPoint = calculateQuadraticBezierPointWithNoiseAndSmoothing(
                {startX, startY}, {startX + dx / 2, startY + dy / 2}, {endX, endY}, t, 10.0, 0.99);
            SetCursorPos(currentPoint.x, currentPoint.y);
            Wait(10);
        }
    } else {
        const double totalTime = static_cast<double>(durationMs);
        while (true) {
            auto currentTime = std::chrono::steady_clock::now();
            double elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();
            double t = elapsedTime / totalTime;

            if (t >= 1.0) {
                SetCursorPos(endX, endY);
                break;
            }

            double ease = 0.5 - 0.5 * cos(3.14159265358979323846 * t); // Cosine easing function for smoother movement

            currentPoint = interpolatePoints({startX, startY}, {endX, endY}, ease);

            SetCursorPos(currentPoint.x, currentPoint.y);
            Wait(10);
        }
    }

    // Ensure the cursor reaches the end position
    SetCursorPos(endX, endY);
}

void Click(int delayBetweenClicksMs) {
    INPUT input = {0};
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    SendInput(1, &input, sizeof(INPUT));
    input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    SendInput(1, &input, sizeof(INPUT));

    if (delayBetweenClicksMs > 0) {
        std::this_thread::sleep_for(std::chrono::milliseconds(delayBetweenClicksMs));
    }
}

void moveMouseRandomCurvedClient(int windowX, int windowY, int durationMs) {

    HWND activeWindow = GetForegroundWindow();
    if (activeWindow == NULL) {
        std::cerr << "Failed to get handle to the active window." << std::endl;
    }

    // Convert window coordinates to screen coordinates
    POINT screenPoint = { windowX, windowY };
    ClientToScreen(activeWindow, &screenPoint);

    // Get the current mouse position
    POINT currentPosition;
    GetCursorPos(&currentPosition);

    // Move the mouse from its current position to the specified position within the client area
    moveMouseRandomCurved(currentPosition.x, currentPosition.y, screenPoint.x, screenPoint.y, durationMs);

}


// Global variable to store the handles of all instances of the target window
std::vector<HWND> targetWindowInstances;

// Callback function for EnumWindows
BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
    char windowTitle[256];
    GetWindowTextA(hwnd, windowTitle, sizeof(windowTitle));
    std::string title = windowTitle;
    std::string targetWindowTitle = reinterpret_cast<const char*>(lParam);
    if (title.find(targetWindowTitle) != std::string::npos) {
        // Add the handle to the list of target window instances
        targetWindowInstances.push_back(hwnd);
    }
    return TRUE; // Continue enumeration
}

// Function to bring the specified window to the foreground by its handle
void bringWindowToForeground(HWND windowHandle) {
    // Bring the window to the foreground
    SetForegroundWindow(windowHandle);
}

// Function to bring the target window instance with the specified index to the foreground
void bringWindowToForegroundByInstance(const char* targetWindowTitle, int instanceNumber) {
    // Enumerate through windows to find all instances of the target window
    targetWindowInstances.clear(); // Clear previous instances
    EnumWindows(EnumWindowsProc, reinterpret_cast<LPARAM>(targetWindowTitle));

    if (instanceNumber >= 0 && instanceNumber < targetWindowInstances.size()) {
        HWND windowHandle = targetWindowInstances[instanceNumber];
        // Restore the window if it is minimized
        if (IsIconic(windowHandle)) {
            ShowWindow(windowHandle, SW_RESTORE);
        }
        // Bring the window to the foreground
        SetForegroundWindow(windowHandle);
    } else {
        std::cerr << "Invalid instance number." << std::endl;
    }
    Wait(200);
}
