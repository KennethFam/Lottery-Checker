# Lottery-Checker

The program takes in 5 unique winning lottery numbers in the range of 1 through 39 and a .txt file that contains lines of 5 numbers with a maximum of 100 numbers.
You need to use gcc to pass arguments. <br />
<br />
Here is the format:
The 5 winning numbers need to be passed in the format [-n num1,num2,num3,num4,num5] without the brackets.
The file needs to be passed in the format [-f filename] without the brackets. <br />
<br />
  Ex: 
    gcc lotterychecker.c -o lotterychecker
    ./lotterychecker -n 1,2,3,4,5 -f mynumbers.txt <br /> <br />
    or <br /> <br />
      gcc lotterychecker.c -o lotterychecker
      ./lotterychecker -f mynumbers.txt -n 1,2,3,4,5
    Note: If you are using MinGW on Windows, use '\' instead of '/'. <br /> <br />

Numbers in the txt file must be in the format [num1 num2 num3 num4 num5] without the brackets. Empty lines will be ignored. <br />
  Ex: <br />
    1 2 3 4 5 <br />
    6 7 8 9 10 <br /> <br />

The program will print out the number of matches in the format: <br />
  5 Matches: {num1,num2,num3,num4,num5} {num6,num7,num8,num9,num10} <br />
  . <br />
  . <br />
  . <br />
  1 Match: {num11,num12,num13,num14,num15} <br /> <br />

  Ex: <br />
    Let's say -n 1,2,3,4,5 was passed and the file contained the same numbers as the last example. The result would be: <br />
      5 Matches: {1,2,3,4,5} <br />
