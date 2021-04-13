#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>
#include <exception>
#include <fstream>
#include <iostream>
#include <streambuf>
#include <string>


void print_frame_numbers(Poco::JSON::Array::Ptr root);

int main(int argc, char** argv)
{
    try {

        //read file
        std::ifstream t("all5.json");
        std::string json_str((std::istreambuf_iterator<char>(t)),
                    std::istreambuf_iterator<char>());

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(json_str);
        Poco::JSON::Array::Ptr json = result.extract<Poco::JSON::Array::Ptr>();
        print_frame_numbers(json);
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}

void print_frame_numbers(Poco::JSON::Array::Ptr root)
{
    for (Poco::JSON::Array::ConstIterator it = root->begin();
         it != root->end(); ++it) {
        Poco::JSON::Object::Ptr obj = it->extract<Poco::JSON::Object::Ptr>();
        Poco::JSON::Object::Ptr source = obj->getObject("_source");
        Poco::JSON::Object::Ptr layers = source->getObject("layers");
        Poco::JSON::Object::Ptr frame = layers->getObject("frame");
        Poco::Dynamic::Var frame_number_var = frame->get("frame.number");
        std::string frame_num = frame_number_var.toString();
        std::cout << "frame_num:" << frame_num << std::endl;
    }
    //std::string root_key = "_source";
    //std::string key = "layers";
    //no checks whether such key acually exists
    //Poco::JSON::Object::Ptr package_json = root->getObject(root_key);
    //get the nested objects
    //Poco::JSON::Object::Ptr nested_sources = package_json->getObject(key);

    //iterate the map
    //Poco::JSON::Object::Iterator it;
    //for(it = nested_sources->begin(); it != nested_sources->end(); it++)
    //{
        //no check of whether it is an object
        //std::cout<<it->first<<"\n";
    //}
}

