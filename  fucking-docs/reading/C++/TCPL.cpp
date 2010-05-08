class Employee {
  enum Empl_type { M, E };
  Empl_type type;
  
  Employee() : type(E){}

  string first_name, family_name;
  char middle_initial;

  Date hiring_date;
  short department;
  // ...
public:
  Employee(const string &name, int dept);
  virtual void print()const;
  // ...
};

class Manager : public Employee {
  set<Employee *> group;  // people managed
  short level;
  //...
public:
  Manager(const string &name, int dept, int lvl );
  void print() const;
  // ...
};

void Employee::print() const
{
  cout << family_name << '\t' << department << '\n';
}

void Manager::print() const {
  Employee::print();
  cout << "\tlevel" << level << '\n';
  // ...
}

void print_list(set<Employee *> &s) {
  for (set<Employee *>::const_iterator p = s.begin(); p != s.end(); ++p)
    (*p)->print();

  // or even like that:
  for_each(s.begin(), s.end(), mem_fun(&Employee::print));
}
