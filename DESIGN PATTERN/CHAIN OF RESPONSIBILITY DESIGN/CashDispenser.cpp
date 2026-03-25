#include<iostream>
using namespace std;

// ABSTRACT HANDLER (BASE CLASS)
class MoneyHandler{
    protected:
    MoneyHandler*nextHandler;

    public:
    MoneyHandler(){
        this->nextHandler = nullptr;
    }

    void setNextHandler(MoneyHandler *next){
        nextHandler = next;
    }

    virtual void dispense(int amount) = 0;
};

// concrete class for rs 1000 handler


class ThousandHandler : public MoneyHandler{
    private:
    int numNotes;

    public:
    ThousandHandler(int numNotes){
        this->numNotes = numNotes;
    }

    void dispense(int amount) override{
        int notesNeeded = amount/1000;

        if(notesNeeded > numNotes){
            notesNeeded = numNotes;
            numNotes = 0;
        }else{
            numNotes -= notesNeeded;
        }
        if(notesNeeded > 0){
            cout<<"Dispensing "<<notesNeeded<<" x Rs1000 notes.\n";
        }

        int remainingAmount = amount - (notesNeeded*1000);
        if(remainingAmount > 0){
            if(nextHandler != nullptr) nextHandler->dispense(remainingAmount);
        else{
            cout<<"Remaining amount of "<<remainingAmount<<" canot be fulfilled (insufficent balance)\n";
        }
    }
    }
};

// concrete classes for 500 rs handler
class FiveHundredHandler : public MoneyHandler{
    private:
    int numNotes;

    public:
    FiveHundredHandler(int numNotes){
        this->numNotes = numNotes;
    }

    void dispense(int amount) override{
        int notesNeeded = amount/500;

        if(notesNeeded > numNotes){
            notesNeeded = numNotes;
            numNotes = 0;
        }else{
            numNotes -= notesNeeded;
        }
        if(notesNeeded > 0){
            cout<<"Dispensing "<<notesNeeded<<" x Rs500 notes.\n";
        }

        int remainingAmount = amount - (notesNeeded*500);
        if(remainingAmount > 0){
            if(nextHandler != nullptr) nextHandler->dispense(remainingAmount);
        else{
            cout<<"Remaining amount of "<<remainingAmount<<" canot be fulfilled (insufficent balance)\n";
        }
    }
    }
};


// Concrete handler for 200rs notes
class TwoHundredHandler : public MoneyHandler{
    private:
    int numNotes;

    public:
    TwoHundredHandler(int numNotes){
        this->numNotes = numNotes;
    }

    void dispense(int amount) override{
        int notesNeeded = amount/200;

        if(notesNeeded > numNotes){
            notesNeeded = numNotes;
            numNotes = 0;
        }else{
            numNotes -= notesNeeded;
        }
        if(notesNeeded > 0){
            cout<<"Dispensing "<<notesNeeded<<" x Rs200 notes.\n";
        }

        int remainingAmount = amount - (notesNeeded*200);
        if(remainingAmount > 0){
            if(nextHandler != nullptr) nextHandler->dispense(remainingAmount);
        else{
            cout<<"Remaining amount of "<<remainingAmount<<" canot be fulfilled (insufficent balance)\n";
        }
    }
    }
};



class HundredHandler : public MoneyHandler{
    private:
    int numNotes;

    public:
    HundredHandler(int numNotes){
        this->numNotes = numNotes;
    }

    void dispense(int amount) override{
        int notesNeeded = amount/100;

        if(notesNeeded > numNotes){
            notesNeeded = numNotes;
            numNotes = 0;
        }else{
            numNotes -= notesNeeded;
        }
        if(notesNeeded > 0){
            cout<<"Dispensing "<<notesNeeded<<" x Rs100 notes.\n";
        }

        int remainingAmount = amount - (notesNeeded*100);
        if(remainingAmount > 0){
            if(nextHandler != nullptr) nextHandler->dispense(remainingAmount);
        else{
            cout<<"Remaining amount of "<<remainingAmount<<" canot be fulfilled (insufficent balance)\n";
        }
    }
    }
};



// client code
int main(){
    // creating handler for each notes type
    MoneyHandler*thousandHandler = new ThousandHandler(3);
    MoneyHandler*fiveHundredHandler = new FiveHundredHandler(5);
    MoneyHandler*twoHundredHandler = new TwoHundredHandler(10);
    MoneyHandler*hundredHandler = new HundredHandler(20);



    // setting up the chain of reponsibility;
    thousandHandler->setNextHandler(fiveHundredHandler);
    fiveHundredHandler->setNextHandler(twoHundredHandler);
    twoHundredHandler->setNextHandler(hundredHandler);

    // Initializing the chain

    int amountToWithdraw = 3000;
    cout<<"Dispensing amount in rs"<<amountToWithdraw<<endl;
    thousandHandler->dispense(amountToWithdraw);



    return 0;



}