#pragma once

namespace MayTinhTay {
	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;
	public interface class TypeListener {
		void virtual ActiveThis(Control^ object);
	};
	enum class MODE {
		HEX,
		DEC,
		BIN
	};
	public ref class NumberTypeButton : Control
	{
		
	protected:
		TypeListener^ listener = nullptr;
	public:
		MODE mode = MODE::HEX;
		String^ Label = "";
		String^ Value = "";
		String^ RepresentValue = "";
		bool isDown = false;
		bool isMoving = false;
		bool isActive = false;
		Brush^ ActiveBrush;
		Brush^ DownBrush;
		Brush^ MoveBrush;
		Brush^ BackBrush;
		Brush^ TextBrush;
		Brush^ ActiveBackBrush;
		Drawing::Font^ f;
		StringFormat^ CSF, ^LSF; // căn chỉnh trung tâm và căn chỉnh trái 
		NumberTypeButton(MODE m,TypeListener^ l,String^ label, String^ value, Brush^ down, Brush^ move, Brush^ back, Brush ^text,Brush^ active,Brush^ activeLine, StringFormat^ centerSF, StringFormat^ leftSF, Drawing::Font^ font, bool isFocus) {
			SetStyle(ControlStyles::UserPaint | ControlStyles::AllPaintingInWmPaint | ControlStyles::DoubleBuffer, true);
			SetStyle(ControlStyles::AllPaintingInWmPaint, true);
			SetStyle(ControlStyles::UserPaint, true);
			SetStyle(ControlStyles::OptimizedDoubleBuffer, true);
			mode = m;
			listener = l;
			Label = label;
			Set(value);

			DownBrush = down;
			BackBrush = back;
			MoveBrush = move;
			TextBrush = text;
			ActiveBackBrush = active;
			ActiveBrush = activeLine;
			CSF = centerSF;
			LSF = leftSF;
			this->f = font;
			this->isActive = isFocus;
			init();
		}

		~NumberTypeButton() {

		}
		void init() {

		}
		void OnResize(System::EventArgs^ eventargs) override {
		Control::OnResize(eventargs);
			init(); // 
			Invalidate();
		}
		bool initted = false;
		void OnPaint(PaintEventArgs^ pEvent) override {
			if (!initted)
			{
				init();
				initted = true;
			}
			Control::OnPaint(pEvent);
			Graphics^ g = pEvent->Graphics;
			g->SmoothingMode = Drawing2D::SmoothingMode::AntiAlias;
			if (isActive)
			{
				g->Clear(((SolidBrush^)ActiveBackBrush)->Color);
				if(Height>29)
				g->FillRectangle(ActiveBrush, 0, 8, 5, Height-16);
				else g->FillRectangle(ActiveBrush, 0, 0, 5, Height);
			}
			else
			g->Clear(((SolidBrush^)BackBrush)->Color); // dọn màu trước khi vẽ 


			SizeF^ size = g->MeasureString(Label, f);
			// Vẽ label 
			g->DrawString(Label, f, TextBrush, 10 + size->Width / 2, Height / 2 , CSF);
			
			SizeF^ sizeRV = g->MeasureString(Value, f);
				SizeF^ sizeRV2 = g->MeasureString(Value, f, SizeF(Width - (20 + size->Width + 10), 10*(Height-4)));
			//Diagnostics::Debug::WriteLine("1 : "+ sizeRV->Width + "/" + sizeRV->Height + " vs " + (Width - (20 + size->Width + 10)) + "/" + Height);
			//Diagnostics::Debug::WriteLine("2 : "+ sizeRV2->Width + "/" + sizeRV2->Height );

			// kich thuoc co the paint dc
			SizeF^ paintSz = gcnew SizeF(Width - (20 + size->Width + 10), Height-4);
				if (sizeRV2->Height>= paintSz->Height) { 
					float pc = 1.2f;
					if (sizeRV2->Height / paintSz->Height >= 1.6f)
						pc = 1.5f;
					g->ScaleTransform(1/pc, 1/pc);
					 g->DrawString(RepresentValue, f, TextBrush, RectangleF((20 + size->Width + 10)*pc, 0, pc*(Width - (20 + size->Width + 10)), Height*pc), LSF);
			}
			else g->DrawString(RepresentValue, f, TextBrush, RectangleF(20 + size->Width + 10, 0, Width - (20 + size->Width + 10), Height), LSF);


			
			if (isMoving) g->FillRectangle(MoveBrush, 0, 0, Width, Height);
			else if (isDown) g->FillRectangle(DownBrush, 0, 0, Width, Height);
		};
		void removeAtEnd() {
			Value->Remove(Value->Length - 1);
			Invalidate();
		}
		void Clear() {
			Value = "0";
				Invalidate();
		}
		void Set(String^ c) {
			Value = "";
			if (c == "") c = "0";
			Add(c);
		}
		void Add(String^ c) {
			Value += c;
			RepresentValue = "";
			if (mode == MODE::HEX||mode == MODE::BIN) {
				for (int i = 0; i != Value->Length; i++)
				{
					if ((i+1) % 4 == 0&& Value->Length - 1 - i!=0)
						RepresentValue = " " + Value[Value->Length - 1 - i] + RepresentValue;
						else RepresentValue = Value[Value->Length - 1 - i] + RepresentValue;
					
				}
			} 
			else {
				for (int i = 0; i != Value->Length; i++)
				{
					if ((i + 1) % 3 == 0&& Value->Length - 1 - i!=0)
						RepresentValue = "," + Value[Value->Length - 1 - i] + RepresentValue;
					else RepresentValue = Value[Value->Length - 1 - i] + RepresentValue;

				}
			}
			
			Invalidate();
		}
		void ActiveThis() {
			if (!isActive) {
				isActive = true;
				Invalidate();
			}
		}
		void DisableThis() {
			if (isActive) {
				isActive = false;
				Invalidate();
			}
		}
		void Debug(String^ s) {
			Diagnostics::Debug::WriteLine(s);
		}
		void OnMouseMove(System::Windows::Forms::MouseEventArgs^ e) override {
			Control::OnMouseMove(e);
			if (!isMoving) {
				isMoving = true;
				Invalidate();
			}
			//Debug("MouseMove");
		}
		void OnMouseLeave(Object^ o, EventArgs^ e) {
			Control::OnMouseEnter(e);
			if (isMoving) {
				isMoving = false;
				Invalidate();
			}
			//Debug("MouseLeave");

		}
		void OnMouseDown(System::Windows::Forms::MouseEventArgs^ e) override {
			Control::OnMouseDown(e);
			if (!isDown&&!isActive) {
				isDown = true;
				
				Invalidate();
				if (listener != nullptr)
					listener->ActiveThis(this);
			}
			//Debug("MouseDown");
		}
		void OnMouseUp(System::Windows::Forms::MouseEventArgs^ e) override {
			Control::OnMouseUp(e);
			if (isDown) {
				isDown = false;
				Invalidate();
			}
		}

	};
}
