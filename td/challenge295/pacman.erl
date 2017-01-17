-module(pacman).
-export([getMaxPacgums/0]).

getNumberOfMoves({ok, [N]}) ->
	N;

getNumberOfMoves(_) ->
	invalid_number_of_moves.

getMaxPacgums() ->
	getNumberOfMoves(io:fread("", "~d")).
