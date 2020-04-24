#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

void removeleadingzeroes(string& s) {
	while (s.length() > 1 && s[0] == '0') s = s.substr(1);
}

string add(string a, string b) {
	removeleadingzeroes(a);
	removeleadingzeroes(b);
	while (a.length() < b.length()) a = "0" + a;
	while (b.length() < a.length()) b = "0" + b;
	a = "0" + a;
	b = "0" + b;
	string sum = "";
	int carry = 0;
	for (int i = a.length() - 1; i >= 0; i--) {
		int s = (a[i] - '0') + (b[i] - '0') + carry;
		carry = s / 10;
		sum = ((char)(s % 10 + '0')) + sum;
	}
	removeleadingzeroes(sum);
	return sum;
}

string sub(string a, string b) {

	removeleadingzeroes(a);
	removeleadingzeroes(b);
	while (b.length() < a.length()) b = "0" + b;
	for (int i = 0; i < b.length(); i++)
		b[i] = 9 - (b[i] - '0') + '0';
	string diff = add(add(a, b), "1").substr(1);
	removeleadingzeroes(diff);
	return diff;
}

string mult(string a, string b) {
	removeleadingzeroes(a);
	removeleadingzeroes(b);
	string sum = "0";
	for (int i = 0; i < a.length(); i++)
		for (int j = 0; j < b.length(); j++) {
			string prod = to_string((a[i] - '0') * (b[j] - '0'));
			for (int k = 0; k < a.length() - i - 1 + b.length() - j - 1; k++)
				prod += "0";
			sum = add(sum, prod);
		}
	return sum;
}

/*	
	returns length of string by iterating through
	each character in string and keeping a count	
*/
string strLength(string x) {
	string ans = "0";
	for (int i = 0; i < x.length(); i++) {
		if (x[i] != -1) {
			ans = add(ans, "1");
		}
	}
	return ans;
}

/*
	compares if a string is numerically less than another
	string. Only uses string manipulation if the strings 
	lengths are the same. 
*/
bool cmpIfLess(string one, string two) {
	if (one.length() == two.length()) {
		for (int i = 0; i < one.length(); i++) {
			int x = one[i] - '0';
			int y = two[i] - '0';
			if(x < y) {
				return true;
			}
			
		}
		return false;
	}
	else {
		return(one.length() < two.length());
	}
}

/*
	compares if two strings are the same by looping
	through each string simultaneosuly and checking if 
	each character at the same position of each 
	string are the same
*/
bool cmpIfSame(string beg, string ans) {
	for (int i = 0; i < ans.length(); i++) {
		if (beg[i] != ans[i]) {
			return false;
		}
	}
	return true;
}

/*
	appends the necessary amount of zeroes to the 
	original number using a basic while loop and count
	technique
*/
string addEndZeros(string num1, string ans) {
	string beg = "0";
	while(true){
		if (cmpIfSame(beg, ans)) {
			break;
		}
		else {
			num1 += "0";
		}
		beg = add(beg, "1");
	}
	return num1;
}

/*
	professors algorithm he gave us to for finding
	cubic roots. Could probably condense, but did it
	this way for now to ensure accuracy.
*/
string algorithm(string ans) {
	string store = ans;
	ans = mult(ans, ans);
	ans = mult(ans, "12");
	string newans = mult(store, "6");
	newans = add(newans, "1");
	string finalans = add(ans, newans);
	return finalans;
}

//method that calls all submethods to perform cubic root calculation
string calculate(string num1, string num2) {
	string three = "3";							//takes number of decimal places you want, multiplies	
	string newnum1 = num1;
	string zeros = mult(num2, three);			//by three, and appends that many zeros onto main number
	num1 = addEndZeros(num1, zeros);

	cout << num1 << endl;
	if (newnum1 == "0") {
		string comp = "0";
		string endanswer = "";
		string strnew = "";
		int l;
		if (num2 != "0") {
			newnum1 = newnum1 + ".";
			while (!cmpIfSame(comp, num2)) {
				strnew = strnew + "0";
				comp = add(comp, "1");
			}
			return newnum1 + strnew;
		}
		return "0";
		
	}
	else {

		string arrLen = mult(strLength(num1), three);	//multiply by three to get correct length to make table
														//table of 8's

		int x = stoi(arrLen);						//convert to int
		string* table8 = new string[x];				//dynamicaly allocate table of 8's
		string start = "1";
		int cnt = 1;
		table8[0] = "1";
		bool isLess = true;

		while (isLess) {								//add all correct elements to table of 8's
			start = mult(start, "8");				//keep multiplying by 8 until number is larger than
			if (cmpIfLess(start, num1)) {			// than original number, but dont use the last number  
				table8[cnt] = start;
				cnt++;
			}
			else {
				isLess = false;
			}
		}

		string ans = "0";
		string prodOf8 = "0";
		string finalAns = "0";
		string finalRem = "0";
		string algAns;

		for (int i = cnt - 1; i >= 0; i--) {			//this is the for loop for the method we learned in class
			algAns = algorithm(ans);				//on how to calculate the table of 8's using the 
			prodOf8 = mult(table8[i], algAns);		//special algorithm
			if (cmpIfLess(prodOf8, num1)) {
				num1 = sub(num1, prodOf8);
				ans = add(ans, ans);
				ans = add(ans, "1");
			}
			else if (cmpIfSame(prodOf8, num1)) {
				num1 = sub(prodOf8, num1);
				ans = add(ans, ans);
				ans = add(ans, "1");
			}
			else {
				ans = add(ans, ans);
			}
		}

		int i;
		string cmp = "0";
		string newstring = "";
		string endans = "";

		//this loop splits the final answer in the right spot
		//to insert the decimal place
		for (i = ans.length() - 1; i >= 0; i--) {
			if (cmpIfSame(cmp, num2)) {
				endans = ans[i] + endans;
			}
			else {
				newstring = ans[i] + newstring;
				cmp = add(cmp, "1");
			}

		}

		//inserts the decimal place and appends the
		//two strings back together.
		endans = endans + ".";
		string finalanswer = endans + newstring;
		return finalanswer;
	}
}


int main() {
	string num1;
	string num2;
	cout << "Choose first number" << endl;
	getline(cin, num1); 
	cout << "Choose second number" << endl;
	getline(cin, num2);
	string ans = calculate(num1, num2);
	cout << ans << endl;

}
