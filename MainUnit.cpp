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
void __fastcall TMainForm::FormCreate(TObject *Sender)     //созадние формы
{
	CapacityGrid -> Cells[0][0] = L"№";              //установка начальных состояний
	CapacityGrid -> Cells[1][0] = L"1";
	CapacityGrid -> Cells[0][1] = L"\u03A9";
	NumDoorsGrid -> Cells[0][0] = L"№";
	NumDoorsGrid -> Cells[1][0] = L"1";
	NumDoorsGrid -> Cells[0][1] = L"Кдв";
	CoefQuanGrid -> Cells[0][0] = L"№";
	CoefQuanGrid -> Cells[1][0] = L"1";
	CoefQuanGrid -> Cells[0][1] = L"Квв";
	MSave->Enabled= false;
	MDelCapacity -> Enabled = false;
	MDelNumDoors -> Enabled = false;
	MDelCoefQuan -> Enabled = false;
	BPrevChart -> Enabled = false;
	BNextChart -> Enabled = false;
	MainForm->Caption=String(Application->Title)+L" - "+DefFileName;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::AddCol(TStringGrid *Grid, TMenuItem *MDel) { //добавление столбцов в таблицах
	Grid->ColCount++;                          //добавление столбца
	Grid->Cells[Grid->ColCount-1][0]=Grid->ColCount-1;  //запись подписи дабавленого столбца
	Grid->Cells[Grid->ColCount-1][1]=L"";               //очистка добавленой ячейки
	MDel -> Enabled = true;                             //включение кнопки удаления столбцах
	if (!MSave->Enabled) {                              //проверка наличия несхраненых уименений
		MSave->Enabled= true;                           //включение кнопки сохранить (признак наличия несохраненых изменений)
		MainForm->Caption+=L"*";                        //добавление признака в заголовок программы
	}
}

void __fastcall TMainForm::DelCol(TStringGrid *Grid, TMenuItem *MDel) { //удаление столбцов таблицы
	if (Grid->ColCount <=2)                             //проверка возможности удаления столбца
		return;
	Grid->ColCount--;                                   //удаление столбца
	if (Grid -> ColCount == 2)
		MDel -> Enabled = false;                        //откючение кнопки удаления
	if (!MSave->Enabled) {                              //проверка наличия несхраненых уименений
		MSave->Enabled= true;                           //включение кнопки сохранить (признак наличия несохраненых изменений)
		MainForm->Caption+=L"*";                        //добавление признака в заголовок программы
	}
}

void __fastcall TMainForm::MAddCapacityClick(TObject *Sender)    //добавление столбца в 1 тпблице
{
	AddCol(CapacityGrid, MDelCapacity);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::MDelCapacityClick(TObject *Sender)    //удаление столбца в 1 таблице
{
	DelCol(CapacityGrid,MDelCapacity);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::MAddNumDoorsClick(TObject *Sender)   //добавление столбца в 2 таблице
{
	AddCol(NumDoorsGrid, MDelNumDoors);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::MDelNumDoorsClick(TObject *Sender)   //удаление столбца в 2 таблице
{
    DelCol(NumDoorsGrid, MDelNumDoors);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::MAddCoefQuanClick(TObject *Sender)    //добавление столбца в 3 таблице
{
	AddCol(CoefQuanGrid, MDelCoefQuan);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::MDelCoefQuanClick(TObject *Sender)    //удаление столбца в 3 таблице
{
    DelCol(CoefQuanGrid, MDelCoefQuan);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::MSaveClick(TObject *Sender)   //нажатие на кнопку сохранить
{
	if (!CheckSourData(true))                         //проверка данных для сохранения
		return;
	String OldFN = SaveFileDialog->FileName;          //сохарнение старого имени файла
	if (SaveFileDialog -> FileName==L"") {            //если файл не открыт
		SaveFileDialog->FileName=DefFileName;         //запись начального имени файла
		if (!SaveFileDialog->Execute()) {             //вызов диалога сохранения
			SaveFileDialog->FileName=OldFN;           //возврашение старого имени файла
			return;
		}
	}
	if (!SaveSourData()) {                              //сохарнение данных
		SaveFileDialog->FileName=OldFN;                //возврашение старого имени файла
		return;
	}
	MSave->Enabled= false;                           //выключение кнопки сохранить (признак наличия несохраненых изменений)
	MainForm->Caption=String(Application->Title)+L" - "+ExtractFileName(SaveFileDialog->FileName); //запись имени файла в заголовок
}
//---------------------------------------------------------------------------
bool __fastcall TMainForm::CheckSourData(bool ForSave) {  //проверка данных на корректность и допустимость
	String ErrMess = L"";                                //переменная для сообщения об ошибке
	for (int i =1; i < CapacityGrid -> ColCount; i++) {   //перебор значений 1 таблицы
		int TestValue;
			if (!(CapacityGrid -> Cells[i][1]==L""&&ForSave) && !TryStrToInt(CapacityGrid -> Cells[i][1], TestValue)||TestValue<0) {  //проверка занчений 1 таблицы
				if (ErrMess == "")     //формирование сообщения об ошибки
					ErrMess=String(L"Некорректные или недопустимые занчения вместимости транспорта №: ") + i;
				else
					ErrMess+=String(L", ")+i;
			}
	}
	if (ErrMess != "")
		ErrMess += L". ";
	bool NotErr = true;
	for (int i =1; i < NumDoorsGrid -> ColCount; i++) {     //перебор значений 2 таблицы
		int TestValue;
			if (!(NumDoorsGrid -> Cells[i][1]==L""&&ForSave) && !TryStrToInt(NumDoorsGrid -> Cells[i][1], TestValue)||TestValue<0) {  //проверка занчений 2 таблицы
				if (NotErr) {          //формирование сообщения об ошибки
					NotErr = false;
					ErrMess+=String(L"Некорректные или недопустимые занчения числа дверей №: ") + i;
				}
				else
					ErrMess+=String(L", ")+i;
			}
	}
	if (!NotErr) {              //формирование сообщения об ошибки
		ErrMess += L". ";
		NotErr = true;
	}
	for (int i =1; i < CoefQuanGrid -> ColCount; i++) {     //перебор значений 3 таблицы
		float TestValue;
			if (!(CoefQuanGrid -> Cells[i][1]==L""&&ForSave) && !TryStrToFloat(CoefQuanGrid -> Cells[i][1], TestValue)||TestValue<0) {     //проверка занчений 3 таблицы
				if (NotErr) {          //формирование сообщения об ошибки
					NotErr = false;
					ErrMess+=String(L"Некорректные или недопустимые занчения коэффициента выхода и входа №: ") + i;
				}
				else
					ErrMess+=String(L", ")+i;
			}
	}
	if (!NotErr) {             //формирование сообщения об ошибки
		ErrMess += L". ";
		NotErr = true;
	}
	float TestValue;
	if (!(ETimeIE->Text==L""&&ForSave) && (!TryStrToFloat(ETimeIE->Text, TestValue)||TestValue<0)) {   //проверка значения в 1 поле ввода
		NotErr = false;
		ErrMess+=L"Некорректные или недопустимое значение: времени выхода и входа";  //формирование сообщения об ошибки
	}
	if (!(EMinInterval->Text==L""&&ForSave) && (!TryStrToFloat(EMinInterval->Text, TestValue)||TestValue<0)) {     //проверка значения в 2 поле ввода
		if (NotErr) {                                                       //формирование сообщения об ошибки
			NotErr = false;
			ErrMess+=L"Некорректные или недопустимое значение: минимального интервала.";
		}
		else
			ErrMess+=L", минимального интервала.";
	}
	if (ErrMess != "") {                  //если были найдены ошибки
		StatusBar->SimpleText=ErrMess;    //вывод теста ошибки в статус бар
		Application->MessageBox(ErrMess.w_str(),Application->Title.w_str(), MB_OK|MB_ICONEXCLAMATION); //вывод текста ошибки в модальное окно
		return false;        //завершение с ошибками
	}
	return true;            //завершение без ошибок
}

bool __fastcall TMainForm::SaveSourData() { //сохранение данных в файл
	DynamicArray<int> DCapacityGrid;       //объявление массивов
	DynamicArray<int> DNumDoorsGrid;
	DynamicArray<double> DCoefQuanGrid;
	try {
		DCapacityGrid.Length=CapacityGrid -> ColCount-1;        //выделение памяти под массивы
		DNumDoorsGrid.Length=NumDoorsGrid -> ColCount-1;
		DCoefQuanGrid.Length=CoefQuanGrid -> ColCount-1;
	} catch (...) {                               //если было вызвано исключение
		DCapacityGrid.Length=0;                   //освобождение памяти из-под массива
		DNumDoorsGrid.Length=0;
		DCoefQuanGrid.Length=0;
		Application->MessageBox(L"Не хватает оперативной памяти, для сохранения данных!",Application->Title.w_str(),  //вывод текста ошибки в модальное окно
									MB_OK|MB_ICONEXCLAMATION);
		return false;    //завершение с ошибкой
	}
	for (int i=0; i < CapacityGrid -> ColCount-1; i++) {      //запись данных из 1 таблице в массив
		if (CapacityGrid -> Cells[i+1][1]==L"")
			DCapacityGrid[i]=INT_MIN;                    //если ячейка пустая, то запись минимального значения
		else
			TryStrToInt(CapacityGrid -> Cells[i+1][1],DCapacityGrid[i]);
	}
	for (int i=0; i < NumDoorsGrid -> ColCount-1; i++) {      //запись данных из 2 таблице в массив
		if (NumDoorsGrid -> Cells[i+1][1]==L"")
			DNumDoorsGrid[i]=INT_MIN;                    //если ячейка пустая, то запись минимального значения
		else
			TryStrToInt(NumDoorsGrid -> Cells[i+1][1],DNumDoorsGrid[i]);
	}
	for (int i=0; i < CoefQuanGrid -> ColCount-1; i++) {      //запись данных из 3 таблице в массив
		if (CoefQuanGrid -> Cells[i+1][1]==L"")
			DCoefQuanGrid[i]=INT_MIN;                    //если ячейка пустая, то запись минимального значения
		else
			TryStrToFloat(CoefQuanGrid -> Cells[i+1][1],DCoefQuanGrid[i]);
	}
	double DataEdit;                    //инициализация вспомогательных элементов
	int ColCount;
	unsigned int CountByte = sizeof(CountByte)+ sizeof(ColCount)*3+(CapacityGrid -> ColCount-1)*sizeof(DCapacityGrid[0])+  //посчет будущего размера файла для провеки целостности при чтении
							  (NumDoorsGrid -> ColCount-1)*sizeof(DNumDoorsGrid[0])+ (CoefQuanGrid -> ColCount-1)*sizeof(DCoefQuanGrid[0])+
								sizeof(DataEdit)*2;
	std::fstream file;
	file.open(AnsiString(SaveFileDialog->FileName).c_str(), std::ios::out | std::ios::binary);  //создание файла для сохранения
	if (!file) {                                 //если неудалось создать файл
		DCapacityGrid.Length=0;                   //освобождение памяти из-под массива
		DNumDoorsGrid.Length=0;
		DCoefQuanGrid.Length=0;
		Application->MessageBox((String(L"Не удалось создать файл \"")+SaveFileDialog->FileName+"\"!").w_str(),Application->Title.w_str(),   //вывод текста ошибки в модальное окно
								MB_OK|MB_ICONERROR);
		return false;      //завершение с ошибкой
	}
	file.write((char*)&CountByte, sizeof(CountByte)); //запись в файл размера файла
	ColCount = CapacityGrid -> ColCount-1;
	file.write((char*)&ColCount, sizeof(ColCount)); //запись в файл размера 1 таблицы
	ColCount = NumDoorsGrid -> ColCount-1;
	file.write((char*)&ColCount, sizeof(ColCount)); //запись в файл размера 2 таблицы
	ColCount = CoefQuanGrid -> ColCount-1;
	file.write((char*)&ColCount, sizeof(ColCount)); //запись в файл размера 3 таблицы
	file.write((char*)&DCapacityGrid[0], sizeof(DCapacityGrid[0])*(CapacityGrid -> ColCount-1));  //запись данных 1 таблицы
	DCapacityGrid.Length=0;                                                   //освобождение памяти из-под 1 массива
	file.write((char*)&DNumDoorsGrid[0], sizeof(DNumDoorsGrid[0])*(NumDoorsGrid -> ColCount-1));  //запись данных 2 таблицы
	DNumDoorsGrid.Length=0;                                                   //освобождение памяти из-под 2 массива
	file.write((char*)&DCoefQuanGrid[0], sizeof(DCoefQuanGrid[0])*ColCount);  //запись данных 3 таблицы
	DCoefQuanGrid.Length=0;                                                   //освобождение памяти из-под 3 массива
	if (ETimeIE->Text==L"")                         //запись данных 1 поля ввода
		DataEdit=DBL_MIN;
	else
		TryStrToFloat(ETimeIE->Text, DataEdit);
	file.write((char*)&DataEdit, sizeof(DataEdit));
	if (EMinInterval->Text==L"")                   //запись данных 2 поля ввода
		DataEdit=DBL_MIN;
	else
		TryStrToFloat(EMinInterval->Text, DataEdit);
	file.write((char*)&DataEdit, sizeof(DataEdit));
	file.close();                                   //закрытие файла
	return true;       //завершение с ошибкой без ошибки
}

void __fastcall TMainForm::MSaveAsClick(TObject *Sender)
{
	if (!CheckSourData(true))                         //проверка данных для сохранения
		return;
	String OldFN = SaveFileDialog->FileName;          //сохарнение старого имени файла
	SaveFileDialog->FileName=DefFileName;         //запись начального имени файла
	if (!SaveFileDialog->Execute()) {             //вызов диалога сохранения
		SaveFileDialog->FileName=OldFN;           //возврашение старого имени файла
		return;
	}
	if (!SaveSourData()) {                              //сохарнение данных
		SaveFileDialog->FileName=OldFN;                //возврашение старого имени файла
		return;
	}
	MSave->Enabled= false;                           //выключение кнопки сохранить (признак наличия несохраненых изменений)
	MainForm->Caption=String(Application->Title)+L" - "+ExtractFileName(SaveFileDialog->FileName); //запись имени файла в заголовок
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::MOpenClick(TObject *Sender)        //открыте файла
{
	if (!CheckChangeData()) //проверка наличия несохраненых изменений
		return;
	if (!OpenFileDialog->Execute())     //вызов диалога открытия
		return;
	unsigned int CountByte;
	std::fstream file;
	file.open(AnsiString(OpenFileDialog->FileName).c_str(), std::ios::in | std::ios::binary);              //открытие файла
	if (!file) {                                                                                //если не удалось открыть файл
		Application->MessageBox((String(L"Не удалось открыть файл \"")+OpenFileDialog->FileName+"\"!").w_str(),Application->Title.w_str(), MB_OK|MB_ICONERROR); //вывод текста ошибки в модальное окно
		return;
	}
	file.read((char*)&CountByte, sizeof(CountByte));   //чтение размера файла при записи
	file.seekg(0, std::ios::end);                          //установка указателя в конец файла
	file.clear();
	if (CountByte != file.tellg()){                   //проверка на целастность файла
		file.close();
		Application->MessageBox((String(L"Не удалось загрузить данные из файла \"")+OpenFileDialog->FileName+"\". Файл поврежден.").w_str(), Application->Title.w_str(), MB_OK|MB_ICONERROR);  //вывод текста ошибки в модальное окно
		return;
	}
	file.clear();
	file.seekg(sizeof(CountByte));      //установка указателя после размера файла
	int ColCount1,ColCount2,ColCount3;
	file.read((char*)&ColCount1, sizeof(ColCount1));//чтение размера таблицы 1
	file.read((char*)&ColCount2, sizeof(ColCount2));//чтение размера таблицы 1 
	file.read((char*)&ColCount3, sizeof(ColCount3));//чтение размера таблицы 1  
	DynamicArray<int> DCapacityGrid;       //объявление массивов
	DynamicArray<int> DNumDoorsGrid;
	DynamicArray<double> DCoefQuanGrid;
	try {
		DCapacityGrid.Length=ColCount1;        //выделение памяти под массивы
		DNumDoorsGrid.Length=ColCount2;
		DCoefQuanGrid.Length=ColCount3;
	} catch (...) {                               //если было вызвано исключение
		DCapacityGrid.Length=0;                   //освобождение памяти из-под массива
		DNumDoorsGrid.Length=0;
		DCoefQuanGrid.Length=0;
		Application->MessageBox(L"Не хватает оперативной памяти, для сохранения данных!",Application->Title.w_str(),  //вывод текста ошибки в модальное окно
									MB_OK|MB_ICONEXCLAMATION);
		return;
	}
	file.read((char*)&DCapacityGrid[0], sizeof(DCapacityGrid[0])*ColCount1);        //чтение данных таблицы 1
	CapacityGrid->ColCount=ColCount1+1;                                             //установка размера таблицы 1
	for (int i=0; i < ColCount1; i++) {                                             //запись данныз таблицы 1
		CapacityGrid -> Cells[i+1][0]=i+1;
		if (DCapacityGrid[i]==INT_MIN)
			CapacityGrid -> Cells[i+1][1]=L"";
		else
			CapacityGrid -> Cells[i+1][1]=DCapacityGrid[i];
	}
	DCapacityGrid.Length=0;                                                        //освобождение данных из-под массива
	file.read((char*)&DNumDoorsGrid[0], sizeof(DNumDoorsGrid[0])*ColCount2);       //чтение данных таблицы 2
	NumDoorsGrid->ColCount=ColCount2+1;                                            //установка размера таблицы 2
	for (int i=0; i < ColCount2; i++) {                                            //запись данныз таблицы 2
		NumDoorsGrid -> Cells[i+1][0]=i+1;
		if (DNumDoorsGrid[i]==INT_MIN)
			NumDoorsGrid -> Cells[i+1][1]=L"";
		else
			NumDoorsGrid -> Cells[i+1][1]=DNumDoorsGrid[i];
	}
	DNumDoorsGrid.Length=0;                                                      //освобождение данных из-под массива
	file.read((char*)&DCoefQuanGrid[0], sizeof(DCoefQuanGrid[0])*ColCount3);     //чтение данных таблицы 3
	CoefQuanGrid->ColCount=ColCount3+1;                                          //установка размера таблицы 3
	for (int i=0; i < ColCount3; i++) {                                          //запись данныз таблицы 3
		CoefQuanGrid -> Cells[i+1][0]=i+1;
		if (DCoefQuanGrid[i]==DBL_MIN)
			CoefQuanGrid -> Cells[i+1][1]=L"";
		else
			CoefQuanGrid -> Cells[i+1][1]=DCoefQuanGrid[i];
	}
	DCapacityGrid.Length=0;                                                       //освобождение данных из-под массива
	double DataEdit;
	file.read((char*)&DataEdit, sizeof(DataEdit));                                //чтение данных поля ввода 1
	if (DataEdit==DBL_MIN)                                                        //запись данных в поле ввода 1
		ETimeIE->Text=L"";
	else
		ETimeIE->Text=DataEdit;
	file.read((char*)&DataEdit, sizeof(DataEdit));                                 //чтение данных поля ввода 2
	file.close();                                                                  //закрытие файла
	if (DataEdit==DBL_MIN)                                                         //запись данных в поле ввода 2
		EMinInterval->Text=L"";
	else
		EMinInterval->Text=DataEdit;
	//ClearOldResults();                                                           //очистка результатов
	if (CapacityGrid -> ColCount>2)                                                    //отключение (включение) кнопок удаления столбцов
		MDelCapacity->Enabled=true;
	else
		MDelCapacity->Enabled=false;
	if (CapacityGrid -> ColCount>2)                                                    //отключение (включение) кнопок удаления столбцов
		MDelNumDoors->Enabled=true;
	else
		MDelNumDoors->Enabled=false;
	if (CoefQuanGrid -> ColCount>2)                                                    //отключение (включение) кнопок удаления столбцов
		MDelCoefQuan->Enabled=true;
	else
		MDelCoefQuan->Enabled=false; 
	SaveFileDialog->FileName=OpenFileDialog->FileName;                           //сохранение имени файла
	MSave->Enabled= false;                           //выключение кнопки сохранить (признак наличия несохраненых изменений)
	MainForm->Caption=String(Application->Title)+L" - "+ExtractFileName(SaveFileDialog->FileName); //запись имени файла в заголовок
	Charts -> Picture->Assign( NULL );//удаление старых результатов обработки
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

bool __fastcall TMainForm::CheckChangeData() {       //проверка наличия несохраненых изменений
	if (MSave->Enabled) {                            //проверка наличия несохраненых изменений
		String OldFN=SaveFileDialog->FileName;       //сохранение имени открытого файла
		if (OldFN==L"") {
			OldFN=DefFileName;                    //запись дефолтного имени файла
		}
		switch (Application->MessageBox((String(L"Присутствуют не сохраненые изменения. Сохранить изменения в файле \"")+   //вывод модального окна с выбором
									OldFN+"\"?").w_str(),
									Application->Title.w_str(), MB_YESNOCANCEL|MB_ICONQUESTION)){
			case mrCancel:                     //нажатие отмена
				return false;                  //выход с запретом дальнейших действий
			case mrNo:
				return true;                    //выход с разрешением дальнейших действий
			case mrYes:
				if (!CheckSourData(true))                         //проверка данных для сохранения
					return false;
				if (SaveFileDialog -> FileName==L"") {            //если файл не открыт
					SaveFileDialog->FileName=DefFileName;         //запись начального имени файла
					if (!SaveFileDialog->Execute()) {             //вызов диалога сохранения
						SaveFileDialog->FileName=L"";           //возврашение старого имени файла
						return false;                  //выход с запретом дальнейших действий
					}
                    OldFN = L"";
				}
				if (!SaveSourData()) {                              //сохарнение данных
					SaveFileDialog->FileName=OldFN;                //возврашение старого имени файла
					return false;                  //выход с запретом дальнейших действий
				}
				break;
		}
	}
	return true;      //выход с разрешением дальнейших действий
}


void __fastcall TMainForm::BCalcDataClick(TObject *Sender)
{
	if (!CheckSourData(false))                         //проверка данных для обработки
		return;	
	if (TableRes.Length!=0) {//удаление старых результатов обработки
		for (int i=0; i < TableRes.Length; i++) {
			TableRes[i]->Free();
			LabelRes[i]->Free();
		}
	}
	DynamicArray<int> DCapacityGrid;       //объявление массивов
	DynamicArray<int> DNumDoorsGrid;
	DynamicArray<double> DCoefQuanGrid;
	try{
		DCapacityGrid.Length=CapacityGrid -> ColCount-1;        //выделение памяти под массивы
		DNumDoorsGrid.Length=NumDoorsGrid -> ColCount-1;
		DCoefQuanGrid.Length=CoefQuanGrid -> ColCount-1;
		TableRes.Length=CoefQuanGrid -> ColCount-1;
		LabelRes.Length=CoefQuanGrid -> ColCount-1;
	}
	catch(...){//обработка исключений
		DCapacityGrid.Length=0;                   //освобождение памяти из-под массива
		DNumDoorsGrid.Length=0;
		DCoefQuanGrid.Length=0;
		TableRes.Length=0;
		LabelRes.Length=0;
		Application->MessageBox(L"Не хватает оперативной памяти для обработки данных",Application->Title.w_str(),  //вывод текста ошибки в модальное окно
								MB_OK|MB_ICONEXCLAMATION);
		return;
	}
	for (int i = 0; i < CapacityGrid -> ColCount-1; i++)            //считываение двнных для обработки
		DCapacityGrid[i] = StrToInt(CapacityGrid->Cells[i+1][1]);
	for (int i = 0; i < NumDoorsGrid -> ColCount-1; i++)
		DNumDoorsGrid[i] = StrToInt(NumDoorsGrid->Cells[i+1][1]);
	for (int i = 0; i < CoefQuanGrid -> ColCount-1; i++)
		DCoefQuanGrid[i] = StrToFloat(CoefQuanGrid->Cells[i+1][1]);		
	int TableTop=5;
	double TimeIE = StrToFloat(ETimeIE->Text);          //считывание полей ввода
	double MinInterval = StrToFloat(EMinInterval->Text);
	for (int q = 0; q < CoefQuanGrid -> ColCount-1; q++) {
		LabelRes[q]=new TLabel(ScrollBoxRes);//создание подписи к таблице
		LabelRes[q]->Parent = ScrollBoxRes;  //начальные настройки подписи
		LabelRes[q]->Height=17;
		LabelRes[q]->Top=TableTop;
		TableTop+=17;
		LabelRes[q]->Left=5;
		LabelRes[q]->Align=alTop;
		LabelRes[q]->Caption=String(L"Коэффициент входящих и выходящих, Квв: ")+ (double)DCoefQuanGrid[q];
		TableRes[q]=new TStringGrid(ScrollBoxRes);    //создание таблицы
		TableRes[q]->Parent = ScrollBoxRes;           //начальные настройки тадлицы
		TableRes[q]->ColCount=DCapacityGrid.Length+1;
		TableRes[q]->Options<<goThumbTracking;
		TableRes[q]->RowCount=DNumDoorsGrid.Length+1;
		TableRes[q]->Height=73;
		TableRes[q]->Top=TableTop;
		TableTop+=73;
		TableRes[q]->Left=5;
		TableRes[q]->ColWidths[0]=75;
		TableRes[q]->Align=alTop;
		TableRes[q] -> Cells[0][0]=L"Kдв\\\u03A9";
		FMax = DBL_MIN;
		for (int i = 0; i < DCapacityGrid.Length; i++)            //заполнение подписи столбцов
			TableRes[q]-> Cells[i+1][0] = DCapacityGrid[i];
		for (int i = 0; i < DNumDoorsGrid.Length; i++) {           //расчет данных
			double res;
			TableRes[q]-> Cells[0][i+1] = DNumDoorsGrid[i];        //заполнение подписи строк
			for (int j = 0; j < DCapacityGrid.Length; j++) {
				res = 2.56*sqrt(MinInterval)+(((double)DCapacityGrid[j]*DCoefQuanGrid[q]*TimeIE)/DNumDoorsGrid[i])+3; //расчет результата
				TableRes[q]-> Cells[j+1][i+1] = round(res*100)/100;	  //запись результата в таблицу с округлением
				if (FMax<res)                              //поиск макстимального значения
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
bool __fastcall TMainForm::PaintChart(int NumChart) {       //рисование графика
	if (TableRes.Length == 0) {
        return false;
	}
	Charts -> Picture->Assign( NULL );
	PatBlt(Charts -> Canvas -> Handle, 0, 0, Charts->Width, Charts->Height, WHITENESS);
	double a =0* M_PI/180,b=252* M_PI/180,c=15* M_PI/180 ; //углы поворота оси координат
	double l1 = cos(a) * cos(c) - cos(b) * sin(a) * sin(c);   //переменные для проекции
	double l2 = -cos(a) * sin(c) + cos(b) * sin(a) * cos(c);
	double l3 = sin(b) * sin(a);
	double m1 = sin(a) * cos(c) + cos(b) * cos(a) * sin(c);
	double m2 = -sin(a) * sin(c) + cos(b) * cos(a) * cos(c);
	double m3 = -sin(b) * cos(a);
	int OMax = INT_MIN;
	int KMax = INT_MIN;
	for (int i=1; i < TableRes[NumChart]->ColCount; i++)               //поиск максимальных элементов
		if (OMax<StrToInt(TableRes[NumChart]-> Cells[i][0]))
			OMax = StrToInt(TableRes[NumChart]-> Cells[i][0]);
	for (int i=1; i < TableRes[NumChart]->RowCount; i++)
		if (KMax<StrToInt(TableRes[NumChart]-> Cells[0][i]))
			KMax = StrToInt(TableRes[NumChart]-> Cells[0][i]);
	KMax*=5;
	double CoefX = (Charts->Width-20)/(OMax + KMax/2);     //коэффициенты маштаба для расчета координат
	double CoefY = (Charts->Height-20)/(FMax + KMax/2);
	double CordN=KMax/2;                    //начало координат
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
	for (int i=1; i < TableRes[NumChart]->ColCount; i++) {                      //Рисование графика
		Charts -> Canvas -> MoveTo(10+(CordN+StrToInt(TableRes[NumChart]-> Cells[i][0])*l1+StrToInt(TableRes[NumChart]-> Cells[0][1])*5*l2+StrToFloat(TableRes[NumChart]-> Cells[i][1])*l3)*CoefX,H-(10+(CordN+StrToInt(TableRes[NumChart]-> Cells[i][0])*m1+StrToInt(TableRes[NumChart]-> Cells[0][1])*5*m2+StrToFloat(TableRes[NumChart]-> Cells[i][1])*m3)*CoefY));
		for (int j = 2;j < TableRes[NumChart]->RowCount; j++) {
			Charts -> Canvas -> LineTo(10+(CordN+StrToInt(TableRes[NumChart]-> Cells[i][0])*l1+StrToInt(TableRes[NumChart]-> Cells[0][j])*5*l2+StrToFloat(TableRes[NumChart]-> Cells[i][j])*l3)*CoefX,H-(10+(CordN+StrToInt(TableRes[NumChart]-> Cells[i][0])*m1+StrToInt(TableRes[NumChart]-> Cells[0][j])*5*m2+StrToFloat(TableRes[NumChart]-> Cells[i][j])*m3)*CoefY));
		}
	}
	for (int i=1; i < TableRes[NumChart]->RowCount; i++) {                      //Рисование графика
		Charts -> Canvas -> MoveTo(10+(CordN+StrToInt(TableRes[NumChart]-> Cells[1][0])*l1+StrToInt(TableRes[NumChart]-> Cells[0][i])*5*l2+StrToFloat(TableRes[NumChart]-> Cells[1][i])*l3)*CoefX,H-(10+(CordN+StrToInt(TableRes[NumChart]-> Cells[1][0])*m1+StrToInt(TableRes[NumChart]-> Cells[0][i])*5*m2+StrToFloat(TableRes[NumChart]-> Cells[1][i])*m3)*CoefY));
		for (int j = 2;j < TableRes[NumChart]->ColCount; j++) {
			Charts -> Canvas -> LineTo(10+(CordN+StrToInt(TableRes[NumChart]-> Cells[j][0])*l1+StrToInt(TableRes[NumChart]-> Cells[0][i])*5*l2+StrToFloat(TableRes[NumChart]-> Cells[j][i])*l3)*CoefX,H-(10+(CordN+StrToInt(TableRes[NumChart]-> Cells[j][0])*m1+StrToInt(TableRes[NumChart]-> Cells[0][i])*5*m2+StrToFloat(TableRes[NumChart]-> Cells[j][i])*m3)*CoefY));
		}
	}
    return true;
}

void __fastcall TMainForm::BNextChartClick(TObject *Sender)            //нажатие кнопки следующий график
{
	BPrevChart->Enabled=true;                                          //включени кнопки предыдущий график
	NumChart++;                                                        //изменение номера графика
	if (NumChart==TableRes.Length-1)                                   //выключение кнопки
		BNextChart -> Enabled = false;
	PaintChart(NumChart);                                              //рисование графика
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::BPrevChartClick(TObject *Sender)
{
	NumChart--;                                                    //изменение номера графика
	BNextChart -> Enabled = true;                                  //включени кнопки следующий график
	if (NumChart == 0)                                             //выключение кнопки
		BPrevChart -> Enabled = false;
	PaintChart(NumChart);                                          //рисование графика
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::FormResize(TObject *Sender)              //изменение размера формы
{
	CapacityGrid->Width = MainForm -> ClientWidth - 16;             //корректировка размера элементов
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

void __fastcall TMainForm::MCreateClick(TObject *Sender)         //кнопка создать
{
	if (!CheckChangeData()) //проверка наличия несохраненых изменений
		return;
    Charts -> Picture->Assign( NULL );//удаление старых результатов обработки
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
	CapacityGrid -> ColCount = 2;                   //установка начальных состояни таблиц
	CapacityGrid -> Cells[1][1] = L"";
	NumDoorsGrid -> ColCount = 2;
	NumDoorsGrid -> Cells[1][1] = L"";
	CoefQuanGrid -> ColCount = 2;
	CoefQuanGrid -> Cells[1][1] = L"";
	ETimeIE -> Text=L"";                                   //установка начальных состояни полей ввода
	EMinInterval -> Text=L"";
	LChart->Caption = L"";                                 //установка начального состояния подписи графика
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::MCloseClick(TObject *Sender)         //назажие на кнопу выход
{
    Close();                                                   //закрытие программы
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormCloseQuery(TObject *Sender, bool &CanClose)  //закрытие программы
{
	if (!CheckChangeData()){   //проверка наличия несохраненых изменений
		CanClose=false;                                             //отмера закрытия
		return;
	}
	TableRes.Length=0;//освобождение ресурсов
	LabelRes.Length=0;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::IntGridKeyPress(TObject *Sender, System::WideChar &Key)  //нажатие кнопки на клавиатуре в таблице при вводе

{
	if (!MSave->Enabled) {                              //проверка наличия несхраненых уименений
		MSave->Enabled= true;                           //включение кнопки сохранить (признак наличия несохраненых изменений)
		MainForm->Caption+=L"*";                        //добавление признака в заголовок программы
	}
	if (!((Key >= '0' && Key <= '9') || (int)Key == 3 || (int)Key == 8 ||  (int)Key == 13 || (int)Key == 22 || (int)Key == 24 || (int)Key == 26)) {   //проверка на допустимость введеного символа
		StatusBar -> SimpleText=String(L"Введен недопустимый символ \"") + Key + L"\"";     //вывод сообщения в статус бар
		Key = 0;                                                                            //отмена ввода
		return;
	}
	StatusBar -> SimpleText = L"";
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::DoubleKeyPress(TObject *Sender, System::WideChar &Key)    //нажатие кнопки на клавиатуре в дробной таблице и полях ввода при вводе

{
	if (!MSave->Enabled) {                              //проверка наличия несхраненых уименений
		MSave->Enabled= true;                           //включение кнопки сохранить (признак наличия несохраненых изменений)
		MainForm->Caption+=L"*";                        //добавление признака в заголовок программы
	}
	if (!((Key >= '0' && Key <= '9') || (int)Key == 3 || (int)Key == 8 ||(int)Key == 44 ||  (int)Key == 13 || (int)Key == 22 || (int)Key == 24 || (int)Key == 26)) {   //проверка на допустимость введеного символа
		StatusBar -> SimpleText=String(L"Введен недопустимый символ \"") + Key + L"\"";     //вывод сообщения в статус бар
		Key = 0;                                                                            //отмена ввода
		return;
	}
	StatusBar -> SimpleText = L"";
}
//---------------------------------------------------------------------------

