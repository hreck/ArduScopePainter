/*
 * 	Arduinio Scope Painter
 *
 *  	Created: Feb 15, 2013
 *  
 *	Author: Harm Reck
 *
 *	License: This code is distributed under CC-BY-SA 3.0 and is unsupported.
 *		 (see creativecommons.org/licenses for info)
 *
 */

/* ****************************************************************************
This code is based on the Oscilloscope Christmas Tree from John M. De Cristofaro which can be found at http://www.johngineer.com/blog/?p=648

attach a rc-filter with 10k/100nF to each output like this:

PWM OUT ----/\/\/\-----+------------ OUTPUT
		R      |
		      === C
                       |
                      PIN4
                      
We're using Pin4 as gnd, so we can build the circuit on some Stripboard and plug it straight on the Arduino
Also i put the Coordinates for the Points in picture.h. Apart from that it's pretty much the same code as John's

**************************************************************************** */
#include "picture.h"

#define TRACE_DELAY	2500  // trace delay in uS. making this longer will
			      // result in a straighter drawing, but slower
			      // refresh rate. making it too short will result
			      // in an angular blob.



#define X               6     // attach scope channel 1 (X) to pin 6
#define Y               5     // attach scope channel 2 (y) to pin 5




void setup()
{
  pinMode(X, OUTPUT);
  pinMode(Y, OUTPUT);
  pinMode(4, OUTPUT);
  digitalWrite(4,LOW);

  // The following sets the PWM clock to maximum on the Arduino(no CPU clock division)
  // DO NOT CHANGE THESE UNLESS YOU KNOW WHAT YOU ARE DOING!
  
  TCCR0A = (	1<<COM0A1 | 0<<COM0A0 |		// clear OC0A on compare match (hi-lo PWM)
		1<<COM0B1 | 0<<COM0B0 |		// clear OC0B on compare match (hi-lo PWM)
		1<<WGM01  | 1<<WGM00);		// set PWM lines at 0xFF

  TCCR0B = (	0<<FOC0A | 0<<FOC0B |		// no force compare match
		0<<WGM02 |			// set PWM lines at 0xFF
		0<<CS02	 | 0<<CS01 |		// use system clock (no divider)
		1<<CS00 );

  TIMSK0 = (	0<<OCIE0B | 0<<TOIE0 |
		0<<OCIE0A );  

}

void loop()
{
    unsigned char t;
    {
      for(t = 0; t < NUM_POINTS; t++)		// run through the points in x & y
      {
        analogWrite(X, x_points[t]);
        analogWrite(Y, y_points[t]);
	delayMicroseconds(TRACE_DELAY);		// wait TRACE_DELAY microseconds
      }
    }
}

