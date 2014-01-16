/**
 * CXmlCreator.h Define the class to create XML files
 *
 * @author: SHUYUFANG
 */

#ifndef _CXML_CREATOR_H
#define _CXML_CREATOR_H

#include <string>
#include "TinyXml/tinyxml.h"

class CXmlCreator
{
public:
    /**
     * Constructor
     * @param sFile: the path of xml file
     */
    CXmlCreator(const std::string& sFile);

	/**
	 * Destructor
	 */
	~CXmlCreator();

	/**
	 * Add root node
	 * @param sName: root node name
	 * @return the root node
	 */
	TiXmlElement* AddRoot(const std::string& sName);

	/**
	 * Add node
	 * @param pParNode: parent node
	 * @param sName: node name
	 * @return the new node
	 */
	TiXmlElement* AddNode(TiXmlElement* pParNode, const std::string& sName);

	/**
	 * Add node attribute
	 * @param pNode: the node to add attribute
	 * @param sName: attribute name
	 * @param sValue: attribute value
	 * @return true if successful, otherwise false
	 */
	bool AddNodeAttr(TiXmlElement* pNode, const std::string& sName, 
                     const std::string& sValue);

	/**
	 * Add node data
	 * @param pNode: the node to add CDATA
	 * @param sData: node data
	 * @return true if successful, otherwise false
	 */
	bool AddNodeData(TiXmlElement* pNode, const std::string& sData);

	/**
	 * Add node text
	 * @param pNode: the node to add text
	 * @param sText: node text
	 * @return true if successful, otherwise false
	 */
	bool AddNodeText(TiXmlElement* pNode, const std::string& sText);

	/**
	 * Create XML file
	 * @param sEncoding: encoding of the XML file
	 * @return true if successful, otherwise false
	 */
	bool CreateXml(const std::string& sEncoding = "utf-8");

private:
    /**
     * Copy constructor
     * @param oXmlCreator: xml creator object
     */
    CXmlCreator::CXmlCreator(const CXmlCreator& oXmlCreator);

private:
	/** the root node object pointer */
	TiXmlElement* m_pRootNode;

	/** the xml file path to create */
	std::string m_sFile;
};

#endif