**Задание**
===========
Реализуйте класс Settings со следующими членами класса:
string input_pipeline;
vector<float> confidence;
vector<vector<vector<float>>> anchors;

В этом классе реализуйте метод readIniFile(), осуществляющий считывание из файла test.ini, преобразование в подходящие типы и присвоение членам классов соответствующих значений.
Также реализуйте метод, который получает значения членов класса извне, и записывающий изменения в файл test.ini с сохранением предыдущей версии файла в test.ini.backup.

Пример файла test.ini:
/* Начало файла */
input_pipeline="src srcconfig=/dev/null device=device0 ! device-mode=0 some-parameter=true another-parameter=0 ! video/x-raw,format=BGR,width=1920,height=1080 ! appsink"
confidence={0.1, 0.3}
anchors={{{1, 2}, {3, 4}, {5, 6}},{{7, 8}, {9, 10}, {11, 12}}}
/* Конец файла */

**Решение**
===========
Решение содержится в файле settings.cpp
