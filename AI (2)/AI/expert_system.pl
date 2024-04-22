% Define facts about animals
has_hair(dog).
has_hair(cat).
has_feathers(sparrow).
has_scales(fish).

% Define rules to classify animals
mammal(X) :- has_hair(X).
bird(X) :- has_feathers(X).
fish(X) :- has_scales(X).

% Define a rule to identify unknown animals
unknown(animal) :- not(mammal(animal)), not(bird(animal)), not(fish(animal)).

% Example queries
% To use this mini expert system, you can query whether a given animal is a mammal, bird, or fish.

% Is a dog a mammal?
% ?- mammal(dog).
% Output: true

% Is a sparrow a bird?
% ?- bird(sparrow).
% Output: true

% Is a goldfish a fish?
% ?- fish(goldfish).
% Output: false

% What kind of animal is a snake?
% ?- unknown(snake).
% Output: true
