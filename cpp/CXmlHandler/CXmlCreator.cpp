/**
 * CXmlCreator.cpp Define the class to create XML files
 *
 * @author: SHUYUFANG
 */

#include <fstream>
#include "CXmlCreator.h"

CXmlCreator::CXmlCreator(const std::string& sFile)
{
	m_sFile = sFile;
    m_pRootNode = NULL;
}

CXmlCreator::CXmlCreator(const CXmlCreator& oXmlCreator)
{
}

CXmlCreator::~CXmlCreator()
{
    if (m_pRootNode)
    {
        delete m_pRootNode;
    }
}

TiXmlElement* CXmlCreator::AddRoot(const std::string& sName)
{
	m_pRootNode = new TiXmlElement(sName.c_str());

	if (!m_pRootNode)
	{
		return NULL;
	}

	return m_pRootNode;
}

TiXmlElement* CXmlCreator::AddNode(TiXmlElement* pParNode, 
                                   const std::string& sName)
{
	if (!pParNode)
	{
		return NULL;
	}

	TiXmlElement* pChiNode = new TiXmlElement(sName.c_str());
	pParNode->LinkEndChild(pChiNode);

	return pChiNode;
}

bool CXmlCreator::AddNodeAttr(TiXmlElement* pNode, const std::string& sName, 
                              const std::string& sValue)
{
	if (!pNode || sName.empty())
	{
		return false;
	}

	pNode->SetAttribute(sName.c_str(), sValue.c_str());

	return true;
}

bool CXmlCreator::AddNodeData(TiXmlElement* pNode, const std::string& sData)
{
	if (!pNode)
	{
		return false;
	}

	TiXmlText* pText = new TiXmlText(sData.c_str());
	pText->SetCDATA(true);
	pNode->LinkEndChild(pText);

	return true;
}

bool CXmlCreator::AddNodeText(TiXmlElement* pNode, const std::string& sText)
{
	if (!pNode)
	{
		return false;
	}

	TiXmlText* pText = new TiXmlText(sText.c_str());
	pText->SetCDATA(false);
	pNode->LinkEndChild(pText);

	return true;
}

bool CXmlCreator::CreateXml(const std::string& sEncoding)
{
    if (m_sFile.empty() || !m_pRootNode)
    {
        return false;
    }

    TiXmlDeclaration* pDecl = new TiXmlDeclaration("1.0", sEncoding.c_str(), "");
    std::string sBuffer = "";
    TiXmlPrinter oPrinter;
    std::ofstream ofsFile(m_sFile.c_str());

    pDecl->Accept(&oPrinter);
    m_pRootNode->Accept(&oPrinter);
    sBuffer = oPrinter.CStr();
    ofsFile << sBuffer << std::endl;

    ofsFile.close();

    return true;
}
