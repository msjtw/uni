msort([],[]).
msort([A], [A]).
msort(L1, L2) :- polowki(L1, LL, LP), msort(LL, ML), msort(LP, MP), merge(ML, MP, L2).

polowki([],[],[]).
polowki([A],[A],[]).
polowki(L,[H1|A],LP) :- append([H1|T1],[H2],L), polowki(T1, A, B), append(B,[H2],LP).

merge([], [], []).
merge([], X, X).
merge(X, [], X).
merge([HL|TL], [HR|TR], [HR|T]) :- HL > HR, !, merge([HL|TL], TR, T).
merge([HL|TL], [HR|TR], [HL|T]) :- merge(TL, [HR|TR], T).
