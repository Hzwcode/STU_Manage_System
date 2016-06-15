#ifndef STUDENT_H_INCLUDED
#define STUDENT_H_INCLUDED

#include <iostream>
#include <string>

using namespace std;

enum Gender{
	MALE, FEMALE
};

class Student{
public:
	string sno;		//ѧ��
	string sname;	//����
	Gender ssex;	//�Ա�
	int sage;		//����

	float credit;
	float score;

	Student(string _sno, string _sname, Gender _ssex, int _sage)
	:sno(_sno),
	 sname(_sname),
	 ssex(_ssex),
	 sage(_sage)
	{
        credit = 0;
        score = 0;
	}
};

#endif // STUDENT_H_INCLUDED
