#ifndef _DRIVE_HPP_
#define _DRIVE_HPP_

void chassisInit();
void chassisForward(okapi::QLength inches, bool async);
void chassisBackward(okapi::QLength inches, bool async);

#endif