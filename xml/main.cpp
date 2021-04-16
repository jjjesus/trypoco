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
                    std::cout << text << " ";
                }
                pNode = it.nextNode();
                if (pNode->nodeName() == "value") {
                    std::string text = pNode->innerText();
                    size_t pos = text.find("0x");
                    if (pos != std::string::npos) {
                        text.erase(pos, 2);
                    }
                    std::cout << text << " ";
                }
                pNode = it.nextNode();
                if (pNode->nodeName() == "comment") {
                    std::string text = pNode->innerText();
                    std::cout << text << " ";
                }
            }
            std::cout << std::endl;
            pNode = it.nextNode();
        }
}

void parse1(Poco::AutoPtr<Poco::XML::Document>& pDoc)
{
        Poco::XML::NodeIterator it(pDoc,
            Poco::XML::NodeFilter::SHOW_ALL
        );
        Poco::XML::Node* pNode = it.nextNode();
        while (pNode)
        {
            if (pNode->nodeName() == "comment") {
                pNode = it.nextNode();
                if (pNode->nodeName() != "#text") {
                    continue;
                }
                std::cout<< "Tag Text: " << pNode->nodeValue() << std::endl;
            }
            std::cout << pNode->nodeName() << ":" << pNode->nodeValue() <<
std::endl;
            std::cout << pNode->innerText() << std::endl;
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

