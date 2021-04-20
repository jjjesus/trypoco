#include "Poco/DOM/DOMParser.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/NodeIterator.h"
#include "Poco/DOM/NodeFilter.h"
#include "Poco/DOM/AutoPtr.h"
#include "Poco/SAX/InputSource.h"

#include <algorithm>
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <streambuf>
#include <string>

#include <cctype>


inline std::string& trim(std::string& str)
{
    str.erase(0, str.find_first_not_of(' '));       //prefixing spaces
    str.erase(str.find_last_not_of(' ')+1);         //suffixing spaces
    return str;
}


void parse2(Poco::AutoPtr<Poco::XML::Document>& pDoc)
{
        Poco::XML::NodeIterator it(pDoc,
            Poco::XML::NodeFilter::SHOW_ELEMENT
        );
        Poco::XML::Node* pNode = it.nextNode();
        while (pNode)
        {
            if (pNode->nodeName() == "constant")
            {
                pNode = it.nextNode();
                if (pNode->nodeName() == "name") {
                    std::string text = pNode->innerText();
                    text = trim(text);
                    std::cout << text << " ";
                }
                pNode = it.nextNode();
                if (pNode->nodeName() == "value") {
                    std::string text = pNode->innerText();
                    size_t pos = text.find("0x");
                    if (pos != std::string::npos) {
                        text.erase(pos, 2);
                    }
                    text = trim(text);
                    std::cout << text << " ";
                }
                pNode = it.nextNode();
                if (pNode->nodeName() == "comment") {
                    std::string text = pNode->innerText();
                    text = trim(text);
                    std::cout << text << " ";
                }
            }
            std::cout << std::endl;
            pNode = it.nextNode();
        }
}


int main(int argc, char** argv)
{
    try {

        std::ifstream in("MessageLabels.xml");
        Poco::XML::InputSource src(in);

        Poco::XML::DOMParser parser;
        parser.setFeature(Poco::XML::DOMParser::FEATURE_FILTER_WHITESPACE, true);
        Poco::AutoPtr<Poco::XML::Document> pDoc = parser.parse(&src);

        parse2(pDoc);
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}

