#ifndef _ANGLER_HPP_
#define _ANGLER_HPP_

bool isTrayGoingOut();
void trayOpControlInit();
void trayOutSlow();
void trayIn();
void lowerCubesInTray();
void trayOutFast();
void trayOutMediumSpeed();
void trayPIDInit();
void trayWaitUntilSettled();
bool isIntakeBusy();

#endif