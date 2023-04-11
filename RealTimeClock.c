#include<msp430.h>
/*
TODO:
    1. Create a "Set_Time" function. This will allow the current time to be set, this is used to initalize the RTC
    2. Create a "Set_Timer" function. This will allow the RTC to keep track of the 5 minute interval of which the process runs
    3. Createa a "Read_Timer" function, this will allow the master to see the timer go off and then take appropriate actions

Setup: (Using the DS3231 RTC from Analog Devices)
    1. RTC is running on I2C bus, with address 0x068 this is hard coded to the RTC
    2. RTC requires setup of the timer which is register 08h
*/

