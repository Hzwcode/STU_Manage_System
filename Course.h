#ifndef COURSE_H_INCLUDED
#define COURSE_H_INCLUDED

#include <iostream>
#include <string>

using namespace std;

class Course{
public:
	string cno;		//�γ̺�
	string cname;	//�γ���
	float ccredit;	//ѧ��

	Course(string _cno, string _cname, float _ccredit)
	:cno(_cno),
	 cname(_cname),
	 ccredit(_ccredit)
	{}
};

#endif // COURSE_H_INCLUDED
