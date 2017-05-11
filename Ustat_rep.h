//---------------------------------------------------------------------------

#ifndef Ustat_repH
#define Ustat_repH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <QuickRpt.hpp>
#include "dbf.hpp"
#include <Db.hpp>
#include <Qrctrls.hpp>
//---------------------------------------------------------------------------
class TForm3 : public TForm
{
__published:	// IDE-managed Components
        TDbf *Drep;
        TQuickRep *QuickRep1;
        TQRBand *QRBand1;
        TQRLabel *QRLabel1;
        TQRDBText *QRDBText1;
        TQRLabel *QRLabel2;
        TQRDBText *QRDBText2;
        TQRLabel *QRLabel3;
        TQRDBText *QRDBText3;
        TQRLabel *QRLabel4;
        TQRDBText *QRDBText4;
        TQRLabel *QRLabel5;
        TQRDBText *QRDBText5;
        TQRLabel *QRLabel6;
        TQRDBText *QRDBText6;
        TQRLabel *QRLabel7;
        TQRDBText *QRDBText7;
        TQRLabel *QRLabel8;
        TQRDBText *QRDBText8;
        TQRLabel *QRLabel9;
        TQRDBText *QRDBText9;
        TQRLabel *QRLabel10;
        TQRDBText *QRDBText10;
        TQRLabel *QRLabel11;
        TQRDBText *QRDBText11;
        TQRLabel *QRLabel12;
        TQRDBText *QRDBText12;
        TQRLabel *QRLabel13;
        TQRDBText *QRDBText13;
        TQRLabel *QRLabel14;
        TQRDBText *QRDBText14;
        TQRLabel *QRLabel15;
        TQRLabel *QRLabel16;
        TQRDBText *QRDBText15;
        TQRLabel *QRLabel17;
        TQRDBText *QRDBText16;
        TQRLabel *QRLabel18;
        TQRDBText *QRDBText17;
        TQRLabel *QRLabel19;
        TQRDBText *QRDBText18;
        TQRLabel *QRLabel20;
        TQRDBText *QRDBText19;
        TQRLabel *QRLabel21;
        TQRDBText *QRDBText20;
        TQRLabel *QRLabel22;
        TQRDBText *QRDBText21;
        TQRLabel *QRLabel23;
        TQRDBText *QRDBText22;
        TQRLabel *QRLabel24;
        TQRDBText *QRDBText23;
        TQRExpr *QRExpr1;
        void __fastcall QuickRep1AfterPreview(TObject *Sender);
private:	// User declarations
public:		// User declarations
void StatRep(void);

        __fastcall TForm3(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm3 *Form3;
//---------------------------------------------------------------------------
#endif
