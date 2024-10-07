qwik(_, [], [], []).
qwik(A, [H|T], [H|T1], T2) :- H < A, qwik(A, T, T1, T2).
qwik(A, [H|T], T1, [H|T2]) :- H > A, qwik(A, T, T1, T2).

qwiksort([], []).
qwiksort([A], [A]).
qwiksort([H|T], X) :- qwik(H, T, L1, L2), qwiksort(L1, X1), qwiksort(L2, X2), append(X1,[H|X2], X).
