%%% Jako pierwszą klauzulę (nie komentarz!) należy zdefiniować swoje dane     %%%
%%% w postaci faktu: student(imię, nazwisko, numer_indeksu, numer_grupy_lab). %%%
%%% Przykładowo:  student(jan,nowak_jeziorański,150000,2).                    %%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%zadanie 1
najwiekszy([X], X).
najwiekszy([H|T], H) :- najwiekszy(T, X), H > X.
najwiekszy([H|T], X) :- najwiekszy(T, X), H =< X.

%zadanie 2
liniowa([_,_]).
liniowa([A,B,C|T]) :- A-B =:= B-C, liniowa([B,C|T]).

%zadanie 3
rozbij([],[],[]).
rozbij(L1, [H2|T2], [P|X]) :- oddziel(L1, H2, P, R), rozbij(R, T2, X).

oddziel([H|T], 1, [H], T).
oddziel([H|T], I, [H|L1], L2) :- A is I-1,  oddziel(T, A, L1, L2).

%zadnie 4
przynaleznosc([], _, [], []).
przynaleznosc([H|T], [L,P], [H|L1], L2) :- H >= L, H =< P, !, przynaleznosc(T, [L,P], L1, L2).
przynaleznosc([H|T], [L,P], L1, [H|L2]) :- H < L, przynaleznosc(T, [L,P], L1, L2).
przynaleznosc([H|T], [L,P], L1, [H|L2]) :- H > P, przynaleznosc(T, [L,P], L1, L2).

%zadnie 5
decnabin(1,[1]).
decnabin(0,[0]).
decnabin(X, L) :- X > 1,  M is mod(X,2), X1 is div(X,2), decnabin(X1, T), append(T, [M], L).

%zadanie 6
szybkisort([],[]).
szybkisort([H|T], S) :- rozdziel(T, H, L1, L2), szybkisort(L1, S1), szybkisort(L2, S2), append(S1,[H|S2], S).

rozdziel([], _, [], []).
rozdziel([H|T], X, [H|M], N) :- H < X, rozdziel(T, X, M, N).
rozdziel([H|T], X, M, [H|N]) :- H >= X, rozdziel(T, X, M, N).

%zadanie 7
wstawsort([],[]).
wstawsort([H|T], S2) :- wstawsort(T, S), doposort(S, H, S2).

doposort([], A, [A]).
doposort([H|T], A, [A,H|T]) :- H > A.
doposort([H|T], A, [H|S]) :- doposort(T, A, S). 

%zadanie 8
unikalne([],[]).
unikalne([A],[A]).
unikalne([H|T], [H|L]) :- unikalne(T, L), not(member(H, L)), !.
unikalne([H|T], X) :- unikalne(T, X), member(H, X), !.

%zadanie 9
najblizszy(_,[A],A).
najblizszy(X, [H|T], H) :- najblizszy(X, T, A), abs(H-X) < abs(A-X).
najblizszy(X, [H|T], A) :- najblizszy(X, T, A), abs(H-X) >= abs(A-X).

%zadanie 10
eratostenes(N, L) :- ciagliczb(2, N, L1), sito(L1, L).

ciagliczb(M, M, [M]).
ciagliczb(N,M,[N|L]) :- N < M, A is N+1, ciagliczb(A, M, L).

odsiewaj(_,[],[]).
odsiewaj(X, [H|T], [H|L]) :- mod(H,X) =\= 0, !, odsiewaj(X, T, L).
odsiewaj(X, [_|T], L) :- odsiewaj(X, T, L).

sito([], []).
sito([H|T], [H|L2]) :- odsiewaj(H, T, L), sito(L, L2).