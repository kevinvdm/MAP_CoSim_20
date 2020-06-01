#define _GNU_SOURCE 1
#include "stdio.h"
#include <termios.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include "libpruio/pruio.h"
#include "libpruio/pruio_pins.h"

//! The pin for PWM output.
#define P_OUT P9_21

//! The main function.
int main(int argc, char **argv)
{
  pruIo *Io = pruio_new(PRUIO_DEF_ACTIVE, 4, 0x98, 0);
    if (Io->Errr) {
               printf("initialisation failed (%s)\n", Io->Errr);}

    if (pruio_pwm_setValue(Io, P_OUT, 500, 0)) {
        printf("failed setting output @P_OUT (%s)\n", Io->Errr);}

    if (pruio_config(Io, 1, 0x1FE, 0, 4)) {
                       printf("config failed (%s)\n", Io->Errr);}
}
