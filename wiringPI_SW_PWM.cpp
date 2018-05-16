/*
Raspberry Pi wiringPi SW serial for motor control
*/
// gcc -o sw_pwm sw_pwm_test.cpp -lwiringPi

#include <wiringPi.h>
#include <softPwm.h>
#include <iostream>
#include <unistd.h>

int pwm_pin1 = 17;
int pwm_pin2 = 27;

using namespace std;

int main(void){
	if (wiringPiSetupGpio() <0 ) return 1;
	pinMode(pwm_pin1, OUTPUT);
	pinMode(pwm_pin2, OUTPUT);
	if (softPwmCreate (pwm_pin1, 0,  100) == 0){
		cout << "PWM Pin1 initialisation successful!" << endl;
	}else{
		cout << "PWM Pin1 initialisation Failed!" << endl;
		}
    if (softPwmCreate (pwm_pin2, 0,  100) == 0){
		cout << "PWM Pin2 initialisation successful!" << endl;
	}else{
		cout << "PWM Pin2 initialisation Failed!" << endl;
		}
		
	softPwmWrite(pwm_pin1, 0);
	softPwmWrite(pwm_pin2, 0);
	for(int pwm=0;pwm<50;pwm+=5){
		softPwmWrite(pwm_pin2, pwm);
		cout << "PWM: " << pwm << endl;
		sleep(2);
		}
	softPwmWrite(pwm_pin1, 0);
	softPwmWrite(pwm_pin2, 0);
	sleep(2);
	cout << "Exit" << endl;
	return 0;
}
