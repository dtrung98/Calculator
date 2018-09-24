#pragma once
#include"Key.h"
#include "NumberTypeButton.h"
namespace MayTinhTay {
	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;
	using namespace Collections::Generic;
	public interface class KeysListener {
		void virtual KeyPressed(String^ tag,int pos);
	};
	public ref class KeysGrid : public Panel
	{
	protected:
		KeysListener^ listener = nullptr;
	public:
		void AddKeyListener(KeysListener^ kl) {
			listener = kl;
		}
		Color BackKeyColor = Color::FromArgb(0, 0, 0), // màu nền nút chữ số
			KeyColor = Color::FromArgb(51, 51, 50), // màu nút số 
			KeyHoverColor = Color::FromArgb(159, 161, 159), // màu nút số khi di chuột 
			KeyMaskColor = Color::FromArgb(164, 164, 162), // màu chữ nút số 
			BackKeyOperatorColor = BackKeyColor, // màu nền nút toán tử 
			KeyOperatorColor = Color::FromArgb(134, 94, 197), // màu nút toán tử 
			KeyHoverOperatorColor = KeyHoverColor, // màu nút toán tử khi di chuột 
			KeyMaskOperatorColor = Color::FromArgb(254, 253, 254), // màu chữ nút toán tử 
			BorderColor = Color::FromArgb(51, 51, 51); // màu  đường viền 
		Key ^Lsh, ^Rsh, ^Or, ^Xor, ^Not, ^And,
			^Shift, ^Mod, ^CE, ^C, ^BackSpace, ^Div,
			^KeyA, ^KeyB, ^Key7, ^Key8, ^Key9, ^Mult,
			^KeyC, ^KeyD, ^Key4, ^Key5, ^Key6, ^Sub,
			^KeyE, ^KeyF, ^Key1, ^Key2, ^Key3, ^Add,
			^LBracket, ^RBracket, ^Sign, ^Key0, ^Dot, ^Equals;
		array<Key^, 2> ^ key = gcnew array<Key^, 2>(6, 6);
		Brush^ NKeyBackBrush = gcnew SolidBrush(Color::FromArgb(51, 51, 50)); // màu nền nút bình thường 
		Brush^ NKeyTextBrush = gcnew SolidBrush(Color::FromArgb(164, 164, 162)); // màu chữ nút bình thường 
		Brush^ ONKeyBackBrush = gcnew SolidBrush(Color::FromArgb(250, 150, 4)); //màu cam, màu nền nút cộng, trừ ..
		Brush^ ONKeyTextBrush = gcnew SolidBrush(Color::FromArgb(254, 253, 254)); // màu chữ nút cộng trừ ..

		Brush^ BitsBackBrush = gcnew SolidBrush(Color::FromArgb(118, 69, 196)); //màu tím, màu nền của các nút tính toán bit 
		Brush^ BitsTextBrush = gcnew SolidBrush(Color::FromArgb(210, 210, 210)); // màu chữ của các nút tính toán bit 
		Brush^ MoveBrush = gcnew SolidBrush(Color::FromArgb(100, 255, 255, 255)); // màu nền được vẽ thêm khi chuột di qua 
		Brush^ DownBrush = gcnew SolidBrush(Color::FromArgb(130, 255, 255, 255)); // màu nền được vẽ thêm khi chuột nhấn 
		Pen^ pen;
		Drawing::Font^ font = gcnew Drawing::Font("Segoe UI", 13, FontStyle::Bold);
		Drawing::Font^ ofont = gcnew Drawing::Font("Segoe UI", 18, FontStyle::Bold);
		Drawing::Font^ tfont = gcnew Drawing::Font("Segoe UI", 10, FontStyle::Bold);
		StringFormat^ SF;
		float min_w, min_h;
		KeysGrid(float min_w, float min_h) {
			SetStyle(ControlStyles::UserPaint | ControlStyles::AllPaintingInWmPaint | ControlStyles::DoubleBuffer, true);
			SetStyle(ControlStyles::AllPaintingInWmPaint, true);
			SetStyle(ControlStyles::UserPaint, true);
			SetStyle(ControlStyles::OptimizedDoubleBuffer, true);

			SF = gcnew StringFormat();
			SF->Alignment = StringAlignment::Center;
			SF->LineAlignment = StringAlignment::Center;
			pen = gcnew Pen(BorderColor, 2);
			this->min_w = min_w;
			this->min_h = min_h;
			createKeys();
			addKeys();
			createOutList();
			alphaTimer->Interval = 10;
			motionTimer->Interval = 10;
			alphaTimer->Tick += gcnew System::EventHandler(this, &MayTinhTay::KeysGrid::alpha_OnTick);
			motionTimer->Tick += gcnew System::EventHandler(this, &MayTinhTay::KeysGrid::motion_OnTick);
			
		}
		float mTiming = 350;
		float aTiming = 300;
		//	void OnLoad(EventArgs^ e) override {
				//init(); // 
			//	setLocation();
			//}
		void addKeys() {
			key = gcnew array<Key^, 2>(6, 6)
			{ {Lsh, Rsh, Or, Xor, Not, And },
			{ Shift,Mod,CE,C, BackSpace,Div },
			{ KeyA,KeyB,Key7,Key8,Key9,Mult },
			{ KeyC,KeyD,Key4,Key5,Key6,Sub },
			{ KeyE,KeyF,Key1,Key2,Key3, Add },
			{ LBracket, RBracket, Sign, Key0, Dot,Equals }
			};
			int x = 5;
		}
		void createKeys() {
			Lsh = gcnew BitsKey(BitsBackBrush, BitsTextBrush, MoveBrush, DownBrush, tfont, SF, pen, "Lsh");
			Rsh = gcnew BitsKey(BitsBackBrush, BitsTextBrush, MoveBrush, DownBrush, tfont, SF, pen, "Rsh");
			Lsh = gcnew BitsKey(BitsBackBrush, BitsTextBrush, MoveBrush, DownBrush, tfont, SF, pen, "Lsh");
			Rsh = gcnew BitsKey(BitsBackBrush, BitsTextBrush, MoveBrush, DownBrush, tfont, SF, pen, "Rsh");
			Or = gcnew BitsKey(BitsBackBrush, BitsTextBrush, MoveBrush, DownBrush, tfont, SF, pen, "Or");
			Xor = gcnew BitsKey(BitsBackBrush, BitsTextBrush, MoveBrush, DownBrush, tfont, SF, pen, "Xor");
			Not = gcnew BitsKey(BitsBackBrush, BitsTextBrush, MoveBrush, DownBrush, tfont, SF, pen, "Not");
			And = gcnew BitsKey(BitsBackBrush, BitsTextBrush, MoveBrush, DownBrush, tfont, SF, pen, "And");
			Shift = gcnew ShiftKey(NKeyBackBrush, NKeyTextBrush, MoveBrush, DownBrush, tfont, SF, "Shift");
			Mod = gcnew NKey(NKeyBackBrush, NKeyTextBrush, MoveBrush, DownBrush, tfont, SF, "Mod");
			CE = gcnew NKey(NKeyBackBrush, NKeyTextBrush, MoveBrush, DownBrush, tfont, SF, "CE");
			C = gcnew NKey(NKeyBackBrush, NKeyTextBrush, MoveBrush, DownBrush, tfont, SF, "C");
			BackSpace = gcnew NKey(NKeyBackBrush, NKeyTextBrush, MoveBrush, DownBrush, tfont, SF, "Back");
			Div = gcnew NKey(ONKeyBackBrush, ONKeyTextBrush, MoveBrush, DownBrush, font, SF, "/");
			KeyA = gcnew NKey(NKeyBackBrush, NKeyTextBrush, MoveBrush, DownBrush, font, SF, "A");
			KeyB = gcnew NKey(NKeyBackBrush, NKeyTextBrush, MoveBrush, DownBrush, font, SF, "B");
			Key7 = gcnew NKey(NKeyBackBrush, NKeyTextBrush, MoveBrush, DownBrush, font, SF, "7");
			Key8 = gcnew NKey(NKeyBackBrush, NKeyTextBrush, MoveBrush, DownBrush, font, SF, "8");
			Key9 = gcnew NKey(NKeyBackBrush, NKeyTextBrush, MoveBrush, DownBrush, font, SF, "9");
			Mult = gcnew NKey(ONKeyBackBrush, ONKeyTextBrush, MoveBrush, DownBrush, tfont, SF, "X");
			KeyC = gcnew NKey(NKeyBackBrush, NKeyTextBrush, MoveBrush, DownBrush, font, SF, "C");
			KeyD = gcnew NKey(NKeyBackBrush, NKeyTextBrush, MoveBrush, DownBrush, font, SF, "D");
			Key4 = gcnew NKey(NKeyBackBrush, NKeyTextBrush, MoveBrush, DownBrush, font, SF, "4");
			Key5 = gcnew NKey(NKeyBackBrush, NKeyTextBrush, MoveBrush, DownBrush, font, SF, "5");
			Key6 = gcnew NKey(NKeyBackBrush, NKeyTextBrush, MoveBrush, DownBrush, font, SF, "6");
			Sub = gcnew NKey(ONKeyBackBrush, ONKeyTextBrush, MoveBrush, DownBrush, ofont, SF, "-");
			KeyE = gcnew NKey(NKeyBackBrush, NKeyTextBrush, MoveBrush, DownBrush, font, SF, "E");
			KeyF = gcnew NKey(NKeyBackBrush, NKeyTextBrush, MoveBrush, DownBrush, font, SF, "F");
			Key1 = gcnew NKey(NKeyBackBrush, NKeyTextBrush, MoveBrush, DownBrush, font, SF, "1");
			Key2 = gcnew NKey(NKeyBackBrush, NKeyTextBrush, MoveBrush, DownBrush, font, SF, "2");
			Key3 = gcnew NKey(NKeyBackBrush, NKeyTextBrush, MoveBrush, DownBrush, font, SF, "3");
			Add = gcnew NKey(ONKeyBackBrush, ONKeyTextBrush, MoveBrush, DownBrush, ofont, SF, "+"),
				LBracket = gcnew NKey(NKeyBackBrush, NKeyTextBrush, MoveBrush, DownBrush, font, SF, "(");
			RBracket = gcnew NKey(NKeyBackBrush, NKeyTextBrush, MoveBrush, DownBrush, font, SF, ")");
			Sign = gcnew NKey(NKeyBackBrush, NKeyTextBrush, MoveBrush, DownBrush, font, SF, "+/-");
			Key0 = gcnew NKey(NKeyBackBrush, NKeyTextBrush, MoveBrush, DownBrush, font, SF, "0");
			Dot = gcnew NKey(NKeyBackBrush, NKeyTextBrush, MoveBrush, DownBrush, font, SF, ".");
			Equals = gcnew EqualKey(ONKeyBackBrush, ONKeyTextBrush, MoveBrush, DownBrush, ofont, SF, "=");
		}
		~KeysGrid() {

		}

		void OnResize(System::EventArgs^ eventargs) override {
			Panel::OnResize(eventargs);
			init(); // 
			setLocation();
			Invalidate();
		}
		float standard_key_size; //chiều dài và chiều rộng của mỗi button 
		float standard_key_margin; // khoảng cách giữa mỗi button 
		float square_width; // độ rộng của grid button 
		float margin_left; // khoảng cách từ viền trái tới grid button 
		float margin_top; // khoảng cách từ viền phải tới grid button
		float pc = 9.0f;
		void redraw() {
			init();

			setLocation();
			Invalidate();
		}
		void init() {
			square_width = (min_w < min_h) ? min_w : min_h;
			if (square_width > Width) square_width = Width;
			if (square_width > Height) square_width = Height;
			standard_key_size = square_width / (6.0f + 7 / pc);
			standard_key_margin = standard_key_size / pc;

			margin_left = (Width - square_width) / 2;
			margin_top = (Height - square_width) / 2;
		}
		
		void setLocation() {
			
			NormalPoint[0] = Point(margin_left + standard_key_size*(3*(1 + 1 / pc) + 1 / pc), margin_top + standard_key_size*(5*(1 + 1 / pc) + 1 / pc));  // 0
			NormalPoint[1] = Point(margin_left + standard_key_size*(2*(1 + 1 / pc) + 1 / pc), margin_top + standard_key_size*(4*(1 + 1 / pc) + 1 / pc));  // 1
			NormalPoint[2] = Point(margin_left + standard_key_size*(4*(1 + 1 / pc) + 1 / pc), margin_top + standard_key_size*(5*(1 + 1 / pc) + 1 / pc));  // =
			
			BinPoint[1] = Point(margin_left + 2 * standard_key_margin, margin_top + 4*standard_key_margin+2.25* standard_key_size); // key 1
			BinPoint[0] = Point(margin_left + 2.5f* standard_key_size + 4 * standard_key_margin, margin_top + 4 * standard_key_margin + 2.25* standard_key_size);  // key 0
			BinPoint[2] = Point(margin_left + standard_key_size*(3 * (1 + 1 / pc) + 1 / pc), margin_top + standard_key_size*(5 * (1 + 1 / pc) + 1 / pc)); // =


			NormalSize[0] = Drawing::Size(standard_key_size, standard_key_size);// 0
			NormalSize[1] = Drawing::Size(standard_key_size, standard_key_size);  // 1
			NormalSize[2] = Drawing::Size(2 * standard_key_size + standard_key_margin, standard_key_size);  // =
			BinSize[0] = Drawing::Size(2.5f*standard_key_size, 2.5f*standard_key_size); // 0
			BinSize[1] = BinSize[0]; // 1
			BinSize[2] = Drawing::Size(3*standard_key_size+ 2*standard_key_margin,standard_key_size); // =
			for (int i = 0; i < 6; i++)
				for (int j = 0; j < 6; j++)
				{  // dong 5, cot 4
					if ((i == 5 && j == 4)||(i==4&&j==2)||(i==5&&j==3)||(i==5&&j==5))
						continue; // bo qua dau cham
					
					key[i, j]->Location = Point(margin_left + standard_key_size*(j*(1 + 1 / pc) + 1 / pc), margin_top + standard_key_size*(i*(1 + 1 / pc) + 1 / pc));
					key[i, j]->Size = Drawing::Size(standard_key_size, standard_key_size);
				}
			
			// set binary key
			///*
			if (isInAnimation) {
				key[4, 2]->Location = CurrentPoint[1];
				key[5, 3]->Location = CurrentPoint[0];
				key[5, 5]->Location = CurrentPoint[2];

				key[4, 2]->Size = CurrentSize[1];
				key[5, 3]->Size = CurrentSize[0];
				key[5, 5]->Size = CurrentSize[2];
			}
			else if (Mode == MODE::BIN)
			{
			//*/
				key[4, 2]->Location = BinPoint[1];
				key[5, 3]->Location = BinPoint[0];
				key[5, 5]->Location = BinPoint[2];

				key[4, 2]->Size = BinSize[1];
				key[5, 3]->Size = BinSize[0];
				key[5, 5]->Size = BinSize[2];
				///*
			}
			else {
				key[4, 2]->Location = NormalPoint[1];
				key[5, 3]->Location = NormalPoint[0];
				key[5, 5]->Location = NormalPoint[2];

				key[4, 2]->Size = NormalSize[1];
				key[5, 3]->Size = NormalSize[0];
				key[5, 5]->Size = NormalSize[2];
			}
			//*/
		}
		/*
		void drawKey(Key^ k, Graphics^ g) {

			if(k->Tag=="/"||k->Tag=="X"||k->Tag=="+"||k->Tag=="-"||k->Tag=="=")
				g->FillEllipse(ONKeyBackBrush, k->Location.X, k->Location.Y, k->Size.Width, k->Size.Height);
			else
			g->FillEllipse(NKeyBackBrush, k->Location.X, k->Location.Y, k->Size.Width, k->Size.Height);
			//g->DrawEllipse(p, Width / 2 - 40, Height / 2 - 40, 80, 80);

			// font chữ dùng hiển thị trong button


			// kích thước gốc của đoạn text
			//SizeF^ size = g->MeasureString(k->Tag, f);
			//			g->Transform->Scale()


			if (k->Tag == "/" || k->Tag == "X" || k->Tag == "+" || k->Tag == "-" || k->Tag == "=")
			g->DrawString(k->Tag, f, ONKeyTextBrush, PointF(k->Location.X + k->Size.Width / 2, k->Location.Y + k->Size.Height / 2), sf);
			else
			g->DrawString(k->Tag, f, NKeyTextBrush, PointF(k->Location.X+ k->Size.Width/2, k->Location.Y + k->Size.Height / 2), sf);


			//g->DrawLine(p, Width / 2, 0, Width / 2, Height);
			//g->DrawLine(p, 0, Height / 2, Width, Height / 2);
		}
		*/
		Brush^ brush = gcnew SolidBrush(BackKeyColor);
		bool initted = false;
		void OnPaint(PaintEventArgs^ pEvent) override {
			if (!initted)
			{
				init();
				setLocation();
				initted = true;
			}
			Panel::OnPaint(pEvent);
			Graphics^ g = pEvent->Graphics;
			g->SmoothingMode = Drawing2D::SmoothingMode::AntiAlias;
			g->Clear(BackKeyColor);
			for (int i = 0; i < 6; i++)
				for (int j = 0; j < 6; j++) {
					key[i, j]->Draw(pEvent->Graphics);
				}


		};


		void OnMouseDown(System::Windows::Forms::MouseEventArgs^ e) override {
			Panel::OnMouseDown(e);
			// chuột di trên panel 
			Point^ p = e->Location;
			for (int i = 0; i < 6; i++)
				for (int j = 0; j < 6; j++)
				{
					if (key[i, j]->IsInside(p) && !key[i, j]->IsDown)
					{
						key[i, j]->IsDown = true;
						redraw();
						if (listener != nullptr)
						{
							if (i == 1 && j == 0) {
								// shift
								ShiftPressed();
							}
							else
								listener->KeyPressed(key[i, j]->Tag,6*i+j);
						}
						return;
					}
				}
		}
		void OnMouseUp(System::Windows::Forms::MouseEventArgs^ e) override {
			Panel::OnMouseUp(e);
			// chuột di trên panel 
			Point^ p = e->Location;
			for (int i = 0; i < 6; i++)
				for (int j = 0; j < 6; j++)
				{
					if (key[i, j]->IsInside(p) && key[i, j]->IsDown)
					{
						key[i, j]->IsDown = false;
						redraw();
						return;
					}
				}
		}
		void OnMouseMove(System::Windows::Forms::MouseEventArgs^ e) override {
			Panel::OnMouseMove(e);
			// chuột di trên panel 
			Point^ p = e->Location;
			for (int i = 0; i < 6; i++)
				for (int j = 0; j < 6; j++)
				{
					bool should_redawn = false;
					if (key[i, j]->IsInside(p) && !key[i, j]->IsMoving)
					{
						key[i, j]->IsMoving = true;

						should_redawn = true;
					}
					else if ((!key[i, j]->IsInside(p)) && key[i, j]->IsMoving) // key được di qua trước đó {
					{
						key[i, j]->IsMoving = false;
						should_redawn = true;

					}
					else if (key[i, j]->IsDown) {
						key[i, j]->IsDown = false;
						should_redawn = true;
					}
					if (should_redawn)
						redraw();

				}
		}

		void OnMouseLeave(Object^ o, EventArgs^ e) {

			// chuột di khỏi panel 
			for (int i = 0; i < 6; i++)
				for (int j = 0; j < 6; j++)
				{
					bool should = false;
					if (key[i, j]->IsMoving)
					{
						key[i, j]->IsMoving = false;
						should = true;

					}
					else if (key[i, j]->IsDown) {
						key[i, j]->IsDown = false;
						should = true;
					}
					if (should) redraw();
				}
		}

	private: void ShiftPressed() {
		if (!isShiftOn) {
			key[0, 0]->Tag = "RoL";
			key[0, 1]->Tag = "RoR";

		}
		else {
			key[0, 0]->Tag = "Lsh";
			key[0, 1]->Tag = "Rsh";
		}
		((ShiftKey^)key[1, 0])->IsOn = !((ShiftKey^)key[1, 0])->IsOn;
		isShiftOn = !isShiftOn;
		Invalidate(Rectangle(key[1, 0]->Location.X, key[1, 0]->Location.Y, key[1, 0]->Size.Width, key[1, 0]->Size.Height));
	}
			 bool isShiftOn = false;
			 bool isInAnimation = false;
			 Timer^ alphaTimer = gcnew Timer();
			 Timer^ motionTimer = gcnew Timer();
			 enum class Command {
				 HexToBin,
				 DecToBin,
				 BinToDec,
				 BinToHex,
				 HexToDec,
				 DecToHex,
				 MoveAndResize_Smaller,
				 MoveAndResize_Bigger
			 };
			 List<NKey^>^ AtoFKey;
			 List<NKey^>^ TwoToNineKey;
			 List<NKey^>^ ZeroOneKey;
			 void createOutList() {
				 AtoFKey = gcnew List<NKey^>();
				 TwoToNineKey = gcnew List<NKey^>();
				 ZeroOneKey = gcnew List<NKey^>();
				 
				 for (int i = 2; i < 5; i++)
					 for (int j = 0; j < 2; j++)
						 AtoFKey->Add(((NKey^)key[i, j]));
				 for (int i = 4; i != 1; i--)
					 for (int j = 2; j != 5; j++)
					 {
						
						 if (i == 4 && j == 2) continue;
							 TwoToNineKey->Add(((NKey^)key[i, j]));
					 }
				 ZeroOneKey->Add(((NKey^)key[5, 3]));
				 ZeroOneKey->Add(((NKey^)key[4, 2]));

				 // 0 1 =
				 BinKey->AddRange(ZeroOneKey);
				 BinKey->Add(((NKey^)key[5, 5]));
				 for (int i = 0; i < 3; i++) {
					 NormalPoint->Add(Point(0, 0));
					 BinPoint->Add(Point(0, 0));
					 NormalSize->Add(Drawing::Size(0, 0));
					 BinSize->Add(Drawing::Size(0, 0));
					 CurrentPoint->Add(Point(0, 0));
					 CurrentSize->Add(Drawing::Size(0, 0));
				 }
			 }
			 MODE Mode = MODE::HEX;
			 enum class WhichWork {
				 Blur,
				 Enclear,
				 Bigger,
				 Smaller
			 };
			 WhichWork WW = WhichWork::Enclear;
			 List<NKey^>^  applyList = gcnew List<NKey^>(); // những key được áp dụng 
			 List<NKey^>^ BinKey = gcnew List<NKey^>(); 
			 List<Point>^ NormalPoint = gcnew List<Point>(),^BinPoint = gcnew List<Point>(); // vị trí trước và sau 
			 List<Drawing::Size>^ NormalSize = gcnew List<Drawing::Size>() , ^BinSize = gcnew List<Drawing::Size>(); // kích thước trước và sau 
			
			 List<Drawing::Size>^ CurrentSize = gcnew List<Drawing::Size>();
			 List<Point>^ CurrentPoint = gcnew List<Point>();
			 float delta = 0;
			 
			 List<Command>^ lastCommand = gcnew List<Command>();
			 void DoThis(Command c) {
				 if (isInAnimation) {
					 lastCommand->Add(c);
					 return;
				 }
				 isInAnimation = true;
				 applyList->Clear();
				 switch (c) {
				 case Command::HexToBin:applyList->AddRange(AtoFKey); applyList->AddRange(TwoToNineKey); WW = WhichWork::Blur; alphaTimer->Enabled = true; 
					 DoThis(Command::MoveAndResize_Bigger); return;
				 case Command::DecToBin :applyList->AddRange(TwoToNineKey); WW = WhichWork::Blur; alphaTimer->Enabled = true;
					 DoThis(Command::MoveAndResize_Bigger); return;
				 case  Command::BinToDec:DoThis(Command::MoveAndResize_Smaller); applyList->AddRange(TwoToNineKey); WW = WhichWork::Enclear; alphaTimer->Enabled = true;
					  return;
				 case Command::BinToHex :DoThis(Command::MoveAndResize_Smaller); applyList->AddRange(AtoFKey); applyList->AddRange(TwoToNineKey); WW = WhichWork::Enclear; alphaTimer->Enabled = true;
					  return;
				 case Command::HexToDec:applyList->AddRange(AtoFKey); WW = WhichWork::Blur; alphaTimer->Enabled = true;
					return;
				 case Command::DecToHex:applyList->AddRange(AtoFKey); WW = WhichWork::Enclear; alphaTimer->Enabled = true; return;
				 case Command::MoveAndResize_Smaller:WW = WhichWork::Smaller; motionTimer->Enabled = true; return;
				 case Command::MoveAndResize_Bigger:WW = WhichWork::Bigger; motionTimer->Enabled = true; return;
				 default:return;
				 }
			 }
			 void alpha_OnTick(System::Object ^sender, System::EventArgs ^e)
			 {
				 if (delta*alphaTimer->Interval < aTiming)
					 delta += 1;
				 else {
					 delta = 0;
					 isInAnimation = false;
					 alphaTimer->Enabled = false;
					// Diagnostics::Debug::WriteLine("Timer disable");
					 // chạy tiếp lệnh kế tiếp 
					 if (lastCommand->Count != 0) {
						 DoThis(lastCommand[0]);
						 lastCommand->RemoveAt(0);
					 }
					 return;
				 }
				 // do your work
				 float pc = (WW == WhichWork::Enclear) ? delta / (aTiming / alphaTimer->Interval + 0.0f) : 1.0f - (delta / (aTiming / (alphaTimer->Interval + 0.0f)));
				for(int i=0;i<applyList->Count;i++)
				 applyList[i]->pc = pc;
					
				 Invalidate(); // draw again
				 }
			  float mTension = 1.5f;
			 float overshoot(float t)
			 {
				 t -= 1.0f;
				 return t * t * ((mTension + 1) * t + mTension) + 1.0f;
			 }
				 void motion_OnTick(System::Object ^sender, System::EventArgs ^e) {
					 if (delta*motionTimer->Interval < mTiming)
						 delta += 1;
					 else {
						 delta = 0;
						 isInAnimation = false;
						 motionTimer->Enabled = false;
						 //Diagnostics::Debug::WriteLine("motion timer disable");
						 if (lastCommand->Count != 0) {
							 DoThis(lastCommand[0]);
							 lastCommand->RemoveAt(0);
						 }
						 return;
					 }
					 // do your work
					 float pc = (WW == WhichWork::Bigger) ? delta / (mTiming / motionTimer->Interval + 0.0f) : 1.0f - (delta / (mTiming / (motionTimer->Interval + 0.0f)));
					// Diagnostics::Debug::WriteLine(" pc =  "+ pc);
					if(WW == WhichWork::Bigger) pc = overshoot(pc);
					else pc = 1 - overshoot(1 - pc);
					 for (int i = 0; i < 3; i++) {
						 CurrentPoint[i] = Point( NormalPoint[i].X + pc*(BinPoint[i].X - NormalPoint[i].X),
						  NormalPoint[i].Y + pc*(BinPoint[i].Y - NormalPoint[i].Y));

						 CurrentSize[i]= Drawing::Size(
							 NormalSize[i].Width + pc*(BinSize[i].Width - NormalSize[i].Width),
							 NormalSize[i].Height + pc*(BinSize[i].Height - NormalSize[i].Height));
						 BinKey[i]->Size = CurrentSize[i];
						 BinKey[i]->Location = CurrentPoint[i];
					 }
					 
					 Invalidate();
				 }
				 public:
				 void SwitchMode(MODE newMode) {
					 MODE oldMode = Mode;
					 Mode = newMode;
					 if (oldMode == MODE::BIN&&newMode == MODE::DEC)
						 DoThis(Command::BinToDec);
					 else if (oldMode == MODE::DEC&&newMode == MODE::BIN)
						 DoThis(Command::DecToBin);
					 else if (oldMode == MODE::DEC&&newMode == MODE::HEX)
						 DoThis(Command::DecToHex);
					 else if (oldMode == MODE::HEX&&newMode == MODE::DEC)
						 DoThis(Command::HexToDec);
					 else if (oldMode == MODE::HEX&&newMode == MODE::BIN)
						 DoThis(Command::HexToBin);
					 else if (oldMode == MODE::BIN&&newMode == MODE::HEX)
						 DoThis(Command::BinToHex);
				 }
				
};

};


