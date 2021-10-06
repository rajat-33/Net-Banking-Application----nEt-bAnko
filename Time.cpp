// C++ program to find Current Day, Date
// and Local Time
#include<iostream>
#include<ctime>
using namespace std;
int main()
{
	// Declaring argument for time()
	time_t tt;

	// Declaring variable to store return value of
	// localtime()
	struct tm * ti;

	// Applying time()
	time (&tt);

	// Using localtime()
	ti = localtime(&tt);
	string s = asctime(ti);
	string date, time;
	for(int i = 0;i<10;i++)
	{
		date.push_back(s[i]);
	}
	for(int i = 11;i<19;i++)
	{
		time.push_back(s[i]);
	}
	cout << "Current Day, Date and Time is = "
		<< date << " " << time;

return 0;
}
