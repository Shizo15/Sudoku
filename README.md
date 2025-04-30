# Sudoku CLI

**Sudoku CLI** to gra Sudoku w trybie tekstowym napisana w języku C. Program pozwala użytkownikowi na rozgrywkę w Sudoku o różnych rozmiarach i poziomach trudności bez potrzeby korzystania z interfejsu graficznego.

## 🧩 Funkcjonalności

- Rozmiary planszy: `4x4`, `9x9`, `16x16`
- Trzy poziomy trudności:
    - Łatwy (więcej podpowiedzi)
    - Średni
    - Trudny (mniej podpowiedzi)
- Interfejs w trybie tekstowym (terminal)
- Zapisywanie i wczytywanie stanu gry
- Sprawdzanie poprawności rozwiązania
- Licznik czasu rozgywki, pustych pól i pomyłek
- Instrukcja wbudowana w aplikację
- Obsługa błędów i nieprawidłowych danych wejściowych

## 🛠️ Kompilacja (Windows, z MinGW)

Do kompilacji potrzebny jest kompilator C (np. `gcc`). Upewnij się, że masz też plik nagłówkowy `sudoku.h`. Otwórz cmd lub inny terminal, przejdź do katalogu gry i wykonaj polecenie:

```bash
gcc main.c -o sudoku.exe

sudoku.exe
```


## 📋 Sterowanie
1. Rozpocznij nową grę lub wczytaj zapisany stan gry
2. Wybierz rozmiar planszy i poziom trudności
3. Korzystaj z menu gry, aby: 
   -  Wykonać ruch (podając wiersz, kolumnę i wartość oddzielone spacjami)
   -  Zapisać grę
   -  Wyświetlić instrukcje
4. Aby wyczyścić pole, wpisz 0 jako wartość
5. Niektóre pola (podpowiedzi) są zablokowane i nie można ich zmieniać

## ⚠️ Znane problemy i ograniczenia
- Brak walidacji unikalności rozwiązania Sudoku (generowany układ może mieć więcej niż jedno rozwiązanie).
- Funkcja clearConsole() jest zakomentowana i wymaga dopasowania do systemu (system("cls") / system("clear")), jednak jej użycie może powodować błędy.
- Brak możliwości cofania ruchu (można go tylko wykonać jeszcze raz lub zastąpić 0, ale nie cofnąć)

Memiki budowlane na poprawę humoru :)

<img src="https://github.com/user-attachments/assets/39272a89-7888-4cd6-b041-a8b07713711f" alt="meme1" width="450">


<img src="https://github.com/user-attachments/assets/4d815ab6-5f3f-474b-a6bf-c2431d6221b1" alt="meme2" width="450">