/*
 ----------------------------------------------------------
|
| Software Name :HEC middleware Ver. 3.0beta
|
|   FileWriter.cxx
|
|                     Written by T.Takeda,    2010/06/01
|                                K.Goto,      2010/01/12
|                                K.Matsubara, 2010/06/01
|
|   Contact address : IIS, The University of Tokyo CISS
|
 ----------------------------------------------------------
*/
#include "FileWriter.h"
using namespace FileIO;
CFileWriter::CFileWriter()
{
    mpGMGModel= pmw::CGMGModel::Instance();
}
CFileWriter::~CFileWriter()
{
    ;
}