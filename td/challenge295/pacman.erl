-module(pacman).
-export([getMaxPacgums/0]).

getNumberOfMoves({ok, [N]}) ->
	N;

getNumberOfMoves(_) ->
	invalid_number_of_moves.

getFields(eof) ->
	%io:format("Get Fields empty~n", []),
	%io:format(standard_error, "EOF", []),
	[];

getFields({error, Info}) ->
	io:format("Get Fields error: ~p~n", [Info]);
	%io:format(standard_error, "Erros~n", []).

getFields(Line) ->
	%io:format("Get Fields line read~n", []),
	%io:format(standard_error, "~s~n", [Line]),
	LineLen = string:len(Line) - 1,
	[string:left(Line, LineLen) | getFields()].

getFields() ->
	%io:format(standard_error, "Get", []),
	getFields(io:get_line("")).

handleNumberOfMoves(invalid_number_of_moves) ->
	void;

handleNumberOfMoves(_) ->
	getFields().

getMaxPacgums() ->
	N = getNumberOfMoves(io:fread("", "~d")),
	io:format("N:~w~n", [N]),
	Fields = handleNumberOfMoves(N),
	io:format("Readed fields ~p~n", [Fields]).
