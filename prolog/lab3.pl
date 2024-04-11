%%% Jako pierwszą klauzulę (nie komentarz!) należy zdefiniować swoje dane     %%%
%%% w postaci faktu: student(imię, nazwisko, numer_indeksu, numer_grupy_lab). %%%
%%% Przykładowo:  student(jan,nowak_jeziorański,150000,2).                    %%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

student(stanisław,fiedler,160250,1).

next(świnoujście,kołobrzeg).
next(świnoujście, szczecin).
next(kołobrzeg,ustka).
next(ustka, gdańsk).
next(gdańsk,toruń).
next(gdańsk,olsztyn).
next(olsztyn,toruń).
next(olsztyn,białystok).
next(szczecin,bydgoszcz).
next(szczecin, gorzów-wlkp).
next(bydgoszcz,toruń).
next(bydgoszcz,poznań).
next(poznań,toruń).
next(gorzów-wlkp,poznań).
next(gorzów-wlkp,zielona-góra).
next(zielona-góra,poznań).
next(zielona-góra,wrocław).
next(toruń,łódź).
next(toruń,warszawa).
next(białystok, warszawa).
next(białystok,lublin).
next(poznań,łódź).
next(warszawa,radom).
next(warszawa,łódź).
next(radom,lublin).
next(radom,kielce).
next(wrocław,łódź).
next(łódź,radom).
next(łódź,częstochowa).
next(częstochowa,kielce).
next(częstochowa,katowice).
next(katowice,kraków).
next(kielce,kraków).
next(kielce,rzeszów).
next(lublin,kielce).
next(lublin,rzeszów).
next(kraków,rzeszów).
% Pytanie: Czy istnieje połączenie miedzy Świnoujściem a Rzeszowem?


połączenie(X,Y) :- next(X,Y).
połączenie(X,Y) :- next(X,Z), połączenie(Z,Y).

zjazd(A,B,A) :- next(A,B).
zjazd(A,B,Z) :- next(A,C), zjazd(C,B,Z).

trasa(A,B,obok(A,B)) :- next(A,B).
trasa(A,B,obok(A,X)) :- next(A,C), trasa(C,B,X).

trasa2(A,B,obok(A,B)) :- next(A,B).
trasa2(A,B,obok(X,B)) :- next(C,B), trasa2(A,C,X).

trasa3(A,B,[A,B]) :- next(A,B).
trasa3(A,B,[A|X]) :- next(A,C), trasa3(C,B,X).
