#pragma config(Sensor, dgtl1,  leftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  rightEncoder,   sensorQuadEncoder)
#pragma config(Motor,  port2,           clawMotor,     tmotorVex269, openLoop)
#pragma config(Motor,  port3,           leftMotor,     tmotorVex269, openLoop, reversed, encoder, encoderPort, dgtl1, 1000)
#pragma config(Motor,  port4,           neckMotor,     tmotorVex269, openLoop)
#pragma config(Motor,  port5,           rightMotor,    tmotorVex269, openLoop, encoder, encoderPort, dgtl3, 1000)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*----------------------------------------------------------------------------------------------------*\
|*                              - Forward for Distance with Encoders -                                *|
|*                                      ROBOTC on VEX 2.0 CORTEX                                      *|
|*                                                                                                    *|
|*  This program instructs the robot to move forward for 5 rotations of the left shaft encoder.       *|
|*                                                                                                    *|
|*                                        ROBOT CONFIGURATION                                         *|
|*    NOTES:                                                                                          *|
|*    1)  																																										        *|
|*        "Squarebot" model, but may not be needed for all robot configurations.                      *|
|*    2)  Whichever encoder is being used for feedback should be cleared just before it starts        *|
|*        counting by using the "SensorValue(encoder) = 0;".  This helps ensure consistancy.          *|
|*                                                                                                    *|
|*    MOTORS & SENSORS:                                                                               *|
|*    [I/O Port]          [Name]              [Type]                [Description]                     *|
|*    Motor   - Port 2    rightMotor          VEX 3-wire module     Right side motor                  *|
|*    Motor   - Port 3    leftMotor           VEX 3-wire module     Left side motor                   *|
|*    Digital - Port 1,2  rightEncoder        VEX Shaft Encoder     Right side                        *|
|*    Digital - Port 3,4  leftEncoder         VEX Shaft Encoder     Left side                         *|
\*----------------------------------------------------------------------------------------------------*/


void driveForward(int dist)
{
	SensorValue[rightEncoder] = 0;//clear the encoders
	SensorValue[leftEncoder] = 0;//clear the encoders

	while(SensorValue[leftEncoder] < dist){

		if(SensorValue[rightEncoder] == SensorValue[leftEncoder]){ // If rightEncoder has counted the same amount as leftEncoder:
			// Move Forward
			motor[rightMotor] = 80;	   // Right Motor is run at power level 80
			motor[leftMotor]  = 80;	   // Left Motor is run at power level 80
		}
		else if(SensorValue[rightEncoder] > SensorValue[leftEncoder]){	// If rightEncoder has counted more encoder counts
			// Turn slightly right
			motor[rightMotor] = 60;	   // Right Motor is run at power level 60
			motor[leftMotor]  = 80;	   // Left Motor is run at power level 80
		}
		else{	// Only runs if leftEncoder has counted more encoder counts
			// Turn slightly left
			motor[rightMotor] = 80;	   // Right Motor is run at power level 80
			motor[leftMotor]  = 60;	   // Left Motor is run at power level 60
		}
	}
}

void stopMotors(){
	motor[rightMotor] = 0; //Stop the right motor
  motor[leftMotor] = 0; //Stop the left motor
  wait1Msec(800); //For 1 second
};

void turn90Degrees(int left,int right){
	motor[leftMotor] = left;
  motor[rightMotor] = right;
  wait1Msec(880);
}
//+++++++++++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++++++++++++

task main()
{
	const int dist = 580;
	driveForward(dist); // drives 500m forward
	stopMotors(); //Stops all motors
	turn90Degrees(-60,60); //90deg turn to the right
	stopMotors(); //stops all motors

	driveForward(dist); // drives 500m forward
	stopMotors(); //stops all motors
	turn90Degrees(60,-80);//90deg turn to the left, our right motor was not as good as the left one so it needed a little boost
	stopMotors(); //stops all motors

	driveForward(dist); // drives 500m forward
	stopMotors(); //stops all motors
	turn90Degrees(60,-80);//90deg turn to the left, our right motor was not as good as the left one so it needed a little boost
	stopMotors(); //stops all motors

	driveForward(dist);// drives 500m forward
	stopMotors(); //stops all motors
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
