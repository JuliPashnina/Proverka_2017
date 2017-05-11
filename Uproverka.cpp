//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Uproverka.h"
#include "inifiles.hpp"
#include "Ustat_form.h"
#include "Ustat_rep.h"
#include "Ustsum_f.h"
TIniFile *Inisys;
String sFilesys;
#include <stdio.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dbf"
#pragma link "dbf"
#pragma link "dbf"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
 //Directory= "";
 ProgDir= GetCurrentDir();
 Directory= ProgDir;
 FLB1->Directory= ProgDir;
 SELDIRHELP= 1000;

 if(!FileExists(ProgDir+"\\proverka.ini")) ShowMessage("НАСТРОЕЧНЫЙ ФАЙЛ proverka.ini НЕ СУЩЕСТВУЕТ В ПАПКЕ С ПРОГРАММОЙ!\nПРИ РАБОТЕ С ПРОГРАММОЙ МОГУТ ВОЗНИКНУТЬ ОШИБКИ!");
 else
 {
  AnsiString def1="";
  int def=0;
  sFilesys= ProgDir+"\\proverka.ini";
  Inisys= new TIniFile(sFilesys);

  uchastki= Inisys->ReadString("Errors_par","E001_uch",def1);
  velichina= Inisys->ReadFloat("Errors_par","E005_velichina",def);
  met_raion= Inisys->ReadInteger("Errors_par","E006_met_raion",def);
  kolvo= Inisys->ReadInteger("Errors_par","E021_kolvo",def);
  value= Inisys->ReadFloat("Errors_par","E022_value",def);
  StatView= Inisys->ReadInteger("Errors_par","Statistika",def);

  delete Inisys;
 }

 list = new TStringList();
 spisok = new TStringList();
 chlist = new TStringList();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormShow(TObject *Sender)
{
 u4astki= new TStringList();

 if(uchastki!="0"&!uchastki.IsEmpty())
 {
  u4astki->Clear();
  AnsiString s=uchastki;
  int t=0;
  while(s.Length()>0)
  {
   t= s.Pos(",");
   if(t!=0)
   {
    u4astki->Add(s.SubString(1,s.Pos(",")-1));
    s.Delete(1,s.Pos(","));
   }
   else
   {
    u4astki->Add(s);
    s= "";
   }
  }
 }

 CBmes->SetFocus();
}
//---------------------------------------------------------------------------

void TForm1::AddField(AnsiString name, TFieldType type, int length)
{
 D1->FieldDefs->Add(name,type,length,false);
}
//---------------------------------------------------------------------------

AnsiString TForm1::TipField(int tip)
{
 AnsiString TipPolya="";
 switch(tip)
 {
  case  0: TipPolya= "Unknown";     break;
  case  1: TipPolya= "String";      break;
  case  2: TipPolya= "Smallint";    break;
  case  3: TipPolya= "Integer";     break;
  case  4: TipPolya= "Word";        break;
  case  5: TipPolya= "Boolean";     break;
  case  6: TipPolya= "Float";       break;
  case  7: TipPolya= "Currency";    break;
  case  8: TipPolya= "BCD";         break;
  case  9: TipPolya= "Date";        break;
  case 10: TipPolya= "Time";        break;
  case 11: TipPolya= "DateTime";    break;
  case 12: TipPolya= "Bytes";       break;
  case 13: TipPolya= "VarBytes";    break;
  case 14: TipPolya= "AutoInc";     break;
  case 15: TipPolya= "Blob";        break;
  case 16: TipPolya= "Memo";        break;
  case 17: TipPolya= "Graphic";     break;
  case 18: TipPolya= "FmtMemo";     break;
  case 19: TipPolya= "ParadoxOle";  break;
  case 20: TipPolya= "DBaseOle";    break;
  case 21: TipPolya= "TypedBinary"; break;
  case 22: TipPolya= "Cursor";      break;
  case 23: TipPolya= "FixedChar";   break;
  case 24: TipPolya= "WideString";  break;
  case 25: TipPolya= "Largeint";    break;
  case 26: TipPolya= "ADT";         break;
  case 27: TipPolya= "Array";       break;
  case 28: TipPolya= "Reference";   break;
  case 29: TipPolya= "DataSet";     break;
  case 30: TipPolya= "OraBlob";     break;
  case 31: TipPolya= "OraClob";     break;
  case 32: TipPolya= "Variant";     break;
  case 33: TipPolya= "Interface";   break;
  case 34: TipPolya= "IDispatch";   break;
  case 35: TipPolya= "Guid";        break;
 }
 return TipPolya.UpperCase();
}
//---------------------------------------------------------------------------

void TForm1::AddStr(AnsiString Rec, AnsiString Txt, int Numrec, int Rn, AnsiString Ls)
{
 if(Rec=="")
 {
  rec= "ЗАПИСЬ №"+IntToStr(Numrec)+" ("+IntToStr(Rn)+") Лицевой:"+Ls;
  list->Add(rec);
 }
 list->Add(Txt);
 b= true;
}
//---------------------------------------------------------------------------

void TForm1::Statistika(void)
{
 if(!FileExists(ProgDir+"\\stat.dbf"))
 {
  Dstat->Active= false;
  Dstat->FilePath= ProgDir;
  Dstat->TableName= "stat.dbf";
  Dstat->FieldDefs->Clear();
  Dstat->FieldDefs->Add("n_mes",ftString,4,false);
  Dstat->FieldDefs->Add("n_uch",ftInteger,0,false);
  Dstat->FieldDefs->Add("e001",ftInteger,0,false);
  Dstat->FieldDefs->Add("e002",ftInteger,0,false);
  Dstat->FieldDefs->Add("e003",ftInteger,0,false);
  Dstat->FieldDefs->Add("e004",ftInteger,0,false);
  Dstat->FieldDefs->Add("e005",ftInteger,0,false);
  Dstat->FieldDefs->Add("e006",ftInteger,0,false);
  Dstat->FieldDefs->Add("e007",ftInteger,0,false);
  Dstat->FieldDefs->Add("e008",ftInteger,0,false);
  Dstat->FieldDefs->Add("e009",ftInteger,0,false);
  Dstat->FieldDefs->Add("e010",ftInteger,0,false);
  Dstat->FieldDefs->Add("e010_1",ftInteger,0,false);
  Dstat->FieldDefs->Add("e010_2",ftInteger,0,false);
  Dstat->FieldDefs->Add("e011",ftInteger,0,false);
  Dstat->FieldDefs->Add("e013",ftInteger,0,false);
  Dstat->FieldDefs->Add("e019",ftInteger,0,false);
  Dstat->FieldDefs->Add("e020",ftInteger,0,false);
  Dstat->FieldDefs->Add("e021",ftInteger,0,false);
  Dstat->FieldDefs->Add("e022",ftInteger,0,false);
  Dstat->FieldDefs->Add("e023",ftInteger,0,false);
  Dstat->FieldDefs->Add("e024",ftInteger,0,false);
  Dstat->FieldDefs->Add("e025",ftInteger,0,false);
  Dstat->CreateTable();
 }
 //kodirovka
 FILE *F;
 char cRus='\0';
 AnsiString rai=ProgDir+"\\stat.dbf";
 F= fopen(rai.c_str(),"r+");
 fseek(F,29,0);
 fwrite(&cRus,sizeof(cRus),1,F);
 fclose(F);

 //проверка на дублирование
 Dstat->Active= false;
 Dstat->FilePath= ProgDir;
 Dstat->TableName= "stat.dbf";
 Dstat->Active= true;
 Dstat->First();
 while(!Dstat->Eof)
 {
  if(Dstat->FieldByName("n_mes")->AsString==mes_opl & Dstat->FieldByName("n_uch")->AsInteger==uchastok) Dstat->Delete();
  else Dstat->Next();
  Application->ProcessMessages();
 }
 Dstat->TryExclusive();
 Dstat->PackTable();
 Dstat->EndExclusive();
 Dstat->Active= false;

 //внесение в статистику
 Dstat->Active= false;
 Dstat->FilePath= ProgDir;
 Dstat->TableName= "stat.dbf";
 Dstat->Active= true;
 Dstat->Insert();
 if(!mes_opl.IsEmpty()) Dstat->FieldByName("n_mes")->AsString= mes_opl.Trim();
 Dstat->FieldByName("n_uch")->AsInteger= uchastok;
 Dstat->FieldByName("e001")->AsInteger= e001;
 Dstat->FieldByName("e002")->AsInteger= e002;
 Dstat->FieldByName("e003")->AsInteger= e003;
 Dstat->FieldByName("e004")->AsInteger= e004;
 Dstat->FieldByName("e005")->AsInteger= e005;
 Dstat->FieldByName("e006")->AsInteger= e006;
 Dstat->FieldByName("e007")->AsInteger= e007;
 Dstat->FieldByName("e008")->AsInteger= e008;
 Dstat->FieldByName("e009")->AsInteger= e009;
 Dstat->FieldByName("e010")->AsInteger= e010;
 Dstat->FieldByName("e010_1")->AsInteger= fio_empty;
 Dstat->FieldByName("e010_2")->AsInteger= street_empty;
 Dstat->FieldByName("e011")->AsInteger= e011;
 Dstat->FieldByName("e013")->AsInteger= e013;
 Dstat->FieldByName("e019")->AsInteger= e019;
 Dstat->FieldByName("e020")->AsInteger= e020;
 Dstat->FieldByName("e021")->AsInteger= e021;
 Dstat->FieldByName("e022")->AsInteger= e022;
 Dstat->FieldByName("e023")->AsInteger= e023;
 Dstat->FieldByName("e024")->AsInteger= e024;
 Dstat->FieldByName("e025")->AsInteger= rec_null;
 Dstat->Post();
 Dstat->Active= false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BcheckClick(TObject *Sender)
{
try
{
 CBmes->Enabled= false;
 ChBselall->Enabled= false;
 Bsel->Enabled= false;
 FLB1->Enabled= false;
 ChBdblls->Enabled= false;
 Bcheck->Enabled= false;
 Bstatuch->Enabled= false;
 Bstatsum->Enabled= false;
 BBclose->Enabled= false;


if(FLB1->SelCount==0) ShowMessage("ВЫБЕРИТЕ ФАЙЛ(Ы) ДЛЯ ПРОВЕРКИ!");
else
{
 //SelectDirectory("Выберите папку выгрузки результатов проверки","",Directory);
 //SelectDirectory(Directory, TSelectDirOpts(), SELDIRHELP);
 //if(Directory.IsEmpty()) ShowMessage("ПАПКА ВЫГРУЗКИ НЕ БЫЛА ВЫБРАНА!\nПРОВЕРКА НА НАЛИЧИЕ ОШИБОК ОТМЕНЕНА!");
 //else
 //{
  Form1->SetFocus();

 //проходим по выделенным для проверки файлам
 for(int i=0;i<FLB1->Items->Count;i++)
 {
  if(FLB1->Selected[i])
  {
   //проверка структуры входного файла
   if(!FileExists(ProgDir+"\\shablon.dbf"))
   {
    ShowMessage("ФАЙЛ shablon.dbf С ШАБЛОНОМ ПОЛЕЙ НЕ СУЩЕСТВУЕТ В КАТАЛОГЕ ПРОГРАММЫ!\nПРОВЕРКА ОТМЕНЕНА!");
    goto EndProv;
   }
   else
   {
    D1->Active= false;
    D1->FilePath= ProgDir;
    D1->TableName= "shablon.dbf";
    D1->Active= true;

    D2->Active= false;
    if(dir.IsEmpty()) dir= GetCurrentDir()+"\\";
    D2->FilePath= dir;
    D2->TableName= ExtractFileName(FLB1->Items->Strings[i]);
    D2->Active= true;

    AnsiString errors="";
    bool err=false, pole=false;
    int ShabFCount=0, FileFCount=0;

    //кол-во полей в шаблоне и файле
    ShabFCount= D1->FieldCount;
    FileFCount= D2->FieldCount;
    if(ShabFCount!=FileFCount)//кол-во полей в шаблоне и провер. файле неравны
    {
     AnsiString NameSh="", NameF="", FieldOff="", message="";

     if(ShabFCount>FileFCount)//в шаблоне больше, чем в файле
     {
      for(int ShabF=0;ShabF<=ShabFCount-1;ShabF++)
      {
       NameSh= D1->FieldDefs->Items[ShabF]->Name;
       pole=false;
       //проход по полям проверяемого файла
       for(int FileF=0;FileF<=FileFCount-1;FileF++)
       {
        if(D2->FieldDefs->Items[FileF]->Name==NameSh) pole= true;
       }
       if(!pole) FieldOff+= NameSh+", ";
       Application->ProcessMessages();
      }//end_for(...) проход по шаблону
      if(!FieldOff.IsEmpty())
      {
       FieldOff.Delete(FieldOff.Length()-1,2);
       message+= "КОЛ-ВО ПОЛЕЙ В ШАБЛОНЕ ("+IntToStr(ShabFCount)+") БОЛЬШЕ КОЛ-ВА ПОЛЕЙ В ФАЙЛЕ "+ExtractFileName(FLB1->Items->Strings[i])+" ("+IntToStr(FileFCount)+")\n\n";
       message+= "В ФАЙЛЕ "+ExtractFileName(FLB1->Items->Strings[i])+" ОТСУТСТВУЮТ ПОЛЯ: "+FieldOff+"\n\n";
       message+= "ПРОВЕРКА ФАЙЛА "+ExtractFileName(FLB1->Items->Strings[i])+" ОТМЕНЕНА!";
       ShowMessage(message);
       goto EndProvFile;
      }
     }//end_if(полей в шаблоне > полей в файле)

     if(ShabFCount<FileFCount)//в шаблоне меньше, чем в файле
     {
      for(int FileF=0;FileF<=FileFCount-1;FileF++)
      {
       NameF= D2->FieldDefs->Items[FileF]->Name;
       pole=false;
       //проход по полям шаблона
       for(int ShabF=0;ShabF<=ShabFCount-1;ShabF++)
       {
        if(D1->FieldDefs->Items[ShabF]->Name==NameF) pole= true;
       }
       if(!pole) FieldOff+= NameF+", ";
       Application->ProcessMessages();
      }//end_for(...) проход по шаблону
      if(!FieldOff.IsEmpty())
      {
       FieldOff.Delete(FieldOff.Length()-1,2);
       message+= "КОЛ-ВО ПОЛЕЙ В ФАЙЛЕ "+ExtractFileName(FLB1->Items->Strings[i])+" ("+IntToStr(FileFCount)+") БОЛЬШЕ КОЛ-ВА ПОЛЕЙ В ШАБЛОНЕ ("+IntToStr(ShabFCount)+")\n\n";
       message+= "В ШАБЛОНЕ ОТСУТСТВУЮТ ПОЛЯ: "+FieldOff+"\n\n";
       message+= "ПРОВЕРКА ФАЙЛА "+ExtractFileName(FLB1->Items->Strings[i])+" ОТМЕНЕНА!";
       ShowMessage(message);
       goto EndProvFile;
      }
     }//end_if(полей в файле > полей в шаблоне)
    }
    else//кол-во полей шаблона и файла равно
    {
    //ПРОХОД ПО ПОЛЯМ SHABLON.DBF
    for(int sh=0;sh<=D1->FieldDefs->Count-1;sh++)
    {
     AnsiString NameField=D1->FieldDefs->Items[sh]->Name;
     int TypeField=D1->FieldDefs->Items[sh]->DataType;
     int SizeField=D1->FieldDefs->Items[sh]->Size;
     //проход по полям проверяемого файла
     for(int pr=0;pr<=D2->FieldDefs->Count-1;pr++)
     {
      if(D2->FieldDefs->Items[pr]->Name==NameField)
      {
       pole= true;
       if(D2->FieldDefs->Items[pr]->DataType!=TypeField)
       {
        err= true;//error
        errors+= D2->FieldDefs->Items[pr]->Name+": тип не "+TipField(D1->FieldByName(NameField)->DataType)+", а "+TipField(D2->FieldByName(NameField)->DataType)+"\n";
       }
       else
       if(D2->FieldDefs->Items[pr]->DataType==D1->FieldDefs->Items[sh]->DataType&D2->FieldDefs->Items[pr]->DataType==1)
       {
        if(D2->FieldDefs->Items[pr]->Size!=D1->FieldDefs->Items[sh]->Size)
        {
         err= true;//error
         errors+= D2->FieldDefs->Items[pr]->Name+": размер не "+IntToStr(SizeField)+", а "+IntToStr(D2->FieldByName(NameField)->Size)+"\n";
        }
       }
      }//end_if(name==name)
      if(pole) goto EndPoleProv;
      Application->ProcessMessages();
     }//end_for_проход по полям проверяемого файла
     EndPoleProv:
     pole= false;
     Application->ProcessMessages();
    }//end_for_ПРОХОД ПО ПОЛЯМ SHABLON.DBF

    if(err)//если есть ошибки
    {
     errors= "В СТРУКТУРЕ ПОЛЕЙ ФАЙЛА "+ExtractFileName(FLB1->Items->Strings[i])+" НАЙДЕНЫ ОШИБКИ!\n\n"+errors;
     errors+= "\nПРОВЕРКА ФАЙЛА "+ExtractFileName(FLB1->Items->Strings[i])+" ОТМЕНЕНА!";
     ShowMessage(errors);
     goto EndProvFile;
    }
    }//end_else_кол-во полей шаблона и файла равно
   }//end_else_shablon_exists

  //имена выходных файлов
  AnsiString name=ExtractFileName(FLB1->Items->Strings[i]);
  name.Delete(1,2);
  name.Delete(6,4);
  if(!FileExists(Directory+"\\ER"+name+".DBF"))
  {
   //CREATING_TABLE
   //структура полей проверяемого файла
   D1->Active = false;
   if(dir.IsEmpty()) dir = GetCurrentDir()+"\\";
   D1->FilePath = dir;
   D1->TableName = ExtractFileName(FLB1->Items->Strings[i]);
//   D1->Active = true;

   //структура полей файла с ошибочными записями
   D2->Active = false;
   D2->FilePath = Directory;
   D2->TableName = "ER"+name+".DBF";

   //создаём структуру полей (копируем поля)
   CopyStructDBF(D1->FilePath, D1->TableName, D2->FilePath, D2->TableName, D1, D2);

/*   TDbfFieldDefs *fds= new TDbfFieldDefs(D1);
   fds->Add("ACCT_ID",ftString,10,false);
   fds->Add("TREST",ftString,3,false);
   fds->Add("GEK",ftString,2,false);
   fds->Add("GOROD",ftString,40,false);
   fds->Add("UL",ftString,30,false);
   fds->Add("DOM",ftString,4,false);
   fds->Add("LIT",ftString,2,false);
   fds->Add("KV",ftString,6,false);
   fds->Add("SCHET",ftString,8,false);
   fds->Add("FIO",ftString,40,false);
   fds->Add("PRIM",ftString,71,false);
   fds->Add("MES_OPL",ftString,4,false);
   fds->Add("P_IND",ftString,6,false);
   fds->Add("DOG",ftSmallint,4,false);
   fds->Add("PRED",ftSmallint,4,false);
//   AddField("SE1",ftFloat);
   TDbfFieldDef *fd= fds->AddFieldDef();
   fd->FieldName= "SE1";
   fd->NativeFieldType= 'N';
   fd->Size= 16;
   fd->Precision= 2;
//   AddField("IT_E",ftFloat);
   fd= fds->AddFieldDef();
   fd->FieldName= "IT_E";
   fd->NativeFieldType= 'N';
   fd->Size= 16;
   fd->Precision= 2;
//   AddField("IT_ED",ftFloat);
   fd= fds->AddFieldDef();
   fd->FieldName= "IT_ED";
   fd->NativeFieldType= 'N';
   fd->Size= 16;
   fd->Precision= 2;
//   AddField("IT_EP",ftFloat);
   fd= fds->AddFieldDef();
   fd->FieldName= "IT_EP";
   fd->NativeFieldType= 'N';
   fd->Size= 16;
   fd->Precision= 2;
//   AddField("SUMMA_E",ftFloat);
   fd= fds->AddFieldDef();
   fd->FieldName= "SUMMA_E";
   fd->NativeFieldType= 'N';
   fd->Size= 16;
   fd->Precision= 2;
   fds->Add("P_ND",ftInteger,9,false);
   fds->Add("R_ND",ftInteger,9,false);
//   AddField("T_ND",ftFloat);
   fd= fds->AddFieldDef();
   fd->FieldName= "T_ND";
   fd->NativeFieldType= 'N';
   fd->Size= 16;
   fd->Precision= 2;
   fds->Add("P_NN",ftInteger,9,false);
   fds->Add("R_NN",ftInteger,9,false);
//   AddField("T_NN",ftFloat);
   fd= fds->AddFieldDef();
   fd->FieldName= "T_NN";
   fd->NativeFieldType= 'N';
   fd->Size= 16;
   fd->Precision= 2;
   fds->Add("R_LD",ftInteger,9,false);
   fds->Add("R_LD2",ftInteger,9,false);
   fds->Add("R_LN",ftInteger,9,false);
//   AddField("T_LD",ftFloat);
   fd= fds->AddFieldDef();
   fd->FieldName= "T_LD";
   fd->NativeFieldType= 'N';
   fd->Size= 16;
   fd->Precision= 2;
//   AddField("T_LD2",ftFloat);
   fd= fds->AddFieldDef();
   fd->FieldName= "T_LD2";
   fd->NativeFieldType= 'N';
   fd->Size= 16;
   fd->Precision= 2;
//   AddField("T_LN",ftFloat);
   fd= fds->AddFieldDef();
   fd->FieldName= "T_LN";
   fd->NativeFieldType= 'N';
   fd->Size= 16;
   fd->Precision= 2;
   fds->Add("Stav1",ftString,12,false);
   fds->Add("Stav2",ftString,12,false);
//   AddField("S_LD",ftFloat);
   fd= fds->AddFieldDef();
   fd->FieldName= "S_LD";
   fd->NativeFieldType= 'N';
   fd->Size= 16;
   fd->Precision= 2;
//   AddField("S_LD2",ftFloat);
   fd= fds->AddFieldDef();
   fd->FieldName= "S_LD2";
   fd->NativeFieldType= 'N';
   fd->Size= 16;
   fd->Precision= 2;
//   AddField("S_LN",ftFloat);
   fd= fds->AddFieldDef();
   fd->FieldName= "S_LN";
   fd->NativeFieldType= 'N';
   fd->Size= 16;
   fd->Precision= 2;
//   AddField("S_ED",ftFloat);
   fd= fds->AddFieldDef();
   fd->FieldName= "S_ED";
   fd->NativeFieldType= 'N';
   fd->Size= 16;
   fd->Precision= 2;
//   AddField("S_EN",ftFloat);
   fd= fds->AddFieldDef();
   fd->FieldName= "S_EN";
   fd->NativeFieldType= 'N';
   fd->Size= 16;
   fd->Precision= 2;
   fds->Add("Dolg_na",ftString,8,false);
   fds->Add("RAION",ftSmallint,4,false);
   fds->Add("PRIM_M",ftString,60,false);
   fds->Add("NCHEL",ftInteger,9,false);
//   AddField("T_M",ftFloat);
   fd= fds->AddFieldDef();
   fd->FieldName= "T_M";
   fd->NativeFieldType= 'N';
   fd->Size= 16;
   fd->Precision= 2;
//   AddField("S_ML1",ftFloat);
   fd= fds->AddFieldDef();
   fd->FieldName= "S_ML1";
   fd->NativeFieldType= 'N';
   fd->Size= 16;
   fd->Precision= 2;
//   AddField("S_ML2",ftFloat);
   fd= fds->AddFieldDef();
   fd->FieldName= "S_ML2";
   fd->NativeFieldType= 'N';
   fd->Size= 16;
   fd->Precision= 2;
   fds->Add("StavM1",ftString,12,false);
   fds->Add("StavM2",ftString,12,false);
//   AddField("IT_MP",ftFloat);
   fd= fds->AddFieldDef();
   fd->FieldName= "IT_MP";
   fd->NativeFieldType= 'N';
   fd->Size= 16;
   fd->Precision= 2;
//   AddField("IT_MD",ftFloat);
   fd= fds->AddFieldDef();
   fd->FieldName= "IT_MD";
   fd->NativeFieldType= 'N';
   fd->Size= 16;
   fd->Precision= 2;
//   AddField("S_M",ftFloat);
   fd= fds->AddFieldDef();
   fd->FieldName= "S_M";
   fd->NativeFieldType= 'N';
   fd->Size= 16;
   fd->Precision= 2;
//   AddField("SE2",ftFloat);
   fd= fds->AddFieldDef();
   fd->FieldName= "SE2";
   fd->NativeFieldType= 'N';
   fd->Size= 16;
   fd->Precision= 2;
   fds->Add("CHAST",ftSmallint,4,false);
//   fds->Add("NKORR",ftSmallint,4,false);
   fds->Add("NSETI",ftString,7,false);
   fds->Add("TDP",ftString,6,false);
   fds->Add("TDT",ftString,6,false);
   fds->Add("TDU",ftString,6,false);
   fds->Add("TNP",ftString,6,false);
   fds->Add("TNT",ftString,6,false);
   fds->Add("TNU",ftString,6,false);
   D1->CreateTableEx(fds);
   delete fds;*/
  }
  else
  {
   D2->Active= false;
   D2->FilePath= Directory;
   D2->TableName= "ER"+name+".DBF";
   D2->Active= true;
   D2->First();
   if(D2->RecordCount>0) while(!D2->Eof) D2->Delete();
   //чистим от удаленных записей
   D2->TryExclusive();
   D2->PackTable();
   D2->EndExclusive();
   D2->Active= false;
  }
  //kodirovka
  FILE *F;
  char cRus='\0';
  AnsiString rai=Directory+"\\ER"+name+".DBF";
  F= fopen(rai.c_str(),"r+");
  fseek(F,29,0);
  fwrite(&cRus,sizeof(cRus),1,F);
  fclose(F);

  list->Clear();
  list->Add(" РЕЗУЛЬТАТЫ ПРОВЕРКИ ФАЙЛА "+ExtractFileName(FLB1->Items->Strings[i]));
  list->Add(" ЗАПИСИ ИЗ ФАЙЛА ER"+name+".DBF"+" ("+ExtractFileName(FLB1->Items->Strings[i])+")");
  list->Add(" ");
  spisok->Clear();

  //ПРОХОД ПО ЗАПИСЯМ
  D1->Active= false;
  if(dir.IsEmpty()) dir= GetCurrentDir()+"\\";
  D1->FilePath= dir;
  D1->TableName= ExtractFileName(FLB1->Items->Strings[i]);

  //kodirovka (проверяемому файлу делаем DOS кодировку)
  cRus='\0';
  rai=dir+"\\"+ExtractFileName(FLB1->Items->Strings[i]);
  F= fopen(rai.c_str(),"r+");
  fseek(F,29,0);
  fwrite(&cRus,sizeof(cRus),1,F);
  fclose(F);

  D1->Active= true;
  D1->First();
  D2->Active= false;
  D2->FilePath= Directory;
  D2->TableName= "ER"+name+".DBF";
  D2->Active= true;

  Bcheck->Caption= "Проверено 0%";
  int numrec=1,rn=0, real=0,tek=0;
  int rr=D1->RecordCount;
  e001=0; e002=0; e003=0; e004=0; e005=0; e006=0; e007=0; e008=0; e009=0; e010=0;
  e011=0; e013=0; e019=0; e020=0; e021=0; e022=0; e023=0; e024=0;
  if(!D1->FieldByName("MES_OPL")->AsString.IsEmpty()) mes_opl= D1->FieldByName("MES_OPL")->AsString;
  AnsiString txt="";
  rec_null=0;
  fio_empty=0;
  street_empty=0;
  ny4d_kol=0;
  
  while(!D1->Eof)
  {
   rn++;
   rec= "";
   b=false;

   real= 100*rn/rr;
   if(tek!=real)
   {
    Bcheck->Caption= "Проверено "+IntToStr(real)+"%";
    Form1->Refresh();
    tek= real;
   }

   //LS= D1->FieldByName("Gek")->AsString;
   //LS= LS+D1->FieldByName("Schet")->AsString;
   LS= D1->FieldByName("ACCT_ID")->AsString;

   //ПРОВЕРКА НА ОШИБКИ
//E001
   AnsiString file=ExtractFileName(FLB1->Items->Strings[i]), uch=file.SubString(3,2);
   int raion=D1->FieldByName("Raion")->AsInteger;
   uchastok= StrToInt(uch);
   bool u=false;
   for(int f=0;f<u4astki->Count;f++)
   {
    if(IntToStr(raion)==u4astki->Strings[f]) u= true;
    Application->ProcessMessages();
   }
   if(raion==uchastok) u= true;
   if(!u)
   {
    txt= " - код участка: "+IntToStr(raion)+" отличный от: "+IntToStr(uchastok);
    if(uchastki!="0"&!uchastki.IsEmpty()) txt= txt+","+uchastki;
    AddStr(rec,txt,numrec,rn,LS);
    e001++;
   }
//E002
//   int kor=D1->FieldByName("Nkorr")->AsInteger;
//   if(kor!=1)
//   {
//    txt= " - Nkorr не равен 1";
//    AddStr(rec,txt,numrec,rn,LS);
//    e002++;
//   }
//E003
   if(D1->FieldByName("P_ind")->AsString.IsEmpty()&D1->FieldByName("Chast")->AsInteger==0/*&D1->FieldByName("Nkorr")->AsInteger==0*/)
   {
//    txt= " - не задан P_ind (поле Chast=0, Nkorr=0, P_ind - пустое)";
    txt= " - не задан P_ind (поле Chast=0, P_ind - пустое)";
    AddStr(rec,txt,numrec,rn,LS);
    e003++;
   }
//E004
   AnsiString ls=D1->FieldByName("Gek")->AsString;
   ls= ls+D1->FieldByName("Schet")->AsString;
   bool t=false;
   for(int i=1;i<=ls.Length();i++)
   {
    if(ls[i]!='0'&ls[i]!='1'&ls[i]!='2'&ls[i]!='3'&ls[i]!='4'&ls[i]!='5'&ls[i]!='6'&ls[i]!='7'&ls[i]!='8'&ls[i]!='9') t= true;
    Application->ProcessMessages();
   }
   if(t)
   {
    txt= " - лицевой счет содержит не цифры";
    AddStr(rec,txt,numrec,rn,LS);
    e004++;
   }
//E005
   double sum=D1->FieldByName("Summa_e")->AsFloat;
   if(sum>velichina)
   {
    txt= " - сумма к оплате > "+FormatFloat("######0.00",velichina)+", а именно ("+FormatFloat("######0.00",sum)+")";
    AddStr(rec,txt,numrec,rn,LS);
    e005++;
   }
//E006
//   if(D1->FieldByName("Raion")->AsInteger==met_raion&D1->FieldByName("Dog")->AsInteger==NULL)
//   {
//    txt= " - поле Dog пустое для Металлургического филиала 'ЗАО Энергосбыт'";
//    AddStr(rec,txt,numrec,rn,LS);
//    e006++;
//   }
//E007
//   if(D1->FieldByName("Nseti")->AsString.IsEmpty())
//   {
//    txt= " - поле Nseti пустое";
//    AddStr(rec,txt,numrec,rn,LS);
//    e007++;
//   }
//E008
//   if(D1->FieldByName("Tdp")->AsString.IsEmpty()|D1->FieldByName("Tdt")->AsString.IsEmpty()|
//      D1->FieldByName("Tdu")->AsString.IsEmpty()|D1->FieldByName("Tnp")->AsString.IsEmpty()|
//      D1->FieldByName("Tnt")->AsString.IsEmpty()|D1->FieldByName("Tnu")->AsString.IsEmpty())
//   {
//    txt= " - поля с промежуточными тарифами пустые (";
//    if(D1->FieldByName("Tdp")->AsString.IsEmpty()) txt= txt+"Tdp,";
//    if(D1->FieldByName("Tdt")->AsString.IsEmpty()) txt= txt+"Tdt,";
//    if(D1->FieldByName("Tdu")->AsString.IsEmpty()) txt= txt+"Tdu,";
//    if(D1->FieldByName("Tnp")->AsString.IsEmpty()) txt= txt+"Tnp,";
//    if(D1->FieldByName("Tnt")->AsString.IsEmpty()) txt= txt+"Tnt,";
//    if(D1->FieldByName("Tnu")->AsString.IsEmpty()) txt= txt+"Tnu";
//    if(txt[txt.Length()]==',') txt.Delete(txt.Length(),1);
//    txt= txt+")";
//    AddStr(rec,txt,numrec,rn,LS);
//    e008++;
//   }
//E009
   double se1=D1->FieldByName("Se1")->AsFloat, /*se2=D1->FieldByName("Se2")->AsFloat,*/ se3=D1->FieldByName("Se3")->AsFloat;
   double /*se4=D1->FieldByName("Se4")->AsFloat,*/ /*se5=D1->FieldByName("Se5")->AsFloat,*/ se=D1->FieldByName("Summa_e")->AsFloat;

   AnsiString s=FormatFloat("######0.00",se1+se3); //FormatFloat("######0.00",se1+se3+se5); //FormatFloat("######0.00",se1+se2+se3+se4+se5);
   AnsiString sum_e=FormatFloat("######0.00",se);
   if(se>0&s!=sum_e)
   {
    txt= " - поле Summa_e не равно Se1+Se3"; //" - поле Summa_e не равно Se1+Se3+Se5"; //" - поле Summa_e не равно Se1+Se2+Se3+Se4+Se5";
    AddStr(rec,txt,numrec,rn,LS);
    e009++;
   }
//E010
   if(D1->FieldByName("Trest")->AsString.IsEmpty()|D1->FieldByName("Gek")->AsString.IsEmpty()|
      /*D1->FieldByName("Gorod")->AsString.IsEmpty()|D1->FieldByName("Ul")->AsString.IsEmpty()|*/
      D1->FieldByName("Dom")->AsString.IsEmpty()|D1->FieldByName("Schet")->AsString.IsEmpty()|
      /*D1->FieldByName("Fio")->AsString.IsEmpty()|*/D1->FieldByName("Mes_opl")->AsString.IsEmpty()|
      D1->FieldByName("Pred")->AsInteger==NULL|D1->FieldByName("Raion")->AsInteger==NULL|
      D1->FieldByName("Dolg_na")->AsString.IsEmpty()/*|
      D1->FieldByName("Nseti")->AsString.IsEmpty()|D1->FieldByName("Nkorr")->AsInteger==NULL*/)
   {
    txt= " - поля не заполнены:";
    if(D1->FieldByName("Trest")->AsString.IsEmpty()) txt= txt+" Trest,";
    if(D1->FieldByName("Gek")->AsString.IsEmpty()) txt= txt+" Gek,";
    if(D1->FieldByName("Gorod")->AsString.IsEmpty()) txt= txt+" Gorod,";
    //if(D1->FieldByName("Ul")->AsString.IsEmpty()) txt= txt+" Ul,";
    if(D1->FieldByName("Dom")->AsString.IsEmpty()) txt= txt+" Dom,";
    if(D1->FieldByName("Schet")->AsString.IsEmpty()) txt= txt+" Schet,";
    //if(D1->FieldByName("Fio")->AsString.IsEmpty()) txt= txt+" Fio,";
    if(D1->FieldByName("Mes_opl")->AsString.IsEmpty()) txt= txt+" Mes_opl,";
    if(D1->FieldByName("Pred")->AsInteger==NULL) txt= txt+" Pred,";
    if(D1->FieldByName("Raion")->AsInteger==NULL) txt= txt+" Raion,";
    if(D1->FieldByName("Dolg_na")->AsString.IsEmpty()) txt= txt+" Dolg_na,";
    //if(D1->FieldByName("Nseti")->AsString.IsEmpty()) txt= txt+" Nseti,";
    //if(D1->FieldByName("Nkorr")->AsInteger==NULL) txt= txt+" Nkorr,";
    if(txt[txt.Length()]==',') txt.Delete(txt.Length(),1);
    AddStr(rec,txt,numrec,rn,LS);
    e010++;
   }
   //E010_1
   if(D1->FieldByName("Fio")->AsString.IsEmpty()) fio_empty++;
   //E010_2
   if(D1->FieldByName("Ul")->AsString.IsEmpty()) street_empty++;
//E011
/*   if(D1->FieldByName("Nkorr")->AsInteger==0&
     (D1->FieldByName("Se1")->AsFloat!=NULL|D1->FieldByName("It_e")->AsFloat!=NULL|
      D1->FieldByName("It_ed")->AsFloat!=NULL|D1->FieldByName("It_ep")->AsFloat!=NULL|
      D1->FieldByName("P_nd")->AsInteger!=NULL|D1->FieldByName("P_nn")->AsInteger!=NULL|
      D1->FieldByName("R_nd")->AsInteger!=NULL|D1->FieldByName("R_nn")->AsInteger!=NULL|
      D1->FieldByName("S_ed")->AsFloat!=NULL|D1->FieldByName("S_en")->AsFloat!=NULL|
      D1->FieldByName("S_ld")->AsFloat!=NULL|D1->FieldByName("S_ld2")->AsFloat!=NULL|
      D1->FieldByName("S_ln")->AsFloat!=NULL|D1->FieldByName("R_ld")->AsInteger!=NULL|
      D1->FieldByName("R_ld2")->AsInteger!=NULL|D1->FieldByName("R_ln")->AsInteger!=NULL|
      D1->FieldByName("T_ld")->AsFloat!=NULL|D1->FieldByName("T_ld2")->AsFloat!=NULL|
      D1->FieldByName("T_ln")->AsFloat!=NULL|//!D1->FieldByName("Prim")->AsString.IsEmpty()|
      !D1->FieldByName("Stav1")->AsString.IsEmpty()|!D1->FieldByName("Stav2")->AsString.IsEmpty()))
   {
    txt= " - Nkorr равно 0, а поля";
    if(D1->FieldByName("Se1")->AsFloat!=NULL) txt= txt+" Se1,";
    if(D1->FieldByName("It_e")->AsFloat!=NULL) txt= txt+" It_e,";
    if(D1->FieldByName("It_ed")->AsFloat!=NULL) txt= txt+" It_ed,";
    if(D1->FieldByName("It_ep")->AsFloat!=NULL) txt= txt+" It_ep,";
    if(D1->FieldByName("P_nd")->AsInteger!=NULL) txt= txt+" P_nd,";
    if(D1->FieldByName("P_nn")->AsInteger!=NULL) txt= txt+" P_nn,";
    if(D1->FieldByName("R_nd")->AsInteger!=NULL) txt= txt+" R_nd,";
    if(D1->FieldByName("R_nn")->AsInteger!=NULL) txt= txt+" R_nn,";
    if(D1->FieldByName("S_ed")->AsFloat!=NULL) txt= txt+" S_ed,";
    if(D1->FieldByName("S_en")->AsFloat!=NULL) txt= txt+" S_en,";
    if(D1->FieldByName("S_ld")->AsFloat!=NULL) txt= txt+" S_ld,";
    if(D1->FieldByName("S_ld2")->AsFloat!=NULL) txt= txt+" S_ld2,";
    if(D1->FieldByName("S_ln")->AsFloat!=NULL) txt= txt+" S_ln,";
    if(D1->FieldByName("R_ld")->AsInteger!=NULL) txt= txt+" R_ld,";
    if(D1->FieldByName("R_ld2")->AsInteger!=NULL) txt= txt+" R_ld2,";
    if(D1->FieldByName("R_ln")->AsInteger!=NULL) txt= txt+" R_ln,";
    if(D1->FieldByName("T_ld")->AsFloat!=NULL) txt= txt+" T_ld,";
    if(D1->FieldByName("T_ld2")->AsFloat!=NULL) txt= txt+" T_ld2,";
    if(D1->FieldByName("T_ln")->AsFloat!=NULL) txt= txt+" T_ln,";
    //if(!D1->FieldByName("Prim")->AsString.IsEmpty()) txt= txt+" Prim,";
    if(!D1->FieldByName("Stav1")->AsString.IsEmpty()) txt= txt+" Stav1,";
    if(!D1->FieldByName("Stav2")->AsString.IsEmpty()) txt= txt+" Stav2";
    if(txt[txt.Length()]==',') txt.Delete(txt.Length(),1);
    txt= txt+" непусты";
    AddStr(rec,txt,numrec,rn,LS);
    e011++;
   }*/
//E012
/*   if(D1->FieldByName("Chast")->AsInteger!=1&
     (D1->FieldByName("Se2")->AsFloat!=NULL|D1->FieldByName("Nchel")->AsInteger!=NULL|
      D1->FieldByName("T_m")->AsFloat!=NULL|D1->FieldByName("S_m")->AsFloat!=NULL|
      D1->FieldByName("It_md")->AsFloat!=NULL|D1->FieldByName("It_mp")->AsFloat!=NULL|
      D1->FieldByName("S_ml1")->AsFloat!=NULL|D1->FieldByName("S_ml2")->AsFloat!=NULL|
      !D1->FieldByName("Prim_m")->AsString.IsEmpty()|!D1->FieldByName("Stavm1")->AsString.IsEmpty()|
      !D1->FieldByName("Stavm2")->AsString.IsEmpty()))
   {
    txt= " - Chast не равно 1, а поля";
    if(D1->FieldByName("Se2")->AsFloat!=NULL) txt= txt+" Se2,";
    if(D1->FieldByName("Nchel")->AsInteger!=NULL) txt= txt+" Nchel,";
    if(D1->FieldByName("T_m")->AsFloat!=NULL) txt= txt+" T_m,";
    if(D1->FieldByName("S_m")->AsFloat!=NULL) txt= txt+" S_m,";
    if(D1->FieldByName("It_md")->AsFloat!=NULL) txt= txt+" It_md,";
    if(D1->FieldByName("It_mp")->AsFloat!=NULL) txt= txt+" It_mp,";
    if(D1->FieldByName("S_ml1")->AsFloat!=NULL) txt= txt+" S_ml1,";
    if(D1->FieldByName("S_ml2")->AsFloat!=NULL) txt= txt+" S_ml2,";
    if(!D1->FieldByName("Prim_m")->AsString.IsEmpty()) txt= txt+" Prim_m,";
    if(!D1->FieldByName("Stavm1")->AsString.IsEmpty()) txt= txt+" Stavm1,";
    if(!D1->FieldByName("Stavm2")->AsString.IsEmpty()) txt= txt+" Stavm2";
    if(txt[txt.Length()]==',') txt.Delete(txt.Length(),1);
    txt= txt+" непусты";
    AddStr(rec,txt,numrec,rn,LS);
   }*/
//E013
   double se_1=D1->FieldByName("Se1")->AsFloat, ite=D1->FieldByName("It_e")->AsFloat, ited=D1->FieldByName("It_ed")->AsFloat, itep=D1->FieldByName("It_ep")->AsFloat;
   double sople=D1->FieldByName("Sople")->AsFloat/*, sodrn=D1->FieldByName("S_odrn")->AsFloat, sdom=D1->FieldByName("S_dom")->AsFloat*/;
   double sumuk;
   bool f_sumuk=false;
   //проверяем наличие поля Sumuk в проверяемом файле
   for(int f_no=0;f_no<=D1->FieldCount-1;f_no++)
   {
    if(D1->FieldDefs->Items[f_no]->Name=="SUMUK") f_sumuk= true;
    Application->ProcessMessages();
   }
   if(f_sumuk) sumuk=D1->FieldByName("Sumuk")->AsFloat;
   //if(sodrn>0) sodrn= 0;
   //if(sdom>0) sdom= 0;
   AnsiString ss=FormatFloat("######0.00",se_1);
   AnsiString summ;
   if(f_sumuk) summ=FormatFloat("######0.00",ite+ited+itep/*+sodrn+sdom*/-sople-sumuk);
   else summ=FormatFloat("######0.00",ite+ited+itep/*+sodrn+sdom*/-sople);
   if(se_1>0&ss!=summ)
   {
    if(f_sumuk) txt= " - Se1 не равно (It_e+It_ed+It_ep-SOplE-Sumuk)";
    else txt= " - Se1 не равно (It_e+It_ed+It_ep-SOplE)";
    AddStr(rec,txt,numrec,rn,LS);
    e013++;
   }
//E014
/*   double se_2=D1->FieldByName("Se2")->AsFloat, itmp=D1->FieldByName("It_mp")->AsFloat, itmd=D1->FieldByName("It_md")->AsFloat, sm=D1->FieldByName("S_m")->AsFloat;
   AnsiString sss=FormatFloat("######0.00",se_2), sum_ma=FormatFloat("######0.00",itmp+itmd+sm);
   if(se_2>0&sss!=sum_ma)
   {
    txt= " - Se2 не равно (It_mp+It_md+S_m)";
    AddStr(rec,txt,numrec,rn,LS);
   }
//E015
   if((!D1->FieldByName("Prim")->AsString.IsEmpty()&D1->FieldByName("Prim")->AsString.Pos(";")==0)
      &
     (D1->FieldByName("S_ld")->AsFloat==NULL|D1->FieldByName("R_ld")->AsFloat==NULL|
      D1->FieldByName("T_ld")->AsFloat==NULL|D1->FieldByName("Stav1")->AsString.IsEmpty()))
   {
    txt= " - в поле Prim обозначена одна льгота, а поля";
    if(D1->FieldByName("S_ld")->AsFloat==NULL) txt= txt+" S_ld,";
    if(D1->FieldByName("R_ld")->AsFloat==NULL) txt= txt+" R_ld,";
    if(D1->FieldByName("T_ld")->AsFloat==NULL) txt= txt+" T_ld,";
    if(D1->FieldByName("Stav1")->AsString.IsEmpty()) txt= txt+" Stav1";
    if(txt[txt.Length()]==',') txt.Delete(txt.Length(),1);
    txt= txt+" не заполнены";
    AddStr(rec,txt,numrec,rn,LS);
   }
//E016
   if((!D1->FieldByName("Prim")->AsString.IsEmpty()&D1->FieldByName("Prim")->AsString.Pos(";")!=0)
      &
     (D1->FieldByName("S_ld")->AsFloat==NULL|D1->FieldByName("R_ld")->AsFloat==NULL|
      D1->FieldByName("T_ld")->AsFloat==NULL|D1->FieldByName("Stav1")->AsString.IsEmpty()|
      D1->FieldByName("S_ld2")->AsFloat==NULL|D1->FieldByName("R_ld2")->AsFloat==NULL|
      D1->FieldByName("T_ld2")->AsFloat==NULL|D1->FieldByName("Stav2")->AsString.IsEmpty()))
   {
    txt= " - в поле Prim обозначены две льготы, а поля";
    if(D1->FieldByName("S_ld")->AsFloat==NULL) txt= txt+" S_ld,";
    if(D1->FieldByName("R_ld")->AsFloat==NULL) txt= txt+" R_ld,";
    if(D1->FieldByName("T_ld")->AsFloat==NULL) txt= txt+" T_ld,";
    if(D1->FieldByName("Stav1")->AsString.IsEmpty()) txt= txt+" Stav1,";
    if(D1->FieldByName("S_ld2")->AsFloat==NULL) txt= txt+" S_ld2,";
    if(D1->FieldByName("R_ld2")->AsFloat==NULL) txt= txt+" R_ld2,";
    if(D1->FieldByName("T_ld2")->AsFloat==NULL) txt= txt+" T_ld2,";
    if(D1->FieldByName("Stav2")->AsString.IsEmpty()) txt= txt+" Stav2";
    if(txt[txt.Length()]==',') txt.Delete(txt.Length(),1);
    txt= txt+" не заполнены";
    AddStr(rec,txt,numrec,rn,LS);
   }
//E017
   if((!D1->FieldByName("Prim_m")->AsString.IsEmpty()&D1->FieldByName("Prim_m")->AsString.Pos(";")==0)
      &
     (D1->FieldByName("S_ml1")->AsFloat==NULL|D1->FieldByName("Stavm1")->AsString.IsEmpty()))
   {
    txt= " - в поле Prim_m обозначена одна льгота, а поля";
    if(D1->FieldByName("S_ml1")->AsFloat==NULL) txt= txt+" S_ml1,";
    if(D1->FieldByName("Stavm1")->AsString.IsEmpty()) txt= txt+" Stavm1";
    if(txt[txt.Length()]==',') txt.Delete(txt.Length(),1);
    txt= txt+" не заполнены";
    AddStr(rec,txt,numrec,rn,LS);
   }
//E018
   if((!D1->FieldByName("Prim_m")->AsString.IsEmpty()&D1->FieldByName("Prim_m")->AsString.Pos(";")!=0)
      &
     (D1->FieldByName("S_ml1")->AsFloat==NULL|D1->FieldByName("Stavm1")->AsString.IsEmpty()|
      D1->FieldByName("S_ml2")->AsFloat==NULL|D1->FieldByName("Stavm2")->AsString.IsEmpty()))
   {
    txt= " - в поле Prim_m обозначены две льготы, а поля";
    if(D1->FieldByName("S_ml1")->AsFloat==NULL) txt= txt+" S_ml1,";
    if(D1->FieldByName("Stavm1")->AsString.IsEmpty()) txt= txt+" Stavm1,";
    if(D1->FieldByName("S_ml2")->AsFloat==NULL) txt= txt+" S_ml2,";
    if(D1->FieldByName("Stavm2")->AsString.IsEmpty()) txt= txt+" Stavm2";
    if(txt[txt.Length()]==',') txt.Delete(txt.Length(),1);
    txt= txt+" не заполнены";
    AddStr(rec,txt,numrec,rn,LS);
   }*/
//E019
   if(ChBdblls->Checked)
   {
    AnsiString gek=D1->FieldByName("Gek")->AsString,sch=D1->FieldByName("Schet")->AsString;
    D3->Active= false;
    D3->FilePath= dir;
    D3->TableName= ExtractFileName(FLB1->Items->Strings[i]);
    D3->Active= true;
    D3->RecNo= rn+1;
    //D3->First();//---
    txt= " - лицевой "+gek+sch+" в записи "+IntToStr(rn)+" такой-же как в записях:";
//    int zapis=D3->RecNo;
    int zapis;//---
    bool dv=false;
    while(!D3->Eof)
    {
     zapis=D3->RecNo;
     if(D3->FieldByName("Gek")->AsString==gek & D3->FieldByName("Schet")->AsString==sch & zapis!=rn)
     {
      txt= txt+IntToStr(zapis)+",";
      dv=true;
     }
     D3->Next();
     Application->ProcessMessages();
    }
    D3->Active= false;
    if(txt[txt.Length()]==',') txt.Delete(txt.Length(),1);
    if(dv)
    {
     AddStr(rec,txt,numrec,rn,LS);
     e019++;
    }
   }
//E020
   AnsiString pind=D1->FieldByName("P_ind")->AsString;
   if(pind=="000000")
   {
    txt= " - в поле P_ind 6 нулей: "+pind;
    AddStr(rec,txt,numrec,rn,LS);
    e020++;
   }
//E021
/*   bool ex=false;
   for(int f=0;f<spisok->Count;f++)
   {
    if(spisok->Strings[f]==D1->FieldByName("P_ind")->AsString) ex= true;
    Application->ProcessMessages();
   }
   int p_otd=0;
   AnsiString zap="";
   if(!ex)//если почт. отденения в spisok не найдено,то
   {
    spisok->Add(D1->FieldByName("P_ind")->AsString);//вносим в spisok
    D3->Active= false;
    D3->FilePath= dir;
    D3->TableName= ExtractFileName(FLB1->Items->Strings[i]);
    D3->Open();
    D3->RecNo= D1->RecNo;//+1;
    while(!D3->Eof)
    {
     if(D3->FieldByName("P_ind")->AsString==D1->FieldByName("P_ind")->AsString)
     {
      p_otd++;
      zap= zap+IntToStr(D3->RecNo)+",";
     }
     D3->Next();
     Application->ProcessMessages();
    }
    D3->Close();
    if(zap.Length()>0)
    {
     if(zap[zap.Length()]==',') zap.Delete(zap.Length(),1);
    }
    if(p_otd<kolvo)
    {
     txt= " - количество аб-ов почтовых отделений (поле P_ind:";
     if(D1->FieldByName("P_ind")->AsString=="") txt= txt+" пустое)";
     else txt= txt+" "+D1->FieldByName("P_ind")->AsString+")";
     txt= txt+" меньше "+IntToStr(kolvo)+", а именно "+IntToStr(p_otd);
     if(p_otd>1) txt= txt+" (также в записях №:"+zap+" проверяемого файла)";
     AddStr(rec,txt,numrec,rn,LS);
     e021++;
    }
   }//end_if(!ex)*/
//E022
   double val=D1->FieldByName("It_e")->AsFloat;
   if(val<=value)
   {
    txt= " - значение поля It_e <= "+FormatFloat("######0.00",value)+", а именно ("+FormatFloat("######0.00",val)+")";
    AddStr(rec,txt,numrec,rn,LS);
    e022++;
   }
//E023
   AnsiString p_ind=D1->FieldByName("P_ind")->AsString;
   int ispr=D1->FieldByName("Isprint")->AsInteger;
   bool error=false, probel=false;
   txt= "";
   if(ispr==1)
   {
    //в P_ind кол-во цифр менее 6
    int kol=0;
    for(int i=1;i<=p_ind.Length();i++)
    {
     if(p_ind[i]=='0'|p_ind[i]=='1'|p_ind[i]=='2'|p_ind[i]=='3'|p_ind[i]=='4'|p_ind[i]=='5'|p_ind[i]=='6'|p_ind[i]=='7'|p_ind[i]=='8'|p_ind[i]=='9') kol++;
     Application->ProcessMessages();
    }
    if(kol<6)
    {
     txt= txt+" в P_ind кол-во цифр менее 6;";
     error= true;
     e023++;
    }
    //первый символ в P_ind не 4
    if(p_ind.SubString(1,1)!='4')
    {
     txt= txt+" первый символ в P_ind не '4';";
     error= true;
     e023++;
    }
    //P_ind содержит пробелы
    for(int i=1;i<=p_ind.Length();i++)
    {
     if(p_ind[i]==' ') probel= true;
     Application->ProcessMessages();
    }
    if(probel)
    {
     txt= txt+" P_ind содержит пробелы;";
     error= true;
     e023++;
    }
    if(error)
    {
     txt= " - некорректный P_ind("+p_ind+"):"+txt;
     AddStr(rec,txt,numrec,rn,LS);
    }
   }//end_if(ispr)
//E024
   int gek_kol=D1->FieldByName("Gek")->AsString.Length(),sch_kol=D1->FieldByName("Schet")->AsString.Length();
   AnsiString licevoy=D1->FieldByName("Gek")->AsString;
   licevoy= licevoy+D1->FieldByName("Schet")->AsString;
   if(gek_kol+sch_kol!=10)
   {
    txt= " - лицевой счёт не 10 символов, а "+IntToStr(gek_kol+sch_kol)+": "+licevoy;
    AddStr(rec,txt,numrec,rn,LS);
    e024++;
   }
//E025
   double it_e=D1->FieldByName("It_e")->AsFloat;
   if(it_e==0) rec_null++;
//E027
//   int isprint=D1->FieldByName("isprint")->AsInteger;
//   if(isprint!=1)
//   {
//    txt= " - Isprint не равен 1";
//    AddStr(rec,txt,numrec,rn,LS);
//   }
//E028
   int ny4d=D1->FieldByName("ny4d")->AsInteger;
   if(ny4d==0) ny4d_kol++;
//E029
/*   int chast=D1->FieldByName("Chast")->AsInteger;
   int r_dom=D1->FieldByName("R_dom")->AsInteger;
   bool empneg=false;
   double t_odrd=D1->FieldByName("T_odrd")->AsFloat;
   double plmoi=D1->FieldByName("Plmoi")->AsFloat;
   double plfl=D1->FieldByName("Plfl")->AsFloat;
   if((chast==2)&(r_dom!=0))
   {
    if(D1->FieldByName("T_odrd")->AsFloat==NULL|t_odrd<0) empneg = true;
    if(D1->FieldByName("Plmoi")->AsFloat==NULL|plmoi<0) empneg = true;
    if(D1->FieldByName("Plfl")->AsFloat==NULL|plfl<0) empneg = true;
    if(empneg)
    {
     txt= " - некорректно заполнены поля T_ODRD="+FloatToStr(t_odrd)+", PLMOI="+FloatToStr(plmoi)+", PLFL="+FloatToStr(plfl);
     AddStr(rec,txt,numrec,rn,LS);
     e029++;
    }
   }
//E030
   int isshetodn=D1->FieldByName("Isshetodn")->AsInteger;
   int rdomsum=D1->FieldByName("Rdomsum")->AsInteger;
   if((chast==2)&(isshetodn==1))
   {
    if((D1->FieldByName("Rdomsum")->AsInteger==NULL)|rdomsum==0)
    {
     txt= " - поле RDomSum не заполнено;";
     AddStr(rec,txt,numrec,rn,LS);
     e030++;
    }
   }*/
//E031
//   int rdomodn=D1->FieldByName("Rdomodn")->AsInteger;
//   double normodr=D1->FieldByName("Normodr")->AsFloat;
//   bool b_031=false;
//   if((chast==2)&(isshetodn==0))
//   {
//    if((D1->FieldByName("Rdomodn")->AsInteger==NULL)|rdomodn==0) b_031 = true;
//    if((D1->FieldByName("Normodr")->AsFloat==NULL)|normodr==0) b_031 = true;
//    if(b_031)
//    {
//     txt= " - поле RDomOdn или(и) NormODR не заполнено;";
//     AddStr(rec,txt,numrec,rn,LS);
//     e031++;
//    }
//   }

   
   //==============
   //если_добавляли_в_er.txt - добавим в er.dbf
   if(b)
   {
    AddRecDBF(D1, D2);
    numrec++;
   }


   D1->Next();
   Application->ProcessMessages();
  }//end_while(!D1->Eof)
  D1->Active= false;
  D2->Active= false;


  //E025=================================
  if(rec_null!=0)
  {
   double procent=((double)rec_null*100)/(double)rr;
   list->Add(" ");
   list->Add("Количество нулевых значений в поле It_e: "+FormatFloat("######0.00",procent)+"%");
  }
  //E10_1================================
  if(fio_empty!=0)
  {
   list->Add(" ");
   list->Add("Количество записей с пустым полем FIO: "+IntToStr(fio_empty));
  }
  //E10_2================================
  if(street_empty!=0)
  {
   list->Add(" ");
   list->Add("Количество записей с пустым полем UL: "+IntToStr(street_empty));
  }
  //E026=================================
//E026
  list->Add(" ");
  int ch;
  bool ex=false;
  D1->Active= false;
  if(dir.IsEmpty()) dir= GetCurrentDir()+"\\";
  D1->FilePath= dir;
  D1->TableName= ExtractFileName(FLB1->Items->Strings[i]);
  D1->Active= true;
  D1->First();
  chlist->Clear();
  while(!D1->Eof)//проход по файлу с заполнением списка
  {
   ch= D1->FieldByName("chast")->AsInteger;
   for(int spch=0;spch<=chlist->Count-1;spch++)
   {
    if(chlist->Strings[spch]==IntToStr(ch)) ex= true;
    Application->ProcessMessages();
   }
   if(!ex) chlist->Add(IntToStr(ch));
   ex=false;
   D1->Next();
   Application->ProcessMessages();
  }

  chlist->Sort();
  if(chlist->Count>0)
  {
   for(int spch=0;spch<=chlist->Count-1;spch++)//пробегаем по списку лицевых(э/э)
   {
    ch= 0;
    D1->First();
    while(!D1->Eof)
    {
     if(D1->FieldByName("chast")->AsInteger==StrToInt(chlist->Strings[spch])) ch++;
     D1->Next();
     Application->ProcessMessages();
    }//end_while
    if(ch>0)
    {
     list->Add("Количество записей где chast="+chlist->Strings[spch]+": "+IntToStr(ch));
    }
    Application->ProcessMessages();
   }//end_for
  }//end_if(chlist_count>0)
  D1->Active= false;
  //E028=================================
  if(ny4d_kol!=0)
  {
   list->Add(" ");
   list->Add("Количество записей c нулевыми значениями в поле NY4D: "+IntToStr(ny4d_kol));
  }
  //=====================================

  list->Add(" ");
  list->Add(" ПРОВЕРКА ФАЙЛА "+ExtractFileName(FLB1->Items->Strings[i])+" ЗАВЕРШЕНА!");
  list->Add(" ПРОВЕРЕНО ЗАПИСЕЙ: "+IntToStr(rn));

  //SAVING_DOC
  AnsiString fn=Directory;
  if(fn.Length()>4) fn= fn+"\\er"+name+".txt";
  else fn= fn+"er"+name+".txt";
  list->SaveToFile(fn);

  //STATISTIKA
  if(StatView!=0)
  {
   if(Application->MessageBox("ВНОСИТЬ РЕЗУЛЬТАТЫ ПРОВЕРКИ ФАЙЛА В СТАТИТСТИКУ?", "Вопрос", MB_OKCANCEL) != IDOK) ShowMessage("ВНЕСЕНИЕ В СТАТИСТИКУ ОТМЕНЕНО.");
   else Statistika();
  }
  else Statistika();
  }//if(FLb1->Selected)

  EndProvFile: //конец проверки текущего файла
  if(FLB1->Selected[i]) FLB1->Selected[i]= false;
  Form1->Refresh();
  Bcheck->Refresh();
  Application->ProcessMessages();
 }//end_for(i=0;FLB1;i++)

 ShowMessage("ПРОВЕРКА ФАЙЛОВ НА НАЛИЧИЕ ОШИБОК ЗАВЕРШЕНА!\n\nРЕЗУЛЬТАТЫ ПРОВЕРКИ НАХОДЯТСЯ В ПАПКЕ "+Directory);
 EndProv://остановка процесса проверки

 //}//end_else_if(Directory.IsEmpty())
}//end_else_if(FLB1->SelCount==0)

}//end_try

__finally
{
 Bcheck->Caption= "Проверить";
 CBmes->Enabled= true;
 ChBselall->Enabled= true;
 Bsel->Enabled= true;
 FLB1->Enabled= true;
 ChBdblls->Enabled= true;
 Bcheck->Enabled= true;
 Bstatuch->Enabled= true;
 Bstatsum->Enabled= true;
 BBclose->Enabled= true;
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BselClick(TObject *Sender)
{
 //SelectDirectory("Выберите папку с файлами для проверки","",dir);
 SelectDirectory(dir, TSelectDirOpts() ,SELDIRHELP);
 if(dir.IsEmpty()) ShowMessage("ПАПКА С ФАЙЛАМИ ДЛЯ ПРОВЕРКИ НЕ БЫЛА ВЫБРАНА!");
 else
 {
  FLB1->Directory= dir;
  Directory= dir;
 }

 ChBselall->Checked= false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ChBselallClick(TObject *Sender)
{
 if(FLB1->Items->Count==0) ChBselall->Checked= false;
 else
 {
  if(ChBselall->Checked==true)
  {
   for(int i=0;i<FLB1->Items->Count;i++)
   {
    if(!FLB1->Selected[i])
    {
     FLB1->Selected[i]= true;
     Form1->Refresh();
    }
    Application->ProcessMessages();
   }
   //проверка месяца
   for(int i=0;i<FLB1->Items->Count;i++)
   {
    if(FLB1->Selected[i])
    {
     D1->Active= false;
     if(dir.IsEmpty()) dir= GetCurrentDir()+"\\";
     D1->FilePath= dir;
     D1->TableName= ExtractFileName(FLB1->Items->Strings[i]);
     D1->Active= true;
     D1->First();
     AnsiString mes_opl=D1->FieldByName("mes_opl")->AsString.Trim();
     D1->Active= false;
     mes_opl= mes_opl.SubString(1,2);
     if(StrToInt(mes_opl)!=mes_num)
     {
      ShowMessage("НОМЕР МЕСЯЦА В ФАЙЛЕ "+FLB1->Items->Strings[i]+" НЕ СООТВЕТСТВУЕТ ВЫБРАННОМУ ВАМИ ("+CBmes->Items->Strings[CBmes->ItemIndex]+")!\nПРОВЕРКА ФАЙЛА НЕВОЗМОЖНА!");
      FLB1->Selected[i]=false;
      ChBselall->Checked= false;
     }
    }//if_FLB1->Selected
    Application->ProcessMessages();
   }//for
  }//end_if(ChBselall->Checked==true)

  if(ChBselall->Checked==false)
  {
   if(FLB1->SelCount==FLB1->Items->Count)
   {
    for(int i=0;i<FLB1->Items->Count;i++)
    {
     if(FLB1->Selected[i])
     {
      FLB1->Selected[i]= false;
      Form1->Refresh();
     }
     Application->ProcessMessages();
    }
   }
  }//end_if(ChBselall->Checked==false)
 }//end_if(FLB1->SelCount>0)
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FLB1Click(TObject *Sender)
{
 if(FLB1->SelCount==FLB1->Items->Count) ChBselall->Checked= true;
 else ChBselall->Checked= false;

 //проверка месяца
 int i=FLB1->ItemIndex;
 if(FLB1->Selected[i])
 {
  D1->Active= false;
  if(dir.IsEmpty()) dir= GetCurrentDir()+"\\";
  D1->FilePath= dir;
  D1->TableName= ExtractFileName(FLB1->Items->Strings[i]);
  D1->Active= true;
  D1->First();
  AnsiString mes_opl=D1->FieldByName("mes_opl")->AsString.Trim();
  D1->Active= false;
  mes_opl= mes_opl.SubString(1,2);
  if(StrToInt(mes_opl)!=mes_num)
  {
   ShowMessage("НОМЕР МЕСЯЦА В ФАЙЛЕ "+FLB1->Items->Strings[i]+" НЕ СООТВЕТСТВУЕТ ВЫБРАННОМУ ВАМИ ("+CBmes->Items->Strings[CBmes->ItemIndex]+")!\nПРОВЕРКА ФАЙЛА НЕВОЗМОЖНА!");
   FLB1->Selected[i]= false;
  }
 }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormDestroy(TObject *Sender)
{
 if(FileExists(ProgDir+"\\tmp_stat.dbf")) DeleteFile(ProgDir+"\\tmp_stat.dbf");
 if(FileExists(ProgDir+"\\tmp_sum.dbf")) DeleteFile(ProgDir+"\\tmp_sum.dbf");

 delete list;
 list= NULL;
 delete spisok;
 spisok= NULL;
 delete u4astki;
 u4astki= NULL;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CBmesChange(TObject *Sender)
{
 mes_num= CBmes->ItemIndex;
 mes_num++;

 if(CBmes->ItemIndex>=0)
 {
  Label1->Font->Color= clBlue;
  Label2->Font->Color= clBlue;
  ChBselall->Enabled= true;
  Bsel->Enabled= true;
  FLB1->Enabled= true;
  FLB1->Color= clWindow;
  ChBdblls->Enabled= true;
  Bcheck->Enabled= true;
 }

 for(int i=0;i<FLB1->Items->Count;i++) FLB1->Selected[i]= false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BstatuchClick(TObject *Sender)
{
 if(!FileExists(ProgDir+"\\stat.dbf"))
 {
  ShowMessage("ФАЙЛ СО СТАТИСТИКОЙ stat.dbf НЕ НАЙДЕН В ПАПКЕ С ПРОГРАММОЙ!");
 }
 else
 {
  Dstat->Active= false;
  Dstat->FilePath= ProgDir;
  Dstat->TableName= "stat.dbf";
  Dstat->Active= true;
  if(Dstat->RecNo==0)
  {
   Dstat->Active= false;
   ShowMessage("В ФАЙЛЕ СТАТИСТИКИ НЕТ ДАННЫХ!");
  }
  else
  {
   Dstat->Active= false;
   Form2->ShowModal();
  }//end_else_if(Dstat->RecNo==0)
 }//end_else_if(!FileExists)
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BstatsumClick(TObject *Sender)
{
 if(!FileExists(ProgDir+"\\stat.dbf"))
 {
  ShowMessage("ФАЙЛ СО СТАТИСТИКОЙ stat.dbf НЕ НАЙДЕН В ПАПКЕ С ПРОГРАММОЙ!");
 }
 else
 {
  Dstat->Active= false;
  Dstat->FilePath= ProgDir;
  Dstat->TableName= "stat.dbf";
  Dstat->Active= true;
  if(Dstat->RecNo==0)
  {
   Dstat->Active= false;
   ShowMessage("В ФАЙЛЕ СТАТИСТИКИ НЕТ ДАННЫХ!");
  }
  else
  {
   Dstat->Active= false;
   Form4->ShowModal();
  }//end_else_if(Dstat->RecNo==0)
 }//end_else_if(!FileExists)
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CopyStructDBF(AnsiString Path1, AnsiString FileName1, AnsiString Path2, AnsiString FileName2, TDbf *Dbf1, TDbf *Dbf2)
{
 //структура полей исходного dbf
 Dbf1->Active = false;
 Dbf1->FilePath = Path1;
 Dbf1->TableName = FileName1;
 Dbf1->Active = true;

 //структура полей создаваемого dbf
 Dbf2->Active = false;
 Dbf2->FilePath = Path2;
 Dbf2->TableName = FileName2;

 //подготовка к формированию структуры
 Dbf2->FieldDefs->Clear();
 Dbf2->LanguageID = DbfLangId_RUS_866;
 TDbfFieldDefs *fds = new TDbfFieldDefs(Dbf2);
 TDbfFieldDef *fd;

 int FieldCount1 = Dbf1->FieldCount;
 AnsiString fName;
 int fType, fSize, fPrecision;

 //проход по полям Dbf1
 for(int fNo=0; fNo < FieldCount1; fNo++)
 {
  fName = Dbf1->DbfFieldDefs->Items[fNo]->FieldName;
  fType = Dbf1->DbfFieldDefs->Items[fNo]->FieldType;
  fSize = Dbf1->DbfFieldDefs->Items[fNo]->Size;
  fPrecision = Dbf1->DbfFieldDefs->Items[fNo]->Precision;

  //по типу поля добавляем в список полей
  switch(fType)
  {
   case 1: //String
        fds->Add(fName,ftString,fSize,false);
        break;
   case 2: //Smallint
        fds->Add(fName,ftInteger,fSize,false);
        break;
   case 3: //Integer
        fds->Add(fName,ftInteger,fSize,false);
        break;
   case 4: //Word
        fds->Add(fName,ftInteger,fSize,false);
        break;
   case 6: //Float
        if(fPrecision==0) fds->Add(fName,ftInteger,fSize,false);
        else
        {
         fd = fds->AddFieldDef();
         fd->FieldName = fName;
         fd->NativeFieldType = 'N';
         fd->Size = fSize;
         fd->Precision = fPrecision;
        }
        break;
   case 9: //DateTime
        fds->Add(fName,ftDate,0,false);
        break;
   default: //Unknown
        fds->Add("unknown",ftUnknown,0,false);
        break;
  }//end_case
 }//end_for_Dbf1

 //создаём структуру
 Dbf2->CreateTableEx(fds);
 delete fds;

 Dbf1->Active= false;
 Dbf2->Active= false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::AddRecDBF(TDbf *Dbf1, TDbf *Dbf2)
{
 int FieldCount2 = Dbf2->FieldCount;
 AnsiString fName;
 int fType, fPrecision;
 int FieldCount1 = Dbf1->FieldCount;
 bool fe = false;
 AnsiString namef;

 Dbf2->Insert();

 //проход по полям Dbf2
 for(int fNo=0; fNo < FieldCount2; fNo++)
 {
  fName = Dbf2->DbfFieldDefs->Items[fNo]->FieldName;
  fType = Dbf2->DbfFieldDefs->Items[fNo]->FieldType;
  fPrecision = Dbf2->DbfFieldDefs->Items[fNo]->Precision;

  //проверяем наличие поля в Dbf1
  fe = false;
  for(int fNum=0; fNum < FieldCount1; fNum++)
  {
   namef = Dbf1->DbfFieldDefs->Items[fNum]->FieldName;
   if(fName==namef) fe = true;
  }

  if(fe)
  {
  //по типу поля добавляем данные в D_OUT
  switch(fType)
  {
   case 1: //String
        if(!Dbf1->FieldByName(fName)->AsString.IsEmpty()) Dbf2->FieldByName(fName)->AsString = Dbf1->FieldByName(fName)->AsString;
        break;
   case 2: //Smallint
        /*if(IntToStr(Dbf1->FieldByName(fName)->AsInteger)!="")*/ Dbf2->FieldByName(fName)->AsInteger = Dbf1->FieldByName(fName)->AsInteger;
        break;
   case 3: //Integer
        /*if(IntToStr(Dbf1->FieldByName(fName)->AsInteger)!="")*/ Dbf2->FieldByName(fName)->AsInteger = Dbf1->FieldByName(fName)->AsInteger;
        break;
   case 4: //Word
        /*if(IntToStr(Dbf1->FieldByName(fName)->AsInteger)!="")*/ Dbf2->FieldByName(fName)->AsInteger = Dbf1->FieldByName(fName)->AsInteger;
        break;
   case 6: //Float
        if(fPrecision==0) /*if(IntToStr(Dbf1->FieldByName(fName)->AsInteger)!="")*/ Dbf2->FieldByName(fName)->AsInteger = Dbf1->FieldByName(fName)->AsInteger;
        else /*if(FloatToStr(Dbf1->FieldByName(fName)->AsFloat)!="")*/ Dbf2->FieldByName(fName)->AsFloat = Dbf1->FieldByName(fName)->AsFloat;
        break;
   case 9: //DateTime
        if(DateTimeToStr(Dbf1->FieldByName(fName)->AsDateTime)!="30.12.1899") Dbf2->FieldByName(fName)->AsDateTime = Dbf1->FieldByName(fName)->AsDateTime;
        break;
   default: //Unknown
        break;
  }//end_case

  }//end_if(fe)
 }//end_for_Dbf2_FieldsCount

 Dbf2->Post();

// D_OUT->Active= false;
}
//---------------------------------------------------------------------------

