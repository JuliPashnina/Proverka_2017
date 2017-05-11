object Form4: TForm4
  Left = 192
  Top = 126
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Суммарная статистика'
  ClientHeight = 377
  ClientWidth = 409
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 409
    Height = 377
    Caption = 'Условия выбора данных'
    Color = clGray
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
    TabOrder = 0
    object Label1: TLabel
      Left = 64
      Top = 32
      Width = 283
      Height = 16
      Caption = 'Добавьте участки и выберите период'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clLime
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label4: TLabel
      Left = 120
      Top = 48
      Width = 174
      Height = 16
      Caption = 'для вывода статистики'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clLime
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object GroupBox2: TGroupBox
      Left = 8
      Top = 88
      Width = 209
      Height = 177
      Caption = 'Добавьте участки'
      Color = clSilver
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentColor = False
      ParentFont = False
      TabOrder = 0
      object CBuch: TComboBox
        Left = 8
        Top = 24
        Width = 73
        Height = 24
        Style = csDropDownList
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ItemHeight = 16
        ParentFont = False
        TabOrder = 0
      end
      object Button1: TButton
        Left = 8
        Top = 56
        Width = 97
        Height = 25
        Caption = 'Добавить ->'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 1
        OnClick = Button1Click
      end
      object LBuch: TListBox
        Left = 128
        Top = 24
        Width = 73
        Height = 113
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ItemHeight = 16
        ParentFont = False
        TabOrder = 2
      end
      object Button2: TButton
        Left = 128
        Top = 144
        Width = 73
        Height = 25
        Caption = 'Удалить'
        Enabled = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 3
        OnClick = Button2Click
      end
    end
    object GroupBox3: TGroupBox
      Left = 240
      Top = 88
      Width = 161
      Height = 177
      Caption = 'Выберите период'
      Color = clSilver
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentColor = False
      ParentFont = False
      TabOrder = 1
      object Label2: TLabel
        Left = 24
        Top = 64
        Width = 11
        Height = 16
        Caption = 'С'
      end
      object Label3: TLabel
        Left = 16
        Top = 120
        Width = 21
        Height = 16
        Caption = 'По'
      end
      object DTP1: TDateTimePicker
        Left = 40
        Top = 56
        Width = 105
        Height = 24
        CalAlignment = dtaLeft
        Date = 39335.4098895023
        Time = 39335.4098895023
        DateFormat = dfShort
        DateMode = dmComboBox
        Kind = dtkDate
        ParseInput = False
        TabOrder = 0
      end
      object DTP2: TDateTimePicker
        Left = 40
        Top = 112
        Width = 105
        Height = 24
        CalAlignment = dtaLeft
        Date = 39335.4099101157
        Time = 39335.4099101157
        DateFormat = dfShort
        DateMode = dmComboBox
        Kind = dtkDate
        ParseInput = False
        TabOrder = 1
      end
    end
    object BitBtn1: TBitBtn
      Left = 304
      Top = 344
      Width = 91
      Height = 25
      Anchors = [akLeft, akBottom]
      Caption = 'Закрыть'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 2
      Kind = bkClose
    end
    object Button3: TButton
      Left = 112
      Top = 288
      Width = 185
      Height = 33
      Caption = 'Вывести статистику'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 3
      OnClick = Button3Click
    end
  end
  object Dsum1: TDbf
    IndexDefs = <>
    OpenMode = omAutoCreate
    TableLevel = 4
    UseFloatFields = True
    Left = 16
    Top = 344
  end
  object Dsum2: TDbf
    IndexDefs = <>
    OpenMode = omAutoCreate
    TableLevel = 4
    UseFloatFields = True
    Left = 48
    Top = 344
  end
end
