#ifndef botball_H__
#define BOTBALL_H__

#ifdef __cplusplus
extern "C"
{
#endif

    void InitBot();
    void SetArm(int);
    void MoveBot(int left_wheel_speed, int right_wheel_speed, int time_of_running);
    void StopBot();
    void FollowObject(int object_number);
    void SetHand(int);
    void CatchUpObject();
    void PutDownObject();

    void SetTwoPartsArmPosition(int percentage);
    void CatchObject(int object_number);
    void MoveForward(char speed, int time_of_running);
    void ChangeDirection(int degrees);
    int  MoveBotFromFile();

#ifdef __cplusplus
}
#endif
#endif