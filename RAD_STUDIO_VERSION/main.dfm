object Form1: TForm1
  Left = 654
  Top = 291
  Caption = 'SQLITE_APP'
  ClientHeight = 461
  ClientWidth = 663
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  Position = poDesigned
  TextHeight = 15
  object additional_info_label: TLabel
    Left = 272
    Top = 327
    Width = 3
    Height = 15
  end
  object our_tree: TVirtualStringTree
    Left = 8
    Top = 8
    Width = 633
    Height = 313
    AccessibleName = 'our_tree'
    Color = clMenu
    DefaultNodeHeight = 19
    Header.AutoSizeIndex = 20
    Header.Background = clHotLight
    Header.Options = [hoColumnResize, hoDrag, hoShowSortGlyphs, hoVisible]
    TabOrder = 0
    WantTabs = True
    OnAddToSelection = our_treeAddToSelection
    OnGetText = our_treeGetText
    Touch.InteractiveGestures = [igPan, igPressAndTap]
    Touch.InteractiveGestureOptions = [igoPanSingleFingerHorizontal, igoPanSingleFingerVertical, igoPanInertia, igoPanGutter, igoParentPassthrough]
    Columns = <
      item
        Position = 0
        Text = 'URL'
        Width = 281
      end
      item
        Position = 1
        Text = 'Title'
        Width = 221
      end>
  end
  object open_file_button: TButton
    Left = 8
    Top = 335
    Width = 193
    Height = 49
    Caption = #1054#1090#1082#1088#1099#1090#1100' '#1041#1044
    TabOrder = 1
    OnClick = open_file_buttonClick
  end
  object delete_button: TButton
    Left = 8
    Top = 402
    Width = 193
    Height = 51
    Caption = #1059#1076#1072#1083#1080#1090#1100' '#1079#1072#1087#1080#1089#1100
    TabOrder = 2
    OnClick = delete_buttonClick
  end
  object file_open: TOpenDialog
    Left = 632
    Top = 432
  end
end
