# filter
 
 Filter.h
 
 Classes:
 
 point:  //класс трехмерной точки хранит координаты и сенсор
 
  X,Y,Z - float
  sensor - String
  
  operators:
  +=  // сложение точек
  /=  // деление точек
  <<  // вывод
  
  methods:
  
  SetPoint(string sensor, float X, float Y, float Z) //присвоить значение точке
  
 filter: //класс фильтра
 
  strength - int //мощность фильтрации (приватное поле)
  
  
  
  methods:
 
  SetStrength(int strength) // задает мощность фильтрации (сколько точек рядом будут усреднены) если число не кратно 2 сделает +1

  GetFiltered(String point_str) // получает строку с точками и возвращает list<points> с отфильтрованными значениями 
  
  Str_parce(String point_str) // приватный метод, вызывается в GetFiltered возвращает list<points>
  
  list_point_avg(std::list <point> list_point) // приватный метод, усредняет list<points> возвращает list<points>
  
  add_list(std::list <point> list_point) //приватный метод, суммирует list<points> возвращает list<points>
 
