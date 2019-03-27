# wykrywacz plagiatów

Program ma za zadanie obliczanie podobieństwa pomiędzy dwoma plikami tekstowymi.

Pierwszym krokiem jest utworzenie słowników (d1, d2) dla obu plików, zawierających słowa oraz liczbę ich wystąpień. Utwożono wspólny słownik (dcommon) zawierający wszystkie słowa, występujące w obu słownikach co najmniej raz.

Następnym krokiem jest obliczenie prawdopodobieństwa wystąpienia słowa w każdym z plików, prawdopodobienstwa sa zapisywane do wektorów v1 i v2. Wektory sa równej długości, określonej przez długość słownika dcommon. Dla wektora v1 prawdopodobieństwo na i-tej pozycji wystąpienia słowa ze słownika dcommon z i-tej pozycji w pliku pierwszym, wektor v2 jest tworzony analogicznie do v1. Prawdopodobieństwo wystąpienia słowa jest obliczane: 

ilość wystąpień słowa / całkowita ilość słów

Wspołczynnik podobieństwa plików jest równy kosinusowi kąta pomiędzy wektorami v1 i v2, zgodnie z wyrażeniem:

    (v1 * v2)/(||v1|| * ||v2||)

gdzie: 
    v1 * v2 - iloczyn skalarny wektorów v1 i v2    
    ||v1||, ||v2|| - dlugość wektorów v1, v2


Wynikiem jest liczba z przedzialu 0 - 1 oznaczająca poziom podobieństwa, 0 (brak jakiegokolwiek podobieństwa, 1 pełne podobieństwo), pełne podobieństwo oznacza zgodność słowników, lecz nie oznacza to identyczności plików, tylko ten sam zestaw słów, ale możliwe, że w innej kolejności.

-------

Przedstawiony program jest moim rozwiązaniem powyższego zadania wykonanym na 2. semestrze studiów.