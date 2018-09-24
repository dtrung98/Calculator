#pragma once
#include "KeysGrid.h"
namespace MayTinhTay {
	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;
	using namespace Collections::Generic;

	public ref class Key abstract {
	public:
		Key() {

		}
		Point Location;
		   Size Size;
		   String^ Tag;
		   Brush^ BackBrush, ^TextBrush,^MoveBrush,^DownBrush;
		   StringFormat^ SF;
		   Font^ f;

		   bool Enable = true;
		   void Disable() {
			   Enable = false;
		   }
		   void Enabled() {
			   Enable = true;
		   }
	private:  bool isInside(int circle_x, int circle_y, int rad, int x, int y)
	{
		// Compare radius of circle with distance of its center from 
		// given point
		if ((x - circle_x)*(x - circle_x) +
			(y - circle_y)*(y - circle_y) <= rad*rad)
			return true;
		else
			return false;
	}
	public:
		bool virtual IsInside(Point^ p) {
			return Enable && isInside(this->Location.X + this->Size.Width / 2, this->Location.Y + this->Size.Height / 2, this->Size.Width / 2, p->X, p->Y);
		}
		void virtual Draw(Graphics^ g) abstract;
		bool IsMoving = false;
		bool IsDown = false;

	};


	public ref class NKey : Key {
	public:
		NKey(Brush^ back, Brush^ text,Brush^ move,Brush^ down,Font^ font, StringFormat^ sf, String^ tag)
		{
			/*
			if (isNumKey) {
				BackBrush = kg->NKeyBackBrush;
				TextBrush = kg->NKeyTextBrush;
			}
			else {
				BackBrush = kg->ONKeyBackBrush;
				TextBrush = kg->ONKeyTextBrush;
			}
			*/
			BackBrush = back;
			TextBrush = text;
			MoveBrush = move;
			DownBrush = down;
			f = font;
			SF = sf;
			Tag = tag;
		}
	public:float pc = 1.0f;
		void virtual Draw(Graphics^ g) override {
			if(pc==1) Enable = true;
			else Enable = false;
			// Tất cả giá trị khác 1, có nghĩa là disable 
			if (pc == 0) {

				return;
			}
			if (pc != 1) {
				Draw(g, pc);
				return;
			}
			
			g->FillEllipse(BackBrush, Location.X, Location.Y, Size.Width, Size.Height);
			
			g->DrawString(Tag, f, TextBrush, PointF(Location.X + Size.Width / 2, Location.Y + Size.Height / 2), SF);
			if (IsDown)
				g->FillEllipse(DownBrush, Location.X, Location.Y, Size.Width, Size.Height);
			else if (IsMoving)
				g->FillEllipse(MoveBrush, Location.X, Location.Y, Size.Width, Size.Height);

		}
		void virtual Draw(Graphics^ g, float pc) {
			g->FillEllipse(BackBrush, Location.X, Location.Y, Size.Width, Size.Height);

			g->DrawString(Tag, f, TextBrush, PointF(Location.X + Size.Width / 2, Location.Y + Size.Height / 2), SF);
			g->FillEllipse(gcnew SolidBrush(Color::FromArgb(255-pc*255.0f, 0, 0, 0)), Location.X, Location.Y, Size.Width, Size.Height);
		}
	};
	public ref class ShiftKey : NKey {
	public:
		Pen^ p;
		ShiftKey(Brush^ back, Brush^ text, Brush^ move, Brush^ down, Font^ font, StringFormat^ sf, String^ tag)
		: NKey(back, text, move, down, font, sf, tag)
	{
			p = gcnew Pen(Color::FromArgb(255,255,255));
			p->Width = 2;
		};
		bool IsOn = false;
		void virtual Draw(Graphics^ g) override {
			if (!IsOn) NKey::Draw(g);
			else {
				g->FillEllipse(TextBrush, Location.X, Location.Y, Size.Width, Size.Height);
				g->DrawString(Tag, f, BackBrush, PointF(Location.X + Size.Width / 2, Location.Y + Size.Height / 2), SF);
				if (IsDown)
					g->FillEllipse(DownBrush, Location.X, Location.Y, Size.Width, Size.Height);
				else if (IsMoving)
					g->FillEllipse(MoveBrush, Location.X, Location.Y, Size.Width, Size.Height);
			}
		}
	};
	
	public ref class BitsKey : Key {
	protected:
		Pen^ bPen;
	public:
		BitsKey(Brush^ back, Brush^ text, Brush^ move, Brush^ down, Font^ font, StringFormat^ sf,Pen^ pen, String^ Tag) : Key() {

			TextBrush = text;// kg->BitsTextBrush;
			BackBrush = back;// kg->BitsBackBrush;
			MoveBrush = move;
			DownBrush = down;
			bPen = pen;
			SF = sf;
			f = font;
			this->Tag = Tag;
		}
	public:
		void Draw(Graphics^ g) override {
			g->FillEllipse(BackBrush, Location.X, Location.Y, Size.Width, Size.Height);
		
			g->DrawString(Tag, f, TextBrush, PointF(Location.X + Size.Width / 2, Location.Y + Size.Height / 2), SF);
			//g->DrawEllipse(bPen, Location.X, Location.Y, Size.Width, Size.Height);
			if (IsDown)
				g->FillEllipse(DownBrush, Location.X, Location.Y, Size.Width, Size.Height);
			else if (IsMoving)
				g->FillEllipse(MoveBrush, Location.X, Location.Y, Size.Width, Size.Height);

		}
	};
	public ref class EqualKey :NKey {
	private:
		Drawing2D::GraphicsPath^ getPath(float x, float y,float w,float h, float d) {
			Drawing2D::GraphicsPath^ gp =
				gcnew Drawing2D::GraphicsPath();
			if (w == 0 && h == 0) return nullptr;
			gp->AddArc(x, y, d, d, 180, 90);
			gp->AddArc(x + w - d, y, d, d, 270, 90);
			gp->AddArc( x+ w - d, y+ h - d, d, d, 0, 90);
			gp->AddArc(x, y + h - d, d, d, 90, 90);
			gp->AddLine(x, y + h - d, x, y + d / 2);
			return gp;
		}
		
	public :
		Drawing2D::GraphicsPath^ gp;
		EqualKey(Brush^ back,Brush^ text, Brush^ move, Brush^ down, Font^ font, StringFormat^ sf,String^ tag) :
			NKey(back, text, move, down, font, sf,tag) {

		}
		bool virtual IsInside(Point^ p) override {
			return gp != nullptr&&gp->IsVisible(p->X, p->Y);
		}
		void virtual Draw(Graphics^ g) override {
			gp = getPath(Location.X, Location.Y, Size.Width, Size.Height, Size.Height );
			if (gp == nullptr) return;
			g->FillPath(BackBrush,gp);
			g->DrawString(Tag, f, TextBrush, PointF(Location.X+Size.Width - Size.Height/2, Location.Y + Size.Height / 2), SF);
			if(IsMoving)  g->FillPath(MoveBrush, gp);
			else if(IsDown) g->FillPath(DownBrush, gp);
		}
	};
}