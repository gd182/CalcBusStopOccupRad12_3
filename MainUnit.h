//---------------------------------------------------------------------------

#ifndef MainUnitH
#define MainUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.Series.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>

#include <fstream>
#include <cmath>

#define DefFileName L"Безымянный"
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
	TMainMenu *MainMenu;
	TMenuItem *N1;
	TMenuItem *MCreate;
	TMenuItem *N2;
	TMenuItem *MOpen;
	TMenuItem *MSave;
	TMenuItem *MSaveAs;
	TMenuItem *N3;
	TMenuItem *MClose;
	TMenuItem *N4;
	TStringGrid *CapacityGrid;
	TLabel *Label1;
	TStringGrid *NumDoorsGrid;
	TStringGrid *CoefQuanGrid;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TMenuItem *MAddCapacity;
	TMenuItem *MDelCapacity;
	TMenuItem *N5;
	TMenuItem *MAddNumDoors;
	TMenuItem *MDelNumDoors;
	TMenuItem *N6;
	TMenuItem *MAddCoefQuan;
	TMenuItem *MDelCoefQuan;
	TSaveDialog *SaveFileDialog;
	TLabel *Label5;
	TEdit *ETimeIE;
	TLabel *Label6;
	TEdit *EMinInterval;
	TStatusBar *StatusBar;
	TOpenDialog *OpenFileDialog;
	TScrollBox *ScrollBoxRes;
	TButton *BCalcData;
	TLabel *Label7;
	TMenuItem *N7;
	TMenuItem *MCalcData;
	TImage *Charts;
	TButton *BNextChart;
	TButton *BPrevChart;
	TLabel *LChart;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall MAddCapacityClick(TObject *Sender);
	void __fastcall MDelCapacityClick(TObject *Sender);
	void __fastcall MAddNumDoorsClick(TObject *Sender);
	void __fastcall MDelNumDoorsClick(TObject *Sender);
	void __fastcall MAddCoefQuanClick(TObject *Sender);
	void __fastcall MDelCoefQuanClick(TObject *Sender);
	void __fastcall MSaveClick(TObject *Sender);
	void __fastcall MSaveAsClick(TObject *Sender);
	void __fastcall MOpenClick(TObject *Sender);
	void __fastcall BCalcDataClick(TObject *Sender);
	void __fastcall BNextChartClick(TObject *Sender);
	void __fastcall BPrevChartClick(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall MCreateClick(TObject *Sender);
	void __fastcall MCloseClick(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall IntGridKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall DoubleKeyPress(TObject *Sender, System::WideChar &Key);
private:	// User declarations
	void __fastcall AddCol(TStringGrid *Grid, TMenuItem *MDel);
	void __fastcall DelCol(TStringGrid *Grid, TMenuItem *MDel);
	bool __fastcall CheckSourData(bool ForSave);
	bool __fastcall SaveSourData();
	bool __fastcall CheckChangeData();
	DynamicArray <TStringGrid *> TableRes;
	DynamicArray <TLabel *> LabelRes;
	bool __fastcall PaintChart(int NumChart);
	double FMax;
	int NumChart =0;
public:		// User declarations
	__fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
