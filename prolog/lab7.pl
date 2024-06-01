%%% Jako pierwszą klauzulę (nie komentarz!) należy zdefiniować swoje dane     %%%
%%% w postaci faktu: student(imię, nazwisko, numer_indeksu, numer_grupy_lab). %%%
%%% Przykładowo:  student(jan,nowak_jeziorański,150000,2).                    %%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

student(stanislaw,fiedler,160250,1).

%zadanie 1
podzielniki(N,N,[]).
podzielniki(N, D, [D|L]) :- D < N, mod(N,D) =:= 0, !, D2 is D + 1, podzielniki(N, D2, L).
podzielniki(N, D, L) :- D < N, D2 is D + 1, podzielniki(N, D2, L).

sumuj([], 0).
sumuj([H|T], S) :- sumuj(T, R), S is R+H.

doskonala(N) :- N > 1,  podzielniki(N,1,L), sumuj(L,N).

%zadanie 2
przekroj([], _, []).
przekroj(_, [], []).
przekroj([H1|T1], [H2|T2], L) :- H1 < H2, !, przekroj(T1, [H2|T2], L).
przekroj([H1|T1], [H2|T2], L) :- H1 > H2, !, przekroj([H1|T1], T2, L).
przekroj([H|T1], [H|T2], [H|L]) :- przekroj(T1, T2, L).

%zadanie 3
glowyogony([],[],[]).
glowyogony([[H|T]|TL], [H|LG], [T|LO]) :- glowyogony(TL, LG, LO).

slad([[A]],A).
slad(M, S) :- glowyogony(M, [LGH|_], [_|LO]), slad(LO, A),S is LGH + A.

%zadnie 4
rozszerzaj([A], A).
rozszerzaj([[HL,HR]|T], [HL,HR]) :- rozszerzaj(T, [A, B]), HL < A, B < HR, !.
rozszerzaj([[HL,_]|T], [HL,B]) :- rozszerzaj(T, [A, B]), HL < A, !.
rozszerzaj([[_,HR]|T], [A,HR]) :- rozszerzaj(T, [A, B]), B < HR, !.
rozszerzaj([_|T], [A,B]) :- rozszerzaj(T, [A, B]).

%zaadnie 5
ciagliczb(M, M, [M]).
ciagliczb(N,M,[N|L]) :- N < M, A is N+1, ciagliczb(A, M, L).

liczpodziel(N, N, 0).
liczpodziel(N, D, C) :- D < N, mod(N, D) =:= 0, !, A is D+1, liczpodziel(N, A, B),  C is B+1.
liczpodziel(N, D, C) :- D < N, mod(N, D) =\= 0, !, A is D+1, liczpodziel(N, A, C).

antyp([], _).
antyp([H|T], D) :- liczpodziel(H, 1, DH), DH < D, !, antyp(T, D).

antypierwsza(N) :- liczpodziel(N, 1, DN), N2 is N-1, ciagliczb(1,N2,L), antyp(L, DN).

%zadanie 6
rozmien(L,N,[N]) :- append(_,[N], L).
rozmien(L,N,R2) :- append(_,[A], L), A < N, !, N2 is N - A, rozmien(L, N2, R), append(R, [A], R2).
rozmien(L,N,R) :- append(L1,[A], L), A > N, rozmien(L1, N, R).

%zadanie 7
wpolu([],_,[]).
wpolu([[X,Y]|T], [[LDX,LDY],[PGX,PGY]], [[X,Y]|R]) :- X >= LDX, X =< PGX, Y >= LDY, Y =< PGY, !, wpolu(T, [[LDX,LDY],[PGX,PGY]], R).
wpolu([[X,_]|T], [[LDX,LDY],[PGX,PGY]], R) :- X < LDX, !, wpolu(T, [[LDX,LDY],[PGX,PGY]], R).
wpolu([[X,_]|T], [[LDX,LDY],[PGX,PGY]], R) :- X > PGX, !, wpolu(T, [[LDX,LDY],[PGX,PGY]], R).
wpolu([[_,Y]|T], [[LDX,LDY],[PGX,PGY]], R) :- Y < LDY, !, wpolu(T, [[LDX,LDY],[PGX,PGY]], R).
wpolu([[_,Y]|T], [[LDX,LDY],[PGX,PGY]], R) :- Y > PGY, !, wpolu(T, [[LDX,LDY],[PGX,PGY]], R).

%zadanie 8
minX([[X,_]], X).
minX([[X,_]|T], X) :- minX(T, X2), X < X2, !.
minX([_|T], X2) :- minX(T, X2).

maxX([[X,_]], X).
maxX([[X,_]|T], X) :- maxX(T, X2), X > X2, !.
maxX([_|T], X2) :- maxX(T, X2).

minY([[_,Y]], Y).
minY([[_,Y]|T], Y) :- minY(T, Y2), Y < Y2, !.
minY([_|T], Y2) :- minY(T, Y2).

maxY([[_,Y]], Y).
maxY([[_,Y]|T], Y) :- maxY(T, Y2), Y > Y2, !.
maxY([_|T], Y2) :- maxY(T, Y2).

minpole(L,[[LDX,LDY],[PGX,PGY]]) :- minX(L, LDX), minY(L, LDY), maxX(L, PGX), maxY(L, PGY).

%zadanie 9
zamien_g([A],[A]).
zamien_g([A,B|T], [A|R]) :- A =< B, !, zamien_g([B|T], R).
zamien_g([A,B|T], [B|R]) :- A > B, zamien_g([A|T], R).

zamien_d([A],[A]).
zamien_d([A,B|T], [A|R]) :- A >= B, !, zamien_d([B|T], R).
zamien_d([A,B|T], [B|R]) :- A < B, zamien_d([A|T], R).

odwracaj([],[]).
odwracaj([H|T],L2) :- odwracaj(T, R), append(R, [H], L2).

koktajl([], []).
koktajl([A], [A]).
koktajl(L,S) :- zamien_g(L, L2), odwracaj(L2, L3), zamien_d(L3, L4), odwracaj(L4, L5), append([Pier|L6],[Ost],L5), koktajl(L6, L7), append([Pier|L7],[Ost],S).

%zadanie 10
ciagFib(N,F1,_,[]) :- F1 > N.
ciagFib(N, F1, F2, [F1|L]) :- F1 =< N, F3 is F1 + F2, ciagFib(N, F2, F3, L), !.

rozklad(L,N,[N]) :- append(_,[N], L).
rozklad(L,N,R2) :- append(_,[A], L), A < N, !, N2 is N - A, rozklad(L, N2, R), append(R, [A], R2).
rozklad(L,N,R) :- append(L1,[A], L), A > N, rozklad(L1, N, R).

rozklad_fib(N, L) :- ciagFib(N, 0, 1, LF), rozklad(LF, N ,L).