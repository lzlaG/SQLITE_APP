//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main.h"
#include "sqlite3.h"
#include <iostream>
#include <string>

using namespace std;


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VirtualTrees"
#pragma link "VirtualTrees.AncestorVCL"
#pragma link "VirtualTrees.BaseAncestorVCL"
#pragma link "VirtualTrees.BaseTree"
#pragma resource "*.dfm"
TForm1 *Form1;



//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	our_tree->NodeDataSize = sizeof(NodeStruct);
}
//---------------------------------------------------------------------------

//функция для заполнения virtualstringtree
void FillTree(TVirtualStringTree *stringTree, sqlite3 *db)
{
	//stringTree->BeginUpdate();

	stringTree->Clear(); // предварительно очищаем дерево

	sqlite3_stmt *pStatement;

	int execResult = sqlite3_prepare_v2(db,"SELECT id,datetime(last_visit_time/1000000-11644473600,'unixepoch','localtime'),url,title,visit_count FROM urls;",-1,
	&pStatement,NULL);
	int stepResult = SQLITE_DONE;
	while(true)
	{
		int stepResult = sqlite3_step(pStatement);

		if(stepResult != SQLITE_ROW)
		{
			break;
		}

		PVirtualNode entryNode = stringTree->AddChild(stringTree->RootNode);
		NodeStruct *nodeData = (NodeStruct*)stringTree->GetNodeData(entryNode);
		//сохраняем данные из sql Запроса в нашу структуру
		nodeData->id = sqlite3_column_int(pStatement, 0);
		nodeData->date = UnicodeString((wchar_t*)sqlite3_column_text16(pStatement, 1));
		nodeData->url = UnicodeString((wchar_t*)sqlite3_column_text16(pStatement, 2));
		nodeData->title = UnicodeString((wchar_t*)sqlite3_column_text16(pStatement, 3));
		nodeData->visit_count = UnicodeString((wchar_t*)sqlite3_column_text16(pStatement, 4));
	};
}

//действия для кнопки открыть бд
void __fastcall TForm1::open_file_buttonClick(TObject *Sender)
{
	wstring filename;

	if(file_open->Execute())
	{
	   filename = file_open->FileName.c_str();
	   sqlite3_open16(filename.c_str(), &db);
	}
	FillTree(our_tree, db);
}
//---------------------------------------------------------------------------
// обработчик для визуализирования информации в virtualstringtree
void __fastcall TForm1::our_treeGetText(TBaseVirtualTree *Sender, PVirtualNode Node,
		  TColumnIndex Column, TVstTextType TextType, UnicodeString &CellText)
{
	NodeStruct *nodeData = (NodeStruct*)Sender->GetNodeData(Node);
	switch(Column)
	{
		case 0: CellText = nodeData->url; break;
		case 1: CellText = nodeData->title; break;
	}
}
//---------------------------------------------------------------------------


void __fastcall TForm1::our_treeAddToSelection(TBaseVirtualTree *Sender, PVirtualNode Node)

{
	//сохраняем выделенную строку(узел) в публичные переменные, для возможности последующего взаимодействия с ними
	CurrentNodeData = (NodeStruct*)Sender->GetNodeData(Node);
	CurrentNode = Node;
	//задаем текст для лейбла
	additional_info_label->Caption = UnicodeString("Дополнительная информация \nПоследнее время посещения: ")+
							CurrentNodeData->date+UnicodeString("\nКоличество посещений: ")+CurrentNodeData->visit_count;
}
//---------------------------------------------------------------------------

// функция для удаления строки из бд
void DeleteRowFromDB(sqlite3* db,NodeStruct* NodeData)
{
   	sqlite3_stmt* stmt;
	string query = "DELETE FROM urls WHERE (id = "+to_string(NodeData->id)+");";
	sqlite3_prepare_v2(db,query.c_str(), -1, &stmt,NULL);
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
};

// действия на клик для кнопки delete_button
void __fastcall TForm1::delete_buttonClick(TObject *Sender)
{
	DeleteRowFromDB(db, CurrentNodeData);
	//удаляем узел
	our_tree->DeleteNode(CurrentNode);
}
//---------------------------------------------------------------------------

