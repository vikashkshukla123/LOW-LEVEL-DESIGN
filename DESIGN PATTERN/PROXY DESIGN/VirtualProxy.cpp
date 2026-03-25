#include<iostream>
#include<string>

using namespace std;

class IImage{
    public:
    virtual void display() = 0;
    virtual ~IImage(){}
};

class RealImage : public IImage{
    string fileName;
    public:
    RealImage(string file){
        this->fileName = file;
        // heavy operation
        cout<<"[RealImage] Loading Image from disk:"<<fileName<<"\n";
    }

    void display() override{
        cout<<"[RealImage] Displaying"<<fileName<<"\n";
    }
};

class IImageProxy : public IImage{
    RealImage* realImage;
    string fileName;

    public:
    IImageProxy(string file){
        this->fileName = file;
        realImage = nullptr;
    }

    void display() override{
        // lazy initialization of realimage
        if(!realImage){
            realImage = new RealImage(fileName);
        }
        realImage->display();
    }


};


int main(){
    IImage * image1 = new IImageProxy("sample.jpg");
    image1->display();
}