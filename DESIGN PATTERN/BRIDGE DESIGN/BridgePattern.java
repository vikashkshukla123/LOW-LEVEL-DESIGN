// implementation hierarchy : Engine interface (LLL)
interface Engine{
    void start();
}

// concrete implementation (LLL)
class PetrolEngine implements Engine{
    @Override
    public void start(){
        System.out.println("Petrol Engine Started with ignition !");
    }
}

class DieselEngine implements Engine{
    @Override
    public void start(){
        System.out.println("Diesel Engine roaring in the road!");
    }
}


class ElectricEngine implements Engine{
    @Override
    public void start(){
        System.out.println("Electric Engine powering up silently!");
    }
}



// Abstraction Hierarchy : Car (HLL)

abstract class Car{
    protected Engine engine;
    public Car(Engine e){
        this.engine = e;
    }

    public abstract void drive();
}


// Refined Abstraction
class Sedan extends Car{
    public Sedan(Engine e){
        super(e);
    }


    @Override
    public void drive(){
        engine.start();
        System.out.println("Driving a sedan on the highway!");
    }
}


class SUV extends Car{
    public SUV(Engine e){
        super(e);
    }


    @Override
    public void drive(){
        engine.start();
        System.out.println("Driving a SUV offroad!");
    }
}



public class BridgePattern{
    public static void main(String[] args){
        // creating an engine implmentations
        Engine petrolEng = new PetrolEngine();
        Engine dieselEng = new DieselEngine();
        Engine electricEng = new ElectricEngine();


        // create a car abtraction , injecting Engine Implementation
        Car mySedan = new Sedan(petrolEng);
        Car mySUV = new SUV(electricEng);
        Car yourSUV = new SUV(dieselEng);


        // use the cars
        mySedan.drive();
        mySUV.drive();
        yourSUV.drive();
    }




}