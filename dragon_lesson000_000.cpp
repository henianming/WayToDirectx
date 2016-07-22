#include "lesson.h"
#ifdef DRAGON_LESSON000_000

#include <D3dx9math.h>

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow) {
	//-------------------------------------------------------------------------����
	D3DXVECTOR3 l_D3DXVECTOR3_u(1.0f, 0.0f, 0.0f);
	D3DXVECTOR3 l_D3DXVECTOR3_v(0.0f, 1.0f, 0.0f);
	D3DXVECTOR3 l_D3DXVECTOR3_result;
	//�����ӷ�
	l_D3DXVECTOR3_result = l_D3DXVECTOR3_u + l_D3DXVECTOR3_v;
	//�Ƚ�����
	BOOL bSame = (l_D3DXVECTOR3_u == l_D3DXVECTOR3_v);
	//�����ĳ���
	float length1 = D3DXVec3Length(&l_D3DXVECTOR3_result);
	//�����淶��(��result����ת��Ϊ��λ���������normalize����)
	D3DXVECTOR3 *l_D3DXVECTOR3_normalize = new D3DXVECTOR3();
	D3DXVec3Normalize(l_D3DXVECTOR3_normalize, &l_D3DXVECTOR3_result);
	float length2 = D3DXVec3Length(l_D3DXVECTOR3_normalize);
	//����(�Ŵ�)
	D3DXVECTOR3 l_D3DXVECTOR3_shucheng(2.0f * *l_D3DXVECTOR3_normalize);
	//���(��u��v���ǵ�λ��������product1Ϊ��2��λ�����нǵ�����)
	float product1 = D3DXVec3Dot(&l_D3DXVECTOR3_u, &l_D3DXVECTOR3_v);
	//���(�õ���ͬʱ������u��v��ֱ������crosss)
	D3DXVECTOR3 *l_D3DXVECTOR3_cross = new D3DXVECTOR3();
	D3DXVec3Cross(l_D3DXVECTOR3_cross, &l_D3DXVECTOR3_u, &l_D3DXVECTOR3_v);

	//-------------------------------------------------------------------------����
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
	//���ʾ����1�е�1�е�Ԫ��
	l_D3DXMATRIX_c(0, 0) = 5.0f;
	D3DXMATRIX l_D3DXMATRIX_temp1 = l_D3DXMATRIX_a*l_D3DXMATRIX_b;
	//��Ŀ���������Ϊ��λ����
	D3DXMATRIX l_D3DXMATRIX_indentity;
	D3DXMatrixIdentity(&l_D3DXMATRIX_indentity);
	//����ת��
	D3DXMATRIX l_D3DXMATRIX_transpose;
	D3DXMatrixTranspose(&l_D3DXMATRIX_transpose, &l_D3DXMATRIX_a);
	//��������
	D3DXMATRIX l_D3DXMATRIX_inverse;
	D3DXMatrixInverse(&l_D3DXMATRIX_inverse, NULL, &l_D3DXMATRIX_a);
	//����ƽ�ƾ���
	D3DXMATRIX l_D3DXMATRIX_translation;
	D3DXMatrixTranslation(&l_D3DXMATRIX_translation, 10.0f, 10.0f, 10.0f);
	//������ת����
	D3DXMATRIX l_D3DXMATRIX_rotationX;
	D3DXMatrixRotationX(&l_D3DXMATRIX_rotationX, 1);
	D3DXMATRIX l_D3DXMATRIX_rotationY;
	D3DXMatrixRotationY(&l_D3DXMATRIX_rotationY, 1);
	D3DXMATRIX l_D3DXMATRIX_rotationZ;
	D3DXMatrixRotationZ(&l_D3DXMATRIX_rotationZ, 1);
	//�������ž���
	D3DXMATRIX l_D3DXMATRIX_scaling;
	D3DXMatrixScaling(&l_D3DXMATRIX_scaling, 2, 3, 4);

	//-------------------------------------------------------------------------�����ڵ�ı任
	D3DXMATRIX l_D3DXMATRIX_changeMatrix(1.0f, 0.0f, 0.0f, 0.0f,
										 0.0f, 1.0f, 0.0f, 0.0f,
										 0.0f, 0.0f, 1.0f, 0.0f,
										 5.0f, 6.0f, 7.0f, 1.0f);
	D3DXVECTOR3 l_D3DXVECTOR3_changeIn(1, 2, 3);
	//��������������������б任
	D3DXVECTOR3 l_D3DXVECTOR3_changeOutVector;
	D3DXVec3TransformNormal(&l_D3DXVECTOR3_changeOutVector, &l_D3DXVECTOR3_changeIn, &l_D3DXMATRIX_changeMatrix);
	//�õ㰴������������б任
	D3DXVECTOR3 l_D3DXVECTOR3_changeOutDot;
	D3DXVec3TransformCoord(&l_D3DXVECTOR3_changeOutDot, &l_D3DXVECTOR3_changeIn, &l_D3DXMATRIX_changeMatrix);

	//-------------------------------------------------------------------------ƽ��
	//����ƽ��(����1��2��3��������Ϊƽ�淨��������������ģΪ1ʱ������4λԭ�㵽��ƽ�������з��ž���)
	D3DXPLANE l_D3DXPLANE_a(1.0f, 1.0f, 1.0f, 1.0f);
	//����ƽ�棬ͨ������normal��ƽ����һ��point
	D3DXPLANE l_D3DXPLANE_pointNormal;
	D3DXVECTOR3 l_D3DXVECTOR3_point(1.0f, 1.0f, 1.0f);
	D3DXVECTOR3 l_D3DXVECTOR3_normal(1.0f, 1.0f, 1.0f);
	D3DXPlaneFromPointNormal(&l_D3DXPLANE_pointNormal, &l_D3DXVECTOR3_point, &l_D3DXVECTOR3_normal);
	//����ƽ�棬ͨ��3��ƽ���ϵ�ȷ��
	D3DXPLANE l_D3DXPLANE_3dot;
	D3DXVECTOR3 l_D3DXVECTOR3_dot1(1.0f, 0.0f, 0.0f);
	D3DXVECTOR3 l_D3DXVECTOR3_dot2(0.0f, 1.0f, 0.0f);
	D3DXVECTOR3 l_D3DXVECTOR3_dot3(0.0f, 0.0f, 1.0f);
	D3DXPlaneFromPoints(&l_D3DXPLANE_3dot, &l_D3DXVECTOR3_dot1, &l_D3DXVECTOR3_dot2, &l_D3DXVECTOR3_dot3);
	//�������ƽ����з��ž���(��l_D3DXPLANE_aģΪ1ʱ)
	D3DXVECTOR3 l_D3DXVECTOR3_distance(10.0f, 10.0f, 10.0f);
	//�˺�����Ϊ��4άw=1
	float distance_a = D3DXPlaneDotCoord(&l_D3DXPLANE_a, &l_D3DXVECTOR3_distance);
	//�˺�����Ϊ��4άw=0
	float distance_b = D3DXPlaneDotNormal(&l_D3DXPLANE_a, &l_D3DXVECTOR3_distance);
	//�˺�����4άw�ɸ�����4ά��������
	D3DXVECTOR4 l_D3DXVECTOR4_distance(10.0f, 10.0f, 10.0f, 1.0f);
	float dixtance_c = D3DXPlaneDot(&l_D3DXPLANE_a, &l_D3DXVECTOR4_distance);
	//ƽ��淶��
	D3DXPLANE l_D3DXPLANE_normalize;
	D3DXPlaneNormalize(&l_D3DXPLANE_normalize, &l_D3DXPLANE_a);

	//-------------------------------------------------------------------------ƽ��任
	D3DXMATRIX l_D3DXMATRIX_planeMatrixTransform(1.0f, 0.0f, 0.0f, 0.0f,
												 0.0f, 1.0f, 0.0f, 0.0f,
												 0.0f, 0.0f, 1.0f, 0.0f,
												 5.0f, 6.0f, 7.0f, 1.0f);
	D3DXPLANE l_D3DXPLANE_planeMatrixTransform(10.0f, 10.0f, 10.0f, 1.0f);
	//��Ҫ�Ƚ�ƽ����ת�ú�����ƽ���������
	D3DXMATRIX temp;
	D3DXMatrixInverse(&temp, NULL, &l_D3DXMATRIX_planeMatrixTransform);
	D3DXMatrixTranspose(&temp, &temp);
	//��ƽ����б任����
	D3DXPLANE l_D3DXPLANE_planeMatrixTransformOut;
	D3DXPlaneTransform(&l_D3DXPLANE_planeMatrixTransformOut, &l_D3DXPLANE_planeMatrixTransform, &temp);

	while (1);
	return 0;
}

#endif // DRAGON_LESSON000_000