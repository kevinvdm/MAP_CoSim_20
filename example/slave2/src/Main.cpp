#include "Slave.hpp"
#include "PWMRead.hpp"

int main(int argc, char *argv[]) {
    Slave slave;
    PWMRead pwm;
    slave.start();
}
