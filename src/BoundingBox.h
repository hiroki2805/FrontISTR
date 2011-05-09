/*
 ----------------------------------------------------------
|
| Software Name :HEC middleware Ver. 3.0beta
|
|   BoundingBox.h
|
|                     Written by T.Takeda,    2010/06/01
|                                K.Goto,      2010/01/12
|                                K.Matsubara, 2010/06/01
|
|   Contact address : IIS, The University of Tokyo CISS
|
 ----------------------------------------------------------
*/
#include "TypeDef.h"
#include "SkinFace.h"
namespace pmw{
#ifndef _BOUNDINGBOX_H
#define	_BOUNDINGBOX_H
class CBoundingBox{
public:
    CBoundingBox();
    virtual ~CBoundingBox();
protected:
    vdouble mMinCoord,mMaxCoord;
    vdouble mvOBBCenter;
    vdouble mvOBBX;
    vdouble mvOBBY;
    vdouble mvOBBZ;
    vdouble mvE;
public:
    void sizingABB(CSkinFace* pFace);
    bool judgeABB(CSkinFace* pFace);
    bool judgeABB(CContactNode* pConNode);
    void sizingOBB(CSkinFace* pFace);
    bool judgeOBB(CContactNode* pConNode);
};
#endif	/* _BOUNDINGBOX_H */
}
