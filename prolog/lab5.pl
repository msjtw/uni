%%% Jako pierwszą klauzulę (nie komentarz!) należy zdefiniować swoje dane     %%%
%%% w postaci faktu: student(imię, nazwisko, numer_indeksu, numer_grupy_lab). %%%
%%% Przykładowo:  student(jan,nowak_jeziorański,150000,2).                    %%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%zadanie 1
klonuj([],[]).
klonuj([H1|T1], [[H1,H1]|T2]) :- klonuj(T1, T2).

%zadanie 2
srodek([A],A).
srodek(L1,S) :- append([_|T1],[_],L1), srodek(T1, S).

%zadanie 3
polowki([],[],[]).
polowki(L,[H1|A],LP) :- append([H1|T1],[H2],L), polowki(T1, A, B), append(B,[H2],LP).

%zadanie 4
sumuj([A],A).
sumuj([H1|T1], S) :- sumuj(T1, A), S is H1+A.

%zadanie 5
ile_wiekszych([],X,0).
ile_wiekszych([H|T],X,N) :- H > X, ile_wiekszych(T,X,A), N is A+1.
ile_wiekszych([H|T],X,N) :- H =< X, ile_wiekszych(T,X,N).

%zadanie 6
plus_minus([],0).
plus_minus([H|T], N) :- [H] = [+], plus_minus(T, A), N is A+1.
plus_minus([H|T], N) :- [H] = [-], plus_minus(T, A), N is A-1.

%zadanie 7
wstawiaj([],X,1,[X]).
wstawiaj([T],X,1,[X,T]).
wstawiaj([H|T],X,1,[X,H|T]).
wstawiaj([H|T],X,I,[H|L1]) :- A is I-1, wstawiaj(T,X,A,L1).

%zadanie 8
usuwaj([T|H],1,H).
usuwaj([H|T],N,L1) :- A is N-1, usuwaj(T,A,L1).

%zadanie 9
rozdziel([], X, [], []).
rozdziel([H|T], X, [H|M], N) :- H < X, rozdziel(T, X, M, N).
rozdziel([H|T], X, M, [H|N]) :- H >= X, rozdziel(T, X, M, N).

%zadanie 10
powiel([],[],[]).
powiel([H1|T1], [0|T2], L) :- powiel(T1, T2, L).
powiel([H1|T1], [H2|T2], [H1|L]) :- A is H2-1, A >= 0, powiel([H1|T1], [A|T2], L).