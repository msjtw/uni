%%% Jako pierwszą klauzulę (nie komentarz!) należy zdefiniować swoje dane     %%%
%%% w postaci faktu: student(imię, nazwisko, numer_indeksu, numer_grupy_lab). %%%
%%% Przykładowo:  student(jan,nowak_jeziorański,150000,2).                    %%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%zadanie 1
ostatni(H,[H]).
ostatni(X,[H|T]) :- ostatni(X,T).

%zadanie 2
przedostatni(H,[H,_]).
przedostatni(X,[H|T]) :- przedostatni(X,T).

%zadanie 3
bezostatniego([_], []).
bezostatniego([H|T], [H|X]) :- bezostatniego(T, X).

%zadanie 4
nakoniec(A, [], [A]).
nakoniec(A, [H|T], [H|X]) :- nakoniec(A, T, X).

%zadanie 5
zakazdym([],X,[]).
zakazdym([H|T],X,[H,X|L2]) :- zakazdym(T,X,L2).

%zadanie 6
codrugi([], []).
codrugi([_], []).
codrugi([H1,H2|T], [H2|L2]) :- codrugi(T, L2).

%zadanie 7
wstaw_za([X|T1],X,Y,[X, Y|T1]).
wstaw_za([H|T1],X,Y,[H|T2]) :-  wstaw_za(T1,X,Y,T2).

%zadanie 8
lewoprawo(X, [X], [], []).
lewoprawo(X, [X|T], [], T).
lewoprawo(X, [X|T], [], T).
lewoprawo(H, [H|T], [], T).
lewoprawo(X, [H1|T1], [H1|LL], LP) :- lewoprawo(X, T1, LL, LP).

%zadanie 9
wymiana(X, Y, [], []).
wymiana(X, Y, [X|T1], [Y|T2]) :- wymiana(X, Y, T1, T2).
wymiana(X, Y, [H1|T1], [H1|T2]) :- wymiana(X, Y, T1, T2).

%zadanie 10
polacz([],[]).
polacz([H1|T1], L1) :- polacz(T1, LP), append(H1,LP,L1).