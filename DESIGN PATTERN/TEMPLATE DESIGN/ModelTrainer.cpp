#include<iostream>
#include<string>

using namespace std;

// 1.BASE CLASS DEFINING THE TEMPLATE METHOD

class ModelTrainer{
    public:
    // this template method is final so the subclasses cannot change the sequence

    void trainPipeline(const string&dataPath){
        loadData(dataPath);
        preprocessData();
        // subclass specific
        trainModel();
        // subclass specific
        evaluateModel();
        // subclass specific or default;
        saveModel();
    }

    protected:
    void loadData(const string&path){
        cout<<"[Common] Loading dataset from "<<path<<"\n";
        // eg readcsv, images etc;
    }

    virtual void preprocessData(){
        cout<<"[Common] splitting into train/test and normalizing \n";
    }
    virtual void trainModel() = 0;
    virtual void evaluateModel() = 0;


    // provide a default save but subclasses can override if needed
    virtual void saveModel(){
        cout<<"[Common] Saving model to disk as default format\n";
    }
};


// 2.CONCRETE SUBCLASS : NEURAL NETWORK
class NeuralNetworkTrainer : public ModelTrainer{
    protected:
    void trainModel() override{
        cout<<"[NeuralNetwork] Training Network for 100 epochs\n";
        // psedo code : forward backward passes, gradient descent
    }
    void evaluateModel() override{
        cout<<"[NeuralNet] Evaluating accuracy and loss on validation set\n";
    }
    void saveModel() override{
        cout<<"[NeuralNet] Serialiazing network weights to .hs files\n ";
    }

};


// 3. Concrete subclass : DECISION TREES
class DecisionTreeTrainer : public ModelTrainer{
    protected:
    // use the default prprocess data() train-test-split + normalize
    void trainModel() override{
        cout<<"[DecisionTree] Buliding decision tree with max_depths\n";
        // psedo code : forward backward passes, gradient descent
    }
    void evaluateModel() override{
        cout<<"[DecisionTree] Computing classification report (precision/recall)\n";
    }

    // use the default save model()


};


int main(){
    cout<<"Neural Network Training====\n";
    ModelTrainer*nnTrainer = new NeuralNetworkTrainer();
    nnTrainer->trainPipeline("data/images/");


    cout<<"Decision Tree Training===\n";
    ModelTrainer*dtTrainer = new DecisionTreeTrainer();
    dtTrainer->trainPipeline("data/iris.csv");

    return 0;

}