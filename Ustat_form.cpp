//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Ustat_form.h"
#include "Uproverka.h"
#include "Ustat_rep.h"
#include <stdio.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dbf"
#pragma link "dbf"
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm2::FormShow(TObject *Sender)
{
 LB1->Clear();
 LB2->Clear();
 //dobavlenie_dat_iz_stat.dbf
 Dst1->Active= false;
 Dst1->FilePath= Form1->ProgDir;
 Dst1->TableName= "stat.dbf";
 Dst1->Active= true;
 AnsiString data="",dt="";
 int dat=0;

 while(!Dst1->Eof)
 {
  data= Dst1->FieldByName("n_mes")->AsString.Trim();
  dt= data;
  dat= StrToInt(dt.Delete(3,2));
  data.Insert(".20",3);
  data+= NameMonth(dat);
  data+= "уч."+IntToStr(Dst1->FieldByName("n_uch")->AsInteger);
  LB1->Items->Add(data);
  Dst1->Next();
 }

 Dst1->Active= false;
}
//---------------------------------------------------------------------------
AnsiString TForm2::NameMonth(int num)
{
 AnsiString ImyaMes="";
 switch(num)
 {
  case  1: ImyaMes= "(Январь)";   break;
  case  2: ImyaMes= "(Февраль)";  break;
  case  3: ImyaMes= "(Март)";     break;
  case  4: ImyaMes= "(Апрель)";   break;
  case  5: ImyaMes= "(Май)";      break;
  case  6: ImyaMes= "(Июнь)";     break;
  case  7: ImyaMes= "(Июль)";     break;
  case  8: ImyaMes= "(Август)";   break;
  case  9: ImyaMes= "(Сентябрь)"; break;
  case 10: ImyaMes= "(Октябрь)";  break;
  case 11: ImyaMes= "(Ноябрь)";   break;
  case 12: ImyaMes= "(Декабрь)";  break;
 }
 return ImyaMes;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button1Click(TObject *Sender)
{
 if(LB1->ItemIndex<0) ShowMessage("НУЖНО ВЫБРАТЬ ДАТУ В СПИСКЕ ДОСТУПНЫХ ДАТ!");
 else
 {
  LB2->Items->Add(LB1->Items->Strings[LB1->ItemIndex]);
  if(LB2->Items->Count>0) Button2->Enabled= true;
  LB1->Items->Delete(LB1->ItemIndex);
  if(LB1->Items->Count==0) Button1->Enabled= false;
  else Button1->Enabled= true;
 }
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button2Click(TObject *Sender)
{
 if(LB2->ItemIndex<0) ShowMessage("НУЖНО ВЫБРАТЬ ДАТУ В СПИСКЕ ДАТ ДЛЯ СТАТИСТИКИ!");
 else
 {
  LB1->Items->Add(LB2->Items->Strings[LB2->ItemIndex]);
  if(LB1->Items->Count>0) Button1->Enabled= true;
  LB2->Items->Delete(LB2->ItemIndex);
  if(LB2->Items->Count==0) Button2->Enabled= false;
  else Button2->Enabled= true;
 }
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button3Click(TObject *Sender)
{
 if(LB2->Items->Count==0) ShowMessage("ДОБАВЬТЕ ДАТЫ ДЛЯ СТАТИСТИКИ!");
 else
 {
  //создаём временный файл
  if(!FileExists(Form1->ProgDir+"\\tmp_stat.dbf"))
  {
   Dst2->Active= false;
   Dst2->FilePath= Form1->ProgDir;
   Dst2->TableName= "tmp_stat.dbf";
   Dst2->FieldDefs->Clear();
   Dst2->FieldDefs->Add("n_mes",ftString,20,false);
   Dst2->FieldDefs->Add("n_uch",ftInteger,0,false);
   Dst2->FieldDefs->Add("e001",ftInteger,0,false);
   Dst2->FieldDefs->Add("e002",ftInteger,0,false);
   Dst2->FieldDefs->Add("e003",ftInteger,0,false);
   Dst2->FieldDefs->Add("e004",ftInteger,0,false);
   Dst2->FieldDefs->Add("e005",ftInteger,0,false);
   Dst2->FieldDefs->Add("e006",ftInteger,0,false);
   Dst2->FieldDefs->Add("e007",ftInteger,0,false);
   Dst2->FieldDefs->Add("e008",ftInteger,0,false);
   Dst2->FieldDefs->Add("e009",ftInteger,0,false);
   Dst2->FieldDefs->Add("e010",ftInteger,0,false);
   Dst2->FieldDefs->Add("e010_1",ftInteger,0,false);
   Dst2->FieldDefs->Add("e010_2",ftInteger,0,false);
   Dst2->FieldDefs->Add("e011",ftInteger,0,false);
   Dst2->FieldDefs->Add("e013",ftInteger,0,false);
   Dst2->FieldDefs->Add("e019",ftInteger,0,false);
   Dst2->FieldDefs->Add("e020",ftInteger,0,false);
   Dst2->FieldDefs->Add("e021",ftInteger,0,false);
   Dst2->FieldDefs->Add("e022",ftInteger,0,false);
   Dst2->FieldDefs->Add("e023",ftInteger,0,false);
   Dst2->FieldDefs->Add("e024",ftInteger,0,false);
   Dst2->FieldDefs->Add("e025",ftInteger,0,false);
   Dst2->CreateTable();
  }
  else
  {
   Dst2->Active= true;
   if(Dst2->RecordCount>0) while(!Dst2->Eof) Dst2->Delete();
  }
  //kodirovka
  FILE *F;
  char cRus='\0';
  AnsiString rai=Form1->ProgDir+"\\tmp_stat.dbf";
  F= fopen(rai.c_str(),"r+");
  fseek(F,29,0);
  fwrite(&cRus,sizeof(cRus),1,F);
  fclose(F);

  //пробегаем по строкам LB2
  for(int sp2=0;sp2<LB2->Items->Count;sp2++)
  {
   //извлекаем из строки мес-год и участок
   AnsiString NameStr= LB2->Items->Strings[sp2];
   AnsiString stroka=NameStr, mes="";
   int uch=0;
   mes= NameStr.SubString(1,2)+NameStr.SubString(6,2);
   stroka.Delete(1,stroka.Pos("."));
   stroka.Delete(1,stroka.Pos("."));
   uch= StrToInt(stroka);

   //ищем запись в stat.dbf по mes и uch
   Dst1->Active= false;
   Dst1->FilePath= Form1->ProgDir;
   Dst1->TableName= "stat.dbf";
   Dst1->Active= true;
   while(!Dst1->Eof)
   {
    if(Dst1->FieldByName("n_mes")->AsString.Trim()==mes.Trim() & Dst1->FieldByName("n_uch")->AsInteger==uch)
    {
     //вносим в файл tmp_stat.dbf найденную запись
     Dst2->Active= false;
     Dst2->FilePath= Form1->ProgDir;
     Dst2->TableName= "tmp_stat.dbf";
     Dst2->Active= true;
     Dst2->Insert();
     Dst2->FieldByName("n_mes")->AsString= NameStr.SubString(1,NameStr.Pos(")"));
     Dst2->FieldByName("n_uch")->AsInteger= uch;
     Dst2->FieldByName("e001")->AsInteger= Dst1->FieldByName("e001")->AsInteger;
     Dst2->FieldByName("e002")->AsInteger= Dst1->FieldByName("e002")->AsInteger;
     Dst2->FieldByName("e003")->AsInteger= Dst1->FieldByName("e003")->AsInteger;
     Dst2->FieldByName("e004")->AsInteger= Dst1->FieldByName("e004")->AsInteger;
     Dst2->FieldByName("e005")->AsInteger= Dst1->FieldByName("e005")->AsInteger;
     Dst2->FieldByName("e006")->AsInteger= Dst1->FieldByName("e006")->AsInteger;
     Dst2->FieldByName("e007")->AsInteger= Dst1->FieldByName("e007")->AsInteger;
     Dst2->FieldByName("e008")->AsInteger= Dst1->FieldByName("e008")->AsInteger;
     Dst2->FieldByName("e009")->AsInteger= Dst1->FieldByName("e009")->AsInteger;
     Dst2->FieldByName("e010")->AsInteger= Dst1->FieldByName("e010")->AsInteger;
     Dst2->FieldByName("e010_1")->AsInteger= Dst1->FieldByName("e010_1")->AsInteger;
     Dst2->FieldByName("e010_2")->AsInteger= Dst1->FieldByName("e010_2")->AsInteger;
     Dst2->FieldByName("e011")->AsInteger= Dst1->FieldByName("e011")->AsInteger;
     Dst2->FieldByName("e013")->AsInteger= Dst1->FieldByName("e013")->AsInteger;
     Dst2->FieldByName("e019")->AsInteger= Dst1->FieldByName("e019")->AsInteger;
     Dst2->FieldByName("e020")->AsInteger= Dst1->FieldByName("e020")->AsInteger;
     Dst2->FieldByName("e021")->AsInteger= Dst1->FieldByName("e021")->AsInteger;
     Dst2->FieldByName("e022")->AsInteger= Dst1->FieldByName("e022")->AsInteger;
     Dst2->FieldByName("e023")->AsInteger= Dst1->FieldByName("e023")->AsInteger;
     Dst2->FieldByName("e024")->AsInteger= Dst1->FieldByName("e024")->AsInteger;
     Dst2->FieldByName("e025")->AsInteger= Dst1->FieldByName("e025")->AsInteger;
     Dst2->Post();
     Dst2->Active= false;

     Dst1->Last();             
    }
    else
    Dst1->Next();
   }//end_while(!Dst1->Eof)
   Dst1->Active= false;
  }//end_for(int sp2=0;sp2<LB2->Items->Count;sp2++)
  Form3->StatRep();
 }//end_else_if(LB2->Items->Count==0)
}
//---------------------------------------------------------------------------
