
// wavcalDlg.h : ヘッダー ファイル
//

#pragma once
#include "afxwin.h"
#include "WaveData.h"
#include "afxcmn.h"

// CwavcalDlg ダイアログ
class CwavcalDlg : public CDialog
{
// コンストラクション
public:
	CwavcalDlg(CWnd* pParent = NULL);	// 標準コンストラクタ

// ダイアログ データ
	enum { IDD = IDD_WAVCAL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート


// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	void Drawf1();
	void Drawf2();
	void Drawf1x2();
	void Drawspectrum();
void CwavcalDlg::drawgraph( CDC* pdc,
						   int posx, int posy, int orgx, int orgy, int cx, int cy, 
						   int minx, int maxx, float *data, int maxdata );

	WaveData m_wavedata;
	WaveData m_wavedata2;
	WaveData m_wavedata1x2;
	WaveData m_spectrum;
	void createwavedata( WaveData* wd, double amp, double freq, double phase, int samples );
	void createinpulse( WaveData* wd, int samples );
	void calc1x2();
	void calcfft();

	int m_samples;
	float m_f1;
	float m_f2;
	float m_theta1;
	float m_theta2;

	int m_1x2_x_max;

	void calcf1();
	void calcf2();

	void Hamming( double *data, int datalen );
	void Hanning( double *data, int datalen );
	void BlackmanHarris( double *data, int datalen );
public:
	CStatic m_img;
	CStatic m_img2;
	CStatic m_img3;
	CStatic m_img4;
	afx_msg void OnEnChangeEditF1();
	afx_msg void OnEnKillfocusEditF1();
	CEdit m_edit_f1;
	CEdit m_edit_f2;
	afx_msg void OnEnKillfocusEditF2();
	CEdit m_edit_theta1;
	CEdit m_edit_theta2;
	afx_msg void OnEnKillfocusEditTheta1();
	afx_msg void OnEnKillfocusEditTheta2();
	afx_msg void OnBnClickedRadioLog();
	afx_msg void OnBnClickedRadioLinear();
private:
	BOOL m_radio_loglinear;
	CButton m_radio_log;
	CSliderCtrl m_slider_f1;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CSliderCtrl m_slider_f2;
	afx_msg void OnCbnSelchangeCombo1();
	CComboBox m_combo_operator;
public:
	CComboBox m_combo_winfunc;
	afx_msg void OnCbnSelchangeComboWinfunc();
	afx_msg void OnBnClickedBtn1x2Full();
private:
	CSliderCtrl m_slider_1x2_zoom;
public:
	CButton m_checkinpulse;
	afx_msg void OnBnClickedInpulse();
	CSliderCtrl m_slider_p1;
	CSliderCtrl m_slider_p2;
	afx_msg void OnNMCustomdrawSliderF1(NMHDR *pNMHDR, LRESULT *pResult);
};
