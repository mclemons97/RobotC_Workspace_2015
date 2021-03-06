#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Sensor, S2,     PSPNX,          sensorI2CCustomFastSkipStates)
#pragma config(Motor,  motorA,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     RightMotor,    tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     LeftMotor,     tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "PS2/includes/PSP-Nx-lib.h"
const ubyte Addr = 0x02;


task main()
{
psp currState;
nI2CBytesReady[PSPNX] = 0;
PlaySound(soundUpwardTones);

	while(true)
	{
		/*user code below*/
		PSP_ReadButtonState(PSPNX, Addr, currState);
		bool joystick_joy1_btn_1			= !(char)currState.square;//
		bool joystick_joy1_btn_2 			= !(char)currState.cross;	//
		bool joystick_joy1_btn_3 			= !(char)currState.circle;//
		bool joystick_joy1_btn_4 			= !(char)currState.triang;//
		bool joystick_joy1_Dpad_Up 		= !(char)currState.d;			//unused
		bool joystick_joy1_Dpad_Right = !(char)currState.c;			//unused
		bool joystick_joy1_Dpad_Down 	= !(char)currState.b;			//unused
		bool joystick_joy1_Dpad_Left 	= !(char)currState.a;			//unused
		bool joystick_joy1_L_Bumper		= !(char)currState.l1;		//
		bool joystick_joy1_R_Bumper		= !(char)currState.r1;		//
		bool joystick_joy1_L_Trigger	= !(char)currState.l2;		//
		bool joystick_joy1_R_Trigger	= !(char)currState.r2;		//
		bool joystick_joy1_btn_13			=	!(char)currState.l_j_b;	//unused
		bool joystick_joy1_btn_14			= !(char)currState.r_j_b;	//unused`
		int joystick_joy1_x1 					= (int)currState.l_j_x;		//unused
		int joystick_joy1_y1 					= (int)currState.l_j_y;		//
		int joystick_joy1_x2					= (int)currState.r_j_x;		//unused
		int joystick_joy1_y2					= (int)currState.r_j_y;		//

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
	}
}
