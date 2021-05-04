#include <Arduino.h>

/**
 *
 *               R
 * PWM OUT ----/\/\/\-----+------------ OUTPUT
 *	                      |
 *	                     === C
 *                        |
 *                       GND
 * R = 10k
 * C = 0.1uF
 *
 * Quartz = 16Mhz
*/

#define X 6 // attach scope channel 1 (X) to pin 6
#define Y 5 // attach scope channel 2 (y) to pin 5

//                                  1     2    3    4   5     6    7   8    9    10   11   12   13   14   15   16   17   18   19    20  21    22   23  24    25    26    27   28   29   30   31  32   33    34   35   36   37   38   39  40    41
const unsigned char x_punisher[] = {128, 128, 115, 115, 115, 102, 90, 51, 64, 45, 64, 102, 128, 154, 192, 211, 192, 205, 166, 154, 141, 141, 141, 128, 128, 134, 192, 179, 134, 122, 64, 77, 122, 121, 116, 125, 121, 135, 140, 131, 135};
const unsigned char y_punisher[] = {102, 38, 39, 102, 39, 40, 115, 102, 128, 179, 230, 253, 255, 253, 230, 179, 128, 102, 115, 40, 39, 102, 39, 38, 102, 141, 179, 141, 141, 141, 179, 141, 141, 140, 125, 115, 140, 140, 125, 115, 140};

void setup()
{
	pinMode(X, OUTPUT);
	pinMode(Y, OUTPUT);

	// The following sets the PWM clock to maximum on the Arduino
	TCCR0A = (1 << COM0A1 | 0 << COM0A0 | // clear OC0A on compare match (hi-lo PWM)
						1 << COM0B1 | 0 << COM0B0 | // clear OC0B on compare match (hi-lo PWM)
						1 << WGM01 | 1 << WGM00);		// set PWM lines at 0xFF

	TCCR0B = (0 << FOC0A | 0 << FOC0B | // no force compare match
						0 << WGM02 |							// set PWM lines at 0xFF
						0 << CS02 | 0 << CS01 |		// use system clock (no divider)
						1 << CS00);

	TIMSK0 = (0 << OCIE0B | 0 << TOIE0 |
						0 << OCIE0A);
}

void loop()
{
	unsigned char t;
	{
		int phases = 20;
		for (int i = 0; i < phases; i++)
		{
			for (t = 0; t < sizeof(x_punisher); t++) // run through the points in x & y
			{
				analogWrite(X, ((short)x_punisher[t] - 128) * i / phases + 128);
				analogWrite(Y, y_punisher[t]);
				delayMicroseconds(3000); // wait TRACE_DELAY microseconds
			}
		}
		for (int i = phases; i > 0; i--)
		{
			for (t = 0; t < sizeof(x_punisher); t++) // run through the points in x & y
			{
				analogWrite(X, ((short)x_punisher[t] - 128) * i / phases + 128);
				analogWrite(Y, y_punisher[t]);
				delayMicroseconds(3000); // wait TRACE_DELAY microseconds
			}
		}
	}
}