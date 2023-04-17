#include<msp430.h>
/*
 *   Control the temperature of a "plant" consisting of a Peltier device and a temperature sensor
 *
 */

#define KP 2.0 // Proportional gain
#define KI 0.1 // Integral gain
#define KD 0.5 // Derivative gain
#define DT 0.1 // Sampling time interval in seconds


// Need some global variables
extern int I2C_Message_Counter;
extern char I2C_Message_Global[32];
extern int Data_Valid;
extern float Derivative;
extern float Integral;
extern float Previous_Error;
extern float Previous_Temperature;
extern float MIN_OUTPUT;

void Peltier_PID(float Current_Temperature, float Target_Temperature)
{

                 int i;
                 // Calculate Error
                 float Error = Target_Temperature - Current_Temperature;
                 // Calculate Integral
                 Integral = Integral + Error * DT;

                 // Calculate Derivative
                 Derivative = (Error - Previous_Error) / DT;

                 // Calculate Output using PID formula
                 float Output = KP * Error + KI * Integral + KD * Derivative;

                 // We are lower than the target
                 if (Output > MIN_OUTPUT && Data_Valid >0) {
                     P5OUT &= ~BIT2;             // Clear Output
                     for(i = 0; i<100; i++){}
                     P5OUT |= BIT3;
                 }

                 // We are higher than the target
                 else if (Output < ( 0 - MIN_OUTPUT) && Data_Valid >0) {
                     P5OUT &= ~BIT3;             // Clear Output
                     for(i = 0; i<100; i++){}
                     P5OUT |= BIT2;
                 }
                 else{
                     P5OUT &= ~BIT2;
                     P5OUT &= ~BIT3;             // Clear Output
                 }

                 // Update previous values
                 Previous_Temperature = Current_Temperature;
                 Previous_Error = Error;

}



