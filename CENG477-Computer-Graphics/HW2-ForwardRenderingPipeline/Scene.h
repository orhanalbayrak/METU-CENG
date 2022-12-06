#ifndef _SCENE_H_
#define _SCENE_H_

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#include "Camera.h"
#include "Color.h"
#include "Model.h"
#include "Rotation.h"
#include "Scaling.h"
#include "Translation.h"
#include "Triangle.h"
#include "Vec3.h"
#include "Vec4.h"
#include "Matrix4.h"

using namespace std;

class Scene
{
public:
	Color backgroundColor;
	bool cullingEnabled;
	int projectionType;

	vector< vector<Color> > image;
	vector< Camera* > cameras;
	vector< Vec3* > vertices;
	vector< Color* > colorsOfVertices;
	vector< Scaling* > scalings;
	vector< Rotation* > rotations;
	vector< Translation* > translations;
	vector< Model* > models;

	Scene(const char *xmlPath);

	void initializeImage(Camera* camera);
	void forwardRenderingPipeline(Camera* camera);
	int makeBetweenZeroAnd255(double value);
	void writeImageToPPMFile(Camera* camera);
	void convertPPMToPNG(string ppmFileName, int osType);
	
	Matrix4 translation(Matrix4 mtr,int trId);
	Matrix4 rotation(Matrix4 mtr,int rId,Camera *cam);
	Matrix4 scaling(Matrix4 mtr,int sId);
	Vec4 per_divide(Vec4 v);
	Vec3 viewport_tr(double mvp[3][4],Vec4 v);
	void line_raster(Vec3 p0,Vec3 p1,Camera *camera);
	void triangle_raster(Vec3 a,Vec3 b,Vec3 c);
	double f01(double x,double y,Vec3 a,Vec3 b);
	double f12(double x,double y,Vec3 a,Vec3 b);
	double f20(double x,double y,Vec3 a,Vec3 b);
	bool backface(Vec4 v1,Vec4 v2,Vec4 v3,Camera *cam);
};

#endif
