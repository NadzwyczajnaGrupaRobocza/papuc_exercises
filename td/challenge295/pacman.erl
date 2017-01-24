-module(pacman).
-export([getMaxPacgums/0]).
-export([parseLine/1]).


getNumberOfMoves({ok, [N]}) ->
	N;

getNumberOfMoves(_) ->
	invalid_number_of_moves.



parseLine([$X | Tail]) ->
	[wall | parseLine(Tail)];

parseLine([$C | Tail]) ->
	[pacman | parseLine(Tail)];

parseLine([String | Tail]) ->
	Integer = case string:to_integer([String]) of
			{Int, _} ->
				  Int;
			  _ ->
				  0
		  end,
	[Integer | parseLine(Tail)];

parseLine(_) ->
	[].


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
	LineInAtoms = parseLine(string:left(Line, LineLen)),
	[LineInAtoms | getFields()].


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

