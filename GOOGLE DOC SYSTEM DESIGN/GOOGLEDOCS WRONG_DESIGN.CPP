#include<iostream>
#include<vector>
#include<string>
#include<fstream>
using namespace std;

class DocumentEditor{
    private:
    vector<string> documentElements;
    string renderedDocument;


    public:
    // adds text as a plain string
    void addText(string text){
        documentElements.push_back(text);
    }

    // adds an image represented by its file path

    void addImage(string imagePath){
        documentElements.push_back(imagePath);
    }

    // renders the document by checking the type of each element at runtime
    string renderDocument(){
        if(renderedDocument.empty()){
            string result;
            for(auto element : documentElements){
                if(element.size() > 4 && (element.substr(element.size() - 4) == ".jpg" || element.substr(element.size() - 4) == ".png")){
                    result += "[Image: " + element + "]" + "\n";
                }else{
                    result += element + '\n';
                }
            }
            renderedDocument = result;
            return renderedDocument;
        }else{
            return renderedDocument;
        }
    }


    void saveToFile(){
        ofstream file("document.txt");
        if(file.is_open()){
            file << renderDocument();
            file.close();
            cout<<"Document saved to document.txt"<<endl;
        }else{
            cout<<"Error : Unable to open file for writting"<<endl;
        }
    }

};

int main(){
    DocumentEditor editor;
    editor.addText("Hello world !");
    editor.addImage("picture.jpg");
    editor.addText("This is document editor.");

    cout<<editor.renderDocument()<<endl;

    editor.saveToFile();

    return 0;

}