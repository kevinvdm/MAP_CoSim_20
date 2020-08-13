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

        //auto var = md->model_variables->getByValueReference(1).as_real();
        //auto var2 = md->model_variables->getByValueReference(2).as_real();
        
        //std::cout << "Name=" << var.name() << ", start=" << var.start().value_or(0) << std::endl;

        slave = cs_fmu->new_instance();

        std::cout << "model_identifier=" << slave->get_model_description()->model_identifier << std::endl;

        slave->setup_experiment();
        slave->enter_initialization_mode();
        slave->exit_initialization_mode();

        vr1 = {
            md->get_variable_by_name("Throttle").value_reference,
	        md->get_variable_by_name("Vdesired").value_reference
            };
	    vr2 = {
            md->get_variable_by_name("Velocity").value_reference
            };
        
        // while ((t = slave->get_simulation_time()) <= stop) {

        //     if (!slave->step(stepSize)) { break; }
        //     if (!slave->read_real(vr, ref)) { break; }
        
        //     std::cout << "Time=" << t << ", Wind=" << ref[0] << ", Incline=" << ref[1] << std::endl;

        // }

        //std::cout << "FMU '" << fmu.model_name() << "' terminated with success: " << (slave->terminate() == 1 ? "true" : "false") << std::endl;

    }

    void doFmuStep(float64_t stepSize, float64_t *v){
            slave->step(stepSize);
            ref2[0] = *v;
            slave->write_real(vr2, ref2);
            slave->read_real(vr1, ref1);
            std::cout << "Time=" << t << ", Throttle=" << ref1[0] << ", Vdesired="  << ref1[1]  << ", Velocity=" << ref2[0] << std::endl;
    }

    float64_t getThrottle(){
        return ref1[0];
    }

   float64_t getVdesired(){
	return ref1[1];
    }

private:


    const std::string fmu_path = "./Controller_Seperate_Step_BBB.fmu";
    std::unique_ptr<fmi4cpp::fmi2::cs_fmu> cs_fmu;
    std::unique_ptr<fmi4cpp::fmi2::cs_slave> slave;
    std::shared_ptr<const fmi4cpp::fmi2::cs_model_description> md;

    std::vector<fmi2ValueReference> vr1;
    std::vector<fmi2ValueReference> vr2;
    std::vector<fmi2Real> ref1 = std::vector<fmi2Real>(1);
    std::vector<fmi2Real> ref2 = std::vector<fmi2Real>(1);

    double t = 0;

};
