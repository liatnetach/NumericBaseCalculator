#pragma once
#include <stdlib.h>

class Polynom : public CObject
{
public:
	DECLARE_SERIAL(Polynom)
	static CString lastFormula;
	Polynom();
	~Polynom();
	Polynom*& operator+(const Polynom* & num)
	{
		Polynom **result = new Polynom*;
		*result = this;
		Node * pOther = num->head;
		while (pOther)
		{
			(*result)->add(pOther->coef, pOther->degree);
			pOther = pOther->next;
		}
		return *result;
	}
	Polynom*& operator-(const Polynom* & num)
	{
		Polynom **result = new Polynom*;
		*result = this;
		Node * pOther = num->head;
		while (pOther)
		{
			(*result)->add(-1*pOther->coef,pOther->degree);
			pOther = pOther->next;
		}
		return *result;
	}
	Polynom*& operator*(const Polynom* & num)
	{
		Polynom **result = new Polynom*;
		*result = this;
		Node * temp = (*result)->head;
		Node * pOther = num->head;
		while (temp)
		{
			temp->coef*=(pOther->coef);
			temp->degree+=(pOther->degree);
			temp = temp->next;
		}
		return *result;
	}
	Polynom*& operator/(const Polynom* & num)
	{
		Polynom **result = new Polynom*;
		*result = this;
		Node * temp = (*result)->head;
		Node * pOther = num->head;
		while (temp)
		{
			temp->coef /= (pOther->coef);
			temp->degree -= (pOther->degree);
			temp = temp->next;
		}
		return *result;
	}
	int solution(int c,int d)
	{
		int res=(pow(c, d));
		return res;
	}
	void add(int c,int d)
	{
		Node *newNode = new Node;
		newNode->coef = c;
		newNode->degree = d;
		newNode->next = nullptr;
		if (head==nullptr) head =end= newNode;
		else end->next=newNode;
	}
	int input(CString str)
	{
		lastFormula = str;
		this->deletNodes();//delete the previous polynom nodes
		CString degS,coefS,op;
		int i = 0, opC = 0, coef, deg, degFlag, negF = 0, monCount=0;
		if (str[i] == '-')
		{
			negF = 1;
			i++;
		}
		while (str[i] != '\0')
		{
			monCount++;
			degFlag = 0;
			degS =coefS= "";
			if (negF)
			{
				coefS += '-';
				negF = 0;
			}
			deg =1;
			while (str[i] != '\0' && ((str[i] <= '9'&& str[i] >= '0') || (str[i] == '^')))
			{
				if (str[i] == '^') 
				{
					degFlag = 1;
					i++;
				}
				if (degFlag == 0) coefS += str[i++];
				else degS += str[i++];
			}
			if (str[i] != '\0')
			{
				op += str[i++];
				opC++;
			}
			coef = _ttoi(coefS);
			if (degFlag == 1) 
			{ 
				deg = _ttoi(degS); 
			}
			this->add(coef,deg);//adding the Monom to the Polynom
		}
		int result1,result = solution(head->coef, head->degree);
		Node * cur = head->next;
		i = 0;
		while (i<opC)
		{
			if (cur)
			{
				result1 = solution(cur->coef, cur->degree);
				if (op[i] == '+')result += result1;
				else if (op[i] == '-')result -= result1;
				else if (op[i] == '/')result /= result1;
				else if (op[i] == '*')result *= result1;
				cur = cur->next;
			}
			i++;
		}
		return result;
	}
	typedef struct node
	{
		int coef;
		int degree;
		struct node *next;
	} Node;
	Node *head,*end;
	Node* findEqual(int degree, Node*& prev) const
	{
		Node *ret = prev = nullptr;
		Node *p = head;
		if (!p)//head
			return ret;
		while (p && p->degree != degree) {
			ret = p;
			prev = ret;
			p = p->next;
		}
		if (!p) return ret;
		return p;
	}
	void deletNodes()
	{
		Node * temp = head;
		while (temp)
		{
			Node *q = temp;
			temp = temp->next;
			delete q;
		}
		head = nullptr;
	}
};
class Monom:public Polynom
{
	DECLARE_SERIAL(Monom)
public:
	Monom();
	~Monom();
	virtual CString print(CString str) { CString s; return s; }
	virtual CString baseToDec(CString str) { CString s; return s; }
	virtual CString decToBase(int decResult) { CString s; return s; }	
	virtual void Serialize(CArchive& ar) {}
	virtual CString decformTobaseform(CString decform)
	{
		CString baseF, newbaseFormula;
		long long int temp = 0;
		int i = 0; 
		while (decform[i] != '\0')
		{
			baseF = "";
			while (decform[i] != '\0' && (decform[i] >= '0'&&decform[i] <= '9'))baseF += decform[i++];
			temp = _ttoi(baseF);
			newbaseFormula += decToBase(temp);
			if (decform[i] != '\0')
			{
				newbaseFormula += decform[i];//adding the operator or ^
				i++;
			}
		}
		return newbaseFormula;//return the current formula in decimal
	}
protected:
};
class BinaryBase:public Monom
{
	DECLARE_SERIAL(BinaryBase)
public:
	BinaryBase();
	~BinaryBase();
	CString print(CString str)
	{
		int decResult=this->input(str);
		if (decResult < 0)
		{
			str = "unsigned numbers only";
			return str;
		}
		str = decToBase(decResult);
		return str;
	}
	CString baseToDec(CString str)
	{
		CString bin, newDecFormula;
		int i = 0;
		while (str[i] != '\0')
		{
			bin = "";
			while (str[i] != '\0' && str[i] >= '0'&&str[i] <= '1')bin += str[i++];
			newDecFormula += binaryToDecimal(bin);
			if (str[i] != '\0')
			{
				newDecFormula += str[i];//adding the operator
				i++;
			}
		}
		return newDecFormula;//return the current formula in decimal
	}
	CString binaryToDecimal(CString str)
	{
		int n = _ttoi(str);
		int num = n;
		int dec_value = 0;
		int base = 1;// Initializing base value to 1, i.e 2^0 
		int temp = num;
		while (temp) 
		{
			int last_digit = temp % 10;
			temp = temp / 10;
			dec_value += last_digit * base;
			base = base * 2;
		}
		str.Format(_T("%d"), dec_value);
		return str;
	}
	CString decToBase(int decResult)
	{
		// To store the binary number 
		unsigned long long int B_Number = 0;
		int cnt = 0;
		while (decResult != 0)
		{
			int rem = decResult % 2;
			unsigned long long int c = pow(10, cnt);
			B_Number += rem * c;
			decResult /= 2;
			// Count used to store exponent value 
			cnt++;
		}
		CString str = _T("");
		str.Format(_T("%llu"), B_Number);
		return str;
	}
	void Serialize(CArchive& ar)
	{
		CObject::Serialize(ar);
		CString temp;
		if (ar.IsStoring())
		{
			temp = decformTobaseform(lastFormula) + L"0";
			ar << temp;
		}
		else // Loading, not storing
		{
			ar >> lastFormula;
		}
	}
};
class OctalBase:public Monom
{
	DECLARE_SERIAL(OctalBase)
public:
	OctalBase();
	~OctalBase();
	CString print(CString str)
	{
		int decResult = this->input(str);
		if (decResult <= 0)
		{
			if (decResult == 0) str = "0";
			else str = "unsigned numbers only";
			return str;
		}
		str=decToBase(decResult);
		return str;
	}
	CString baseToDec(CString str)
	{
		CString oct, newDecFormula;
		int i = 0;
		while (str[i] != '\0')
		{
			oct = "";
			while (str[i] != '\0' && str[i] >= '0'&&str[i] <= '7')oct += str[i++];
			newDecFormula += octalToDecimal(oct);
			if (str[i] != '\0')
			{
				newDecFormula += str[i];//adding the operator
				i++;
			}
		}
		return newDecFormula;//return the current formula in decimal
	}
	CString octalToDecimal(CString str)
	{
		int n = _ttoi(str);
		int num = n;
		int dec_value = 0;
		int base = 1;// Initializing base value to 1, i.e 8^0
		int temp = num;
		while (temp) 
		{
			// Extracting last digit 
			int last_digit = temp % 10;
			temp = temp / 10;
			dec_value += last_digit * base;
			base = base * 8;
		}
		str.Format(_T("%d"), dec_value);
		return str;
	}
	CString decToBase(int decResult)
	{
		int octalNum[100];// array to store octal number 
		int i = 0;// counter for octal number array 
		while (decResult != 0)
		{
			octalNum[i] = decResult % 8;// storing remainder in octal array 
			decResult = decResult / 8;
			i++;
		}
		// copy the octal number array in reverse order to str 
		CString str = _T("");
		for (int j = i - 1; j >= 0; j--)
		{
			char c = (octalNum[j] + '0');
			str += c;
		}
		return str;
	}
	void Serialize(CArchive& ar)
	{
		CObject::Serialize(ar);
		CString temp;
		if (ar.IsStoring())
		{
			temp = decformTobaseform(lastFormula) + L"1";
			ar << temp;
		}
		else // Loading, not storing
		{
			ar >> lastFormula;
		}
	}
};
class DecimalBase:public Monom
{
	DECLARE_SERIAL(DecimalBase)
public:
	DecimalBase();
	~DecimalBase();
	CString print(CString str)
	{
		int decResult = this->input(str);
		str = decToBase(decResult);
		return str;
	}
	CString baseToDec(CString str)
	{
		return str;
	}
	CString decToBase(int decResult)
	{
		CString str = _T("");
		str.Format(_T("%d"), decResult);
		return str;
	}
	void Serialize(CArchive& ar)
	{
		CObject::Serialize(ar);
		CString temp;
		if (ar.IsStoring())
		{
			temp = decformTobaseform(lastFormula) + L"2";
			ar << temp;
		}
		else // Loading, not storing
		{
			ar >> lastFormula;
		}
	}
};
class HexadecimalBase :public Monom
{
	DECLARE_SERIAL(HexadecimalBase)

public:
	HexadecimalBase();
	~HexadecimalBase();
	CString print(CString str)
	{
		int decResult = this->input(str);
		if (decResult <= 0)
		{
			if (decResult == 0) str = "0";
			else str = "unsigned numbers only";
			return str;
		}
		str=decToBase(decResult);
		return str;
	}
	CString baseToDec(CString str)
	{
		CString hex,newDecFormula;
		int i = 0;
		while (str[i] != '\0')
		{
			hex = "";
			while (str[i] != '\0'&&((str[i] >= '0'&&str[i] <= '9')||(str[i] >= 'A'&&str[i] <= 'F')))hex += str[i++];
			newDecFormula += hexadecimalToDecimal(hex);
			if (str[i] != '\0')
			{
				newDecFormula += str[i];//adding the operator or ^
				i++;
			}
		}
		return newDecFormula;//return the current formula in decimal
	}
	CString hexadecimalToDecimal(CString hexVal)
	{
		int len = hexVal.GetLength();
		int base = 1;// Initializing base value to 1, i.e 16^0
		int dec_val = 0;
		for (int i = len - 1; i >= 0; i--)// Extracting characters as digits from last character 
		{
			if (hexVal[i] >= '0' && hexVal[i] <= '9')// if character lies in '0'-'9'
			{
				dec_val += (hexVal[i] - 48)*base;
				base = base * 16;// incrementing base by power
			}
			else if (hexVal[i] >= 'A' && hexVal[i] <= 'F')// if character lies in 'A'-'F'
			{
				dec_val += (hexVal[i] - 55)*base;
				base = base * 16;// incrementing base by power 
			}
		}
		hexVal.Format(_T("%d"), dec_val);//converting the decimal num to CString
		return hexVal;
	}
	CString decToBase(int decResult)
	{
		char hexaDeciNum[100];// char array to store hexadecimal number 
		int i = 0;// counter for hexadecimal number array 
		while (decResult != 0)
		{
			int temp = 0;// temporary variable to store remainder 
			temp = decResult % 16;// storing remainder in temp variable. 
			if (temp < 10)// check if temp < 10
			{
				hexaDeciNum[i] = temp + 48;//48 is '0'
				i++;
			}
			else
			{

				hexaDeciNum[i] = temp + 55;//55 is '7'
				i++;
			}
			decResult = decResult / 16;
		}
		// copy the hexadecimal number array in reverse order to str 
		CString str = _T("");
		for (int j = i - 1; j >= 0; j--)
		{
			str += hexaDeciNum[j];
		}
		return str;
	}
	void Serialize(CArchive& ar)
	{
		CObject::Serialize(ar);
		CString temp;
		if (ar.IsStoring())
		{
			temp = decformTobaseform(lastFormula) + L"3";
			ar << temp;
		}
		else // Loading, not storing
		{
			ar >> lastFormula;
		}
	}
};
