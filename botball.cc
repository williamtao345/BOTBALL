//#include <kipr/botball.h>
#include "botball.h"
#include "base_functions.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <memory.h>

// Define numbers
#define LEFT_WHEEL_NUMBER 2
#define RIGHT_WHEEL_NUMBER 3
#define ARM_SERVO_NUMBER 3
#define ARM_SERVO_FIRST_PART_NUMBER 0
#define ARM_SERVO_SECOND_PART_NUMBER 0
#define CAMERA_SERVO_NUMBER 0
#define HAND_SERVO_NUMBER 2

// Define positions 
#define CAMERA_FORWARD_SERVO_POSITION 0
#define ARM_UP_SERVO_POSITION 700
#define ARM_UP_SERVO_FIRST_PART_POSITION 0
#define ARM_UP_SERVO_SECOND_PART_POSITION 0
#define ARM_DOWN_SERVO_FIRST_PART_POSITION 0
#define ARM_DOWN_SERVO_SECOND_PART_POSITION 0
#define ARM_DOWN_SERVO_POSITION 1265
#define HAND_OPEN_POSITION 1175
#define HAND_CLOSED_POSITION 470

// Define ratios 
#define ANGLE_RATIO 50

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Initialize for C Programing DataBase~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* typedef int DataType;
void SetArm(int);
void SetHand(int);
void CatchUpObject();
void PutDownObject();
void SetTwoPartsArmPosition(int percentage);
void InitBot();
void CatchObject(int object_number);
int Length_CharString(char *p);
void StopBot();
int Insert_to_end_of_LinkList_for_tracks_recording(int left_speed, int right_speed, int runningTime);
void Clean_up_track_recording();
void go_back_as_records();
void motor_record(int left_speed, int right_speed, int runningTime);
void MoveForward(char speed, int runningTime);
void MoveBot(int leftWheelSpeed, int rightWheelSpeed, int runningTime);
void ChangeDirection(int degrees);
int MoveBotFromFile();
void FollowObject(int object_number);
 */
/* ----------------------------------LinkList---------------------------------------- */

/* typedef struct node
{
    DataType data;
    struct node *link;
} LinkNode, *LinkList;

int Length_CharString(char *p);
LinkList Locate(LinkList(*first), int i);
int Insert_LinkNode(LinkList(*first), int i, DataType x);
int Insert_to_end_of_LinkList(LinkList(*first), DataType x);
int Remove_LinkNode(LinkList(*first), int i);
LinkList String_to_LinkList(int *p, int length);
void Printf_LinkList(LinkList x); */

/* ----------------------------------Stack---------------------------------------- */
/* #define initSize 20
typedef int SElemType;
typedef struct
{
    SElemType *elem;
    int maxSize, top;
} SeqStack;

void InitStack(SeqStack(*S));
int Push(SeqStack *S, DataType x);
int Pop(SeqStack(*S), SElemType *x);
int GetTop(SeqStack *S);
int StackEmpty(SeqStack(*S));
int StackFull(SeqStack(*S)); */

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~DataBase for botball~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* ----------------------------------Record tracks---------------------------------- */

/* int use_track_recording = 0;
typedef struct tracksRecording
{
    int speed_of_left, speed_of_right, runningTime;
    struct tracksRecording(*link_to_next), (*link_to_last);
} LinkNode_for_tracks_recording, *LinkList_for_tracks_recording;

LinkList_for_tracks_recording track_recording;
LinkNode_for_tracks_recording *pointer_of_the_last_record;
int the_max_number_of_times_of_recording = 200;
int the_number_of_times_of_recording = 0;

void initLinkList_for_tracks_recording()
{
    track_recording = (LinkList_for_tracks_recording)malloc(sizeof(LinkList_for_tracks_recording));
    track_recording->link_to_last = 0;
    pointer_of_the_last_record = track_recording;
}

int Insert_to_end_of_LinkList_for_tracks_recording(int left_speed, int right_speed, int runningTime)
{
    if (the_number_of_times_of_recording == the_max_number_of_times_of_recording) //Remove the first LinkNode.
    {
        LinkNode_for_tracks_recording *p;
        p = track_recording;
        track_recording = track_recording->link_to_next;
        //printf("----%d------\n", p->data);
        free(p);
        the_number_of_times_of_recording--;
    }

    LinkNode_for_tracks_recording *q, *p = track_recording;
    q = (LinkList_for_tracks_recording)malloc(sizeof(LinkList_for_tracks_recording));
    while (p->link_to_next != NULL)
    {
        p = p->link_to_next;
    }
    q->speed_of_left = left_speed;
    q->speed_of_right = right_speed;
    q->runningTime = runningTime;
    q->link_to_next = 0;
    q->link_to_last = p;
    p->link_to_next = q;
    the_number_of_times_of_recording++;
    pointer_of_the_last_record = q;

    return 1;
}

void Clean_up_track_recording()
{
    LinkList_for_tracks_recording p = track_recording->link_to_next;
    track_recording = 0;
    int i;
    for (i = 0; i < the_number_of_times_of_recording - 1; i++)
    {
        LinkList_for_tracks_recording q = p;
        p = p->link_to_next;
        free(q);
    }
}

void go_back_as_records()
{
    LinkNode_for_tracks_recording *p = pointer_of_the_last_record;
    int i;
    for (i = 0; i < the_number_of_times_of_recording; i++)
    {
        motor(LEFT_WHEEL_NUMBER, -(p->speed_of_left));
        motor(RIGHT_WHEEL_NUMBER, -(p->speed_of_right));
        msleep(p->runningTime);
        p = p->link_to_last;
    }
}

void motor_record(int left_speed, int right_speed, int runningTime)
{
    MoveBot(left_speed, right_speed, runningTime);
    Insert_to_end_of_LinkList_for_tracks_recording(left_speed, right_speed, runningTime);
} */

/* ----------------------------------Move forward---------------------------------- */
/*Speed is char from 1-100.                         */
/*If speed is greater than 0 is running forward.    */
/*If speed is less than 0 is running backward.      */
void MoveForward(char speed, int runningTime)
{
    motor(LEFT_WHEEL_NUMBER, speed);
    motor(RIGHT_WHEEL_NUMBER, speed);
    msleep(runningTime);
}

/* void MoveForward(char speed, int runningTime)
{
    if (use_track_recording)
    {
        motor_record(speed, speed, runningTime);
    }
    else
    {
        motor(LEFT_WHEEL_NUMBER, speed);
        motor(RIGHT_WHEEL_NUMBER, speed);
        msleep(runningTime);
    }
} */

/*Set two motors' each speed and running time.*/
/*If runningTime is 0, no running time.*/
void MoveBot(int leftWheelSpeed, int rightWheelSpeed, int runningTime)
{
    motor(LEFT_WHEEL_NUMBER, leftWheelSpeed);
    motor(RIGHT_WHEEL_NUMBER, rightWheelSpeed);
    msleep(runningTime);
}

/* ----------------------------------Stop the Wheels---------------------------------- */
void StopBot()
{
    MoveBot(0, 0, 0);
}
/* ----------------------------------Change direction---------------------------------- */
/*If degrees greater than 0 is turning left. */
/*If degrees less than 0 is turning right.   */
void ChangeDirection(int degrees)
{
    if (degrees >= 0)
    {
        MoveBot(-100, 100, degrees * ANGLE_RATIO);
    }
    else
    {
        MoveBot(100, -100, degrees * ANGLE_RATIO);
    }
}
/* void ChangeDirection(int degrees)
{
    if (use_track_recording)
    {
        if (degrees >= 0)
        {
            MoveBot(-100, 100, degrees * ANGLE_RATIO);
        }
        else
        {
            MoveBot(100, -100, degrees * ANGLE_RATIO);
        }
    }
    else
    {
        if (degrees >= 0)
        {
            motor_record(-100, 100, degrees * ANGLE_RATIO);
        }
        else
        {
            motor_record(100, -100, degrees * ANGLE_RATIO);
        }
    }
} */
/* ----------------------------------Move from informations from files---------------------------------- */
int IfFscanfNull(int degrees, char speed, int time) {
    if(degrees == 0)
        return 1;
    if(speed == 0)
        return 1;
    if(time == 0)
        return 1;
    else
        return 0;
}
/*Form of file per line: "number of direction(int degrees)" "running speed(char speed)" "time of running(int time)"\n. */
/*If degrees greater than 0 is turning left.        */
/*If degrees less than 0 is turning right.          */
/*Speed is char from 1-100.                         */
/*If speed is greater than 0 is running forward.    */
/*If speed is less than 0 is running backward.      */
int MoveBotFromFile()
{
    FILE *movementFile = fopen("movements.txt", "a+");
    if (!feof(movementFile))
    {
        return 0;
    }

    int degrees, time;
    char speed;
    do
    {
        fscanf(movementFile, "%d %c %d", &degrees, &speed, &time);
        if(!IfFscanfNull(degrees,speed,time))
            return 0;
        ChangeDirection(degrees);
        MoveForward(speed, time);
    } while (feof(movementFile));

    return 1;
}
/* ----------------------------------Follow the Object---------------------------------- */
/*If lose object, wait until find the object agian. */
void FollowObject(int object_number)
{
    camera_open_black();
    camera_update();
    printf("%d\n", get_object_center_y(0, object_number));
    while (get_object_center_y(0, object_number) < 110)
    {
        //printf("%d\n", get_object_center_y(0, object_number));
        camera_update();
        int object_center_x = get_object_center_x(0, object_number);
        if (get_object_center_y(0, object_number) < 60) {
            if (object_center_x > 80)
                MoveBot(100, 50, 0);
            else if (object_center_x < 80 && object_center_x > 0)
                MoveBot(50, 100, 0);
            else if (object_center_x == 80)
                MoveBot(100, 100, 0);
            else
                MoveBot(0, 0, 0);
        }
        else {
            if (object_center_x > 80)
                MoveBot(50, 10, 0);
            else if (object_center_x < 80 && object_center_x > 0)
                MoveBot(10, 50, 0);
            else
                MoveBot(30, 30, 0);
        };
    };

    camera_close();
}
/* void FollowObject(int object_number)
{
    camera_open_black();
    camera_update();
    printf("%d\n", get_object_center_y(0, object_number));
    if (use_track_recording)
    {
        while (get_object_center_y(0, object_number) < 110)
        {
            //printf("%d\n", get_object_center_y(0, object_number));
            camera_update();
            int object_center_x = get_object_center_x(0, object_number);
            if (get_object_center_y(0, object_number) < 60)
            {
                if (object_center_x > 80)
                {
                    motor_record(100, 50, 50);
                }
                else if (object_center_x < 80 && object_center_x > 0)
                {
                    motor_record(50, 100, 50);
                }
                else if (object_center_x == 80)
                {
                    motor_record(100, 100, 50);
                }
                else
                {
                    MoveBot(0, 0, 0);
                }
            }
            else
            {
                if (object_center_x > 80)
                {
                    motor_record(50, 10, 50);
                }
                else if (object_center_x < 80 && object_center_x > 0)
                {
                    motor_record(10, 50, 50);
                }
                else
                {
                    motor_record(30, 30, 50);
                }
            }
        }
    }
    else
    {
        while (get_object_center_y(0, object_number) < 110)
        {
            //printf("%d\n", get_object_center_y(0, object_number));
            camera_update();
            int object_center_x = get_object_center_x(0, object_number);
            if (get_object_center_y(0, object_number) < 60)
            {
                if (object_center_x > 80)
                {
                    MoveBot(100, 50, 0);
                }
                else if (object_center_x < 80 && object_center_x > 0)
                {
                    MoveBot(50, 100, 0);
                }
                else if (object_center_x == 80)
                {
                    MoveBot(100, 100, 0);
                }
                else
                {
                    MoveBot(0, 0, 0);
                }
            }
            else
            {
                if (object_center_x > 80)
                {
                    MoveBot(50, 10, 0);
                }
                else if (object_center_x < 80 && object_center_x > 0)
                {
                    MoveBot(10, 50, 0);
                }
                else
                {
                    MoveBot(30, 30, 0);
                }
            }
        }
    }
    camera_close();
} */

/* -----------------------------------Movement of servo----------------------------------- */
void SetArm(int degree)
{
    set_servo_position(ARM_SERVO_NUMBER, degree);
}

void SetHand(int degree)
{
    set_servo_position(HAND_SERVO_NUMBER, degree);
}

void CatchUpObject()
{
    SetArm(ARM_DOWN_SERVO_POSITION);
    msleep(300);
    SetHand(HAND_CLOSED_POSITION);
    msleep(300);
    SetArm(ARM_UP_SERVO_POSITION);
}

void PutDownObject()
{
    SetArm(ARM_DOWN_SERVO_POSITION);
    msleep(300);
    SetHand(HAND_OPEN_POSITION);
    SetArm(ARM_UP_SERVO_POSITION);
}

/*Percentage is from 0 to 100;  */
/*0 is lowest, 100 is highest;  */
void SetTwoPartsArmPosition(int percentage)
{
    int first_part_range = ARM_UP_SERVO_FIRST_PART_POSITION - ARM_DOWN_SERVO_FIRST_PART_POSITION;
    int second_part_range = ARM_UP_SERVO_SECOND_PART_POSITION - ARM_DOWN_SERVO_SECOND_PART_POSITION;
    set_servo_position(ARM_SERVO_FIRST_PART_NUMBER, first_part_range * percentage / 100);
    set_servo_position(ARM_SERVO_SECOND_PART_NUMBER, second_part_range * percentage / 100);
};
/* -----------------------------------Reset every part---------------------------------- */
/*Wheels stop.               */
/*Camera face forward.      */
/*Arm up.                   */
/*Hnad close.               */
void InitBot()
{
    MoveBot(0, 0, 0);
    //set_servo_position(CAMERA_SERVO_NUMBER, CAMERA_FORWARD_SERVO_POSITION);
    set_servo_position(ARM_SERVO_NUMBER, ARM_DOWN_SERVO_POSITION);
    set_servo_position(HAND_SERVO_NUMBER, HAND_OPEN_POSITION);
}
/* -----------------------------------Inset Programs----------------------------------- */
void CatchObject(int object_number)
{
    InitBot();
    FollowObject(object_number);
    CatchUpObject();
}