#include <fmi4cpp/fmi4cpp.hpp>

#include <iostream>
#include <string>

using namespace fmi4cpp;

class FMULoader {
public:
    FMULoader() {
        fmi2::fmu fmu("ExternalSim_Test.fmu");

        auto cs_fmu = fmu.as_cs_fmu();

        //smart pointer to a cs_model_description instance
        auto cs_md = cs_fmu->get_model_description();
        std::cout << "model_identifier=" << cs_md->model_identifier << std::endl;

        auto var = cs_md->get_variable_by_name("b").as_real();
        std::cout << "Name=" << var.name() <<  ", start=" << var.start().value_or(0) << std::endl;
              
        auto slave = cs_fmu->new_instance();
    
        slave->setup_experiment();
        slave->enter_initialization_mode();
        slave->exit_initialization_mode();

        auto vr = var.valueReference();

        while ( (t = slave->get_simulation_time()) <= stop) {

            if (!slave->step(stepSize)) {
                std::cerr << "Error! step() returned with status: " << to_string(slave->last_status()) << std::endl;
                break;
            }
        
            if (!slave->read_real(vr, value)) {
                std::cerr << "Error! step() returned with status: " << to_string(slave->last_status()) << std::endl;
                break;
            }
            std::cout << "t=" << t << ", " << var.name() << "=" << value << std::endl;
     
        }
    
        slave->terminate();
    }

    void simulateFmu(){

    }


private:

    const double stop = 10;
    const double stepSize = 1E-3;

    double t;
    double value;

};