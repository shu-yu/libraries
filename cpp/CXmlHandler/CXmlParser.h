/**
 * CXmlParser.h Define the class to parse XML files
 *
 * @author: SHUYUFANG
 */

#ifndef _CXML_PARSER_H
#define _CXML_PARSER_H

#include <cstdlib>
#include <string>
#include <list>
#include "TinyXml/tinyxml.h"

class CXmlParser
{
public:
    /**
     * Constructor
     * @param sFile: the path of the xml file
     */
    CXmlParser(const std::string& sFile);

    /**
     * Destructor
     */
    ~CXmlParser();

    /**
	 * Get root node
	 * @return the root node
	 */
	TiXmlElement* GetRoot();
    
	/**
	 * Get first child node 
	 * @param pParNode: parent node
	 * @param sChiNode: child node name
	 * @return the first child node
	 */
	TiXmlElement* GetFirstChildNode(TiXmlElement* pParNode, 
                                    const std::string& sChiNodeName = "");
    
	/**
	 * Get child node list
	 * @param pParNode: parent node
	 * @param sChiNode: child node name
	 * @return the child node list
	 */
	std::list<TiXmlElement*> GetChildNodes(TiXmlElement* pParNode, const std::string& sChiNodeName = "");
	
	/**
	 * Get node name
	 * @param pNode: the node
	 * @return the name of the node
	 */
	std::string GetNodeName(TiXmlElement* pNode);
	
	/**
	 * Get node attribute value
	 * @param pNode: the node
	 * @param sAttr: the name of the attribute
	 * @return the value of the attribute
	 */
	std::string GetNodeAttrValue(TiXmlElement* pNode, const std::string& sAttr);
	
	/**
	 * Get node content
	 * @param pNode: the node
	 * @return the content of the node
	 */
	std::string GetNodeContent(TiXmlElement* pNode);

private:
    /**
     * Copy constructor
     * @param oXmlParser: xml parser object
     */
    CXmlParser::CXmlParser(const CXmlParser& oXmlParser);

private:
    /** the path of the xml file */
    std::string m_sFile;

    /** the pointer of the document object */
    TiXmlDocument* m_pDoc;
};

#endif