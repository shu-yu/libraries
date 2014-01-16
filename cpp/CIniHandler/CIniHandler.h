/**
 * CIniHandler.h Define the class to handle INI files
 *
 * @author: SHUYUFANG
 */

#ifndef _CINI_HANDLER_H
#define _CINI_HANDLER_H

#include <string>

class CIniHandler
{
public:
    /**
     * Constructor
     * @param sFileName: the name of the ini file
     */
    CIniHandler(const std::string& sFileName);

    /**
     * Destructor
     */
    virtual ~CIniHandler();

    /**
     * Get the name of the ini file
     * @return the name of the ini file
     */
    const std::string& GetFileName() const;

    /**
     * Get the name of the section
     * @return the name of the section
     */
    const std::string& GetSection() const;

    /**
     * Set the name of the section
     * @param sSection: name of the section
     */
    void SetSection(const std::string& sSection);

    /**
     * Write a string as value to the file
     * @param sKey: the name of the key
     * @param sValue: the string value
     * @return successfully write or not
     */
    bool Write(const std::string& sKey, const std::string& sValue) const;

    /**
     * Write an integer as value to the file
     * @param sKey: the name of the key
     * @param iValue: the integer value
     * @return successfully write or not
     */
    bool Write(const std::string& sKey, int iValue) const;

    /**
     * Read a string from the file
     * @param sKey: the name of the key
     * @param sDefaultValue: the default value
     * @return the actual value if successful, the default value if not
     */
    std::string ReadString(const std::string& sKey, 
                           const std::string& sDefaultValue = "") const;

    /**
     * Read an integer from the file
     * @param sKey: the name of the key
     * @param iDefaultValue: the default value
     * @return the actual value if successful, the default value if not
     */
    int ReadInteger(const std::string& sKey, int iDefaultValue = 0) const;

public:
    /**
     * Read a string from ini file according to the section and the key
     * @param sFileName: the name of the ini file
     * @param sSection: the name of the section
     * @param sKey: the name of the key
     * @param sValue: the value to read from the file
     * @param sDefaultValue: the default value
     * @return the actual value if successful, the default value if not
     */
    static bool ReadProfileString(const std::string& sFileName, 
                                  const std::string& sSection, 
                                  const std::string& sKey, std::string& sValue, 
                                  const std::string& sDefaultValue = "");
    
    /**
     * Read an integer from ini file according to the section and the key
     * @param sFileName: the name of the ini file
     * @param sSection: the name of the section
     * @param sKey: the name of the key
     * @param sValue: the value to read from the file
     * @param iDefaultValue: the default value
     * @return the actual value if successful, the default value if not
     */
    static bool ReadProfileInteger(const std::string& sFileName, 
                                   const std::string& sSection, 
                                   const std::string& sKey, 
                                   int* pValue, int iDefaultValue = 0);
    
    /**
     * Write a string to ini file
     * @param sFileName: the name of the ini file
     * @param sSection: the name of the section
     * @param sKey: the name of the key
     * @param sValue: the value
     * @return successfully write or not
     */
    static bool WriteProfileString(const std::string& sFileName, 
                                   const std::string& sSection, 
                                   const std::string& sKey, 
                                   const std::string& sValue);
    
    /**
     * Write an integer to ini file
     * @param sFileName: the name of the ini file
     * @param sSection: the name of the section
     * @param sKey: the name of the key
     * @param iValue: the value
     * @return successfully write or not
     */
    static bool WriteProfileInteger(const std::string& sFileName, 
                                    const std::string& sSection, 
                                    const std::string& sKey, 
                                    int iValue);

private:
    /**
     * Copy constructor
     * @param oIniHandler: the ini handler to be copied
     */
    CIniHandler(const CIniHandler& oIniHandler);

    /**
     * Load the content of the file into the buffer
     * @param sFileName: the name of the ini file
     * @param sBuffer: the buffer to be loaded
     * @return successfully load or not
     */
    static bool LoadFile(const std::string& sFileName, std::string& sBuffer);

    /**
     * Judge whether the character is '\r' or '\n'
     * @param c: the character
     * @return it's '\r' or '\n' or not
     */
    static bool IsNewLine(char c);
    
    /**
     * Judge whether the character is '\0'
     * @param c: the character
     * @return it's a '\0' or not
     */
    static bool IsEndOfString(char c);
    
    /**
     * Judge whether the character is '['
     * @param c: the character
     * @return it's a '[' or not
     */
    static bool IsLeftBrace(char c);
    
    /**
     * Judge whether the character is ']'
     * @param c: the character
     * @return it's a ']' or not
     */
    static bool IsRightBrace(char c);
    
    /**
     * Parse the file to get the position of the section, key and value
     * @param sBuffer: the buffer of the ini file
     * @param sSection: the name of the section
     * @param sKey: the name of the key
     * @param pSecStart: pointer of the variable representing start of section
     * @param pSecEnd: pointer of the variable representing end of section
     * @param pKeyStart: pointer of the variable representing start of key
     * @param pKeyEnd: pointer of the variable representing end of key
     * @param pValueStart: pointer of the variable representing start of value
     * @param pValueEnd: pointer of the variable representing end of value
     * @return successfully parse or not
     */
    static bool ParseFile(const std::string& sBuffer, 
                          const std::string& sSection, 
                          const std::string& sKey, 
                          int* pSecStart, int* pSecEnd, 
                          int* pKeyStart, int* pKeyEnd, 
                          int* pValueStart, int* pValueEnd);

private:
    /** the name of the ini file */
    std::string m_sFileName;

    /** the name of the section */
    std::string m_sSection;
};

#endif
