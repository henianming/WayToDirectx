#include "lesson.h"
#ifdef DRAGON_LESSON000_000

#include <D3dx9math.h>

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow) {
	//-------------------------------------------------------------------------向量
	D3DXVECTOR3 l_D3DXVECTOR3_u(1.0f, 0.0f, 0.0f);
	D3DXVECTOR3 l_D3DXVECTOR3_v(0.0f, 1.0f, 0.0f);
	D3DXVECTOR3 l_D3DXVECTOR3_result;
	//向量加法
	l_D3DXVECTOR3_result = l_D3DXVECTOR3_u + l_D3DXVECTOR3_v;
	//比较向量
	BOOL bSame = (l_D3DXVECTOR3_u == l_D3DXVECTOR3_v);
	//向量的长度
	float length1 = D3DXVec3Length(&l_D3DXVECTOR3_result);
	//向量规范化(把result矩阵转换为单位矩阵，输出到normalize矩阵)
	D3DXVECTOR3 *l_D3DXVECTOR3_normalize = new D3DXVECTOR3();
	D3DXVec3Normalize(l_D3DXVECTOR3_normalize, &l_D3DXVECTOR3_result);
	float length2 = D3DXVec3Length(l_D3DXVECTOR3_normalize);
	//数乘(放大)
	D3DXVECTOR3 l_D3DXVECTOR3_shucheng(2.0f * *l_D3DXVECTOR3_normalize);
	//点积(若u和v都是单位向量，则product1为这2单位向量夹角的余弦)
	float product1 = D3DXVec3Dot(&l_D3DXVECTOR3_u, &l_D3DXVECTOR3_v);
	//叉积(得到了同时与向量u和v垂直的向量crosss)
	D3DXVECTOR3 *l_D3DXVECTOR3_cross = new D3DXVECTOR3();
	D3DXVec3Cross(l_D3DXVECTOR3_cross, &l_D3DXVECTOR3_u, &l_D3DXVECTOR3_v);

	//-------------------------------------------------------------------------矩阵
	D3DXMATRIX l_D3DXMATRIX_a(1.0f, 2.0f, 3.0f, 4.0f,
							  1.0f, 2.0f, 3.0f, 4.0f,
							  1.0f, 2.0f, 3.0f, 4.0f,
							  1.0f, 2.0f, 3.0f, 4.0f);
	D3DXMATRIX l_D3DXMATRIX_b(1.0f, 2.0f, 3.0f, 4.0f,
							  1.0f, 2.0f, 3.0f, 4.0f,
							  1.0f, 2.0f, 3.0f, 4.0f,
							  1.0f, 2.0f, 3.0f, 4.0f);
	D3DXMATRIX l_D3DXMATRIX_c(3.0f, 0.0f, 0.0f, 0.0f,
							  0.0f, 3.0f, 0.0f, 0.0f,
							  0.0f, 0.0f, 3.0f, 0.0f,
							  0.0f, 0.0f, 0.0f, 3.0f);
	//访问矩阵第1行第1列的元素
	l_D3DXMATRIX_c(0, 0) = 5.0f;
	D3DXMATRIX l_D3DXMATRIX_temp1 = l_D3DXMATRIX_a*l_D3DXMATRIX_b;
	//将目标矩阵设置为单位矩阵
	D3DXMATRIX l_D3DXMATRIX_indentity;
	D3DXMatrixIdentity(&l_D3DXMATRIX_indentity);
	//矩阵转置
	D3DXMATRIX l_D3DXMATRIX_transpose;
	D3DXMatrixTranspose(&l_D3DXMATRIX_transpose, &l_D3DXMATRIX_a);
	//矩阵求逆
	D3DXMATRIX l_D3DXMATRIX_inverse;
	D3DXMatrixInverse(&l_D3DXMATRIX_inverse, NULL, &l_D3DXMATRIX_a);
	//创建平移矩阵
	D3DXMATRIX l_D3DXMATRIX_translation;
	D3DXMatrixTranslation(&l_D3DXMATRIX_translation, 10.0f, 10.0f, 10.0f);
	//创建旋转矩阵
	D3DXMATRIX l_D3DXMATRIX_rotationX;
	D3DXMatrixRotationX(&l_D3DXMATRIX_rotationX, 1);
	D3DXMATRIX l_D3DXMATRIX_rotationY;
	D3DXMatrixRotationY(&l_D3DXMATRIX_rotationY, 1);
	D3DXMATRIX l_D3DXMATRIX_rotationZ;
	D3DXMatrixRotationZ(&l_D3DXMATRIX_rotationZ, 1);
	//创建缩放矩阵
	D3DXMATRIX l_D3DXMATRIX_scaling;
	D3DXMatrixScaling(&l_D3DXMATRIX_scaling, 2, 3, 4);

	//-------------------------------------------------------------------------向量于点的变换
	D3DXMATRIX l_D3DXMATRIX_changeMatrix(1.0f, 0.0f, 0.0f, 0.0f,
										 0.0f, 1.0f, 0.0f, 0.0f,
										 0.0f, 0.0f, 1.0f, 0.0f,
										 5.0f, 6.0f, 7.0f, 1.0f);
	D3DXVECTOR3 l_D3DXVECTOR3_changeIn(1, 2, 3);
	//让向量按照所给矩阵进行变换
	D3DXVECTOR3 l_D3DXVECTOR3_changeOutVector;
	D3DXVec3TransformNormal(&l_D3DXVECTOR3_changeOutVector, &l_D3DXVECTOR3_changeIn, &l_D3DXMATRIX_changeMatrix);
	//让点按照所给矩阵进行变换
	D3DXVECTOR3 l_D3DXVECTOR3_changeOutDot;
	D3DXVec3TransformCoord(&l_D3DXVECTOR3_changeOutDot, &l_D3DXVECTOR3_changeIn, &l_D3DXMATRIX_changeMatrix);

	//-------------------------------------------------------------------------平面
	//创建平面(参数1，2，3构成向量为平面法向量，若法向量模为1时，参数4位原点到该平面的最短有符号距离)
	D3DXPLANE l_D3DXPLANE_a(1.0f, 1.0f, 1.0f, 1.0f);
	//创建平面，通过法线normal和平面上一点point
	D3DXPLANE l_D3DXPLANE_pointNormal;
	D3DXVECTOR3 l_D3DXVECTOR3_point(1.0f, 1.0f, 1.0f);
	D3DXVECTOR3 l_D3DXVECTOR3_normal(1.0f, 1.0f, 1.0f);
	D3DXPlaneFromPointNormal(&l_D3DXPLANE_pointNormal, &l_D3DXVECTOR3_point, &l_D3DXVECTOR3_normal);
	//创建平面，通过3个平面上点确定
	D3DXPLANE l_D3DXPLANE_3dot;
	D3DXVECTOR3 l_D3DXVECTOR3_dot1(1.0f, 0.0f, 0.0f);
	D3DXVECTOR3 l_D3DXVECTOR3_dot2(0.0f, 1.0f, 0.0f);
	D3DXVECTOR3 l_D3DXVECTOR3_dot3(0.0f, 0.0f, 1.0f);
	D3DXPlaneFromPoints(&l_D3DXPLANE_3dot, &l_D3DXVECTOR3_dot1, &l_D3DXVECTOR3_dot2, &l_D3DXVECTOR3_dot3);
	//计算点于平面的有符号距离(当l_D3DXPLANE_a模为1时)
	D3DXVECTOR3 l_D3DXVECTOR3_distance(10.0f, 10.0f, 10.0f);
	//此函数认为第4维w=1
	float distance_a = D3DXPlaneDotCoord(&l_D3DXPLANE_a, &l_D3DXVECTOR3_distance);
	//此函数认为第4维w=0
	float distance_b = D3DXPlaneDotNormal(&l_D3DXPLANE_a, &l_D3DXVECTOR3_distance);
	//此函数第4维w由给出的4维向量决定
	D3DXVECTOR4 l_D3DXVECTOR4_distance(10.0f, 10.0f, 10.0f, 1.0f);
	float dixtance_c = D3DXPlaneDot(&l_D3DXPLANE_a, &l_D3DXVECTOR4_distance);
	//平面规范化
	D3DXPLANE l_D3DXPLANE_normalize;
	D3DXPlaneNormalize(&l_D3DXPLANE_normalize, &l_D3DXPLANE_a);

	//-------------------------------------------------------------------------平面变换
	D3DXMATRIX l_D3DXMATRIX_planeMatrixTransform(1.0f, 0.0f, 0.0f, 0.0f,
												 0.0f, 1.0f, 0.0f, 0.0f,
												 0.0f, 0.0f, 1.0f, 0.0f,
												 5.0f, 6.0f, 7.0f, 1.0f);
	D3DXPLANE l_D3DXPLANE_planeMatrixTransform(10.0f, 10.0f, 10.0f, 1.0f);
	//需要先将平面逆转置后，再与平面进行运算
	D3DXMATRIX temp;
	D3DXMatrixInverse(&temp, NULL, &l_D3DXMATRIX_planeMatrixTransform);
	D3DXMatrixTranspose(&temp, &temp);
	//与平面进行变换运算
	D3DXPLANE l_D3DXPLANE_planeMatrixTransformOut;
	D3DXPlaneTransform(&l_D3DXPLANE_planeMatrixTransformOut, &l_D3DXPLANE_planeMatrixTransform, &temp);

	while (1);
	return 0;
}

#endif // DRAGON_LESSON000_000