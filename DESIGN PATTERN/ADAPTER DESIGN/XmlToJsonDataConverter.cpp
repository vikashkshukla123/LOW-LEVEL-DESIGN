#include<iostream>
#include<string>

using namespace std;

// Target Interface expected by a client
class IReports{
    public:
    // now takes the raw data string and converts into JSON
    virtual string getJsonData(const string&data) = 0;
    virtual ~IReports() {}
};


// 2. Adaptee : provides XML data from a raw input
class XmlDataProvider{
    public:
    // expects data in "name : id" format (eg: 'Alice:42')
    string getXmlData(const string&data){
        size_t sep = data.find(':');
        string name = data.substr(0,sep);
        string id = data.substr(sep+1);

        // builds an xml representation
        return "<user>"
               "<name>" + name + "</name>"
               "<id>" + id + "</id>"
               "</user>";
    }
};

// 3. Adapter : implements IReoprts by converting xml to json
class XmlDataProviderAdapter : public IReports{
    private:
    XmlDataProvider* xmlProvider;
    public :
    XmlDataProviderAdapter(XmlDataProvider* provider){
        this->xmlProvider = provider;
    }

    string getJsonData(const string&data) override {
        // 1. get xml from adaptee
        string xml = xmlProvider->getXmlData(data);

        // Naively parse out <name> and <id> values

        size_t startName = xml.find("<name>") + 6;
        size_t endName = xml.find("</name>");
        string name = xml.substr(startName,endName - startName);


        size_t startId = xml.find("<id>") + 4;
        size_t endId = xml.find("</id>");
        string id = xml.substr(startId, endId - startId);




        return "{\"name\":\"" + name + "\", \"id\":" + id + "}";
    }

};

// 4. client code works only with ireports
class Client{
    public:
    void getReport(IReports* report, string rawData){
        cout<<"Processes JSON: "<<report->getJsonData(rawData)<<endl;
    }
};


int main(){
    // 1 created a adaptee
    XmlDataProvider* xmlProv = new XmlDataProvider;

    // 2  make our adapter
    IReports*adapter = new XmlDataProviderAdapter(xmlProv);

    //3 give it some raw data;
    string rawData = "Alice:42";

    // 4 client print the json
    Client * client = new Client();
    client->getReport(adapter, rawData);

    // Processes json : {'name"::"Alice", "id:"42}


    // 5 clean up

    delete adapter;
    delete xmlProv;
    return 0;
}