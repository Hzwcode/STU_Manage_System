#include "operation.h"
#include <cstring>
#include <algorithm>

Operation::Operation(){
    /***�γ��б��ʼ��***/
    ifstream fin;
    fin.open("Course.txt", ios::in);
    string cno, cname;
    float ccredit;
    while(!fin.eof()){
        fin >> cno >> cname >> ccredit;
        Course course(cno, cname, ccredit);
        cvec.push_back(course);
    }
    fin.close();
    /*��ʼ��ѧ����Ϣ��ѡ�γɼ���Ϣ*/
    fin.open("Student.txt", ios::in);
    while(!fin.eof()){
        string sno, sname;
        string sex;
        Gender ssex;
        int sage, n;
        fin >> sno >> sname >> sex >> sage >> n;
        ssex = (sex == "��") ? MALE : FEMALE;
        Student stu(sno, sname, ssex, sage);
        string cno;
        float cscore;
        for(int i = 0; i < n; i++){
            fin >> cno >> cscore;
            stu.score += cscore;
            vector<Course>::iterator it;
            for(it = cvec.begin(); it != cvec.end(); it++){
                if(it->cno == cno){
                    stu.credit += it->ccredit;
                    Score score(*it, stu, cscore);
                    scvec.push_back(score);
                    break;
                }
            }
        }
        if(sno.length() == 0 || sname.length() == 0) continue;
        svec.push_back(stu);
    }
    fin.close();
}

void Operation::Search_stu(string sno){
    int find = 0;
    vector<Student>::iterator it;
    for(it = svec.begin(); it != svec.end(); it++){
        if(it->sno == sno){
            find = 1;
            printf("\t����������������������������\n");
            printf("\t��         ��ѯ���       ��\n");
            printf("\t����������������������������\n");
            printf("\t��ѧ��:%15s\t  ��\n",it->sno.c_str());
            printf("\t������:%15s\t  ��\n",it->sname.c_str());
            if(it->ssex == MALE)
                printf("\t���Ա�:%15s\t  ��\n","��");
            else
                printf("\t���Ա�:%15s\t  ��\n","Ů");
            printf("\t������:%15d\t  ��\n",it->sage);
            printf("\t����ѧ��:%13.1f\t  ��\n",it->credit);
            printf("\t���ܳɼ�:%13.2f\t  ��\n",it->score);
            printf("\t����������������������������\n");
        }
    }
    if(find == 0)
        printf("δ���������ѧ����Ϣ��\n");
}

void Operation::add()
{
    string sno, sname, sex;
    Gender ssex;
    int sage;
    cout << "������ѧ�������Ϣ:" << endl;
    cout << "ѧ��:"; cin >> sno;
    vector<Student>::iterator it1;
    for(it1 = svec.begin(); it1 != svec.end(); it1++){
        if(it1->sno == sno){
            cout << "��ѧ����Ϣ�Ѵ���,�����ԣ�" << endl;
            return ;
        }
    }
    cout << "����:"; cin >> sname;
    cout << "�Ա�[��/Ů]:"; cin >> sex;
    if(sex == "��")
        ssex = MALE;
    else if(sex == "Ů")
        ssex = FEMALE;
    else{
        cout << "Input Error!!!" << endl;
        return ;
    }
    cout << "����:"; cin >> sage;
    Student stu(sno, sname, ssex, sage);
    char ch1;
    while(1){
        cout << "�Ƿ��������ɼ�[y/n]��";
        cin >> ch1;
        getchar();
        if(ch1 == 'Y' || ch1 == 'y'){
            char ch2;
            vector< pair<string,float> > sc;
            string cno;
            float score;
            while(1){
                cout << "������γ̺�: "; cin >> cno;
                cout << "������ɼ�: "; cin >> score;

                int flag = 0;
                vector<Course>::iterator it;
                for(it = cvec.begin(); it != cvec.end(); it++){
                    if(it->cno == cno){
                        flag = 1;
                        break;
                    }
                }
                if(flag != 1){
                    cout << "���������ſγ̣����������룡" << endl;
                    cout << "�Ƿ��������ɼ�[y/n]��";
                    cin >> ch2;
                    if(ch2 == 'Y' || ch2 == 'y')
                        break;
                    else
                       continue;
                }

                sc.push_back(pair<string, float> (cno,score));
                while(1){
                    cout << "�Ƿ��������ɼ�[y/n]��";
                    cin >> ch2; getchar();
                    if(ch2 == 'Y' || ch2 == 'y'){
                        break;
                    }
                    else if(ch2 == 'N' || ch2 == 'n'){
                        break;
                    }
                    else{
                        cout << "���벻��ȷ��������ѡ��" << endl;
                    }
                }
                if(ch2 == 'N' || ch2 == 'n') break;
            }
            //������Ϣ,break
            for(unsigned i = 0; i < sc.size(); i++){
                //fin >> cno >> cscore;
                stu.score += sc[i].second;
                vector<Course>::iterator it;
                for(it = cvec.begin(); it != cvec.end(); it++){
                    if(it->cno == sc[i].first){
                        stu.credit += it->ccredit;
                        Score score(*it, stu, sc[i].second);
                        scvec.push_back(score);
                        break;
                    }
                }
            }
            svec.push_back(stu);
            break;
        }
        else if(ch1 == 'N' || ch1 == 'n'){
            svec.push_back(stu);
            break;
        }
        else{
            cout << "���벻��ȷ��������ѡ��" << endl;
        }
    }
    printf("����ɹ�!\n");
}

void Operation::update()
{
    string sno;
    cout << "��������޸�ѧ��ѧ�ţ�"; cin >> sno;
    //��ӡԭʼ��Ϣ
    cout << endl << "��ѧ��ԭʼ��Ϣ���£�" << endl;
    vector<Student>::iterator it1;
    for(it1 = svec.begin(); it1 != svec.end(); it1++){
        if(it1->sno == sno){
            printf("ѧ�ţ�%s  ������%s  ", it1->sno.c_str(), it1->sname.c_str());
            if(it1->ssex == MALE)
                printf("�Ա���  ���䣺%d\n", it1->sage);
            else
                printf("�Ա�Ů  ���䣺%d\n", it1->sage);
            break;
        }
    }
    if(it1 == svec.end()){
        cout << "��ѧ�������ڣ������ԣ�" << endl;
        return ;
    }
    vector<Score>::iterator it2;
    for(it2 = scvec.begin(); it2 != scvec.end(); it2++){
        if(it2->student.sno == sno){
            cout << it2->course.cno << " " << it2->course.cname << " " << it2->score << endl;
        }
    }
    //����¼������Ϣ
    int cmd;
    cout << "---------------�޸�ѡ��------------" << endl;
    cout << "        1.�޸�ѧ��������Ϣ" <<endl;
    cout << "        2.�޸�ѧ���ɼ���Ϣ" <<endl;
    cout << "        3.����" <<endl;
    cout << "-----------------------------------" << endl;
    cout << "Please input your option[1-3]: ";
    cin >> cmd;
    if(cmd == 1){
        cout << "�����������ѧ��������Ϣ:" << endl;
        string sname, sex;
        Gender ssex;
        int sage;
        cout << "����:"; cin >> sname;
        cout << "�Ա�[��/Ů]:"; cin >> sex;
        if(sex == "��")
            ssex = MALE;
        else if(sex == "Ů")
            ssex = FEMALE;
        else{
            cout << "Input Error!!!" << endl;
            return ;
        }
        cout << "����:"; cin >> sage;
        //Student stu(sno, sname, ssex, sage);
        vector<Student>::iterator it3;
        for(it3 = svec.begin(); it3 != svec.end(); it3++){
            if(it3->sno == sno){
                it3->sname = sname;
                it3->ssex = ssex;
                it3->sage = sage;
                break;
            }
        }
        vector<Score>::iterator it4;
        for(it4 = scvec.begin(); it4 != scvec.end(); it4++){
            if(it4->student.sno == sno){
                it4->student.sname = sname;
                it4->student.ssex = ssex;
                it4->student.sage = sage;
            }
        }
        cout << "�޸ĳɹ�!" << endl;
    }
    else if(cmd == 2){
        cout << "�����������ѧ���ɼ���Ϣ[���б䶯]:" << endl;
        string cno;
        float score;
        vector< pair<string,float> > sc;
        while(1){
            cout << "������γ̺�: "; cin >> cno;
            cout << "������ɼ�: "; cin >> score;

            int flag = 0;
            char ch2;
            vector<Course>::iterator it;
            for(it = cvec.begin(); it != cvec.end(); it++){
                if(it->cno == cno){
                    flag = 1;
                    break;
                }
            }
            if(flag != 1){
                cout << "���������ſγ̣����������룡" << endl;
                cout << "�Ƿ��������ɼ�[y/n]��";
                cin >> ch2;
                if(ch2 == 'Y' || ch2 == 'y')
                    break;
                else
                   continue;
            }

            sc.push_back(pair<string, float> (cno,score));
            while(1){
                cout << "�Ƿ��������ɼ�[y/n]��";
                cin >> ch2; getchar();
                if(ch2 == 'Y' || ch2 == 'y'){
                    break;
                }
                else if(ch2 == 'N' || ch2 == 'n'){
                    break;
                }
                else{
                    cout << "���벻��ȷ��������ѡ��" << endl;
                }
            }
            if(ch2 == 'N' || ch2 == 'n') break;
        }

        for(unsigned i = 0; i < sc.size(); i++){
            int find = 0;
            vector<Score>::iterator it;
            for(it = scvec.begin(); it != scvec.end(); it++){
                if(it->student.sno == sno && it->course.cno == sc[i].first){
                    find = 1;
                    float lep = sc[i].second - it->score;
                    it->score = sc[i].second;
                    //�޸��ܳɼ�
                    vector<Student>::iterator it2;
                    for(it2 = svec.begin(); it2 != svec.end(); it2++){
                        if(it2->sno == sno){
                            it2->score += lep;
                        }
                    }
                    break;
                }
            }
            if(find != 1){
                vector<Student>::iterator it1;
                for(it1 = svec.begin(); it1 != svec.end(); it1++){
                    if(it1->sno == sno){
                        vector<Course>::iterator it2;
                        for(it2 = cvec.begin(); it2 != cvec.end(); it2++){
                            if(it2->cno == sc[i].first){
                                it1->credit += it2->ccredit;
                                it1->score += sc[i].second;
                                Score score(*it2, *it1, sc[i].second);
                                scvec.push_back(score);
                                break;
                            }
                        }
                    }
                }
            }
        }
        cout << "�޸ĳɹ�!" << endl;
    }
    else if(cmd == 3){}
    else{
        cout << "doesn't have the choice!!!" << endl;
    }
}

void Operation::del()
{
    string sno;
    cout << "�������ɾ��ѧ��ѧ�ţ�"; cin >> sno;
    //��ӡԭʼ��Ϣ
    cout << endl << "��ѧ��ԭʼ��Ϣ���£�" << endl;
    vector<Student>::iterator it1;
    for(it1 = svec.begin(); it1 != svec.end(); it1++){
        if(it1->sno == sno){
            printf("ѧ�ţ�%s  ������%s  ", it1->sno.c_str(), it1->sname.c_str());
            if(it1->ssex == MALE)
                printf("�Ա���  ���䣺%d\n", it1->sage);
            else
                printf("�Ա�Ů  ���䣺%d\n", it1->sage);
            break;
        }
    }
    if(it1 == svec.end()){
        cout << "��ѧ�������ڣ������ԣ�" << endl;
        return ;
    }
    vector<Score>::iterator it2;
    for(it2 = scvec.begin(); it2 != scvec.end(); it2++){
        if(it2->student.sno == sno){
            cout << it2->course.cno << " " << it2->course.cname << " " << it2->score << endl;
        }
    }

    int cmd;
    cout << "---------------ɾ��ѡ��------------" << endl;
    cout << "        1. ɾ��ѧ��������Ϣ" <<endl;
    cout << "        2. ɾ��ѧ���ɼ���Ϣ" <<endl;
    cout << "        3. ����" <<endl;
    cout << "-----------------------------------" << endl;
    cout << "Please input your option[1-3]: ";
    cin >> cmd;
    switch(cmd){
        case 1:{
            char ch;
            while(1){
                cout << "ȷ��ɾ������������Ϣ[y/n]����"; cin >> ch; getchar();
                if(ch == 'Y' || ch == 'y'){
                    vector<Student>::iterator it1;
                    for(it1 = svec.begin(); it1 != svec.end(); ){
                        if(it1->sno == sno){
                            it1 = svec.erase(it1);
                        }
                        else
                            ++it1;
                    }
                    vector<Score>::iterator it2;
                    for(it2 = scvec.begin(); it2 != scvec.end(); ){
                        if(it2->student.sno == sno){
                            it2 = scvec.erase(it2);
                        }
                        else
                            ++it2;
                    }
                    cout << "ɾ���ɹ���" << endl;
                    break;
                }
                else if(ch == 'N' || ch == 'n'){
                    cout << "�ɹ�����ɾ����" << endl;
                    break;
                }
                else{
                    cout << "��������������ѡ��" << endl;
                }
            }
            break;}
        case 2:{
            string cno;
            while(1){
                cout << "������Ҫɾ���Ŀγ̺ţ�" ; cin >> cno;
                vector<Score>::iterator it1;
                int find = 0;
                for(it1 = scvec.begin(); it1 != scvec.end(); ){
                    if(it1->student.sno == sno && it1->course.cno == cno){
                        find = 1;
                        vector<Student>::iterator it2;
                        for(it2 = svec.begin(); it2 != svec.end(); it2++){
                            if(it2->sno == sno){
                                //�ҵ����ٵ�ѧ��
                                float credit;
                                vector<Course>::iterator it3;
                                for(it3 = cvec.begin(); it3 != cvec.end(); it3++){
                                    if(it3->cno == cno){
                                        credit = it3->ccredit;
                                        break;
                                    }
                                }
                                it2->score -= it1->score; //���ٵķ���
                                it2->credit -= credit;    //���ٵ�ѧ��
                                break;
                            }
                        }
                        it1 = scvec.erase(it1);
                        break;
                    }
                    else
                        ++it1;
                }
                char ch;
                if(find != 1){
                    cout << "����û��ѡ�޹����ſΣ�ɾ��ʧ�ܣ�" << endl;
                    while(1){
                        cout << "�Ƿ����ɾ������[y/n]����"; cin >> ch;
                        if(ch == 'Y' || ch == 'y')
                            break;
                        else if(ch == 'N' || ch == 'n')
                            break;
                        else
                            cout << "������������������'y'��'n'��" << endl;
                    }
                    if(ch == 'N' || ch == 'n') break;
                    if(ch == 'Y' || ch == 'y') continue;
                }
                cout << "ɾ���ɹ���" << endl;
                while(1){
                    cout << "�Ƿ����ɾ�������γ̳ɼ�[y/n]����"; cin >> ch;
                    if(ch == 'Y' || ch == 'y'){
                        break;
                    }
                    else if(ch == 'N' || ch == 'n'){
                        break;
                    }
                    else{
                        cout << "������������������'y'��'n'��" << endl;
                    }
                }
                if(ch == 'N' || ch == 'n') break;
            }
            //cout << "ɾ���ɹ���" << endl;
            break;}
        case 3:
            break;
        default:
            cout << "doesn't have the choice!!!" << endl;
    }
}

void Operation::Search_sno(string sno){
    int find = 0;
    printf("\n%22s����ѯ�����\n"," ");
    vector<Student>::iterator it1;
    for(it1 = svec.begin(); it1 != svec.end(); it1++){
        if(it1->sno == sno){
            printf("  ѧ�ţ�%s\t������%s\t��ѧ�֣�%.1f\n", it1->sno.c_str(), it1->sname.c_str(), it1->credit);
            break;
        }
    }
    printf("����������������������������������������������������������\n");
    printf("��  �γ̺�  ��         �γ���         ��  �ɼ�  �� ѧ�� ��\n");
    printf("����������������������������������������������������������\n");
    vector<Score>::iterator it2;
    for(it2 = scvec.begin(); it2 != scvec.end(); it2++){
        if(it2->student.sno == sno){
            find = 1;
            printf("��  %-8s�� %-22s �� %-7.2f�� %-5.1f��\n",it2->course.cno.c_str(),it2->course.cname.c_str(),it2->score,it2->course.ccredit);
        }
    }
    if(find==0)
        printf("��%18sδ�����������Ϣ��%18s��\n"," "," ");
    printf("����������������������������������������������������������\n");
}

void Operation::Search_cno(string cno){
    int find = 0;
    printf("\n%24s����ѯ�����\n"," ");
    vector<Course>::iterator it1;
    for(it1 = cvec.begin(); it1 != cvec.end(); it1++){
        if(it1->cno == cno){
            printf("  �γ̺ţ�%s  �γ�����%s  ѧ�֣�%.1f\n", it1->cno.c_str(), it1->cname.c_str(), it1->ccredit);
            break;
        }
    }
    printf("����������������������������������������������������������\n");
    printf("��       ѧ��       ��       ����       ��     �ɼ�     ��\n");
    printf("����������������������������������������������������������\n");
    vector<Score>::iterator it2;
    for(it2 = scvec.begin(); it2 != scvec.end(); it2++){
        if(it2->course.cno == cno){
            find = 1;
            printf("��    %-14s��      %-11s ��    %-10.2f��\n",it2->student.sno.c_str(),it2->student.sname.c_str(),it2->score);
        }
    }
    if(find==0)
        printf("��%18sδ�����������Ϣ��%18s��\n"," "," ");
    printf("����������������������������������������������������������\n");
}

void Operation::Stat1(){
    int find = 0;
    printf("\n%24s��ͳ�ƽ����\n"," ");
    printf("����������������������������������������������������������\n");
    printf("��           �γ�           ��     ѧ��     ��   �ɼ�   ��\n");
    printf("����������������������������������������������������������\n");
    vector<Score>::iterator it2;
    for(it2 = scvec.begin(); it2 != scvec.end(); it2++){
        if(it2->score < 60){
            find = 1;
            printf("��  %-24s��    %-9s ��  %-8.2f��\n",it2->course.cname.c_str(),it2->student.sname.c_str(),it2->score);
        }
    }
    if(find==0)
        printf("��%18sδ�����������Ϣ��%18s��\n"," "," ");
    printf("����������������������������������������������������������\n");
}

bool compare2(Score i,Score j)
{
    if(!(i.course.cno == j.course.cno))
        return (i.course.cno < j.course.cno);
    return (i.score < j.score);
}

void Operation::Stat2(){
    int find = 0;
    printf("\n%24s��ͳ�ƽ����\n"," ");
    printf("����������������������������������������������������������\n");
    printf("��           �γ�           ��     ѧ��     ��   �ɼ�   ��\n");
    printf("����������������������������������������������������������\n");
    stable_sort(scvec.begin(), scvec.end(), compare2);

    vector<Score>::iterator it2;
    for(it2 = scvec.begin(); it2 != scvec.end(); it2++){
        find = 1;
        printf("��  %-24s��    %-9s ��  %-8.2f��\n",it2->course.cname.c_str(),it2->student.sname.c_str(),it2->score);
    }
    if(find==0)
        printf("��%18sδ�����������Ϣ��%18s��\n"," "," ");
    printf("����������������������������������������������������������\n");
}

bool compare3(Student i,Student j)
{
    return (i.credit < j.credit);
}

void Operation::Stat3(){
    int find = 0;
    printf("\n%24s��ͳ�ƽ����\n"," ");
    printf("����������������������������������������������������������\n");
    printf("��     ѧ��     ��    ����   ��   ��ѧ��   ��  �ܳɼ�   ��\n");
    printf("����������������������������������������������������������\n");

    stable_sort(svec.begin(), svec.end(), compare3);
    vector<Student>::iterator it2;
    for(it2 = svec.begin(); it2 != svec.end(); it2++){
        find = 1;
        printf("��  %-12s��  %-8s ��    %-8.1f��  %-9.2f��\n",it2->sno.c_str(),it2->sname.c_str(),it2->credit,it2->score);
    }
    if(find==0)
        printf("��%18sδ�����������Ϣ��%18s��\n"," "," ");
    printf("����������������������������������������������������������\n");
}

void Operation::save()
{
    ofstream fout;
    fout.open("Student.txt", ios::out);
    if(!fout){
        cout << "�����ļ�ʧ��" << endl;
        return ;
    }
    //fout << "hhh" << endl;

    vector<Student>::iterator it1;
    for(it1 = svec.begin(); it1 != svec.end(); it1++){
            //cout << "1111" << endl;
            fout << it1->sno << " " << it1->sname << " ";
            //cout << it1->sno << " " << it1->sname << " ";
            if(it1->ssex == MALE){
                fout << "�� " << it1->sage << " ";
                //cout << "�� " << it1->sage << " ";
            }
            else{
                fout << "Ů " << it1->sage << " ";
                //cout << "Ů " << it1->sage << " ";
            }
            vector<Score>::iterator it2;
            int n = 0;
            for(it2 = scvec.begin(); it2 != scvec.end(); it2++){
                if(it2->student.sno == it1->sno) ++n;
            }
            fout << n << endl;
            //cout << n << endl;
            vector<Score>::iterator it3;
            for(it3 = scvec.begin(); it3 != scvec.end(); it3++){
                if(it3->student.sno == it1->sno){
                    fout << it3->course.cno << " " << it3->score << endl;
                    //cout << it3->course.cno << " " << it3->score << endl;
                }
            }
    }
}


