//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCreate(TObject *Sender)     //�������� �����
{
	CapacityGrid -> Cells[0][0] = L"�";              //��������� ��������� ���������
	CapacityGrid -> Cells[1][0] = L"1";
	CapacityGrid -> Cells[0][1] = L"\u03A9";
	NumDoorsGrid -> Cells[0][0] = L"�";
	NumDoorsGrid -> Cells[1][0] = L"1";
	NumDoorsGrid -> Cells[0][1] = L"���";
	CoefQuanGrid -> Cells[0][0] = L"�";
	CoefQuanGrid -> Cells[1][0] = L"1";
	CoefQuanGrid -> Cells[0][1] = L"���";
	MSave->Enabled= false;
	MDelCapacity -> Enabled = false;
	MDelNumDoors -> Enabled = false;
	MDelCoefQuan -> Enabled = false;
	BPrevChart -> Enabled = false;
	BNextChart -> Enabled = false;
	MainForm->Caption=String(Application->Title)+L" - "+DefFileName;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::AddCol(TStringGrid *Grid, TMenuItem *MDel) { //���������� �������� � ��������
	Grid->ColCount++;                          //���������� �������
	Grid->Cells[Grid->ColCount-1][0]=Grid->ColCount-1;  //������ ������� ����������� �������
	Grid->Cells[Grid->ColCount-1][1]=L"";               //������� ���������� ������
	MDel -> Enabled = true;                             //��������� ������ �������� ��������
	if (!MSave->Enabled) {                              //�������� ������� ����������� ���������
		MSave->Enabled= true;                           //��������� ������ ��������� (������� ������� ������������ ���������)
		MainForm->Caption+=L"*";                        //���������� �������� � ��������� ���������
	}
}

void __fastcall TMainForm::DelCol(TStringGrid *Grid, TMenuItem *MDel) { //�������� �������� �������
	if (Grid->ColCount <=2)                             //�������� ����������� �������� �������
		return;
	Grid->ColCount--;                                   //�������� �������
	if (Grid -> ColCount == 2)
		MDel -> Enabled = false;                        //��������� ������ ��������
	if (!MSave->Enabled) {                              //�������� ������� ����������� ���������
		MSave->Enabled= true;                           //��������� ������ ��������� (������� ������� ������������ ���������)
		MainForm->Caption+=L"*";                        //���������� �������� � ��������� ���������
	}
}

void __fastcall TMainForm::MAddCapacityClick(TObject *Sender)    //���������� ������� � 1 �������
{
	AddCol(CapacityGrid, MDelCapacity);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::MDelCapacityClick(TObject *Sender)    //�������� ������� � 1 �������
{
	DelCol(CapacityGrid,MDelCapacity);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::MAddNumDoorsClick(TObject *Sender)   //���������� ������� � 2 �������
{
	AddCol(NumDoorsGrid, MDelNumDoors);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::MDelNumDoorsClick(TObject *Sender)   //�������� ������� � 2 �������
{
    DelCol(NumDoorsGrid, MDelNumDoors);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::MAddCoefQuanClick(TObject *Sender)    //���������� ������� � 3 �������
{
	AddCol(CoefQuanGrid, MDelCoefQuan);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::MDelCoefQuanClick(TObject *Sender)    //�������� ������� � 3 �������
{
    DelCol(CoefQuanGrid, MDelCoefQuan);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::MSaveClick(TObject *Sender)   //������� �� ������ ���������
{
	if (!CheckSourData(true))                         //�������� ������ ��� ����������
		return;
	String OldFN = SaveFileDialog->FileName;          //���������� ������� ����� �����
	if (SaveFileDialog -> FileName==L"") {            //���� ���� �� ������
		SaveFileDialog->FileName=DefFileName;         //������ ���������� ����� �����
		if (!SaveFileDialog->Execute()) {             //����� ������� ����������
			SaveFileDialog->FileName=OldFN;           //����������� ������� ����� �����
			return;
		}
	}
	if (!SaveSourData()) {                              //���������� ������
		SaveFileDialog->FileName=OldFN;                //����������� ������� ����� �����
		return;
	}
	MSave->Enabled= false;                           //���������� ������ ��������� (������� ������� ������������ ���������)
	MainForm->Caption=String(Application->Title)+L" - "+ExtractFileName(SaveFileDialog->FileName); //������ ����� ����� � ���������
}
//---------------------------------------------------------------------------
bool __fastcall TMainForm::CheckSourData(bool ForSave) {  //�������� ������ �� ������������ � ������������
	String ErrMess = L"";                                //���������� ��� ��������� �� ������
	for (int i =1; i < CapacityGrid -> ColCount; i++) {   //������� �������� 1 �������
		int TestValue;
			if (!(CapacityGrid -> Cells[i][1]==L""&&ForSave) && !TryStrToInt(CapacityGrid -> Cells[i][1], TestValue)||TestValue<0) {  //�������� �������� 1 �������
				if (ErrMess == "")     //������������ ��������� �� ������
					ErrMess=String(L"������������ ��� ������������ �������� ����������� ���������� �: ") + i;
				else
					ErrMess+=String(L", ")+i;
			}
	}
	if (ErrMess != "")
		ErrMess += L". ";
	bool NotErr = true;
	for (int i =1; i < NumDoorsGrid -> ColCount; i++) {     //������� �������� 2 �������
		int TestValue;
			if (!(NumDoorsGrid -> Cells[i][1]==L""&&ForSave) && !TryStrToInt(NumDoorsGrid -> Cells[i][1], TestValue)||TestValue<0) {  //�������� �������� 2 �������
				if (NotErr) {          //������������ ��������� �� ������
					NotErr = false;
					ErrMess+=String(L"������������ ��� ������������ �������� ����� ������ �: ") + i;
				}
				else
					ErrMess+=String(L", ")+i;
			}
	}
	if (!NotErr) {              //������������ ��������� �� ������
		ErrMess += L". ";
		NotErr = true;
	}
	for (int i =1; i < CoefQuanGrid -> ColCount; i++) {     //������� �������� 3 �������
		float TestValue;
			if (!(CoefQuanGrid -> Cells[i][1]==L""&&ForSave) && !TryStrToFloat(CoefQuanGrid -> Cells[i][1], TestValue)||TestValue<0) {     //�������� �������� 3 �������
				if (NotErr) {          //������������ ��������� �� ������
					NotErr = false;
					ErrMess+=String(L"������������ ��� ������������ �������� ������������ ������ � ����� �: ") + i;
				}
				else
					ErrMess+=String(L", ")+i;
			}
	}
	if (!NotErr) {             //������������ ��������� �� ������
		ErrMess += L". ";
		NotErr = true;
	}
	float TestValue;
	if (!(ETimeIE->Text==L""&&ForSave) && (!TryStrToFloat(ETimeIE->Text, TestValue)||TestValue<0)) {   //�������� �������� � 1 ���� �����
		NotErr = false;
		ErrMess+=L"������������ ��� ������������ ��������: ������� ������ � �����";  //������������ ��������� �� ������
	}
	if (!(EMinInterval->Text==L""&&ForSave) && (!TryStrToFloat(EMinInterval->Text, TestValue)||TestValue<0)) {     //�������� �������� � 2 ���� �����
		if (NotErr) {                                                       //������������ ��������� �� ������
			NotErr = false;
			ErrMess+=L"������������ ��� ������������ ��������: ������������ ���������.";
		}
		else
			ErrMess+=L", ������������ ���������.";
	}
	if (ErrMess != "") {                  //���� ���� ������� ������
		StatusBar->SimpleText=ErrMess;    //����� ����� ������ � ������ ���
		Application->MessageBox(ErrMess.w_str(),Application->Title.w_str(), MB_OK|MB_ICONEXCLAMATION); //����� ������ ������ � ��������� ����
		return false;        //���������� � ��������
	}
	return true;            //���������� ��� ������
}

bool __fastcall TMainForm::SaveSourData() { //���������� ������ � ����
	DynamicArray<int> DCapacityGrid;       //���������� ��������
	DynamicArray<int> DNumDoorsGrid;
	DynamicArray<double> DCoefQuanGrid;
	try {
		DCapacityGrid.Length=CapacityGrid -> ColCount-1;        //��������� ������ ��� �������
		DNumDoorsGrid.Length=NumDoorsGrid -> ColCount-1;
		DCoefQuanGrid.Length=CoefQuanGrid -> ColCount-1;
	} catch (...) {                               //���� ���� ������� ����������
		DCapacityGrid.Length=0;                   //������������ ������ ��-��� �������
		DNumDoorsGrid.Length=0;
		DCoefQuanGrid.Length=0;
		Application->MessageBox(L"�� ������� ����������� ������, ��� ���������� ������!",Application->Title.w_str(),  //����� ������ ������ � ��������� ����
									MB_OK|MB_ICONEXCLAMATION);
		return false;    //���������� � �������
	}
	for (int i=0; i < CapacityGrid -> ColCount-1; i++) {      //������ ������ �� 1 ������� � ������
		if (CapacityGrid -> Cells[i+1][1]==L"")
			DCapacityGrid[i]=INT_MIN;                    //���� ������ ������, �� ������ ������������ ��������
		else
			TryStrToInt(CapacityGrid -> Cells[i+1][1],DCapacityGrid[i]);
	}
	for (int i=0; i < NumDoorsGrid -> ColCount-1; i++) {      //������ ������ �� 2 ������� � ������
		if (NumDoorsGrid -> Cells[i+1][1]==L"")
			DNumDoorsGrid[i]=INT_MIN;                    //���� ������ ������, �� ������ ������������ ��������
		else
			TryStrToInt(NumDoorsGrid -> Cells[i+1][1],DNumDoorsGrid[i]);
	}
	for (int i=0; i < CoefQuanGrid -> ColCount-1; i++) {      //������ ������ �� 3 ������� � ������
		if (CoefQuanGrid -> Cells[i+1][1]==L"")
			DCoefQuanGrid[i]=INT_MIN;                    //���� ������ ������, �� ������ ������������ ��������
		else
			TryStrToFloat(CoefQuanGrid -> Cells[i+1][1],DCoefQuanGrid[i]);
	}
	double DataEdit;                    //������������� ��������������� ���������
	int ColCount;
	unsigned int CountByte = sizeof(CountByte)+ sizeof(ColCount)*3+(CapacityGrid -> ColCount-1)*sizeof(DCapacityGrid[0])+  //������ �������� ������� ����� ��� ������� ����������� ��� ������
							  (NumDoorsGrid -> ColCount-1)*sizeof(DNumDoorsGrid[0])+ (CoefQuanGrid -> ColCount-1)*sizeof(DCoefQuanGrid[0])+
								sizeof(DataEdit)*2;
	std::fstream file;
	file.open(AnsiString(SaveFileDialog->FileName).c_str(), std::ios::out | std::ios::binary);  //�������� ����� ��� ����������
	if (!file) {                                 //���� ��������� ������� ����
		DCapacityGrid.Length=0;                   //������������ ������ ��-��� �������
		DNumDoorsGrid.Length=0;
		DCoefQuanGrid.Length=0;
		Application->MessageBox((String(L"�� ������� ������� ���� \"")+SaveFileDialog->FileName+"\"!").w_str(),Application->Title.w_str(),   //����� ������ ������ � ��������� ����
								MB_OK|MB_ICONERROR);
		return false;      //���������� � �������
	}
	file.write((char*)&CountByte, sizeof(CountByte)); //������ � ���� ������� �����
	ColCount = CapacityGrid -> ColCount-1;
	file.write((char*)&ColCount, sizeof(ColCount)); //������ � ���� ������� 1 �������
	ColCount = NumDoorsGrid -> ColCount-1;
	file.write((char*)&ColCount, sizeof(ColCount)); //������ � ���� ������� 2 �������
	ColCount = CoefQuanGrid -> ColCount-1;
	file.write((char*)&ColCount, sizeof(ColCount)); //������ � ���� ������� 3 �������
	file.write((char*)&DCapacityGrid[0], sizeof(DCapacityGrid[0])*(CapacityGrid -> ColCount-1));  //������ ������ 1 �������
	DCapacityGrid.Length=0;                                                   //������������ ������ ��-��� 1 �������
	file.write((char*)&DNumDoorsGrid[0], sizeof(DNumDoorsGrid[0])*(NumDoorsGrid -> ColCount-1));  //������ ������ 2 �������
	DNumDoorsGrid.Length=0;                                                   //������������ ������ ��-��� 2 �������
	file.write((char*)&DCoefQuanGrid[0], sizeof(DCoefQuanGrid[0])*ColCount);  //������ ������ 3 �������
	DCoefQuanGrid.Length=0;                                                   //������������ ������ ��-��� 3 �������
	if (ETimeIE->Text==L"")                         //������ ������ 1 ���� �����
		DataEdit=DBL_MIN;
	else
		TryStrToFloat(ETimeIE->Text, DataEdit);
	file.write((char*)&DataEdit, sizeof(DataEdit));
	if (EMinInterval->Text==L"")                   //������ ������ 2 ���� �����
		DataEdit=DBL_MIN;
	else
		TryStrToFloat(EMinInterval->Text, DataEdit);
	file.write((char*)&DataEdit, sizeof(DataEdit));
	file.close();                                   //�������� �����
	return true;       //���������� � ������� ��� ������
}

void __fastcall TMainForm::MSaveAsClick(TObject *Sender)
{
	if (!CheckSourData(true))                         //�������� ������ ��� ����������
		return;
	String OldFN = SaveFileDialog->FileName;          //���������� ������� ����� �����
	SaveFileDialog->FileName=DefFileName;         //������ ���������� ����� �����
	if (!SaveFileDialog->Execute()) {             //����� ������� ����������
		SaveFileDialog->FileName=OldFN;           //����������� ������� ����� �����
		return;
	}
	if (!SaveSourData()) {                              //���������� ������
		SaveFileDialog->FileName=OldFN;                //����������� ������� ����� �����
		return;
	}
	MSave->Enabled= false;                           //���������� ������ ��������� (������� ������� ������������ ���������)
	MainForm->Caption=String(Application->Title)+L" - "+ExtractFileName(SaveFileDialog->FileName); //������ ����� ����� � ���������
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::MOpenClick(TObject *Sender)        //������� �����
{
	if (!CheckChangeData()) //�������� ������� ������������ ���������
		return;
	if (!OpenFileDialog->Execute())     //����� ������� ��������
		return;
	unsigned int CountByte;
	std::fstream file;
	file.open(AnsiString(OpenFileDialog->FileName).c_str(), std::ios::in | std::ios::binary);              //�������� �����
	if (!file) {                                                                                //���� �� ������� ������� ����
		Application->MessageBox((String(L"�� ������� ������� ���� \"")+OpenFileDialog->FileName+"\"!").w_str(),Application->Title.w_str(), MB_OK|MB_ICONERROR); //����� ������ ������ � ��������� ����
		return;
	}
	file.read((char*)&CountByte, sizeof(CountByte));   //������ ������� ����� ��� ������
	file.seekg(0, std::ios::end);                          //��������� ��������� � ����� �����
	file.clear();
	if (CountByte != file.tellg()){                   //�������� �� ����������� �����
		file.close();
		Application->MessageBox((String(L"�� ������� ��������� ������ �� ����� \"")+OpenFileDialog->FileName+"\". ���� ���������.").w_str(), Application->Title.w_str(), MB_OK|MB_ICONERROR);  //����� ������ ������ � ��������� ����
		return;
	}
	file.clear();
	file.seekg(sizeof(CountByte));      //��������� ��������� ����� ������� �����
	int ColCount1,ColCount2,ColCount3;
	file.read((char*)&ColCount1, sizeof(ColCount1));//������ ������� ������� 1
	file.read((char*)&ColCount2, sizeof(ColCount2));//������ ������� ������� 1 
	file.read((char*)&ColCount3, sizeof(ColCount3));//������ ������� ������� 1  
	DynamicArray<int> DCapacityGrid;       //���������� ��������
	DynamicArray<int> DNumDoorsGrid;
	DynamicArray<double> DCoefQuanGrid;
	try {
		DCapacityGrid.Length=ColCount1;        //��������� ������ ��� �������
		DNumDoorsGrid.Length=ColCount2;
		DCoefQuanGrid.Length=ColCount3;
	} catch (...) {                               //���� ���� ������� ����������
		DCapacityGrid.Length=0;                   //������������ ������ ��-��� �������
		DNumDoorsGrid.Length=0;
		DCoefQuanGrid.Length=0;
		Application->MessageBox(L"�� ������� ����������� ������, ��� ���������� ������!",Application->Title.w_str(),  //����� ������ ������ � ��������� ����
									MB_OK|MB_ICONEXCLAMATION);
		return;
	}
	file.read((char*)&DCapacityGrid[0], sizeof(DCapacityGrid[0])*ColCount1);        //������ ������ ������� 1
	CapacityGrid->ColCount=ColCount1+1;                                             //��������� ������� ������� 1
	for (int i=0; i < ColCount1; i++) {                                             //������ ������ ������� 1
		CapacityGrid -> Cells[i+1][0]=i+1;
		if (DCapacityGrid[i]==INT_MIN)
			CapacityGrid -> Cells[i+1][1]=L"";
		else
			CapacityGrid -> Cells[i+1][1]=DCapacityGrid[i];
	}
	DCapacityGrid.Length=0;                                                        //������������ ������ ��-��� �������
	file.read((char*)&DNumDoorsGrid[0], sizeof(DNumDoorsGrid[0])*ColCount2);       //������ ������ ������� 2
	NumDoorsGrid->ColCount=ColCount2+1;                                            //��������� ������� ������� 2
	for (int i=0; i < ColCount2; i++) {                                            //������ ������ ������� 2
		NumDoorsGrid -> Cells[i+1][0]=i+1;
		if (DNumDoorsGrid[i]==INT_MIN)
			NumDoorsGrid -> Cells[i+1][1]=L"";
		else
			NumDoorsGrid -> Cells[i+1][1]=DNumDoorsGrid[i];
	}
	DNumDoorsGrid.Length=0;                                                      //������������ ������ ��-��� �������
	file.read((char*)&DCoefQuanGrid[0], sizeof(DCoefQuanGrid[0])*ColCount3);     //������ ������ ������� 3
	CoefQuanGrid->ColCount=ColCount3+1;                                          //��������� ������� ������� 3
	for (int i=0; i < ColCount3; i++) {                                          //������ ������ ������� 3
		CoefQuanGrid -> Cells[i+1][0]=i+1;
		if (DCoefQuanGrid[i]==DBL_MIN)
			CoefQuanGrid -> Cells[i+1][1]=L"";
		else
			CoefQuanGrid -> Cells[i+1][1]=DCoefQuanGrid[i];
	}
	DCapacityGrid.Length=0;                                                       //������������ ������ ��-��� �������
	double DataEdit;
	file.read((char*)&DataEdit, sizeof(DataEdit));                                //������ ������ ���� ����� 1
	if (DataEdit==DBL_MIN)                                                        //������ ������ � ���� ����� 1
		ETimeIE->Text=L"";
	else
		ETimeIE->Text=DataEdit;
	file.read((char*)&DataEdit, sizeof(DataEdit));                                 //������ ������ ���� ����� 2
	file.close();                                                                  //�������� �����
	if (DataEdit==DBL_MIN)                                                         //������ ������ � ���� ����� 2
		EMinInterval->Text=L"";
	else
		EMinInterval->Text=DataEdit;
	//ClearOldResults();                                                           //������� �����������
	if (CapacityGrid -> ColCount>2)                                                    //���������� (���������) ������ �������� ��������
		MDelCapacity->Enabled=true;
	else
		MDelCapacity->Enabled=false;
	if (CapacityGrid -> ColCount>2)                                                    //���������� (���������) ������ �������� ��������
		MDelNumDoors->Enabled=true;
	else
		MDelNumDoors->Enabled=false;
	if (CoefQuanGrid -> ColCount>2)                                                    //���������� (���������) ������ �������� ��������
		MDelCoefQuan->Enabled=true;
	else
		MDelCoefQuan->Enabled=false; 
	SaveFileDialog->FileName=OpenFileDialog->FileName;                           //���������� ����� �����
	MSave->Enabled= false;                           //���������� ������ ��������� (������� ������� ������������ ���������)
	MainForm->Caption=String(Application->Title)+L" - "+ExtractFileName(SaveFileDialog->FileName); //������ ����� ����� � ���������
	Charts -> Picture->Assign( NULL );//�������� ������ ����������� ���������
	if (TableRes.Length!=0) {
		for (int i=0; i < TableRes.Length; i++) {
			TableRes[i]->Free();
			LabelRes[i]->Free();
		}
	}
	TableRes.Length=0;
	LabelRes.Length=0;
    BPrevChart -> Enabled = false;
	BNextChart -> Enabled = false;
}
//---------------------------------------------------------------------------

bool __fastcall TMainForm::CheckChangeData() {       //�������� ������� ������������ ���������
	if (MSave->Enabled) {                            //�������� ������� ������������ ���������
		String OldFN=SaveFileDialog->FileName;       //���������� ����� ��������� �����
		if (OldFN==L"") {
			OldFN=DefFileName;                    //������ ���������� ����� �����
		}
		switch (Application->MessageBox((String(L"������������ �� ���������� ���������. ��������� ��������� � ����� \"")+   //����� ���������� ���� � �������
									OldFN+"\"?").w_str(),
									Application->Title.w_str(), MB_YESNOCANCEL|MB_ICONQUESTION)){
			case mrCancel:                     //������� ������
				return false;                  //����� � �������� ���������� ��������
			case mrNo:
				return true;                    //����� � ����������� ���������� ��������
			case mrYes:
				if (!CheckSourData(true))                         //�������� ������ ��� ����������
					return false;
				if (SaveFileDialog -> FileName==L"") {            //���� ���� �� ������
					SaveFileDialog->FileName=DefFileName;         //������ ���������� ����� �����
					if (!SaveFileDialog->Execute()) {             //����� ������� ����������
						SaveFileDialog->FileName=L"";           //����������� ������� ����� �����
						return false;                  //����� � �������� ���������� ��������
					}
                    OldFN = L"";
				}
				if (!SaveSourData()) {                              //���������� ������
					SaveFileDialog->FileName=OldFN;                //����������� ������� ����� �����
					return false;                  //����� � �������� ���������� ��������
				}
				break;
		}
	}
	return true;      //����� � ����������� ���������� ��������
}


void __fastcall TMainForm::BCalcDataClick(TObject *Sender)
{
	if (!CheckSourData(false))                         //�������� ������ ��� ���������
		return;	
	if (TableRes.Length!=0) {//�������� ������ ����������� ���������
		for (int i=0; i < TableRes.Length; i++) {
			TableRes[i]->Free();
			LabelRes[i]->Free();
		}
	}
	DynamicArray<int> DCapacityGrid;       //���������� ��������
	DynamicArray<int> DNumDoorsGrid;
	DynamicArray<double> DCoefQuanGrid;
	try{
		DCapacityGrid.Length=CapacityGrid -> ColCount-1;        //��������� ������ ��� �������
		DNumDoorsGrid.Length=NumDoorsGrid -> ColCount-1;
		DCoefQuanGrid.Length=CoefQuanGrid -> ColCount-1;
		TableRes.Length=CoefQuanGrid -> ColCount-1;
		LabelRes.Length=CoefQuanGrid -> ColCount-1;
	}
	catch(...){//��������� ����������
		DCapacityGrid.Length=0;                   //������������ ������ ��-��� �������
		DNumDoorsGrid.Length=0;
		DCoefQuanGrid.Length=0;
		TableRes.Length=0;
		LabelRes.Length=0;
		Application->MessageBox(L"�� ������� ����������� ������ ��� ��������� ������",Application->Title.w_str(),  //����� ������ ������ � ��������� ����
								MB_OK|MB_ICONEXCLAMATION);
		return;
	}
	for (int i = 0; i < CapacityGrid -> ColCount-1; i++)            //����������� ������ ��� ���������
		DCapacityGrid[i] = StrToInt(CapacityGrid->Cells[i+1][1]);
	for (int i = 0; i < NumDoorsGrid -> ColCount-1; i++)
		DNumDoorsGrid[i] = StrToInt(NumDoorsGrid->Cells[i+1][1]);
	for (int i = 0; i < CoefQuanGrid -> ColCount-1; i++)
		DCoefQuanGrid[i] = StrToFloat(CoefQuanGrid->Cells[i+1][1]);		
	int TableTop=5;
	double TimeIE = StrToFloat(ETimeIE->Text);          //���������� ����� �����
	double MinInterval = StrToFloat(EMinInterval->Text);
	for (int q = 0; q < CoefQuanGrid -> ColCount-1; q++) {
		LabelRes[q]=new TLabel(ScrollBoxRes);//�������� ������� � �������
		LabelRes[q]->Parent = ScrollBoxRes;  //��������� ��������� �������
		LabelRes[q]->Height=17;
		LabelRes[q]->Top=TableTop;
		TableTop+=17;
		LabelRes[q]->Left=5;
		LabelRes[q]->Align=alTop;
		LabelRes[q]->Caption=String(L"����������� �������� � ���������, ���: ")+ (double)DCoefQuanGrid[q];
		TableRes[q]=new TStringGrid(ScrollBoxRes);    //�������� �������
		TableRes[q]->Parent = ScrollBoxRes;           //��������� ��������� �������
		TableRes[q]->ColCount=DCapacityGrid.Length+1;
		TableRes[q]->Options<<goThumbTracking;
		TableRes[q]->RowCount=DNumDoorsGrid.Length+1;
		TableRes[q]->Height=73;
		TableRes[q]->Top=TableTop;
		TableTop+=73;
		TableRes[q]->Left=5;
		TableRes[q]->ColWidths[0]=75;
		TableRes[q]->Align=alTop;
		TableRes[q] -> Cells[0][0]=L"K��\\\u03A9";
		FMax = DBL_MIN;
		for (int i = 0; i < DCapacityGrid.Length; i++)            //���������� ������� ��������
			TableRes[q]-> Cells[i+1][0] = DCapacityGrid[i];
		for (int i = 0; i < DNumDoorsGrid.Length; i++) {           //������ ������
			double res;
			TableRes[q]-> Cells[0][i+1] = DNumDoorsGrid[i];        //���������� ������� �����
			for (int j = 0; j < DCapacityGrid.Length; j++) {
				res = 2.56*sqrt(MinInterval)+(((double)DCapacityGrid[j]*DCoefQuanGrid[q]*TimeIE)/DNumDoorsGrid[i])+3; //������ ����������
				TableRes[q]-> Cells[j+1][i+1] = round(res*100)/100;	  //������ ���������� � ������� � �����������
				if (FMax<res)                              //����� �������������� ��������
					FMax=res;
			}
		}
	}
	NumChart = 0;
	PaintChart(NumChart);
	BNextChart -> Enabled = true;
    BPrevChart -> Enabled = false;
}

//---------------------------------------------------------------------------
bool __fastcall TMainForm::PaintChart(int NumChart) {       //��������� �������
	if (TableRes.Length == 0) {
        return false;
	}
	Charts -> Picture->Assign( NULL );
	PatBlt(Charts -> Canvas -> Handle, 0, 0, Charts->Width, Charts->Height, WHITENESS);
	double a =0* M_PI/180,b=252* M_PI/180,c=15* M_PI/180 ; //���� �������� ��� ���������
	double l1 = cos(a) * cos(c) - cos(b) * sin(a) * sin(c);   //���������� ��� ��������
	double l2 = -cos(a) * sin(c) + cos(b) * sin(a) * cos(c);
	double l3 = sin(b) * sin(a);
	double m1 = sin(a) * cos(c) + cos(b) * cos(a) * sin(c);
	double m2 = -sin(a) * sin(c) + cos(b) * cos(a) * cos(c);
	double m3 = -sin(b) * cos(a);
	int OMax = INT_MIN;
	int KMax = INT_MIN;
	for (int i=1; i < TableRes[NumChart]->ColCount; i++)               //����� ������������ ���������
		if (OMax<StrToInt(TableRes[NumChart]-> Cells[i][0]))
			OMax = StrToInt(TableRes[NumChart]-> Cells[i][0]);
	for (int i=1; i < TableRes[NumChart]->RowCount; i++)
		if (KMax<StrToInt(TableRes[NumChart]-> Cells[0][i]))
			KMax = StrToInt(TableRes[NumChart]-> Cells[0][i]);
	KMax*=5;
	double CoefX = (Charts->Width-20)/(OMax + KMax/2);     //������������ ������� ��� ������� ���������
	double CoefY = (Charts->Height-20)/(FMax + KMax/2);
	double CordN=KMax/2;                    //������ ���������
	Charts -> Canvas -> Pen -> Color = (TColor)RGB(0,0,0);
	Charts -> Canvas -> Pen -> Width  = 1;
	int H = Charts->Height;
	Charts -> Canvas -> MoveTo(10+(CordN)*CoefX,H-(10+(CordN)*CoefY));
	Charts -> Canvas -> LineTo(10+(CordN+OMax*l1)*CoefX,H-(10+(CordN+m1*OMax)*CoefY));
	Charts -> Canvas -> MoveTo(10+(CordN)*CoefX,H-(10+(CordN)*CoefY));
	Charts -> Canvas -> LineTo(10+(CordN+KMax*l2)*CoefX,H-(10+(CordN+m2*KMax)*CoefY));
	Charts -> Canvas -> MoveTo(10+(CordN)*CoefX,H-(10+(CordN)*CoefY));
	Charts -> Canvas -> LineTo(10+(CordN+FMax*l3)*CoefX,H-(10+(CordN+m3*FMax)*CoefY));
	Charts -> Canvas -> Pen -> Color = (TColor)RGB(255,0,0);
	LChart -> Caption = LabelRes[NumChart]->Caption;
	for (int i=1; i < TableRes[NumChart]->ColCount; i++) {                      //��������� �������
		Charts -> Canvas -> MoveTo(10+(CordN+StrToInt(TableRes[NumChart]-> Cells[i][0])*l1+StrToInt(TableRes[NumChart]-> Cells[0][1])*5*l2+StrToFloat(TableRes[NumChart]-> Cells[i][1])*l3)*CoefX,H-(10+(CordN+StrToInt(TableRes[NumChart]-> Cells[i][0])*m1+StrToInt(TableRes[NumChart]-> Cells[0][1])*5*m2+StrToFloat(TableRes[NumChart]-> Cells[i][1])*m3)*CoefY));
		for (int j = 2;j < TableRes[NumChart]->RowCount; j++) {
			Charts -> Canvas -> LineTo(10+(CordN+StrToInt(TableRes[NumChart]-> Cells[i][0])*l1+StrToInt(TableRes[NumChart]-> Cells[0][j])*5*l2+StrToFloat(TableRes[NumChart]-> Cells[i][j])*l3)*CoefX,H-(10+(CordN+StrToInt(TableRes[NumChart]-> Cells[i][0])*m1+StrToInt(TableRes[NumChart]-> Cells[0][j])*5*m2+StrToFloat(TableRes[NumChart]-> Cells[i][j])*m3)*CoefY));
		}
	}
	for (int i=1; i < TableRes[NumChart]->RowCount; i++) {                      //��������� �������
		Charts -> Canvas -> MoveTo(10+(CordN+StrToInt(TableRes[NumChart]-> Cells[1][0])*l1+StrToInt(TableRes[NumChart]-> Cells[0][i])*5*l2+StrToFloat(TableRes[NumChart]-> Cells[1][i])*l3)*CoefX,H-(10+(CordN+StrToInt(TableRes[NumChart]-> Cells[1][0])*m1+StrToInt(TableRes[NumChart]-> Cells[0][i])*5*m2+StrToFloat(TableRes[NumChart]-> Cells[1][i])*m3)*CoefY));
		for (int j = 2;j < TableRes[NumChart]->ColCount; j++) {
			Charts -> Canvas -> LineTo(10+(CordN+StrToInt(TableRes[NumChart]-> Cells[j][0])*l1+StrToInt(TableRes[NumChart]-> Cells[0][i])*5*l2+StrToFloat(TableRes[NumChart]-> Cells[j][i])*l3)*CoefX,H-(10+(CordN+StrToInt(TableRes[NumChart]-> Cells[j][0])*m1+StrToInt(TableRes[NumChart]-> Cells[0][i])*5*m2+StrToFloat(TableRes[NumChart]-> Cells[j][i])*m3)*CoefY));
		}
	}
    return true;
}

void __fastcall TMainForm::BNextChartClick(TObject *Sender)            //������� ������ ��������� ������
{
	BPrevChart->Enabled=true;                                          //�������� ������ ���������� ������
	NumChart++;                                                        //��������� ������ �������
	if (NumChart==TableRes.Length-1)                                   //���������� ������
		BNextChart -> Enabled = false;
	PaintChart(NumChart);                                              //��������� �������
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::BPrevChartClick(TObject *Sender)
{
	NumChart--;                                                    //��������� ������ �������
	BNextChart -> Enabled = true;                                  //�������� ������ ��������� ������
	if (NumChart == 0)                                             //���������� ������
		BPrevChart -> Enabled = false;
	PaintChart(NumChart);                                          //��������� �������
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::FormResize(TObject *Sender)              //��������� ������� �����
{
	CapacityGrid->Width = MainForm -> ClientWidth - 16;             //������������� ������� ���������
	NumDoorsGrid->Width = MainForm -> ClientWidth - 16;
	CoefQuanGrid->Width = MainForm -> ClientWidth - 16;
	ScrollBoxRes->Height = MainForm -> ClientHeight - 506;
	ScrollBoxRes->Width = (MainForm -> ClientWidth - 32)/2;
	Charts->Width = (MainForm -> ClientWidth - 32)/2;
	LChart->Left = ScrollBoxRes->Width+22;
	Charts->Left = ScrollBoxRes->Width+22;
	Charts->Height = MainForm -> ClientHeight - 560;
	BPrevChart->Left = ScrollBoxRes->Width+22;
	BPrevChart->Top = MainForm -> ClientHeight-57;
	BNextChart->Left = MainForm -> ClientWidth- 152;
	BNextChart->Top = MainForm -> ClientHeight-57;
    PaintChart(NumChart);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::MCreateClick(TObject *Sender)         //������ �������
{
	if (!CheckChangeData()) //�������� ������� ������������ ���������
		return;
    Charts -> Picture->Assign( NULL );//�������� ������ ����������� ���������
	if (TableRes.Length!=0) {
		for (int i=0; i < TableRes.Length; i++) {
			TableRes[i]->Free();
			LabelRes[i]->Free();
		}
	}
	TableRes.Length=0;
	LabelRes.Length=0;
	MSave->Enabled= false;
	MDelCapacity -> Enabled = false;
	MDelNumDoors -> Enabled = false;
	MDelCoefQuan -> Enabled = false;
	BPrevChart -> Enabled = false;
	BNextChart -> Enabled = false;
	MainForm->Caption=String(Application->Title)+L" - "+DefFileName;
	CapacityGrid -> ColCount = 2;                   //��������� ��������� �������� ������
	CapacityGrid -> Cells[1][1] = L"";
	NumDoorsGrid -> ColCount = 2;
	NumDoorsGrid -> Cells[1][1] = L"";
	CoefQuanGrid -> ColCount = 2;
	CoefQuanGrid -> Cells[1][1] = L"";
	ETimeIE -> Text=L"";                                   //��������� ��������� �������� ����� �����
	EMinInterval -> Text=L"";
	LChart->Caption = L"";                                 //��������� ���������� ��������� ������� �������
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::MCloseClick(TObject *Sender)         //������� �� ����� �����
{
    Close();                                                   //�������� ���������
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormCloseQuery(TObject *Sender, bool &CanClose)  //�������� ���������
{
	if (!CheckChangeData()){   //�������� ������� ������������ ���������
		CanClose=false;                                             //������ ��������
		return;
	}
	TableRes.Length=0;//������������ ��������
	LabelRes.Length=0;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::IntGridKeyPress(TObject *Sender, System::WideChar &Key)  //������� ������ �� ���������� � ������� ��� �����

{
	if (!MSave->Enabled) {                              //�������� ������� ����������� ���������
		MSave->Enabled= true;                           //��������� ������ ��������� (������� ������� ������������ ���������)
		MainForm->Caption+=L"*";                        //���������� �������� � ��������� ���������
	}
	if (!((Key >= '0' && Key <= '9') || (int)Key == 3 || (int)Key == 8 ||  (int)Key == 13 || (int)Key == 22 || (int)Key == 24 || (int)Key == 26)) {   //�������� �� ������������ ��������� �������
		StatusBar -> SimpleText=String(L"������ ������������ ������ \"") + Key + L"\"";     //����� ��������� � ������ ���
		Key = 0;                                                                            //������ �����
		return;
	}
	StatusBar -> SimpleText = L"";
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::DoubleKeyPress(TObject *Sender, System::WideChar &Key)    //������� ������ �� ���������� � ������� ������� � ����� ����� ��� �����

{
	if (!MSave->Enabled) {                              //�������� ������� ����������� ���������
		MSave->Enabled= true;                           //��������� ������ ��������� (������� ������� ������������ ���������)
		MainForm->Caption+=L"*";                        //���������� �������� � ��������� ���������
	}
	if (!((Key >= '0' && Key <= '9') || (int)Key == 3 || (int)Key == 8 ||(int)Key == 44 ||  (int)Key == 13 || (int)Key == 22 || (int)Key == 24 || (int)Key == 26)) {   //�������� �� ������������ ��������� �������
		StatusBar -> SimpleText=String(L"������ ������������ ������ \"") + Key + L"\"";     //����� ��������� � ������ ���
		Key = 0;                                                                            //������ �����
		return;
	}
	StatusBar -> SimpleText = L"";
}
//---------------------------------------------------------------------------

