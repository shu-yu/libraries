#include <iostream>
#include "CIniHandler.h"

int main()
{
    std::string sFileName("test.ini");
    CIniHandler oIniHandler(sFileName);

    std::string sStudentName = "hello";
    int iStudentNumber = 123;
    std::string sTeacherName = "world";
    int iTeacherRoom = 456;
    std::string sTeacherLevel = "high";

    oIniHandler.SetSection("student");
    oIniHandler.Write("name", sStudentName);
    oIniHandler.Write("number", iStudentNumber);

    oIniHandler.SetSection("teacher");
    CIniHandler::WriteProfileInteger(sFileName, "teacher", "room", iTeacherRoom);
    CIniHandler::WriteProfileString(sFileName, "teacher", "name", sTeacherName);
    CIniHandler::WriteProfileString(sFileName, "teacher", "level", sTeacherLevel);

    oIniHandler.SetSection("student");
    sStudentName = oIniHandler.ReadString("name", "unknown");
    iStudentNumber = oIniHandler.ReadInteger("number", -1);

    CIniHandler::ReadProfileString(sFileName, "teacher", "name", sTeacherName, "unknown");
    CIniHandler::ReadProfileInteger(sFileName, "teacher", "room", &iTeacherRoom, -1);
    CIniHandler::ReadProfileString(sFileName, "teacher", "level", sTeacherLevel, "unknown");

    std::cout << "student name: " << sStudentName << std::endl;
    std::cout << "student number: " << iStudentNumber << std::endl;
    std::cout << "teacher name: " << sTeacherName << std::endl;
    std::cout << "teacher room: " << iTeacherRoom << std::endl;
    std::cout << "teacher level: " << sTeacherLevel << std::endl;

    return 0;
}
