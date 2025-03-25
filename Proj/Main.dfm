object Form1: TForm1
  Left = 0
  Top = 0
  BorderStyle = bsSingle
  Caption = '  Network Perf Tracker'
  ClientHeight = 353
  ClientWidth = 557
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  DesignSize = (
    557
    353)
  PixelsPerInch = 96
  TextHeight = 13
  object PerformanceGraph1: TPerformanceGraph
    Left = 8
    Top = 108
    Width = 539
    Height = 118
    Anchors = [akLeft, akTop, akRight]
    Scale = 0
    Gradient = 100
    ExplicitWidth = 478
  end
  object Label1: TLabel
    Left = 8
    Top = 57
    Width = 50
    Height = 13
    Caption = 'LoopDelay'
  end
  object Label2: TLabel
    Left = 117
    Top = 57
    Width = 43
    Height = 13
    Caption = 'Time Out'
  end
  object Label3: TLabel
    Left = 214
    Top = 57
    Width = 47
    Height = 13
    Caption = 'Sensibility'
  end
  object Label4: TLabel
    Left = 320
    Top = 9
    Width = 27
    Height = 13
    Caption = 'Alarm'
  end
  object Label5: TLabel
    Left = 9
    Top = 84
    Width = 42
    Height = 13
    Caption = 'Log Path'
  end
  object Label6: TLabel
    Left = 318
    Top = 57
    Width = 47
    Height = 13
    Caption = 'AutoSave'
  end
  object LbxLog: TListBox
    Left = 9
    Top = 232
    Width = 540
    Height = 113
    Anchors = [akLeft, akTop, akRight, akBottom]
    ItemHeight = 13
    TabOrder = 0
  end
  object BtnStart: TButton
    Left = 8
    Top = 8
    Width = 73
    Height = 20
    Caption = 'Start'
    TabOrder = 1
    OnClick = BtnStartClick
  end
  object BtnStop: TButton
    Left = 87
    Top = 8
    Width = 73
    Height = 21
    Caption = 'Stop'
    TabOrder = 2
    OnClick = BtnStopClick
  end
  object EdLoopDelay: TEdit
    Left = 64
    Top = 54
    Width = 42
    Height = 21
    TabOrder = 3
    Text = '2000'
  end
  object EdTimeOut: TEdit
    Left = 166
    Top = 54
    Width = 42
    Height = 21
    TabOrder = 4
    Text = '1500'
  end
  object EdSensibility: TEdit
    Left = 267
    Top = 54
    Width = 42
    Height = 21
    TabOrder = 5
    Text = '2'
  end
  object EdAlarm: TEdit
    Left = 353
    Top = 6
    Width = 42
    Height = 21
    TabOrder = 6
    Text = '100'
  end
  object CbAutostart: TCheckBox
    Left = 176
    Top = 8
    Width = 73
    Height = 17
    Caption = 'Autostart'
    Enabled = False
    TabOrder = 7
  end
  object CbHidden: TCheckBox
    Left = 255
    Top = 8
    Width = 59
    Height = 17
    Caption = 'Hidden'
    Enabled = False
    TabOrder = 8
  end
  object EdLogPath: TEdit
    Left = 65
    Top = 81
    Width = 484
    Height = 21
    Anchors = [akLeft, akTop, akRight]
    TabOrder = 9
    Text = 'C:\Temp'
  end
  object EdUrl: TEdit
    Left = 8
    Top = 31
    Width = 339
    Height = 21
    TabOrder = 10
    Text = 'www.google.com'
  end
  object EdDelay: TEdit
    Left = 353
    Top = 30
    Width = 80
    Height = 21
    TabOrder = 11
    Text = '2000'
  end
  object EdAutoSave: TEdit
    Left = 371
    Top = 54
    Width = 42
    Height = 21
    TabOrder = 12
    Text = '500'
  end
  object LoopTimer: TTimer
    Enabled = False
    OnTimer = LoopTimerTimer
    Left = 432
    Top = 248
  end
end
