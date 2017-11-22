// VisualTextView.h : interface of the CVisualTextView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GUI_VISUALSTUDIO6VIEW_H__59303E9E_F890_45AB_8D8B_B3D9AE27D84C__INCLUDED_)
#define AFX_GUI_VISUALSTUDIO6VIEW_H__59303E9E_F890_45AB_8D8B_B3D9AE27D84C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "undo.h"

enum CURSOR_LINE_TYPE {
	CURSOR_LINE_NORMAL = 0,
	CURSOR_LINE_BLANK,
	CURSOR_LINE_RULE_UNFORMATTED,
	CURSOR_LINE_RULE_FORMATTED_FIRST,
	CURSOR_LINE_RULE_FORMATTED_LAST,
	CURSOR_LINE_RULE_FORMATTED,
};

/////////////////////////////////////////////////////////////////////////////
// CVisualTextView view

class CVisualTextDoc;
class CVisualTextView : public CRichEditView
{
protected: // create from serialization only
	CVisualTextView();
	DECLARE_DYNCREATE(CVisualTextView)

	BOOL IsStringQuote(TCHAR ch);
	int IsZone(LPCTSTR lpszSymbol);
	int IsNLPWord(LPCTSTR lpszSymbol);
	int IsNodeWord(LPCTSTR lpszSymbol);
	int IsConstant(LPCTSTR lpszSymbol);
	int IsAttribute(LPCTSTR lpszSymbol);

	void SetAsModified();
	void GetUndoParmsSelText(CString* pStr, CHARRANGE &cr, BOOL bPreAction=false, _TCHAR nChar=0);
	BOOL GetSelFromCursor(int& selStart, int& selEnd);
	BOOL SetFormatRangeFont(int nStart, int nEnd);
	void SetFormatRange(int nStart, int nEnd, BOOL bBold, COLORREF clr);
	void FormatTextRange(int nStart, int nEnd);
	bool IsInWordList(_TCHAR *wordList[], CString wordStr, BOOL bCaseSensitive=true);
	void FormatTextLines(int nStart, int nEnd);
	void ChangeCase(int nStart, int nEnd, LPCTSTR lpszStr);
	void WhenChange();
	void DoForm();

	struct SymbolColor {
		COLORREF clrColor;
		BOOL bBold;
	};

	SymbolColor m_icNLP;
	SymbolColor m_icNode;
	SymbolColor m_icZone;
	SymbolColor m_icAttribute;
	SymbolColor m_icConstant;
	SymbolColor m_icComment;
	SymbolColor m_icString;

// Attributes
public:
	CVisualTextDoc* GetDocument();
	void RemoveUndoList (void);

	BOOL m_bCursorAtEndOfDocument;
	CStringArray m_strURLs;
	BOOL m_bInsertMode;
	BOOL m_bCaseSensitive;
	BOOL m_bChangeCase;
	TCHAR m_chComment;
	TCHAR m_chComment2;


// Operations
public:
	void FormatAll();
	void FindForward();
	void FindBack();

	CFont m_font;
	BOOL m_bInForcedChange;
	CString m_strStringQuotes;
	CString m_strComment;

	void CreateFont();
	void Scroll(int lines);
	void Initialize();
	void ClearFormat();

	void SetCaseSensitive(BOOL bSensitive);
	void SetChangeCase(BOOL bChange);

	void SetSLComment(TCHAR chComment, TCHAR chComment2 = 0);
	void SetSLComment(LPCTSTR lpszComment);
	void SetStringQuotes(LPCTSTR lpszStrQ);

	void AddKeywords(LPCTSTR lpszKwd);
	void AddConstants(LPCTSTR lpszKwd);
	void AddLargers(LPCTSTR lpszKwd);
	void ClearKeywords();
	void ClearConstants();
	void ClearLargers();

	void SetZoneColor(COLORREF clr, BOOL bBold);
	void SetAttributeColor(COLORREF clr, BOOL bBold);
	void SetConstantColor(COLORREF clr, BOOL bBold);
	void SetCommentColor(COLORREF clr, BOOL bBold);
	void SetNLPColor(COLORREF clr, BOOL bBold);
	void SetNodeColor(COLORREF clr, BOOL bBold);
	void SetStringColor(COLORREF clr, BOOL bBold);

	void SerializePublic(CArchive& ar);
	void SaveState();

	void ColorSelections(CString processTextStr, CStringList &selList);

	void SetIconType();

	bool GetSelTextTrim();	
	bool GetSelTextTrim(bool trimFlag, bool askFlag=true);	
	bool GetSelTextTrim(long &start, long &end, bool trimFlag=true, bool askFlag=true);

	void AdjustStartEnd(long &start, long &end, CString textPathStr=_T(""));
	void Mask();
	void WindowSizeFromTextSize(long width, long length, long &wOut, long &lOut);
	void AdjustDocSizeToText(CString fullFilePathStr);
	CString StateStr();
	void AppendToText(CString textStr, int blankLines=0);
	bool IsSampleFile();
	bool IsAutoGenerated();

private:
	void AddToUndoList (CUndoItem *pItemAdd);
	void AdjustUndoParms(CString* pStr, CHARRANGE &cr);
	bool GetCursorLine(CString &lineStr, int nth=-1);
	void OnFindBack();
	void OnFindForward();
	void LogFilePathStr(CString &logPathStr, CString &textPathStr);
	int LogFilePassNumberFromTitle(bool logFileFlag=false);
	CString RuleFileFromLog();
	void TextAddExample(UINT menuID=0);
	void SelectText();
	void InitVars();
	void StringToTokens(CStringList &tokens, CString textStr);
	void GetWindowBitmap();
	void SetWindowBitmap();
	void DragLabel(CPoint point);
	void SortSelection();
	void InsertString(CString str);
	void AddRuleElement(CString newRuleElementStr, bool parens=false);
	void ElementLocation(CString lineStr, CString elementStr, int &cursor, int &insertPoint,
										 int &bracketStart, int &bracketEnd,
										 int &elementStart, int &elementEnd);
	void TokenizeLine(CStringList &tokens, CString lineStr);
	void AddAttribute(CString newElementStr, CString valueStr=_T(""));
	void ChangeElement(CString newElementStr);
	CString StandardizeLine(CString lineInStr, int ruleLineNum=-1);
	bool ReformatRule(BOOL bLink=false);
	void GetRuleLines(CStringList &ruleLines, long &start, long &end, bool noAlert=false);
	void InsertLine(CString str, int cursorPos=0);
	int IndentReturn(int lineOffset);
	bool GetWorkingText(CString &lineStr,long &lineIndex,long &selStart,long &selEnd, CString alertMsgStr);
	bool SelectionInRule(bool noAlert=false);
	bool ApplyTabToSelection(bool shiftFlag=false);
	void ProcessFocus();
	void TextViewPopup(CPoint point);
	void RulePopup(CPoint point);
	void LogPopup(CPoint point);
	void FindLocal();
	CURSOR_LINE_TYPE GetCursorLineType();
	void SetCursorLineType();
	bool CalculateIsAnalyzed();

	CONCEPT *m_concept;
	HICON m_icon;
	CBitmap m_bitmap;
	CBitmap *m_dragBitmap;
	bool m_boolFirstTime;
	bool m_boolIsSampleFile;
	bool m_boolIsAutoGenerated;
	bool m_boolIsAnalyzed;
	CDC m_dragDC;
	CRect m_dragRect;
	int m_intCharWidth;
	int m_intLineHeight;
	TEXTMETRIC m_tm;
	DOC_TYPE m_docType;
	CURSOR_LINE_TYPE m_cursorLineType;
	BOOL m_bCutOp;
	CPtrArray m_UndoList;
	int m_IndexUndo;
	CHARRANGE m_crPre, m_crPost, m_cr2Pre, m_cr2Post; // Working Variables
	CString m_strPre, m_strPost; // Working Variables

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVisualTextView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CVisualTextView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CVisualTextView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnHelpCodejocksoftwareonthewebCodejocksoftwarehomepage();
	//}}AFX_MSG
	afx_msg void OnFilePrintPreview();
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in GUI_VisualStudioView.cpp
inline CVisualTextDoc* CVisualTextView::GetDocument()
   { return (CVisualTextDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GUI_VISUALSTUDIO6VIEW_H__59303E9E_F890_45AB_8D8B_B3D9AE27D84C__INCLUDED_)
