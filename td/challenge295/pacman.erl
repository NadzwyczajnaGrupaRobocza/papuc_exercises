-module(pacman).
-export([getMaxPacgums/0]).

getNumberOfMoves({ok, [N]}) ->
	N;

getNumberOfMoves(_) ->
	invalid_number_of_moves.

getFields() ->
	io:fread("", "~s").

handleNumberOfMoves(invalid_number_of_moves) ->
	void;

handleNumberOfMoves(_) ->
	getFields().

getMaxPacgums() ->
	N = getNumberOfMoves(io:fread("", "~d")),
	io:format("N:~w~n", [N]),
	handleNumberOfMoves(N).
