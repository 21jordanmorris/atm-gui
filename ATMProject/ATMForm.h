#pragma once
#include "Bank.h"
#include "Account.h"

namespace ATMProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for ATMForm
	/// </summary>
	public ref class ATMForm : public System::Windows::Forms::Form
	{
	private:
		Bank* main_bank_pointer;
		Account* bob_pointer;
		Account* jan_pointer;
		Account* perry_pointer;
		Account* fred_pointer;
	public:
		ATMForm(void)
		{
			InitializeComponent();
			main_bank_pointer = new Bank();
			bob_pointer = new Account(68452, 32185);
			jan_pointer = new Account(98765, 43210);
			perry_pointer = new Account(78631, 94568, 1807.87);
			fred_pointer = new Account(35648, 75426, 97.67);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ATMForm()
		{
			if (components)
			{
				delete components;
				delete main_bank_pointer, bob_pointer, jan_pointer, perry_pointer, fred_pointer;
			}
		}

#pragma region Variables and Methods
	private:
		int pin_attempt_counter, numbers_after_decimal;
		/*
			The value of state_tracker (0-11) will determine which state the form should be presenting.
		*/
		int state_tracker;
		/*
			User input variables
		*/
		String^ user_input;
		int account_number_input, pin_number_input, menu_choice_input, transfer_to_account_num;
		double withdraw_amount, deposit_amount, transfer_amount;

		void change_state(int state_numeric_version);
		/*
			User input methods
		*/
		bool can_input_decimal();
		bool can_input_number();
		void add_to_user_input(String^ text);
		void reset_user_input();
		int string_hat_to_int(String^ text);
		double string_hat_to_double(String^ text);
		char * string_hat_to_char(String^ text);

		void number_click(String^ num);


#pragma region Auto generated button and panel declarations
	private: System::Windows::Forms::Panel^ KeypadPanel;
	private: System::Windows::Forms::Button^ One;
	private: System::Windows::Forms::Button^ Two;
	private: System::Windows::Forms::Button^ Three;
	private: System::Windows::Forms::Button^ Four;
	private: System::Windows::Forms::Button^ Five;
	private: System::Windows::Forms::Button^ Six;
	private: System::Windows::Forms::Button^ Seven;
	private: System::Windows::Forms::Button^ Eight;
	private: System::Windows::Forms::Button^ Nine;
	private: System::Windows::Forms::Button^ Zero;
	private: System::Windows::Forms::Button^ Enter;
	private: System::Windows::Forms::TextBox^ txtDisplay;
	private: System::Windows::Forms::Panel^ TakeCashPanelBig;
	private: System::Windows::Forms::Panel^ TakeCashPanelSmall;
	private: System::Windows::Forms::Label^ TakeCashLabel;
	private: System::Windows::Forms::Panel^ InsertPanelBig;
	private: System::Windows::Forms::Button^ Backspace;
	private: System::Windows::Forms::Button^ Decimal;
	private: System::Windows::Forms::Panel^ InsertPanelSmall;
	private: System::Windows::Forms::Label^ InsertLabel;
	private: System::ComponentModel::Container ^components;
#pragma endregion

#pragma endregion

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(ATMForm::typeid));
			this->KeypadPanel = (gcnew System::Windows::Forms::Panel());
			this->Backspace = (gcnew System::Windows::Forms::Button());
			this->Decimal = (gcnew System::Windows::Forms::Button());
			this->Enter = (gcnew System::Windows::Forms::Button());
			this->Zero = (gcnew System::Windows::Forms::Button());
			this->Six = (gcnew System::Windows::Forms::Button());
			this->Nine = (gcnew System::Windows::Forms::Button());
			this->Eight = (gcnew System::Windows::Forms::Button());
			this->Seven = (gcnew System::Windows::Forms::Button());
			this->Five = (gcnew System::Windows::Forms::Button());
			this->Four = (gcnew System::Windows::Forms::Button());
			this->Three = (gcnew System::Windows::Forms::Button());
			this->Two = (gcnew System::Windows::Forms::Button());
			this->One = (gcnew System::Windows::Forms::Button());
			this->txtDisplay = (gcnew System::Windows::Forms::TextBox());
			this->TakeCashPanelBig = (gcnew System::Windows::Forms::Panel());
			this->TakeCashPanelSmall = (gcnew System::Windows::Forms::Panel());
			this->TakeCashLabel = (gcnew System::Windows::Forms::Label());
			this->InsertPanelBig = (gcnew System::Windows::Forms::Panel());
			this->InsertPanelSmall = (gcnew System::Windows::Forms::Panel());
			this->InsertLabel = (gcnew System::Windows::Forms::Label());
			this->KeypadPanel->SuspendLayout();
			this->TakeCashPanelBig->SuspendLayout();
			this->InsertPanelBig->SuspendLayout();
			this->SuspendLayout();
			// 
			// KeypadPanel
			// 
			this->KeypadPanel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->KeypadPanel->BackColor = System::Drawing::Color::Teal;
			this->KeypadPanel->Controls->Add(this->Backspace);
			this->KeypadPanel->Controls->Add(this->Decimal);
			this->KeypadPanel->Controls->Add(this->Enter);
			this->KeypadPanel->Controls->Add(this->Zero);
			this->KeypadPanel->Controls->Add(this->Six);
			this->KeypadPanel->Controls->Add(this->Nine);
			this->KeypadPanel->Controls->Add(this->Eight);
			this->KeypadPanel->Controls->Add(this->Seven);
			this->KeypadPanel->Controls->Add(this->Five);
			this->KeypadPanel->Controls->Add(this->Four);
			this->KeypadPanel->Controls->Add(this->Three);
			this->KeypadPanel->Controls->Add(this->Two);
			this->KeypadPanel->Controls->Add(this->One);
			this->KeypadPanel->Location = System::Drawing::Point(9, 153);
			this->KeypadPanel->Margin = System::Windows::Forms::Padding(2);
			this->KeypadPanel->Name = L"KeypadPanel";
			this->KeypadPanel->Size = System::Drawing::Size(169, 257);
			this->KeypadPanel->TabIndex = 0;
			this->KeypadPanel->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &ATMForm::KeypadPanel_Paint);
			// 
			// Backspace
			// 
			this->Backspace->BackColor = System::Drawing::SystemColors::InactiveCaption;
			this->Backspace->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Backspace->Location = System::Drawing::Point(111, 166);
			this->Backspace->Margin = System::Windows::Forms::Padding(2);
			this->Backspace->Name = L"Backspace";
			this->Backspace->Size = System::Drawing::Size(45, 46);
			this->Backspace->TabIndex = 12;
			this->Backspace->Text = L"←";
			this->Backspace->UseVisualStyleBackColor = false;
			this->Backspace->Click += gcnew System::EventHandler(this, &ATMForm::Backspace_Click);
			// 
			// Decimal
			// 
			this->Decimal->BackColor = System::Drawing::SystemColors::InactiveCaption;
			this->Decimal->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Decimal->Location = System::Drawing::Point(13, 166);
			this->Decimal->Margin = System::Windows::Forms::Padding(2);
			this->Decimal->Name = L"Decimal";
			this->Decimal->Size = System::Drawing::Size(45, 46);
			this->Decimal->TabIndex = 10;
			this->Decimal->Text = L".";
			this->Decimal->UseVisualStyleBackColor = false;
			this->Decimal->Click += gcnew System::EventHandler(this, &ATMForm::Decimal_Click);
			// 
			// Enter
			// 
			this->Enter->BackColor = System::Drawing::SystemColors::InactiveCaption;
			this->Enter->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Enter->Location = System::Drawing::Point(13, 216);
			this->Enter->Margin = System::Windows::Forms::Padding(2);
			this->Enter->Name = L"Enter";
			this->Enter->Size = System::Drawing::Size(145, 34);
			this->Enter->TabIndex = 0;
			this->Enter->Text = L"ENTER";
			this->Enter->UseVisualStyleBackColor = false;
			this->Enter->Click += gcnew System::EventHandler(this, &ATMForm::Enter_Click);
			// 
			// Zero
			// 
			this->Zero->BackColor = System::Drawing::SystemColors::InactiveCaption;
			this->Zero->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Zero->Location = System::Drawing::Point(62, 166);
			this->Zero->Margin = System::Windows::Forms::Padding(2);
			this->Zero->Name = L"Zero";
			this->Zero->Size = System::Drawing::Size(45, 46);
			this->Zero->TabIndex = 11;
			this->Zero->Text = L"0";
			this->Zero->UseVisualStyleBackColor = false;
			this->Zero->Click += gcnew System::EventHandler(this, &ATMForm::Zero_Click);
			// 
			// Six
			// 
			this->Six->BackColor = System::Drawing::SystemColors::InactiveCaption;
			this->Six->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Six->Location = System::Drawing::Point(112, 65);
			this->Six->Margin = System::Windows::Forms::Padding(2);
			this->Six->Name = L"Six";
			this->Six->Size = System::Drawing::Size(45, 46);
			this->Six->TabIndex = 6;
			this->Six->Text = L"6";
			this->Six->UseVisualStyleBackColor = false;
			this->Six->Click += gcnew System::EventHandler(this, &ATMForm::Six_Click);
			// 
			// Nine
			// 
			this->Nine->BackColor = System::Drawing::SystemColors::InactiveCaption;
			this->Nine->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Nine->Location = System::Drawing::Point(112, 116);
			this->Nine->Margin = System::Windows::Forms::Padding(2);
			this->Nine->Name = L"Nine";
			this->Nine->Size = System::Drawing::Size(45, 46);
			this->Nine->TabIndex = 9;
			this->Nine->Text = L"9";
			this->Nine->UseVisualStyleBackColor = false;
			this->Nine->Click += gcnew System::EventHandler(this, &ATMForm::Nine_Click);
			// 
			// Eight
			// 
			this->Eight->BackColor = System::Drawing::SystemColors::InactiveCaption;
			this->Eight->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Eight->Location = System::Drawing::Point(62, 116);
			this->Eight->Margin = System::Windows::Forms::Padding(2);
			this->Eight->Name = L"Eight";
			this->Eight->Size = System::Drawing::Size(45, 46);
			this->Eight->TabIndex = 8;
			this->Eight->Text = L"8";
			this->Eight->UseVisualStyleBackColor = false;
			this->Eight->Click += gcnew System::EventHandler(this, &ATMForm::Eight_Click);
			// 
			// Seven
			// 
			this->Seven->BackColor = System::Drawing::SystemColors::InactiveCaption;
			this->Seven->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Seven->Location = System::Drawing::Point(12, 116);
			this->Seven->Margin = System::Windows::Forms::Padding(2);
			this->Seven->Name = L"Seven";
			this->Seven->Size = System::Drawing::Size(45, 46);
			this->Seven->TabIndex = 7;
			this->Seven->Text = L"7";
			this->Seven->UseVisualStyleBackColor = false;
			this->Seven->Click += gcnew System::EventHandler(this, &ATMForm::Seven_Click);
			// 
			// Five
			// 
			this->Five->BackColor = System::Drawing::SystemColors::InactiveCaption;
			this->Five->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Five->Location = System::Drawing::Point(62, 65);
			this->Five->Margin = System::Windows::Forms::Padding(2);
			this->Five->Name = L"Five";
			this->Five->Size = System::Drawing::Size(45, 46);
			this->Five->TabIndex = 5;
			this->Five->Text = L"5";
			this->Five->UseVisualStyleBackColor = false;
			this->Five->Click += gcnew System::EventHandler(this, &ATMForm::Five_Click);
			// 
			// Four
			// 
			this->Four->BackColor = System::Drawing::SystemColors::InactiveCaption;
			this->Four->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Four->Location = System::Drawing::Point(12, 65);
			this->Four->Margin = System::Windows::Forms::Padding(2);
			this->Four->Name = L"Four";
			this->Four->Size = System::Drawing::Size(45, 46);
			this->Four->TabIndex = 4;
			this->Four->Text = L"4";
			this->Four->UseVisualStyleBackColor = false;
			this->Four->Click += gcnew System::EventHandler(this, &ATMForm::Four_Click);
			// 
			// Three
			// 
			this->Three->BackColor = System::Drawing::SystemColors::InactiveCaption;
			this->Three->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Three->Location = System::Drawing::Point(112, 15);
			this->Three->Margin = System::Windows::Forms::Padding(2);
			this->Three->Name = L"Three";
			this->Three->Size = System::Drawing::Size(45, 46);
			this->Three->TabIndex = 3;
			this->Three->Text = L"3";
			this->Three->UseVisualStyleBackColor = false;
			this->Three->Click += gcnew System::EventHandler(this, &ATMForm::Three_Click);
			// 
			// Two
			// 
			this->Two->BackColor = System::Drawing::SystemColors::InactiveCaption;
			this->Two->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Two->Location = System::Drawing::Point(62, 15);
			this->Two->Margin = System::Windows::Forms::Padding(2);
			this->Two->Name = L"Two";
			this->Two->Size = System::Drawing::Size(45, 46);
			this->Two->TabIndex = 2;
			this->Two->Text = L"2";
			this->Two->UseVisualStyleBackColor = false;
			this->Two->Click += gcnew System::EventHandler(this, &ATMForm::Two_Click);
			// 
			// One
			// 
			this->One->BackColor = System::Drawing::SystemColors::InactiveCaption;
			this->One->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->One->Location = System::Drawing::Point(12, 15);
			this->One->Margin = System::Windows::Forms::Padding(2);
			this->One->Name = L"One";
			this->One->Size = System::Drawing::Size(45, 46);
			this->One->TabIndex = 1;
			this->One->Text = L"1";
			this->One->UseVisualStyleBackColor = false;
			this->One->Click += gcnew System::EventHandler(this, &ATMForm::One_Click);
			// 
			// txtDisplay
			// 
			this->txtDisplay->BackColor = System::Drawing::Color::Black;
			this->txtDisplay->Cursor = System::Windows::Forms::Cursors::Arrow;
			this->txtDisplay->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->txtDisplay->ForeColor = System::Drawing::Color::Lime;
			this->txtDisplay->Location = System::Drawing::Point(9, 10);
			this->txtDisplay->Margin = System::Windows::Forms::Padding(2);
			this->txtDisplay->Multiline = true;
			this->txtDisplay->Name = L"txtDisplay";
			this->txtDisplay->ReadOnly = true;
			this->txtDisplay->Size = System::Drawing::Size(607, 139);
			this->txtDisplay->TabIndex = 1;
			this->txtDisplay->Text = L"Welcome!\r\n\r\nPlease enter your account number: ";
			// 
			// TakeCashPanelBig
			// 
			this->TakeCashPanelBig->BackColor = System::Drawing::Color::Teal;
			this->TakeCashPanelBig->Controls->Add(this->TakeCashPanelSmall);
			this->TakeCashPanelBig->Controls->Add(this->TakeCashLabel);
			this->TakeCashPanelBig->Location = System::Drawing::Point(196, 153);
			this->TakeCashPanelBig->Margin = System::Windows::Forms::Padding(2);
			this->TakeCashPanelBig->Name = L"TakeCashPanelBig";
			this->TakeCashPanelBig->Size = System::Drawing::Size(420, 124);
			this->TakeCashPanelBig->TabIndex = 14;
			// 
			// TakeCashPanelSmall
			// 
			this->TakeCashPanelSmall->BackColor = System::Drawing::Color::Black;
			this->TakeCashPanelSmall->Location = System::Drawing::Point(44, 83);
			this->TakeCashPanelSmall->Margin = System::Windows::Forms::Padding(2);
			this->TakeCashPanelSmall->Name = L"TakeCashPanelSmall";
			this->TakeCashPanelSmall->Size = System::Drawing::Size(345, 19);
			this->TakeCashPanelSmall->TabIndex = 1;
			// 
			// TakeCashLabel
			// 
			this->TakeCashLabel->AutoSize = true;
			this->TakeCashLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->TakeCashLabel->Location = System::Drawing::Point(126, 28);
			this->TakeCashLabel->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->TakeCashLabel->Name = L"TakeCashLabel";
			this->TakeCashLabel->Size = System::Drawing::Size(161, 24);
			this->TakeCashLabel->TabIndex = 0;
			this->TakeCashLabel->Text = L"Take Cash Here";
			// 
			// InsertPanelBig
			// 
			this->InsertPanelBig->BackColor = System::Drawing::Color::Teal;
			this->InsertPanelBig->Controls->Add(this->InsertPanelSmall);
			this->InsertPanelBig->Controls->Add(this->InsertLabel);
			this->InsertPanelBig->Location = System::Drawing::Point(196, 288);
			this->InsertPanelBig->Margin = System::Windows::Forms::Padding(2);
			this->InsertPanelBig->Name = L"InsertPanelBig";
			this->InsertPanelBig->Size = System::Drawing::Size(420, 122);
			this->InsertPanelBig->TabIndex = 15;
			// 
			// InsertPanelSmall
			// 
			this->InsertPanelSmall->BackColor = System::Drawing::Color::Black;
			this->InsertPanelSmall->Location = System::Drawing::Point(53, 81);
			this->InsertPanelSmall->Margin = System::Windows::Forms::Padding(2);
			this->InsertPanelSmall->Name = L"InsertPanelSmall";
			this->InsertPanelSmall->Size = System::Drawing::Size(324, 17);
			this->InsertPanelSmall->TabIndex = 3;
			// 
			// InsertLabel
			// 
			this->InsertLabel->AutoSize = true;
			this->InsertLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->InsertLabel->Location = System::Drawing::Point(66, 35);
			this->InsertLabel->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->InsertLabel->Name = L"InsertLabel";
			this->InsertLabel->Size = System::Drawing::Size(284, 24);
			this->InsertLabel->TabIndex = 1;
			this->InsertLabel->Text = L"Insert Deposit Envelope Here";
			// 
			// ATMForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->ClientSize = System::Drawing::Size(627, 420);
			this->Controls->Add(this->InsertPanelBig);
			this->Controls->Add(this->TakeCashPanelBig);
			this->Controls->Add(this->txtDisplay);
			this->Controls->Add(this->KeypadPanel);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Margin = System::Windows::Forms::Padding(2);
			this->Name = L"ATMForm";
			this->Text = L"ATM";
			this->Load += gcnew System::EventHandler(this, &ATMForm::ATMForm_Load);
			this->KeypadPanel->ResumeLayout(false);
			this->TakeCashPanelBig->ResumeLayout(false);
			this->TakeCashPanelBig->PerformLayout();
			this->InsertPanelBig->ResumeLayout(false);
			this->InsertPanelBig->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void KeypadPanel_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {}
	private: System::Void ATMForm_Load(System::Object^ sender, System::EventArgs^ e);
	private: System::Void One_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void Two_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void Three_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void Four_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void Five_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void Six_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void Seven_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void Eight_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void Nine_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void Zero_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void Enter_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void Backspace_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void Decimal_Click(System::Object^ sender, System::EventArgs^ e);
};
}
