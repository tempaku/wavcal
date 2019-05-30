
// wavcalDlg.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "wavcal.h"
#include "wavcalDlg.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// �A�v���P�[�V�����̃o�[�W�������Ɏg���� CAboutDlg �_�C�A���O

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

// ����
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CwavcalDlg �_�C�A���O




CwavcalDlg::CwavcalDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CwavcalDlg::IDD, pParent)
	, m_radio_loglinear(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CwavcalDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IMG, m_img);
	DDX_Control(pDX, IDC_IMG2, m_img2);
	DDX_Control(pDX, IDC_IMG3, m_img3);
	DDX_Control(pDX, IDC_IMG4, m_img4);
	DDX_Control(pDX, IDC_EDIT_F1, m_edit_f1);
	DDX_Control(pDX, IDC_EDIT_F2, m_edit_f2);
	DDX_Control(pDX, IDC_EDIT_THETA1, m_edit_theta1);
	DDX_Control(pDX, IDC_EDIT_THETA2, m_edit_theta2);
	DDX_Radio(pDX, IDC_RADIO_LOG, m_radio_loglinear);
	DDX_Control(pDX, IDC_RADIO_LOG, m_radio_log);
	DDX_Control(pDX, IDC_SLIDER_F1, m_slider_f1);
	DDX_Control(pDX, IDC_SLIDER_F2, m_slider_f2);
	DDX_Control(pDX, IDC_COMBO1, m_combo_operator);
	DDX_Control(pDX, IDC_COMBO_WINFUNC, m_combo_winfunc);
	DDX_Control(pDX, IDC_SLIDER_1x2_ZOOM, m_slider_1x2_zoom);
	DDX_Control(pDX, IDC_INPULSE, m_checkinpulse);
	DDX_Control(pDX, IDC_SLIDER_P1, m_slider_p1);
	DDX_Control(pDX, IDC_SLIDER_P2, m_slider_p2);
}

BEGIN_MESSAGE_MAP(CwavcalDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_EN_CHANGE(IDC_EDIT_F1, &CwavcalDlg::OnEnChangeEditF1)
	ON_EN_KILLFOCUS(IDC_EDIT_F1, &CwavcalDlg::OnEnKillfocusEditF1)
	ON_EN_KILLFOCUS(IDC_EDIT_F2, &CwavcalDlg::OnEnKillfocusEditF2)
	ON_EN_KILLFOCUS(IDC_EDIT_THETA1, &CwavcalDlg::OnEnKillfocusEditTheta1)
	ON_EN_KILLFOCUS(IDC_EDIT_THETA2, &CwavcalDlg::OnEnKillfocusEditTheta2)
	ON_BN_CLICKED(IDC_RADIO_LOG, &CwavcalDlg::OnBnClickedRadioLog)
	ON_BN_CLICKED(IDC_RADIO_LINEAR, &CwavcalDlg::OnBnClickedRadioLinear)
	ON_WM_HSCROLL()
	ON_CBN_SELCHANGE(IDC_COMBO1, &CwavcalDlg::OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO_WINFUNC, &CwavcalDlg::OnCbnSelchangeComboWinfunc)
	ON_BN_CLICKED(IDC_BTN_1x2_FULL, &CwavcalDlg::OnBnClickedBtn1x2Full)
	ON_BN_CLICKED(IDC_INPULSE, &CwavcalDlg::OnBnClickedInpulse)
END_MESSAGE_MAP()


// CwavcalDlg ���b�Z�[�W �n���h��

BOOL CwavcalDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// "�o�[�W�������..." ���j���[���V�X�e�� ���j���[�ɒǉ����܂��B

	// IDM_ABOUTBOX �́A�V�X�e�� �R�}���h�͈͓̔��ɂȂ���΂Ȃ�܂���B
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���̃_�C�A���O�̃A�C�R����ݒ肵�܂��B�A�v���P�[�V�����̃��C�� �E�B���h�E���_�C�A���O�łȂ��ꍇ�A
	//  Framework �́A���̐ݒ�������I�ɍs���܂��B
	SetIcon(m_hIcon, TRUE);			// �傫���A�C�R���̐ݒ�
	SetIcon(m_hIcon, FALSE);		// �������A�C�R���̐ݒ�

	// TODO: �������������ɒǉ����܂��B
	m_samples = 2048;
	m_f1 = 32.0;
	m_f2 = 64.0;
	m_theta1 = 0.0;
	m_theta2 = 0.0;
	m_1x2_x_max = 400;
	CString str;

	str.Format( _T("%.2f"), m_f1 );
	m_edit_f1.SetWindowTextW( str );
	str.Format( _T("%.2f"), m_f2 );
	m_edit_f2.SetWindowTextW( str );
	str.Format( _T("%.2f"), m_theta1 );
	m_edit_theta1.SetWindowTextW( str );
	str.Format( _T("%.2f"), m_theta2 );
	m_edit_theta2.SetWindowTextW( str );
	m_radio_loglinear = FALSE;
	UpdateData( FALSE );

	m_slider_f1.SetRange( 1, 2000 );
	m_slider_f1.SetPos( (int)(m_f1*10.0) );
	m_slider_f2.SetRange( 1, 2000 );
	m_slider_f2.SetPos( (int)(m_f2*10.0) );

	m_slider_p1.SetRange( 0, 100 );
	m_slider_p1.SetPos( 50 );
	m_slider_p2.SetRange( 00, 100 );
	m_slider_p2.SetPos( 50 );

	m_slider_1x2_zoom.SetRange( 400, m_samples );
	m_slider_1x2_zoom.SetPos( m_1x2_x_max );

	m_combo_operator.SetCurSel( 0 );
	m_combo_winfunc.SetCurSel( 0 );

	createwavedata( &m_wavedata, 1.0f, m_f1, m_theta1, m_samples );
	createwavedata( &m_wavedata2, 1.0f, m_f2, m_theta2, m_samples );
	calc1x2();
	calcfft();

	return TRUE;  // �t�H�[�J�X���R���g���[���ɐݒ肵���ꍇ�������ATRUE ��Ԃ��܂��B
}

void CwavcalDlg::calc1x2()
{
	if ( m_wavedata.data == 0 || m_wavedata2.data == 0 ) return;

	if ( m_wavedata1x2.data ) delete [] m_wavedata1x2.data;
	m_wavedata1x2.data = new double[ m_wavedata.size ];

	BOOL bmult = (m_combo_operator.GetCurSel() == 0 )?TRUE:FALSE;
	int i;
	for ( i = 0; i < m_wavedata.size; i ++ ) {
		if ( bmult ) {
			m_wavedata1x2.data[i] = 
				m_wavedata.data[i] * m_wavedata2.data[i];
		} else {
			m_wavedata1x2.data[i] = 
				m_wavedata.data[i] + m_wavedata2.data[i];
		}
	}
	m_wavedata1x2.size = m_wavedata.size;

	if ( m_combo_winfunc.GetCurSel() == 1 ) {
		Hamming( m_wavedata1x2.data, m_wavedata1x2.size );
	} else if ( m_combo_winfunc.GetCurSel() == 2 ) {
		Hanning( m_wavedata1x2.data, m_wavedata1x2.size );
	} else if ( m_combo_winfunc.GetCurSel() == 3 ) {
		BlackmanHarris( m_wavedata1x2.data, m_wavedata1x2.size );
	}
}

void CwavcalDlg::Hamming( double *data, int datasize )
{
	int i;
	double pi = 4.0f * atan( 1.0 );
	float rate;

    for (i=0; i < datasize; i++)
	{
		rate = pi*(double)i/(double)datasize;
        data[i] = data[i]*(0.54 - 0.46 * cos(2*rate));	
	}
}
void CwavcalDlg::Hanning( double *data, int datasize )
{
	int i;
	double pi = 4.0f * atan( 1.0 );
	float rate;

    for (i=0; i < datasize; i++)
	{
		rate = pi*(double)i/(double)datasize;
        data[i] = data[i]*(0.5 - 0.5 * cos(2*rate));	
	}
}

void CwavcalDlg::BlackmanHarris( double *data, int datasize )
{
	int i;
	double pi = 4.0f * atan( 1.0 );
	float rate;

    for (i=0; i < datasize; i++)
	{
		rate = pi*(double)i/(double)datasize;
		data[i] = data[i]*(0.35875F - 0.48829F * cos(2.0F*rate) + 0.14128F * cos(4.0F*rate) - 0.01168F * cos(6.0F*rate));
	}
}

extern "C" void ctfft( double ar[], double ai[], int n );

void CwavcalDlg::calcfft()
{
	if ( m_wavedata1x2.data == 0 ) return;

	double *ar, *ai;
	ar = new double[ m_wavedata1x2.size ];
	ai = new double[ m_wavedata1x2.size ];
	int i;
	for ( i = 0; i < m_wavedata1x2.size; i ++ ) {
		ar[i] = m_wavedata1x2.data[i];
		ai[i] = 0.0;
	}

	ctfft( ar, ai, m_wavedata1x2.size );

	if ( m_spectrum.data ) delete [] m_spectrum.data;
	m_spectrum.data = new double[ m_wavedata1x2.size/2 + 1];
	for ( i = 0; i <= m_wavedata1x2.size/2; i ++ ) {
		m_spectrum.data[i] = sqrt( ar[i]*ar[i] + ai[i]*ai[i] );
	}
	m_spectrum.size = m_wavedata1x2.size/2+1;
	delete [] ar;
	delete [] ai;
}

void CwavcalDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �_�C�A���O�ɍŏ����{�^����ǉ�����ꍇ�A�A�C�R����`�悷�邽�߂�
//  ���̃R�[�h���K�v�ł��B�h�L�������g/�r���[ ���f�����g�� MFC �A�v���P�[�V�����̏ꍇ�A
//  ����́AFramework �ɂ���Ď����I�ɐݒ肳��܂��B

void CwavcalDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �`��̃f�o�C�X �R���e�L�X�g

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// �N���C�A���g�̎l�p�`�̈���̒���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �A�C�R���̕`��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{

		CDialog::OnPaint();
		Drawf1( );
		Drawf2( );
		Drawf1x2( );
		calcfft();
		Drawspectrum();

	}
}

// ���[�U�[���ŏ��������E�B���h�E���h���b�O���Ă���Ƃ��ɕ\������J�[�\�����擾���邽�߂ɁA
//  �V�X�e�������̊֐����Ăяo���܂��B
HCURSOR CwavcalDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CwavcalDlg::drawgraph( CDC* pdc,
						   int posx, int posy, int orgx, int orgy, int cx, int cy, 
						   int minx, int maxx, float *data, int maxdata )
{
	{
		CPen *pen = new CPen( PS_SOLID, 1, RGB(0, 255, 0));
		CPen *OldPen;
		OldPen = (CPen*)pdc->SelectObject(pen);

		pdc->MoveTo( posx+orgx, 0 );
		pdc->LineTo( posx+orgx, posy+cy );

		pdc->MoveTo( posx, posy+orgy );
		pdc->LineTo( posx+cx, posy+orgy );

		pdc->SelectObject(OldPen);
		delete pen;
	}
	CPen *pen = new CPen( PS_SOLID, 1, RGB(0, 255, 255));
	CPen *OldPen;
	OldPen = (CPen*)pdc->SelectObject(pen);

	{
		int i;
		float max = 0;
		for ( i = 0; i < maxdata; i ++ ) {
			if ( max < data[i] ) max = data[i];
		}
		for ( i = 0; i < maxdata; i ++ ) {
			data[i] /= max;
		}
	}

	int datamax = (maxx > maxdata)?maxdata:maxx;
	int i;
	float dx = (float)(cx-orgx) / (float)((datamax-minx)-1);
	float x, y;

	x = (float)posx+(float)orgx;
	y = (float)posy+(float)(orgy)-(data[minx])*(float)(cy/2);
	pdc->MoveTo( (int)x, (int)y );
	for ( i = minx+1; i < datamax ; i ++ ) {
		x += dx;
		y = (float)posy+(float)(orgy)-(data[i])*(float)(cy/2);
		pdc->LineTo( x, y );
	}
	pdc->SelectObject(OldPen);
	delete pen;
}

void CwavcalDlg::Drawf1( )
{
	CDC* pdc = m_img.GetDC();
	{
		pdc->SetBkColor( RGB( 0, 0, 0 ) );

		RECT rect;
		m_img.GetClientRect( &rect );

		pdc->FillSolidRect( &rect, RGB( 0,0,0 ) );
		int cx = rect.right - rect.left;
		int cy = rect.bottom - rect.top;
		int startx = 0;
		int starty = 0;
		int orgx = 20;
		int orgy = cy/2;
		int maxy = cy/2;
		int minx = 0;
		int maxx = 400;

		TRACE("%d, %d\n", cx, cy );

		if ( m_wavedata.data ) {
			int i;
			float *data = new float[ m_wavedata.size ];
			for ( i = 0; i < m_wavedata.size; i ++ ) {
				data[i] = m_wavedata.data[i];
			}
			drawgraph( pdc,
				startx, starty, orgx, orgy, cx, cy,
				minx, maxx, data, m_wavedata.size );

			delete [] data;
		}
		
		static int n = 0;
		TRACE(" %d\n", n++ );
	}
	m_img.ReleaseDC( pdc );
}

void CwavcalDlg::Drawf2( )
{
	CDC* pdc = m_img2.GetDC();
	{
		pdc->SetBkColor( RGB( 0, 0, 0 ) );

		RECT rect;
		m_img2.GetClientRect( &rect );

		pdc->FillSolidRect( &rect, RGB( 0,0,0 ) );
		int cx = rect.right - rect.left;
		int cy = rect.bottom - rect.top;
		int startx = 0;
		int starty = 0;
		int orgx = 20;
		int orgy = cy/2;
		int maxy = cy/2;
		int minx = 0;
		int maxx = 400;

		TRACE("%d, %d\n", cx, cy );

		if ( m_wavedata2.data ) {
			int i;
			float *data = new float[ m_wavedata2.size ];
			for ( i = 0; i < m_wavedata2.size; i ++ ) {
				data[i] = m_wavedata2.data[i];
			}
			drawgraph( pdc,
				startx, starty, orgx, orgy, cx, cy,
				minx, maxx, data, m_wavedata2.size );

			delete [] data;
		}
		
		static int n = 0;
		TRACE(" %d\n", n++ );
	}
	m_img2.ReleaseDC( pdc );
}

void CwavcalDlg::Drawf1x2( )
{
	CDC* pdc = m_img3.GetDC();
	{
		pdc->SetBkColor( RGB( 0, 0, 0 ) );

		RECT rect;
		m_img3.GetClientRect( &rect );

		pdc->FillSolidRect( &rect, RGB( 0,0,0 ) );
		int cx = rect.right - rect.left;
		int cy = rect.bottom - rect.top;
		int startx = 0;
		int starty = 0;
		int orgx = 20;
		int orgy = cy/2;
		int maxy = cy/2;
		int minx = 0;
		int maxx = m_1x2_x_max;

		TRACE("%d, %d\n", cx, cy );

		if ( m_wavedata1x2.data ) {
			int i;
			float *data = new float[ m_wavedata1x2.size ];
			for ( i = 0; i < m_wavedata1x2.size; i ++ ) {
				data[i] = m_wavedata1x2.data[i];
			}
			drawgraph( pdc,
				startx, starty, orgx, orgy, cx, cy,
				minx, maxx, data, m_wavedata1x2.size );

			delete [] data;
		}
		
		static int n = 0;
		TRACE(" %d\n", n++ );
	}
	m_img3.ReleaseDC( pdc );
}

void CwavcalDlg::Drawspectrum( )
{
	CDC* pdc = m_img4.GetDC();
	{
		pdc->SetBkColor( RGB( 0, 0, 0 ) );

		RECT rect;
		m_img4.GetClientRect( &rect );

		pdc->FillSolidRect( &rect, RGB( 0,0,0 ) );
		int cx = rect.right - rect.left;
		int cy = rect.bottom - rect.top;
		int startx = 0;
		int starty = 0;
		int orgx = 20;
		int orgy = cy;
		int maxy = cy;
		int minx = 0;
		int maxx = 400;

		TRACE("%d, %d\n", cx, cy );

		if ( m_spectrum.data ) {
			int i;
			float *data = new float[ m_spectrum.size ];
			double max = 0.0;
			for ( i = 0; i < m_spectrum.size; i ++ ) {
				if ( max < m_spectrum.data[i] ) max = m_spectrum.data[i];
			}

			for ( i = 0; i < m_spectrum.size; i ++ ) {
				data[i] = m_spectrum.data[i] / max;
			}

			UpdateData( TRUE );
			if ( m_radio_loglinear ) {
			} else {
				double min = 0.0;
				for ( i = 0; i < m_spectrum.size; i ++ ) {
					data[i] = log(data[i]);
					if ( data[i] < min ) min = data[i];
				}
				TRACE("%f\n", min );
				for ( i = 0; i < m_spectrum.size; i ++ ) {
					data[i] -= min;
					data[i] /= (-1*min);
				}
			}
			drawgraph( pdc,
				startx, starty, orgx, orgy, cx, cy,
				minx, maxx, data, m_spectrum.size );

			delete [] data;
		}
		
		static int n = 0;
		TRACE(" %d\n", n++ );
	}
	m_img4.ReleaseDC( pdc );
}
void CwavcalDlg::createwavedata( WaveData* wd, double amp, double freq, double phase, int samples )
{
	int i;
	double pi = 4.0f * atan( 1.0 );
	double dt;

	dt = 2.0f * pi * freq / (double)samples;

	if ( wd->data ) delete [] wd->data;
	wd->data = new double[ samples ];
	for ( i = 0; i < samples; i ++ ) {
		wd->data[i] = cos( i*dt + phase*pi);
	}
	wd->size = samples;
}

void CwavcalDlg::createinpulse( WaveData* wd, int samples )
{
	int i;

	if ( wd->data ) delete [] wd->data;
	wd->data = new double[ samples ];
	for ( i = 0; i < samples; i ++ ) {
		wd->data[i] = 0.0f;
	}
	wd->data[0] = 1.0f;
	wd->size = samples;
}


void CwavcalDlg::OnEnChangeEditF1()
{
	// TODO:  ���ꂪ RICHEDIT �R���g���[���̏ꍇ�A���̃R���g���[����
	// ���̒ʒm�𑗐M����ɂ́ACDialog::OnInitDialog() �֐����I�[�o�[���C�h���A
	// CRichEditCtrl().SetEventMask() ��
	// OR ��Ԃ� ENM_CHANGE �t���O���}�X�N�ɓ���ČĂяo���K�v������܂��B

	// TODO:  �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����Ă��������B
}

void CwavcalDlg::calcf1()
{
	CString str;
	LPCTSTR ptr;
	float f;

	if ( m_checkinpulse.GetCheck() ) {
		createinpulse( &m_wavedata, m_samples );
	} else {
		m_edit_f1.GetWindowText( str );
		ptr = (LPCTSTR)str;
		f = _wtof( (const wchar_t *)ptr );
		str.Format( _T("%.2f"), f );
		m_edit_f1.SetWindowText( str );
		m_f1 = f;

		m_edit_theta1.GetWindowText( str );
		ptr = (LPCTSTR)str;
		f = _wtof( (const wchar_t *)ptr );
		str.Format( _T("%.2f"), f );
		m_edit_theta1.SetWindowText( str );
		m_theta1 = f;

		createwavedata( &m_wavedata, 1.0f, m_f1, m_theta1, m_samples );
	}
	calc1x2();
	calcfft();

	Drawf1( );
	Drawf1x2( );
	Drawspectrum();

}

void CwavcalDlg::calcf2()
{
	CString str;
	LPCTSTR ptr;
	float f;
	m_edit_f2.GetWindowText( str );
	ptr = (LPCTSTR)str;
	f = _wtof( (const wchar_t *)ptr );
	str.Format( _T("%.2f"), f );
	m_edit_f2.SetWindowText( str );
	m_f2 = f;

	m_edit_theta2.GetWindowText( str );
	ptr = (LPCTSTR)str;
	f = _wtof( (const wchar_t *)ptr );
	str.Format( _T("%.2f"), f );
	m_edit_theta2.SetWindowText( str );
	m_theta2 = f;

	createwavedata( &m_wavedata2, 1.0f, m_f2, m_theta2, m_samples );
	calc1x2();
	calcfft();

	Drawf2( );
	Drawf1x2( );
	Drawspectrum();

}

void CwavcalDlg::OnEnKillfocusEditF1()
{
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
	calcf1();
}

void CwavcalDlg::OnEnKillfocusEditF2()
{
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
	calcf2();

}

void CwavcalDlg::OnEnKillfocusEditTheta1()
{
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
	calcf1();
}

void CwavcalDlg::OnEnKillfocusEditTheta2()
{
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
	calcf2();
}

void CwavcalDlg::OnBnClickedRadioLog()
{
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
	Drawspectrum();
}

void CwavcalDlg::OnBnClickedRadioLinear()
{
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
	Drawspectrum();
}

void CwavcalDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
	if ( (CSliderCtrl*)pScrollBar == &m_slider_f1 ) {
		int pos = m_slider_f1.GetPos();

		float f = (float)pos / 10.0f;
		CString str;
		str.Format( _T("%.2f"), f );
		m_edit_f1.SetWindowTextW( str );
		calcf1();
	} else if ( (CSliderCtrl*)pScrollBar == &m_slider_f2 ) {
		int pos = m_slider_f2.GetPos();

		float f = (float)pos / 10.0f;
		CString str;
		str.Format( _T("%.2f"), f );
		m_edit_f2.SetWindowTextW( str );
		calcf2();

	} else if ( (CSliderCtrl*)pScrollBar == &m_slider_p1 ) {
		int pos = m_slider_p1.GetPos();
		
		float f = (float)(pos-50) / 100.0f;
		CString str;
		str.Format( _T("%.2f"), f );
		m_edit_theta1.SetWindowTextW( str );
		calcf1();


	} else if ( (CSliderCtrl*)pScrollBar == &m_slider_p2 ) {
		int pos = m_slider_p2.GetPos();
		
		float f = (float)(pos-50) / 100.0f;
		CString str;
		str.Format( _T("%.2f"), f );
		m_edit_theta2.SetWindowTextW( str );
		calcf2();


	} else if ( (CSliderCtrl*)pScrollBar == &m_slider_1x2_zoom ) {
		int pos = m_slider_1x2_zoom.GetPos();
		
		m_1x2_x_max =pos;
		Drawf1x2();
	}

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CwavcalDlg::OnCbnSelchangeCombo1()
{
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
	calc1x2();
	calcfft();

	Drawf1x2( );
	Drawspectrum();
}

void CwavcalDlg::OnCbnSelchangeComboWinfunc()
{
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
	calc1x2();
	calcfft();

	Drawf1x2( );
	Drawspectrum();
}

void CwavcalDlg::OnBnClickedBtn1x2Full()
{
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
	m_1x2_x_max = m_wavedata1x2.size;
	m_slider_1x2_zoom.SetPos( m_1x2_x_max );
	Drawf1x2( );
}

void CwavcalDlg::OnBnClickedInpulse()
{
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
	calcf1();
}
