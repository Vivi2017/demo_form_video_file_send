#pragma once

namespace demo_form {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	static bool stopPush = false;
	/// <summary>
	/// Summary for MyForm1
	/// </summary>
	public ref class MyFormProgress : public System::Windows::Forms::Form
	{
	public:
		MyFormProgress(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyFormProgress()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:
	private: System::Windows::Forms::Button^  button_cancel;
	private: System::Windows::Forms::BindingSource^  bindingSource1;
	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->button_cancel = (gcnew System::Windows::Forms::Button());
			this->bindingSource1 = (gcnew System::Windows::Forms::BindingSource(this->components));
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->bindingSource1))->BeginInit();
			this->SuspendLayout();
			// 
			// button_cancel
			// 
			this->button_cancel->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->button_cancel->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->button_cancel->Location = System::Drawing::Point(100, 23);
			this->button_cancel->Name = L"button_cancel";
			this->button_cancel->Size = System::Drawing::Size(103, 39);
			this->button_cancel->TabIndex = 1;
			this->button_cancel->Text = L"Cancel";
			this->button_cancel->UseVisualStyleBackColor = true;
			this->button_cancel->Click += gcnew System::EventHandler(this, &MyFormProgress::button_cancel_Click);
			// 
			// MyFormProgress
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->ClientSize = System::Drawing::Size(330, 89);
			this->Controls->Add(this->button_cancel);
			this->Name = L"MyFormProgress";
			this->Text = L"Playing...";
			this->Load += gcnew System::EventHandler(this, &MyFormProgress::MyFormProgress_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->bindingSource1))->EndInit();
			this->ResumeLayout(false);

		}

	public:void setProgress(int pos)
		{
			//this->progressBar->Increment(pos);
		 
		}
#pragma endregion
	private: System::Void button_cancel_Click(System::Object^  sender, System::EventArgs^  e) {
		stopPush = true;
		this->Hide();
	}
	private: System::Void progressBar_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void MyFormProgress_Load(System::Object^  sender, System::EventArgs^  e) {
	}
	};
}
