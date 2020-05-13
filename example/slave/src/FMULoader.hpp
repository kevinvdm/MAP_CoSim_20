#include <fmi4cpp/fmi4cpp.hpp>

#include <iostream>
#include <string>

using namespace fmi4cpp;

class FMULoader {
public:

    FMULoader() {
        fmi2::fmu fmu("ExternalSim_Test.fmu");

        auto cs_fmu = fmu.as_cs_fmu();
        auto md = cs_fmu->get_model_description();

        auto var = md->model_variables->getByValueReference(1).as_real();
        
        std::cout << "Name=" << var.name() << ", start=" << var.start().value_or(0) << std::endl;

        auto slave1 = cs_fmu->new_instance();
        auto slave2 = cs_fmu->new_instance();

        std::cout << "model_identifier=" << slave1->get_model_description()->model_identifier << std::endl;

        slave1->setup_experiment();
        slave1->enter_initialization_mode();
        slave1->exit_initialization_mode();

        slave2->setup_experiment();
        slave2->enter_initialization_mode();
        slave2->exit_initialization_mode();

        std::vector<fmi2Real> ref(2);
        std::vector<fmi2ValueReference> vr = {
            md->get_variable_by_name("wind").value_reference,
            md->get_variable_by_name("b").value_reference};
        
        while ((t = slave1->get_simulation_time()) <= stop) {

            if (!slave1->step(stepSize)) { break; }
            if (!slave1->read_real(vr, ref)) { break; }
            std::cout << "Time=" << t << ", Wind=" << ref[0] << ", Incline=" << ref[1] << std::endl;
        }

        std::cout << "FMU '" << fmu.model_name() << "' terminated with success: " << (slave1->terminate() == 1 ? "true" : "false") << std::endl;
        std::cout << "FMU '" << fmu.model_name() << "' terminated with success: " << (slave2->terminate() == 1 ? "true" : "false") << std::endl;

    }

    void simulateFmu(){

    }


private:

    const double stop = 10;
    const double stepSize = 1E-3;

    double t = 0;

};