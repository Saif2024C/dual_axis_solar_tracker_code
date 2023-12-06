/*
Code : Mohammad Saifullah 
Title : Dual Axis Solar Tracking
V0 = 6/12/23
*/

#include <Servo.h>
Servo horizontal; // horizontal servo
Servo vertical; // vertical servo 

int VerticalPos=90;
int HorizontalPos=90;
int servoDefault = 90 ;  // default angle for both the servo motors 
int tol = 60; // tol=tolerance 


int TL = A0; //LDR TOP LEFT 
int TR = A1; //LDR TOP RIGHT
int BL = A2; //LDR BOTTOM LEFT
int BR = A3; //LDR BOTTOM RIGHT

void setup()
{
Serial.begin(9600);
horizontal.attach(9);
vertical.attach(8);
horizontal.write(servoDefault);
vertical.write(servoDefault);
}

void loop() {

int TopLeft = analogRead(TL); // top left
int TopRight = analogRead(TR); // top right
int BottomLeft = analogRead(BL); // down left
int BottomRight = analogRead(BR); // down right

int avtop = (TopLeft+TopRight)*0.5; // average value top
int avddown = (BottomLeft + BottomRight)*0.5; // average value down
int avgleft = (TopLeft + BottomRight)*0.5; // average value left
int avgright = (TopRight + BottomRight)*0.5; // average value right

int VDiff = avtop - avddown; // check the diffirence of up and down
int HDiff = avgleft - avgright;// check the diffirence of left and right


if (abs(VDiff)>tol) // check if the Vertical diffirence is in the tolerance else change Vertical angle
{
  
  VerticalPos = VerticalPos - round(VDiff/abs(VDiff))  ;
  if(0 < VerticalPos && VerticalPos < 180)
  {
    vertical.write(VerticalPos);
  }

  else if( VerticalPos > 180)
  {
    VerticalPos = 180;
    vertical.write(VerticalPos);
  }

  else
  {
    VerticalPos = 0;
    vertical.write(VerticalPos);
  }
delay(50);
}


if (abs(HDiff)>tol) // check if the Horizontal diffirence is in the tolerance else change horizontal angle
{
  HorizontalPos = HorizontalPos - round(HDiff/abs(HDiff)) ;

  if( 0 < HorizontalPos && HorizontalPos < 180 )
  {
    horizontal.write(HorizontalPos);
  }

 else if( VerticalPos > 180)
  {
    VerticalPos = 180;
    vertical.write(VerticalPos);
  }

  else
  {
    VerticalPos = 0;
    vertical.write(VerticalPos);
  }
  delay(50);

}

delay(20);

}