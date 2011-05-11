/*
	fstr_res_util Ver.1.3
	2010.09.27 by K.Suemitsu (AdvanceSoft)
	2004.10.26 by N.Imai (RIST)
	--------------------------------------------------------
	ʬ���Ƿ׻����줿��̤��ɹ��߽������뤿��Υ桼�ƥ���ƥ�
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "hecmw_util.h"
#include "hecmw_io_mesh.h"
#include "hecmw_io_struct.h"
#include "hecmw_struct.h"
#include "hecmw_config.h"
#include "hecmw_dist.h"
#include "hecmw_dist_free.h"
#include "hecmw_common.h"

#include "hecmw_control.h"
#include "hecmw_result.h"
#include "hecmw_io_dist.h"
#include "hecmw_io_get_mesh.h"


/* ���Ϸ�̥ե�������� */
typedef struct {
	int nnode_gid;
	int nelem_gid;
	int* node_gid;
	int* elem_gid;
	struct hecmwST_result_data* result;
} fstr_res_info;

/* �������Х�Υ�������ID �б� */
typedef struct {
	int global;
	int local;
	int area;
} fstr_gl_rec;

/* �������Х�Υ��������б�ɽ */
/* ���˥��롼�Х�ID����ʣ�����ǽ������ */
typedef struct {
	fstr_gl_rec* nrec;
	fstr_gl_rec* erec;
	int node_n;
	int elem_n;
} fstr_gl_t;


/* ��ʬ����å�����ɹ���( area_n : ʬ���ΰ�ο�) */
struct hecmwST_local_mesh** fstr_get_all_local_mesh( char* name_ID, int* area_n );

/* ��å���κ�� */
void fstr_free_mesh( struct hecmwST_local_mesh** mesh, int area_n );

/* ���ƥå׿���Ĵ�٤�ʥե������¸�ߤ�Ĵ�٤�� */
int fstr_get_step_n( char* name_ID );

/* ���ƥå� step �����ΰ�Υǡ��������� */
fstr_res_info** fstr_get_all_result( char* name_ID, int step, int area_n );

/* ���ƥå� step �����ΰ�Υǡ������礹�� */
struct hecmwST_result_data* fstr_all_result( fstr_gl_t* glt,
	fstr_res_info** res, int* n_node, int* n_elem );

/* result �κ�� */
void fstr_free_result( fstr_res_info** res, int area_n );

/* �ơ��֥� fstr_gl_t �κ��� */
fstr_gl_t* fstr_create_glt( struct hecmwST_local_mesh** mesh, int area_n );

/* ��ե���������ǥơ��֥�κ��� */
fstr_gl_t* fstr_refine_glt( fstr_gl_t* glt, fstr_res_info** res, int area_n );

/* fstr_gl_t �κ�� */
void fstr_free_gl_t( fstr_gl_t* glt );

/* �������Х�ID��å���κ��� */
struct hecmwST_local_mesh* fstr_create_glmesh( fstr_gl_t* glt );

/* �������Х�ID��å���κ�� */
void fstr_free_glmesh( struct hecmwST_local_mesh* mp );
