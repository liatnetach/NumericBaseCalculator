#include "pch.h"
#include "Polynom.h"
#include <iostream>
using namespace std;
IMPLEMENT_SERIAL(Polynom, CObject, 1)
IMPLEMENT_SERIAL(Monom, CObject, 1)
IMPLEMENT_SERIAL(BinaryBase, CObject, 1)
IMPLEMENT_SERIAL(OctalBase, CObject, 1)
IMPLEMENT_SERIAL(DecimalBase, CObject, 1)
IMPLEMENT_SERIAL(HexadecimalBase, CObject, 1)

CString Polynom::lastFormula = L"";
Polynom::Polynom()
{
	end=head = nullptr;
}

Polynom::~Polynom()
{
	Node *p = head;
	while (p)
	{
		Node *q = p;
		p = p->next;
		delete q;
	}
}

Monom::Monom(){}
Monom::~Monom(){}

BinaryBase::BinaryBase() {}
BinaryBase::~BinaryBase() {}

OctalBase::OctalBase() {}
OctalBase::~OctalBase() {}

DecimalBase::DecimalBase() {}
DecimalBase::~DecimalBase() {}

HexadecimalBase::HexadecimalBase() {}
HexadecimalBase::~HexadecimalBase() {}