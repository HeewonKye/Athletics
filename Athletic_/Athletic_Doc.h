
// Athletic_Doc.h : CAthletic_Doc Ŭ������ �������̽�
//


#pragma once
#include "Volume.h"
#include "Cpu_VR.h"
#include "Gpu_VR.h"
class CAthletic_Doc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CAthletic_Doc();
	DECLARE_DYNCREATE(CAthletic_Doc)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// �����Դϴ�.
public:
	virtual ~CAthletic_Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnFileOpen();
	
	afx_msg void OnCpuVR();
	afx_msg void OnGpuVR();
	afx_msg void OnGpuVR_AO();

public:
	Cpu_VR m_render_cpu;
	Gpu_VR m_render_gpu;
};
