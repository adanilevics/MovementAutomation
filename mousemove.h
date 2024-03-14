#ifndef MOUSEMOVE_H
#define MOUSEMOVE_H

#include <Windows.h>

void moveMouseRandomCurved(int startX, int startY, int endX, int endY, int durationMs);
void Wait(int milliseconds);
void Click(int delayBetweenClicksMs = 0);

#endif // MOUSEMOVE_H