/*=====================================================================*
 *                                                                     *
 *   Software Name : neu2fstr                                          *
 *         Version : 1.00                                              *
 *                                                                     *
 *     Last Update : 2006/06/01                                        *
 *        Category : FrontSTR Input File Converter                     *
 *                                                                     *
 *            Written by Noboru Imai (Univ. of Tokyo)                  *
 *                                                                     *
 *     Contact address :  IIS,The University of Tokyo RSS21 project    *
 *                                                                     *
 *     "Structural Analysis System for General-purpose Coupling        *
 *      Simulations Using Hight End Computing Middleware (HEC-MW)"     *
 *                                                                     *
 *=====================================================================*/

/*
	CHECDB_EGroup Ver.1.0
*/

#include "CHECDB.h"
#include "CHECData.h"

using namespace std;
using namespace hecd_util;



CHECDB_EGroup::CHECDB_EGroup()
 : CHECDataBlock(HECDB_EGROUP), ElemList()
{
	name[0] = 0;
}


CHECDB_EGroup::~CHECDB_EGroup()
{
}


void CHECDB_EGroup::Clear()
{
	ElemList.clear();
}


void CHECDB_EGroup::Write( CHECData* hecd )
{
	if( ElemList.size() == 0 ) return;

	hecd->WriteHeader( "!EGROUP", "S", "EGRP", name );

	set<int>::iterator iter;
	for(iter = ElemList.begin(); iter != ElemList.end(); iter++){
		hecd->WriteData( "I", *iter );
	}
}


bool CHECDB_EGroup::Read( CHECData* hecd, char* header_line )
{
	int rcode[5];
	if(! hecd->ParseHeader( header_line, rcode, "S", "EGRP", name )) return false;

	char line[256];
	const int max_id_n = 100;
	int id[max_id_n];
	int i,n;

	while(1) {
		if(!hecd->ReadLine(line)) break;
		if( line[0] == '!' ) {
			hecd->PushReadLine(line);
			break;
		}
		n = hecd->ParseIntDataArray( line, id );
		if(n<0) return false;
		for(i=0;i<n;i++) {
			ElemList.insert( id[i] );
		}
	}
	return true;
}


