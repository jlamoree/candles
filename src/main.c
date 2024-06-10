
#define ENABLE_BIT_DEFINITIONS


//#include "iotiny85.h"
#include <avr/io.h>
#include "prng.h"

#define SetDutyCycle(duty)    (OCR1A = 0xFF - duty)
#define IncramentDutyCycle(a) (OCR1A -= a)
#define DecramentDutyCycle(a) (OCR1A += a)
#define GetDutyCycle()        (0xFF - OCR1A)

void InitPwm(void);
unsigned int randint(unsigned int min, unsigned int max);
unsigned long randlong(unsigned long min, unsigned long max);

#define MIN_IL 50
#define MAX_IL 255

#define MIN_RT 100
#define MAX_RT 1000

#define MIN_ID 3000
#define MAX_ID 100000

#define MS_TIMER (waitTime)
#define TimeoutExpired(a) ((long)MS_TIMER - (long)a < 0)

int main( void )
{
  unsigned long time = 0;
  unsigned long waitTime = 0;
  unsigned long rampTime;
  int seed;
  unsigned char illumination;

  InitPwm();
  srand(seed);

  for(;;)
  {
    // Set ilumination level
    illumination = randint(MIN_IL,MAX_IL);
    rampTime = randint(MIN_RT,MAX_RT);

    for(;;)
    {
        for(time = 0; time < rampTime; time++);
        if( GetDutyCycle() < illumination )
        {
            IncramentDutyCycle(1);
        }
        else
        {
            DecramentDutyCycle(1);
        }

        if( GetDutyCycle() == illumination )
            break;
    }

    // Set illumination duration
    waitTime = randlong(MIN_ID,MAX_ID);
    //while(!TimeoutExpired(waitTime));

    for(time = 0; time < waitTime; time++);
  }
}

void InitPwm(void)
{
    // Fast PWM with non-inverting OCRx
    TCCR1 = (1<<PWM1A)|(0<<COM1A1)|(1<<COM1A0 )|(1<<CS12)|(0<<CS11 )|(1<<CS10);
    //GTCCR = (1<<PWM1B)|(1<<COM1B1)|(0<<COM1B0);
    //TCCR1 = 0x05;
    //GTCCR = 0x70;
    //OCR1C = 0xFF;

    DDRB = 0x01;
}

//generates a psuedo-random integer between min and max
unsigned int randint(unsigned int min, unsigned int max)
{
    unsigned int randVal = (unsigned int)rand();
    randVal = min + randVal % (max - min);

    return randVal;
}

unsigned long randlong(unsigned long min, unsigned long max)
{
    unsigned long randVal = rand();
    randVal = min + randVal % (max - min);

    return randVal;
}
