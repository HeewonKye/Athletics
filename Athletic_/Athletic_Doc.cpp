
// Athletic_Doc.cpp : CAthletic_Doc Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "Athletic_.h"
#endif

#include "Athletic_Doc.h"
#include "Athletic_View.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include <propkey.h>

#include "vtkDICOMImageReader.h"
#include "vtkSmartPointer.h"
#include "vtkImageData.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAthletic_Doc

IMPLEMENT_DYNCREATE(CAthletic_Doc, CDocument)

BEGIN_MESSAGE_MAP(CAthletic_Doc, CDocument)
	ON_COMMAND(ID_FILE_OPEN, &CAthletic_Doc::OnFileOpen)
	ON_COMMAND(ID_CPU_VR, &CAthletic_Doc::OnCpuVR)
	ON_COMMAND(ID_GPU_VR, &CAthletic_Doc::OnGpuVR)
	ON_COMMAND(ID_GPU_AO, &CAthletic_Doc::OnGpuVR_AO)
END_MESSAGE_MAP()


// CAthletic_Doc ����/�Ҹ�

CAthletic_Doc::CAthletic_Doc()
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.
	m_render_cpu= Cpu_VR();
	m_render_gpu= Gpu_VR();

}

CAthletic_Doc::~CAthletic_Doc()
{
}

BOOL CAthletic_Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.

	return TRUE;
}




// CAthletic_Doc serialization

void CAthletic_Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
	}
}

#ifdef SHARED_HANDLERS

// ����� �׸��� �����մϴ�.
void CAthletic_Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// ������ �����͸� �׸����� �� �ڵ带 �����Ͻʽÿ�.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// �˻� ó���⸦ �����մϴ�.
void CAthletic_Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// ������ �����Ϳ��� �˻� �������� �����մϴ�.
	// ������ �κ��� ";"�� ���еǾ�� �մϴ�.

	// ��: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CAthletic_Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CAthletic_Doc ����

#ifdef _DEBUG
void CAthletic_Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CAthletic_Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CAthletic_Doc ���

static int CALLBACK BrowseCallbackProc( HWND hWnd, UINT uMsg, LPARAM lParam,
										LPARAM lpData )
{
	switch( uMsg )
	{
	case BFFM_INITIALIZED:		// ���� ���� ��ȭ���ڸ� �ʱ�ȭ �� ��, �ʱ� ��� ����
		{
			::SendMessage( hWnd, BFFM_SETSELECTION, TRUE, (LPARAM)lpData );
		}
		break;

	// BROWSEINFO ����ü�� ulFlags ���� BIF_STATUSTEXT �� ������ ��� ȣ��
	// ��, BIF_NEWDIALOGSTYLE �� �����Ǿ� ���� ��� ȣ����� ����
	case BFFM_SELCHANGED:		// ����ڰ� ������ ������ ��� ��ȭ���ڿ� ���õ� ��� ǥ��
		{
			TCHAR szPath[ MAX_PATH ] = { 0, };

			::SHGetPathFromIDList( (LPCITEMIDLIST)lParam, szPath );
			::SendMessage( hWnd, BFFM_SETSTATUSTEXT, 0, (LPARAM)szPath );
		}
		break;

	// BROWSEINFO ����ü�� ulFlags ���� BIF_VALIDATE �� ������ ��� ȣ��
	// BIF_EDITBOX �� ���� ������ ��츸 ȣ���
	case BFFM_VALIDATEFAILED:	// ������ ��Ʈ�ѿ��� ���� �̸��� �߸� �Է��� ��� ȣ��
		{
			::MessageBox( hWnd, _T( "�ش� ������ ã�� �� �����ϴ�." ), _T( "����" ),
				MB_ICONERROR | MB_OK );
		}
		break;
	}

	return 0;
}
void CAthletic_Doc::OnFileOpen()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CWnd *pWnd = AfxGetMainWnd();
	HWND hWnd = pWnd->m_hWnd;

	BROWSEINFO bi;

	TCHAR szTemp[ MAX_PATH ] = { 0, };

	TCHAR * pszPath = _T( "C:\\" );
	
	::ZeroMemory( &bi, sizeof( BROWSEINFO ) );

	bi.hwndOwner	= hWnd;
	bi.lpszTitle	= _T( "���� ��θ� �������ּ���." );
	bi.ulFlags		= BIF_NEWDIALOGSTYLE | BIF_EDITBOX | BIF_RETURNONLYFSDIRS
						| BIF_STATUSTEXT | BIF_VALIDATE;
	bi.lpfn			= BrowseCallbackProc;
	bi.lParam		= (LPARAM)pszPath;

	LPITEMIDLIST pItemIdList = ::SHBrowseForFolder( &bi );

	if( !::SHGetPathFromIDList( pItemIdList, szTemp ) )
		return;

	vtkSmartPointer<vtkImageData> input = vtkSmartPointer<vtkImageData>::New();
	
	char charPath[MAX_PATH] = {0};
	WideCharToMultiByte(CP_ACP, 0, szTemp, MAX_PATH, charPath, MAX_PATH, NULL, NULL);

	printf("Run vtkDICOMImageReader.. \n"); 
	vtkSmartPointer<vtkDICOMImageReader> dicomReader = vtkSmartPointer<vtkDICOMImageReader>::New();
	dicomReader->SetDirectoryName(charPath);
	dicomReader->SetDataScalarTypeToShort();
	dicomReader->Update();
	input->DeepCopy(dicomReader->GetOutput());
	
	int dim[3];
	input->GetDimensions(dim);
	
	if(dim[0] < 2 || dim[1] < 2 || dim[2] < 2){
		return;
	}else{
		printf("load Volume data size (x,y,z) : %d, %d, %d\n", dim[0], dim[1], dim[2]);
	}

	short *h_volume = (short*)input->GetScalarPointer();

	double *range =input->GetScalarRange();
	printf("-min density : %.1f\n-max density : %.1f\n", range[0], range[1]);

	double *spacing = input->GetSpacing();
	printf("-voxel spacing : %f %f %f\n", spacing[0], spacing[1], spacing[2]);


	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	CChildFrame *pChild = (CChildFrame *)pFrame->GetActiveFrame();
	CAthletic_View *pView = (CAthletic_View *)pChild->GetActiveView();

	pView->SetImageSize(dim[0]+200, dim[2]+200);
	float firstView[3] = {(float)dim[0]/2.f, (float)dim[1], (float)dim[2]/2.f};
	pView->SetViewPoint(firstView);
	firstView[1] /= 2.f;
	pView->SetVolumeCenter(firstView);

	pView->SetVolume(h_volume, dim, range, spacing);
	pView->SetTF(4096);

	printf("\n[Volume Load Complete]\n\n");
	
	MessageBox( hWnd, szTemp, _T("���� �ε� Ȯ��"), MB_OK );

}


void CAthletic_Doc::OnCpuVR()
{
	CWnd *pWnd = AfxGetMainWnd();
	HWND hWnd = pWnd->m_hWnd;

	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	CChildFrame *pChild = (CChildFrame *)pFrame->GetActiveFrame();
	CAthletic_View *pView = (CAthletic_View *)pChild->GetActiveView();

	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if(pView->GetVolume()->GetDensityPointer() == NULL) {
		printf("no Volume \n");
		MessageBox( hWnd, _T("������ �����ϴ�."), _T("���"), MB_OK );
		return;
	}
	if(pView->GetTF()->GetTFData() == NULL) {
		MessageBox( hWnd, _T("��ȯ�Լ��� �����ϴ�."), _T("���"), MB_OK );
		return;
	}
	
	//printf("%d %d \n", pView->GetImageSize()[0], pView->GetImageSize()[1]);

	uchar *image = m_render_cpu.VR_basic(pView->GetVolume(), pView->GetTF(), 
		pView->GetImageSize(), pView->GetViewingPoint());
	pView->SetBuffer(image);
	pView->SetRenderType(0);
	
	pView->Invalidate(TRUE);
}


void CAthletic_Doc::OnGpuVR()
{
	CWnd *pWnd = AfxGetMainWnd();
	HWND hWnd = pWnd->m_hWnd;

	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	CChildFrame *pChild = (CChildFrame *)pFrame->GetActiveFrame();
	CAthletic_View *pView = (CAthletic_View *)pChild->GetActiveView();

	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if(pView->GetVolume()->GetDensityPointer() == NULL) {
		printf("no Volume \n");
		MessageBox( hWnd, _T("������ �����ϴ�."), _T("���"), MB_OK );
		return;
	}
	if(pView->GetTF()->GetTFData() == NULL) {
		MessageBox( hWnd, _T("��ȯ�Լ��� �����ϴ�."), _T("���"), MB_OK );
		return;
	}
	
	//printf("%d %d \n", pView->GetImageSize()[0], pView->GetImageSize()[1]);

	uchar *image = m_render_gpu.VR_basic(pView->GetVolume(), pView->GetTF(), 
		pView->GetImageSize(), pView->GetViewingPoint());

	pView->SetBuffer(image);
	pView->SetRenderType(100);

	pView->Invalidate(TRUE);
}


void CAthletic_Doc::OnGpuVR_AO()
{
	CWnd *pWnd = AfxGetMainWnd();
	HWND hWnd = pWnd->m_hWnd;

	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	CChildFrame *pChild = (CChildFrame *)pFrame->GetActiveFrame();
	CAthletic_View *pView = (CAthletic_View *)pChild->GetActiveView();

	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if(pView->GetVolume()->GetDensityPointer() == NULL) {
		printf("no Volume \n");
		MessageBox( hWnd, _T("������ �����ϴ�."), _T("���"), MB_OK );
		return;
	}
	if(pView->GetTF()->GetTFData() == NULL) {
		MessageBox( hWnd, _T("��ȯ�Լ��� �����ϴ�."), _T("���"), MB_OK );
		return;
	}

	//printf("%d %d \n", pView->GetImageSize()[0], pView->GetImageSize()[1]);

	uchar *image = m_render_gpu.VR_AmbientOcclusion(pView->GetVolume(), pView->GetTF(), 
		pView->GetImageSize(), pView->GetViewingPoint());
	if(image == NULL){
		MessageBox( hWnd, _T("����� ���� �ϼ���."), _T("����"), MB_OK );
		return;
	}

	pView->SetBuffer(image);
	pView->SetRenderType(101);

	pView->Invalidate(TRUE);
}
