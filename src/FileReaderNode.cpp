/*
 ----------------------------------------------------------
|
| Software Name :HEC middleware Ver. 3.0beta
|
|   FileReaderNode.cxx
|
|                     Written by T.Takeda,    2010/06/01
|                                K.Goto,      2010/01/12
|                                K.Matsubara, 2010/06/01
|
|   Contact address : IIS, The University of Tokyo CISS
|
 ----------------------------------------------------------
*/
#include "FileReaderNode.h"
using namespace FileIO;
CFileReaderNode::CFileReaderNode()
{
}
CFileReaderNode::~CFileReaderNode()
{
}
bool CFileReaderNode::Read(ifstream& ifs, string& sLine)
{
    uint   nNodeID, nMeshID, numOfNode, maxID, minID;
    vdouble vCoord; vCoord.resize(3);
    uint  nType, numOfScalarParam, numOfVectorParam;
    string sType;
    uint  mgLevel(0); 
    if(TagCheck(sLine, FileBlockName::StartNode()) ){
        mpLogger->Info(Utility::LoggerMode::MWDebug, sLine);
        sLine = getLineSt(ifs);
        istringstream iss(sLine.c_str());
        iss >> numOfNode >> nMeshID >> maxID >> minID;
        mpFactory->reserveNode(mgLevel, nMeshID, numOfNode);
        mpFactory->initBucketNode(mgLevel, nMeshID, maxID, minID);
        uint nCount(0);
        while(true){
            sLine = getLineSt(ifs);
            if(TagCheck(sLine, FileBlockName::EndNode()) ) break;
            istringstream iss(sLine.c_str());
            iss  >> sType >> numOfScalarParam >> numOfVectorParam >> nNodeID >> vCoord[0] >> vCoord[1] >> vCoord[2];
            if(sType=="sv"||sType=="SV"){
                nType=pmw::NodeType::ScalarVector;
            }else if(sType=="s"||sType=="S"){
                nType=pmw::NodeType::Scalar;
            }else if(sType=="v"||sType=="V"){
                nType=pmw::NodeType::Vector;
            }
            else{
                mpLogger->Info(Utility::LoggerMode::Error,"NodeType mismatch, at FileReaderNode");
            }
            mpLogger->Monitor(Utility::LoggerMode::MWDebug, nNodeID, vCoord, "Node");
            if(!mpFactory) mpLogger->Info(Utility::LoggerMode::MWDebug, "Factory => NULL, at FileReaderNode");
            mpFactory->GeneNode(mgLevel, nMeshID, nNodeID, vCoord, nType, numOfScalarParam, numOfVectorParam);
            mpFactory->setIDBucketNode(mgLevel, nMeshID, nNodeID, nCount);
            nCount++;
        };
        mpLogger->Info(Utility::LoggerMode::MWDebug, sLine);
        mpFactory->setupNode(mgLevel, nMeshID);
        mpFactory->reserveAggregate(mgLevel, nMeshID, nCount);
        mpFactory->GeneAggregate(mgLevel, nMeshID, nCount);   
        return true;
    }else{
        return false;
    }
}
