

#include <gtest/gtest.h>

struct BankAccount
{
	int balance = 0;

	BankAccount()
	{
	}

	explicit BankAccount(const int balance)
	: balance{balance}
	{
	}

	void deposit(int amount)
	{
		balance += amount;
	}

	bool withdraw(int amount)
	{
		if (amount <= balance)
		{
			balance -= amount;
			return true;
		}
		return false;
	}
};

struct BankAccountTest : testing::Test
{
	BankAccount* account;

	BankAccountTest()
	{
		account = new BankAccount;
	}

	virtual ~BankAccountTest()
	{
		delete account;
	}
};

TEST_F(BankAccountTest, BankAccountStarsEmpty)
{
	EXPECT_EQ(0, account->balance);
}

TEST_F(BankAccountTest, CanDepositMoney)
{
	account->deposit(100);
	EXPECT_EQ(100, account->balance);
}

struct account_state
{
	int initial_balance;
	int withdraw_amount;
	int final_balance;
	bool success;

// Readable and Nice GetParam error.
	friend std::ostream& operator<<(std::ostream& os, const account_state& obj)
	{
		return os
				<< "initial_balance: " << obj.initial_balance
				<< " withdraw_amount: " << obj.withdraw_amount
				<< " final_balance: " << obj.final_balance
				<< " success: " << obj.success;
	}
};

struct withdrawAccountTest : BankAccountTest, testing::WithParamInterface<account_state>
{
	withdrawAccountTest()
		{
			account->balance = GetParam().initial_balance;
		}
};

TEST_P(withdrawAccountTest, FinalBalance)
{
	auto as = GetParam();
	auto success = account->withdraw(as.withdraw_amount);
	EXPECT_EQ(as.final_balance, account->balance);
	EXPECT_EQ(as.success, success);

}

INSTANTIATE_TEST_CASE_P(Default, withdrawAccountTest,
		testing::Values(
				account_state{100,50,50,true},
				account_state{100,200,100,true} //Error: true
		));

int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
