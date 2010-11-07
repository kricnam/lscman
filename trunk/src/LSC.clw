; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAWSFactorDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "LSC.h"

ClassCount=7
Class1=CLSCApp
Class2=CLSCDlg

ResourceCount=7
Resource2=IDD_DIALOG_SPECTRUM
Resource1=IDR_MAINFRAME
Class3=CDataCollectionDlg
Resource3=IDD_LSC_DIALOG
Class4=CFileSettingDlg
Resource4=IDD_DIALOG_DATA_COLLECTION
Resource5=IDD_DIALOG_AWS_FACTOR_SETTING
Class5=CAWSFactorSttingDlg
Class6=CSpectrumDlg
Resource6=IDD_DIALOG_FILE_SETTING
Class7=CAWSFactorDlg
Resource7=IDD_DIALOG_AWS_FACTOR

[CLS:CLSCApp]
Type=0
HeaderFile=LSC.h
ImplementationFile=LSC.cpp
Filter=N

[CLS:CLSCDlg]
Type=0
HeaderFile=LSCDlg.h
ImplementationFile=LSCDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CLSCDlg



[DLG:IDD_LSC_DIALOG]
Type=1
Class=CLSCDlg
ControlCount=0

[DLG:IDD_DIALOG_FILE_SETTING]
Type=1
Class=CFileSettingDlg
ControlCount=17
Control1=IDC_BUTTON_DATA_COLLECTION,button,1342242816
Control2=IDC_STATIC,button,1342177287
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_COMBO_MYNO,combobox,1344339971
Control8=IDC_RADIO_COLLECTION_YES,button,1342308361
Control9=IDC_RADIO__COLLECTION_NO,button,1342177289
Control10=IDC_COMBO_EXTEN,combobox,1344339971
Control11=IDC_EDIT_FILENAME,edit,1350633600
Control12=IDC_BUTTON_OPEN_FILEDIA,button,1342242816
Control13=IDC_BUTTON_SET,button,1342242816
Control14=IDC_LIST_SET,SysListView32,1350631425
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_COMBO_COMNO,combobox,1344339971

[DLG:IDD_DIALOG_DATA_COLLECTION]
Type=1
Class=CDataCollectionDlg
ControlCount=16
Control1=IDC_BUTTON_FILE_SETTING,button,1342242816
Control2=IDC_BUTTON_SPECTRUM,button,1342242816
Control3=IDC_BUTTON_AWS_FACTOR,button,1342242816
Control4=IDC_BUTTON_SHUT_DOWN,button,1342242816
Control5=IDC_STATIC,button,1342177287
Control6=IDC_STATIC,button,1342177287
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_EDIT_START_TIME,edit,1350633601
Control13=IDC_EDIT_CURRENT_TIME,edit,1350633601
Control14=IDC_EDIT_MYNO,edit,1350633601
Control15=IDC_EDIT_STATUS,edit,1350633601
Control16=IDC_EDIT_FILE_NAME,edit,1350633600

[CLS:CDataCollectionDlg]
Type=0
HeaderFile=DataCollectionDlg.h
ImplementationFile=DataCollectionDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDataCollectionDlg

[CLS:CFileSettingDlg]
Type=0
HeaderFile=FileSettingDlg.h
ImplementationFile=FileSettingDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CFileSettingDlg

[DLG:IDD_DIALOG_SPECTRUM]
Type=1
Class=CSpectrumDlg
ControlCount=33
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT_FILENAME,edit,1350633600
Control3=IDC_BUTTON_OPEN_FILEDIA,button,1342242816
Control4=IDC_BUTTON_AWS,button,1342242816
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT_ESCR,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT_SCCR,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_EDIT7,edit,1350631552
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_EDIT9,edit,1350631552
Control16=IDC_SPIN1,msctls_updown32,1342177312
Control17=IDC_EDIT11,edit,1350631552
Control18=IDC_SPIN2,msctls_updown32,1342177312
Control19=IDC_EDIT3,edit,1350631552
Control20=IDC_EDIT4,edit,1350631552
Control21=IDC_STATIC,static,1342308352
Control22=IDC_EDIT8,edit,1350631552
Control23=IDC_EDIT10,edit,1350631552
Control24=IDC_SPIN3,msctls_updown32,1342177312
Control25=IDC_EDIT12,edit,1350631552
Control26=IDC_SPIN4,msctls_updown32,1342177312
Control27=IDC_EDIT5,edit,1350631552
Control28=IDC_EDIT6,edit,1350631552
Control29=IDC_BUTTON_SELECT,button,1342242816
Control30=IDC_BUTTON_DELETE,button,1342242816
Control31=IDC_BUTTON_FILE_OPEN,button,1342242816
Control32=IDC_BUTTON_FILE_SAVE,button,1342242816
Control33=IDC_BUTTON_AWS_FACTOR,button,1342242816

[DLG:IDD_DIALOG_AWS_FACTOR_SETTING]
Type=1
Class=CAWSFactorSttingDlg
ControlCount=2
Control1=IDC_BUTTON_FILE_SAVE,button,1342242816
Control2=IDC_BUTTON_CANCEL,button,1342242816

[CLS:CAWSFactorSttingDlg]
Type=0
HeaderFile=AWSFactorSttingDlg.h
ImplementationFile=AWSFactorSttingDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CAWSFactorSttingDlg

[CLS:CSpectrumDlg]
Type=0
HeaderFile=SpectrumDlg.h
ImplementationFile=SpectrumDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CSpectrumDlg

[DLG:IDD_DIALOG_AWS_FACTOR]
Type=1
Class=CAWSFactorDlg
ControlCount=1
Control1=IDC_BUTTON_SPECTRUM,button,1342242816

[CLS:CAWSFactorDlg]
Type=0
HeaderFile=AWSFactorDlg.h
ImplementationFile=AWSFactorDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CAWSFactorDlg

