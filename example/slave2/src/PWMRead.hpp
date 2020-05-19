#define _GNU_SOURCE 1
#include "stdio.h"
#include <termios.h>
#include <unistd.h>
#include <errno.h>
#include "libpruio/pruio.h"
#include "libpruio/pruio_pins.h"

//! The pin for CAP input.
#define P_IN P9_42
//! The pin for PWM output.
#define P_OUT P9_21

class PWMRead {
public:
    PWMRead() {

        //configure input pin
        if (pruio_cap_config(Io, P_IN, 2.)) { 
          printf("failed setting input @P_IN (%s)\n", Io->Errr);
        }

        //pin config OK, transfer local settings to PRU and start
        if (pruio_config(Io, 1, 0x1FE, 0, 4)) {
                       printf("config failed (%s)\n", Io->Errr);
        }
    }

    //get current input
    float_t readFrequency() {
        if (pruio_cap_Value(Io, P_IN, &f, &d)) {
          printf("failed reading input @P_IN (%s)\n", Io->Errr);
        }
        printf("Frequency: %10f", f);
        return f;
    }

    //get current duty cycle
    float_t readDutyCycle() {
        if (pruio_cap_Value(Io, P_IN, &f, &d)) {
          printf("failed reading input @P_IN (%s)\n", Io->Errr);
        }
        printf("Duty cycle: %10f", d);
        return d;
    }

    //set new output
    void writePWM(float64_t *t){
      if (pruio_pwm_setValue(Io, P_OUT, 31250, *t)) {
        printf("failed setting output @P_OUT (%s)\n", Io->Errr);
      }
      printf("Set duty cycle on P9_21: %10f", *t);
    }

private:

    //! create new driver structure
    pruIo *Io = pruio_new(PRUIO_DEF_ACTIVE, 0x98, 0, 1);

    //calculated frequency f and duty cycle d
    float_t f;
    float_t d;

};
