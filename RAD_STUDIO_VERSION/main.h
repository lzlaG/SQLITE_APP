//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "VirtualTrees.AncestorVCL.hpp"
#include "VirtualTrees.BaseAncestorVCL.hpp"
#include "VirtualTrees.BaseTree.hpp"
#include "VirtualTrees.hpp"
#include <Vcl.Dialogs.hpp>
#include "sqlite3.h"
//---------------------------------------------------------------------------
//структура для данных
typedef struct
{
	int id;
	UnicodeString date;
	UnicodeString url;
	UnicodeString title;
	UnicodeString visit_count;

} NodeStruct;

class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TVirtualStringTree *our_tree;
	TOpenDialog *file_open;
	TButton *open_file_button;
	TLabel *additional_info_label;
	TButton *delete_button;
	void __fastcall open_file_buttonClick(TObject *Sender);
	void __fastcall our_treeGetText(TBaseVirtualTree *Sender, PVirtualNode Node, TColumnIndex Column,
          TVstTextType TextType, UnicodeString &CellText);
	//void __fastcall additional_info_labelClick(TObject *Sender);
	void __fastcall our_treeAddToSelection(TBaseVirtualTree *Sender, PVirtualNode Node);
	void __fastcall delete_buttonClick(TObject *Sender);

private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
	sqlite3 *db;  // база данных
	NodeStruct *CurrentNodeData; // текущая данные
	PVirtualNode CurrentNode; //текущий узел
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
