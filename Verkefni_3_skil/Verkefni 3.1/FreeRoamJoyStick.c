#pragma config(Sensor, dgtl1,  leftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  rightEncoder,   sensorQuadEncoder)
#pragma config(Motor,  port2,           clawMotor,     tmotorVex269, openLoop)
#pragma config(Motor,  port3,           leftMotor,     tmotorVex269, openLoop, reversed)
#pragma config(Motor,  port4,           armMotor,      tmotorVex269, openLoop)
#pragma config(Motor,  port5,           rightMotor,    tmotorVex269, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*----------------------------------------------------------------------------------------------------*\
|*                                - Clawbot Single Joystick Control -                                 *|
|*                                      ROBOTC on VEX 2.0 Cortex                                      *|
|*                                                                                                    *|
|*  This program uses a single joystick, either right or left to drive the robot. Use notes below     *|
|*  to reconfigure which joystick is used. The joystick buttons are used to raise and lower the arm.	*|
|*  The joystick buttons are used to open and close the claw.																					*|
|*																																																		*|
|*                                        ROBOT CONFIGURATION                                         *|
|*    NOTES:                                                                                          *|
|*    1)	Ch1 is the X axis and Ch2 is the Y axis for the RIGHT joystick.                             *|
|*    2)	Ch3 is the Y axis and Ch4 is the X axis for the LEFT joystick.                              *|
|*		3)	Button 5U and 5L are on the front left side of the joystick.																*|
|*		3)	Button 6U and 6L are on the front right side of the joystick.																*|
|*                                                                                                    *|
|*    MOTORS & SENSORS:                                                                               *|
|*    [I/O Port]        [Name]          [Type]                               [Description]            *|
|*    Motor - Port 2   rightMotor    VEX 393 Motor                         Right drive motor          *|
|*    Motor - Port 6   clawMotor     VEX 393 Motor w/ Motor Controler 29   Claw motor                 *|
|*    Motor - Port 7   armMotor      VEX 393 Motor w/ Motor Controler 29   Arm motor                  *|
|*    Motor - Port 10  leftMotor     VEX 393 Motor                         Left drive motor           *|
\*----------------------------------------------------------------------------------------------------*/


/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!| ToDo |!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	1. While accelerating right side spins right away while left side starts a millisecond later
		-Possibly a mechanical problem
	2. Make the code our's
		-
	3. There's friction at the QuadEncoders with the bearing and is eating at the plastic casing
		-
	4. Switch the neck from a straight one to one with a 45? angle
		-
	5. Connect the Display?
		-
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

task checkIfStopped()
{
	while(true){
		if(vexRT[Btn8U] == 1)
		{
			StopAllTasks();
		}
	}
}

//+++++++++++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++++++++++++
task main ()
{
	startTask(checkIfStopped);

	while(true)
	{
		motor[leftMotor]  = (vexRT[Ch3] + vexRT[Ch4])/2;  // (y + x)/2
		motor[rightMotor] = (vexRT[Ch3] - vexRT[Ch4])/2;  // (y - x)/2


// Raise, lower or do not move arm
		if(vexRT[Btn5U] == 1)       	//If button 5U is pressed...
		{
			motor[armMotor] = 127;    	//...raise the arm.
		}
		else if(vexRT[Btn5D] == 1)  	//Else, if button 5D is pressed...
		{
			motor[armMotor] = -127;   	//...lower the arm.
		}
		else                      		//Else (neither button is pressed)...
		{
			motor[armMotor] = 0;      	//...stop the arm.
		}

// Open, close or do not more claw
		if(vexRT[Btn6U] == 1)       	//If Button 6U is pressed...
		{
			motor[clawMotor] = 127;  		//...close the gripper.
		}
		else if(vexRT[Btn6D] == 1)  	//Else, if button 6D is pressed...
		{
			motor[clawMotor] = -127; 		//...open the gripper.
		}
		else                      		//Else (neither button is pressed)...
		{
			motor[clawMotor] = 0;    		//...stop the gripper.
		}
	}
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
