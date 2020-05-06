#include <iostream> 
#include <fmi4cpp/fmi4cpp.hpp>

using namespace fmi4cpp;

const double stop = ...;
const double stepSize = ...;

int main() 
{
    fmi2::fmu fmu("path/to/fmu.fmu");

    auto cs_fmu = fmu.as_cs_fmu();
    auto me_fmu = fmu.as_me_fmu();
    
    auto cs_md = cs_fmu->get_model_description(); //smart pointer to a cs_model_description instance
    std::cout << "model_identifier=" << cs_md->model_identifier << std::endl;
    
    
    auto me_md = me_fmu->get_model_description(); //smart pointer to a me_model_description instance
    std::cout << "model_identifier=" << me_md->model_identifier << std::endl;
    
    auto var = cs_md->get_variable_by_name("my_var").as_real();
    std::cout << "Name=" << var.name() <<  ", start=" << var.start().value_or(0) << std::endl;
              
    auto slave = cs_fmu->new_instance();
    
    slave->setup_experiment();
    slave->enter_initialization_mode();
    slave->exit_initialization_mode();
    
    double t;
    double value;
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
    
    return 0;
}
