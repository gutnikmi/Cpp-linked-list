Реализуйте функции сериализации и десериализации двусвязного списка. Данные должны  
быть записаны в бинарном формате. Ожидаемая а лгоритмическая сложность меньше  
квадратичной.  
 ```struct ListNode  
  {  
   ListNode* prev = nullptr; // указатель на предыдущий элемент списка, либо `nullptr` в случае начала списка  
   ListNode* next = nullptr;  
   ListNode* rand = nullptr; // указатель на произвольный элемент данного списка, либо `nullptr`  
   std::string data; // произвольные пользовательские данные  
  };  
 class List  
  {  
   public:  
   void Serialize(FILE* file); // сохранение списка в файл, файл открыт с помощью `fopen(path, "wb")`  
   void Deserialize(FILE* file); // восстановление списка из файла, файл открыт с помощью `fopen(path, "rb")`  
  // ... ваши методы для заполнения списка  
  private:  
   ListNode* head = nullptr;  
   ListNode* tail = nullptr;  
   int count = 0;  
   };
  
