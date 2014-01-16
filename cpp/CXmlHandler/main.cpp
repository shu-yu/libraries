#include <iostream>
#include "CXmlCreator.h"
#include "CXmlParser.h"

int main()
{
    // create xml file
    CXmlCreator oXmlCreator("test.xml");

    TiXmlElement* pClassElem = oXmlCreator.AddRoot("class");

    TiXmlElement* pTeacherElem = oXmlCreator.AddNode(pClassElem, "teacher");
    TiXmlElement* pTNameElem = oXmlCreator.AddNode(pTeacherElem, "name");
    oXmlCreator.AddNodeData(pTNameElem, "xiaoming");
    TiXmlElement* pTNumberElem = oXmlCreator.AddNode(pTeacherElem, "number");
    oXmlCreator.AddNodeData(pTNumberElem, "123");

    TiXmlElement* pStudentElem = oXmlCreator.AddNode(pClassElem, "student");
    TiXmlElement* pSNameElem = oXmlCreator.AddNode(pStudentElem, "name");
    oXmlCreator.AddNodeData(pSNameElem, "daming");
    TiXmlElement* pSNumberElem = oXmlCreator.AddNode(pStudentElem, "number");
    oXmlCreator.AddNodeText(pSNumberElem, "456");

    oXmlCreator.CreateXml();

    // parse xml file
    CXmlParser oXmlParser("test.xml");

    pClassElem = oXmlParser.GetRoot();
    pTeacherElem = oXmlParser.GetFirstChildNode(pClassElem, "teacher");
    pTNameElem = oXmlParser.GetFirstChildNode(pTeacherElem, "name");
    std::cout << "teacher name: " << oXmlParser.GetNodeContent(pTNameElem) << std::endl;
    pTNumberElem = oXmlParser.GetFirstChildNode(pTeacherElem, "number");
    std::cout << "teacher number: " << oXmlParser.GetNodeContent(pTNumberElem) << std::endl;

    pStudentElem = oXmlParser.GetChildNodes(pClassElem, "student").front();
    pSNameElem = oXmlParser.GetChildNodes(pStudentElem, "name").front();
    std::cout << "student name: " << oXmlParser.GetNodeContent(pSNameElem) << std::endl;
    pSNumberElem = oXmlParser.GetChildNodes(pStudentElem, "number").front();
    std::cout << "student number: " << oXmlParser.GetNodeContent(pSNumberElem) << std::endl;

    return 0;
}