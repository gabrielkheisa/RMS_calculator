#include <iostream>
#include <math.h>
#define pi 3.141
using namespace std;

/*
source of RMS formula : 

http://tiij.org/issues/issues/fall2007/30_Cartwright/Cartwright-Waveforms.pdf
https://en.wikipedia.org/wiki/Root_mean_square

waveforms including AC(sinusoidal), sawtooth, and adjustable duty cycle PWM.
*/
float sgn(float x) {
    if (x > 0) return 1;
    if (x < 0) return -1;
}

float f_sin(float amplitude, float i) {
    return amplitude*sin(i);
}

float f_sawtooth(float amplitude, float i) {
    return (fmod(i,pi)/pi)*amplitude;
}

float f_PWM(float amplitude, float duty, float i){
    return (( sgn(sin(i)+(2*duty)-1)+1 )/2)*amplitude;
}


float RMS_sin(float amplitude) {
    float x = 0;
    float n = 0;
    float a = 0;
    for(float i=0; i<2*pi;) {
        n++;
       
        a = a + pow(f_sin(amplitude,i),2);
        i=i+0.1;
    }
    x = sqrt(a/n);
    return x;
}

float RMS_sawtooth(float amplitude){
    float x = 0;
    float n = 0;
    float a = 0;
    for(float i=0; i<2*pi;) {
        n++;
      
        a = a + pow(f_sawtooth(amplitude,i),2);
        i=i+0.1;
    }
    x = sqrt(a/n);
    return x;    
}

float RMS_PWM(float amplitude, float duty) {
    float x = 0;
    float n = 0;
    float a = 0;
    for(float i=0; i<10*pi;) {
        n++;
      
        a = a + pow(f_PWM(amplitude,duty,i),2);
        i=i+0.1;
    }
    x = sqrt(a/n);
    return x;    
}

int main()
{
    float amplitude = 311;
	float PWM_duty = 0.3; //PWM duty cycle 0 - 1 (0 - 100%)
    cout << RMS_sin(amplitude) << "\n";
    cout << RMS_sawtooth(amplitude) << "\n";
	cout << RMS_PWM(amplitude, PWM_duty);
}
