#pragma once
#include "NumberTypeButton.h"
namespace MayTinhTay {
	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;
	public ref class WordWrapLabel : Control
	{
	protected:
		Brush^ BackBrush;
	    Brush^ TextBrush;
		MODE mode;
		String^ Value="";
		String^ RepresentValue="";
		Drawing::Font^ f;
		StringFormat^ sf;
	public:
		WordWrapLabel(MODE m,String^ s,Brush^ text, Brush^ backBrush, Drawing::Font^ font, StringFormat^ SF) {
			SetStyle(ControlStyles::UserPaint | ControlStyles::AllPaintingInWmPaint | ControlStyles::DoubleBuffer, true);
			SetStyle(ControlStyles::AllPaintingInWmPaint, true);
			SetStyle(ControlStyles::UserPaint, true);
			SetStyle(ControlStyles::OptimizedDoubleBuffer, true);
			TextBrush = text;
			BackBrush = backBrush;
			mode = m;
			f = font;
			sf = SF;
			RepresentValue = Value = s;
			
		}
		void SetValue(String^ s, bool boqua) {
			if (s == ""&&!boqua) s = "0";
			if (Value == s) return;
			Value = s;
			if (boqua) {
				RepresentValue = Value;Invalidate(); return;
			}
			else 
			RepresentValue = "";
			if (mode == MODE::HEX || mode == MODE::BIN) {
				for (int i = 0; i != Value->Length; i++)
				{
					if ((i + 1) % 4 == 0 && Value->Length - 1 - i != 0)
						RepresentValue = " " + Value[Value->Length - 1 - i] + RepresentValue;
					else RepresentValue = Value[Value->Length - 1 - i] + RepresentValue;

				}
			}
			else {
				for (int i = 0; i != Value->Length; i++)
				{
					if ((i + 1) % 3 == 0 && Value->Length - 1 - i != 0)
						RepresentValue = "," + Value[Value->Length - 1 - i] + RepresentValue;
					else RepresentValue = Value[Value->Length - 1 - i] + RepresentValue;

				}
			}

			Invalidate();
		}
		void OnResize(System::EventArgs^ eventargs) override {
			Control::OnResize(eventargs);
			
			Invalidate();
		}
		~WordWrapLabel();
		void virtual OnPaint(PaintEventArgs^ pEvent) override {

			Control::OnPaint(pEvent);
			Graphics^ g = pEvent->Graphics;
		
			g->SmoothingMode = Drawing2D::SmoothingMode::AntiAlias;
			g->Clear(((SolidBrush^)BackBrush)->Color);
			SizeF^ size = g->MeasureString(RepresentValue, f);
			//Diagnostics::Debug::WriteLine(size->Width  / Width);
			if (size->Width > Width) {
				if (Width / size->Width > 1 / 3.0f)
				{
					g->ScaleTransform(Width / size->Width, Width / size->Width);
					// g->DrawString(RepresentValue, f, TextBrush, Rectangle(0, 0, size->Width, Height*size->Width / Width), sf);
					g->DrawString(RepresentValue, f, TextBrush, size->Width, Height*size->Width / Width / 2, sf);
				}
				else {
					g->ScaleTransform(1 / 3.0f, 1 / 3.0f);
					g->DrawString(RepresentValue, f, TextBrush, Rectangle(0, 0, 3 * Width, 3 * Height), sf);
				}
				}
			else g->DrawString(RepresentValue, f, TextBrush, Rectangle(0, 0, Width, Height), sf);

				}
	};
	public ref class SmallWWLabel : WordWrapLabel {
	public:
		SmallWWLabel(MODE m, String^ s, Brush^ text, Brush^ backBrush, Drawing::Font^ font, StringFormat^ SF) :
			WordWrapLabel(m, s, text, backBrush, font, SF) {
		}

		void virtual OnPaint(PaintEventArgs^ pEvent) override {
			Control::OnPaint(pEvent);
			Graphics^ g = pEvent->Graphics;

			g->SmoothingMode = Drawing2D::SmoothingMode::AntiAlias;
			g->Clear(((SolidBrush^)BackBrush)->Color);
			
			g->DrawString(RepresentValue, f, TextBrush, Rectangle(20, 0, Width - 40, Height), sf);

		}
	};
}

