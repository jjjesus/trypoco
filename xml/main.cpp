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


int main(int argc, char** argv)
{
    try {

        std::ifstream in("MessageLabels.xml");
        Poco::XML::InputSource src(in);

        Poco::XML::DOMParser parser;
        Poco::AutoPtr<Poco::XML::Document> pDoc = parser.parse(&src);

        Poco::XML::NodeIterator it(pDoc, Poco::XML::NodeFilter::SHOW_ELEMENT);
        Poco::XML::Node* pNode = it.nextNode();
        while (pNode)
        {
            std::cout<<pNode->nodeName()<<":"<< pNode->nodeValue()<<std::endl;
            pNode = it.nextNode();
        }

    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}

