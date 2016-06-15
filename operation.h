#ifndef OPERATION_H_INCLUDED
#define OPERATION_H_INCLUDED

#include "Course.h"
#include "Score.h"
#include "Student.h"
#include <vector>
#include <fstream>
#include <cstdlib>
#include <cstdio>

using namespace std;

class Operation{
private:
	vector<Course> cvec;	//�γ��б�
	vector<Student> svec;	//ѧ���б�
	vector<Score> scvec;	//�ɼ��б�

public:
	Operation();
	~Operation() {}

	//������
	void Search_stu(string sno);    //��ѯѧ����Ϣ
    void add();
    void update();
    void del();
    void save();

    //��ѯ����
	void Search_sno(string sno);    //��ѧ�Ų�ѯѧ���ɼ���ѧ����Ϣ
	void Search_cno(string cno);    //���γ̲�ѯĳ�ſγ̵�����ѧ���ɼ�

	//ͳ�ƹ���
	void Stat1();   //���γ�ͳ�Ʋ�����ѧ��
	void Stat2();   //���γ̽�ĳ�ſεĳɼ�����
	void Stat3();   //�����пγ̵��ܷ�����
};

#endif // OPERATION_H_INCLUDED
