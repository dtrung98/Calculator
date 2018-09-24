#pragma once
#include "UIHelper.h"
namespace MayTinhTay {
	using namespace Collections::Generic;
	public ref class LinearPanel : Panel
	{
	public:
		LinearPanel() : Panel() {};
	protected:
		List<float>^  child_radio = gcnew List<float>();
		List<Control^>^ child_control = gcnew List<Control^>();
		float radio_sum = 1;
		bool vertical = true;
	public:
		void SetOrientation(bool vertical) {
			this->vertical = vertical;
		}
		void SetRadioSummary(float sum) {
			radio_sum = sum;
		}
		void Add(Control^ c, float radio) {
			this->Controls->Add(c);
			child_radio->Add(radio);
			child_control->Add(c);
			OnDecorate();
		}
		// cân chỉnh lại vị trí các control trong panel 
		void OnDecorate() {
			float pos = 0;
			this->SuspendLayout();
			for (int i = 0; i < child_control->Count; i++) {
				if (vertical) {
					child_control[i]->Width = Width;
					child_control[i]->Height = this->Height*child_radio[i] * 1.0f / radio_sum;
					child_control[i]->Location = Point(0,pos);
					pos += child_control[i]->Height;
				}
				else {
					child_control[i]->Height = Height;
					child_control[i]->Width = this->Width*child_radio[i] * 1.0f / radio_sum;
					child_control[i]->Location = Point(pos, 0);
					pos += child_control[i]->Width;

				}
				
			}
			this->ResumeLayout();
		}
		void OnResize(System::EventArgs^ eventargs) override {
			OnDecorate();
			Panel::OnResize(eventargs);
			}
		
	
	};

}