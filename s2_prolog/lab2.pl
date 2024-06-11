%%% Jako pierwszą klauzulę (nie komentarz!) należy zdefiniować swoje dane     %%%
%%% w postaci faktu: student(imię, nazwisko, numer_indeksu, numer_grupy_lab). %%%
%%% Przykładowo:  student(jan,nowak_jeziorański,150000,2).                    %%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

pionowy(odcinek(punkt(X, Y1), punkt(X, Y2))).
poziomy(odcinek(punkt(X1, Y), punkt(X2, Y))).


regularny(prostokąt(punkt(X1, Y1), punkt(X2, Y1), punkt(X2, Y2), punkt(X1, Y2))).

ptak(X) :- pokrycie(X, pióra), ruch(X, latanie).
pokrycie(kura, pióra).
pokrycie(wróbel, pióra).
pokrycie(sójka, pióra).
pokrycie(gołab, pióra).
ruch(kura, bieganie).
ruch(wróbel, latanie).
ruch(sójka, latanie).
ruch(gołąb, bieganie).

safe(state(X, W, X, C)).
safe(state(X, X, G, X)).

move(state(west, W, G, west), farmer_kapusta_east, state(east, W, G, east)) :- safe(state(east, W, G, east)).
move(state(west, west, G, C), farmer_wilk_east, state(east, east, G, C)) :- safe(state(east, east, G, C)).
move(state(west, W, west, C), farmer_koza_east, state(east, W, east, C)) :- safe(state(east, W, east, C)).
move(state(west, W, G, C), farmer_sam_east, state(east, W, G, C)) :- safe(state(east, W, G, C)).

move(state(east, W, G, C), farmer_sam_west, state(west, W, G, C)) :- safe(state(west, W, G, C)).
move(state(east, W, east, C), farmer_koza_west, state(west, W, west, C)) :- safe(state(west, W, west, C)).
move(state(east, east, G, C), farmer_wilk_west, state(west, west, G, C)) :- safe(state(west, west, G, C)).
move(state(east, W, G, east), farmer_kapusta_west, state(west, W, G, west)) :- safe(state(west, W, G, west)).

can_get(state(east,east,east,east)).
can_get(Before) :- move(Before, Move, After), can_get(After).