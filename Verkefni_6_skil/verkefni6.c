#pragma config(Sensor, in1,    gyro,           sensorGyro)
#pragma config(Sensor, in2,    lineFollowerLEFT, sensorLineFollower)
#pragma config(Sensor, in3,    lineFollowerCENTER, sensorLineFollower)
#pragma config(Sensor, in4,    lineFollowerRIGHT, sensorLineFollower)
#pragma config(Sensor, in5,    armSensor,      sensorPotentiometer)
#pragma config(Sensor, in6,    lightSensor,    sensorNone)
#pragma config(Sensor, dgtl1,  leftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  rightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  touchSensor,    sensorTouch)
#pragma config(Sensor, dgtl6,  sonarSensor,    sensorSONAR_cm)
#pragma config(Motor,  port2,           clawMotor,     tmotorVex269, openLoop)
#pragma config(Motor,  port3,           leftMotor,     tmotorVex269, openLoop, reversed, encoder, encoderPort, dgtl1, 1000)
#pragma config(Motor,  port4,           neckMotor,     tmotorVex269, openLoop)
#pragma config(Motor,  port5,           rightMotor,    tmotorVex269, openLoop, encoder, encoderPort, dgtl3, 1000)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task checkIfStopped()
{
	while(true){
		if(vexRT[Btn8U] == 1)
		{
			StopAllTasks();
		}
	}
}
void stopMotors(){
	motor[rightMotor] = 0; //Stop the right motor
  motor[leftMotor] = 0; //Stop the left motor
  wait1Msec(1500); //For 1 second
};

void claw(int value){
		if(value == 60){
			motor[clawMotor] = 60;
			wait1Msec(1000);
		}
		else{
			motor[clawMotor] = -60;
			wait1Msec(1000);
		}
		motor[clawMotor] = 0;
}
void followLine()
{
	int threshold = 2500;
	while(true)
	{
		while(SensorValue(sonarSensor) > 9 || SensorValue(sonarSensor) == -1)
		{
			// RIGHT sensor sees dark:
			if(SensorValue(lineFollowerRIGHT) > threshold)
			{
				// counter-steer right:
				motor[leftMotor]  = 50;
				motor[rightMotor] = 00;
			}

			// CENTER sensor sees dark:
			if(SensorValue(lineFollowerCENTER) > threshold)
			{
				// go straight
				motor[leftMotor]  = 50;
				motor[rightMotor] = 50;
			}

			// LEFT sensor sees dark:
			if(SensorValue(lineFollowerLEFT) > threshold)
			{
				// counter-steer left:
				motor[leftMotor]  = 00;
				motor[rightMotor] = 50;
			}
		}
		if(SensorValue(sonarSensor) < 12)
		{
			break;
		}
	}
}
void turnaround()
{
	motor[leftMotor] = 60;
	motor[rightMotor] = -60;
	wait1Msec(1000);
}


//+++++++++++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++++++++++++
task main()
{

	StartTask(checkIfStopped);
	claw(60);

	while(SensorValue(sonarSensor) > 9)
	{
		followLine();
	}

	stopMotors();
	claw(-60);
	while(SensorValue(armSensor) < 400)
  {
  	motor[neckMotor] = -30;
  }
  motor[neckMotor] = 0;

	turnaround();

	while(SensorValue(sonarSensor) > 9)
	{
		followLine();
	}

	stopMotors();
  while(SensorValue(armSensor) > 150)
  {
  	motor[neckMotor] = 30;
  }
  motor[neckMotor] = 0;

	claw(60);

	while(true){}
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
