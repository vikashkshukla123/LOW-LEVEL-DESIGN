#include<iostream>
using namespace std;

// Subsystems;
class PowerSupply {
    public:
    void providePower(){
        cout<<"Power Supply : providing power.."<<endl;
    }
};

class CoolingSystem{
    public:
    void startFans(){
        cout<<"Cooling System : Fans started..."<<endl;
    }
};


class CPU{
    public:
    void initialize(){
        cout<<"CPU : Initialization started..."<<endl;
    }
};

class Memory{
    public:
    void selfTest(){
        cout<<"Memory: Self Test Passed"<<endl;
    }
};
class HardDrive{
    public:
    void spinUp(){
        cout<<"Hard Drive : Spinning up"<<endl;
    }
};

class BIOS{
    public:
    void boot(CPU&cpu, Memory&memory){
        cout<<"BIOS : Booting cpu and memory checks..."<<endl;
        cpu.initialize();
        memory.selfTest();
    }
};

class OperatingSystem{
    public:
    void load(){
        cout<<"Operating System : Loading into the memory"<<endl;
    }
};



// FACADE
class ComputerFacade{
    private:
    PowerSupply powerSupply;
    CoolingSystem coolingSystem;
    CPU cpu;
    Memory memory;
    HardDrive hardDrive;
    BIOS bios;
    OperatingSystem os;

    public:
    void startComputer(){
        cout<<"......STARTING COMPUTER...."<<endl;
        powerSupply.providePower();
        coolingSystem.startFans();
        bios.boot(cpu,memory);
        hardDrive.spinUp();
        os.load();
        cout<<"Computer Booted Successfully"<<endl;

        }
};


// Client
int main(){
    ComputerFacade computer;
    computer.startComputer();
    return 0;
}
