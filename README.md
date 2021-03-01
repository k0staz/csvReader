--ENG--
A program that reads an arbitrary CSV form from a file and calculates the values of the cells, if it's necessary, after that displays the resulting plate in the CSV-form to the console.

Input CSV file might look like this:
	
      ,A,B,Cell
      1,1,0,1
      2,2,=A1+Cell30,0
      30,0,=B1+A1,5
And in that case the output should look like this:

      ,A,B,Cell
      1,1,0,1
      2,2,6,0,
      30,0,1,5

--RUS--
Программа, которая читает произвольную CSV-форму из файла (количество строк и столбцов может быть любым), вычисляет значения ячеек, если это необходимо, и выводит получившуюся табличку в виде CSV-представления в консоль.

Данные на вход могут выглядеть следующим образом:

      ,A,B,Cell
      1,1,0,1
      2,2,=A1+Cell30,0
      30,0,=B1+A1,5

В данном случае в консоль должно быть выведенно следующее:
      
      ,A,B,Cell
      1,1,0,1
      2,2,6,0,
      30,0,1,5
