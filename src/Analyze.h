/*
 *  Analyze.h
 *
 *  Created by rOBERTO tORO on 06/04/2006.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef __Analyze__
#define __Analyze__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define UNKNOWN	0
#define	BINARY	1
#define UCHAR	2
#define SHORT	4
#define	INT		8
#define FLOAT	16
#define COMPLEX	32
#define	DOUBLE	64
#define RGB		128
#define ALL		255

#define RGBFLOAT	144	// added for DTI volumes

typedef struct
{
    // header key
	int		sizeof_hdr		__attribute__((packed));	// used to detect endianness (348 coded as {0,0,1,92}, i.e., Motorola style)
	char	data_type[10];//	__attribute__((packed));
    char	db_name[18];//		__attribute__((packed));
	int		extents			__attribute__((packed));
	short	session_error	__attribute__((packed));
	char	regular;//		__attribute__((packed));
	char	hkey_un0;//		__attribute__((packed));
	
	// image dimension
	short	dim[8]			__attribute__((packed));
	short	unused[7]		__attribute__((packed));
	short	datatype		__attribute__((packed));
	short	bitpix			__attribute__((packed));
	short	dim_un0			__attribute__((packed));
	float	pixdim[8]		__attribute__((packed));
	float	vox_offset		__attribute__((packed));
	float	funused[3]		__attribute__((packed));
	float	cal_max			__attribute__((packed));
	float	cal_min			__attribute__((packed));
	float	compressed		__attribute__((packed));
	float	verified		__attribute__((packed));
	int		glmax			__attribute__((packed));
	int		glmin			__attribute__((packed));
	
	// data history
	char	descrip[80];//		__attribute__((packed));
	char	aux_file[24];//	__attribute__((packed));
	char	orient;//			__attribute__((packed));
	
	//char	originator[10]; // originator is used to store the volume origin
	short	orig[3]			__attribute__((packed));
	char	originator[4];//	__attribute__((packed));

	char	generated[10];//	__attribute__((packed));
	char	scannum[10];//		__attribute__((packed));
	char	patient_id[10];//	__attribute__((packed));
	char	exp_date[10];//	__attribute__((packed));
	char	exp_time[10];//	__attribute__((packed));
	char	hist_un0[3];//		__attribute__((packed));
	int		views			__attribute__((packed));
	int		vols_added		__attribute__((packed));
	int		start_field		__attribute__((packed));
	int		field_skip		__attribute__((packed));
	int		omax			__attribute__((packed));
	int		omin			__attribute__((packed));
	int		smax			__attribute__((packed));
	int		smin			__attribute__((packed));
}AnalyzeHeader;

typedef struct
{
	unsigned char	r,g,b;
}RGBValue;

typedef struct
{
	float	x,y,z;
}rgb;

int Analyze_load(char *path, char **addr,int *sz, int *swapped);
int Analyze_load_hdr(char *path, AnalyzeHeader *hdr, int *swapped);
int Analyze_load_img(char *path, AnalyzeHeader hdr, char *img);
int Analyze_save_hdr(char *path, AnalyzeHeader hdr);
int Analyze_save_img(char *path, AnalyzeHeader hdr, char *img);

int AnalyzeBytesPerVoxel(AnalyzeHeader hdr);
void swap_hdr(AnalyzeHeader *hdr);
void swap_img(char *img, AnalyzeHeader hdr);
void swap_short(short *v);
void swap_int(int *v);
void swap_float(float *v);
void swap_rgbfloat(rgb *v);

float getValue(AnalyzeHeader *hdr, char *addr, int x, int y, int z);
void setValue(AnalyzeHeader *hdr, char *addr, float val, int x, int y, int z);

#endif