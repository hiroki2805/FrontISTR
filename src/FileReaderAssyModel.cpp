/*
 ----------------------------------------------------------
|
| Software Name :HEC middleware Ver. 3.0beta
|
|   FileReaderAssyModel.cxx
|
|                     Written by T.Takeda,    2010/06/01
|                                K.Goto,      2010/01/12
|                                K.Matsubara, 2010/06/01
|
|   Contact address : IIS, The University of Tokyo CISS
|
 ----------------------------------------------------------
*/
#include "FileReaderAssyModel.h"
using namespace FileIO;
CFileReaderAssyModel::CFileReaderAssyModel()
{
    ;
}
CFileReaderAssyModel::~CFileReaderAssyModel()
{
    ;
}
bool CFileReaderAssyModel::Read(ifstream& ifs, string& sLine)
{
    uint nMeshID, numOfMesh, maxID, minID;
    vint vMeshID;
    uint mgLevel(0);
    if(TagCheck(sLine, FileBlockName::StartAssyModel()) ){
        mpLogger->Info(Utility::LoggerMode::MWDebug, "FileReaderAssyModel", sLine);
        sLine = getLineSt(ifs);
        istringstream iss(sLine.c_str());
        iss >> numOfMesh >> maxID >> minID;
        mpFactory->setupBucketMesh(mgLevel, maxID, minID);
        while(true){
            sLine = getLineSt(ifs);
            if(TagCheck(sLine, FileBlockName::EndAssyModel()) ) break;
            istringstream iss(sLine.c_str());
            while(iss >> nMeshID){
                mpLogger->Info(Utility::LoggerMode::MWDebug, "nMeshID == ", nMeshID);
                vMeshID.push_back(nMeshID);
            };
        };
        mpFactory->reserveMesh(mgLevel, numOfMesh);
        uint i;
        for(i=0; i < vMeshID.size(); i++){
            mpFactory->GeneMesh(mgLevel, vMeshID[i], i);
        };
        return true;
    }else{
        return false;
    }
}
