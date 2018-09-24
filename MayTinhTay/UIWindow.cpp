#pragma once
#include <iostream>
#include <string>
#include "stdafx.h"
#include "UIWindow.h"

namespace MayTinhTay {
	using namespace Drawing;
	using namespace System::Diagnostics;
	using namespace System::Runtime::InteropServices;
	std::string ToStandardString(String ^);

	String^ ToSystemString(std::string);
	inline MayTinhTay::UIWindow::UIWindow(String^ smallString,String^ bigString,QInt q)
	{
		
		InitializeComponent();
		panel = gcnew LinearPanel();
		this->Controls->Add(panel);
		panel->Dock = DockStyle::Fill;

		panel->SetRadioSummary(15);
		lb1 = gcnew Label();
		
		lb1->BackColor = Color::Black;
		lb2 = gcnew Label();
		lb2->Text = "Label 2";
		lb2->BackColor = Color::FromArgb(20,20,20);
		
	

		Brush^ backlabel = gcnew SolidBrush(Color::FromArgb(20,20,20));
		Brush^ textlabel = gcnew SolidBrush(Color::FromArgb(220, 220, 220));
		Drawing::Font^ flabel = gcnew Drawing::Font("Segoe UI", 38, FontStyle::Regular);
		Drawing::Font^ tflabel = gcnew Drawing::Font("Segoe UI", 12, FontStyle::Regular);
		StringFormat^ sflabel = gcnew StringFormat();
		sflabel->Alignment = StringAlignment::Far;
		sflabel->LineAlignment = StringAlignment::Center;
		
		ResultLabel = gcnew WordWrapLabel(MODE::DEC,bigString, textlabel, backlabel, flabel, sflabel);
		SmallLabel = gcnew SmallWWLabel(MODE::DEC,smallString, textlabel, backlabel, tflabel, sflabel);
		panel->Add(lb2, 1.5f);
		panel->Add(SmallLabel, 0.5f);
		panel->Add(ResultLabel,2);
		
		// mode line
		Brush^ back = gcnew SolidBrush(Color::FromArgb(10, 10, 10));
		Brush^ text = gcnew SolidBrush(Color::FromArgb(157, 156, 158));
		Brush^ move = gcnew SolidBrush(Color::FromArgb(20,255,255,255));
		Brush^ down = gcnew SolidBrush(Color::FromArgb(20,255,255,255));
		Brush^ active = gcnew SolidBrush(Color::FromArgb(40,118,69,196));
		Brush^ activeline = gcnew SolidBrush(Color::FromArgb(118, 69, 196));
		StringFormat^ csf = gcnew StringFormat();
		csf->Alignment = StringAlignment::Center;
		csf->LineAlignment = StringAlignment::Center;
		Drawing::Font^ f = gcnew Drawing::Font("Segoe UI", 10, FontStyle::Bold);
		StringFormat^ lsf = gcnew StringFormat();
		//lsf->Alignment = StringAlignment::Center;
		lsf->LineAlignment = StringAlignment::Center;
		HexButton = gcnew NumberTypeButton(MODE::HEX,this,"Hex", ToSystemString(q.BinToHex()),down, move, back, text, active,activeline, csf, lsf, f, true);
		DecButton = gcnew NumberTypeButton(MODE::DEC,this,"Dec", ToSystemString(q.BinToDec()), down, move, back, text, active,activeline, csf, lsf, f, false);
		BinButton = gcnew NumberTypeButton(MODE::BIN,this,"Bin", ToSystemString(q.ShowBin()), down, move, back, text, active,activeline, csf, lsf, f, false);
		
		HexButton->MouseLeave += gcnew System::EventHandler(HexButton, &NumberTypeButton::OnMouseLeave);
		DecButton->MouseLeave += gcnew System::EventHandler(DecButton, &NumberTypeButton::OnMouseLeave);
		BinButton->MouseLeave +=gcnew System::EventHandler(BinButton,&NumberTypeButton::OnMouseLeave);
		panel->Add(HexButton, 1);
		panel->Add(DecButton, 1);
		panel->Add(BinButton, 1);

		// keyboard
		float h_measure = SystemInformation::VirtualScreen.Height*1.0f * 5 / 6;
		float w_measure = h_measure *8/15;
		this->MinimumSize = Drawing::Size(w_measure,h_measure);
		this->Size = this->MinimumSize;
		lb2->Text = ""+Width+"|"+Height;
		keysGrid = gcnew KeysGrid(w_measure, h_measure);
		panel->Add(keysGrid, 8);
		keysGrid->AddKeyListener(this);
		keysGrid->MouseLeave += gcnew  System::EventHandler(keysGrid, &KeysGrid::OnMouseLeave);

		Operator = gcnew array<String^>(14) {
			"=", // 0
			"+", // 1
			"-", // 2
			"X", // 3
			"/", // 4
			"And", // 5
			"Not", // 6
			"Xor", // 7
			"Or",  //8
			"Rsh",  // 9
			"Lsh", // 10
			"RoL", // 11
			"RoR", // 12
			"Mod" //13
		};
		Number[0] = new QInt();
		Number[1] = new QInt();
	}
	int UIWindow::getOperatorCodeID(String^ s) {
		for (int i = 0; i < Operator->Length; i++)
			if (s == Operator[i]) return i;
		return -1;
	}
	std::string ToStandardString(String ^s) {
		const char* cstr = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
		std::string sstr = cstr;
		Marshal::FreeHGlobal(System::IntPtr((void*)cstr));
		return sstr;
	}

	String^  ToSystemString(std::string s) {
		return gcnew String(s.c_str());
	}
	void MayTinhTay::UIWindow::ML(Object^ s, EventArgs^ e) {
		Debug::WriteLine("Mouse Leave from Form1");
	}
	template < class T, class U >
	Boolean isinst(U u) {
		return dynamic_cast< T >(u) != nullptr;
	}
	
	void UIWindow::ActiveThis(Control^ object)
	{
		if (isinst< NumberTypeButton^ >(object))
		{
			HexButton->DisableThis();
			DecButton->DisableThis();
			BinButton->DisableThis();
			((NumberTypeButton^)object)->ActiveThis();
			MODE newMode = ((NumberTypeButton^)object)->mode;
			keysGrid->SwitchMode(newMode);
			if (Mode != newMode) {
				UpdateValueType();
				Parameters = "";
			}
			Mode = newMode;
		}
	}

	// Gọi mỗi khi giá trị hiển thị trên 3 hệ số cần thay đổi 
	void MayTinhTay::UIWindow::UpdateValueType() {
		HexButton->Set(ToSystemString(Number[whichNumber]->BinToHex()));
		DecButton->Set(ToSystemString(Number[whichNumber]->BinToDec()));
		BinButton->Set(ToSystemString(Number[whichNumber]->ShowBin()));
		switch (Mode) {
		case MODE::HEX:ResultLabel->SetValue(ToSystemString(Number[whichNumber]->BinToHex()),false); break;
		case MODE::DEC:ResultLabel->SetValue(ToSystemString(Number[whichNumber]->BinToDec()),false); break;
		case MODE::BIN:ResultLabel->SetValue(ToSystemString(Number[whichNumber]->ShowBin()),false); break;
		}
		
	}
	void MayTinhTay::UIWindow::EqualPressed() {
		if (whichNumber == 1&&Parameters!="") { //chỉ xử lý khi đã đủ 2 toán hạng 
			QInt result;
			switch (WhichOperator) {
			case 1:result = *Number[0] + *Number[1]; break;
			case 2: result = *Number[0] - *Number[1]; break;
			case 3:result = (*Number[0]) * (*Number[1]); break;
			case 4:result = *Number[0] / *Number[1]; break;
			case 5:result = *Number[0] & *Number[1]; break;
			case 6:break;
			case 7:result = *Number[0] ^ *Number[1]; break;;
			case 8:result = *Number[0] | *Number[1]; break;
			case 9:result = *Number[0] << std::stoi(Number[1]->BinToDec()); break;
			case 10:result = *Number[0] >> std::stoi(Number[1]->BinToDec()); break;
			case 11:break;
			case 12:break;
			case 13:result = *Number[0] % *Number[1];
			}
			
			SmallLabel->SetValue(GetNumber(0) + " " + Operator[WhichOperator]+" "+Parameters, true);
			whichNumber = 0;
			*Number[0] = result;
			Parameters = "";

			UpdateValueType();
		}
	}
	String^ MayTinhTay::UIWindow::GetNumber(int i) {
		switch (Mode) {
		case MODE::HEX:return ToSystemString(Number[i]->BinToHex()); 
		case MODE::DEC:return ToSystemString(Number[i]->BinToDec());
		case MODE::BIN:return ToSystemString(Number[i]->ShowBin());
		}
	}
	void MayTinhTay::UIWindow::OperatorPressed(int which) {
		//  gọi hàm này khi phím được bấm là một toán tử
		WhichOperator = which; // lưu dấu toán tử 
		if(whichNumber==0) // đang nhập số thứ nhất 
		{  // chuyển sang nhập số thứ 2
		   // update text lên small label 
			SmallLabel->SetValue(GetNumber(0)+" "+Operator[WhichOperator], true);
			whichNumber = 1;
			Parameters = "";

		}
		else { // đang nhập số thứ hai 
			// tính toán kết quả 
			// gán vào số thứ nhất 
			// in ra màn hình 
			
		}
	}
	void MayTinhTay::UIWindow::BackPressed() {
		if (Parameters != "") Parameters= Parameters->Substring(0,Parameters->Length-1);
		Number[whichNumber]->Clear();
		switch (Mode) {
		case MODE::BIN:Number[whichNumber]->InputBin(ToStandardString(Parameters)); break;
		case MODE::HEX:Number[whichNumber]->InputHex(ToStandardString(Parameters)); break;
		case MODE::DEC:Number[whichNumber]->InputDec(ToStandardString(Parameters)); break;
		}
		UpdateValueType();
	}
	void MayTinhTay::UIWindow::NumberPressed(Char which) {
		// gọi hàm này nếu phím được bấm là số 
		if (which != '=')
		Parameters = Parameters+ which;
		//Diagnostics::Debug::WriteLine(Parameters);
		Number[whichNumber]->Clear();
		switch (Mode) {
		case MODE::BIN:Number[whichNumber]->InputBin(ToStandardString(Parameters)); break;
		case MODE::HEX:Number[whichNumber]->InputHex(ToStandardString(Parameters)); break;
		case MODE::DEC:Number[whichNumber]->InputDec(ToStandardString(Parameters)); break;
		}
		UpdateValueType();
		if (which == '=') {
			Parameters = "";
			whichNumber = 0;
		}
	}
	void MayTinhTay::UIWindow::SignPressed() {
		Diagnostics::Debug::WriteLine("Sign pressed : "+Parameters);
		*Number[whichNumber] = Number[whichNumber]->Reverse();
		UpdateValueType();
	}
	void MayTinhTay::UIWindow::KeyPressed(String^ Tag, int pos) {
		if (Tag == "CE"//);
	//	else if (
			||(Tag == "C"&&pos == 9)) 
		{
			SmallLabel->SetValue("", true);
			Parameters = ""; whichNumber = 0; Number[0]->Clear(); Number[1]->Clear(); UpdateValueType();
		}
		else if (Tag == "Back") BackPressed();
		else if (Tag == "(" || Tag == ")");
		else if (Tag == "+/-") SignPressed();
		else if (Tag == "=") EqualPressed();
		else if (getOperatorCodeID(Tag) != -1) OperatorPressed(getOperatorCodeID(Tag)); // nut toan tu
		else NumberPressed(Tag[0]);
		}
	 
	 
	
	 };