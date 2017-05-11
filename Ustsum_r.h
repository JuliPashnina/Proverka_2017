//---------------------------------------------------------------------------

#ifndef Ustsum_rH
#define Ustsum_rH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <QuickRpt.hpp>
#include <Qrctrls.hpp>
#include "dbf.hpp"
#include <Db.hpp>
//---------------------------------------------------------------------------
class TForm5 : public TForm
{
__published:	// IDE-managed Components
        TDbf *Dsum;
        TQuickRep *QuickRep1;
        TQRBand *QRBand1;
        TQRLabel *QRLabel1;
        TQRBand *QRBand2;
        TQRMemo *QRMemo1;
        TQRMemo *QRMemo2;
        TQRMemo *QRMemo3;
        TQRMemo *QRMemo4;
        TQRMemo *QRMemo5;
        TQRMemo *QRMemo6;
        TQRMemo *QRMemo7;
        TQRMemo *QRMemo8;
        TQRMemo *QRMemo9;
        TQRMemo *QRMemo10;
        TQRMemo *QRMemo11;
        TQRMemo *QRMemo12;
        TQRMemo *QRMemo13;
        TQRMemo *QRMemo14;
        TQRMemo *QRMemo15;
        TQRMemo *QRMemo16;
        TQRMemo *QRMemo17;
        TQRMemo *QRMemo18;
        TQRMemo *QRMemo19;
        TQRMemo *QRMemo20;
        TQRMemo *QRMemo21;
        TQRMemo *QRMemo22;
        TQRMemo *QRMemo23;
        TQRBand *QRBand3;
        TQRDBText *QRDBText1;
        TQRDBText *QRDBText2;
        TQRDBText *QRDBText3;
        TQRDBText *QRDBText4;
        TQRDBText *QRDBText5;
        TQRDBText *QRDBText6;
        TQRDBText *QRDBText7;
        TQRDBText *QRDBText8;
        TQRDBText *QRDBText9;
        TQRDBText *QRDBText10;
        TQRDBText *QRDBText11;
        TQRDBText *QRDBText12;
        TQRDBText *QRDBText13;
        TQRDBText *QRDBText14;
        TQRDBText *QRDBText15;
        TQRDBText *QRDBText16;
        TQRDBText *QRDBText17;
        TQRDBText *QRDBText18;
        TQRDBText *QRDBText19;
        TQRDBText *QRDBText20;
        TQRDBText *QRDBText21;
        TQRDBText *QRDBText22;
        TQRExpr *QRExpr1;
        TQRBand *QRBand4;
        TQRLabel *QRLabel2;
        TQRExpr *QRExpr2;
        void __fastcall QuickRep1AfterPreview(TObject *Sender);
private:	// User declarations
public:		// User declarations
void StatSum(AnsiString);
        __fastcall TForm5(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm5 *Form5;
//---------------------------------------------------------------------------
#endif
