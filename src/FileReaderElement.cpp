/*
 ----------------------------------------------------------
|
| Software Name :HEC middleware Ver. 3.0beta
|
|   FileReaderElement.cxx
|
|                     Written by T.Takeda,    2010/06/01
|                                K.Goto,      2010/01/12
|                                K.Matsubara, 2010/06/01
|
|   Contact address : IIS, The University of Tokyo CISS
|
 ----------------------------------------------------------
*/
#include "ElementType.h"
#include "FileReaderElement.h"
using namespace FileIO;
CFileReaderElement::CFileReaderElement()
{
}
CFileReaderElement::~CFileReaderElement()
{
}
bool CFileReaderElement::Read(ifstream& ifs, string& sLine)
{
    string sTypeName;
    uint   nElementID, numOfElem, nMeshID, maxID, minID;
    vint   vLocalNode;
    uint   mgLevel(0);
    uint  i;
    if(TagCheck(sLine, FileBlockName::StartElement()) ){
        mpLogger->Info(Utility::LoggerMode::MWDebug, "FileReaderElement ", sLine);
        sLine = getLineSt(ifs);
        istringstream iss(sLine.c_str());
        iss >> numOfElem >> nMeshID >> maxID >> minID;
        mpFactory->reserveElement(mgLevel, nMeshID, numOfElem);
        mpFactory->initBucketElement(mgLevel, nMeshID, maxID, minID);
        uint nCount(0);
        while(true){
            sLine = getLineSt(ifs);
            if(TagCheck(sLine, FileBlockName::EndElement()) ) break; 
            istringstream iss(sLine.c_str());
            iss >> sTypeName;
            vLocalNode.clear();
            if(sTypeName=="Tetra"){
                vLocalNode.resize(4);
                iss >> nElementID;
                for(i=0; i< vLocalNode.size(); i++){ iss >> vLocalNode[i]; }
                mpLogger->Monitor(Utility::LoggerMode::MWDebug, nElementID, vLocalNode, sTypeName);
                mpFactory->GeneElement(mgLevel, nMeshID, nElementID, pmw::ElementType::Tetra,vLocalNode);
                mpFactory->setIDBucketElement(mgLevel, nMeshID, nElementID, nCount);
                nCount++;
            }
            if(sTypeName=="Hexa"){
                vLocalNode.resize(8);
                iss >> nElementID;
                for(i=0; i< vLocalNode.size(); i++){ iss >> vLocalNode[i]; }
                mpFactory->GeneElement(mgLevel, nMeshID, nElementID, pmw::ElementType::Hexa,vLocalNode);
                mpFactory->setIDBucketElement(mgLevel, nMeshID, nElementID, nCount);
                nCount++;
            }
            if(sTypeName=="Prism"){
                vLocalNode.resize(6);
                iss >> nElementID;
                for(i=0; i< vLocalNode.size(); i++){ iss >> vLocalNode[i];}
                mpFactory->GeneElement(mgLevel, nMeshID, nElementID, pmw::ElementType::Prism,vLocalNode);
                mpFactory->setIDBucketElement(mgLevel, nMeshID, nElementID, nCount);
                nCount++;
            }
            if(sTypeName=="Pyramid"){
                vLocalNode.resize(5);
                iss >> nElementID;
                for(i=0; i< vLocalNode.size(); i++){ iss >> vLocalNode[i];}
                mpFactory->GeneElement(mgLevel, nMeshID, nElementID, pmw::ElementType::Pyramid,vLocalNode);
                mpFactory->setIDBucketElement(mgLevel, nMeshID, nElementID, nCount);
                nCount++;
                mpLogger->Info(Utility::LoggerMode::Warn,"Non-Support MultiGrid, Pyramid Element");
            }
            if(sTypeName=="Triangle"){
                vLocalNode.resize(3);
                iss >> nElementID;
                for(i=0; i< vLocalNode.size(); i++){ iss >> vLocalNode[i];}
                mpFactory->GeneElement(mgLevel, nMeshID, nElementID, pmw::ElementType::Triangle,vLocalNode);
                mpFactory->setIDBucketElement(mgLevel, nMeshID, nElementID, nCount);
                nCount++;
            }
            if(sTypeName=="Quad"){
                vLocalNode.resize(4);
                iss >> nElementID;
                for(i=0; i< vLocalNode.size(); i++){ iss >> vLocalNode[i]; }
                mpFactory->GeneElement(mgLevel, nMeshID, nElementID, pmw::ElementType::Quad,vLocalNode);
                mpFactory->setIDBucketElement(mgLevel, nMeshID, nElementID, nCount);
                nCount++;
            }
            if(sTypeName=="Beam"){
                vLocalNode.resize(2);
                iss >> nElementID;
                for(i=0; i< vLocalNode.size(); i++){ iss >> vLocalNode[i]; }
                mpFactory->GeneElement(mgLevel, nMeshID, nElementID, pmw::ElementType::Beam,vLocalNode);
                mpFactory->setIDBucketElement(mgLevel, nMeshID, nElementID, nCount);
                nCount++;
            }
        };
        mpFactory->setupElement(mgLevel, nMeshID);
        mpLogger->Info(Utility::LoggerMode::MWDebug, "FileReaderElement ", sLine);
        return true;
    }else{
        return false;
    }
}