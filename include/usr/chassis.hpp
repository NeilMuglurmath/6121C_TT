#ifndef _DRIVE_HPP_
#define _DRIVE_HPP_

void chassisInit();

void chassisGenerateStraightPath(okapi::QLength inches, std::string pathName);
void chassisGeneratePath(okapi::QLength x, okapi::QLength y, okapi::QAngle degrees, std::string pathName);
void chassisGenerateSlowStraightPath(okapi::QLength inches, std::string pathName, double maxVel);
void chassisGenerateSlowPath(okapi::QLength x, okapi::QLength y, okapi::QAngle degrees, std::string pathName, double maxVel);
void chassisExecutePath(std::string pathName, bool async, bool backwards, bool mirrored);
void chassisForward(okapi::QLength inches, std::string pathName, bool async);
void chassisForwardSlow(okapi::QLength inches, std::string pathName, bool async, double maxVel);
void chassisBackward(okapi::QLength inches, std::string pathName, bool async);
void chassisBackwardSlow(okapi::QLength inches, std::string pathName, bool async, double maxVel);
void chassisMove(okapi::QLength x, okapi::QLength y, okapi::QAngle degrees, std::string pathName, bool async, bool mirrored);
void chassisGenerateTurnPath(okapi::QLength inches, std::string pathName);
void chassisExecuteTurnPath(std::string pathName, bool async, bool backwards, bool mirrored);
void chassisTurn(okapi::QLength inches, std::string pathName, bool async, bool right);
void chassisWaitUntilSettled();
void chassisMoveVoltage(int voltage);
void chassisTurnWaitUntilSettled();

#endif