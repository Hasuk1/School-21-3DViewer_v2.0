# **School-21-3DViewer_v2.0**

![prev](misc/3d3.jpg)

`3D Viewer` is a computer graphics viewer.

## **Information**

## **Паттерны проектирования**

В любой человеческой деятельности, как, например, готовка еды или проведение экспериментов в области ядерной физики, существует некоторый набор устоявшихся практик, решающих базовые элементарные задачи. Они не требуют индивидуального подхода и обычно разрешаются устоявшимися за долгое время подходами, основанными на уже накопленном опыте предыдущих поваров или ядерных физиков. Например, для того чтобы испечь пирог, пусть даже и необычный, скорее всего понадобится тесто, технология приготовления которого заранее известна и обычно не требует некоторого творческого подхода. Так же и с программированием, при проектировании часто возникают элементарные задачи, с которыми до вас сталкивалось огромное число программистов, а их совокупный опыт вылился в устоявшиеся паттерны проектирования.

**`Паттерн проектирования`** описывает часто повторяющуюся при проектировании приложений задачу и принцип ее решения, который является универсальным для этой задачи. То есть для программиста паттерн проектирование ни что иное, как строительный блок, элементарная единица, которая реализуется в случае возникновения типовой подзадачи внутри проекта.

Обычно паттерны проектирования разделяют на три группы: порождающие, структурные и паттерны поведения. В действительности, различных паттернов огромное количество и ниже представлены лишь основные из них, которые устоялись в сообществе разработчиков. Их также называют паттернами от "Банды Четырех".

**Порождающие паттерны** - отвечают за создание новых объектов. 

| Название | Краткое описание | Применение в рамках проекта |
| - | - | - |
| [Одиночка (singleton)](https://ru.wikipedia.org/wiki/%D0%9E%D0%B4%D0%B8%D0%BD%D0%BE%D1%87%D0%BA%D0%B0_(%D1%88%D0%B0%D0%B1%D0%BB%D0%BE%D0%BD_%D0%BF%D1%80%D0%BE%D0%B5%D0%BA%D1%82%D0%B8%D1%80%D0%BE%D0%B2%D0%B0%D0%BD%D0%B8%D1%8F)) | Гарантирует, что у класса есть только один экземпляр, и предоставляет к нему глобальную точку доступа. | Контроллер |
| Строитель (builder) | Отделяет конструирование сложного объекта от его представления, так что в результате одного и того же процесса конструирования могут получаться разные представления. | - |
| Фабричный метод (factory method) | Определяет интерфейс для создания объекта, но оставляет подклассам решение о том, экземпляры какого класса должны создаваться. Фабричный метод позволяет классу делегировать создание экземпляров подклассам. | - |
| Абстрактная фабрика (abstract factory) | Предоставляет интерфейс для создания семейств взаимосвязанных или взаимозависимых объектов, не специфицируя их конкретных классов. | - |
| Прототип (prototype) | Задает виды создаваемых объектов с помощью экземпляра-прототипа и создает новые объекты путем копирования этого прототипа. | - |

**Структурные паттерны** - отвечают за структуризацию классов и объектов. 

| Название | Краткое описание | Применение в рамках проекта |
| - | - | - |
| [Фасад (facade)](https://ru.wikipedia.org/wiki/%D0%A4%D0%B0%D1%81%D0%B0%D0%B4_(%D1%88%D0%B0%D0%B1%D0%BB%D0%BE%D0%BD_%D0%BF%D1%80%D0%BE%D0%B5%D0%BA%D1%82%D0%B8%D1%80%D0%BE%D0%B2%D0%B0%D0%BD%D0%B8%D1%8F)) | Предоставляет унифицированный интерфейс вместо набора интерфейсов некоторой подсистемы. Фасад определяет интерфейс более высокого уровня, который упрощает использование подсистемы. | Модель |
| Декоратор (decorator) | Динамически добавляет объекту новые обязанности. Является гибкой альтернативой порождению подклассов с целью расширения функциональности. | - |
| Адаптер (adapter) | Преобразует интерфейс одного класса в другой интерфейс, на который рассчитаны клиенты. Адаптер обеспечивает совместную работу классов с несовместимыми интерфейсами, которая без него была бы невозможна. | - |
| Мост (bridge) | Позволяет отделить абстракцию от ее реализации так, чтобы то и другое можно было изменять независимо. | - |
| [Компоновщик (composite)](https://ru.wikipedia.org/wiki/%D0%9A%D0%BE%D0%BC%D0%BF%D0%BE%D0%BD%D0%BE%D0%B2%D1%89%D0%B8%D0%BA_(%D1%88%D0%B0%D0%B1%D0%BB%D0%BE%D0%BD_%D0%BF%D1%80%D0%BE%D0%B5%D0%BA%D1%82%D0%B8%D1%80%D0%BE%D0%B2%D0%B0%D0%BD%D0%B8%D1%8F)) | Компонует объекты в древовидные структуры для представления иерархий «часть — целое». Позволяет клиентам единообразно трактовать индивидуальные и составные объекты. | Парсер |
| Заместитель (proxy) | Является суррогатом другого объекта и контролирует доступ к нему. | - |
| Приспособленец (flyweight) | Применяет совместное использование для эффективной поддержки множества мелких объектов. | - |

**Поведенческие паттерны** - отвечают за взаимодействие объектов. 

| Название | Краткое описание | Применение в рамках проекта |
| - | - | - |
| Состояние (state) | Позволяет объекту изменять свое поведение в зависимости от внутреннего состояния. Извне создается впечатление, что изменился класс объекта. | - |
| Итератор (iterator) | Предоставляет способ последовательного обращения ко всем элементам составного объекта без раскрытия его внутреннего представления. | - |
| Посетитель (visitor) | Описывает операцию, выполняемую с каждым объектом из некоторой структуры. Паттерн посетитель позволяет определить новую операцию, не изменяя классы этих объектов. | - |
| [Стратегия (strategy)](https://ru.wikipedia.org/wiki/%D0%A1%D1%82%D1%80%D0%B0%D1%82%D0%B5%D0%B3%D0%B8%D1%8F_(%D1%88%D0%B0%D0%B1%D0%BB%D0%BE%D0%BD_%D0%BF%D1%80%D0%BE%D0%B5%D0%BA%D1%82%D0%B8%D1%80%D0%BE%D0%B2%D0%B0%D0%BD%D0%B8%D1%8F)) | Определяет семейство алгоритмов, инкапсулирует каждый из них и делает их взаимозаменяемыми. Стратегия позволяет изменять алгоритмы независимо от клиентов, которые ими пользуются. | Афинные преобразования |
| Наблюдатель (observer) | Определяет зависимость типа «один ко многим» между объектами таким образом, что при изменении состояния одного объекта все зависящие от него оповещаются об этом и автоматически обновляются. | - |
| Команда (command) | Инкапсулирует запрос как объект, позволяя тем самым задавать параметры для обработки соответствующих запросов, ставить запросы в очередь или протоколировать их, а также поддерживать отмену операций. | - |
| Цепочка обязанностей (chain of responsibility) | Позволяет избежать привязки отправителя запроса к его получателю, предоставляя возможность обработать запрос нескольким объектам. Связывает объекты-получатели в цепочку и передает запрос по этой цепочке, пока он не будет обработан. | - |
| Посредник (mediator) | Определяет объект, инкапсулирующий способ взаимодействия множества объектов. Посредник обеспечивает слабую связанность системы, избавляя объекты от необходимости явно ссылаться друг на друга и позволяя тем самым независимо изменять взаимодействия между ними. | - |
| Хранитель (memento) | Не нарушая инкапсуляции, фиксирует и выносит за пределы объекта его внутреннее состояние, так чтобы позднее можно было восстановить в нем объект. | - |
| Шаблонный метод (template method) | Шаблонный метод определяет основу алгоритма и позволяет подклассам переопределить некоторые шаги алгоритма, не изменяя его структуру в целом. | - |
| Интерпретатор (interpeter) | Для заданного языка определяет представление его грамматики, а также интерпретатор предложений этого языка. | - |

В проекте SmartCalc v2.0 вы уже сталкивались с применением уже устоявшихся практик (паттернов) при проектировании приложений (паттерн MVC). Напоминаем, что MVC в том или ином виде является одним из самых частых решений в плане структурирования кода в ходе разработки приложений с пользовательским интерфейсом. Пользовательский интерфейс и бизнес-логику с прилежащим к ней контроллером обычно разбивают на два различных глобальных домена: домен интерфейса и домен бизнес-логики.

Домен интерфейса отвечает только за отображение интерфейса и передачу команд домену бизнес-логики. Загруженные из файла данные не должны храниться в домене интерфейса.

Домен бизнес-логики отвечает за основную функциональность системы. Именно в нем хранятся загруженные данные, выполняются все операции над ними. Также в этом домене производится отрисовка.

С примерной предлагаемой диаграммой классов для домена бизнес-логики можете ознакомиться в материалах.

## Part 1. 3DViewer v2.0

Разработать программу для визуализации каркасной модели в трехмерном пространстве.

- Программа должна быть разработана на языке C++ стандарта C++17. 
- Код программы должен находиться в папке src 
- При написании кода необходимо придерживаться Google Style
- Сборка программы должна быть настроена с помощью Makefile со стандартным набором целей для GNU-программ: all, install, uninstall, clean, dvi, dist, tests. Установка должна вестись в любой другой произвольный каталог 
- Программа должна быть разработана в соответствии с принципами объектно-ориентированного программирования, структурный подход запрещен
- Должно быть обеспечено полное покрытие unit-тестами модулей, связанных с загрузкой моделей и аффинными преобразованиями
- В один момент времени должна быть только одна модель на экране.
- Программа должна предоставлять возможность:
    - Загружать каркасную модель из файла формата obj (поддержка только списка вершин и поверхностей).
    - Перемещать модель на заданное расстояние относительно осей X, Y, Z.
    - Поворачивать модель на заданный угол относительно своих осей X, Y, Z.
    - Масштабировать модель на заданное значение.
- В программе должен быть реализован графический пользовательский интерфейс, на базе любой GUI-библиотеки с API для C++  
  * Для Linux: GTK+, CEF, Qt, JUCE
  * Для Mac: GTK+, CEF, Qt, JUCE, SFML, Nanogui, Nngui
- Графический пользовательский интерфейс должен содержать:
    - Кнопку для выбора файла с моделью и поле для вывода его названия.
    - Зону визуализации каркасной модели.
    - Кнопку/кнопки и поля ввода для перемещения модели. 
    - Кнопку/кнопки и поля ввода для поворота модели. 
    - Кнопку/кнопки и поля ввода для масштабирования модели.  
    - Информацию о загруженной модели - название файла, кол-во вершин и ребер.
- Программа должна корректно обрабатывать и позволять пользователю просматривать модели с деталями до 100, 1000, 10 000, 100 000, 1 000 000 вершин без зависания (зависание - это бездействие интерфейса более 0,5 секунды).
- Программа должна быть реализована с использованием паттерна MVC, то есть:
    - не должно быть кода бизнес-логики в коде представлений
    - не должно быть кода интерфейса в контроллере и в модели
    - контроллеры должны быть тонкими
- Необходимо использовать минимум три различных паттерна проектирования (например, фасад, стратегия и команда)
- Классы должны быть реализованы внутри пространства имен `s21`
- Для осуществления афинных преобразований могут использоваться матрицы из библиотеки из предыдущего проекта s21_matrix+

*Замечание:* **Не загружайте тяжелые файлы (>10 мб) в гит.**

## Part 2. Дополнительно. Настройки

- Программа должна позволять настраивать тип проекции (параллельная и центральная)
- Программа должна позволять настраивать тип (сплошная, пунктирная), цвет и толщину ребер, способ отображения (отсутствует, круг, квадрат), цвет и размер вершин
- Программа должна позволять выбирать цвет фона
- Настройки должны сохраняться между перезапусками программы

## Part 3. Дополнительно. Запись
 
- Программа должна позволять сохранять полученные ("отрендеренные") изображения в файл в форматах bmp и jpeg
- Программа должна позволять по специальной кнопке записывать небольшие "скринкасты" - текущие пользовательские аффинные преобразования загруженного объекта в gif-анимацию (640x480, 10fps, 5s)
