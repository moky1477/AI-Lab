% Facts
male(aryan).
male(siddharth).
male(rajan).
female(saylee).
female(manda).
female(pallavi).
parent(siddharth, aryan).
parent(saylee, aryan).
parent(manda, siddharth).
parent(rajan, siddharth).
parent(manda, pallavi).
parent(rajan, pallavi).

% Rules
father(X, Y) :- male(X), parent(X, Y).
mother(X, Y) :- female(X), parent(X, Y).
grandparent(X, Z) :- parent(X, Y), parent(Y, Z).
sibling(X, Y) :- parent(Z, X), parent(Z, Y), X \= Y.

% Custom rule to print a family tree
print_family_tree :-
    write("Family Tree:\n"),
    print_family_member(aryan).

% Custom rule to print information about a family member
print_family_member(Member) :-
    father(Father, Member),
    write(Member),
    write(" (child of "),
    write(Father),
    write(")\n"),
    fail.
print_family_member(Member) :-
    mother(Mother, Member),
    write(Member),
    write(" (child of "),
    write(Mother),
    write(")\n"),
    fail.
print_family_member(_).

% Custom rule to start printing the family tree
start_printing :-
    print_family_tree,
    halt.