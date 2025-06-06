# Задание 9 — Фильтрация студентов по предмету

## Описание

Программа представляет собой MFC-приложение, выполняющее загрузку и фильтрацию списка студентов. Список загружается из текстового файла `Students.txt`, содержащего по одному студенту на строку в формате:

```
Фамилия Предмет
```

После загрузки производится фильтрация по следующим правилам:

- Если студент изучает **химию** или **биологию**, он включается в выходной файл `FilteredStudents.txt`
- Если студент изучает **физику**, он исключается из результирующего списка

## Пример работы

**Входной файл `Students.txt`:**
```
Иванов химия
Петров физика
Сидорова биология
Кузнецов математика
```

**Результат в `FilteredStudents.txt`:**
```
Иванов химия
Сидорова биология
```

## Этапы работы программы

1. Пользователь нажимает кнопку **Загрузить**
2. Открывается и считывается файл `Students.txt`
3. Производится фильтрация данных в соответствии с условиями
4. Результаты записываются в `FilteredStudents.txt`


## Выполнение требований задания

Реализация соответствует условиям задачи №9:

- Используются контейнеры и алгоритмы стандартной библиотеки C++ (STL)
- Исключено использование С-конструкций
- Интерфейс реализован с использованием MFC
- Ведётся логирование всех действий приложения
- Обеспечена обработка ошибок (например, отсутствие входного файла, некорректный формат строк и др.)

## Зависимости

- Visual Studio с поддержкой MFC
- Компилятор C++ с поддержкой STL
