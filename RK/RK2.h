#include <iostream>
#include <string.h>
#include <vector>

class Student
{
public:
	int age, stepuha, intense; //intense - интенсивность учебы
	std::string name;
	void leave()
	{
		
	}
	int rightRk()
	{
		intense += 100500;
		int mark = rand() % 1000;
		return mark;
	}
} badstudent;

class Decan
{
	protected:
		int age, salary;
		std::string name;
	public:
		Decan() : age(40), salary(80), name("FirstDean")
		{}

		Decan(int _age, int _salary, std::string _name) : age(_age), salary(_salary), name(_name) 
		{}
		
		virtual void ComeToWork()
		{
			std::cout << "пришел в 12";
		}

		void signorder(std::string & order)  // подписать приказ
		{
			order += " ";
			order += name;
		}
		
		virtual void kicksomeone(Student & stud)
		{
			stud.stepuha-=1000;
		}

		virtual void UpSalary()
		{
			salary += 5000;
		}

		virtual void TakeVacation(int days /*кол-во дней*/)
		{
				salary -= days*100;
		} 

		void leave()
		{
			salary = 0;
			age = 0;
			name = " ";
		}


		virtual ~Decan()
		{ 
		}
};

class ZamDeck : public Decan
{
	public: 
		ZamDeck() : Decan(30, 50, "Zamer")
		{}

		ZamDeck (int _age, int _salary, std::string _name) : Decan(_age, _salary, _name) 
		{}

		void ComeToWork() override
		{
			std::cout << "пришел в 10";
		}

		void kicksomeone(Student & stud) override
		{
			stud.stepuha-=100;
		}

		void UpSalary() override
		{
			salary += 500;
		}

		void TakeVacation(int days /*кол-во дней*/) override
		{
				salary -= days*200;
		} 

		void FireStudent(Student & badstudent)
		{
			badstudent.leave();
		}



};

class Prepod : public Decan
{
	public: 
		Prepod() : Decan(25, 40, "Prepod")
		{}

		Prepod (int _age, int _salary, std::string _name) : Decan(_age, _salary, _name) 
		{}

		void ComeToWork() override
		{
			std::cout << "пришел в 8";
		}

		void kicksomeone(Student & stud) 
		{
			stud.intense += 100;
		}
		
		int * MakeRk (Student * students, int kol) 
		{
			int * marks = new int [kol];
			for(int i = 0; i < kol; i++)
				marks[i] = students[i].rightRk();
			return marks;
		}


};



int main()
{
	Decan dekmt, dekiu(39, 100, "DecanIU");
	ZamDeck zamMT, zamIU(30, 80, "ZamDekIU");
	Decan * p = &dekmt, * p1 = &dekiu;
	p->ComeToWork();
	p = &zamIU;
	p->ComeToWork();

	std::vector<Decan *> a;
	a.push_back(p);
	a.push_back(p1);
	for(int i = 0; i < 2; i++)
	{
		a[i]->UpSalary();
		a[i]->TakeVacation(365);
	}
	system("pause");
return 0;
} 