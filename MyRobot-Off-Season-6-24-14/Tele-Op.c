#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  HTMotor)
#pragma config(Sensor, S1,     MotorMotorServo, sensorI2CMuxController)
#pragma config(Sensor, S2,     Left_IR,        sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S3,     Right_IR,       sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  motorA,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     LeftMotor,     tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     RightMotor,    tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     TowerLift,     tmotorTetrix, openLoop)
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

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.
task main()
{
	waitForStart();
	while(true)
	{

		getJoystickSettings(joystick);
//first joypad
	//right drive
	 const int threshold =8; // Int 'threshold' will allow us to ignore low  readings that keep our robot in perpetual motion.
		if(abs(joystick.joy1_y1) > threshold)   // If the right analog stick's Y-axis readings are either above or below the threshold:
		{
		motor[RightMotor] = joystick.joy1_y1;         // Motor D is assigned a power level equal to the right analog stick's Y-axis reading.
		}else                                    // Else if the readings are within the threshold:
			{
				motor[RightMotor] = 0;                        // Motor D is stopped with a power level of 0.
			}
 //left drive
		if(abs(joystick.joy1_y2) > threshold)   // If the left analog stick's Y-axis readings are either above or below the threshold:
		{
		motor[LeftMotor] = joystick.joy1_y2;         // Motor E is assigned a power level equal to the left analog stick's Y-axis reading.
		}
			else                                    // Else if the readings are within the threshold:
			{
				motor[LeftMotor] = 0;                        // Motor E is stopped with a power level of 0.
			}
//Flag Raiser
			if(joy1Btn(5))
			{
				motor[FlagRaiser] = 80;
		  }
		  else if(joy1Btn(7))
		  {
		  	motor[FlagRaiser] = -80;
		  }
		  else
		  {
		 		motor[FlagRaiser] = 0;
		  }
//Second Joypad
		//Tower Lift--has two paralell motors mounted on the uprights
		if(joy2Btn(2))//A
			{
				motor[TowerLift]=-80;//down
			}else if(joy2Btn(3))//B
				{
					motor[TowerLift]=80;//up
				}else//not A, or B...
					{
						motor[TowerLift]=0;//stop
					}
	//lift--has one motor mounted at the tower cross-section
		if(joy2Btn(4))//X
			{
				writeDebugStreamLine("arm: %i", nMotorEncoder[potentiometer]);
				motor[Lift]=80;//down
			}else if(joy2Btn(1))//Y
				{
					writeDebugStreamLine("arm: %i", nMotorEncoder[potentiometer]);
					motor[Lift]=-80;//up
				}else//not X, or Y...
					{
						motor[Lift]=0;//stop
					}
	//Block Gate
			if(joy2Btn(6))//LB
			{
			servo[BlockGate]=254;// opens the block gate
			}else//not LB...
				{
					servo[BlockGate]=5;//close block gate
				}
	//ejector
			if(joy2Btn(8)&&servo[BlockGate] !=5)
			{
				servo[Ejector]=100;//opens the ejector servo
			}else
				{
					servo[Ejector]=5;//closes the ejector servo
				}
	}//end of while(true)
}//main end block
