/*
 ----------------------------------------------------------
|
| Software Name :HEC middleware Ver. 3.0beta
|
|   FileReaderRefine.cxx
|
|                     Written by T.Takeda,    2010/06/01
|                                K.Goto,      2010/01/12
|                                K.Matsubara, 2010/06/01
|
|   Contact address : IIS, The University of Tokyo CISS
|
 ----------------------------------------------------------
*/
#include "FileReaderRefine.h"
using namespace FileIO;
CFileReaderRefine::CFileReaderRefine()
{
    ;
}
CFileReaderRefine::~CFileReaderRefine()
{
    ;
}
bool CFileReaderRefine::Read(ifstream& ifs, string& sLine)
{
    uint numOfRefine;
    if(TagCheck(sLine, FileBlockName::StartRefine()) ){
        while(true){
            sLine = getLineSt(ifs);
            if(TagCheck(sLine, FileBlockName::EndRefine()) ) break;
            istringstream iss(sLine.c_str());
            iss >> numOfRefine;
            mpLogger->Info(Utility::LoggerMode::MWDebug, "FileReaderRefine::numOfRefine == ", numOfRefine);
        };
        mpFactory->GeneAssyModel(numOfRefine+1);
        mpFactory->setMGLevel(numOfRefine);     
        return true;
    }else{
        return false;
    }
}
