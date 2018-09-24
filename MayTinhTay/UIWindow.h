
#include "LinearPanel.h"
#include "KeysGrid.h"
#include "NumberTypeButton.h"
#include "WordWrapLabel.h"
#include "QInt.h"
namespace MayTinhTay {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Zusammenfassung für Form1
	/// </summary>
	public ref class UIWindow : public System::Windows::Forms::Form, KeysListener, TypeListener
	{
	public:

		UIWindow(String^, String^, QInt);

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~UIWindow()
		{
			if (components)
			{
				delete components;
			}
		}
	public: LinearPanel^ panel;
			Label^ lb1 = nullptr, ^lb2, ^lb3;
			KeysGrid^ keysGrid;
			NumberTypeButton^ HexButton, ^DecButton, ^BinButton;
			WordWrapLabel^ ResultLabel;
			WordWrapLabel^ SmallLabel;
			// biến lưu giá trị của số ở 3 chế độ 
			
			// biến lưu 2 toán hạng của phép toán 
			String^ Parameters = "";
			array<QInt*>^ Number = gcnew array<QInt*>(2);
			// biến lưu toán hạng hiện tại 
			int WhichOperator = 0; // ID cua toan tu
			array<String^>^ Operator; // Mang toan tu
			int whichNumber = 0; // 0 nghia la so thu nhat, 1 nghia la so thu 2
	public:


	protected:

	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(UIWindow::typeid));
			this->SuspendLayout();
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Black;
			this->ClientSize = System::Drawing::Size(402, 933);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Margin = System::Windows::Forms::Padding(4);
			this->MinimumSize = System::Drawing::Size(420, 980);
			this->Name = L"Form1";
			this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
			this->Text = L"Máy Tính Tay";
			this->Load += gcnew System::EventHandler(this, &UIWindow::Form1_Load);
			this->SizeChanged += gcnew System::EventHandler(this, &UIWindow::Form1_SizeChanged);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void Form1_SizeChanged(System::Object^  sender, System::EventArgs^  e) {
		if(lb2!=nullptr)
		lb2->Text = Width + " : " + Height;
	}

			 // Inherited via KeysListener
	public:
		
		void UpdateValueType();
		void EqualPressed();
		String ^ GetNumber(int i);
		void OperatorPressed(int which);
		void BackPressed();
		void NumberPressed(Char which);
		void SignPressed();
		virtual void KeyPressed(String^ tag,int);
			void ML(Object^, EventArgs^ e);
			int getOperatorCodeID(String ^ s);
			virtual void ActiveThis(Control^);
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
	}

			 // Inherited via TypeListener
			
	public: 
			 MODE Mode = MODE::HEX;
	};
}
