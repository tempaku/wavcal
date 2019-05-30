
// wavcal.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです。
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CwavcalApp:
// このクラスの実装については、wavcal.cpp を参照してください。
//

class CwavcalApp : public CWinAppEx
{
public:
	CwavcalApp();

// オーバーライド
	public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CwavcalApp theApp;