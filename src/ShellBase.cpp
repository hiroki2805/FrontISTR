/*
 ----------------------------------------------------------
|
| Software Name :HEC middleware Ver. 3.0beta
|
|   ShellBase.cxx
|
|                     Written by T.Takeda,    2010/06/01
|                                K.Goto,      2010/01/12
|                                K.Matsubara, 2010/06/01
|
|   Contact address : IIS, The University of Tokyo CISS
|
 ----------------------------------------------------------
*/
#include "ShellBase.h"
#include "ElementType.h"
using namespace pmw;
uint CShellBase::mnBaseType = BaseElementType::Shell;
CShellBase::CShellBase():CElement()
{
    ;
}
CShellBase::~CShellBase()
{
}
