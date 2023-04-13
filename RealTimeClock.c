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


void Set_Time(void);

void Set_Time(void){
    //Send I2C Message to the RTC to set the time
    //

    //Need to put I2C in transmit mode...
    //Need to set buffer length to 7
    //Should be able to use Send_I2C_Message
    Send_I2C_Message(RTC, Set_Time_ptr, 7);
}

#pragma vector = EUSCI_B1_VECTOR
__interrupt void EUSCI_B1_I2C_ISR(void){

    switch(UCB1IV){
     case 0x16:                 //ID 16: RXIFG0 -->Recieve, used for both temperature and RTC. 
                                //Expecting 7 bytes of data from the RTC
                                //Expecting 1 byte from the LM92 
         for(temp_pos = 0; temp_pos < sizeof(Data_In); temp_pos++){
         Data_In[temp_pos] = UCB1RXBUF;   // receive data
         int j;
         for (j = 0; j < 500; ++j) {
            //delay
        }
         }
         break;

     case 0x18:                 // ID 18: TXIFG0 --> Transmit
         if(first_Set_Time == 0 && Data_Cnt <= 8){
                 UCB1TBCNT = 8;  //# of bytes in Set_Time

                 UCB1TXBUF = Set_Time[Data_Cnt];

                 if(Data_Cnt == 7){
                     first_Set_Time = 1;
                 }
                 else{
                     Data_Cnt++;
                 }

         }
         else{
                UCB1TXBUF = 0x03;      //send register address to start
         }
         break;
     default:
         break;
    }
}