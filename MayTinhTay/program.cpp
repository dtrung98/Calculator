// CppCLR_WinformsProjekt.cpp: Hauptprojektdatei.

// #include "stdafx.h"
// using namespace System;

//int main(array<System::String ^> ^args)
//{
//    Console::WriteLine(L"Hello World");
//    return 0;
//}
#include "stdafx.h"
#include "UIWindow.h"
#include "QInt.h"
#include "helper.h"
#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <Windows.h>
#pragma once
using namespace System;
using namespace System::Windows::Forms;
using namespace System::Runtime::InteropServices;
using namespace System::IO;
using namespace System::Reflection;
#pragma comment(lib, "user32.lib")

// Hàm thực hiện yêu cầu bài toán 
// Đọc file theo từng dòng, tính kết quả và xuất ra file.
// đồng thời nó trả về mảng chuỗi 2 phần tử :
// +. chuỗi đầu tiên là dòng text đầu tiên của input file 
// +. chuỗi thứ hai là kết quả của dòng text đầu tiên đó 
array<String^>^ CalculateAndExportFile(array<String^>^ args,QInt&);

// Hàm hiện giao diện UI "Máy tính tay" của chương trình
// Nếu khởi chạy với tham số, nó sẽ hiện lên kết quả của phép tính đầu tiên trong file input 
// String 1 : dòng text đầu tiên của file 
// String 2 : kết quả tính của dòng đó 
void ShowUI(String^, String^,QInt);

// Hàm chuyển đổi chuỗi System::String^ về chuỗi string chuẩn std::string 
std::string ToStandardString(String ^);

String^ ToSystemString(std::string);

// Hàm main mặc định của một chương trình CLI 
// Đây là hàm đầu tiên chương trình được khởi chạy 
    [STAThread]
	int main(array<String^>^ args) {
		QInt q; // Biến QInt dùng để truyền vào UI 
		q.InputBin(ToStandardString("0"));
		array<String^>^ results = CalculateAndExportFile(args,q);
		ShowUI(results[0], results[1],q);
		return 0;
	}
	
	array<String^>^ CalculateAndExportFile(array<String^>^ args,QInt& q) {
		
		if (args->Length == 0) return gcnew array<String^>(2) { "", "0" };
		else if (args->Length > 2) return gcnew array<String^>(2) { "", "Your parameter is invalid." };
		
		std::string infileStr = ToStandardString(args[0]); // tên file nhập 
		std::string outfileStr = ToStandardString(args[1]); // tên file xuất 
		std::ifstream fin; //Biến fin lưu dữ liệu lấy từ file
		fin.open(infileStr); //Mở file

		if (!fin.good()) //Kiểm tra có mở được file không
		return gcnew array<String^>(2) { "","Sorry, fail to load input file." };
		
		std::ofstream fout;
		fout.open(outfileStr); // File xuất ra luôn mở được, không cần kiểm tra
		std::string output_result;
		std::string firstLine="", resultOfFirstLine;
		while (!fin.eof())
		{
			if (firstLine == "") {
				output_result = QInt::LoadFile(fin, firstLine,q);
				resultOfFirstLine = output_result;
			}
			else {
				output_result = QInt::LoadFile(fin);
			}
			fout << output_result << std::endl;
		}
		fin.close();
		fout.close();
		return gcnew array<String^>(2) { ToSystemString(firstLine), ToSystemString(resultOfFirstLine) };
	}

	void ShowUI(String^ smallString, String^ bigString,QInt q) {

		if (Environment::OSVersion->Version->Major >= 6)
			SetProcessDPIAware();
		Application::EnableVisualStyles();
		Application::SetCompatibleTextRenderingDefault(false);
		Application::Run(gcnew MayTinhTay::UIWindow(smallString, bigString,q));
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