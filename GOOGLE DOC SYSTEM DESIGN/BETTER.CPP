#include<iostream>
#include<string>
#include<vector>
#include<fstream>

using namespace std;

// abstraction for document element
class DocumentElement{
    public:
    virtual string render() = 0;
};

// concrete implementation of text elements
class TextElement : public DocumentElement{
    private:
    string text;

    public :
    TextElement(string text){
        this->text = text;
    }
    string render() override {
        return text;
    }
};

// concrete implementation of image elements
class ImageElement : public DocumentElement{
    private:
    string imagePath;

    public :
    ImageElement(string imagePath){
        this->imagePath = imagePath;
    }
    string render() override{
        return "[Image : " + imagePath + "]";
    }
};
// newline element reperesents a tab space in the document

class NewLineElement : public DocumentElement{
    public :
    string render() override{
        return "\n";
    }
};

// tabspace element represents a tab sapce in the document
class TabSpaceElement : public DocumentElement{
    public :
    string render() override{
        return "\t";
    }
};

// DOCUMENT CLASS REPONSIBLE FOR HOLDING A COLLECTION OF ELEMENTS
class Document{
    private:
    vector<DocumentElement*> documentElements;

    public:
    void addElement(DocumentElement* element){
        documentElements.push_back(element);
    }

    string render(){
        string result;
        for(auto element : documentElements){
            result += element->render();
        }
        return result;
    }

    // renders the document by concatenationg the render output of all elements
};

// persistance interface
class Persistance{
    public : 
    virtual void save(string data) = 0;
};


// filestorage implementatio of persistance;
class FileStorage : public Persistance{
    public :
    void save(string data) override{
        ofstream outFile("document.txt");
        if(outFile){
            outFile << data;
            outFile.close();
            cout<<"Document saved to document.txt"<<endl;
        }else{
            cout<<"Error : Unable to open file for writing."<<endl;
        }
    }
};

// db implementation of persistance

class DBStorage : public Persistance{
    public:
    void save(string data) override{
        // save to db
    }
};


// documentEdiotor class or managing client interactions

class DocumentEditor{
    private:
    Document* document;
    Persistance* storage;
    string renderedDocument;


    public:
    DocumentEditor(Document*document, Persistance*storage){
        this->document = document;
        this->storage = storage;
    }

    void addText(string text){
        document->addElement(new TextElement(text));
    }

    void addImage(string imagePath){
        document->addElement(new ImageElement(imagePath));
    }

    // adds a new line to the element
    void addNewLine(){
        document->addElement(new NewLineElement());
    }

    // adds a tab space to the document
    void addTabSpace(){
        document->addElement(new TabSpaceElement());
    }

    string renderDocument(){
        if(renderedDocument.empty()){
            renderedDocument = document->render();
        }
        return renderedDocument;
    }

    void saveDocument(){
        storage->save(renderDocument());
    }
};


// clinet usage example

int main(){
    Document*document = new Document();
    Persistance*persistance = new FileStorage();

    DocumentEditor*editor = new DocumentEditor(document,persistance);

    // simulate a client using the editor with common text formatting features;
    editor->addText("Hello World !");
    editor->addNewLine();
    editor->addText("This is a real world document editor example.");
    editor->addNewLine();
    editor->addTabSpace();
    editor->addText("Indented text after a tab space");
    editor->addImage("picture.jpg");


    // render and display the final document;
    cout<<editor->renderDocument() <<endl;

    editor->saveDocument();

    return 0;

}
