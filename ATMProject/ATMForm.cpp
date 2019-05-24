#include "ATMForm.h"
#include "Account.h"
#include "Bank.h"
#include <iostream>
#include <sstream>
#include <thread>
#include <msclr\marshal_cppstd.h>

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Runtime::InteropServices;
using namespace ATMProject;

// ENUMERATORS
#define ACCOUNT_STATE                  0
#define PIN_STATE                      1
#define MENU_STATE                     2
#define BALANCE_STATE                  3
#define PROMPT_WITHDRAW_STATE          4
#define WITHDRAW_COMPLETION_STATE      5
#define PROMPT_DEPOSIT_STATE           6
#define DEPOSIT_COMPLETION_STATE       7
#define TRANSFER_ACCOUNT_STATE         8
#define TRANSFER_AMOUNT_STATE          9
#define TRANSFER_COMPLETION_STATE     10
#define EXIT_STATE                    11

[STAThreadAttribute]
int main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	ATMForm form;
	Application::Run(% form);
}


/*
  When calling change_state, you must pass a numerical value representing a specific state. This method will go 
  to the designated state and handle changes to the screen. Below is the state that corresponds with each number:
  [0] - Account State                      [5] - Withdraw Completion State               [10] - Transfer Completion State
  [1] - Pin State                          [6] - Prompt Desposit State                   [11] - Exit State
  [2] - Main Menu State                    [7] - Deposit Completion State            
  [3] - View Balance State                 [8] - Transfer Account State
  [4] - Prompt Withdraw State              [9] - Transfer Amount State
*/
void ATMForm::change_state(int state_numeric_value)
{
	switch (state_numeric_value)
	{
		/*
			Account Input State
		*/
		case ACCOUNT_STATE:
			state_tracker = ACCOUNT_STATE;
			txtDisplay->Text = " Welcome!\r\n\r\n Please enter your account number: ";
			break;
		/*
			PIN Input State
		*/
		case PIN_STATE:
			state_tracker = PIN_STATE;
			txtDisplay->Text += "\r\n Enter your pin number: ";
			break;
		/*
			Main Menu State
		*/
		case MENU_STATE:
			state_tracker = MENU_STATE;
			if (TakeCashPanelSmall->BackColor == System::Drawing::Color::Green)
				TakeCashPanelSmall->BackColor = System::Drawing::Color::Black;
			txtDisplay->Text = " Main Menu:\r\n\r\t1 - View my balance\r\n\r\t2 - Withdraw Cash\r\n\r\t3 - Deposit Funds\r\n\r\t4 - Transfer Funds\r\n\r\t5 - Exit\r\n Enter a choice: ";
			break;
		/*
			Check Balance State
		*/
		case BALANCE_STATE:
			state_tracker = BALANCE_STATE;
			txtDisplay->Text = " Your current balance: $" + main_bank_pointer->get_account(account_number_input).get_balance();

			add_to_user_input("" + main_bank_pointer->get_account(account_number_input).get_balance());
			if (!user_input->Contains("."))
				txtDisplay->Text += ".00";
			else if (user_input->IndexOf(".") == user_input->Length - 2)
				txtDisplay->Text += "0";
			reset_user_input();

			txtDisplay->Text += "\r\n\r\n\r\n Press enter to go back to the main menu.\r\n\r\n\r\n\r\n\r\n\r\n\r\n ";
			break;
		/*
			Withdraw State
		*/
		case PROMPT_WITHDRAW_STATE:
			state_tracker = PROMPT_WITHDRAW_STATE;
			txtDisplay->Text = " Enter the amount to be withdrawn: $";
			break;
		/*
			Withdraw State Completion
		*/
		case WITHDRAW_COMPLETION_STATE:
			state_tracker = WITHDRAW_COMPLETION_STATE;
			TakeCashPanelSmall->BackColor = System::Drawing::Color::Green;
			txtDisplay->Text = " Your balance has been updated. \r\n\r\n\r\n Press enter to go back to the main menu\r\n\r\n\r\n\r\n\r\n ";
			break;
		/*
			Deposit State
		*/
		case PROMPT_DEPOSIT_STATE:
			state_tracker = PROMPT_DEPOSIT_STATE;
			InsertPanelSmall->BackColor = System::Drawing::Color::Orange;
			txtDisplay->Text = " Enter the amount to be deposited: $";
			break;
		/*
			Deposit State Completion
		*/
		case DEPOSIT_COMPLETION_STATE:
			state_tracker = DEPOSIT_COMPLETION_STATE;
			InsertPanelSmall->BackColor = System::Drawing::Color::Black;
			txtDisplay->Text = " Your balance has been updated. \r\n\r\n\r\n Press enter to go back to the main menu\r\n\r\n\r\n\r\n\r\n";
			break;
		/*
			Transfer Funds Account State
		*/
		case TRANSFER_ACCOUNT_STATE:
			state_tracker = TRANSFER_ACCOUNT_STATE;
			txtDisplay->Text = " Enter the account number to transfer to: ";
			break;
		/*
			Transfer Funds Amount State
		*/
		case TRANSFER_AMOUNT_STATE:
			state_tracker = TRANSFER_AMOUNT_STATE;
			txtDisplay->Text += "\r\n Enter the amount to be transferred: $";
			break;
		/*
			Transfer Funds Completion State
		*/
		case TRANSFER_COMPLETION_STATE:
			state_tracker = TRANSFER_COMPLETION_STATE;
			txtDisplay->Text = " Transfer was successful. \r\n\r\n\r\n Press enter to go back to the main menu\r\n\r\n\r\n\r\n\r\n\r\n ";
			break;
		/*
			Exit State
		*/
		case EXIT_STATE:
			state_tracker = EXIT_STATE;
			/*
				Setting account and pin number back to zero to simulate logging out.
			*/
			account_number_input = 0;
			pin_number_input = 0;

			/*
				Recursively call change_state to go back to the welcome page.
			*/
			change_state(ACCOUNT_STATE);
			break;
		default:
			throw std::invalid_argument("Invalid state value");
	}
}

/*
  Concatenates desired text to the user_input String^ variable.
*/
void ATMForm::add_to_user_input(String^ text)
{
	user_input += text;
}

/*
  Resets user_input variable to an empty string.
*/
void ATMForm::reset_user_input()
{
	numbers_after_decimal = -1;
	user_input = "";
}

/*
  Returns true if the user has not already inputted a decimal (without deleting it) and if the current
  state the user is in is ok to place one.
*/
bool ATMForm::can_input_decimal()
{
	if (!user_input->Contains(".") && (state_tracker == PROMPT_WITHDRAW_STATE || state_tracker == PROMPT_DEPOSIT_STATE || state_tracker == TRANSFER_AMOUNT_STATE))
		return true;
	return false;

}

/*
  Returns true if the current state the user is in allows for numbers to be inputted.
*/
bool ATMForm::can_input_number()
{
	if (state_tracker == BALANCE_STATE || state_tracker == WITHDRAW_COMPLETION_STATE || state_tracker == DEPOSIT_COMPLETION_STATE || state_tracker == TRANSFER_COMPLETION_STATE)
		return false;
	return true;
}

/*
  Converts String^ to char pointer (used for other conversion methods)
*/
char * ATMForm::string_hat_to_char(String^ text)
{
	/* Marshal::StringToHGlobalAnsi : copies the contents of a managed String into unmanaged memory, converting into ANSI format */
	IntPtr ptr_to_native_string = Marshal::StringToHGlobalAnsi(text);
	return static_cast<char*>(ptr_to_native_string.ToPointer());

}

/*
  Converts String^ to integer
*/
int ATMForm::string_hat_to_int(String^ text)
{
	return atoi(string_hat_to_char(text));
}

/*
  Converts String^ to double
*/
double ATMForm::string_hat_to_double(String^ text)
{
	return atof(string_hat_to_char(text));
}

/*
  Called whenever a numerical button is clicked. Checks for numbers after decimal and if the user is in a state that allows for 
  numerical input.
*/
void ATMForm::number_click(String^ num)
{
	/* Checks if there is a decimal and if so, makes sure that the user cannot input a third decimal place. */
	if (numbers_after_decimal < 2)
	{
		/* Makes sure the user is in a state that allows for numerical input. */
		if (can_input_number())
		{
			add_to_user_input(num);
			/* Hides input if entering a pin number. */
			if (state_tracker == PIN_STATE)
				txtDisplay->Text += "*";
			else
				txtDisplay->Text += num;
		}
	}

	/* If a decimal place has been placed and there is still room for more ($12. or $12.3) then increase numbers_after_decimal */
	if (numbers_after_decimal != -1 && numbers_after_decimal != 2)
		numbers_after_decimal++;
}


/*
  When loading up the users already created will be added to the Bank's lists and the app will initialize in the
  initial stage (prompting for the account number).
*/
void ATMForm::ATMForm_Load(System::Object^ sender, System::EventArgs^ e) 
{
	pin_attempt_counter = 0;
	numbers_after_decimal = -1;
	main_bank_pointer->add_account(*bob_pointer);
	main_bank_pointer->add_account(*jan_pointer);
	main_bank_pointer->add_account(*perry_pointer);
	main_bank_pointer->add_account(*fred_pointer);
	reset_user_input();
	change_state(ACCOUNT_STATE);
}

/*
  Numerical button event listeners. When a numerical button is pressed, that number is concatenated to user_input
  along with displaying the number on the ATM screen. If the state_number = 2 (and is in the pin number
  mode) then it will hide the number (as a *).
*/
void ATMForm::One_Click(System::Object^ sender, System::EventArgs^ e)
{
	number_click("1");
}
void ATMForm::Two_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	number_click("2");
}
void ATMForm::Three_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	number_click("3");
}
void ATMForm::Four_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	number_click("4");
}
void ATMForm::Five_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	number_click("5");
}
void ATMForm::Six_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	number_click("6");
}
void ATMForm::Seven_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	number_click("7");
}
void ATMForm::Eight_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	number_click("8");
}
void ATMForm::Nine_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	number_click("9");
}
void ATMForm::Zero_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	number_click("0");
}

/*
  Enter button event listener. When the enter button is pressed, this method will check what the current state
  the ATM is in and handle neccessary actions such as changing state and calling methods from the Bank and Account
  classes.
*/
void ATMForm::Enter_Click(System::Object ^ sender, System::EventArgs ^ e)
{

	if (state_tracker == ACCOUNT_STATE)
	{
		/* Verify account number and change state based on result */
		account_number_input = string_hat_to_int(user_input);
		reset_user_input();
		if (main_bank_pointer->account_number_exists(account_number_input))
			change_state(PIN_STATE);
		else
			change_state(ACCOUNT_STATE);
	}
	else if (state_tracker == PIN_STATE)
	{
		/* Verify pin number and change state based on result */
		pin_number_input = string_hat_to_int(user_input);
		reset_user_input();
		if (main_bank_pointer->verify_pin(account_number_input, pin_number_input))
			change_state(MENU_STATE);
		else
		{
			pin_attempt_counter++;
			if (pin_attempt_counter <= 2)
				txtDisplay->Text += "\r\n Incorrect PIN, please try again: ";
			else
			{
				pin_attempt_counter = 1;
				change_state(ACCOUNT_STATE);
			}
		}
	}
	else if (state_tracker == MENU_STATE)
	{
		menu_choice_input = string_hat_to_int(user_input);
		reset_user_input();
		switch (menu_choice_input)
		{
		case 1:
			/* Change to balance state */
			change_state(BALANCE_STATE);
			break;
		case 2:
			/* Change to withdraw state */
			change_state(PROMPT_WITHDRAW_STATE);
			break;
		case 3:
			/* Change to deposit state */
			change_state(PROMPT_DEPOSIT_STATE);
			break;
		case 4:
			/* Change to transfer state */
			change_state(TRANSFER_ACCOUNT_STATE);
			break;
		case 5:
			/* Change to exit state */
			change_state(EXIT_STATE);
			break;
		default:
			/* Non 1-5 input, stays at menu state */
			change_state(MENU_STATE);
		}
	}
	else if (state_tracker == PROMPT_WITHDRAW_STATE)
	{
		withdraw_amount = string_hat_to_double(user_input);
		reset_user_input();
		/* Call checker before withdrawing funds */
		if (main_bank_pointer->get_account(account_number_input).can_withdraw_funds(withdraw_amount))
		{
			/* Withdraw funds */
			main_bank_pointer->get_account(account_number_input).withdraw_funds(withdraw_amount);
			change_state(WITHDRAW_COMPLETION_STATE);
		}
		else
		{
			/* Insufficient Funds - Change state to main menu */
			change_state(MENU_STATE);
			txtDisplay->Text = " Insufficient Funds.\r\n" + txtDisplay->Text;
		}
	}
	else if (state_tracker == PROMPT_DEPOSIT_STATE)
	{
		/* Deposit desired amount into the account and change state */
		deposit_amount = string_hat_to_double(user_input);
		reset_user_input();
		main_bank_pointer->get_account(account_number_input).deposit_funds(deposit_amount);
		change_state(DEPOSIT_COMPLETION_STATE);
	}
	else if (state_tracker == TRANSFER_ACCOUNT_STATE)
	{
		/* Verify account number input and change state based off result. */
		transfer_to_account_num = string_hat_to_int(user_input);
		reset_user_input();
		if (main_bank_pointer->account_number_exists(transfer_to_account_num) && (transfer_to_account_num != account_number_input))
			change_state(TRANSFER_AMOUNT_STATE);
		else
		{
			change_state(MENU_STATE);
			txtDisplay->Text = " Invalid Account Number.\r\n" + txtDisplay->Text;
		}
	}
	else if (state_tracker == TRANSFER_AMOUNT_STATE)
	{
		/* Check if current account can afford to withdraw amount and if so, send those funds to the "TO" account */
		transfer_amount = string_hat_to_double(user_input);
		reset_user_input();
		if (main_bank_pointer->get_account(account_number_input).can_withdraw_funds(transfer_amount))
		{
			main_bank_pointer->get_account(account_number_input).withdraw_funds(transfer_amount);
			main_bank_pointer->get_account(transfer_to_account_num).deposit_funds(transfer_amount);
			change_state(TRANSFER_COMPLETION_STATE);
		}
		else
		{
			change_state(MENU_STATE);
			txtDisplay->Text = " Insufficient Funds.\r\n" + txtDisplay->Text;
		}
	}
	else
	{
		/* Every scenario where input is not required. Return to main menu. */
		reset_user_input();
		change_state(MENU_STATE);
	}
}

/*
  Backspace event listener. If the last index of the display string is not a whitespace or dollar sign then the last character
  of the display will be removed, along with the last character of the user_input string.
*/
void ATMForm::Backspace_Click(System::Object^ sender, System::EventArgs^ e) 
{
	if (user_input->EndsWith("."))
		numbers_after_decimal = -1;
	else
		numbers_after_decimal--;

	if (!txtDisplay->Text->EndsWith(" ") && !txtDisplay->Text->EndsWith("$"))
	{
		txtDisplay->Text = txtDisplay->Text->Remove(txtDisplay->Text->Length - 1);
		if (user_input->Length > 0)
			user_input = user_input->Remove(user_input->Length - 1);
	}
}

/*
  After checking if a decimal place is allowed, the even listener will display a decimal place along with adding one to 
  the end of the user_input string
*/
void ATMForm::Decimal_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (can_input_decimal())
	{
		numbers_after_decimal = 0;
		add_to_user_input(".");
		txtDisplay->Text += ".";
	}
}