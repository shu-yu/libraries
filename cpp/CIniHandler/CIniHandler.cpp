/**
 * CIniHandler.cpp Realization of the class to handle INI files
 *
 * @author: SHUYUFANG
 */

#include <fstream>
#include <sstream>
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include "CIniHandler.h"

const int MAX_INI_FILE_SIZE = 1024 * 32;
const int MAX_INI_LINE_SIZE = 1024;

CIniHandler::CIniHandler(const std::string& sFileName)
{
    m_sFileName = sFileName;
}

CIniHandler::CIniHandler(const CIniHandler& oIniHandler)
{
}

CIniHandler::~CIniHandler()
{
    
}

const std::string& CIniHandler::GetFileName() const
{
    return m_sFileName;
}

const std::string& CIniHandler::GetSection() const
{
    return m_sSection;
}

void CIniHandler::SetSection(const std::string& sSection)
{
    m_sSection = sSection;
}

bool CIniHandler::Write(const std::string& sKey, 
                        const std::string& sValue) const
{
    return WriteProfileString(m_sFileName, m_sSection, sKey, sValue);
}

bool CIniHandler::Write(const std::string& sKey, int iValue) const
{
    std::stringstream ssStream;
    std::string sValue = "";

    ssStream << iValue;
    ssStream >> sValue;

    return Write(sKey, sValue);
}

std::string CIniHandler::ReadString(const std::string& sKey, 
                                    const std::string& sDefaultValue) const
{
    std::string sValue;
    ReadProfileString(m_sFileName, m_sSection, sKey, sValue, sDefaultValue);
    return sValue;
}

int CIniHandler::ReadInteger(const std::string& sKey, 
                             int iDefaultValue) const
{
    int iValue;
    ReadProfileInteger(m_sFileName, m_sSection, sKey, &iValue, iDefaultValue);
    return iValue;
}

bool CIniHandler::LoadFile(const std::string& sFileName, 
                           std::string& sBuffer)
{
    std::ifstream ifsFile(sFileName.c_str());
    if (!ifsFile)
    {
        sBuffer = "";
        return false;
    }

    sBuffer = "";
    char szBuf[MAX_INI_LINE_SIZE + 1];

    while (ifsFile.getline(szBuf, MAX_INI_LINE_SIZE))
    {
        sBuffer.append(szBuf);
        sBuffer.append("\n");
    }

    sBuffer.append(szBuf);

    ifsFile.clear();
    ifsFile.close();
    return true;
}

bool CIniHandler::IsNewLine(char c)
{
    return ('\n' == c || '\r' == c);
}

bool CIniHandler::IsEndOfString(char c)
{
    return '\0' == c;
}

bool CIniHandler::IsLeftBrace(char c)
{
    return '[' == c;
}

bool CIniHandler::IsRightBrace(char c)
{
    return ']' == c;
}

bool CIniHandler::ParseFile(const std::string& sBuffer, 
                            const std::string& sSection, 
                            const std::string& sKey, 
                            int* pSecStart, 
                            int* pSecEnd, 
                            int* pKeyStart, 
                            int* pKeyEnd, 
                            int* pValueStart, 
                            int* pValueEnd)
{
    if (sSection.empty() || sKey.empty() || sBuffer.empty())
    {
        return false;
    }
    
    const char* pBuf = sBuffer.c_str();
    *pSecStart = -1;
    *pSecEnd = -1;
    *pKeyStart = -1;
    *pKeyEnd = -1;
    *pValueStart = -1;
    *pValueEnd = -1;

    int iPos = 0;
    while (!IsEndOfString(pBuf[iPos]))
    {
        // find the section
        if ((0 == iPos || IsNewLine(pBuf[iPos - 1])) && \
            IsLeftBrace(pBuf[iPos]))
        {
            int iSecStart = iPos + 1;

            // find the right brace
            do
            {
                ++iPos;
            } 
            while (!IsRightBrace(pBuf[iPos]) && !IsEndOfString(pBuf[iPos]));

            if (0 == strncmp(pBuf + iSecStart, sSection.c_str(), iPos - iSecStart))
            {
                int iNewlineStart = 0;
                ++iPos;
                while (isspace(pBuf[iPos]))
                {
                    ++iPos;
                }

                *pSecStart = iSecStart;
                *pSecEnd = iPos;

                while (!(IsNewLine(pBuf[iPos - 1]) && \
                       IsLeftBrace(pBuf[iPos])) && \
                       !IsEndOfString(pBuf[iPos]))
                {
                    int iTmpPos = 0;

                    // get a new line
                    iNewlineStart = iPos;
                    while (!IsNewLine(pBuf[iPos]) && \
                           !IsEndOfString(pBuf[iPos]))
                    {
                        ++iPos;
                    }

                    iTmpPos = iNewlineStart;

                    if (';' != pBuf[iTmpPos])
                    {
                        while (iTmpPos < iPos && \
                               pBuf[iTmpPos] != '=')
                        {
                            ++iTmpPos;
                            if ('=' == pBuf[iTmpPos] && 
                                0 == strncmp(sKey.c_str(), 
                                             pBuf + iNewlineStart, 
                                             iTmpPos - iNewlineStart))
                            {
                                *pKeyStart = iNewlineStart;
                                *pKeyEnd = iTmpPos - 1;

                                *pValueStart = iTmpPos + 1;
                                *pValueEnd = iPos;

                                return true;
                            }
                        }
                    }
                    ++iPos;
                }
            }
        }
        else
        {
            ++iPos;
        }
    }

    return false;
}

bool CIniHandler::ReadProfileString(const std::string& sFileName, 
                                    const std::string& sSection, 
                                    const std::string& sKey, 
                                    std::string& sValue, 
                                    const std::string& sDefaultValue)
{
    if (sSection.empty() || sKey.empty() || sFileName.empty())
    {
        return false;
    }

    std::string sBuffer = "";
    if (!LoadFile(sFileName, sBuffer))
    {
        sValue = sDefaultValue;
        return false;
    }

    int iSecStart = 0;
    int iSecEnd = 0;
    int iKeyStart = 0;
    int iKeyEnd = 0;
    int iValueStart = 0;
    int iValueEnd = 0;

    if (!ParseFile(sBuffer, sSection, sKey, &iSecStart, &iSecEnd, &iKeyStart, 
                   &iKeyEnd, &iValueStart, &iValueEnd))
    {
        sValue = sDefaultValue;
        return false;
    }

    sValue = sBuffer.substr(iValueStart, iValueEnd - iValueStart);

    return true;
}

bool CIniHandler::ReadProfileInteger(const std::string& sFileName, 
                                     const std::string& sSection, 
                                     const std::string& sKey, 
                                     int* pValue, int iDefaultValue)
{
    std::stringstream ssStream;
    std::string sValue = "";
    if (!ReadProfileString(sFileName, sSection, sKey, sValue))
    {
        *pValue = iDefaultValue;
        return false;
    }

    ssStream << sValue;
    ssStream >> (*pValue);
    
    return true;
}

bool CIniHandler::WriteProfileString(const std::string& sFileName, 
                                     const std::string& sSection, 
                                     const std::string& sKey, 
                                     const std::string& sValue)
{
    if (sSection.empty() || sKey.empty() || sFileName.empty())
    {
        return false;
    }

    std::string sBuffer = "";
    std::string sNewBuffer = "";

    int iSecStart = 0;
    int iSecEnd = 0;
    int iKeyStart = 0;
    int iKeyEnd = 0;
    int iValueStart = 0;
    int iValueEnd = 0;

    if (!LoadFile(sFileName, sBuffer))
    {
        iSecStart = -1;
    }
    else if (sBuffer.size() <= MAX_INI_FILE_SIZE)
    {
        ParseFile(sBuffer, sSection, sKey, &iSecStart, &iSecEnd, 
                  &iKeyStart, &iKeyEnd, &iValueStart, &iValueEnd);
    }
    else
    {
        return false;
    }

    if (-1 == iSecStart)
    {
        if (sBuffer.empty())
        {
            sNewBuffer.append("[").append(sSection).append("]\n").append(sKey).append("=").append(sValue).append("\n");
        }
        else
        {
            sNewBuffer.append(sBuffer);
            sNewBuffer.append("\n[").append(sSection).append("]\n").append(sKey).append("=").append(sValue).append("\n");
        }
    }
    else if (-1 == iKeyStart)
    {
        sNewBuffer.append(sBuffer.substr(0, iSecEnd));
        sNewBuffer.append(sKey).append("=").append(sValue).append("\n");
        sNewBuffer.append(sBuffer.substr(iSecEnd));
    }
    else
    {
        sNewBuffer.append(sBuffer.substr(0, iValueStart));
        sNewBuffer.append(sValue);
        sNewBuffer.append(sBuffer.substr(iValueEnd));
    }

    std::ofstream ofsFile(sFileName.c_str());
    if (!ofsFile)
    {
        return false;
    }

    ofsFile << sNewBuffer;

    ofsFile.clear();
    ofsFile.close();
    return true;
}

bool CIniHandler::WriteProfileInteger(const std::string& sFileName, 
                                const std::string& sSection, 
                                const std::string& sKey, 
                                int iValue)
{
    std::stringstream ssStream;
    std::string sValue = "";

    ssStream << iValue;
    ssStream >> sValue;

    return CIniHandler::WriteProfileString(sFileName, sSection, sKey, sValue);
}
