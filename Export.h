#pragma once
// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� DESIGNERCMD_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// DESIGNERCMD_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef DESIGNERCMD_EXPORTS
#define DESIGNERCMD_API __declspec(dllexport)
#else
#define DESIGNERCMD_API __declspec(dllimport)
#endif

// �����Ǵ� DesignerCMD.dll ������
class DESIGNERCMD_API CDesignerCMD {
public:
	CDesignerCMD(void){}
	// TODO: �ڴ�������ķ�����
};
