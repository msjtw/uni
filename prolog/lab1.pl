%            Maria-Piotr        Adam-Ewa
%            -----------        --------
%              /  |  \          /  |  \
%             /   |   \        /   |   \
%            /  Marek  \      /  Joanna \
% Robert-Agata         Jan-Anna         Krzysztof-Agnieszka
% ------------         --------         -------------------
%     /  \               /  \                   /  \
%    /    \             /    \                 /    \
%   /      \           /      \               /      \
% Radek   Beata      Darek   Tomek         Jacek    Iwona

student(stanisław,fiedler,160250,1).

kobieta(maria).
kobieta(ewa).
kobieta(joanna).
kobieta(agata).
kobieta(anna).
kobieta(agnieszka).
kobieta(beata).
kobieta(iwona).

mężczyzna(piotr).
mężczyzna(adam).
mężczyzna(marek).
mężczyzna(robert).
mężczyzna(jan).
mężczyzna(krzysztof).
mężczyzna(radek).
mężczyzna(darek).
mężczyzna(tomek).
mężczyzna(jacek).

rodzic(maria, agata).
rodzic(maria, marek).
rodzic(maria, jan).
rodzic(piotr, agata).
rodzic(piotr, marek).
rodzic(piotr, jan).
rodzic(adam, anna).
rodzic(adam, joanna).
rodzic(adam, krzysztof).
rodzic(ewa, anna).
rodzic(ewa, joanna).
rodzic(ewa, krzysztof).
rodzic(robert, radek).
rodzic(robert, beata).
rodzic(agata, radek).
rodzic(agata, beata).
rodzic(jan, darek).
rodzic(jan, tomek).
rodzic(anna, darek).
rodzic(anna, tomek).
rodzic(krzysztof, jacek).
rodzic(krzysztof, iwona).
rodzic(agnieszka, jacek).
rodzic(agnieszka, iwona).

małżeństwo(maria, piotr).
małżeństwo(adam, ewa).
małżeństwo(robert, agata).
małżeństwo(jan, anna).
małżeństwo(krzysztof, agnieszka).

matka(X, Y) :- kobieta(X), rodzic(X, Y).
ojciec(X, Y) :- mężczyzna(X), rodzic(X, Y).
rodzeństwo(X, Y) :- rodzic(Z, X), rodzic(Z, Y), X\=Y.
siostra(X, Y) :- rodzeństwo(X, Y), kobieta(X).
brat(X, Y) :- rodzeństwo(X, Y), mężczyzna(X).
babcia(X, Y) :- rodzic(X, Z), rodzic(Z, Y), kobieta(X).
dziadek(X, Y) :- rodzic(X, Z), rodzic(Z, Y), mężczyzna(X).
wuj(X, Y) :- rodzic(Z, Y), brat(X, Z), kobieta(Z).
stryj(X, Y) :- rodzic(Z, Y), brat(X, Z), mężczyzna(Z).
kuzyn(X, Y) :- rodzic(A, X), rodzic(B, Y), rodzeństwo(A, B), mężczyzna(X).

teściowa(X, Y) :- małżeństwo(Y, Z), kobieta(Z), matka(X, Z).
teściowa(X, Y) :- małżeństwo(Z, Y), kobieta(Z), matka(X, Z).
szwagier(X, Y) :- małżeństwo(Y, Z), kobieta(Z), brat(X, Z).
szwagier(X, Y) :- małżeństwo(Z, Y), kobieta(Z), brat(X, Z).
szwagier(X, Y) :- siostra(Z, Y), małżeństwo(Z, X), mężczyzna(X).
szwagier(X, Y) :- siostra(Z, Y), małżeństwo(X, Z), mężczyzna(X).