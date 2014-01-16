/**
 * CXmlParser.cpp Define the class to parse XML files
 *
 * @author: SHUYUFANG
 */

#include <fstream>
#include "CXmlParser.h"

CXmlParser::CXmlParser(const std::string& sFile)
{
    std::ifstream ifsFile(sFile.c_str());
	if (!ifsFile)
	{
        return;
	}

	m_pDoc = new TiXmlDocument();
    if (!m_pDoc)
    {
        return;
    }
	if (!m_pDoc->LoadFile(sFile.c_str()))
	{
        delete m_pDoc;
        m_pDoc = NULL;
        return;
	}
}

CXmlParser::CXmlParser(const CXmlParser& oXmlParser)
{
}

CXmlParser::~CXmlParser()
{
	if (m_pDoc)
	{
		delete m_pDoc;
		m_pDoc = NULL;
	}
}

TiXmlElement* CXmlParser::GetRoot()
{
	if (!m_pDoc)
	{
		return NULL;
	}

	return m_pDoc->RootElement();
}

TiXmlElement* CXmlParser::GetFirstChildNode(TiXmlElement* pParNode, 
	                                        const std::string& sChiNodeName)
{
	if (!pParNode)
	{
		return NULL;
	}

	TiXmlElement* pChildNode = pParNode->FirstChildElement();
	while (pChildNode)
	{
		if (sChiNodeName.empty())
		{
			return pChildNode;
		}
		else
		{
			if (0 == sChiNodeName.compare(pChildNode->Value()))
			{
				return pChildNode;
			}
		}
		pChildNode = pChildNode->NextSiblingElement();
	}

	return NULL;
}

std::list<TiXmlElement*> CXmlParser::GetChildNodes(TiXmlElement* pParNode, 
	                                               const std::string& sChiNodeName)
{
	std::list<TiXmlElement*> nodeList;

	if (!pParNode)
	{
		return nodeList;
	}

	TiXmlElement* pChildNode = pParNode->FirstChildElement();
	while (pChildNode)
	{
		if (sChiNodeName.empty())
		{
			nodeList.push_back(pChildNode);
		}
		else
		{
			if (0 == sChiNodeName.compare(pChildNode->Value()))
			{
				nodeList.push_back(pChildNode);
			}
		}
		pChildNode = pChildNode->NextSiblingElement();
	}

	return nodeList;
}

std::string CXmlParser::GetNodeName(TiXmlElement* pNode)
{
	if (!pNode)
	{
		return "";
	}

	std::string sNodeName(pNode->Value());
	return sNodeName;
}

std::string CXmlParser::GetNodeAttrValue(TiXmlElement* pNode, 
                                         const std::string& sAttr)
{
	if (!pNode)
	{
		return "";
	}

	const char* pAttrValue = pNode->Attribute(sAttr.c_str());

	if (!pAttrValue)
	{
		return "";
	}
	std::string sAttrValue(pAttrValue);
	return sAttrValue;
}

std::string CXmlParser::GetNodeContent(TiXmlElement* pNode)
{
	if (!pNode)
	{
		return "";
	}

	std::string sContent(pNode->GetText());
	return sContent;
}