#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <cmath>

#include "Scene.h"
#include "Matrix4.h"
#include "Camera.h"
#include "Color.h"
#include "Model.h"
#include "Rotation.h"
#include "Scaling.h"
#include "Translation.h"
#include "Triangle.h"
#include "Vec3.h"
#include "Vec4.h"
#include "tinyxml2.h"
#include "Helpers.h"
#define PI 3.14159265
using namespace tinyxml2;
using namespace std;

/*
	Transformations, clipping, culling, rasterization are done here.
	You can define helper functions inside Scene class implementation.
*/
void Scene::forwardRenderingPipeline(Camera *camera)
{
	//Orhan Albayrak
	//cout << "cam gaze: " << camera->gaze<<"v: " << camera->v.x << " " << camera->v.y << " " << camera->v.z << endl;
	double mcam_m[4][4] = {{camera->u.x,camera->u.y,camera->u.z,-1*(camera->u.x*camera->pos.x + camera->u.y*camera->pos.y + camera->u.z*camera->pos.z)},
				  {camera->v.x,camera->v.y,camera->v.z,-1*(camera->v.x*camera->pos.x + camera->v.y*camera->pos.y + camera->v.z*camera->pos.z)},
				  {camera->w.x,camera->w.y,camera->w.z,-1*(camera->w.x*camera->pos.x + camera->w.y*camera->pos.y + camera->w.z*camera->pos.z)},
				  {0,0,0,1}};
	Matrix4 mcam(mcam_m); 
	cout<<"mcam matrix in scene \n";
	
	cout<<mcam;
	

	double morth_m[4][4] = {
					{2.0/(camera->right-camera->left),0,0,-1*((camera->right+camera->left)/(camera->right-camera->left))},
				   	{0.0,2.0/(camera->top-camera->bottom),0,-1*(camera->top+camera->bottom)/(camera->top-camera->bottom)},
				   	{0.0,0.0,-2/(camera->far-camera->near),-1*(camera->far+camera->near)/(camera->far-camera->near)},
				   {0.0,0.0,0.0,1.0}};
	Matrix4 morth(morth_m);
	cout<<"\nmorth matrix in scene \n";
	
	cout<<morth;

	double mp2o_m[4][4] = {{camera->near,0,0,0},
				  {0,camera->near,0,0},
				  {0,0,camera->far+camera->near,camera->far*camera->near},
				  {0,0,-1,0}};
	Matrix4 mp2o(mp2o_m); // Matrix4 m = *(new Matrix4(arr));
	cout<<"\nmp2o matrix in scene \n";
	
	cout<<mp2o;

	Matrix4 mprj;
	
	if(projectionType == 1){
		mprj=multiplyMatrixWithMatrix(morth,mp2o);	
	} else {
		mprj = morth;
	}	

	cout<<"\nmprj matrix in scene \n";
	
	cout<<mprj;

	double mvp[3][4] = {{camera->horRes/2.0,0,0,(camera->horRes-1)/2.0},
				   {0,(camera->verRes)/2.0,0,(camera->verRes-1)/2.0},
				   {0,0,1/2,1/2}};


	int modelsize = models.size();
	//for every triangle in every object
	for(int i=0; i<modelsize; i++){
		for(int j=0; j<models[i]->numberOfTriangles; j++){
			Vec3 res;
			Triangle t = models[i]->triangles[j];

			Vec3 a = *vertices[t.getFirstVertexId()-1];
			Vec3 b = *vertices[t.getSecondVertexId()-1];
			Vec3 c = *vertices[t.getThirdVertexId()-1];

			//printVec3(a);
			//printVec3(b);
			//printVec3(c);

			Vec4 a1 = *(new Vec4(a.x, a.y, a.z, 1, a.colorId));
			Vec4 b1 = *(new Vec4(b.x, b.y, b.z, 1, b.colorId));
			Vec4 c1 = *(new Vec4(c.x, c.y, c.z, 1, c.colorId));
			double unit[4][4] = {{1,0,0,0},
								 {0,1,0,0},
								 {0,0,1,0},
								 {0,0,0,1.0}};
			Matrix4 mtransfom(unit);
			// apply transformations
			for(int k=0; k <models[i]->numberOfTransformations; k++){ 
				if (models[i]->transformationTypes[k] == 't')
				{
					mtransfom = translation(mtransfom,models[i]->transformationIds[k]);
				}else if (models[i]->transformationTypes[k] == 'r')
				{
					mtransfom = rotation(mtransfom,models[i]->transformationIds[k],camera);
				} else{
					mtransfom = scaling(mtransfom,models[i]->transformationIds[k]);
				}
			}
			//apply modeling transform
			a1 = multiplyMatrixWithVec4(mtransfom,a1);
			b1 = multiplyMatrixWithVec4(mtransfom,b1);
			c1 = multiplyMatrixWithVec4(mtransfom,c1);
			if(cullingEnabled == 1 && backface(a1,b1,c1,camera)){
				continue;
			}
			

			cout << "After modeling a1: "<< a1 << "\nb1: "<< b1 << "\nc1: " << c1 << endl;

			// apply camera transfomation
			a1 = multiplyMatrixWithVec4(mcam,a1);
			b1 = multiplyMatrixWithVec4(mcam,b1);	
			c1 = multiplyMatrixWithVec4(mcam,c1);

			cout << "After cam transf a1: "<< a1 << "\nb1: "<< b1 << "\nc1: " << c1 << endl;

			// perspective projection
			a1 = multiplyMatrixWithVec4(mprj,a1);
			b1 = multiplyMatrixWithVec4(mprj,b1);
			c1 = multiplyMatrixWithVec4(mprj,c1);

			cout << "\nAFTER mprj a1: " << a1 << endl;
			cout << "\nAFTER mprj b1: " << b1 << endl;
			cout << "\nAFTER mprj c1: " << c1 << endl;

			// apply perspective divide
			a1 = per_divide(a1);
			b1 = per_divide(b1);
			c1 = per_divide(c1);
			cout << "colorid: "<< a1.colorId << endl;
			cout << "\na1: " << a1 << endl;
			cout << "\nb1: " << b1 << endl;
			cout << "\nc1: " << c1 << endl;
			// apply viewport transformation
			// a1 = mvp*a1
			Vec3 a_1 = viewport_tr(mvp,a1);
			Vec3 b_1 = viewport_tr(mvp,b1);
			Vec3 c_1 = viewport_tr(mvp,c1);

			cout << "\nimage vert res: " << camera->verRes << " hor res " << camera->horRes << endl;
			
			cout << a_1.colorId << endl;
			cout << "\na_1: " << a_1 << " " << *colorsOfVertices[a_1.colorId-1] << endl;
			cout << "\nb_1: " << b_1 << " " << *colorsOfVertices[b_1.colorId-1] << endl;
			cout << "\nc_1: " << c_1 << " " << *colorsOfVertices[c_1.colorId-1] << endl;
			
			 //image[x-1][y-1].r = colorsOfVertices[p_0.colorId-1]->r
			
			

			cout << "hello4" << endl;

			if(models[i]->type == 1){
				triangle_raster(a_1,b_1,c_1);
			}else {
				line_raster(a_1,b_1,camera);
				line_raster(a_1,c_1,camera);
				line_raster(b_1,c_1,camera);
			}
			if(a_1.x>=0 && a_1.x<camera->horRes && a_1.y >=0 && a_1.y<=camera->verRes){
				this->image[a_1.x][a_1.y] = *colorsOfVertices[a_1.colorId-1];
			}	
			if(b_1.x>=0 && b_1.x<camera->horRes && b_1.y >=0 && b_1.y<=camera->verRes){
				this->image[b_1.x][b_1.y] = *colorsOfVertices[b_1.colorId-1];
			}
			if(c_1.x>=0 && c_1.x<camera->horRes && c_1.y >=0 && c_1.y<=camera->verRes){	
				this->image[c_1.x][c_1.y] = *colorsOfVertices[c_1.colorId-1];
			}
		}
	}

	// TODO: Implement this function.
}

//returns true if to be culled
bool Scene::backface(Vec4 v1,Vec4 v2,Vec4 v3,Camera *cam){
	//find tr center
	Vec3 tr_center((v1.x+v2.x+v3.x)/3.0,(v1.y+v2.y+v3.y)/3.0,(v1.z+v2.z+v3.z)/3.0,0);
	//subtract center from cam.pos
	Vec3 v(tr_center.x-cam->pos.x,tr_center.y-cam->pos.y,tr_center.z-cam->pos.z,0);
	//Find triangle normal
	Vec3 _v1(v1.x,v1.y,v1.z,0);
	Vec3 _v2(v2.x,v2.y,v2.z,0);
	Vec3 _v3(v3.x,v3.y,v3.z,0);

	Vec3 tr_normal = normalizeVec3(crossProductVec3(subtractVec3(_v2,_v1),subtractVec3(_v3,_v2)));
	
	//dot prd | if cond.
	if(dotProductVec3(tr_normal,v) < 0){
		return false;
	}else {
		return true;
	}
}
//used in triangle rasterization
double Scene::f01(double x,double y,Vec3 a,Vec3 b){
	return x*(a.y - b.y) + y*(b.x - a.x) + a.x*b.y - a.y*b.x;
}
double Scene::f12(double x,double y,Vec3 b,Vec3 c){
	return x*(b.y - c.y) + y*(c.x - b.x) + b.x*c.y - b.y*c.x;
}
double Scene::f20(double x,double y,Vec3 a,Vec3 c){
	return x*(c.y - a.y) + y*(a.x - c.x) + c.x*a.y - c.y*a.x;
}


void Scene::triangle_raster(Vec3 a,Vec3 b,Vec3 c){
	double ymin,ymax,xmin,xmax;
	Color c0 = *colorsOfVertices[a.colorId-1], c1 = *colorsOfVertices[b.colorId-1], c2 = *colorsOfVertices[c.colorId-1];
	if(a.y <= b.y && a.y < c.y){
		ymin = a.y;
	} else if(b.y < a.y && b.y < c.y){
		ymin = b.y; 
	} else {
		ymin = c.y;
	}

	if(a.y >= b.y && a.y > c.y){
		ymax = a.y;
	} else if(b.y > a.y && b.y > c.y){
		ymax = b.y; 
	} else {
		ymax = c.y;
	}

	if(a.x <= b.x && a.x < c.x){
		xmin = a.x;
	} else if(b.x < a.x && b.x < c.x){
		xmin = b.x; 
	} else {
		xmin = c.x;
	}

	if(a.x >= b.x && a.x > c.x){
		xmax = a.x;
	} else if(b.x > a.x && b.x > c.x){
		xmax = b.x; 
	} else {
		xmax = c.x;
	}

	for(int y = ymin; y < ymax; y++){
		for(int x = xmin; x < xmax; x++){
			double alpha,beta,gamma;
			alpha = f12(x,y,b,c)/f12(a.x,a.y,b,c);
			beta = f20(x,y,a,c)/f20(b.x,b.y,a,c);
			gamma = f01(x,y,a,b)/f01(c.x,c.y,a,b);
			if(alpha >= 0 && beta >= 0 && gamma >= 0){
				//c0.r,c0.g,c0.b;
				
				this->image[x][y].r = alpha*c0.r + beta*c1.r + gamma*c2.r;
				this->image[x][y].g = alpha*c0.g + beta*c1.g + gamma*c2.g;
				this->image[x][y].b = alpha*c0.b + beta*c1.b + gamma*c2.b;
			}
		}
	}
}

void Scene::line_raster(Vec3 p0,Vec3 p1,Camera *camera){
	double x0 =  p0.x, y0 = p0.y;
	double x1 =  p1.x, y1 = p1.y;
	Color c0 = *colorsOfVertices[p0.colorId-1];
	Color c1 = *colorsOfVertices[p1.colorId-1];

	double m = (y1 - y0)/(x1 -x0);

	if(m >= 0 && m <= 1){
		if(x1 >= x0){ //1. octant
			double y = y0;
			double d = 2*(y0-y1) + (x1-x0);
			for(int x = x0; x <= x1; x++){
				if(x>=0 && x<camera->horRes && y >=0 && y<=camera->verRes){
					double alpha = (x-x0) / (x1-x0);
					this->image[x][y].r = (1-alpha)*c0.r + alpha*c1.r;
					this->image[x][y].g = (1-alpha)*c0.g + alpha*c1.g;
					this->image[x][y].b = (1-alpha)*c0.b + alpha*c1.b;
					if(d < 0){ // NE
						y = y+1;
						d += 2*((y0-y1) + (x1-x0));
					} else {
						d += 2*(y0-y1);
					}
				}//abc
			}
		}
		else { //5. octant
			double y = y1;
			double d = 2*(y1-y0) + (x0-x1);
			for(int x = x1; x <= x0; x++){
				if(x>=0 && x<camera->horRes && y >=0 && y<=camera->verRes){
					double alpha = (x-x0) / (x1-x0);
					this->image[x][y].r = (1-alpha)*c0.r + alpha*c1.r;
					this->image[x][y].g = (1-alpha)*c0.g + alpha*c1.g;
					this->image[x][y].b = (1-alpha)*c0.b + alpha*c1.b;
					if(d < 0){ // NE
						y = y+1;
						d += 2*((y1-y0) + (x0-x1));
					} else {
						d += 2*(y1-y0);
					}
				}//abc
			}
		}
	}
	else if(m > 1){	
		if(y1 >= y0){	
			double x = x0;	 
			double d = 2*(x0-x1) + (y1-y0);
			
			for(int y = y0; y <= y1; y++){
				if(x>=0 && x<camera->horRes && y >=0 && y<=camera->verRes){
					double alpha = (y-y0) / (y1-y0);
					this->image[x][y].r = (1-alpha)*c0.r + alpha*c1.r;
					this->image[x][y].g = (1-alpha)*c0.g + alpha*c1.g;
					this->image[x][y].b = (1-alpha)*c0.b + alpha*c1.b;
					if(d < 0){ // NE
						x = x+1;
						d += 2*((x0-x1) + (y1-y0));
					} else {
						d += 2*(x0-x1);
					}
				}//abc
			}
		}else { // 6. octant
			double x = x1;
			double d = 2*(x1-x0) + (y0-y1);
			
			for(int y = y1; y <= y0; y++){
				if(x>=0 && x<camera->horRes && y >=0 && y<=camera->verRes){
					double alpha = (y-y0) / (y1-y0);
					this->image[x][y].r = (1-alpha)*c0.r + alpha*c1.r;
					this->image[x][y].g = (1-alpha)*c0.g + alpha*c1.g;
					this->image[x][y].b = (1-alpha)*c0.b + alpha*c1.b;
					if(d < 0){ // NE
						x = x+1;
						d += 2*((x1-x0) + (y0-y1));
					} else {
						d += 2*(x1-x0);
					}
				}//abc
			}
		}
	}
	else if(m <= 0 && m >= -1){
		if(x0 <= x1){ //4. octant
			double y = y0;
			double d = 2*(y1-y0) + (x1-x0);
			
			for(int x = x0; x <= x1; x++){
				if(x>=0 && x<camera->horRes && y >=0 && y<=camera->verRes){
					double alpha = (y-y0) / (y1-y0);
					this->image[x][y].r = (1-alpha)*c0.r + alpha*c1.r;
					this->image[x][y].g = (1-alpha)*c0.g + alpha*c1.g;
					this->image[x][y].b = (1-alpha)*c0.b + alpha*c1.b;
					if(d < 0){ // NE
						y = y-1;
						d += 2*((y1-y0) + (x1-x0));
					} else {
						d += 2*(y1-y0);
					}
				}//abc
			}
		}else { // 8. octant
			double y = y1;
			double d = 2*(y0-y1) + (x0-x1);
			for(int x = x1; x <= x0; x++){
				if(x>=0 && x<camera->horRes && y >=0 && y<=camera->verRes){
					double alpha = (x-x0) / (x1-x0);
					this->image[x][y].r = (1-alpha)*c0.r + alpha*c1.r;
					this->image[x][y].g = (1-alpha)*c0.g + alpha*c1.g;
					this->image[x][y].b = (1-alpha)*c0.b + alpha*c1.b;

					if(d < 0){ // NE
						y = y-1;
						d += 2*((y0-y1) + (x0-x1));
					} else {
						d += 2*(y0-y1);
					}
				}//abc
			}
		}
	}
	else if(m < -1){
		if(y1 >= y0){ //3. octant
			double x = x0;
			double d = 2*(x1-x0) + (y1-y0);
			
			for(int y = y0; y <= y1; y++){
				if(x>=0 && x<camera->horRes && y >=0 && y<=camera->verRes){
					double alpha = (y-y0) / (y1-y0);
					this->image[x][y].r = (1-alpha)*c0.r + alpha*c1.r;
					this->image[x][y].g = (1-alpha)*c0.g + alpha*c1.g;
					this->image[x][y].b = (1-alpha)*c0.b + alpha*c1.b;
					if(d < 0){ // NE
						x = x-1;
						d += 2*((x1-x0) + (y1-y0));
					} else {
						d += 2*(x1-x0);
					}
				}//abc
			}
		}else { // 7. octant
			double x = x1;
			double d = 2*(x0-x1) + (y0-y1);
			
			for(int y = y1; y <= y0; y++){
				if(x>=0 && x<camera->horRes && y >=0 && y<=camera->verRes){
					double alpha = (y-y0) / (y1-y0);
					this->image[x][y].r = (1-alpha)*c0.r + alpha*c1.r;
					this->image[x][y].g = (1-alpha)*c0.g + alpha*c1.g;
					this->image[x][y].b = (1-alpha)*c0.b + alpha*c1.b;
					if(d < 0){ // NE
						x = x-1;
						d += 2*((x0-x1) + (y0-y1));
					} else {
						d += 2*(x0-x1);
					}
				}//abc
			}
		}
	}
}



Vec3 Scene::viewport_tr(double mvp[3][4],Vec4 v){
	double values[3];
    double total;

    for (int i = 0; i < 3; i++)
    {
        total = 0;
        for (int j = 0; j < 4; j++)
        {
            total += mvp[i][j] * v.getElementAt(j);
        }
        values[i] = total;
    }
			cout << "aaa: "<< endl;

    return Vec3(values[0], values[1], values[2], v.colorId);
}

Vec4 Scene::per_divide(Vec4 v){
	Vec4 a;
	double t = v.t;
	a.x = v.x/t;
    a.y = v.y/t;
    a.z = v.z/t;
    a.t = 1;
	a.colorId = v.colorId;
	cout << "v becomes: " << a << endl;
	return a;
}

Matrix4 Scene::translation(Matrix4 mtr,int trId){
	cout << "\nInside translation, mtr is: " << mtr << " incoming trid: " << trId << endl;
	
	Translation t = *translations[trId-1];
	double tx = t.tx;
	double ty = t.ty;
	double tz = t.tz;
	double tr_m[4][4] = {{1,0,0,tx},{0,1,0,ty},{0,0,1,tz},{0,0,0,1}};
	Matrix4 tr_matrix(tr_m);
	cout << "\ntr_matrix is: " << tr_matrix << endl;
	return multiplyMatrixWithMatrix(tr_matrix,mtr);
}

Matrix4 Scene::rotation(Matrix4 mtr,int rId,Camera *cam){
	cout << "\nInside rotation, mtr is: " << mtr<< " incoming rid: " << rId  << endl;

	Rotation r = *rotations[rId-1];
	
	double ux = r.ux,uy = r.uy,uz = r.uz,vx,vy,vz,wx,wy,wz;
	Vec3 uu,vv;
	if(abs(ux) <= abs(uy) && abs(ux) < abs(uz)){
		vx = 0; vy = -1*uz; vz = uy;
		uu.x= ux;uu.y = uy;uu.z = uz;uu.colorId = 1;
		vv.x= vx;vv.y = vy;vv.z = vz;vv.colorId = 1;

	} else if(abs(uy) <= abs(uz) && abs(uy) < abs(ux)){
		vy = 0; vx = -1*uz; vz = ux;

		uu.x= ux;uu.y = uy;uu.z = uz;uu.colorId = 1;
		vv.x= vx;vv.y = vy;vv.z = vz;vv.colorId = 1;

	} else {
		vz = 0; vx = -1*uy; vy = ux;

		uu.x= ux;uu.y = uy;uu.z = uz;uu.colorId = 1;
		vv.x= vx;vv.y = vy;vv.z = vz;vv.colorId = 1;
	}

	Vec3 ww = crossProductVec3(uu,vv);

	uu = normalizeVec3(uu);
	vv = normalizeVec3(vv);
	ww = normalizeVec3(ww);

	ux = uu.x; uy = uu.y; uz = uu.z;
	vx = vv.x; vy = vv.y; vz = vv.z;
	wx = ww.x; wy = ww.y; wz = ww.z;

	double angle = r.angle*PI/180.0;
	
	double m[4][4] = {{ux,uy,uz,0},{vx,vy,vz,0},{wx,wy,wz,0},{0,0,0,1}};
	double m_1[4][4] = {{ux,vx,wx,0},{uy,vy,wy,0},{uz,vz,wz,0},{0,0,0,1}}; //inverse of m
	double R_x[4][4] = {{1,0,0,0},{0,cos(angle),-1*sin(angle),0},{0,sin(angle),cos(angle),0},{0,0,0,1}};

	Matrix4 m_matrix(m);
	cout << "m is: " << m_matrix<< endl;
	Matrix4 m_1_matrix(m_1);
	cout << "m_1_matrix: " << m_1_matrix<< endl;

	Matrix4 R_x_matrix(R_x);
	cout << "R_x_matrix: " << R_x_matrix<< endl;

	Matrix4 mm = multiplyMatrixWithMatrix(m_1_matrix,multiplyMatrixWithMatrix(R_x_matrix,m_matrix));
	cout << "\nmm is: " << mm << endl;

	return multiplyMatrixWithMatrix(mm,mtr);
}

Matrix4 Scene::scaling(Matrix4 mtr,int sId){
	cout << "\nInside scaling, mtr is: " << mtr << " incoming sid: " << sId << endl;
	
	Scaling s = *scalings[sId-1];
	double sx = s.sx;
	double sy = s.sy;
	double sz = s.sz;
	cout << "sx: " << sx << "sy: " << sy << "sz: " << sz;
	double s_m[4][4] = {{sx,0,0,0},{0,sy,0,0},{0,0,sz,0},{0,0,0,1}};
	Matrix4 s_matrix(s_m);
	cout << "\ns_matrix is: " << s_matrix << endl;

	return multiplyMatrixWithMatrix(s_matrix,mtr);
}



/*
	Parses XML file
*/
Scene::Scene(const char *xmlPath)
{
	const char *str;
	XMLDocument xmlDoc;
	XMLElement *pElement;

	xmlDoc.LoadFile(xmlPath);

	XMLNode *pRoot = xmlDoc.FirstChild();

	// read background color
	pElement = pRoot->FirstChildElement("BackgroundColor");
	str = pElement->GetText();
	sscanf(str, "%lf %lf %lf", &backgroundColor.r, &backgroundColor.g, &backgroundColor.b);

	// read culling
	pElement = pRoot->FirstChildElement("Culling");
	if (pElement != NULL)
		pElement->QueryBoolText(&cullingEnabled);

	// read projection type
	pElement = pRoot->FirstChildElement("ProjectionType");
	if (pElement != NULL)
		pElement->QueryIntText(&projectionType);

	// read cameras
	pElement = pRoot->FirstChildElement("Cameras");
	XMLElement *pCamera = pElement->FirstChildElement("Camera");
	XMLElement *camElement;
	while (pCamera != NULL)
	{
		Camera *cam = new Camera();

		pCamera->QueryIntAttribute("id", &cam->cameraId);

		camElement = pCamera->FirstChildElement("Position");
		str = camElement->GetText();
		sscanf(str, "%lf %lf %lf", &cam->pos.x, &cam->pos.y, &cam->pos.z);

		camElement = pCamera->FirstChildElement("Gaze");
		str = camElement->GetText();
		sscanf(str, "%lf %lf %lf", &cam->gaze.x, &cam->gaze.y, &cam->gaze.z);

		camElement = pCamera->FirstChildElement("Up");
		str = camElement->GetText();
		sscanf(str, "%lf %lf %lf", &cam->v.x, &cam->v.y, &cam->v.z);

		cam->gaze = normalizeVec3(cam->gaze);
		cam->u = crossProductVec3(cam->gaze, cam->v);
		cam->u = normalizeVec3(cam->u);

		cam->w = inverseVec3(cam->gaze);
		cam->v = crossProductVec3(cam->u, cam->gaze);
		cam->v = normalizeVec3(cam->v);

		camElement = pCamera->FirstChildElement("ImagePlane");
		str = camElement->GetText();
		sscanf(str, "%lf %lf %lf %lf %lf %lf %d %d",
			   &cam->left, &cam->right, &cam->bottom, &cam->top,
			   &cam->near, &cam->far, &cam->horRes, &cam->verRes);

		camElement = pCamera->FirstChildElement("OutputName");
		str = camElement->GetText();
		cam->outputFileName = string(str);

		cameras.push_back(cam);

		pCamera = pCamera->NextSiblingElement("Camera");
	}

	// read vertices
	pElement = pRoot->FirstChildElement("Vertices");
	XMLElement *pVertex = pElement->FirstChildElement("Vertex");
	int vertexId = 1;

	while (pVertex != NULL)
	{
		Vec3 *vertex = new Vec3();
		Color *color = new Color();

		vertex->colorId = vertexId;

		str = pVertex->Attribute("position");
		sscanf(str, "%lf %lf %lf", &vertex->x, &vertex->y, &vertex->z);

		str = pVertex->Attribute("color");
		sscanf(str, "%lf %lf %lf", &color->r, &color->g, &color->b);

		vertices.push_back(vertex);
		colorsOfVertices.push_back(color);

		pVertex = pVertex->NextSiblingElement("Vertex");

		vertexId++;
	}

	// read translations
	pElement = pRoot->FirstChildElement("Translations");
	XMLElement *pTranslation = pElement->FirstChildElement("Translation");
	while (pTranslation != NULL)
	{
		Translation *translation = new Translation();

		pTranslation->QueryIntAttribute("id", &translation->translationId);

		str = pTranslation->Attribute("value");
		sscanf(str, "%lf %lf %lf", &translation->tx, &translation->ty, &translation->tz);

		translations.push_back(translation);

		pTranslation = pTranslation->NextSiblingElement("Translation");
	}

	// read scalings
	pElement = pRoot->FirstChildElement("Scalings");
	XMLElement *pScaling = pElement->FirstChildElement("Scaling");
	while (pScaling != NULL)
	{
		Scaling *scaling = new Scaling();

		pScaling->QueryIntAttribute("id", &scaling->scalingId);
		str = pScaling->Attribute("value");
		sscanf(str, "%lf %lf %lf", &scaling->sx, &scaling->sy, &scaling->sz);

		scalings.push_back(scaling);

		pScaling = pScaling->NextSiblingElement("Scaling");
	}

	// read rotations
	pElement = pRoot->FirstChildElement("Rotations");
	XMLElement *pRotation = pElement->FirstChildElement("Rotation");
	while (pRotation != NULL)
	{
		Rotation *rotation = new Rotation();

		pRotation->QueryIntAttribute("id", &rotation->rotationId);
		str = pRotation->Attribute("value");
		sscanf(str, "%lf %lf %lf %lf", &rotation->angle, &rotation->ux, &rotation->uy, &rotation->uz);

		rotations.push_back(rotation);

		pRotation = pRotation->NextSiblingElement("Rotation");
	}

	// read models
	pElement = pRoot->FirstChildElement("Models");

	XMLElement *pModel = pElement->FirstChildElement("Model");
	XMLElement *modelElement;
	while (pModel != NULL)
	{
		Model *model = new Model();

		pModel->QueryIntAttribute("id", &model->modelId);
		pModel->QueryIntAttribute("type", &model->type);

		// read model transformations
		XMLElement *pTransformations = pModel->FirstChildElement("Transformations");
		XMLElement *pTransformation = pTransformations->FirstChildElement("Transformation");

		pTransformations->QueryIntAttribute("count", &model->numberOfTransformations);

		while (pTransformation != NULL)
		{
			char transformationType;
			int transformationId;

			str = pTransformation->GetText();
			sscanf(str, "%c %d", &transformationType, &transformationId);

			model->transformationTypes.push_back(transformationType);
			model->transformationIds.push_back(transformationId);

			pTransformation = pTransformation->NextSiblingElement("Transformation");
		}

		// read model triangles
		XMLElement *pTriangles = pModel->FirstChildElement("Triangles");
		XMLElement *pTriangle = pTriangles->FirstChildElement("Triangle");

		pTriangles->QueryIntAttribute("count", &model->numberOfTriangles);

		while (pTriangle != NULL)
		{
			int v1, v2, v3;

			str = pTriangle->GetText();
			sscanf(str, "%d %d %d", &v1, &v2, &v3);

			model->triangles.push_back(Triangle(v1, v2, v3));

			pTriangle = pTriangle->NextSiblingElement("Triangle");
		}

		models.push_back(model);

		pModel = pModel->NextSiblingElement("Model");
	}
}

/*
	Initializes image with background color
*/
void Scene::initializeImage(Camera *camera)
{
	if (this->image.empty())
	{
		for (int i = 0; i < camera->horRes; i++)
		{
			vector<Color> rowOfColors;

			for (int j = 0; j < camera->verRes; j++)
			{
				rowOfColors.push_back(this->backgroundColor);
			}

			this->image.push_back(rowOfColors);
		}
	}
	// if image is filled before, just change color rgb values with the background color
	else
	{
		for (int i = 0; i < camera->horRes; i++)
		{
			for (int j = 0; j < camera->verRes; j++)
			{
				this->image[i][j].r = this->backgroundColor.r;
				this->image[i][j].g = this->backgroundColor.g;
				this->image[i][j].b = this->backgroundColor.b;
			}
		}
	}
}

/*
	If given value is less than 0, converts value to 0.
	If given value is more than 255, converts value to 255.
	Otherwise returns value itself.
*/
int Scene::makeBetweenZeroAnd255(double value)
{
	if (value >= 255.0)
		return 255;
	if (value <= 0.0)
		return 0;
	return (int)(value);
}

/*
	Writes contents of image (Color**) into a PPM file.
*/
void Scene::writeImageToPPMFile(Camera *camera)
{
	ofstream fout;

	fout.open(camera->outputFileName.c_str());

	fout << "P3" << endl;
	fout << "# " << camera->outputFileName << endl;
	fout << camera->horRes << " " << camera->verRes << endl;
	fout << "255" << endl;

	for (int j = camera->verRes - 1; j >= 0; j--)
	{
		for (int i = 0; i < camera->horRes; i++)
		{
			fout << makeBetweenZeroAnd255(this->image[i][j].r) << " "
				 << makeBetweenZeroAnd255(this->image[i][j].g) << " "
				 << makeBetweenZeroAnd255(this->image[i][j].b) << " ";
		}
		fout << endl;
	}
	fout.close();
}

/*
	Converts PPM image in given path to PNG file, by calling ImageMagick's 'convert' command.
	os_type == 1 		-> Ubuntu
	os_type == 2 		-> Windows
	os_type == other	-> No conversion
*/
void Scene::convertPPMToPNG(string ppmFileName, int osType)
{
	string command;

	// call command on Ubuntu
	if (osType == 1)
	{
		command = "convert " + ppmFileName + " " + ppmFileName + ".png";
		system(command.c_str());
	}

	// call command on Windows
	else if (osType == 2)
	{
		command = "magick convert " + ppmFileName + " " + ppmFileName + ".png";
		system(command.c_str());
	}

	// default action - don't do conversion
	else
	{
	}
}