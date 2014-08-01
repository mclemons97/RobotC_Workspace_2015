#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  HTMotor)
#pragma config(Sensor, S1,     MotorMotorServo, sensorNone)
#pragma config(Sensor, S2,     PSPNX,          sensorI2CCustomFastSkipStates)
#pragma config(Motor,  motorA,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     LeftMotor,     tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     RightMotor,    tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     TowerLift,     tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     FlagRaiser,    tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C4_1,     Lift,          tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C4_2,     potentiometer, tmotorTetrix, openLoop, encoder)
#pragma config(Servo,  srvo_S1_C3_1,    BlockGate,            tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    Ejector,              tServoStandard)
#pragma config(Servo,  srvo_S1_C3_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.
#include "PS2/includes/PSP-Nx-lib.h"
const ubyte Addr = 0x02;
5
task main()
{
psp currState;
nI2CBytesReady[PSPNX] = 0;
PlaySound(soundUpwardTones);

	while(true)
	{
/*user code below*/
PSP_ReadButtonState(PSPNX, Addr, currState);
bool joystick_joy1_btn_1			= !(char)currState.square;	//
bool joystick_joy1_btn_2 			= !(char)currState.cross;	//
bool joystick_joy1_btn_3 			= !(char)currState.circle;	//
bool joystick_joy1_btn_4 			= !(char)currState.triang;	//
bool joystick_joy1_Dpad_Up 		= !(char)currState.d;			//unused
bool joystick_joy1_Dpad_Right = !(char)currState.c;			//unused
bool joystick_joy1_Dpad_Down 	= !(char)currState.b;			//unused
bool joystick_joy1_Dpad_Left 	= !(char)currState.a;			//unused
bool joystick_joy1_L_Bumper		= !(char)currState.l1;			//
bool joystick_joy1_R_Bumper		= !(char)currState.r1;			//
bool joystick_joy1_L_Trigger	= !(char)currState.l2;			//
bool joystick_joy1_R_Trigger	= !(char)currState.r2;			//
bool joystick_joy1_btn_13			=	!(char)currState.l_j_b;	//unused
bool joystick_joy1_btn_14			= !(char)currState.r_j_b;	//unused`
int joystick_joy1_x1 					= (int)currState.l_j_x;		//unused
int joystick_joy1_y1 					= (int)currState.l_j_y;		//
int joystick_joy1_x2					= (int)currState.r_j_x;		//unused
int joystick_joy1_y2					= (int)currState.r_j_y;		//


		//clearDebugStream();

	//first joypad
	//right drive

	 const static int threshold =12; // Int 'threshold' will allow us to ignore low  readings that keep our robot in perpetual motion.

	 if(abs(joystick_joy1_y1) > threshold)   // If the right analog stick's Y-axis readings are either above or below the threshold:
		{
		motor[RightMotor] = joystick_joy1_y1;         // Motor D is assigned a power level equal to the right analog stick's Y-axis reading.
 		writeDebugStreamLine("joystick_joy1_y1: %i",joystick_joy1_y1);
		}else                                    // Else if the readings are within the threshold:
			{
				motor[RightMotor] = 0;                        // Motor D is stopped with a power level of 0.
			}
 //left drive
		if(abs(joystick_joy1_y2) > threshold)   // If the left analog stick's Y-axis readings are either above or below the threshold:
		{
		motor[LeftMotor] = joystick_joy1_y2;         // Motor E is assigned a power level equal to the left analog stick's Y-axis reading.
		writeDebugStreamLine("joystick_joy1_y2: %i",joystick_joy1_y2);
		}
			else                                    // Else if the readings are within the threshold:
			{
				motor[LeftMotor] = 0;                        // Motor E is stopped with a power level of 0.
			}
//Flag Raiser


			if(joystick_joy1_L_Bumper)
			{
				motor[FlagRaiser] = 80;
				writeDebugStreamLine("joystick_joy1_L_Bumper: %i",joystick_joy1_L_Bumper);
		  }
		  else if(joystick_joy1_L_Trigger)
		  {
		  	motor[FlagRaiser] = -80;
		  	writeDebugStreamLine("joystick_joy1_L_Trigger: %i",joystick_joy1_L_Trigger);
		  }
		  else
		  {
		 		motor[FlagRaiser] = 0;
		  }
		  	//lift--has one motor mounted at the tower cross-section
		  if(joystick_joy1_btn_4)//X
			{
				motor[Lift]=80;//up
				writeDebugStreamLine("joystick_joy1_btn_4: %i",joystick_joy1_btn_4);
			}else if(joystick_joy1_btn_1)//Y
				{
					motor[Lift]=-80;//down
					writeDebugStreamLine("joystick_joy1_btn_1: %i",joystick_joy1_btn_1);
				}else//not X, or Y...
					{
						motor[Lift]=0;//stop
					}
		//Tower Lift--has two paralell motors mounted on the uprights
		if(joystick_joy1_btn_3)//A
			{
				motor[TowerLift]=-80;//down
				writeDebugStreamLine("joystick_joy1_btn_3: %i",joystick_joy1_btn_3);
			}else if(joystick_joy1_btn_2)//B
				{
					motor[TowerLift]=80;//up
					writeDebugStreamLine("joystick_joy1_btn_2: %i",joystick_joy1_btn_2);
				}else//not A, or B...
					{
						motor[TowerLift]=0;//stop
					}
	//Block Gate
			if(joystick_joy1_R_Bumper )//LB
			{
			servo[BlockGate]=254;// opens the block gate
			writeDebugStreamLine("joystick_joy1_R_Bumper: %i",joystick_joy1_R_Bumper);
			}else//not LB...
				{
					servo[BlockGate]=5;//close block gate
				}
	//ejector
			if(joystick_joy1_R_Trigger &&servo[BlockGate] !=5)
			{
				servo[Ejector]=100;//opens the ejector servo
				writeDebugStreamLine("joystick_joy1_R_Trigger: %i",joystick_joy1_R_Trigger);
			}else
				{
					servo[Ejector]=5;//closes the ejector servo
				}
	}//end of while(true)
}//main end block
