#include <fmi4cpp/fmi4cpp.hpp>
#include <iostream>
#include <string>

using namespace fmi4cpp;

class FMULoader {
public:
    FMULoader() {

        fmi2::fmu fmu(fmu_path);
        cs_fmu = fmu.as_cs_fmu();

        md = cs_fmu->get_model_description();

        auto var = md->model_variables->getByValueReference(1).as_real();
        
        std::cout << "Name=" << var.name() << ", start=" << var.start().value_or(0) << std::endl;

        slave = cs_fmu->new_instance();

        std::cout << "model_identifier=" << slave->get_model_description()->model_identifier << std::endl;

        slave->setup_experiment();
        slave->enter_initialization_mode();
        slave->exit_initialization_mode();

        ref = ref(2);

        vr = {
            md->get_variable_by_name("wind").value_reference,
            md->get_variable_by_name("b").value_reference};
        
        while ((t = slave->get_simulation_time()) <= stop) {

            if (!slave->step(stepSize)) { break; }
            if (!slave->read_real(vr, ref)) { break; }
        
            std::cout << "Time=" << t << ", Wind=" << ref[0] << ", Incline=" << ref[1] << std::endl;

        }

        std::cout << "FMU '" << fmu.model_name() << "' terminated with success: " << (slave->terminate() == 1 ? "true" : "false") << std::endl;

    }

    void doFmuStep(){
        while(1){
            if (!slave->step(stepSize)){
                break;
            }
            if (!slave->read_real(vr, ref)) { 
                break; 
            }
        }
    }


private:


    const std::string fmu_path;
    std::unique_ptr<fmi4cpp::fmi2::cs_fmu> cs_fmu;
    std::unique_ptr<fmi4cpp::fmi2::cs_slave> slave;
    std::shared_ptr<const fmi4cpp::fmi2::cs_model_description> md;

    std::vector<fmi2ValueReference> vr;
    std::vector<fmi2Real> ref;

    const double stop = 10;
    const double stepSize = 1E-3;

    double t = 0;

};