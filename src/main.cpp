/*
 * AS5050A Encoder library
 * CONNECTIONS:
 * ---
 * POWER:
 * Orange:  VDD
 * Yellow:  GND
 * ---
 * SPI:
 * Green:   MOSI (SPI bus data input)
 * Blue:    MISO (SPI bus data output)
 * Purple:  SCK  (SPI clock)
 */

#include "AS5050.h"
#include "Servo.h"
#include "mbed.h"
#include "MyPid.h"
#define  numberOfPid  3

static PIDimp*  pid[numberOfPid];
double kp=1;
double ki=0;
double kd=0;

 int main() {
   pid[0] = new PIDimp( new Servo(PC_9, 5),
                         new AS5050(PB_5, PB_4, PB_3, PA_4));
   pid[1] = new PIDimp( new Servo(PC_10, 5),
                         new AS5050(PB_5, PB_4, PB_3, PA_3));
   pid[2] = new PIDimp( new Servo(PC_11, 5),
                         new AS5050(PB_5, PB_4, PB_3, PA_2));
   for (int i=0;i<numberOfPid;i++){
     pid[i]->setPIDConstants(kp,ki,kd);
     pid[i]->InitilizePidController();
   }

    while(1) {
      // update all positions fast and together
      for (int i=0;i<numberOfPid;i++)
        pid[i]->updatePosition();
      // next update all control outputs
      for (int i=0;i<numberOfPid;i++)
        pid[i]->updateControl();
      wait_ms(1);
    }
 }
